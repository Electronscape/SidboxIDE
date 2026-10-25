# Stage 5.93 — Optional sounds for item-targeted Triggers

Use **Game Designer → Game Object Properties → Switch & Trigger** on a Trigger that has **Interact with inventory item** configured. Three optional Sound resource selectors appear:

- **Wrong inventory item — sound:** plays when the player tries any item other than the required one.
- **Successful USE — sound:** plays once when the correct item activates the linked action (whether or not the item is consumed, including one-shot Triggers).
- **Cancel USE — sound:** plays when FIRE2 backs out of the targeted inventory selector without using an item.

Each selector defaults to **None** and can be assigned independently. The existing Sound assets and assigned SIDBOX channels, volume and panning are reused. `Audio / Range & Fade` can set an optional range; range 0 retains the Sound resource's chosen volume and pan rather than applying distance attenuation.

For example, Steve the Doorman could have a `wrong.wav` when offered an unrelated item, `unlock.wav` when offered the correct item, and `back.wav` when the inventory selector is cancelled. These names are examples only; **no specific files or game logic are hardcoded.**

## Integration

The three Sound resources are stored by **stable resource ID** in the world's `.sbgm` file. They are validated during export and included in the generated world's sound wrappers. A small event callback is added to the generic Adventure runtime to report FIRE2 cancellation; the world Trigger runtime plays the matching sound for wrong/success/cancel. No additional sound mixer, engine or edits to a user-owned `main.c` are required.

**Installation:** Copy the source and `idelibs/codehelpers/game/` files from the ZIP over the corresponding IDE project paths. Rebuild CoderGirl, set the Trigger's sound events in the Game Object Properties, save the world and choose **Update Game Project** to regenerate the world/runtime. Rebuild your game before testing on SIDBOX. Existing triggers with no sound configured remain silent.

## Compatibility and test status

- General CoderGirl rules, usable in any project with Adventure inventory and Trigger objects.
- Ordinary triggers with no required item are unchanged.
- Wrong items never activate the Trigger or consume an item.
- Success SFX plays before the one-shot target is cleared.
- Cancel SFX plays when FIRE2 closes the item-selection modal, not when opening or closing ordinary inventory.
- Native GCC test passes for wrong, success, cancel, per-object sound selection and one-shot actions.
- Native GCC test passes for the Adventure FIRE2 cancellation callback and reset on world load.
- **Qt6 build and real SIDBOX hardware/audio playback not performed in this environment**; test on Fedora and hardware.

Files changed: `gamedesigner.h`, `gamedesigner.cpp`, `gamedesigner_project.cpp`, `gamedesigner_export.cpp`, `gamefloweditor.cpp`, `splashscreenwidget.cpp`, `idelibs/codehelpers/game/adventureruntime.rulec`, `adventureruntime.ruleh`, `gameadventure.rulec`, `gameworlditems.rulec`, `gameworlditems.ruleh`.

Splash build: `5.93.241026`.
