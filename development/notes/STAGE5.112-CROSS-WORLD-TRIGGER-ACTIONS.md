# Stage 5.112.251026 — Cross-world Trigger linked actions

## Purpose
Trigger linked actions can target Game Objects in other saved `.sbgm` worlds.

**Example:** World1's knicker-exchange Trigger selects `Forest: Big Steve` and chooses **Disable**. Forest's Steve can display a dressed INACTIVE-state frame or be hidden. If desired, enable a separately placed clothed version as another action.

## Editing
1. Save each `.sbgm` world first, including Forest and its Game Objects.
2. Open the Trigger in World1 > **Ordered linked actions** > **+ Add Linked Action**.
3. Local objects appear by name. Other worlds appear as **`Forest: Big Steve [type]`**.
4. Select **Enable**, **Disable**, or **Toggle**. Multiple actions execute in their listed order.
5. Save worlds and choose **Update Game Project**. This stage changes the shared world manager and every world's generated helper. Rebuild the game afterwards.
6. **No edits to user-owned `main.c`.**

## Runtime behaviour
- Generator resolves cross-world **stable object IDs** to the target world's numbered object slot at build time.
- Actions on the active world run immediately. Actions on unloaded worlds enqueue only small RAM state changes. Target worlds are NOT loaded on demand.
- On entering the destination world, saved object state is restored first, then queued overrides are applied. First-time visits use configured initial active states as their Toggle baseline.
- Repeated toggles before visiting the destination resolve correctly. Multiple actions preserve order.
- Changes persist over world visits **within the current game session**. `gameworlds_shutdown()` clears the queued states for a fresh session. This does NOT add TFCard save games.
- The Logic Flow Chart can show cross-world edges and the expanded Trigger displays `World: Object` names.
- The Game Designer does not re-author other worlds or modify their PPBs. Missing/deleted cross-world IDs produce a generation error instead of targeting the wrong object.
- The feature is intentionally limited to **Trigger** linked-object actions. Key/enemy/NPC links still use their existing behaviour (NPC spotlight actions are unaffected).

## Hardware acceptance checklist
- First visit to Forest after changing Steve in World1
- Previously visited Forest, then changed Steve in World1, then returned
- Multiple actions targeting the same Forest object, including Toggle twice
- Forest object with an INACTIVE state frame and without one
- Local actions, Player Spotlight actions, and a cross-world action in one Trigger
- 50 FPS and no regressions during transitions

## Testing caveat
Native GCC tests exercise the queued-state functions and world transition behaviour. The desktop Qt6 editor is not available in this build environment; verify compile and real SIDBOX behaviour before declaring acceptance.
