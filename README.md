# Build numbering convention (from 30 October 2026)

Splash: `Build: 5.SUBVERSION.REVISION.DDMMYY`, exactly four parts.
Current release: **5.128.1.301026**.

**5.128.1** hotfix: Quest ON COMPLETED -> Show Dialogue connections now
select/commit an actual Adventure dialogue rather than leaving an unlinked
purple placeholder; also fixes quest linked-card/orphan detection.
See `README-STAGE5.128.1-QUEST-COMPLETION-DIALOGUE-FIX.txt`.

---

# Build numbering convention (from 30 October 2026)

Splash: `Build: 5.SUBVERSION.REVISION.DDMMYY`, **exactly four dot-separated values**.
Current splash: `Build: 5.128.0.301026` (this source is otherwise identical to historical Stage 5.166.128).
New feature: increment SUBVERSION and reset REVISION to zero; hotfix: increment REVISION only.
DDMMYY is the release date. Historical Stage 5.166.x.y notes below are retained unchanged for traceability.
This update changes the splash label and documentation only, not the generated game runtime.

---

Stage 5.166.128: Quest Lines ON COMPLETED now supports direct editable Adventure Show Dialogue cards, dispatched once through the Stage119 FIFO. Works with existing completion actions, no dummy logic gate or main.c changes. See README-STAGE5.166.128-QUEST-COMPLETION-DIALOGUE.txt.
Stage 5.166.127.2: Removed invalid direct melee timer resets from generated main; player_anim_step() still owns all timing. See README-STAGE5.166.127.2-MAIN-ANIM-RESET-FIX.txt.
Stage 5.166.127.1: Player melee animation now uses the existing player_anim_step() call; see README-STAGE5.166.127.1-PLAYER-ANIM-API-CORRECTION.txt.

# Stage 5.166.127: Player Toolkit Melee Animation (30 Oct 2026)

Source candidate based on Stage 5.166.126. Toolkit custom state **Melee** (case-insensitive) can now play automatically for every accepted FIRE1 swing when current Player Physics Profile has combat enabled. Play once for the clip's frame timings, then return to Idle/Walk/Jump/Fall; Hurt interrupts. Existing attack damage/hit logic unchanged. Source-only change to animation export and generated sample main integration; hand-owned main.c must opt in via a one-line call replacement. No .sbpi or save schema changes.

See `README-STAGE5.166.127-PLAYER-MELEE-ANIMATION.txt` for exact user-owned main.c replacement. Native C and source regression tests pass; full Qt6 build and hardware pending.

---

# Stage 5.166.126: Visual Nodes STATE vs EVENT guidance (30 Oct 2026)

Editor-only clarity update: STATE/ALIVE and EVENT/ON HIT/ON DEFEAT labels,
source-coloured logic inputs, persistent-state vs momentary-pulse tooltips,
contextual AND/NOT guidance and a compact canvas legend. All existing graph
contracts and runtime behavior are preserved. Details: see
`README-STAGE5.166.126-STATE-EVENT-GUIDANCE.txt`.

---

# Stage 5.166.125: Optional Enemy Hit Feedback (30 Oct 2026)

Added independent Player Hit Effects / Enemy Hit Effects groups under
Damage / Knockback / Hurt Effects. Enemy damage can now trigger an optional
solid-CLUT flash and/or a temporary PPB hit-frame animation, on melee, stomps
and underside hits. Existing multi-hit counts, death animations, drops and
quest events are preserved. Effects are OFF by default for old projects.

Full details and hardware test instructions:
`README-STAGE5.166.125-ENEMY-HIT-EFFECTS.txt`. Native runtime and focused
source tests pass; a full Qt6 compile is unavailable here (Qt6 SDK missing).

---

# Stage 5.166.123: Flow Debugger virtual action references (30 Oct 2026)

Stage 5.166.122 plus a read-only Flow Debugger resolver correction.

- Previously a real `stopLift -> @player_time:0` (daylight) action was shown as a missing Game Object even though world C export supported it. The same bug affected other built-in PLAYER and quest-event targets.
- Trigger primary and extra links, and enemy primary and ON DEFEAT extra links, now draw valid PLAYER/Time, PLAYER/Weather, PLAYER/World, PLAYER/Spotlight and QUEST EVENT targets as named runtime-action cards instead of red "Broken reference" cards.
- Trigger detail now labels built-in actions by their actual name rather than "Missing object". A quest signal action also links to the corresponding project-wide Quest Event node.
- Unsupported modes, unknown world destinations, unknown quest signals and invalid enable-only actions remain visible diagnostics, not silently accepted.
- No changes to .sbgm, .vsgm, world C generation, runtime quest logic, save data, or the user's game project.

Validation: Stage 123 focused source/fixture test, Stage 121 native quest/save test, and Stage 122 native Journal renderer test passed. Some older Stage 67/69 tests no longer match the updated queue and weather runtime; they were not counted as passes. Full Qt6 IDE build is unavailable here (Qt6 dev SDK not installed). Desktop visual acceptance remains for the user.

# Stage 5.166.122: Quest Journal Objective Details (30 Oct 2026)

