#include "adventureruntime.h"
#include "apis.h"
#include <string.h>

/* Bounded static memory: 64 inventory types, up to 3 choices per node. */
#define GA_MAX_ITEMS 64
#define GA_COLS 54 /* 8-pixel-wide glyphs, not 16-pixel glyphs. */
#define GA_LINES 6
static const game_adventure_item_t *ga_items;
static const game_adventure_node_t *ga_nodes;
static const game_adventure_npc_t *ga_npcs;
static uint16_t ga_item_count, ga_node_count, ga_npc_count;
static uint16_t ga_counts[GA_MAX_ITEMS];
static uint8_t ga_state; /* 0 idle, 1 dialogue, 2 inventory, 3 reply */
static uint8_t ga_prev_buttons, ga_choice, ga_inventory_offset;
static uint16_t ga_node, ga_typed, ga_ticks, ga_reply_typed, ga_reply_ticks;
static int16_t ga_after_reply;
static const char *ga_reply;
static int32_t ga_player_x, ga_player_y;
static const uint8_t *ga_skin_pixels;
static uint16_t ga_skin_w, ga_skin_h;
static uint8_t ga_tile, ga_frames_per_char;
static uint16_t ga_skin_indices[9];
static uint8_t ga_text_colour=15, ga_outline_enabled, ga_outline_colour;
static const game_adventure_npc_animation_t *ga_animations;
static uint16_t ga_animation_count, ga_active_npc;
static uint16_t ga_animation_ticks[256];
static uint8_t ga_animation_frames[256], ga_animation_mode[256];
static uint8_t ga_animation_original_index[256];
static game_adventure_action_t ga_action;
static void *ga_user;

void game_adventure_text_style(uint8_t text_index, uint8_t outline_enabled,
                               uint8_t outline_index)
{
    ga_text_colour = text_index;
    ga_outline_enabled = outline_enabled ? 1u : 0u;
    ga_outline_colour = outline_index;
}

void game_adventure_npc_animations(const game_adventure_npc_animation_t *animations,
                                   uint16_t count)
{
    ga_animations = animations;
    ga_animation_count = animations && count <= 256u ? count : (animations ? 256u : 0u);
    memset(ga_animation_ticks, 0, sizeof(ga_animation_ticks));
    memset(ga_animation_frames, 0, sizeof(ga_animation_frames));
    memset(ga_animation_mode, 0xFF, sizeof(ga_animation_mode));
    for (uint16_t i=0; i<ga_animation_count; ++i)
        ga_animation_original_index[i] = animations[i].sprite ? animations[i].sprite->index : 0;
}

/* The animation follows the active conversation, but ticking happens during
   game_adventure_input(), so custom main.c needs no new frame-loop hook. */
static void ga_tick_animations(uint16_t frames)
{
    for (uint16_t i=0; i<ga_animation_count; ++i) {
        const game_adventure_npc_animation_t *a = &ga_animations[i];
        if (!a->sprite || !a->sprite->imgdat) continue;
        const uint8_t speaking = (ga_state == 1u && ga_active_npc == i) ? 1u : 0u;
        uint16_t first = speaking && a->talk_count ? a->talk_first : a->idle_first;
        uint16_t count = speaking && a->talk_count ? a->talk_count : a->idle_count;
        uint16_t rate = speaking && a->talk_count ? a->talk_speed : a->idle_speed;
        if (!count) {
            if (ga_animation_mode[i] != 0xFFu && ga_animation_mode[i] != 0u) {
                a->sprite->index = ga_animation_original_index[i];
                ga_animation_mode[i] = 0u;
            }
            continue;
        }
        if (!rate) rate = 1;
        const uint16_t max_cells = (a->sprite->width && a->sprite->height)
            ? (uint16_t)((a->sprite->atlas_stride / a->sprite->width) *
                         (a->sprite->atlas_height / a->sprite->height)) : 0;
        if (first + count > max_cells || first + count > 256u) continue;
        if (ga_animation_mode[i] != speaking) {
            ga_animation_mode[i] = speaking;
            ga_animation_ticks[i] = 0;
            ga_animation_frames[i] = 0;
        } else {
            const uint32_t total = (uint32_t)ga_animation_ticks[i] + frames;
            ga_animation_frames[i] = (uint8_t)((ga_animation_frames[i] + total / rate) % count);
            ga_animation_ticks[i] = (uint16_t)(total % rate);
        }
        a->sprite->index = (uint8_t)(first + ga_animation_frames[i]);
    }
}

