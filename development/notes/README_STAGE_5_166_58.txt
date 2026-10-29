SIDBOX CoderGirl IDE — Stage 5.166.58.281026
Editable Boolean branches in Game Object Properties

The Trigger-owned Boolean configuration used by Visual Nodes is now editable
from Game Object Properties, using the exact same .sbgm fields.

Trigger: open Switch, Trigger & Save Checkpoint -> Boolean. Choose the Game
Object whose active state is read, TRUE/FALSE dialogue from the Adventure
folder tree, and ordered Game Object Enable/Disable/Toggle actions.

State source (for example Lifty): open Triggers Reading This Object. The
same stopLift-owned condition can be edited here without inventing independent
On Enable/On Disable events on Lifty.

Controls: + Add, Remove, Up and Down for each TRUE/FALSE action list. Save
commits through the existing Game Object resource undo path; Cancel discards
uncommitted edits. Visual Nodes reads those saved .sbgm fields on next open.

No generated runtime code, save format, .map, .vsgm, or main.c changes.
Full Qt6 GUI compilation is NOT verified here; native and schema tests only.
