CoderGirl IDE Build 5.131.7.311026
Fix: Unrelated Visual Logic dialogue replay when Health or Quest status changes

APPLY THIS PATCH TO THE WORKING BUILD 5.131.6 SOURCE.
Replace ONLY the two files included in this ZIP, at IDE source root:
  gamedesigner_export.cpp
  splashscreenwidget.cpp

Authoritative user case: Archive.tar(20261031-012737).gz
World1 Game Object: stopLift
 - logic1: AND(lifty.active, doormanSteve.active) -> Adventure dialogue #15
 - logic2: COMPARE(Health > 50) WHEN stopLift ON ACTIVATE -> dialogue #22

Previously, a Health revision evaluated and DISPATCHED every node belonging to
stopLift, including unrelated logic1 whose TRUE state remained held. Hazard
spikey[0..2] therefore replayed dialogue #15 without a new Trigger event.

Exporter fix:
 - Separate ordinary owner/event activation from stat/quest revision watches.
 - Continue computing every graph expression together before actions run.
 - Dispatch a node on an independent stat or quest change ONLY if that node
   itself watches the changed condition or consumes a dependent logic node.
 - Keep existing normal Trigger/event and event-pulse guards unchanged.
 - Do not change .sbgm/.vsgm formats, generated main.c, or quest/save data.

Test guidance:
 1. Rebuild IDE, regenerate World1, build the game .app.
 2. Ensure lifty and doormanSteve are active; touch a spike: health should
    decrease, but dialogue #15 must NOT play from an unrelated health change.
 3. Activate stopLift: its original logic1 and logic2 branches may still run
    as authored. If Health > 50, logic2 may display dialogue #22.
 4. Hit or defeat baguy[0], verify its ON HIT/ON DEFEAT event dialogues.
 5. Check compare->AND dependent wiring and quest completion conditions.

Verification done in this container:
 - Matched actual .sbgm dialogue refs, graph nodes, and generated World1
   actions (24 is dialogue #15).
 - Native GCC -Werror test of intended per-node watch behavior passed.
 - Existing generated world1/gameworlditems.c syntax passed native GCC.
 - Inspected exporter C++ changes for known Qt keyword/lambda hazards.

Limitations: Complete Qt6 build unavailable here (Qt6 SDK not installed),
and regenerated ARM game .app and real SIDBOX hardware still need user tests.
