SIDBOX / CoderGirl IDE source - Stage 5.57.231026

Adds draggable numeric HUD statistics, signed enemy/hazard stat changes
(health, lives, score, coins, shared custom stats) and opt-in top/bottom
HUD docking with an appropriately reduced tilemap playfield. Overlay remains
the default; original PPBs and palette cell indices are not modified.

See STAGE5.57-HUD-STATS-SIGNED-DAMAGE-DOCKING.md, especially the integration
steps for user-owned main.c and the full-width dock requirement.

Native regression tests pass; Qt6 GUI build and STM32 hardware tests are
outstanding. Do not assume the new HUD dock has been performance-accepted.