The runtime Journal now opens each quest on its description. RIGHT opens its
complete objective checklist, LEFT returns to the description, and UP/DOWN
changes quests while resetting to the description. RIGHT also pages long
objective lists; ordered and unordered quests are both supported. Objective
progress and save formats are unchanged. See
`README-STAGE5.166.122-QUEST-OBJECTIVE-JOURNAL.txt`.

---

# Stage 5.166.116.4: Exporter compatibility hotfix (30 Oct 2026)

See `README-STAGE5.166.116.4-EXPORTER-MATCH.txt`.  Use a clean source/build directory to prevent mixed Stage 114 and Stage 116 code.

---

# Stage 5.166.116.1: Qt lookupGraph compile hotfix (30 Oct 2026)

Fixed the missing index argument in `VisualNodesDialog::addConnection()` for ON HIT/ON DESTROY event-to-existing-logic connections. Full Stage 116 functionality retained; no runtime or save changes. See `STAGE-5.166.116.1-RELEASE-NOTES.txt`.

---

# Stage 5.166.113: Numbered Logic Input Sockets (29 Oct 2026)

Independent Boolean/NOT nodes display one input; OR two; AND begins with two then adds a spare input square as new wires are connected, up to sixteen. Wires terminate on their own indexed squares and the card resizes dynamically. No runtime, export, save payload or operator semantics changes. See `README-STAGE5.166.113-LOGIC-INPUT-SOCKETS.txt`.

---

# Stage 5.166.111.1: ON ARRIVAL Logic Picker Visibility (29 Oct 2026)

On the golden ON ARRIVAL port, the Logic chooser now appears first and expanded, with a direct Toggle action hint. This is an IDE menu-only fix; the generator, saves, and existing Toggle logic are unchanged. If you see a chooser with only Game Objects/NPC Conversations/PLAYER, verify the splash build, as that matches Stage 5.166.110. See `README-STAGE5.166.111.1-ARRIVAL-PICKER.txt`.

---

# Stage 5.166.106.1: Dependency Audit Qt String-Literal Compile Hotfix (29 Oct 2026)

Fixed `gamedesigner.cpp`, inside `GameDesigner::editGameObject()`, where the
"Trigger has missing linked targets" warning text contained unescaped newlines
within C++ string literals. Both are now `\n` escape sequences. This corrects
the reported "missing terminating quote" and `QStringLiteral` macro errors.
No audit, game project, exporter or runtime logic changed. Splash build string
updated to `Build: 5.166.106.1.291026`.

Qt6 compilation is not available in this environment. Source regressions and
lexical checks passed. See `README-STAGE5.166.106.1.txt`.

---

# Stage 5.166.105: Repeatable Stompable Enemy Loot (29 Oct 2026)

Added an independent 0–8 ordinary loot drop pool per Stompable Enemy, separate from unique quest rewards. The IDE offers a multi-select list of up to eight eligible Collectables, minimum/maximum drop counts and an opt-in for custom repeatable inventory kinds. The generator retains original exclusive quest-item ownership validation; keys, persistent and unique reward Collectables cannot enter loot pools. The generated world controller includes a fixed 64-slot maximum pool of independent pickup copies, gravity, tile collision, standard pickup callback integration, and per-world/TFCard state persistence. No user `main.c` edits. Regenerate all worlds and rebuild to test. See `README-STAGE5.166.105.txt`.

---

# Stage 5.166.103: Game Object Type Sidebar Mapping Fix (29 Oct 2026)

The left-hand **OBJECT TYPE** selector in Game Object Properties previously
showed 14 labels for 15 model behaviours, shifting everything after the
ordinary Decoration. Replaced brittle parallel labels/icons with a keyed
presentation map for all 15 stable behaviour IDs. **Stompable enemy** now
selects `enemy`, and **Goto World** selects `goto_world`. Gameplay code and
resource serialization are unchanged. Inspect any game objects saved while
using the old incorrect labels; they cannot be auto-corrected safely.

# Stage 5.166.102.3: Snow Particle Size 32 px (29 Oct 2026)

The Snow particle size slider and spinbox now range from **2 to 32 px**. Saved project loading, generated world records and the runtime limit accept 32 px. Preview sprites, atlas BOBs and fallback circles already scale using the configured size. Default remains 5 px. No changes to world save format or user `main.c`. After rebuilding the IDE, use **Regenerate ALL Worlds** and rebuild the game. See `README-STAGE5.166.102.3.txt`.

---

# Stage 5.166.102.1: Weather Atlas Picker Qt6 Compile Hotfix (29 Oct 2026)

Fixes the `gamedesigner.cpp` snow atlas picker callback: capturing a stack-allocated `QDialog` by value attempts to invoke the deleted Qt copy constructor, and also produces `const QWidget*` to `QWidget*` conversion errors in QMessageBox and `chooseGameAtlasCell`. The callback now explicitly captures the existing dialog by reference, with explicit control and helper captures. **No generated runtime, weather logic or game project changes.** See `README-STAGE5.166.102.1.txt`.

---

# Stage 5.166.102: Weather Resource Tiles and Thunder Bursts (29 Oct 2026)

Snow uses the Game Resources atlas list and existing graphical tile picker. Snow/rain no longer wrap visibly near the screen bottom, and lightning storms can include occasional additional softer strikes without changing the primary average interval. See `README-STAGE5.166.102.txt`.

