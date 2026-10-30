/* Stage 5.165: builds against the same generated world manager and fake TFCard. */
#define main previous_save_suite
#include "test_stage5164_save_load_native.c"
#undef main
int main(void)
{
    assert(previous_save_suite()==0);
    active_world=&worlds[0];
    gw_quest_reset();
    assert(gameworlds_quest_count()==3);
    assert(gameworlds_quest_status(0)==1);
    assert(gameworlds_quest_status(1)==0);
    assert(gameworlds_quest_status(2)==1);
    assert(gameworlds_quest_track("side"));
    assert(gameworlds_quest_tracked()==2);
    assert(gameworlds_quest_event("opened_door")==1);
    /* Inventory already contains Ruby Key and the second objective advances. */
    assert(gameworlds_quest_status(0)==2);
    assert(gameworlds_quest_status(1)==1);
    assert(gameworlds_quest_status(2)==3);
    assert(gameworlds_quest_event_number(41)==0);
    assert(gameworlds_quest_event_number(42)==1);
    assert(gameworlds_quest_status(1)==2);
    assert(gameworlds_quest_tracked()==-1);
    assert(gameworlds_save_slot(7));
    active_world=NULL;
    gw_quest_reset();
    assert(gameworlds_load_slot(7));
    assert(gameworlds_quest_status(0)==2);
    assert(gameworlds_quest_status(1)==2);
    assert(gameworlds_quest_status(2)==3);
    /* Recreate an actual v1-format save: same body, no quest extension. */
    active_world=&worlds[0];
    assert(gameworlds_save_slot(8));
    char name[40];gw_save_filename(name,8,'A');
    FILE *f=fopen(pathmap(name),"rb");assert(f);
    gw_save_header_t head;assert(fread(&head,sizeof(head),1,f)==1);
    uint8_t *data=(uint8_t *)malloc(head.length);assert(data);
    assert(fread(data,1,head.length,f)==head.length);fclose(f);
    head.version=1;
    head.length-=(uint32_t)sizeof(gw_save_quests_t);
    head.checksum=gw_save_checksum(data,head.length);
    f=fopen(pathmap(name),"wb");assert(f);
    assert(fwrite(&head,sizeof(head),1,f)==1);
    assert(fwrite(data,1,head.length,f)==head.length);
    fclose(f);free(data);
    active_world=NULL;gw_quest_reset();
    assert(!gameworlds_slot_exists(8));
    assert(!gameworlds_load_slot(8)); /* v1 lacks trusted object identity. */
    assert(gameworlds_quest_status(0)==1); /* reset remains untouched */
    assert(gameworlds_quest_status(1)==0);
    assert(gameworlds_quest_status(2)==1);
    puts("PASS Stage 5.166.109: quests, tracking, Adventure events, v3 saves and safe v1 rejection");
    return 0;
}
