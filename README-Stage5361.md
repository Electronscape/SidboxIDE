# Stage 5.36.1: TFCard PPB deployment safeguard

Based on Stage 5.36. This is an IDE-only improvement, with no generated gameplay logic changes.

- Generates a per-world `worlds/<world>/TFCard-REQUIRED-FILES.txt` on Update Game Project or world publication.
- Uses paths from actual generated world asset C and shared player C, plus selected tilemap atlas. The manifest records whole-file SHA-256, byte length, and NEW / CHANGED / UNCHANGED since previous publication.
- The game code generation summary calls out TFCard resources, changed PPBs, and a warning about stale tilemap atlases.
- It cannot inspect the user's real TFCard without an active transfer workflow. `UNCHANGED` compares project exports, not TFCard files.
- No changes to main.c, generated runtime source, tilemap physics, or authored levels.
- Splash: Build 5.36.1.231026.
- Qt6 GUI build and real SIDBOX hardware test remain unverified here.
