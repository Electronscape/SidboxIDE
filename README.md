CoderGirl Qt6 IDE source, Stage 5.41.1 (23 October 2026).

Hotfix for Qt `QVariant::toInt(8)` compiler errors and HUD inventory balances.
See README-Stage5411.md.

---

CoderGirl Qt6 IDE source, Stage 5.41 (23 October 2026).

Newest changes: see README-Stage541.md. This release adds unified HUD palette colours, per-item inventory PPB atlas choices, opt-in collectible persistence with cross-world inventory definitions, array-aware object pasting and viewport-centred resource imports.

The original Stage 5.12 README is preserved below for historical context.

---

CoderGirl Qt6 IDE source, Stage 5.12 (22 October 2026).

Based on Stage 5.11, including Stage 5.10 persistent Tile Stamp fix,
Stage 5.8 compile corrections, multi-world global stamps and helpers.

Changes in Stage 5.12:
- Remove byte-identical generated root gameassets C/H after publishing.
- Keep world-specific gameassets C/H under worlds/<world>/gameassets/.
- Prune obsolete root asset source references when saving .proj.
- Preserve current world's embedded/external graphics mode across F5.
- Point explicit Generate V1 warning at the world-specific files.

Read STAGE5.12-REMOVE-DUPLICATE-GAMEASSETS.md for testing and details.
Qt6 compilation and SIDBOX hardware testing are pending.