---

# Stage 5.166.84.1 — Qt compile hotfix (28 Oct 2026)

Fixes the Qt6 `QObject::findChildren` static assertion in GIVE socket redraw.
Searches for `QComboBox*` and retains `giveRouteBranch` matching.
No gameplay/runtime changes. See `README-STAGE5.166.84.1.txt`.

---

# Stage 5.166.84 — GIVE output dropdown alignment (28 Oct 2026)

Fixes the visibly staggered output circles on expanded NPC GIVE Exchange
cards by positioning each socket from the **final Qt dropdown geometry**
after proxy embedding. All five sockets are re-anchored before routing wires,
including after the first visible layout. Data and game runtime remain
unchanged. See `README-STAGE5.166.84.txt` for installation and testing.

---

# Stage 5.166.83 — GIVE socket pull-out and visual alignment (28 Oct 2026)

Turquoise GIVE anchors can now be dragged from a dialogue answer onto the
canvas to reposition their existing exchange card. No new exchange is created,
and the actual Adventure engine data is unchanged. Dialogue answer outputs
cluster near each answer, all circular outputs centre on card borders, collapsed
cards retain sockets in a tidy vertical row, and hollow ports have opaque canvas
backgrounds that hide overlapping wires and borders. See
`README-STAGE5.166.83.txt` for installation and tests.

---

# Stage 5.166.72 — NPC Conversations in Visual Nodes (28 Oct 2026)

The Visual Nodes graph now recognises authored `adventure.npcs` associations
as first-class editable NPC cards. Opening/after-helped conversation dropdowns
(with Dialogue Editor folder browser), talk radius and initially-visible controls
use the same `.sbgm` properties as the Adventure Editor. The node picker can
connect existing NPC opening/after-helped dialogues to Trigger actions and
independent TRUE/FALSE logic via ordinary Show Dialogue calls. Refresh from
World rereads the NPC state; an NPC card can be hidden persistently in `.vsgm`
without deleting its required opening dialogue. See
`development/notes/INSTALL-STAGE5.166.72.txt` for test steps and limitations.

---

# Stage 5.166.69.281026 — Weather PLAYER actions: ON/OFF/Toggle

PLAYER Weather targets now support Enable, Disable and Toggle, including both
branches wired to the same Snow/Rain/Storm card. Stage 5.166.67/68 saved
Enable/Enable weather pairs are migrated in the Visual Nodes editor and also
handled directly by the exporter for backward compatibility. The Game Object
Properties action selector is enabled for weather. Mode-specific Disable avoids
clearing another graph's unrelated weather. Existing Spotlight, startup sync,
Time of Day and world-transition paths remain intact. No change to main.c.

**Install and hardware test:** `development/notes/INSTALL-STAGE5.166.69.txt`.
Native C and targeted regression tests pass; the Qt IDE rebuild and physical
SIDBOX weather test are not verified here.

---

# Stage 5.166.68.281026 — Initial visual logic at world start and checkpoint reload

Independent graph outputs now resolve immediately on world activation, after
saved object states and cross-world actions have been restored and after scene
effects are configured. Initial synchronisation applies RESULT state bindings
and idempotent enable/disable actions (including PLAYER Spotlight, weather,
day/night). It deliberately excludes dialogue, Toggle and Goto World actions,
which are gameplay events, not save-load callbacks. Every ordinary Trigger
execution path is unchanged. No new save format or `main.c` integration.

**Install and hardware test:** `development/notes/INSTALL-STAGE5.166.68.txt`.
Source/native smoke tests pass; GUI compilation and physical SIDBOX testing
must be verified on the user's machine.

---

# Stage 5.166.67.281026 — PLAYER visual logic commands

Real PLAYER targets now live under the Visual Nodes PLAYER tree for Spotlight,
Weather & Effects, Time of Day, and World Transitions. Normal Trigger and
independent logic TRUE/FALSE action branches compile to the existing world
manager's spotlight and deferred world request APIs, plus new live weather/
daylight setters. Existing RESULT and independent AND/OR object bindings are
unchanged. The sibling-world discovery matches the Goto World editor.

**Install, regression and SIDBOX test checklist:**
`development/notes/INSTALL-STAGE5.166.67.txt`. Full Qt6 GUI build and real
SIDBOX hardware still require verification. Your hand-maintained `main.c`
is not modified; regenerate All Worlds for the generated runtime changes.

---

# Stage 5.166.58.281026 — Editable Boolean branches in Game Object Properties

The formerly read-only Boolean State / Visual Nodes summary is now editable.
Trigger-owned Boolean source, TRUE/FALSE dialogues and ordered Enable/Disable/
Toggle actions can be edited in **Switch, Trigger & Save Checkpoint**. A state
source object (e.g. Lifty) can edit incoming Trigger branches under **Triggers
Reading This Object**. Both modify the same authoritative Trigger fields in
`.sbgm`, preserving the existing Visual Nodes round-trip and runtime semantics.

See `development/notes/INSTALL-STAGE5.166.58.txt`. The Qt6 desktop build and
mouse interaction are unverified here; native/schema regressions were run.

