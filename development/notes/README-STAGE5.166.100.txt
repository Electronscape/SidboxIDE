SIDBOX CoderGirl IDE, Stage 5.166.100 (29 October 2026)

Visual Nodes side-pane improvements:
- Removed the large instructional banner above the editor.
- Visible Nodes is a searchable, grouped tree, including NPCs, Game Objects,
  Logic, dialogue actions, and conversation flows. Double-click a card to
  centre it on the canvas.
- Sidebar node registrations continue to use existing card IDs and game data.
- Selected Card now has an accessible two-column property inspector showing
  the important authored data of NPCs, Triggers, dialogue choices and GIVE
  exchanges; long reference explanations are optional.
- Action connection editing buttons remain available for relevant card types.
- Removed fixed maximum width from left pane and the maximum height from the
  action list. Splitter sizes are restored/saved in per-world .vsgm metadata,
  including when closing with no gameplay edits.
- Splash version updated to Build: 5.166.100.291026.

This is an IDE UI-only update. No changes to game generation, .sbgm game
schema, runtime, TF-card saves, or hand-maintained main.c.

Test on your Fedora Qt desktop: tree population and search, double-click
navigation, inspector data, splitter persistence after closing and reopening,
Undo after editing a graph and editing actual action links.

Qt desktop compilation could not be performed in this environment.
