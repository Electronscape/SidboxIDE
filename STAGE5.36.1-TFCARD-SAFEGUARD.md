# Stage 5.36.1: tracing Result 1 in GameTest

## Diagnosis

`main.c` assigns Result 1 only if `gameworlds_start(WORLDLEVEL)` fails. The game's `WORLDLEVEL` is `world1`. During activation it checks world assets, map/atlas loading and object initialization.

The October 22 working archive had `graphics/tilemap.ppb` pixel FNV-1a `1705505461`. In the October 23 GameTest archive, this PPB was changed and hashes to `520431515`. The generated `worlds/world1/gamelevels/world1.c` expects `520431515`; the unchanged old TFCard file would fail the atlas hash check and cause world activation to return false (Result 1). This is the most likely cause, but the physical TFCard hasn't been examined.

Also, the generated `gameassets.c` loads `graphics/pickups.ppb` (plural). The user said they copied `pickup.ppb` (singular). The PPB loader doesn't check its return value; this separate mismatch can produce missing or corrupt sprite graphics but is not by itself proven to cause Result 1.

## Immediate fix

Copy the updated `graphics/tilemap.ppb` and `graphics/pickups.ppb` from the GameTest project to the TFCard `graphics/` folder, preserving names and case. Re-run the existing platform3.app. This should be tried before changing C source. There is no need to replace user main.c.

## IDE guard

The Game Designer's world publish path creates `worlds/<world>/TFCard-REQUIRED-FILES.txt` with exact resource paths, SHA-256 fingerprints and changed/new markers comparing project files to the prior checklist. The publish confirmation warns that a successful `.app` build does not transfer PPBs to the TFCard. A missing referenced PPB triggers a warning.

This is not a TFCard-aware deployment/verification tool: once copied, the user still has to verify the SD/TFCard files themselves. In batch publish, the checklist is written without interrupting the batch with a modal informational message.
