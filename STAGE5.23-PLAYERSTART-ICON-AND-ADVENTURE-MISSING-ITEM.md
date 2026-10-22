# Stage 5.23 — Player Start Icon + Adventure Missing-Item Reply

Based on Stage 5.22.

## Part 1: Player Starts icon

The Game Designer resource tree now has a dedicated 16x16 icon for Player Starts:

- `icons/gr_icon_playerstart.png`
- Root **Player Starts** uses it
- Child entries such as **Default start** and named door starts use it

Artists can replace `gr_icon_playerstart.png` later.

## Part 2: Adventure dialogue missing-item branch

Dialogue answers that use **Requires this item** can now still be selected even when
that item is missing.

Each answer now has:

- **If missing required item** → choose another dialogue node, or leave it as
  **Keep current behaviour (do nothing)**.

Runtime behaviour:

- If the player HAS the item: existing flow is unchanged
- If the player does NOT have the item:
  - the answer can still be chosen
  - no give/take/event/once/completed side-effects happen
  - the dialogue moves to the selected fallback node

This makes it possible to avoid hinting to the player that they chose the
"correct" hidden item answer.

## Files changed

- `CMakeLists.txt`
- `gamedesigner.cpp`
- `gameadventureeditor.cpp`
- `gameadventuregen.cpp`
- `splashscreenwidget.cpp`
- `idelibs/codehelpers/game/adventureruntime.ruleh`
- `idelibs/codehelpers/game/adventureruntime.rulec`
- `icons/gr_icon_playerstart.png`

## Suggested quick test

1. Open Adventure Editor.
2. Create an answer with **Requires this item = Key**.
3. Set **If missing required item** to a dialogue node like `"You don't have it yet."`.
4. Test once without the item and once with the item.
5. Confirm the Player Starts tree shows the new icon.