uint8_t game_adventure_open(void) { return ga_state != 0; }
uint16_t game_adventure_quantity(uint16_t i) { return i < ga_item_count ? ga_counts[i] : 0; }
uint16_t game_adventure_add(uint16_t i, uint16_t n)
{
    if (i >= ga_item_count) return 0;
    const uint16_t old = ga_counts[i], max = ga_items[i].capacity;
    const uint32_t wanted = (uint32_t)old + n;
    ga_counts[i] = (uint16_t)(wanted > max ? max : wanted);
    return ga_counts[i] - old;
}
uint8_t game_adventure_remove(uint16_t i, uint16_t n)
{
    if (i >= ga_item_count || ga_counts[i] < n) return 0;
    ga_counts[i] -= n;
    return 1;
}
uint16_t game_adventure_collect(uint16_t kind)
{
    uint16_t matched = 0;
    for (uint16_t i = 0; i < ga_item_count; ++i)
        if (kind && ga_items[i].pickup_kind == kind) {
            game_adventure_add(i, 1); ++matched;
        }
    return matched;
}

void game_adventure_start(const game_adventure_item_t *items, uint16_t item_count,
                          const game_adventure_node_t *nodes, uint16_t node_count,
                          const game_adventure_npc_t *npcs, uint16_t npc_count,
                          const uint8_t *skin_pixels, uint16_t atlas_width,
                          uint16_t atlas_height, uint8_t tile_size,
                          const uint16_t skin_indices[9], uint8_t frames_per_char,
                          game_adventure_action_t action, void *user)
{
    ga_items = items; ga_item_count = item_count > GA_MAX_ITEMS ? GA_MAX_ITEMS : item_count;
    ga_nodes = nodes; ga_node_count = node_count;
    ga_npcs = npcs; ga_npc_count = npc_count;
    memset(ga_counts, 0, sizeof(ga_counts));
    for (uint16_t i = 0; i < ga_item_count; ++i)
        ga_counts[i] = ga_items[i].initial > ga_items[i].capacity
            ? ga_items[i].capacity : ga_items[i].initial;
    ga_state = ga_prev_buttons = ga_choice = ga_inventory_offset = 0;
    ga_active_npc = 0xFFFFu;
    game_adventure_npc_animations(0,0);
    game_adventure_text_style(15,0,0);
    ga_node = ga_typed = ga_ticks = ga_reply_typed = ga_reply_ticks = 0;
    ga_after_reply = -1; ga_reply = 0;
    ga_skin_pixels = skin_pixels; ga_skin_w = atlas_width; ga_skin_h = atlas_height;
    ga_tile = tile_size >= 4 && tile_size <= 32 ? tile_size : 8;
    for (uint8_t i = 0; i < 9; ++i) ga_skin_indices[i] = skin_indices ? skin_indices[i] : i;
    ga_frames_per_char = frames_per_char ? frames_per_char : 2;
    ga_action = action; ga_user = user;
}
static uint8_t ga_has_choices(void)
{
    if (ga_node >= ga_node_count) return 0;
    uint8_t n = 0;
    for (uint8_t i = 0; i < 3; ++i)
        if (ga_nodes[ga_node].choices[i].label && ga_nodes[ga_node].choices[i].label[0]) ++n;
    return n;
}
static uint8_t ga_allowed(const game_adventure_choice_t *c)
{
    return c->requires < 0 || ((uint16_t)c->requires < ga_item_count && ga_counts[c->requires]);
}
static void ga_next_node(int16_t node)
{
    if (node < 0 || node >= ga_node_count) { ga_state = 0; return; }
    ga_node = (uint16_t)node; ga_state = 1;
    ga_choice = 0; ga_typed = 0; ga_ticks = 0;
    const game_adventure_choice_t *options = ga_nodes[ga_node].choices;
    for (uint8_t i=0;i<3;++i)
        if (options[i].label && options[i].label[0]) { ga_choice=i; break; }
}
uint8_t game_adventure_input(uint8_t buttons, int32_t player_x, int32_t player_y,
                             uint16_t player_w, uint16_t player_h, uint16_t frames)
{
    const uint8_t press = (buttons & BTN_FIRE2) && !(ga_prev_buttons & BTN_FIRE2);
    const uint8_t up = (buttons & BTN_UP) && !(ga_prev_buttons & BTN_UP);
    const uint8_t down = (buttons & BTN_DOWN) && !(ga_prev_buttons & BTN_DOWN);
    ga_prev_buttons = buttons;
    ga_tick_animations(frames);
    ga_player_x = player_x; ga_player_y = player_y;
    if (ga_state == 0) {
        if (!press) return 0;
        const int32_t pcx = player_x + player_w / 2, pcy = player_y + player_h / 2;
        for (uint16_t i = 0; i < ga_npc_count; ++i) {
            const game_adventure_npc_t *npc = &ga_npcs[i];
            const int32_t nx = npc->x + npc->width / 2;
            const int32_t ny = npc->y + npc->height / 2;
            const int32_t dx = nx - pcx, dy = ny - pcy;
            if (dx >= -(int32_t)npc->radius && dx <= npc->radius &&
                dy >= -(int32_t)npc->radius && dy <= npc->radius && npc->first_node < ga_node_count) {
                ga_active_npc = i;
                ga_next_node((int16_t)npc->first_node);
                return 1;
            }
        }
        if (buttons & BTN_UP) { ga_state = 2; ga_inventory_offset = 0; return 1; }
        return 0;
    }
    if (ga_state == 2) {
        if (press) { ga_state = 0; return 0; }
        if (down && ga_inventory_offset + GA_LINES < ga_item_count) ++ga_inventory_offset;
        if (up && ga_inventory_offset) --ga_inventory_offset;
        return 1;
    }
    if (ga_state == 3) {
        if (ga_reply && ga_reply_typed < strlen(ga_reply)) {
            const uint32_t elapsed = (uint32_t)ga_reply_ticks + frames;
            ga_reply_typed += elapsed / ga_frames_per_char;
            ga_reply_ticks = (uint16_t)(elapsed % ga_frames_per_char);
            if (ga_reply_typed > strlen(ga_reply)) ga_reply_typed = (uint16_t)strlen(ga_reply);
        }
        if (press) ga_next_node(ga_after_reply);
        return 1;
    }
    if (ga_node >= ga_node_count) { ga_state = 0; return 0; }
    const game_adventure_node_t *n = &ga_nodes[ga_node];
    const uint16_t text_len = (uint16_t)strlen(n->text ? n->text : "");
    if (ga_typed < text_len) {
        const uint32_t elapsed = (uint32_t)ga_ticks + frames;
        ga_typed += elapsed / ga_frames_per_char;
        ga_ticks = (uint16_t)(elapsed % ga_frames_per_char);
        if (ga_typed > text_len) ga_typed = text_len;
    }
    const uint8_t count = ga_has_choices();
    if (count && up) {
        do { ga_choice = (uint8_t)((ga_choice + 2) % 3); }
        while (!n->choices[ga_choice].label || !n->choices[ga_choice].label[0]);
    }
    if (count && down) {
        do { ga_choice = (uint8_t)((ga_choice + 1) % 3); }
        while (!n->choices[ga_choice].label || !n->choices[ga_choice].label[0]);
    }
    if (press) {
        if (ga_typed < text_len) { ga_typed = text_len; return 1; }
        if (!count) { ga_state = 0; return 0; }
        const game_adventure_choice_t *c = &n->choices[ga_choice];
        if (!ga_allowed(c)) return 1;
        if (c->take >= 0 && !game_adventure_remove((uint16_t)c->take, 1)) return 1;
        if (c->give >= 0) game_adventure_add((uint16_t)c->give, 1);
        if (c->action >= 0 && ga_action) ga_action((uint16_t)c->action, ga_user);
        ga_reply = c->reply && c->reply[0] ? c->reply : c->label;
        ga_reply_typed = 0;
        if (ga_reply && ga_reply[0]) {
            ga_after_reply = c->next;
            ga_reply_ticks = 0;
            ga_state = 3;
        } else ga_next_node(c->next);
    }
    return 1;
}

