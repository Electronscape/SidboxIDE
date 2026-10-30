Stage 5.166.126.301026 (30 October 2026)
Visual Nodes: distinguish persistent STATE conditions from event PULSES

WHAT CHANGED
- A small legend above the visible node tree: teal = held STATE, gold = EVENT pulse.
- Stompable Enemy: STATE: ALIVE/ACTIVE (teal), EVENT: ON DEFEAT and
  EVENT: ON HIT (gold), with separate, specific hover explanations.
- Other ordinary Game Objects: STATE: ACTIVE (teal); named event outputs
  now carry EVENT: prefixes. Trigger: EVENT: ON ACTIVATE, and remembered
  STATE: ON / STATE: OFF under the Trigger settings.
- Logic input labels, socket fill and hover text distinguish EVENT, STATE,
  and connected LOGIC RESULT inputs. Right-click wire editing unchanged.
- Selecting a logic card now shows contextual guidance in the inspector.
  NOT(EVENT) gets an amber border and a caution explaining that it does
  not mean the opposite persistent state. Connecting EVENT + STATE to AND
  shows the event-gated meaning (including ON HIT + STATE: ALIVE).
- A state-only TRUE branch can run again on subsequent reevaluation. This
  is documented in port hover text and technical notes. No runtime
  dispatch or save-format changes have been made.

YOUR HARDWARE-VERIFIED GRAPH
  baguy[0] / ON DEFEAT -> BOOLEAN TRUE -> death dialogue #18
  baguy[0] / ON HIT     -> AND INPUT 1
  baguy[0] / STATE: ALIVE -> AND INPUT 2
  AND TRUE -> nonlethal-hit dialogue #23

Because ON HIT includes the lethal hit and ALIVE becomes false on death,
AND avoids playing #23 on the killing blow. The event/held-state distinction
now appears directly on the graph and in the inspector.

CHANGED FILES
  gamevisualnodes.cpp                    - UI only
  splashscreenwidget.cpp                 - Build 5.166.126.301026
  README.md, this file                   - release documentation
  development/tests/test_stage5166_126_state_event_socket_guidance.py
  development/tests/test_stage5166_125_enemy_hit.py          - version assertion modernized
  development/tests/test_stage5166_123_flow_virtual_actions.py - version assertion modernized

VALIDATION
  Qt6 SDK unavailable in this container. The native C and source regressions
  were run, and source patterns were scanned. Desktop Qt6 compilation and
  visual acceptance are still needed; no claims of a full Qt build.

No gameplay logic, export data, .sbgm, .vsgm, game files or runtime changed.
