"""Stage 5.149: all spawners must render independently of selection.
Qt graphics cannot be executed on headless build hosts without Qt dev libs,
so verify the complete source data flow as well as the native runtime guards.
"""
from pathlib import Path
import re
root=Path(__file__).resolve().parents[1]
cpp=(root/'gamedesigner.cpp').read_text()
h=(root/'gamedesigner.h').read_text()
splash=(root/'splashscreenwidget.cpp').read_text()
main_preview=cpp.split('void SidboxGameDesigner::updateParticlePreview()')[1].split('void SidboxGameDesigner::rebuildScene()')[0]
reset=cpp.split('void SidboxGameDesigner::resetParticlePreview()')[1].split('void SidboxGameDesigner::setParticlePreviewDraft')[0]
clear_draft=cpp.split('void SidboxGameDesigner::clearParticlePreviewDraft()')[1].split('void SidboxGameDesigner::updateParticlePreview()')[0]

assert 'm_showParticlePreview->setChecked(true)' in cpp
assert 'Animate ALL placed Particle Spawners together' in cpp
assert 'm_objectPreviewTimer->setInterval(20)' in cpp
assert 'for (int index = 0; index < m_resources.size(); ++index)' in main_preview
assert 'selectedIndex()' not in main_preview
assert 'r.objectType != QStringLiteral("particle_emitter")' in main_preview
assert 'm_particlePreviewDraftIndex == index' in main_preview
assert 'QVector<ParticlePreviewEmitter> m_particlePreviewEmitters;' in h
assert 'QVector<ParticlePreviewParticle> particles;' in h
assert 'm_particlePreviewEmitters.append(created);' in main_preview
assert 'created.particles.resize(32);' in main_preview
assert 'created.items.append(item);' in main_preview
assert 'ParticlePreviewEmitter &emitter = m_particlePreviewEmitters[emitterPos];' in main_preview
assert '++emitter.step' in main_preview
assert 'emitter.random' in main_preview
assert 'emitter.particles[i]' in main_preview
assert 'emitter.items[i]' in main_preview
assert 'const int limit = qBound(1, r.particleCount, 32)' in main_preview
assert 'particle.x100 += r.particleWind + gust' in main_preview
assert 'particle.vy100 = qMin(1200, particle.vy100 + r.particleGravity)' in main_preview
assert 'particle.overPlayer = !r.drawBehindTiles && r.particlePlayerLayerMix' in main_preview
assert 'item->setZValue(r.drawBehindTiles ? 1.95 :' in main_preview
assert 'discardEmitter(i)' in main_preview and 'm_particlePreviewEmitters.removeAt(pos);' in main_preview
assert 'm_particlePreviewEmitters.clear();' in reset
assert 'm_particlePreviewEmitters.removeAt(i);' in clear_draft
assert 'resetParticlePreview()' not in clear_draft
assert 'updateParticlePreview();' in clear_draft
assert 'm_particlePreviewEmitters.clear(); // Scene owns and deletes every preview sprite.' in cpp
assert 'QTimer particleDialogPreviewTimer(&dialog)' in cpp
assert 'new QGraphicsView(m_scene, particlePreviewDock)' in cpp
assert 'Build: 5.158.261026' in splash
print('Stage 5.149: per-emitter simulation, selection-independent preview, draft isolation, cleanup, splash version PASS')