---

# Stage 5.166.57.281026 — Boolean State Game Object visibility

The new Boolean State / Visual Nodes card in Game Object Properties reads real
Trigger-owned conditional branches in `.sbgm` from both the Trigger and
its referenced Game Object. This is GUI-only, read-only; it does **not** create
new On Enable/On Disable runtime callbacks. See
`development/notes/INSTALL-STAGE5.166.57.txt`.

## Stage 5.166.53.281026 — Visual Nodes: Read Toggle State TRUE/FALSE dialogue branches

SIDBOX CoderGirl IDE — Stage 5.166.53.281026
VISUAL NODES — READ TOGGLE STATE / TRUE-FALSE DIALOGUE BRANCH

INSTALL
Apply hotfix over Stage 5.166.52, then rebuild the Qt IDE.
Regenerate ALL worlds / Update Game Project, then rebuild the V1 game before
hardware testing. This stage includes generated-runtime changes.
Your hand-owned main.c does not need modification.
Existing .map files and save slot formats are unchanged.

HOW TO TEST
1. Open a world .vsgm and select an existing Trigger (FIRE2 or touch).
2. Click '+ Read Toggle State' (or right-click Trigger > Add Read Toggle State).
3. Right-click the new teal card > Choose Game Object state source.
   Pick a same-world Game Object, e.g. Lifty.
4. Connect your Trigger to Lifty with a Toggle action, as before.
5. Drag the condition's green TRUE or red FALSE port into empty canvas.
   Choose an existing dialogue using the same folder tree as the Dialogue
   Editor, or choose Create New Dialogue. Both produce purple branch cards.
6. Save Graph + World, regenerate ALL worlds, rebuild V1.
7. Activate the Trigger twice: the selected object's new active state is
   tested AFTER all normal Trigger actions, so TRUE and FALSE choose
   different single-message dialogues on alternating toggles.
8. Save and reopen .vsgm, then edit the Trigger in Game Object Properties;
   save that editor, reopen .vsgm. The TRUE/FALSE settings must persist.
9. Right-click a branch wire to remove that connection. Deleting a condition
   node unlinks its TRUE/FALSE dialogues, not the underlying Adventure nodes.

DATA MODEL / SCOPE
.sbgm remains authoritative. Only three optional fields per Trigger were
added: toggleStateTargetId, toggleTrueDialogueNode, toggleFalseDialogueNode.
.vsgm stores card positions/camera but no gameplay connection copies.
The condition reads the active bit of a local Game Object, NOT transient
trigger_fired. Remote/NPC targets are deliberately not offered.
TRUE and FALSE dialogue is displayed in single-message/no-actions mode for
this first pass, so it doesn't execute accidental quest/dialogue actions.
Unconditional Show Dialogue remains independently configurable.

VERIFICATION
Selected Visual Nodes regression checks and native GCC branch-behaviour
check passed. Full Qt6 IDE compilation and SIDBOX hardware behaviour have
NOT been verified in this environment. Test with the backed-up game first.

---

## Stage 5.166.52.281026 — Visual Nodes: persisted canvas panning

Visual Nodes now remembers the exact pan/scrollbar offsets along with zoom and
scene centre in the optional `.vsgm` camera section. Same-sized maximised
viewports restore exact pan; resized windows use the scene-centre fallback.
Camera is still saved on close, even when the node graph was not edited.
See `development/notes/INSTALL-STAGE5.166.52.txt`. IDE-only update.

---

## Stage 5.166.51.281026 — Visual Nodes: 8px snapping and Visible Nodes dialogue entries

Game Object and Show Dialogue cards now snap to 8px grid positions when moved. Purple Show Dialogue cards appear in the Visible Nodes sidebar, including their Trigger name and active dialogue number, and support double-click focus and existing deletion paths. Old saved positions remain unmodified on open. IDE-only; runtime and game file formats unchanged. See `development/notes/INSTALL-STAGE5.166.51.txt`.

# Latest: Stage 5.166.50.281026 — Smooth Visual Nodes dialogue wires

Purple Show Dialogue wires no longer use rectangular routes over the top of
cards when the dialogue sits left of its Trigger. Both left and right
placements now use cubic Bezier curves, with the connection entering the
nearest useful side of the dialogue card. See
`development/notes/INSTALL-STAGE5.166.50.txt`. IDE-only; no runtime changes.
Qt6 desktop visual testing is still required.

---

# Latest: Stage 5.166.49.281026 — Visual Nodes Delete and wire cleanup

See `development/notes/INSTALL-STAGE5.166.49.txt`. Selected cards can now be
removed with Delete, the right-hand button or a card context menu; real Trigger
actions and dialogue links are disconnected without deleting underlying Game
Objects/NPCs/Adventure dialogue nodes. Purple dialogue wires share the regular
right-click disconnect affordance, and use corrected routing. All changes to
real connections remain pending until Save Graph + World. Full Qt6 build and
mouse/keyboard interaction remain to be verified.

---

# Latest: Stage 5.166.48.281026 — Visual Nodes trees and orphan cleanup

