/* Stage 5.114: dialogue-local thought bubbles and legacy NEXT mode. */
#include "adventureruntime.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

static unsigned alpha, beta, local_next, inherited, dialogue_next, ordinary;
static unsigned actions;
void test_colour(uint8_t value) { (void)value; }
void test_rect(int x,int y,int w,int h) { (void)x;(void)y;(void)w;(void)h; }
void test_bob(gfxbob_t *bob) { (void)bob; }
void test_text(int x,int y,const char *text)
{
    (void)x;(void)y;
    if (!text) return;
    if (strstr(text,"ALPHA THOUGHT")) ++alpha;
    if (strstr(text,"BETA THOUGHT")) ++beta;
    if (strstr(text,"NODE1 THOUGHT")) ++local_next;
    if (strstr(text,"LEGACY THOUGHT")) ++inherited;
    if (strstr(text,"NEXT DIALOGUE")) ++dialogue_next;
    if (strstr(text,"ordinary speech")) ++ordinary;
}
static void action(uint16_t id,void *ctx) { (void)id; (void)ctx; ++actions; }
static const game_adventure_node_t nodes[]={
    {.speaker="Steve",.text="CURRENT DIALOGUE",.choices={
        {.label="First",.reply="ALPHA THOUGHT",.next=1,.requires=-1,.give=-1,.take=-1,.action=17},
        {.label="Second",.reply="BETA THOUGHT",.next=1,.requires=-1,.give=-1,.take=-1,.action=18},
        {.label="Third",.reply="ordinary speech",.next=1,.requires=-1,.give=-1,.take=-1,.action=19}}},
    {.speaker="Steve",.text="NEXT DIALOGUE",.choices={
        {.label="Thinking",.reply="NODE1 THOUGHT",.next=-1,.requires=-1,.give=-1,.take=-1,.action=-1},
        {.label="Plain",.reply="",.next=-1,.requires=-1,.give=-1,.take=-1,.action=-1},{0}}},
    {.speaker="Steve",.text="LEGACY START",.choices={
        {.label="Continue",.reply="LEGACY THOUGHT",.next=1,.requires=-1,.give=-1,.take=-1,.action=-1},{0},{0}}},
    {.speaker="Steve",.text="EMPTY SPEECH",.choices={
        {.label="Continue",.reply="",.next=1,.requires=-1,.give=-1,.take=-1,.action=-1},{0},{0}}}
};
static const uint8_t flags[12]={2,2,0, 2,0,0, 1,0,0, 2,0,0};
static void tick(uint8_t b) { (void)game_adventure_input(b,0,0,16,16,600); }
static void paint(void) { game_adventure_draw(0,0,0,0); }
static void clear_counts(void) { alpha=beta=local_next=inherited=dialogue_next=ordinary=0; }
static void setup(void)
{
    static const uint16_t skin[9]={0};
    game_adventure_start(0,0,nodes,4,0,0,0,0,0,8,skin,1,action,0);
    game_adventure_thought_choices(flags,12);
    game_adventure_thought_box(30,10,300,70,skin,0);
    actions=0;
}
int main(void)
{
    setup();
    assert(game_adventure_trigger_dialogue(0));
    tick(0);clear_counts();paint();
    assert(alpha>0 && beta==0 && ordinary==0);
    assert(actions==0); /* Merely highlighting is not a gameplay choice. */

    tick(BTN_DOWN);clear_counts();paint();
    assert(beta>0 && alpha==0 && actions==0);
    tick(0);tick(BTN_DOWN);clear_counts();paint();
    assert(alpha==0 && beta==0 && ordinary==0);
    tick(0);tick(BTN_UP);clear_counts();paint();
    assert(beta>0 && alpha==0);

    tick(0);tick(BTN_FIRE2);tick(0);clear_counts();paint();
    assert(dialogue_next>0 && beta==0 && ordinary==0);
    assert(local_next>0); /* Second dialogue's own preview takes priority. */
    assert(actions==1); /* Real choice fires once. */

    /* Legacy bit 0 still means ONLY with NEXT dialogue. */
    setup();assert(game_adventure_trigger_dialogue(2));
    tick(0);clear_counts();paint();assert(inherited==0);
    tick(BTN_FIRE2);tick(0);clear_counts();paint();
    assert(dialogue_next>0 && local_next>0 && inherited==0);
    tick(BTN_DOWN);clear_counts();paint();
    assert(inherited>0 && local_next==0); /* Falls back to inherited thought. */
    assert(actions==0);

    /* Trigger Message hides answer choices: no local bubble leaks in. */
    setup();assert(game_adventure_trigger_message(0));
    tick(0);clear_counts();paint();
    assert(alpha==0 && beta==0 && actions==0);

    /* Message sequence follows the same selected-choice previews, no actions. */
    setup();assert(game_adventure_trigger_sequence(0));
    tick(0);clear_counts();paint();assert(alpha>0);
    tick(BTN_DOWN);clear_counts();paint();assert(beta>0 && alpha==0);
    tick(0);tick(BTN_FIRE2);tick(0);clear_counts();paint();
    assert(dialogue_next>0 && local_next>0 && beta==0 && actions==0);

    /* An empty Player speech is not replaced by the answer's label. */
    setup();assert(game_adventure_trigger_dialogue(3));
    tick(0);clear_counts();paint();
    assert(alpha==0 && beta==0 && local_next==0 && inherited==0 && ordinary==0);
    tick(BTN_FIRE2);tick(0);clear_counts();paint();
    assert(dialogue_next>0 && local_next>0 && actions==0);
    puts("Stage 5.114: this/next thought timing, answer switching, triggers PASS");
    return 0;
}
