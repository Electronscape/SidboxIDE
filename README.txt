GamerGirl Stage 4.10a — Qt6 toolbar compile hotfix
===============================================

FIXED:
  File: gametilemap.cpp
  Function: SidboxTilemapEditor::setTheme()
  Original reported line: 2235

  Qt6's QObject::findChildren<TilemapFlagButton *>() triggers a compile-time
  static assertion because TilemapFlagButton is a small custom QToolButton
  subclass without the Q_OBJECT macro.

  Instead of adding Q_OBJECT/moc requirements, setTheme now iterates over the
  eight already-stored QToolButton pointers and casts each back to its known
  TilemapFlagButton type. The rest of the toolbar and editor is unchanged.

INSTALLATION — simple hotfix:
  Replace the IDE root gametilemap.cpp with the one in the changed-files
  archive (or the standalone source file) and rebuild.
  No header changes. No other files needed.

  Alternatively use the full Stage4.10a archive and rebuild the IDE.

VALIDATION:
  Source-level regression tests Stage 4.00–4.10a passed.
  Qt6 development SDK is unavailable in this container, so the full native
  Qt compile must be confirmed on Fedora.

NO CHANGES TO:
  Firmware, game engine, collision math, resource format, editor preferences,
  player reference or hitbox overlays.