See `development/notes/INSTALL-STAGE5.166.48.txt`. The on-demand node picker
now groups Game Objects by type and opens collapsed. Added right-click and
right-panel controls to remove unconnected/orphaned graph cards without
removing Game Objects or dialogues from `.sbgm`. No runtime changes.
Full Qt6 GUI build and mouse testing remain to be verified.

---

# Latest: Stage 5.166.47.271026 — Visual Nodes dialogue tree and layout

See `development/notes/INSTALL-STAGE5.166.47.txt`. Show Dialogue cards
now save live canvas positions. Trigger output selection and purple-card
browsing use the actual Adventure Dialogue Editor folder tree, with Create New
last. Qt6 mouse-release global position API updated. GUI-only; full Qt6
compilation and mouse testing remain to be verified.

---

# Latest: Stage 5.166.44.271026 — Visual Nodes Qt compilation hotfix

See `development/notes/INSTALL-STAGE5.166.44.txt`. Fixes QVariant::toInt(bool *)
being called with the integer `-1` in the inline Show Dialogue combo box.
No runtime changes. Full Qt6 GUI compilation still unavailable in this environment.

---

# Latest: Stage 5.166.40.271026 — Visual Nodes (.vsgm) Phase 1

See `development/notes/INSTALL-STAGE5.166.40.txt`. This is an opt-in, maximised
visual Trigger → Game Object link editor. It does not change the existing Logic
Flow or runtime. Full Qt6 compilation is unverified in this environment.

---

# Latest: CoderGirl Stage 5.166.36.271026 — Defeat FIRE1 / Title Input Latch

**Start here:** `development/notes/INSTALL-STAGE5.166.36.txt`.
The generated title runtime now ignores FIRE1/FIRE2 inherited from the death
screen until those buttons are released once. Previously FIRE1 could dismiss a
no-save death screen AND instantly activate the first Start Game item, making
Forest appear to load directly. Regenerate ALL Worlds / Game Project to update
`gamehelpers/gametitle.c`. No `main.c` changes. Native C test of the actual
title function and selected regressions passed; hardware/Qt GUI unverified.

---

# Latest: CoderGirl Stage 5.166.31.271026 — Qt Lambda Compile Hotfix

**Start here:** `development/notes/INSTALL-STAGE5.166.31.txt`.
Corrects a C++ compilation error introduced in Stage 5.166.30, in
`gamerpguieditors.h` at `editGameWorldMap()`: the `selectMode` lambda was
erroneously declared `auto *` instead of `auto`. The lambda remains functionally
identical; only its declaration is fixed. No game or world regeneration is
required. A repository-wide lambda-pointer source scan plus a standalone C++
compiler regression are included. Qt6 development packages are not available in
this environment; a complete GUI build remains to be verified locally.

---

# Latest: CoderGirl Stage 5.166.30.271026 — World Map Editor + Animations + Death Notes

**Start here:** `development/notes/INSTALL-STAGE5.166.30.txt`.
World Map tools now appear on the left with the atlas above painting controls;
map boundary/flag flash colour selectors are at the top, and Paint Tiles vs
Choose Flag Art are separate exclusive toggles. Animated map tiles now share
Visual Tilemap Editor playback semantics (frames, VBlanks/frame, loop, ping-pong)
and display in both designer and SIDBOX runtime. Hazard Zones now have their
own Death Note in Game Object properties, without changing their callback-only
kill policy. Murder Objects and Enemies retain existing notes. Regenerate ALL
Worlds / Game Project and rebuild V1. No new user-owned main.c changes beyond
the pre-existing Stage 5.166.29 fast-path integration. Native C regressions pass;
Qt6 GUI compilation and SIDBOX hardware acceptance remain outstanding.

---

# Latest: CoderGirl Stage 5.166.29.271026 — World Map Render Fast Path

**Start here:** `development/notes/INSTALL-STAGE5.166.29.txt`.
The generated V1 game now skips background, tilemap (both layers), objects,
player, NPCs, spotlight and weather **drawing** while the World Map is open.
The HUD, World Map, display and music still run. The Quest Journal was not
being drawn underneath. **User-authored `main.c` must be updated using the
included exact render-brace instructions:** the IDE never overwrites it.
Regenerate ALL Worlds / Game Project and rebuild V1. The native map, title
and render-gate regressions pass; Qt/hardware still need checking.

---

# Latest: CoderGirl Stage 5.166.28.271026 — World Map Four-Rectangle Runtime Frame

**Start here:** `development/notes/INSTALL-STAGE5.166.28.txt`.
The runtime World Map now draws its map art first, then four solid panels
(top 24px, bottom 32px, left/right 8px) in **the World Map boundary colour**.
The active-world name and control instructions are drawn on top. This removes
the accidental Quest Journal-coloured green top/bottom bars. The established
HUD-aware viewport, flag flashing, panning, save/title behaviour and user
`main.c` remain unchanged. Rebuild the IDE, save the boundary selection,
**Update ALL Worlds / Update Game Project**, then rebuild the V1 game.
Native rendering and selected regressions pass; Qt GUI and hardware remain untested.

---

# Latest: CoderGirl Stage 5.166.27.271026 — Death Title Start + Map Boundary

