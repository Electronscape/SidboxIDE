SIDBOX CoderGirl Stage 5.103 (25 October 2026)
==============================================

WHAT IS NEW
-----------
- Trigger objects now have an ordered Linked Actions table: + Add Linked Action,
  Remove, Move Up, Move Down. Each row selects a placed Game Object and Enable,
  Disable, or Toggle. Maximum 64 rows.
- Legacy single targetObjectId/targetAction fields remain first in the list,
  preserving old worlds and the existing key/enemy one-target behaviour.
- Extra rows persist as gameObject.triggerExtraActions[] in .sbgm (stable IDs).
- Generated world C executes linked actions in order after a Trigger fires.
  Both ordinary touch/FIRE2 and inventory-USE Triggers use the same path.
- World-flow debugger draws links for extra targets.
- Copy/paste remaps referenced IDs; Update Project rejects missing targets.
- Fade animation Frames per fade step now capped at 32,656 (instead of 65,535)
  in the editor, project loader and exporter. The underlying 16-bit storage
  and game runtime templates remain unchanged.

IMPORTANT TIMING
----------------
0xFFFF = 65535, NOT 32656.
At SIDBOX's 50 FPS, 30,000 frames = 10 minutes and
32,656 frames = 10 minutes 53.12 seconds *PER FADE STEP*.
To fade all the way from 0% to 100% in around 10 minutes, choose e.g.
lowest 0, highest 100, step 100, frames per step 30000.
Smaller steps make the complete fade take many more steps.

USING THE NEW ACTIONS
---------------------
1. In Game Designer, configure a placed sprite as a Game Object, e.g. an
   initially-inactive lamp with an appropriate ACTIVE state frame.
2. Open your Trigger -> Linked Object card.
3. Use + Add Linked Action to assign a target Game Object and action.
   Example ordered rows:
       Steve        Disable
       Lamp left    Enable
       Lamp right   Enable
       Door         Toggle
4. Save the world, run Update Game Project and rebuild the game.
   If an inactive target has no INACTIVE state frame, it is hidden.
5. NPC conversation choice logic remains unchanged. Music, sound and dialogue
   Trigger events use their existing controls, separate from this object list.

COMPATIBILITY AND INSTALLATION
------------------------------
Copy replacement files onto your existing Stage 5.102 IDE source, preserving
relative paths; rebuild the IDE. The ZIP's code files do not touch custom
main.c or change the firmware or game engine templates. Backup your source
and .sbgm files before updating.

The original linked action is stored in legacy targetObjectId/targetAction;
subsequent links are stored in triggerExtraActions. Once the Trigger contains
multiple actions, do not open-and-save that world in a pre-5.103 IDE: older
versions cannot preserve the extra action list.

TESTING
-------
PASS: Stage5.103 static pipeline and native GCC action-order test.
PASS: Stage5.94 trigger and state frame tests.
PASS: Stage5.97 trigger dialogue and wrong-item tests.
PASS: Stage5.98 thought-bubble test.
PASS: Stage5.99.2 reply scaling test.
PASS: Stage5.102 native fade C animation (the older test script also checks
      the outdated splash version and fails ONLY that revision assertion).

NOT YET TESTED: Qt6 desktop compilation and SIDBOX hardware acceptance.
Build marker: 5.103.251026.
