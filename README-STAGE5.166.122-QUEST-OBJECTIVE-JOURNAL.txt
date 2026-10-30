CoderGirl IDE - Stage 5.166.122.301026
Quest Journal: description / objectives view, D-pad navigation

HARDWARE TEST FEEDBACK
- User verified on SIDBOX that the two-objective unordered quest DOES complete.
  stopLift was switched ON BEFORE kim[2] pickup, then Dildo[0] collected.
- Both Quest Event signal IDs matched generated game calls: liftoff01 and
  getdildo01. The original test was an event-order / visibility question,
  not a broken quest signal implementation.
- User requested a separate objective list view and exact D-pad semantics.

CHANGES
- Every quest with objectives (ORDERED and ANY ORDER) opens at its description.
- RIGHT: open the selected quest's objective checklist in the entire right pane.
- LEFT in checklist: return to the quest description.
- UP/DOWN: change selected quest and reset to DESCRIPTION and first checklist page.
- Repeated RIGHT within checklist advances to next page (wraps to first page)
  when a quest has more objectives than fit in the panel.
- Each objective is numbered and shows + (done) or - (pending) with live progress
  total: OBJECTIVES X/Y DONE.
- LEFT in description cycles through long description text (wraps at end).
  This preserves description browsing while RIGHT is assigned to the objective view.
- Lists are sized to the actual HUD-constrained journal viewport and skin inset.
- FIRE1 track, FIRE2 close, touch open, and existing quest-list selection stay.
- Quest progress, queued event actions, prereqs, and save/load formats unchanged.
- Existing project .sbgm/.vsgm and assets unchanged. Regenerate all worlds and
  rebuild the game to deploy the new generated runtime.

SOURCE CHANGES
- idelibs/codehelpers/game/adventureruntime.rulec: two-view input/render flow,
  page and reset state, screen-aware layout.
- Stage 122 objective listing bridge (from Stage 121 runtime) retained:
  gameworlds.rulec/h, adventureruntime.ruleh, gameadventure.rulec.
- development/tests/test_stage5166_122_journal_objective_list.py: native
  input/renderer regression for first open, paging, left return, ordered quests,
  state reset, live completion marks and docked HUD.

VALIDATION
- Stage 122 native C renderer test: PASS (-Wall -Wextra -Werror).
- Stage 121 ordered/unordered/save/restore/v3 migration native tests: PASS.
- Stage 121 source-contract suite: 7 PASS.
- Stage 120 Quest Event source-contract suite: 5 PASS.
- Stage 5.166.12 native journal-scroll test: PASS after updating only the old
  hard-coded expected splash version in a temporary test execution.
- Full Qt6 IDE compile and physical SIDBOX .app testing not available here.
  Treat as a source candidate until user tests compiled IDE and runtime.
