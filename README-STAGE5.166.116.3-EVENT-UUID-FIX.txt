SIDBOX IDE Stage 5.166.116.3 (30 Oct 2026)
Breakable event-UUID resolution fix

Symptom: Game World Object Generation refuses a valid Breakable ON DESTROY -> AND graph with:
  Logic node logic1 reads a missing event @event:destroy:<uuid>.

Fix:
- gamevisualgraphlogic.h: graph ordering now recognises an event by its REAL
  owning Game Object UUID, rather than requiring a synthetic @event:* key
  in the set of valid object identities. Missing source objects are still
  rejected. Event kind/owner checks in the exporter remain in place.
- No changes to graph storage, node wires, exporter runtime pulse logic or
  saved game format.
- splashscreenwidget.cpp: Stage 5.166.116.3.301026.

Install:
1. Prefer the FULL ZIP, unpack into a clean IDE source directory.
2. CMake configure/build and verify the updated splash number.
3. Open your existing world and Update World Objects. Do NOT delete or redraw
   the existing bonkCollect -> AND connections.

Tested:
- 22 focused/related regression tests pass, including a case with the event
  referring to a real UUID but no separate synthetic event registration.
- Full Qt compilation and hardware testing unavailable in this environment.

If this exact error persists even with the complete new build, the latest
world1.sbgm is needed to check whether the graph contains an OUTDATED UUID
(the screenshot's UUID matches the earlier uploaded world archive).