/* Draw the nine atlas cells as a stretched tiled frame. The LCD canvas is
   assumed to be 480x320; the frame is drawn last, after all world sprites. */
static void ga_frame(int16_t x, int16_t y, uint16_t width, uint16_t height)
{
    gfx_setcolour(2); gfx_rectf(x, y, width, height);
    if (!ga_skin_pixels || ga_skin_w < ga_tile * 3 || ga_skin_h < ga_tile * 3) return;
    const uint16_t columns = ga_skin_w / ga_tile;
    const uint16_t rows = ga_skin_h / ga_tile;
    const uint32_t cells = (uint32_t)columns * rows;
    for (uint16_t iy = 0; iy < height; iy += ga_tile) {
        for (uint16_t ix = 0; ix < width; ix += ga_tile) {
            const uint8_t pos = (uint8_t)((iy == 0 ? 0 : iy + ga_tile >= height ? 2 : 1) * 3 +
                                          (ix == 0 ? 0 : ix + ga_tile >= width ? 2 : 1));
            const uint16_t index = ga_skin_indices[pos];
            if (index >= cells) continue;
            gfxbob_t tile;
            memset(&tile, 0, sizeof(tile));
            /* gfxbob_t.index is uint8_t. Rebase the pixel pointer to the
               selected cell so tile IDs beyond 255 render correctly too. */
            const uint32_t pixel_offset = ((uint32_t)(index / columns) * ga_tile * ga_skin_w)
                                        + (uint32_t)(index % columns) * ga_tile;
            tile.imgdat = ga_skin_pixels + pixel_offset;
            tile.atlas_stride = ga_skin_w;
            tile.atlas_height = ga_tile; tile.width = ga_tile; tile.height = ga_tile;
            tile.drawx = x + ix; tile.drawy = y + iy;
            tile.scale = 100; tile.index = 0;
            gfx_drawbob(&tile);
        }
    }
}
static void ga_text(int x, int y, const char *text)
{
    if (!text || !text[0]) return;
    if (ga_outline_enabled) {
        gfx_setcolour(ga_outline_colour);
        gfx_drawtext(x-1,y,text);
        gfx_drawtext(x+1,y,text);
        gfx_drawtext(x,y-1,text);
        gfx_drawtext(x,y+1,text);
    }
    gfx_setcolour(ga_text_colour);
    gfx_drawtext(x,y,text);
}
static void ga_wrapped(const char *text, uint16_t visible, int x, int y,
                       uint8_t max_columns, uint8_t max_lines)
{
    if (!text) return;
    char line[GA_COLS + 1]; uint16_t pos = 0; uint8_t lines = 0;
    while (text[pos] && pos < visible && lines < max_lines) {
        uint8_t n = 0;
        while (text[pos] && pos < visible && text[pos] != '\n' &&
               n < max_columns && n < GA_COLS)
            line[n++] = text[pos++];
        if (n == max_columns && text[pos] && pos < visible &&
            text[pos] != ' ' && text[pos] != '\n') {
            uint8_t last_space = n;
            while (last_space && line[last_space-1] != ' ') --last_space;
            if (last_space > 0) {
                pos -= n - last_space + 1;
                n = last_space - 1;
            }
        }
        while (n && line[n-1] == ' ') --n;
        line[n] = 0;
        if (text[pos] == '\n' && pos < visible) ++pos;
        while (text[pos] == ' ' && pos < visible) ++pos;
        ga_text(x, y + lines * (ga_outline_enabled ? 20 : 16), line);
        ++lines;
    }
}

