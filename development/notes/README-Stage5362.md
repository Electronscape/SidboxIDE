# Stage 5.36.2: Remove intrusive TFCard checklist

Fix for a 5.36.1 regression: `TFCard-REQUIRED-FILES.txt` was written to the generated world folder, but was not in its `world-build.json` owned-file list. This made the **next** update fail with a misleading "additional file" error.

- Reverted Stage 5.36.1's TFCard checklist and extra export warnings. No further checklist is generated.
- The world bundler recognizes *only* the obsolete CoderGirl-generated checklist, identified by its exact header, so the next successful world publication quietly drops it as part of the normal atomic bundle replacement.
- Real user-authored extra files are **still protected**, and the bundler still refuses to delete them.
- Existing source/runtime asset checksum behaviour unchanged; IDE's internal dependency checks are not disabled.
- Does not modify project `main.c`, hand-authored files, `.sbgm` designs, or PPBs.
- Build: 5.36.2.231026. IDE-only source hotfix.

## Install

Replace the changed IDE files, rebuild the IDE, and run **Update Game Project** normally. No manual file deletion is necessary for the Stage 5.36.1-generated checklist.

## Validation

Source regression asserts that no manifest code remains, that the legacy file is recognized by its generated marker, and that protection against other user files remains. Full Qt6 GUI build not available in this container.
