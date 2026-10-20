"""Stage 4.13 editor polish and user-replaceable icon regression checks."""
from pathlib import Path
p = Path(__file__).resolve().parents[2]
tile=(p/'gametilemap.cpp').read_text()
world=(p/'gamedesigner.cpp').read_text()
anim=(p/'gameanimationeditor.cpp').read_text()
common=(p/'ideglobaltheme.h').read_text()
main=(p/'mainwindow.cpp').read_text()
icons=(p/'gameeditoricons.h').read_text()
cmake=(p/'CMakeLists.txt').read_text()
assert 'markerFont.setWeight(QFont::DemiBold)' in tile
assert 'dest.width() < 12 ? 1.0 : 1.6' in tile
assert 'cell.width() < 12 ? 1.0 : 1.6' in tile
assert 'tagFont.setWeight(QFont::Black)' in world
assert 'objectName->setSizePolicy(QSizePolicy::Maximum' in world
assert 'objectHeading->addWidget(nextObject);\n    objectHeading->addStretch(1);' in world
assert 'objectHeading->addWidget(objectName, 1);' not in world
assert 'gameEditorIconOverride' in icons
assert 'QCoreApplication::applicationDirPath()' in icons
assert 'gameEditorExternalIcon(filenames.at(int(glyph)))' in tile
assert 'gameEditorExternalIcon(right' in world
assert 'gameEditorIcon(fileName)' in world
assert 'gameEditorIcon("compile.png")' in main
assert 'image:url("@tick")' in common
assert 'ideCheckedBoxImageUrl(theme)' in common
assert 'setStyleSheet(QString());' in world
assert 'global theme controls' in anim
assert 'qApp->setStyleSheet(ideGlobalControlStyle(m_theme))' in main
assert (p/'icons/checkbox_tick.png').is_file()
assert 'icons/checkbox_tick.png' in cmake
assert 'm_paletteZeroBackground = QColor::fromRgb(palette.at(0))' in anim
assert 'm_previewBackgroundChoice->addItem(tr("Palette 0"), 0)' in anim
assert 'm_previewBackgroundChoice->addItem(tr("Custom"), 2)' in anim
assert 'QColorDialog::getColor(' in anim
assert 'preview.fill(background)' in anim
assert 'PlayerAnimation/previewBackgroundMode' in anim
assert 'PlayerAnimation/previewBackgroundColour' in anim
print('PASS Stage 4.13: contrast, arrows, external icons, checked ticks, preview backgrounds')
