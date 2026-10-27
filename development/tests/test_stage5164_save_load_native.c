/* Stage 5.164: use the public SIDBOX file-I/O API against a native TFCard
 * stub.  The generated single-world manager is included below. */
#include "apis.h"
#undef API
static API_Root mock_api;
#define API ((volatile const API_Root *)&mock_api)
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "gameworlds.c"
static int32_t fake_data=77;
static void fake_save(void (*emit)(const void*,uint32_t,void*),void *ctx)
{ emit(&fake_data,sizeof(fake_data),ctx); }
static uint8_t fake_import(uint8_t (*take)(void*,uint32_t,void*),void *ctx)
{ return take(&fake_data,sizeof(fake_data),ctx); }
static FILE *current;
static char pathbuf[512];
static char *pathmap(const char *p)
{
    /* Absolute paths map to TFCard root; relative paths map to the
     * simulated launcher working directory containing platform3.app. */
    snprintf(pathbuf,sizeof(pathbuf),"%s%s%s",TEST_FS_ROOT,
             (*p=='/') ? "" : "/game/", p);
    return pathbuf;
}
static FRESULT fsopen(uint8_t n,char *path,uint8_t mode)
{(void)n;current=fopen(pathmap(path),(mode&SD_WRITE)?"wb":"rb");return current?FR_OK:FR_NO_FILE;}
static uint32_t fslen(uint8_t n)
{(void)n;long x=ftell(current);fseek(current,0,SEEK_END);long z=ftell(current);fseek(current,x,SEEK_SET);return (uint32_t)z;}
static FRESULT fsread(uint8_t n,void *v,uint32_t l,uint32_t *r)
{(void)n;*r=(uint32_t)fread(v,1,l,current);return FR_OK;}
static FRESULT fswrite(uint8_t n,const void *v,uint32_t l,uint32_t *r)
{(void)n;*r=(uint32_t)fwrite(v,1,l,current);return *r==l?FR_OK:FR_DISK_ERR;}
static FRESULT fsclose(uint8_t n)
{(void)n;int e=fclose(current);current=NULL;return e?FR_DISK_ERR:FR_OK;}
static FRESULT fsmkdir(char *p)
{return mkdir(pathmap(p),0700)==0?FR_OK:FR_EXIST;}
static const API_FILEIO fs={.sbopen=fsopen,.sbfilelen=fslen,.sbread=fsread,
                            .sbwrite=fswrite,.sbclose=fsclose,.sbmkdir=fsmkdir};
static const API_SYSTEMS systems={.sys_fileio=&fs};
int main(void)
{
    mock_api.system=&systems;
    (void)mkdir(TEST_FS_ROOT,0700);
    (void)mkdir(TEST_FS_ROOT "/game",0700);
    active_world=&worlds[0];persistent.health=45;persistent.lives=3;
    inventory_put("Ruby Key",7,0);
    assert(gameworlds_save_slot(0)); assert(gameworlds_slot_exists(0));
    fake_data=79;persistent.health=31;assert(gameworlds_save_slot(0));
    active_world=NULL;fake_data=0;persistent.health=0;inventory_count=0;
    assert(gameworlds_load_slot(0));
    assert(fake_data==79 && persistent.health==31 && persistent.lives==3);
    assert(inventory_count==1 && inventory[0].amount==7 && strcmp(inventory[0].name,"Ruby Key")==0);
    assert(strcmp(gameworlds_saved_world(),"world1")==0);
    active_world=&worlds[0];gameworlds_spawn_t position={0};
    assert(gameworlds_player_start(&position) && position.x==10 && position.y==20);
    /* Recompute the checksum after malicious structural corruption, to
     * exercise full-payload fallback rather than just checksum checking. */
    char filename[40];gw_save_filename(filename,0,'B');
    FILE *f=fopen(pathmap(filename),"r+b");assert(f);
    gw_save_header_t header={0}; assert(fread(&header,sizeof(header),1,f)==1);
    uint8_t *payload=(uint8_t *)malloc(header.length);assert(payload);
    assert(fread(payload,header.length,1,f)==1);
    uint32_t invalid_world=UINT32_MAX;
    memcpy(payload+sizeof(gameworlds_player_state_t),&invalid_world,sizeof(invalid_world));
    header.checksum=gw_save_checksum(payload,header.length);
    rewind(f);assert(fwrite(&header,sizeof(header),1,f)==1);
    assert(fwrite(payload,header.length,1,f)==1);
    fclose(f);free(payload);
    active_world=NULL;fake_data=0;persistent.health=0;inventory_count=0;
    assert(gameworlds_slot_exists(0));assert(gameworlds_load_slot(0));
    assert(fake_data==77 && persistent.health==45);
    /* A queued checkpoint saves at a frame boundary, not in the callback. */
    active_world=&worlds[0];
    assert(gameworlds_checkpoint_request(2));
    assert(gameworlds_apply_pending());
    assert(gameworlds_save_status()==1 && gameworlds_slot_exists(2));
    assert(gameworlds_save_status()==0);
    /* Refuse a slot once every independent bank is invalid. */
    gw_save_filename(filename,0,'A');f=fopen(pathmap(filename),"wb");assert(f);fclose(f);
    assert(!gameworlds_slot_exists(0));assert(!gameworlds_load_slot(0));
    /* A Stage 5.164.4 bank stored at TFCard root must remain readable.
     * Saving again creates a game-local file without damaging the legacy one. */
    fake_data=123;persistent.health=91;active_world=&worlds[0];
    assert(gameworlds_save_slot(4));
    char source[512], destination[512];
    gw_save_filename(filename,4,'A');strcpy(source,pathmap(filename));
    assert(fsmkdir("/CGSAVES")==FR_OK);
    gw_save_legacy_filename(filename,4,'A');strcpy(destination,pathmap(filename));
    assert(rename(source,destination)==0);
    active_world=NULL;fake_data=0;persistent.health=0;
    assert(gameworlds_slot_exists(4));assert(gameworlds_load_slot(4));
    assert(fake_data==123 && persistent.health==91);
    active_world=&worlds[0];fake_data=124;persistent.health=92;
    assert(gameworlds_save_slot(4));
    gw_save_filename(filename,4,'A');
    FILE *local=fopen(pathmap(filename),"rb");assert(local);fclose(local);
    FILE *legacy=fopen(destination,"rb");assert(legacy);fclose(legacy);
    active_world=NULL;fake_data=0;persistent.health=0;
    assert(gameworlds_load_slot(4));
    assert(fake_data==124 && persistent.health==92);
    printf("PASS Stage 5.164.5: game-local saves, legacy migration, dual-bank recovery\n");
    return 0;
}
