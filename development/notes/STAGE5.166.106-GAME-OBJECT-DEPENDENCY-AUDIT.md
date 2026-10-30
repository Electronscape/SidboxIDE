# Stage 5.166.106 (29 October 2026) — Game Object dependency audit

## Modified source

- `gamedesigner.cpp`: `SidboxGameDesigner::editObjectProperties()` now runs a live audit over the unsaved, active object's configuration. A warning-icon review control appears when rules are violated; relevant controls get an amber highlight and a detailed tooltip. Review allows the author to inspect a particular issue, apply an explicitly chosen suggested fix where safe, or keep editing. Advisory settings can be kept and saved explicitly. Conflicts that violate the code generator's assumptions block saving until corrected.
- `gamedesigner.cpp`: Ordinary enemy loot picker **shows** non-eligible Collectables as unavailable, with a reason, rather than silently hiding them. Previously selected ineligible/missing IDs are displayed for review instead of silently removed from the draft. Key/persistent/reward-exclusive restrictions and the maximum of eight candidates are unchanged.
- `gamedesigner.cpp`: Reward, world destination, spline and legacy linked-object dropdowns preserve missing saved references with warning-labelled entries when loading/navigating, instead of quietly selecting None.
- `splashscreenwidget.cpp`: build tag 5.166.106.291026.
- `development/tests/test_stage5166_106_object_dependency_audit.py`: static source-contract checks.

## Coverage

Checks key/persistent/custom loot prerequisites, existing enemy pools that depend on a Collectable, duplicated/exclusive quest rewards, tilemap and spline requirements, missing references, inactive ordinary loot ranges, enemy roam, break modes, required-item drop triggers, configured music with no tune, empty world destinations, moving platform paths, zero-speed conveyors, zero-delta hazards, particle layering, spring inertia, and animation/stamp interactions. Existing runtime/export restrictions remain authoritative.

## Checks completed

- Source-contract tests for Stages 5.166.103, 104, 105 and 106 passed.
- C++ source brace balance checked.
- **Qt development libraries are not installed in the execution environment**, so no Qt compilation, GUI session or real-hardware verification was performed. Build and exercise the dialog in the user's Fedora Qt6 IDE before hardware sign-off.

## Suggested live tests

1. Check a custom Collectable's repeatable-loot option while Key or Persistent is selected. Check warning explanations and explicit fix; change it back to a non-key, non-persistent type, then verify its visibility in the enemy loot pool after saving.
2. Put that Collectable in an enemy loot pool. Attempt to make it persistent, a key, or change it to a different Game Object type. Saving must warn/block until the dependency is resolved.
3. Assign a unique quest reward to one enemy and then to a second. Saving the second assignment must fail with an actionable warning; ordinary loot must continue to work independently.
4. Remove a referenced Collectable or movement spline in a copy of the project. Inspect missing entries and ensure edits do not silently discard them.
5. Try trigger drop without required inventory item, Play Music without a tune, Goto World without a target, and enemy loot without tilemap. Check that warnings update live and only deliberate choices change settings.
6. Use Previous/Next while changing settings, then choose Save, No or Cancel. Audit indicators must always describe the currently selected draft.
