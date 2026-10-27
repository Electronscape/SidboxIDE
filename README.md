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
