from pathlib import Path
root=Path(__file__).resolve().parents[1]
cpp=(root/'gamedesigner.cpp').read_text()
h=(root/'gamedesigner.h').read_text()
assert 'm_showParticlePreview = new QCheckBox(tr("Particles")' in cpp
assert 'm_showParticlePreview->setChecked(true)' in cpp
assert 'm_objectPreviewTimer->setInterval(20)' in cpp
assert 'updateParticlePreview();\n        updateWeatherPreview();\n        for (int i = 0;' in cpp
assert 'void SidboxGameDesigner::updateParticlePreview()' in cpp
assert 'void SidboxGameDesigner::resetParticlePreview()' in cpp
assert 'm_scene->addItem(item);' in cpp
assert 'm_particlePreviewItems.resize' not in cpp
assert 'created.particles.resize(32);' in cpp
assert 'particle.fade' in cpp and 'particle.vy100' in cpp
assert 'const int limit = qBound(1, r.particleCount, 32)' in cpp
assert 'particle.x100 += r.particleWind + gust' in cpp
assert 'particle.overPlayer = !r.drawBehindTiles && r.particlePlayerLayerMix' in cpp
assert 'm_particlePreviewEmitters.clear(); // Scene owns and deletes every preview sprite.' in cpp
assert 'const auto updateParticleDraft =' in cpp
for field in ('particleAreaW','particleAreaH','particleCount','particleInterval',
              'particleLifetime','particleWind','particleFall','particleGravity',
              'particleFlutter','particlePlayerLayerMix','particleFadeEnabled',
              'particleFadeIn','particleFadeOut','particleFadeSpeed'):
    assert 'draft.'+field+' =' in cpp, field
assert 'QTimer particleDialogPreviewTimer(&dialog)' in cpp
assert 'ParticleWorldPreviewDock' in cpp and 'ParticleWorldPreviewCanvas' in cpp
assert 'new QGraphicsView(m_scene, particlePreviewDock)' in cpp
assert 'particlePreviewCanvas->fitInView(particlePreviewLastBounds, Qt::KeepAspectRatio)' in cpp
assert 'particlePreviewNeedsFit = false' in cpp
assert 'particleDialogPreviewTimer.start()' in cpp
assert 'clearParticlePreviewDraft();' in cpp
assert 'QVector<ParticlePreviewParticle> particles;' in h
assert 'm_particlePreviewDraftActive = false;' in h
assert 'Build: 5.159.261026' in (root/'splashscreenwidget.cpp').read_text()
# The runtime is not patched for an IDE preview; world data remain unchanged.
assert (root/'idelibs/codehelpers/game/gameworlditems.rulec').exists()
print('Stage 5.148 source checks: canvas-only 50 Hz preview, 32 pool, live modal draft, cleanup, fade and layer settings passed')
