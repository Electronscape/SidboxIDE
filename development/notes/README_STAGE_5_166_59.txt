SIDBOX CODERGIRL IDE — STAGE 5.166.59.281026
Multi-input Boolean / AND / OR nodes and collapsible Game Object Properties

Base: Stage 5.166.58.281026

WHAT CHANGED
* Visual Nodes has Logic > Boolean, AND (2–16 inputs) and OR (exactly 2 inputs).
* Drag the output of one Game Object into blank space and choose a logic operator.
  That first Game Object must have an existing Trigger action controlling it,
  since the conditional actions are owned by a Trigger in the current runtime.
* Add further inputs: place the next Game Object card on the graph, then drag
  its teal state-output socket directly onto the AND/OR card.
* The output of TRUE and FALSE connects to existing action/dialogue cards.
* Right-click a condition card to change Boolean/AND/OR operator.
* Right-click incoming state wires to remove individual inputs.
* New .sbgm fields are toggleStateOperator (default boolean) and
  toggleStateInputIds (additional inputs). The original toggleStateTargetId
  remains the first input for compatibility with existing .sbgm files.
* Game Object Properties: Switch / Trigger / Save Checkpoint now has a collapsed
  condition section. Triggers Reading This Object has collapsed groups as well.
  Choose the same operator, input Game Objects, TRUE/FALSE dialogues and ordered
  TRUE/FALSE actions. On an incoming target, the currently inspected object is
  explicitly marked as a fixed input, not a redundant source dropdown.
* .vsgm remains layout-only, read-only Logic Flow remains untouched.
* Generated runtime evaluates the named Game Objects' active state AFTER the
  owning Trigger has performed its normal Enable/Disable/Toggle actions.
  AND = all active; OR = at least one active. Old Boolean = one active.

IMPORTANT EXECUTION SEMANTICS
The condition runs when ITS OWNING TRIGGER ACTIVATES. It is not a continuously
polled state watcher. If two different switches toggle two different objects,
attach the check to the event whose activation should evaluate the puzzle, or
add corresponding checks to both Triggers. A future state-change event mode
would be a separate runtime feature.

VALIDATION
AND requires 2–16 unique active-state inputs, OR requires exactly two, and
Boolean requires one. Incomplete graph conditions cannot save to .sbgm, and
export validation rejects invalid/missing input IDs.

INSTALL
Extract HOTFIX over the matching Stage 5.166.58 IDE source tree and rebuild.
When you change any actual gameplay conditions, Update ALL Worlds / Update Game
Project and rebuild V1. No changes to game-owned main.c or existing .map files.

TEST
1) Trigger A toggles Lifty. Connect Lifty output -> Logic > AND.
2) Place Door card and drag Door state output -> AND card.
3) From TRUE connect Show Dialogue 'Both are enabled'.
4) From FALSE connect Show Dialogue 'Not yet'.
5) Save, close graph, open Game Object Properties for Lifty and Door.
6) Verify the condition is editable in 'Triggers Reading This Object'.
7) Reopen graph and check positions, all wires and TRUE/FALSE dialogues.
8) Regenerate worlds and test on actual SIDBOX hardware.
9) Test equivalent OR condition (only one active needed).
10) Recheck new-game reset/save-load and title recovery after rebuild.

VERIFICATION
* Native GCC compiled state truth-table test: passed.
* Old Boolean / Visual Nodes source and native tests 5.166.53–58: passed
  (stale text-only test assertions updated to accept multi-input implementation).
* Stage 5.166.36 title button latch and 5.166.38 pickup reset: passed.
* Braces/delimiters checked on edited C++ files: balanced.
* Full Qt6 IDE compilation and desktop UI testing: NOT performed here,
  because Qt6 development headers/libraries are unavailable.
* Physical SIDBOX runtime testing: NOT performed here.

Back up your .sbgm and .vsgm before trying this experimental release.
