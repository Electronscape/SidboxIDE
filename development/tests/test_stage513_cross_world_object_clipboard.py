#!/usr/bin/env python3
"""Stage 5.13 source contracts. Does NOT compile Qt or execute GUI paste."""
from pathlib import Path
r=Path(__file__).resolve().parents[2]
cpp=(r/'gamedesigner.cpp').read_text()
h=(r/'gamedesigner.h').read_text()
project=(r/'gamedesigner_project.cpp').read_text()
for s in (
    'static Resource s_copiedWorldObject;',
    'static QVector<Resource> s_copiedWorldResources;',
    'static QVector<SplinePath> s_copiedWorldSplines;',
    'static QString s_copiedWorldSource;',
    'void copySelectedSprite(int resourceIndex = -1);',
    'm_undoResourceSplines', 'm_redoResourceSplines',
): assert s in h,s
for s in (
    'menu.addAction(tr("Copy Game Object"))',
    'menu.addAction(tr("Paste Game Object"))',
    'copySelectedSprite(resourceIndex);',
    's_copiedWorldResources = m_resources;',
    's_copiedWorldSplines = m_splinePaths;',
    'QFileInfo(s_copiedWorldSource).absolutePath()',
    'QFileInfo(m_filePath).absolutePath()',
    'const QString absolute = sourceFile(original->path);',
    'r.animationFile = storedPath(sourceFile(r.animationFile));',
    's_copiedWorldObject.id, copy.id',
    '&Resource::sfxSpring', '&Resource::sfxBreakHit',
    '&Resource::sfxHazardAmbient',
    'r.targetObjectId = importById(r.targetObjectId);',
    'r.breakDropCollectableId = importById(r.breakDropCollectableId);',
    'r.triggerMusicId = importById(r.triggerMusicId);',
    'r.objectSplineId = splineRemap.value(oldId);',
    'm_splinePaths.append(cloned);',
    'point += QPoint(deltaX, deltaY);',
    'copy.x = qBound(0, qRound(centre.x()), right);',
    'm_undoResourceSplines.takeLast();',
    'm_redoResourceSplines.takeLast();',
    'if (assetFilesChanged) assetFilesChanged();',
): assert s in cpp,s
assert 'm_hasCopiedSprite' not in cpp+project+h
assert 'm_copiedSprite' not in cpp+project+h
assert 'for (int dependencyIndex = importedBegin; dependencyIndex < m_resources.size(); ++dependencyIndex)' in cpp
assert 'QFileInfo::isFile(' not in cpp
assert 'QString Resource::* soundFields[]' in cpp
assert 'QFileInfo(implicit).isFile()' in cpp
assert 'sourceDir.relativeFilePath(implicit)' in cpp
assert 'm_undoResourceSplines.clear();' in project
print('PASS Stage 5.13 source checks: shared clipboard, ID remapping, asset rebasing, spline/undo, GUI actions')
