SIDBOX CoderGirl IDE Stage 5.166.76 (28 October 2026)

Conversation Flow editing:
- Expanded @conversation cards now edit speaker, dialogue text, three answers and next-dialogue numeric destinations.
- Read/write directly via adventure.nodes in the current world .sbgm. IDs and advanced answer fields remain intact.
- Existing item-required alternate paths remain visible and are edited in Adventure Editor.
- The "Open this dialogue in Adventure Editor..." button saves pending graph/world changes then opens the Adventure Editor on the exact dialogue ID.
- Collapsed layout/positions persist in the same .vsgm; no game runtime or user main.c changes.

Install: extract this full source archive over Stage 5.166.75.1, rebuild the IDE,
check splash version 5.166.76.281026, and open a conversation flow.
Test: change text + an answer route, Save Graph + World, reopen, verify route,
then use the Adventure button and verify the correct dialogue is selected.

IMPORTANT: Qt desktop compile and interactive/hardware behaviour have not been verified here.
