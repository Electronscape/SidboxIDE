# SIDBOX / CoderGirl IDE Stage 5.42 (23 October 2026)

## Sprite Stamp (Game Object Properties)
- Sprite Stamp save/configuration no longer creates `gamesprites/generated/stamp_*.ppb`.
- The .sbgm stores the original source PPB reference and the existing 8x8 cell lookup (tile ID, per-cell horizontal/vertical flips, empty cells).
- Generated `gameworlditems.c` draws managed object stamps straight from the existing loaded PPB with C lookup tables, including whole-object mirroring.
- The generated main-game starter supports stamped foreground decorations with lookup tables as well. Stamps do not need an additional PPB on TFCard.
- Stage 5.36 projects that saved a generated stamp PPB are automatically redirected to the original source PPB when opened. Old on-disk generated stamp PPBs are not auto-deleted.
- Sprite Stamp previews are composed in the editor **in memory only** and match saved cell dimensions.

## Inventory drops
- The Asset Generator now includes every inventory item's chosen icon atlas in `gameassets`, even when it is not the active tilemap atlas or dialogue skin.
- Adventure item rendering continues to reference the item's configured atlas rather than substituting the dialogue atlas when a custom atlas is missing. A missing chosen PPB produces the visible fallback instead.

## Apply and hardware testing
1. Back up the IDE and game project as usual.
2. Use the updated IDE sources and rebuild the Qt IDE (the archive is *source*, not an AppImage).
3. Open and save the game design to migrate any Stage 5.36 generated-stamp paths.
4. Use **Update Game Project** to refresh generated world code and Adventure runtime helpers. Preserve user-owned `main.c` (the IDE deliberately will not overwrite it); when using stamped decorations, copy the updated generated rendering into user-owned code if necessary.
5. No stamp-generated PPB needs to be copied to TFCard. Keep the **original** referenced PPB sheet available as before.
6. On SIDBOX hardware, test a multi-cell stamped world object, X/Y mirroring, a decoration stamp, and drop/re-pick an inventory item whose icon atlas differs from the dialogue/tilemap atlases.

## Validation
`python development/tests/test_stage542_stamps_and_inventory.py`
C renderer tests (including tile IDs above 255, cell/global flips, and camera), existing inventory and cross-world tests: PASS.
A complete Qt IDE build and SIDBOX STM32 hardware run were **not** possible in this environment.
