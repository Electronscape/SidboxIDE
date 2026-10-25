# CoderGirl Stage 5.106.251026: Player-following light anchor and X/Y offsets

Use **Player Start -> Enable local darkness with player spotlight**.

* **Spotlight anchor**: Centre of player sprite (default, uses the shared player's
  visible BOB width/height and scale); or Player sprite origin (top-left).
* **Light offset X**: signed pixels, positive right / negative left.
* **Light offset Y**: signed pixels, positive down / negative up.
* Offsets are **relative to the selected anchor**; they do not modify player
  collisions, animation, world camera or the flashlight radius.
* Settings are saved with the world in `playerStart` of `.sbgm` and restored
  after switching worlds. Old designs missing these properties use centre/0/0.
* Only the SHARED-player path knows the actual sprite dimensions. For worlds
  without a shared player, the runtime keeps the original world coordinate.
* Existing hand-owned `main.c` calls from 5.105 are unchanged; the generated
  world manager resolves the anchor internally.

Installation: overwrite listed source files, rebuild CoderGirl, save the world,
Update Game Project, rebuild/reinstall the game. No firmware change.

Hardware note: the previous Stage 5.105 pseudo-darkness was user-verified at
50 FPS on SIDBOX. This version alters only the light centre calculation and
not the row mask algorithm. Needs a fresh on-device acceptance test.
