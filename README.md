# CoderGirl IDE / SIDBOX Stage 5.71.5.241026

**Gift-to-HUD hotfix:** Inventory grants from dialogue-close now display immediately in HUD inventory-linked pickup counts, even before any floor pickup. Stage 5.71.4 dialogue gifts and NPC visibility remain intact. No additional per-frame or TFCard work.

Apply the drop-in over Stage 5.71.4, rebuild the IDE, use **Update Game Project** to regenerate `gamehelpers/gameworlds.c` and `gamehelpers/gameadventureruntime.c`, then rebuild the SIDBOX game. Leave handwritten `main.c` untouched.

See `STAGE5.71.5-DIALOGUE-GIFT-HUD.md` for diagnosis and tests.
