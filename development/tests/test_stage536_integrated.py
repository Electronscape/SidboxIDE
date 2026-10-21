"""Stage 5.2e/5.3/5.4 source contracts. Qt/ARM still need actual build."""
from pathlib import Path
root=Path(__file__).resolve().parents[2]
load=lambda file:(root/file).read_text()
main=load('mainwindow.cpp')
designer=load('gamedesigner.cpp')
project=load('gamedesigner_project.cpp')
registry=load('gameworldsnapshot.h')
export=load('gamedesigner_export.cpp')
rule=load('idelibs/codehelpers/game/maingame.rulec')
worldrule=load('idelibs/codehelpers/game/gameworlds.rulec')
profile=load('gameplayerprofile.h')
# One manual Update Project/F5 code path; all .sbgm worlds scanned.
assert 'bool MainWindow::updateGameWorldPaths(' in main
assert 'if (!updateGameWorldPaths(targets, true))' in main
assert 'if (!updateGameWorldPaths(worlds, true))' in main
assert 'game->updateAllProjectWorlds = [this]() { return updateAllGameWorlds(); }' in main
assert 'QStringLiteral("*.sbpi")' in main and 'lower == QStringLiteral("sbpi")' in main
assert '2048LL * 1024LL' in main
# Saved world metadata and visible draggable start.
assert 'obj.insert(QStringLiteral("playerStart"), start)' in project
assert 'm_playerStartX = qMax(0,start.value(' in project
assert 'spawn->setFlag(QGraphicsItem::ItemIsMovable,true)' in designer
assert 'spawn->moved=[this]' in designer
assert 'world_api.h' in registry and 'spawnFields.at(i)' in registry
assert 'worlds[]' in worldrule and 'uint8_t gameworlds_player_start' in worldrule
# Shared player never written under worlds/ or free'd by world shutdown.
assert 'players/player.sbpi' in profile
assert 'gamehelpers/gameplayer.c' in main
assert 'gameplayer_shutdown()' in rule and 'gameplayer_init()' in rule
assert rule.index('gameplayer_init()') < rule.index('gameworlds_start("@IDE{WORLD_BASE}")')
assert 'gameplayer_defaults.custom_hitbox' in rule
assert 'gameplayer_defaults.physics_preset' in rule
assert 'GamePlayerProfile::generate' in export
assert 'HAS_SHARED_PLAYER' in export
assert 'QSaveFile out' in profile
assert 'Create / Edit Player...' in designer
for tab in ['Appearance & Animations', 'Hitbox', 'Movement & Physics', 'Initial Stats', 'Inventory']:
    assert tab in designer,tab
assert 'm_playerStartMarker = nullptr;' in designer
assert 'GAMERGIRL_PLAYER_BOB (gameplayer_sprite)' in rule
assert 'GAMERGIRL_PLAYER_BOB.drawx = spawn.x' in rule
assert 'GAMERGIRL_PLAYER_BOB.drawy = spawn.y' in rule
assert 'GAMERGIRL_PLAYER_BOB.flags' in rule
print('Stage 5.2e/5.3/5.4 editor, project and rule source contracts: PASS')
