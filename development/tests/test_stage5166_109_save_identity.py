#!/usr/bin/env python3
"""Stage 5.166.109: native v3 save validation and source-side identity coverage.

Compiles actual generated gameworlds.rulec with host GCC + SIDBOX file I/O mocks.
No Qt required. The IDE-side Qt compilation still needs Fedora.
"""
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'development/tests'))
from test_stage5163_rules_flow_audit import render

FLAGS = {'HAS_ADVENTURE_RUNTIME':False,'HAS_PICKUPS':False,'HAS_SHARED_PLAYER':False,
         'HAS_WORLD_PHYSICS':False,'HAS_PLAYER_VISIBILITY':False,'HAS_TITLE':False,'HAS_MAP':False}
QUESTS = '''#define GW_QUEST_COUNT 0u
#define GW_OBJECTIVE_COUNT 0u
typedef struct {const char *id,*title,*description,*requires,*excludes;uint16_t first,count;uint8_t initially_hidden;} gw_quest_def_t;
typedef struct {const char *id,*title,*kind,*target,*hint;} gw_objective_def_t;
static const gw_quest_def_t gw_quest_defs[]={{0}};
static const gw_objective_def_t gw_objective_defs[]={{0}};
'''
DECLS = '''static void fake_save(void (*)(const void*,uint32_t,void*),void*);
static uint8_t fake_import(uint8_t (*)(void*,uint32_t,void*),void*);'''
RECORD = '''{.name="world1",.start_x=10,.start_y=20,.start_facing=1,
.object_disk_export=fake_save,.story_disk_export=fake_save,
.object_disk_import=fake_import,.story_disk_import=fake_import}'''
NATIVE = (ROOT/'development/tests/test_stage5164_save_load_native.c').read_text()
# Reuse the full, real SIDBOX FileIO simulator from Stage 5.164.
SIMULATOR = NATIVE.split('int main(void)',1)[0]
MAIN = r'''
int main(int argc,char **argv)
{
    assert(argc==2);
    mock_api.system=&systems;
    (void)mkdir(TEST_FS_ROOT,0700);
    (void)mkdir(TEST_FS_ROOT "/game",0700);
    if(strcmp(argv[1],"write")==0){
        active_world=&worlds[0];persistent.health=42;fake_data=13;
        assert(gameworlds_save_slot(0));
        persistent.health=66;fake_data=99;
        assert(gameworlds_save_slot(0));
        assert(gameworlds_slot_exists(0));
    }else if(strcmp(argv[1],"valid")==0){
        assert(gameworlds_slot_exists(0));
        assert(gameworlds_load_slot(0));
        assert(fake_data==99 && persistent.health==66);
    }else if(strcmp(argv[1],"reject")==0){
        /* A mismatched layout must not touch existing data or player state. */
        assert(!gameworlds_slot_exists(0));
        fake_data=777;persistent.health=88;
        assert(!gameworlds_load_slot(0));
        assert(fake_data==777 && persistent.health==88);
    }else if(strcmp(argv[1],"corruptA")==0 || strcmp(argv[1],"corruptB")==0){
        char path[40];gw_save_filename(path,0,argv[1][7]);
        FILE *f=fopen(pathmap(path),"r+b");assert(f);
        gw_save_header_t h={0};assert(fread(&h,sizeof(h),1,f)==1);
        assert(h.version==GW_SAVE_VERSION);
        h.identity ^= 0x1010000100000101ULL;
        rewind(f);assert(fwrite(&h,sizeof(h),1,f)==1);
        fclose(f);
    }else if(strcmp(argv[1],"fallback")==0){
        assert(gameworlds_slot_exists(0));
        assert(gameworlds_load_slot(0));
        assert(fake_data==99 && persistent.health==66);
    }else if(strcmp(argv[1],"oldVersion")==0){
        /* Both banks are syntactically v2: no proof of identity -> reject. */
        for(int i=0;i<2;++i){
            char path[40];gw_save_filename(path,0,i?'B':'A');
            FILE *f=fopen(pathmap(path),"r+b");assert(f);
            gw_save_header_t h={0};assert(fread(&h,sizeof(h),1,f)==1);
            h.version=2u;
            rewind(f);assert(fwrite(&h,sizeof(h),1,f)==1);
            fclose(f);
        }
    }else {assert(0 && "unknown test action");}
    return 0;
}
'''

