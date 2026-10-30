Stage 5.166.104 - Stompable Enemy Patrol: Turn BEFORE Ledges
29 October 2026

INSTALL
  Overlay this complete IDE source package on Stage 5.166.103.
  Rebuild CoderGirl; splash: Build: 5.166.104.291026.
  In your game project, regenerate ALL Worlds and rebuild your game,
  because the fix is in the generated helper gameworldobjects.c.
  Your hand-maintained main.c does not change.

WHY THE ENEMY WALKED OFF A CLIFF
  game_world_objects_roam() in the worldobjects.rulec generator tested
  ground under the ENTIRE enemy hitbox. At a platform edge the rear foot
  stayed supported, so the enemy continued walking into empty space.

WHAT CHANGED
  Ahead of each 1px patrol step, probe for collision support under the
  leading foot (right edge when walking right, left edge when walking
  left). Reject gaps/abrupt deep drops and reverse direction BEFORE
  advancing into them. To preserve gradual downhill slopes, the probe
  can search deeper than the usual step height, but compares the next
  pixel of terrain against the preceding pixel to reject abrupt drops.
  The existing full-width descent calculation, climbing and wall-turn
  logic remains unchanged. No extra project fields, game save changes,
  new heap allocations or additional object properties.

TESTING
  A host-native C harness compiles the actual patrol code from the
  generator template and checks: left/right edge turns, movement at 8
  px/frame, deep step reversal, both gently and steeply descending
  slopes, wall collisions, small up/down steps, and sprite facing/coords.
  Additional source-level regression tests exercise previous IDE features.
  Actual SIDBOX hardware performance and gameplay must still be tested.

DESIGN LIMITS
  Very unusually wide enemy hitboxes on exceptionally steep, extended
  slopes may turn sooner than intended due to the bounded look-ahead.
  The collision callback uses the same solid/slope rules as the player;
  one-way platforms remain unchanged by this patch.
