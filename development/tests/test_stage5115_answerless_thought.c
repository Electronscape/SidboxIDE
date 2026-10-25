/* Stage 5.115: 'THIS dialogue' must work with no Answer text. */
#include "adventureruntime.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

static unsigned forest_thought, third_row_thought, selectable_thought, npc_dialogue;
static unsigned events;
void test_colour(uint8_t value) { (void)value; }
void test_rect(int x,int y,int w,int h) { (void)x;(void)y;(void)w;(void)h; }
void test_bob(gfxbob_t *bob) { (void)bob; }
void test_text(int x,int y,const char *text)
{
    (void)x;(void)y;
    if (!text) return;
    if (strstr(text,"STILL WARM")) ++forest_thought;
    if (strstr(text,"THIRD ROW")) ++third_row_thought;
    if (strstr(text,"SELECTABLE THOUGHT")) ++selectable_thought;
    if (strstr(text,"FOREST NPC")) ++npc_dialogue;
}
static void action(uint16_t event,void *user)
{ (void)event; (void)user; ++events; }
static const game_adventure_node_t nodes[]={
    {.speaker="Big Steve",.text="FOREST NPC thanks Kim",.choices={
        {.label="",.reply="STILL WARM",.next=2,.requires=-1,.give=-1,.take=-1,.action=19},
        {0},{0}}},
    {.speaker="Big Steve",.text="Other answerless",.choices={
        {0},{0},{.label="",.reply="THIRD ROW",.next=2,.requires=-1,.give=-1,.take=-1,.action=18}}},
    {.speaker="Big Steve",.text="With answer",.choices={
        {.label="Continue",.reply="SELECTABLE THOUGHT",.next=-1,.requires=-1,.give=-1,.take=-1,.action=17},
        {0},{0}}},
    {.speaker="Big Steve",.text="Has answer but no selection in message mode",.choices={
        {.label="Continue",.reply="STILL WARM",.next=-1,.requires=-1,.give=-1,.take=-1,.action=17},
        {0},{0}}},
    {.speaker="Big Steve",.text="Legacy NEXT without answer",.choices={
        {.label="",.reply="STILL WARM",.next=2,.requires=-1,.give=-1,.take=-1,.action=19},
        {0},{0}}},
    {.speaker="Big Steve",.text="Empty player speech",.choices={
        {.label="",.reply="",.next=2,.requires=-1,.give=-1,.take=-1,.action=19},
        {0},{0}}}
};
static const uint8_t flags[]={
    2,0,0, 0,0,2, 2,0,0, 2,0,0, 1,0,0, 2,0,0
};
static void reset_paint(void)
{
    forest_thought=third_row_thought=selectable_thought=npc_dialogue=0;
    game_adventure_draw(0,0,0,0);
}
static void tick(uint8_t press) { (void)game_adventure_input(press,0,0,16,16,600); }
static void setup(void)
{
    static const uint16_t skin[9]={0};
    game_adventure_start(0,0,nodes,6,0,0,0,0,0,8,skin,1,action,0);
    game_adventure_thought_choices(flags,(uint16_t)sizeof(flags));
    game_adventure_thought_box(24,12,300,70,skin,0);
    events=0;
}
int main(void)
{
    setup();
    assert(game_adventure_trigger_dialogue(0));
    tick(0);reset_paint();
    assert(forest_thought>0 && npc_dialogue>0);
    assert(events==0); /* A blank answer must NEVER fire an action. */
    tick(BTN_FIRE2);tick(0);reset_paint();
    assert(!game_adventure_open()); /* Fire2 closes, not a fake answer. */
    assert(forest_thought==0 && events==0);

    /* The first flagged non-empty speech row wins, even if it is Choice 3. */
    setup(); assert(game_adventure_trigger_dialogue(1));
    tick(0);reset_paint();assert(third_row_thought>0 && events==0);
    tick(BTN_FIRE2);assert(!game_adventure_open());assert(events==0);

    /* Ordinary actual answer continues to show the selected thought. */
    setup(); assert(game_adventure_trigger_dialogue(2));
    tick(0);reset_paint();assert(selectable_thought>0 && forest_thought==0);
    tick(BTN_FIRE2);assert(events==1);
    assert(!game_adventure_open());

    /* Trigger Message hides labelled answers but shows node-only thoughts. */
    setup(); assert(game_adventure_trigger_message(3));
    tick(0);reset_paint();assert(forest_thought==0 && events==0);
    tick(BTN_FIRE2);assert(!game_adventure_open());
    setup(); assert(game_adventure_trigger_message(0));
    tick(0);reset_paint();assert(forest_thought>0 && events==0);
    tick(BTN_FIRE2);assert(!game_adventure_open());

    /* Legacy NEXT can't make a no-answer 'this-dialogue' bubble. */
    setup(); assert(game_adventure_trigger_dialogue(4));
    tick(0);reset_paint();assert(forest_thought==0);
    tick(BTN_FIRE2);assert(!game_adventure_open());

    /* Don't show a bubble for blank Player speech. */
    setup(); assert(game_adventure_trigger_dialogue(5));
    tick(0);reset_paint();assert(forest_thought==0 && third_row_thought==0);
    tick(BTN_FIRE2);assert(!game_adventure_open());
    puts("Stage 5.115: Fire2-only thought bubbles, selectable answers, and message mode PASS");
    return 0;
}
