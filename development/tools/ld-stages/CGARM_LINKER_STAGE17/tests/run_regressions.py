from pathlib import Path
import subprocess
root=Path('/mnt/data/CGARM_LINKER_STAGE17/tests')
bin=str(root/'cgarm-v2-compare')
P=Path('/mnt/data/CGARM_LINKER_STAGE13/tests')
Q=Path('/mnt/data/CGARM_LINKER_STAGE10/tests')
R=Path('/mnt/data/CGARM_LINKER_STAGE12/tests')

def test(name, arguments, expected=True, phrase=''):
    res=subprocess.run([bin,*map(str,arguments)],capture_output=True,text=True)
    (root/(name+'.log')).write_text(res.stdout+'\n'+res.stderr)
    good=(res.returncode==0)==expected and (not phrase or phrase in res.stdout+res.stderr)
    print(('PASS' if good else 'FAIL'), name, 'rc=',res.returncode,'signature=', (res.stderr.strip()[-200:] if res.returncode else res.stdout.splitlines()[-3:]))
    if not good:raise SystemExit(1)
    return res

runtime=[Q/'runtime-cg.elf',Q/'runtime-cg.app',Q/'runtime-llvm.elf',Q/'runtime-llvm.app','--cg-map',Q/'runtime-cg.cgmap','--llvm-map',Q/'runtime-llvm.map','--objects','/mnt/data/cgarm_stage4_work/runtimewithptr.o', '--archives','/mnt/data/libcgarm.a','--min-matched','0']
test('archive-runtime-positive',runtime,True,'Selected library members:  1')
test('archive-runtime-no-archives',runtime[:runtime.index('--archives')]+['--min-matched','0'],True,'PASS:')
test('archive-runtime-wrong-library',runtime[:runtime.index('--archives')]+['--archives','/mnt/data/sb3dlibrary.a','--min-matched','0'],False,'selected archive member not supplied')
mutdir=root/'mutated';mutdir.mkdir(exist_ok=True)
original=bytearray(Path('/mnt/data/libcgarm.a').read_bytes())
# alter one selected member without changing archive structure or member size
idx=original.find(b'cgarm_memory.o')
assert idx!=-1
head=idx; assert original[head+58:head+60]==b'`\n'
start=head+60; assert original[start:start+4]==b'\x7fELF'
original[start+70]^=0x01
(mutdir/'libcgarm.a').write_bytes(original)
test('archive-selected-member-corruption',runtime[:runtime.index('--archives')]+['--archives',mutdir/'libcgarm.a','--min-matched','0'],False,'Selected archive member has changed')
# Should be rejected, not silently ignored.
branch=[P/'anonymous-corrupt.elf',P/'anonymous-corrupt.app',P/'anonymous-llvm.elf',P/'anonymous-llvm.app','--cg-map',P/'anonymous-corrupt.cgmap','--llvm-map',P/'anonymous-llvm.map','--objects',P/'anonymous-caller.o',P/'branch-helper.o','--min-matched','1']
test('corrupt-branch-identity',branch,False,'Thumb destination mismatch')
branch_ok=[P/'anonymous-cg.elf',P/'anonymous-cg.app',P/'anonymous-llvm.elf',P/'anonymous-llvm.app','--cg-map',P/'anonymous-cg.cgmap','--llvm-map',P/'anonymous-llvm.map','--objects',P/'anonymous-caller.o',P/'branch-helper.o','--min-matched','1']
test('anonymous-branch-positive',branch_ok,True,'Exact local destinations: 2')
short=[P/'short-cg.elf',P/'short-cg.app',P/'short-llvm.elf',P/'short-llvm.app','--cg-map',P/'short-cg.cgmap','--llvm-map',P/'short-llvm.map','--objects',P/'short-merge.o','--min-matched','1']
test('merge-short-record-positive',short,True,'Mergeable targets verified:   3')
print('ALL STAGE 15 REGRESSIONS FINISHED')