**Start here:** `development/notes/INSTALL-STAGE5.166.27.txt`.
A no-save death returning to the title now starts the validated original
fresh-snapshot world on New Game, regardless of the title menu's new-world
selection or published registry order. Title Load Game retains saved world.
The runtime World Map's thick surround and 5-pixel frame both use the
World Map boundary colour rather than the Quest Journal's background index.
Regenerate ALL Worlds and rebuild the game. Native C regressions pass;
Qt6 GUI and real SIDBOX hardware remain to test.

---

# Latest: CoderGirl Stage 5.166.25.271026 — World Bundle HAS_TITLE hotfix

**Start here:** `development/notes/INSTALL-STAGE5.166.25.txt`.
Fixes World Bundle failure `Unknown/non-boolean condition HAS_TITLE at gameworlds.rulec:11`,
plus the unresolved `@IDE{WORLD_BASE}` in the recent death return-to-title path.
The game now remembers its initial world if the player visits another world
before dying. **Rebuild the IDE and Update ALL Worlds / Game Project**.
No user `main.c` or saved-game changes. Native title ON/OFF tests pass; Qt GUI
and physical SIDBOX remain untested here.

---

# Latest: CoderGirl Stage 5.166.2.271026 — Quest Journal Designer & joystick navigation

**Start here:** `INSTALL-STAGE5.166.2.txt`. The project-wide Quest Journal Designer
is available from **Quests... → Journal Appearance...**. Touch *only* opens the
journal; UP/DOWN selects, FIRE1/RIGHT tracks and FIRE2/LEFT closes. The journal
fits the HUD playfield, and modal dialogue/inventory/quests temporarily use the
original, untinted palette so weather/night colours cannot darken text. Quest IDs,
TFCard save versions and owner-maintained `main.c` are unchanged. Update ALL
Worlds / Game Project after installing, not just shared helpers.

**Validation:** native touch/joystick tests, SIDBOX SDK-header GCC syntax,
quest/save/checkpoint/two-world regressions pass. Qt6 GUI and physical hardware
not tested in this environment.

---

# Latest: CoderGirl Stage 5.166.1.271026 — Tap Anywhere to Open Quest Journal

**Start here:** `INSTALL-STAGE5.166.1.txt`.

The HUD's QUESTS button was removed. During gameplay, a fresh touchscreen
press anywhere opens the Quest Journal. The existing release-edge latch prevents
that press from immediately selecting or closing an option. While the journal
is open, tapping its quest rows, TRACK, scroll and CLOSE controls retains the
Stage 5.166 behaviour; FIRE2 still closes it.

The SIDBOX touch provider is now reinitialised on each world journal
registration, rather than only once per applet lifetime. The existing SDK
API is used, and no firmware changes are assumed. If taps still do not
register, the firmware's touch provider needs checking on the device.

**Only runtime helper and splash screen sources changed.** No project save
format, main.c changes, quest IDs, rule generation, or world regeneration are
required. Update Game Project and accept the `gameadventureruntime.c` helper
replacement. Native touchscreen, quest/save, checkpoint, and SDK-header GCC
syntax tests passed. GUI/full ARM and physical touch behaviour untested.

---

# Latest: CoderGirl Stage 5.164.3.261026 — Multi-World Save API Compile Fix

**Start here:** `INSTALL-STAGE5.164.3.txt`.

Fixes eight undeclared callback errors in Platformer3's generated gameworlds.c
(world1 and forest). The generated world_api.h headers now declare four
world-prefixed disk save/import callback functions that the registry requires.
CoderGirl also marks existing old world headers as outdated during the build
check. **Update ALL Worlds**, not just the active .sbgm, after installing.
Existing save data format, gameplay, Checkpoint interactions and main.c are
unchanged.

**Validation:** native two-world world-manager C syntax compile and negative
missing-prototype check; existing save/load corruption, checkpoint, and rule
regressions. Full Qt6 GUI and ARM hardware compilation still to verify.

---

## Previous release: Stage 5.164.2

# Latest: CoderGirl Stage 5.164.2.261026 — Inventory-Operated Checkpoints

**Start here:** `INSTALL-STAGE5.164.2.txt`.

Fixes the Stage 5.164.1 Save Game Checkpoint properties mismatch. A checkpoint can now require a real inventory item for USE activation, unlocking wrong-item / success / cancel sounds, dialogues, rewards and stat outcomes via the existing proven inventory-interaction runtime. Touch/FIRE2-only checkpoints still work when no required item is chosen. The saved-world Flow Debugger now draws inventory → checkpoint → save-slot links. No TFCard save-format changes, runtime rule template edits, or main.c changes.

**Validation:** inventory USE-to-checkpoint generated-runtime C test, existing native 10-slot save/recovery test, 16 world flag combinations, and UI/export/flow source checks passed. Qt6 IDE and physical SIDBOX tests remain outstanding.

---

## Previous release: Stage 5.164.1

# Latest: CoderGirl Stage 5.164.1.261026 — Checkpoint Selector + Stable Particle Preview

**Start here:** `INSTALL-STAGE5.164.1.txt`. Stage 5.164.1 fixes the off-by-one Game Object type display (the Save Game Checkpoint now has its own entry, followed by Particle Spawner) and stabilises the modal particle-scene viewport. The Stage 5.164 TFCard save/load runtime and generated game rules are unchanged.

