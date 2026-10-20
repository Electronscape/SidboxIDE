# Stage 3.95a — Qt6 deprecation-warning hotfix

Overwrite only `gamedesigner.cpp` in your IDE's source root, then rebuild in Qt Creator.
The two `QImage::mirrored` warning sites are now `QImage::flipped(Qt::Orientations)`.
No game runtime, export, format or physics changes; no F5 Update Project necessary.

Notes and regression test: `development/notes/STAGE3.95A-QIMAGE-FLIPPED-WARNINGS.md`
and `development/tests/test_stage395a_qimage_flip_deprecation.py`.
