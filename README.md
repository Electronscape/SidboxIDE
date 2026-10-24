SIDBOX / CoderGirl IDE source — Stage 5.68.241026

Title-screen runtime: fixed main-menu rectangle geometry and separated the
PPB background onto the hardware BACK layer, leaving the title text and menu
selector on the foreground with their editable ARGB CLUT. The Options background
has its own opaque PPB-derived CLUT, restored on submenu exit.

See STAGE5.68-TITLE-RECT-AND-ALPHA-LAYERS.md for details and hardware limitations.

Regenerate gamehelpers/gametitle.c with Update Game Project and rebuild the game.
No change to user-owned main.c, game worlds, PPBs, or the audio mixer.