class SaveIdentity(unittest.TestCase):
    def test_export_identity_uses_stable_uuid_order_and_frozen_manifest(self):
        text=(ROOT/'gameworldsnapshot.h').read_text()
        self.assertIn('identity.append(id);',text)
        self.assertIn('identity.append(type);',text)
        self.assertIn('if (type==QStringLiteral("collectable")) pickups.append(identity);',text)
        self.assertIn('else objects.append(identity);',text)
        self.assertIn('layout.insert(QStringLiteral("nodes"),adventure.value',text)
        self.assertIn('manifest.insert(QStringLiteral("saveLayoutDigest"), saveLayoutDigest);',text)
        self.assertIn('publishedSaveLayouts.insert(name, layoutDigest);',text)
        self.assertIn('QCryptographicHash::Sha256',text)
        self.assertIn('generated.replace("@IDE{SAVE_IDENTITY}",identityLiteral)',text)
        self.assertIn('Open and re-export that world',text)
        self.assertIn('Build: 5.166.113.291026',(ROOT/'splashscreenwidget.cpp').read_text())

    def test_native_dual_bank_header_checksum_and_identity(self):
        folder=ROOT/'idelibs/codehelpers/game'
        base=render((folder/'gameworlds.rulec').read_text(), FLAGS)
        header=render((folder/'gameworlds.ruleh').read_text(), FLAGS)
        base=(base.replace('@IDE{WORLD_DECLARATIONS}',DECLS)
             .replace('@IDE{WORLD_RECORDS}',RECORD)
             .replace('@IDE{SAVE_KEY}','123')
             .replace('@IDE{QUEST_DATA}',QUESTS))
        self.assertIn('GW_SAVE_VERSION 3u',base)
        self.assertIn('temp.identity!=GW_SAVE_IDENTITY',base)
        self.assertIn('header.identity=GW_SAVE_IDENTITY',base)
        self.assertIn('header.checksum=gw_save_checksum(',base)
        self.assertIn('const char bank=!va',base)
        with tempfile.TemporaryDirectory(prefix='cg5166_109_') as root:
            project=Path(root)
            def compile_binary(ident: str, name: str):
                (project/'gameworlds.c').write_text(base.replace('@IDE{SAVE_IDENTITY}', ident))
                (project/'gameworlds.h').write_text(header)
                source=project/(name+'.c');source.write_text(SIMULATOR+MAIN)
                executable=project/name
                subprocess.run(['gcc','-std=gnu11','-O0','-ffunction-sections','-fdata-sections',
                    '-Wl,--gc-sections','-Wno-unused-function','-Wno-unused-variable',
                    '-I',str(project),'-I',str(ROOT/'idelibs/api'),'-I',str(folder),
                    f'-DTEST_FS_ROOT="{project}/fs"',str(source),'-o',str(executable)],
                    check=True, capture_output=True, text=True)
                return executable
            correct=compile_binary('0x0123456789abcdef','correct')
            wrong=compile_binary('0x1111456789abcdef','wrong')
            def run(bin,name):
                subprocess.run([str(bin),name],check=True,capture_output=True,text=True)
            run(correct,'write')
            run(correct,'valid')
            # Two structurally identical save blobs, different compiled object IDs:
            run(wrong,'reject')
            run(correct,'corruptA')
            run(correct,'fallback')
            run(correct,'corruptB')
            run(correct,'reject')
            run(correct,'write')
            run(correct,'oldVersion')
            run(correct,'reject')

if __name__=='__main__':unittest.main()
