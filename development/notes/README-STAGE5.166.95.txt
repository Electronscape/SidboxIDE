SIDBOX CoderGirl IDE Stage 5.166.95 (29 October 2026)

CRITICAL Undo/Redo crash hotfix for Conversation Flow Groups.

Cause: restoreGraphHistory() called m_scene->clear() (which destroys
FlowGroupBox items), but left dangling pointers in m_flowGroups.
Rendering the restored graph then called setTitle() through a freed group.

Fix: clear non-owning m_flowGroups references before clearing the scene,
then construct new groups from the restored model and card layout.

Also includes the hidden/visible conversation root state in Undo history
and digest so Undo/Redo restores group visibility consistently.

No changes to .sbgm gameplay schema, exporter, runtime or main.c.
Extract over Stage 5.166.94 and rebuild the IDE.