---

## Previous release: Stage 5.164

# Latest: CoderGirl Stage 5.164.261026 — TFCard Save/Load + Checkpoint Game Objects

**Start here:** `INSTALL-STAGE5.164.txt` for installation, exact files, save format, hardware-test steps and limitations.

Stage 5.164 adds 10 persistent TFCard save slots, alternating A/B verified file copies, saved game/world/adventure state, a working title-screen Load Game slot selector, and a new selectable Save Game Checkpoint object (touch or FIRE2, choose slot 1–10). The saved-design Flow Debugger now draws checkpoint → TFCard slot links. Existing owner-maintained `main.c` startup flows using `request_at()` and `apply_pending()` are supported. Stage 5.163 rules and 5.162 atmospheric effects are preserved.

**Validation:** 16 conditional generator test configurations and a native C save/load + corrupt-copy recovery regression passed. Qt6/ARM/physical SIDBOX checks are still required.

---

## Previous release: Stage 5.163

# Latest: CoderGirl Stage 5.163.261026 — audited rule generation and flow diagnostics

**Start here:** `INSTALL-STAGE5.163.txt` for exact drop-in installation, source changes, regression tests, and known limits.

Stage 5.163 repairs the world registry nested-condition parser and marks invalid splines as broken in the saved-design Flow Debugger. The older wrong-item test is corrected for newest-first inventory order. The rain/day-night code from Stage 5.162 is unchanged.

---

## Previous release: Stage 5.162

# CoderGirl Stage 5.162.261026 — natural layered rain + persistent world day/night clocks

## Changes

### Layered, natural rain (plus scattered snow)

* Old fixed `i * 97 / i * 137` positions and `i % 3` speed lanes replaced with stable 32-bit-hashed starting positions.
* Three interleaved **rain fall-rate/length layers**, all using the **existing density** setting. Slow 4–6 px/frame / 3–5px streaks, mid 7–10 / 5–7px, quick 11–15 / 7–10px, 50 Hz. No additional near-camera density.
* A drop gets a new, deterministic random X after each bottom-to-top wrap, so repeating vertical columns cannot form. Wind remains active. Rain/snow rectangles stay inside the 480×320 viewport; drops begin populated immediately, without pre-warming or heap allocations.
* Snow also uses scattered positions and 1–3 px/frame fall speeds.
* Long-running rain no longer resets its animation every 16,384 frames (about 5.5 minutes).
* World Canvas Weather preview follows the same scatter/three speed layers, clipped to the viewport.
* Existing lightning duration/brightness/shape, spotlight, weather colour and palette tint logic **unchanged**.

### Remember time-of-day when returning to a world

* During world unload, save its current day/night phase **per world index**. When that world is entered again, restore its clock before the first rendered palette frame. A different world's cycle can have different durations and current progress.
* Inactive worlds' day/night clocks **pause** while away, then continue from their saved point on re-entry. They do not advance off-screen. (Future enhancement, if desired, could make world clocks use shared global time.)
* Fixed tint (e.g. World 1 fog) stays fixed and is unaffected by saved cycle state; first visits still respect "Start at night".
* Shutdown resets the saved clocks for a fresh game session.
* Memory cost is 5 bytes per world (32-bit tick + validity byte); no change to serialized world files, `.pal` files, world registry or main.c API.

## Install option A: CoderGirl IDE

1. Install `CoderGirl-Stage5.162-261026-DROPIN.zip` **over Stage 5.161** using the files' relative paths (not inside a new subdirectory).
2. Rebuild CoderGirl; splash should say `Build: 5.162.261026`.
3. Open the project and run **Update Game Project** to regenerate `gamehelpers/gameworlds.c`, then rebuild/upload the game.
4. Your **hand-maintained `main.c` must be left untouched**. Keep the Stage 5.161 arrangement: update `game_update_weather(1)` and `game_update_particles(1)` exactly once per frame outside the dialogue/transition pause, but keep `game_update_gameplay(1)` inside that pause. Render spotlight before weather.

## Install option B: immediate Tiny Red Riot game test

`TinyRedRiot-Stage5.162-GameTest-PATCH.zip` contains a ready-patched **`gamehelpers/gameworlds.c` only**, adapted from the **Stage 5.161 game patch produced from your uploaded Tiny Red Riot project**. Back up your game source, replace only that generated `.c`, rebuild and upload. **There are no changes to your `main.c` in this stage.** When you later use Update Game Project, ensure CoderGirl is at Stage 5.162, otherwise the generated manager could revert.

## SIDBOX test checklist

1. In rainy Forest, inspect the 64 drops at 50 FPS: they should scatter horizontally and fall at mixed speeds/lengths, not in three regimented lanes. Wind and density controls should still behave.
2. Let it rain longer than 5.5 minutes. The pattern should not abruptly reset.
3. Configure a world with an automatic day → dusk → night → dawn cycle. Leave it **mid-dusk**, visit another world, and return: it should resume from the saved dusk progress, rather than starting from daytime.
4. Leave Forest and enter World 1 (fixed fog), then return Forest. Each world's palette should be correct through the circular transition, while Forest remembers its own cycle position.
5. Ensure lightning shape/duration/strength, pause-during-dialogue and spotlight rendering remain unchanged.

