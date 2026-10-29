SIDBOX CoderGirl IDE - Stage 5.166.60.281026

EXPERIMENTAL: Independent, chainable Visual Logic Nodes

This stage changes the IDE and generated game-world logic; the legacy single
Boolean conditions remain compatible, and the old game files are not touched
by installation. Use a backed-up test world before editing existing puzzles.

The same node data lives in .sbgm and is editable in Visual Nodes and the
collapsed Game Object Properties panels. The .vsgm still stores layout only.

Full installation, migration, execution semantics and first-test instructions:
  development/notes/STAGE-5.166.60-GRAPH-REWRITE.md

Apply source hotfix over Stage 5.166.59, rebuild IDE, then regenerate worlds
and rebuild V1 only after adding new graph connections. Leave user main.c alone.

Native source/schema tests and standalone C truth tables passed. The FULL Qt6
IDE compilation and physical SIDBOX test are UNVERIFIED in this environment.
