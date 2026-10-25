# SIDBOX CoderGirl Stage 5.104 - Expandable Touch / Button Trigger cards

Build: 5.104.251026

## New in the Logic Flow Chart

Each Touch / button trigger card has a small [+] at the upper right.
Click [+] to expand the card and see its actual saved Trigger configuration:
- activation type (touch, touch + FIRE2, or inventory USE via FIRE2)
- one-shot / repeatable mode, and inventory consumption
- every linked-object Enable / Disable / Toggle action, in list order
- named target objects instead of opaque IDs (and missing-target warnings)
- success and wrong-item dialogues, rewards, stats, music, and sound events

Click [-] to collapse the card. The closed card shows a detail count.
Expanders also work for Trigger mini cards in manual and automatic array
Flow groups, including nested arrays. A group's container grows to fit the
expanded card. When the Flow Chart is laid out automatically, successive
cards move down to give expanded cards room. With manual card positions, cards
stay wherever you placed them, so move them if two expanded cards overlap.

Expanded states and positions are written ONLY to `.sidbox-flow-layout.json`,
not to the game `.sbgm`. The generated game and running code are unchanged.
The relationship wires still point at exactly the same nodes and are
recomputed when cards change size.

## Installing

Extract the drop-in ZIP over a backed-up Stage 5.103.1 IDE source tree:

- `gamefloweditor.cpp`
- `splashscreenwidget.cpp`
- `development/tests/test_stage5104_trigger_flow_expanders.py`
- `development/tests/test_stage5103_trigger_action_list.py` (version assertion only)

Rebuild the Qt6 IDE, then open Logic Flow. No Update Game Project and no
SIDBOX firmware flash are required. **main.c is not modified.**

## Verification

- Stage 5.104 static UI wiring checks: PASS
- Stage 5.103 linked-action generator/native C regression: PASS
- Package integrity: PASS
- Qt6 desktop compile and live Flow Chart interaction: require Fedora test

The pre-existing Stage 5.554 and 5.556 tests encode old assumptions about
flow source text / old splash versions. They are not usable as modern tests.
