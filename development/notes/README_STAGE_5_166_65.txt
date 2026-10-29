SIDBOX CoderGirl IDE  -  Stage 5.166.65.281026

Independent Logic: Adventure NPC action-target compatibility.

Fixes world generation rejecting an independent logic FALSE (or TRUE)
action targeting an Adventure NPC such as Guardian[0]. Normal Trigger
actions already supported these targets. Independent logic actions now
use exactly the same target resolver.

Supports both existing local Visual Nodes sprite IDs and canonical
@npc:<world>:<spriteId> IDs; no graph reconstruction or file migration.
Game Object Properties also labels NPC targets as NPCs.

Strict socket rule: Game Objects have local .active state; Adventure NPCs
have visibility via gameworlds_npc_action(). Logic TRUE/FALSE action
outputs may show/hide/toggle NPCs. Direct RESULT -> NPC state binding is
not supported, and Visual Nodes now blocks it during editing.

How to install:
  Apply the hotfix over Stage 5.166.64 sources and rebuild the IDE.
  Open the existing .vsgm, do not reconstruct the nodes.
  Run Update ALL Worlds / Update Game Project, and rebuild V1.
  No main.c, .map, .sbgm, or .vsgm migration required.

Tested: focused graph/Decoration/Boolean and title/save reset regressions,
plus native C test using the actual gameworlds_npc_action and
adventureruntime NPC visibility functions. Full Qt6 GUI build and physical
SIDBOX execution of this precise NPC branch are not verified here.

See development/notes/INSTALL-STAGE5.166.65.txt.
