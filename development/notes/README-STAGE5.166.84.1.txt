SIDBOX / CoderGirl IDE Stage 5.166.84.1 (28 October 2026)
HOTFIX: Qt6 compile error in GIVE dropdown socket alignment

ERROR
 gamevisualnodes.cpp:4881: static assertion failed: No Q_OBJECT in the class passed to QObject::findChildren

FIX
 The GIVE redraw pass now searches for QComboBox children (a Q_OBJECT-enabled Qt class),
 then identifies the correct GIVE destination widgets by the already present
 giveRouteBranch dynamic property. The private ConversationTreeCombo subclass
 does not need a Q_OBJECT declaration or moc integration.

INSTALL
 1. Extract this FULL-SOURCE archive over Stage 5.166.84.
 2. Rebuild the IDE and check splash Build: 5.166.84.1.281026.
 3. Open Future Kim's GIVE exchange and verify all five socket centre lines.

No game exporter, game project, dialogue IDs, main.c, or gameplay runtime changes.
Source regression checks passed; Qt desktop compile and visual behaviour need
verification in the user's build environment.