void game_adventure_draw_npcs(int32_t camera_x, int32_t camera_y)
{
    /* NPCs use the SAME BOB used by the animation system. World locations
       come from regenerated adventure data, not a hand-edited main.c. */
    for (uint16_t i = 0; i < ga_npc_count && i < ga_animation_count; ++i) {
        gfxbob_t *sprite = ga_animations[i].sprite;
        if (!sprite || !sprite->imgdat) continue;
        const int32_t x = ga_npcs[i].x - camera_x;
        const int32_t y = ga_npcs[i].y - camera_y;
        if (x <= -((int32_t)sprite->width) || y <= -((int32_t)sprite->height)
            || x >= 480 || y >= 320) continue;
        sprite->drawx = (int16_t)x;
        sprite->drawy = (int16_t)y;
        gfx_drawbob(sprite);
    }
}

void game_adventure_draw(int32_t camera_x, int32_t camera_y,
                          int32_t player_x, int32_t player_y)
{
    if (!ga_state) return;
    if (ga_state == 2) {
        ga_frame(40, 34, 400, 172);
        ga_text(56, 48, "INVENTORY");
        for (uint8_t i = 0; i < GA_LINES; ++i) {
            uint16_t id = ga_inventory_offset + i;
            if (id >= ga_item_count) break;
            char line[60];
            /* bounded display: no heap allocation and no variable precision libc */
            const char *name = ga_items[id].name ? ga_items[id].name : "Item";
            uint8_t n = 0; while (name[n] && n < 34) { line[n] = name[n]; ++n; }
            line[n++] = ' '; line[n++] = 'x';
            uint16_t qty = ga_counts[id]; char tmp[6]; uint8_t digits = 0;
            do { tmp[digits++] = (char)('0' + qty % 10); qty /= 10; } while (qty && digits < 6);
            while (digits) line[n++] = tmp[--digits];
            line[n] = 0;
            if (ga_skin_pixels && ga_items[id].icon < (ga_skin_w/ga_tile)*(ga_skin_h/ga_tile)) {
                gfxbob_t icon; memset(&icon,0,sizeof(icon));
                icon.imgdat=ga_skin_pixels; icon.atlas_stride=ga_skin_w;
                icon.atlas_height=ga_skin_h; icon.width=ga_tile;
                icon.height=ga_tile; icon.scale=100; icon.index=ga_items[id].icon;
                icon.drawx=56; icon.drawy=68+i*22;
                gfx_drawbob(&icon);
            }
            ga_text(76, 68 + i * 22, line);
        }
        return;
    }
    if (ga_state == 3) {
        /* Player's selected reply types out above their own head. */
        const int screen_x = player_x - camera_x, screen_y = player_y - camera_y;
        const int bubble_x = screen_x > 360 ? 275 : screen_x < 20 ? 10 : screen_x - 8;
        const int bubble_y = screen_y < 62 ? screen_y + 26 : screen_y - (ga_outline_enabled ? 58 : 52);
        ga_frame(bubble_x, bubble_y, 185, ga_outline_enabled ? 54 : 48);
        ga_wrapped(ga_reply, ga_reply_typed, bubble_x + 8, bubble_y + 9, 20, 2);
        return;
    }
    if (ga_node >= ga_node_count) return;
    const game_adventure_node_t *node = &ga_nodes[ga_node];
    /* Three wrapped dialogue lines, a breathing-space row, then choices.
       20px text rows when outlined avoids adjacent 1px borders touching. */
    ga_frame(20, 148, 440, 162);
    ga_text(32, 158, node->speaker ? node->speaker : "");
    ga_wrapped(node->text, ga_typed, 32, 180, 50, 3); /* 50 x 8px fits 416px text area. */
    for (uint8_t i = 0; i < 3; ++i) {
        const game_adventure_choice_t *c = &node->choices[i];
        if (!c->label || !c->label[0]) continue;
        const int y = 249 + i * 20; /* spacer after NPC text and between answers */
        ga_text(32, y, i == ga_choice ? ">" : " ");
        ga_text(44, y, c->label);
        if (!ga_allowed(c)) ga_text(422, y, "X");
    }
}
