# GamerGirl Stage 4.37a — Visible Enemy Properties & Approach-Based Knockback

Stage 4.37a is a **small corrective update** to Stage 4.37. It does not change the `.sbgm` format or the protected game `main.c`.

## What was wrong

The Stage 4.37 Game Object Properties code **created** the `Stompable Enemy` panel, but accidentally did not **add it** to the central scrollable panel layout. Therefore the enemy properties — including `Walk on tilemap`, patrol speed, slope step height, stomp count and defeat drop — were invisible even though they existed in the designer and generated code.

Stage 4.37 also used the *final* centres of the player and enemy to choose enemy knockback direction. A rapidly moving enemy or player could cross the other one's centre in one frame and get knocked the wrong way.

## Fixes

1. Adds the `Stompable Enemy` panel to the central Properties column, directly above `Damage / Knockback / Hurt Effects`. It is shown only when the selected object is a Stompable Enemy.
2. Exposes all existing enemy controls, including **Walk on tilemap**, **Patrol speed**, **Start walking left**, **Slope climb / descent (px)**, **Hits before enemy dies**, **Drop when defeated** and defeat frame/timer.
3. Explains slope tolerance better: **lower** height means the enemy refuses steeper climbs/descents, **higher** means it can follow steeper terrain. Setting applies per 1-pixel horizontal movement and remains limited to 1–12 px.
4. Horizontal *enemy* knockback now derives direction from the **approach side at the beginning of the frame**, falling back to relative movement if the rectangles were already overlapping. Works both when Kim runs into the enemy and when an enemy runs into Kim. No dependency on sprite-facing flip or end-of-frame centre.
5. Enemy knockback **replaces** residual spring external X force, rather than merely adding to it, to guarantee a push *away* from the collision when a magnitude is configured. Murder Object knockback keeps its original signed/additive semantics. A configured **X=0** still means no horizontal kick.

## Installation (Stage 4.37 must already be installed)

1. Back up your IDE source and platformer project.
2. **IDE ZIP**: extract `GamerGirl-Stage4.37a-IDE-Fix.zip` at the **GamerGirl IDE SOURCE ROOT**, overwriting `gamedesigner.cpp` and `idelibs/codehelpers/game/worldobjects.c`. Rebuild GamerGirl using your normal Fedora build script.
3. **Game Helper ZIP**: extract `GamerGirl-Stage4.37a-Game-Helper-Fix.zip` at the **existing platformer PROJECT ROOT**, overwriting `gamehelpers/gameworldobjects.c`. The `.h` file does not change from Stage 4.37.
4. Open the design and edit a Stompable Enemy. You should now see the `Stompable Enemy` card, including roaming and slope settings.
5. Set `Knock player back on hit`, **Knockback X** to a nonzero *magnitude* (e.g. `8`) and **Knockback Y** to a negative value (e.g. `-7`) in the `Damage / Knockback / Hurt Effects` card. Save Design → Update Game Project → rebuild the platformer.

For enemy knockback, either signed X input is treated as a **strength**, with direction chosen automatically. Murder Objects continue using negative=left/positive=right as before.

## Hardware checklist

- Enemy stops at a wall, reverses and follows ordinary slopes when tilemap patrol is ON; follows spline/stays still when OFF.
- Lower slope climb limit to refuse steeper sections, raise it to traverse them.
- Kim colliding from left gets pushed left; from right gets pushed right.
- Enemy walking into a stationary Kim knocks Kim away from the side it approached.
- Hurt flashing/animation, multi-hit stomps, drop on death and linked actions still behave as before.

## Validation performed in this environment

- Native C tests passed: Stage 4.36 stomp enemy, Stage 4.37 tilemap patrol, new Stage 4.37a approach-based knockback (including fast crossing and moving enemies).
- Prior hazard and breakable native regression tests passed (Stages 3.90, 3.91, 3.92, 3.96 head-butt).
- Stage 4.37 generator/persistence source test passed.
- Static check confirms enemy panel is included in the properties layout.
- **Qt6 development packages are unavailable in this environment, so Fedora Qt6 compilation and SIDBOX hardware testing remain to be performed by you.**
