"""Stage 3.97 persistent settings and editor wiring (Qt6 build still required)."""
from pathlib import Path
r=Path(__file__).resolve().parents[2]
t=lambda f:(r/f).read_text()
model=t('gamedesigner.h'); project=t('gamedesigner_project.cpp'); editor=t('gamedesigner.cpp'); exp=t('gamedesigner_export.cpp'); main=t('mainwindow.cpp')
for field in ('breakRewardImpulse','breakRewardVx','breakRewardVy'):
    assert field in model
    assert f'QStringLiteral("{field}")' in project
    assert f'r.{field} =' in editor
assert 'Launch reward when block breaks' in editor
assert 'Reward X speed' in editor and 'Reward Y speed' in editor
assert 'Hidden until activated / spawned' in editor
assert '!hiddenCollectable->isChecked()' in editor
assert 'droppingPickups.contains(ix)' in exp
assert 'r.objectInitiallyActive ? "1" : "0"' in exp
assert 'block.breakRewardImpulse ? block.breakRewardVx * 100 : 0' in exp
assert 'block.breakRewardImpulse ? block.breakRewardVy * 100 : 0' in exp
assert 'cg_reward_x100' in exp and 'cg_reward_vx100' in exp
assert 'itemDoubleClicked, this, &MainWindow::openProjectFile' in main
assert 'itemActivated, this, &MainWindow::openProjectFile' not in main
assert 'openTreeItemAction->setShortcuts' in main
assert 'const qint64 largeSourceThreshold = 2048LL * 1024LL;' in main
print('PASS: launch UI + persist + export; linked-hidden rewards; PPB single open / Enter')
