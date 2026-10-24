# Stage 5.65 — SIDBOX Title Screen Options submenu

2026-10-23

## Design

In Title Screen Designer click **Edit Options Screen...** to open an independent
480x320 scene. Title, optional separate PPB background (or inherit main title
background), Sprite/Direct prepared/Direct convert modes, text CLUT colour,
independent text X/Y scaling, snap grid, mouse wheel zoom and middle-button pan
are editable. Drag the heading and eight fixed option rows to position them.
Labels and X/Y positions are editable. The settings and their defaults are
stored under `optionsScreen` in `.sidbox-title-screen.json`, with no new file.
Accepting the screen groups its edits into the existing title editor's history;
Cancel leaves original data unchanged.

## Generated runtime

- Main menu **Options** opens the second screen.
- UP/DOWN changes the selection. LEFT/RIGHT adjusts sliders by 5 and changes
  difficulty; FIRE1 toggles an item or increments its value.
- FIRE1 on Back, or FIRE2 anywhere on Options, returns to main menu.
- Music On/Off stops/restarts the selected title music on demand.
- Music volume 0–100 is stored/accessible, but **the present SDK API has no
  global MP3/music-volume mixer function**. Moving its slider does not yet
  change MP3 amplitude. Don't claim otherwise.
- SFX enable/volume 0–100 is applied to newly generated `gameassets.rulec`
  playback wrappers and `gameworlditems.rulec` positional gain via a weak
  optional `gametitle_scale_sfx()` symbol. Projects without title support
  retain their previous sound behaviour. Re-export the worlds.
- Screen shake, text speed (0–100), and difficulty (Easy/Normal/Hard with
  project-configurable Easy/Hard multiplier percentages) are exposed by
  `gametitle.h` getters. The game must use these values in its camera,
  dialogue and difficulty logic respectively. No fake automatic effects.
- Load Game still does nothing. Controls remapping is deferred.
- Settings last for the current runtime session. The prototype deliberately
  does not add TFCard reads/writes for preferences while MP3 playback may
  contend with other filesystem operations. Persistence comes later.
- Selector style/colour from the main title is reused in Options.

## Regeneration

Regenerate from Game Designer / Update Game Project, review the updated
`maingame.c.txt` if needed, and rebuild. **Never overwrite a handwritten
`main.c`.** PPBs retain their own palette indices.

## Verification

Source checks plus real-C syntax compile against SIDBOX `apis.h`; full Qt6
build and real hardware visual/performance validation must be done on Fedora.
