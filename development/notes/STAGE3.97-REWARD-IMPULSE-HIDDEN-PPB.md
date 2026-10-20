# Stage 3.97 — Reward launch impulse, hidden collectables and single-open PPB viewer

Based on the real-hardware-tested Stage 3.96 source. No other game physics paths are changed.

## Breakable rewards

Game Object Properties → Breakable → **Drop collectable on break**: choose an existing Collectable resource. The new optional checkbox **Launch reward when block breaks** enables two signed fields. **Reward X speed**: negative = left, positive = right (default 0); **Reward Y speed**: negative = up, positive = down (default -8). Units are pixels per 50 Hz game/physics frame; allowed range -20..+20. Both fields support accurate number spinners and quick sliders. With the checkbox OFF, the previous Stage 3.96 simple falling reward remains unchanged.

On the final break hit, generated `gameworlditems.c` activates the assigned hidden collectable at the breakable's position and initialises X/Y velocity. Every physics tick adds vertical gravity (+0.65 px/frame², capped at +9 px/frame) and damps horizontal velocity to 97% (to stop prizes drifting forever). Pixel-by-pixel collision sweeps on both axes prevent travel through the level's static tile walls, ceiling and floor; touching a ceiling cancels upward velocity. On landing the reward stops, and only THEN `can_collect` becomes 1. The reward remains a normal Collectable for score, health, keys, audio and respawn behaviour. This is **not** a physical-body engine for moving objects.

**Requirements carried forward:** A tilemap must be enabled; every breakable reward needs its own distinct collectable resource; the reward must not follow a spline. Reward links use stable resource IDs. Ordinary breakables without prizes are unchanged.

## Hidden collectables

Collectable Properties → **Hidden until activated / spawned** is the inverse of the existing `objectInitiallyActive` property. It does not create a second persistent state. Checking this hides a normal collectable at level start; it is not drawn, cannot be picked up and can be activated later by an existing link/trigger or a breakable reward. Rewards linked to breakables were **already hidden automatically** by Stage 3.96, whether this box is checked or not; the UI now makes that behavior discoverable. No project format change is required for the hidden option, and old `.sbgm` values are preserved. Unlinked hidden collectables stay hidden until activated by game logic; merely checking Hidden does not create a trigger.

## PPB viewer opens only once

The Project Explorer's `itemDoubleClicked` and `itemActivated` signals could both fire on the same mouse double-click and open two consecutive modal PPB dialogs. The `itemActivated` connection is removed, leaving `itemDoubleClicked` as the one mouse-open route. Separate scoped Return/Enter actions preserve keyboard opening of the current tree item. Toolbar `View PPB...` remains unchanged.

## Installation

Copy modified production files from the changed-files archive into the IDE source root, retaining directory structure, then rebuild in Qt Creator. To apply new reward launch settings: edit the breakable, save your `.sbgm`, then **F5 → Update and Compile** to regenerate `gameworlditems.c`. Existing protected `main.c` need not change: the current `gameworlditems_update/before/after/check` calls are sufficient.

## Verification

- Compile & run exact exported C gravity/impulse loop: gravity-only default, upwards/left/right/downwards impulse, ceiling/wall/floor collision, post-landing pickup unlock — PASS.
- Native C Stage 3.96 head-butt, contact rearming and reward pickup gating — PASS.
- Stage 3.90–3.96 focused source/integration regression tests — PASS.
- Stage 3.97 save/load, controls, export, project explorer single-open regression check — PASS.
- **Qt6 compilation and SIDBOX hardware tests were not available here**. Please test the Qt form, project tree behaviour and real physics on your Fedora/SIDBOX setup.

## Known limitations

Prizes collide with the **static tilemap**, not moving platforms or other dynamic game objects. If starting position overlaps solid tile collision, the movement sweep may stop immediately. Initial upward velocity works best when the breakable sits in open space just below a clear ceiling.
