STAGE 5.166.116.1 (30 October 2026) - Qt compile hotfix

Reported Fedora build error:
  gamevisualnodes.cpp:7140: no matching function for
  VisualNodesDialog::lookupGraph(const QString&, QString*)

Cause:
  The Stage 116 event-to-existing-logic connection branch called lookupGraph
  with two arguments. The declared member function requires at least three:
    lookupGraph(const QString &key, QString *owner, int *index,
                QJsonObject *found = nullptr)

Fix:
  Pass nullptr for the unused index parameter:
    lookupGraph(to, &graphOwner, nullptr)

No runtime or project changes. No graph semantics or save format changes.
Stage 116 breakable dialogue/event features are retained unchanged.

Validation:
  - Verified updated call matches the declared function signature.
  - Stage 116 breakable dialogue picker regression test.
  - Additional focused compile-time stub test of the three-argument call.
  - Qt full IDE build unavailable here; Fedora compilation required.
