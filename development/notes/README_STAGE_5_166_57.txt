Stage 5.166.57.281026 - Boolean State cross-reference in Game Object Properties

The existing Visual Nodes Boolean remains owned by the firing Trigger. Its
TRUE/FALSE action and dialogue branches now appear read-only in BOTH:
 - the firing Trigger's Game Object Properties
 - the source object's Game Object Properties (e.g., Lifty)

The section shows the real .sbgm dialogue ID and text, branch object actions,
and the owning Trigger. The label deliberately says that these are checks
AFTER the owning Trigger fires, not generic on_enable/on_disable hooks.

The existing Visual Nodes editor remains the editable place for these links.
No changes to .sbgm/.vsgm formats, runtime rule generation, .map or main.c.
Apply over Stage 5.166.56, rebuild Qt IDE only.
Full Qt6 GUI compilation unavailable in this container.
