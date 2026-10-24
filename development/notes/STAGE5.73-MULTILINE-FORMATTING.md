# CoderGirl IDE Stage 5.73.241026 - Multiline formatting

Builds on the user's accepted Stage 5.72 source-editor features.

## What changed

- **Format Sourcecode** now reindents continuation lines inside `(...)` and `[...]` to one additional literal tab beyond the opening expression's line. Existing incorrect or missing leading indentation is corrected rather than preserved.
- Calls nested on *the same opening line* do not each add a further tab; a nested call started on its own continuation line indents further.
- A standalone closing `)` or `]` aligns with its opening line. Closing delimiters at the *end of an argument line* remain at the argument indentation.
- For a multiline control condition ending in `) {`, the trailing `{` goes on a new line, aligned with its `if` / `for` / `while` / `switch` / `catch`. Single-line conditions retain their existing brace placement, and already-separated braces stay put.
- Commented trailing braces, preprocessor/macro text, multiline raw strings and continued string literals are not structurally rewritten.
- Standard editor context menu, bracket matching, four-column tab stops, Ctrl+Z for a full formatting pass, user-owned source files and previous generator behaviour are otherwise unchanged.

## Example

Before (deliberately unindented arguments):

```c
if (gameplayer_defaults.custom_hitbox) {
    if (!game_tile_player_set_hitbox(&player_physics,
(uint16_t)gameplayer_defaults.hitbox_x,
(uint16_t)gameplayer_defaults.hitbox_y,
gameplayer_defaults.hitbox_w, gameplayer_defaults.hitbox_h)) {
        result = 7; goto cleanup;
    }
}
```

After (all indentation shown here as 4 visual spaces, but is real tabs):

```c
if (gameplayer_defaults.custom_hitbox) {
    if (!game_tile_player_set_hitbox(&player_physics,
        (uint16_t)gameplayer_defaults.hitbox_x,
        (uint16_t)gameplayer_defaults.hitbox_y,
        gameplayer_defaults.hitbox_w, gameplayer_defaults.hitbox_h))
    {
        result = 7; goto cleanup;
    }
}
```

## Testing and constraints

- The formatting rules were independently exercised against deliberately damaged indentation, nested calls, bracket expressions, macro continuations, quoted strings, raw C++ strings, and the supplied `main.c` and `maingame.c.txt`. Repeated formatting was stable in those checks.
- **The Qt6 IDE has not been compiled or run here** because Qt6 development libraries are not installed in this environment. Please rebuild on Fedora and verify the output in the IDE.
- Formatting makes in-memory editor changes only until saved. One Undo (Ctrl+Z) restores the entire formatting pass. This is a lightweight indentation formatter, not clang-format.
- Does not modify `main.c`, game resources, code generators or `mainwindow.cpp`. The 2048 KB syntax-highlight limit is preserved.

## Modified files (relative to Stage 5.72)

- `codeeditor.cpp`
- `splashscreenwidget.cpp` (splash build updated to `5.73.241026`)

`codeeditor.h` is intentionally unchanged. For source-only upgrades from Stage 5.72, overwrite only these two files and rebuild the IDE.
