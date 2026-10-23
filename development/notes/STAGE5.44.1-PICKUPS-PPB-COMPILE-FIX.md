# Stage 5.44.1 (23 October 2026): PPB sprite name vs runtime pickup symbol

## Root cause

A sprite (including an atlas resource) named `pickups` or `pickups[0]`
uses the C graphics symbol `pickups`. The old worlditems rule also declared
`static game_collectable_t pickups[...]`. With the per-world symbol map,
`pickups[0].flags` resolved to the physics struct, which has no `flags` field.
The platform runtime had the equivalent latent problem for `platforms`.

## Fix

- `idelibs/codehelpers/game/gameworlditems.rulec`: managed collectables
  now live in `cg_gwi_pickups`, managed world objects in `cg_gwi_platforms`.
  All save, restore, draw, physics, reward, link, sound and object initialisation
  code references those new array names.
- `gamedesigner_export.cpp`: emitted `ARRAY_NAME` and stable-ID target
  expressions refer to the same namespaced arrays.
- `splashscreenwidget.cpp`: `Build: 5.44.1.231026`.
- Native C test actually compiles initializer statements rendered from the
  shipping rule template with graphics named `pickups[0]` and `platforms[0]`.

This changes only generated C identifiers and does not modify resource IDs,
PPBs, saved designs, inventory behaviour or palette indices.

## Apply and verify

Apply drop-in to Stage 5.44 IDE, rebuild IDE, and use Update Game Project
for **all worlds** so old C is replaced (e.g. worlds/forest/gamehelpers/gameworlditems.c).
Do not edit generated C manually.

No complete Qt6 GUI build or STM32 hardware validation in this environment.