## Validation

Stage 5.162 native GCC test checks real extracted renderer functions: 64 drops remain within viewport, >45 distinct initial X columns, three different speed layers, new X positions after wraps, no short animation-clock reset, and separate saved day/night phases on multiple world visits. All Stage 5.146–5.161 focused regression suites also pass (17 total). Native host compiler is **not** a Qt6 GUI compile or a real SIDBOX performance test.

## Stage 5.166.3 (27 October 2026)
The project-wide Quest Journal Designer now selects its own PPB nine-slice
atlas/cells and uses the standard 256-colour palette picker. The live preview
renders the selected tiles, reads HUD docking from `gamehud.sbhud`, and drops
the redundant manual HUD preview selector and shared dialogue-skin checkbox.
The generated quest viewport avoids applying the top-dock offset twice.
See INSTALL-STAGE5.166.3.txt for installation, resource deployment and tests.

## Stage 5.166.38 (27 October 2026): Fresh New Game resets collected world items

Fixed a persistent-pickup reset omission: title New Game cleared world snapshots
but did not clear `cg_pickup_permanently_collected[]` in individual world
modules. Every world's remote-reset function now clears permanent pickup
flags and saved world/pickup/reward RAM, including worlds with pickups but no
managed platforms. Story reset also clears its saved payload. Load Game
continues to import selected saved progression after this reset. No changes
to `.map` files, saved-file version or hand-owned `main.c`. See
`development/notes/INSTALL-STAGE-5.166.38.txt`.


## Stage 5.166.39 (27 October 2026): Game Object checkbox alignment

- Game Object Properties checkbox rows now span the form columns to protect
  their borders and text from the width of adjacent labels.
- Dependency-guard checkboxes have equal enabled/disabled padding and
  minimum content height in the global IDE theme.
- This is a GUI-only styling/layout release. No game regeneration required.

See `development/notes/INSTALL-STAGE-5.166.39.txt`.

## Stage 5.166.42.271026 — Visual Nodes connection usability

- Makes wire right-click targeting more forgiving, with 20-scene-unit path shapes
  and a 21×21-viewport-pixel context-menu query.
- Separates multiple connection curves between the same Trigger and object.
- Adds a Trigger Connections list, Edit Action and Remove buttons to the right
  details panel; explicit action dispatch prevents Remove falling back to Enable.
- Narrows the Game Objects sidebar to a 175-pixel initial width (220 max).
- Does **not** modify saved .sbgm/.vsgm schemas, game runtime, .map or main.c.
- Tested source/schema and existing native suites 5.166.31–.38 and Visual Nodes
  .40–.42. Full Qt GUI compilation and interaction require verification.

Stage 5.166.71 (28 October 2026): existing Game Object connections can now be
refreshed into the Visual Nodes graph, including Enemy defeat/key pickup links
and explicit cross-world/NPC action targets. See development/notes/INSTALL-STAGE5.166.71.txt.

## Stage 5.166.121 (30 October 2026): unordered quests and ON COMPLETED Visual Nodes

- Quest Designer: per-quest **Allow objectives in ANY ORDER** checkbox. Unticked is the existing ordered behaviour, and old quest JSON defaults to ordered.
- Unordered objectives each have an independent completion bit (256 maximum = 32 bytes globally). All must be complete for the quest to finish. Repeated signals do not double-count. Inventory/world objectives are rechecked automatically while active; dialogue and event signals are consumed only while active.
- Project-wide quest prerequisites (`requires`) and mutually exclusive branches (`excludes`) retain their existing meaning. On completion the next prerequisite quest can unlock in the same refresh.
- Visual Nodes: **Quest Lines / Completion Events** contains a virtual card for each quest. Its gold **ON COMPLETED** socket drives ordinary action targets, including the existing QUEST EVENT/SIGNAL target. Links are saved in the world `.sbgm` under `questCompletionActions` (not `.vsgm`). One-shot transition only, not a constant TRUE and never replayed on restore. Completion actions are local to the world where the quest finishes.
- Generated C: world-manager completion hook appends actions to the Stage 119 bounded FIFO. No direct object actions from the quest manager and no recursive dispatcher.
- Save payload version 4 adds a 32-byte completion bitset and accepts prior v3 ordered save payloads where the project identity/schema are still compatible. Changing objective IDs, order, or a quest to unordered changes the project quest schema and may invalidate previous saves by design.
- Current limitations: the Journal shows the first unfinished objective for an unordered quest, not a simultaneous tick-list. Virtual ON COMPLETED nodes currently connect directly to executable targets, not independent Logic cards or dialogue cards. Worlds containing zero managed Game Objects cannot export active completion links; the exporter reports an error instead of silently omitting them. These are follow-up UI/runtime enhancements, not yet implemented.
- Native regression: `python3 development/tests/test_stage5166_121_quest_runtime.py` verifies ordered and unordered signals, duplicates, save/load, v3 migration, and one-shot completion. `python3 development/tests/test_stage5166_121_quest_sources.py` checks editor/generator wiring. Full Qt IDE build and STM32 hardware execution remain to be verified.
