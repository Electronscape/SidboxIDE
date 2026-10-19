# Stage 3.93 — Game Object Properties workstation

## Install

Replace `gamedesigner.cpp` in the root of your Qt6 GamerGirl IDE source, then rebuild in Qt Creator. There is no change to runtime helpers, `.sbgm`, SDK APIs, or exported C. **No F5 Update Project is required** solely for this editor layout change.

## Changes

- Turns the old two-scroll-column Game Object Properties modal into a three-column themed workspace inspired by the Player Animation Toolkit: object types on the left; collapsible settings cards in the scrollable centre; pixel-art sprite and collision previews on the right.
- All accent highlighting uses the active `m_theme.accent` (rather than hardcoded red). Existing square-corner styling is retained.
- Type list uses the ten object types actually supported by the existing engine (including decorations, collectables, movers, conveyors, springs, triggers, doors, hazard zones, breakables and murder hazards). Loop tracks remain in their existing tilemap editor and are **not** a sprite-object type.
- Irrelevant type-specific behaviour and audio cards are **hidden**; for collectable keys the linked-target card appears. Independent animation controls appear only when enabled.
- Relevant signed momentum, damage, bounce, collision, timing and hit-count fields have paired sliders plus accurate spin boxes. Both directions stay synchronised.
- The preview uses the existing cached source image / PPB decode and foreground colour table, honours atlas cell geometry and frame sequencing (Loop, Ping-pong or Once), and shows a separate approximate collision box (hitbox begins at the sprite origin).
- The existing `Resource` model, validation, save assignments, scene refresh, audio IDs and generated source code were **not changed**.
- There is intentionally no Reset or Apply button: those would need distinct persistence semantics. OK and Cancel retain the safe, tested original behaviour.

## Testing and limits

- Run `python development/tests/test_stage393_game_object_properties.py` for source-level coverage.
- Previously shipped regressions for Stage 3.83, 3.85, 3.85a, 3.90, 3.91, 3.92, 3.92a and 3.92b pass.
- Qt6 headers/tools are not present in the assistant's runtime, so compiling and interacting with the live Qt dialog **needs testing on Fedora**. Please test opening a saved collectable, then changing type to hazard, editing a slider/spin, saving, re-opening, and cancelling another edit.
- A preview is a design-time presentation of an atlas cell, not a running game simulation. The collision box visualisation uses the current placed sprite's X/Y origin and editable hitbox width/height.
