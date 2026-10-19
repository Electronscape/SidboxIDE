# Stage 3.91 — Breakable Game Object sounds

Baseline: **Stage 3.90**, including the user's tested Stage 3.88 momentum and Stage 3.89 breakables.

## Features

Placed Game Objects configured as **Breakable Object** now offer three optional Sound-resource selectors in the right-hand AUDIO panel:

- **Breakable — hit**: plays on every successful damage contact, **including** the final hit.
- **Breakable — bounce**: plays whenever a qualifying stomp produces an actual spring-like launch (only with Bounce on; not in Touch mode).
- **Breakable — shatter**: plays exactly once on the final hit that deactivates the object.

A final bouncing hit may trigger all three. If they need to overlap audibly, assign separate channels in the underlying Sound resources. A sound played on an occupied channel can interrupt the current sound. Choosing **None** leaves that sound silent; older `.sbgm` files have all three selectors defaulted to None.

All three reuse the existing sound resource's channel, volume/pan, plus the configured Game Object **Audible radius** (0 = nonpositional). No new runtime sound format or audio API was added.

## Implementation

- `gamedesigner.h`, `gamedesigner.cpp`: store 3 stable sound IDs per placed resource; add selectors and enable only for breakables. Bounce sound is enabled only when Bounce is on and Touch mode is off.
- `gamedesigner_project.cpp`: serialize `sfxBreakHit`, `sfxBreakBounce`, `sfxBreakFinish`. Missing fields default to empty ID.
- `gamedesigner_export.cpp`: validate referenced sound IDs and generate `cg_sound_*()` calls in `gameworlditems_after` based on the event flags, with the same spatial attenuation and channel handling as springs.
- `idelibs/codehelpers/game/worldobjects.c/.h`: expose `break_hit_triggered` and `break_bounce_triggered` alongside existing `break_triggered`. Initialise/reset each on update; set only on actual hit or launch; break flag remains tied to the final hit.
- `idelibs/codehelpers/game/worldobjects.txt`: explain sounds and direct C usage.

## Testing

- `development/tests/test_stage391_breakable_sound_events.c` — native physics test covering no false sounds when walking/falling, hit+bounce, final shatter, pulse reset, touch mode, bounce disabled.
- `development/tests/test_stage391_breakable_audio_integration.py` — editor/save/export structural checks.
- Earlier Stage 3.89, 3.90 and 3.68 native world-object tests also passed.
- **Qt6 GUI and SIDBOX hardware were not available here; test in Qt Creator and on the device.**

## Applying

For the IDE, replace all listed changed production files, including the **C and H worldobjects helpers in the IDE templates**, and rebuild in Qt Creator. Then configure your breakable sound resources and choose **F5 → Update and Compile** to refresh generated `gameworlditems.c` and helper templates in the game project. A regular Compile Without Updating will *not* export the new audio triggers into the existing project.

User-owned `main.c`, physics/tilemap source and stage UI styles were not modified.
