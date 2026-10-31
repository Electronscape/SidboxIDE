SIDBOX IDE Build 5.131.4.311026 - COMPARE / QUEST STATE connection integration

PATCH ONLY - apply over the already installed 5.131.3.311026 source tree.
Replace the four files in the ZIP at IDE source-root paths. Do not replace runtime, generated game sources, or your project's main.c.

CHANGED FILES
- gamevisualgraphlogic.h: COMPARE and QUEST STATE now accept 0 or 1 optional WHEN inputs; generated C expressions combine WHEN && numeric/quest condition. Existing zero-input conditions retain their previous behaviour.
- gamevisualnodes.cpp: real, visible optional WHEN input socket on both cards; accepts STATE, EVENT, or LOGIC RESULT; creates connected nodes when dragged from an eligible existing output; supports editing/replacing the input. Cross-owner logic-node links remain disallowed and report the mismatch; choose the same object owner or create from the gate's owner.
- gamedesigner.cpp: Game Object Properties now displays and preserves the optional WHEN input, and rejects more than one selected WHEN input on Save instead of silently deleting the connection.
- splashscreenwidget.cpp: Build 5.131.4.311026

USE
1. Open Visual Nodes. Existing COMPARE cards should show a left-hand WHEN: (optional) square. They remain valid and independent until connected.
2. Drag a trigger STATE ON/OFF, a gold ON ACTIVATE/ON HIT event, an object STATE, or an existing logic RESULT into that square. This is a real .sbgm input link.
3. For a new automatically wired COMPARE, drag one of those outputs onto empty canvas, then choose Logic > COMPARE.
4. Configure stat/operator/threshold within the Compare card.
5. Drag RESULT to another logic gate input (same owner) or to a Game Object; drag TRUE/FALSE to actions/Adventure dialogue; Save Graph + World, reopen and regenerate the game.

BEHAVIOUR
- No WHEN input: Compare watches its stat/Health; Quest State watches quest changes (same as Stage 131.3).
- Teal STATE/LOGIC WHEN: requires a true held condition AND the numeric/quest comparison.
- Gold EVENT WHEN: requires that one-frame pulse AND the numeric/quest comparison; an unrelated stat change won't repeat event-pulse dialogue.
- An unsupported cross-owner logic link is still rejected. The graph definition is stored per owning Game Object in .sbgm, not in .vsgm.

VALIDATION
- 17 focused checks passed, including a native GCC -Werror test of the actual generated compare helper and source-regression checks across the editor/schema/exporter.
- Full Qt6 IDE compilation and SIDBOX hardware tests NOT performed here: Qt 6.5 development SDK is missing.
- No user game files modified.
