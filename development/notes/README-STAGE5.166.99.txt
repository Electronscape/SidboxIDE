CoderGirl IDE Stage 5.166.99 (29 October 2026)
Visual Nodes: Theme Control Consistency

- Uses the actual IDETheme passed to openGameVisualNodes().
- All proxy-widget controls on NPC, Trigger, independent logic, legacy Boolean, dialogue and GIVE cards share one theme-derived palette.
- Node-body fills use panelBackground; text fields/dropdowns/spinboxes use inputBackground.
- Buttons use accent, with hover, disabled, selected text, borders and tooltips from the IDE theme.
- Canvas uses editorBackground; flow group body uses a translucent alternateBackground.
- Existing coloured header stripes, node outlines, input/output sockets, and wire colours remain unchanged.
- No game exporter, world format, dialogue rules, .vsgm schema or runtime modifications.

Extract on top of Stage 5.166.98, rebuild and verify 5.166.99.291026 on splash.
