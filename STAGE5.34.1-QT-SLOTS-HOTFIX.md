# Stage 5.34.1: Qt `slots` name collision hotfix

**Based on Stage 5.34.** Fixes Qt6 compilation failures in `gameadventureeditor.cpp` near line 575.

## Cause

Qt defines `slots` as a macro for its signal/slot declarations. The new NPC exchange editor used `QComboBox *slots[4]`, so the Qt preprocessor erased the variable name and caused cascading syntax errors.

## Changes

- Rename the local array to `itemSlots` everywhere in `editExchange()`. No functionality, serialization or game runtime changes.
- Splash version is `Build: 5.34.1.221026`.
- Update the existing NPC-exchange regression's version assertion.

## Install

Extract the changed-files archive into the **IDE source directory**, preserving folder paths; overwrite the existing files. Rebuild CoderGirl. No need to change `main.c`, regenerate the game project or edit `.sbgm`.

## Validation

- Checked no Qt-reserved local `slots` variable remains in the modified editor.
- Verified that the C++ macro collision reproduces before the fix and disappears when using `itemSlots`.
- Stage 5.34 generated-C runtime regression passes under host GCC.
- Full Qt6 IDE compilation still needs testing in the user's Fedora environment; the current sandbox does not have Qt6 development headers.
