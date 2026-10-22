# Stage 5.8 — Live Tile Stamp Banks across open world tabs

**Baseline:** Stage 5.7 *with the `this` lambda capture compiler fix*.
**Scope:** IDE only. `gametilemap.cpp`, `.map` runtime formats, firmware, and game helper C files are unchanged.

## Changes

- Every open `SidboxGameDesigner` world tab within the same project receives the latest atlas-stamp banks immediately after **Save** or **Apply to Design** succeeds. Different projects remain isolated.
- The Tilemap Editor also refreshes the `.proj` stamp bank at the moment it opens. No need to close/reopen the world tab, and edits from a second running IDE can be picked up on the next editor open.
- A world saves only the atlas stamp banks it actually edited. Older cached banks from other worlds cannot silently overwrite newer `.proj` definitions.
- Stage 5.7's one-time inline stamp migration is preserved for atlases not yet committed to `.proj`.
- **Save** writes `.sbgm` and `.proj` without prompting for C export; it leaves the editor open.
- **Apply to Design** also saves `.sbgm` and `.proj` automatically. It only offers to create missing runtime files if they are not already present. The shared stamp banks themselves do not need runtime regeneration.
- If a **different IDE process** edits the exact same atlas while an editor has unsaved edits, a real conflict still produces a warning. It does not demand closure of world tabs.

## Test with two open world tabs

1. Compile the IDE, open `forest` and `world1` tabs together. Set both to the same PPB Tile Atlas.
2. In forest's Tilemap Editor, add a stamp and press **Save** (do not press Update Game Project, do not close the forest tab).
3. Open world1's Tilemap Editor. The stamp appears immediately.
4. Rename the stamp in world1 using Enter, then press **Apply to Design**. Reopen forest's Tilemap Editor without closing its world tab. The new name appears.
5. Remove the stamp in forest (confirm Yes), press Save, and verify it disappears in world1. Previously painted tiles must stay untouched.
6. Give world1 a different atlas. Create a stamp there, save, and verify forest's original atlas bank remains independent.
7. Save world1 after forest has made further stamp changes. The original atlas bank must not revert to stale contents.
8. Optionally rebuild and run the game. Stamp banks remain IDE-only; physics/map cells have not changed.

## Changed source files

- `gamedesigner.cpp`: pull bank on tilemap entry; save/apply commit without manual Update.
- `gamedesigner.h`: declare per-tab bank synchronisation method.
- `gamedesigner_project.cpp`: merge changed atlas banks, refresh other open world tabs after save.
- `development/tests/test_stage58_live_tile_stamp_banks.py`: source-level checks.

## Verification

PASS: Stages 5.6/5.7/5.8 source checks, Stage 5.2 world manager and world feature tests, Stage 5.4f player/world integration and Stage 5.4i adventure/world test.

Not verified: Full Qt6 GUI compilation / interactive behaviour (Qt6 development libraries not installed in this environment). The customer's previous working Stage 5.7 GUI remains the correct build baseline.
