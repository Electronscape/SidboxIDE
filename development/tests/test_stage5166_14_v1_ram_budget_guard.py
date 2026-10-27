#!/usr/bin/env python3
"""Regression: V1 game budget guard runs after link and before .app creation."""
import re
from pathlib import Path
ROOT=Path(__file__).resolve().parents[2]
s=(ROOT/'mainwindow.cpp').read_text()

# The user-configured game allowance is intentionally not a V1 link-region limit.
link=(ROOT/'idelibs/gaming.ld').read_text()
assert '_requested_app_size' in link
assert '_profile_is_desktop ? _requested_app_size : (_applet_ram_top - _startram)' in link
# The budget guard must run before assembly, objcopy, and compile success.
link_start=s.index('if (m_buildStep == BuildStep::Linking) {')
measurement=s.index('Measure the actual linked RAM span',link_start)
assembly=s.index('appendOutputLine(tr("Generating .asm output..."',measurement)
assert link_start<measurement<assembly
segment=s[measurement:assembly]
for fragment in [
    'game SDRAM', 'measuredRamBytes', 'm_projectType == GameProjectType',
    'used > allowance', 'physicalCeilingKb', 'recommendedKb',
    'QMessageBox::Warning', 'Increase to %1 KB and continue',
    'Keep %1 KB and stop build', 'dialog.clickedButton() != increase',
    'updateProjectLinkerScript(&scriptError)', 'saveProjectFile(m_projectFilePath)',
    'm_appSizeKb = previousKb;',
    'm_buildStep = BuildStep::None;',
    'Cannot measure V1 applet RAM',
    'No new .app will be generated',
    'm_currentBuildIsV2 ? qint64(m_v2HeapKb) * 1024 : 0',
    'R"(^\\s*0x([0-9a-fA-F]+)\\s+(_appstart|__stack_end__)\\s*=)"',
]:
    assert fragment in segment,fragment

# Mimic our map fallback on a small *synthetic* fragment rather than
# relying on the user's platform3 map being present in source distributions.
text='''                0x00000000d0028000                _appstart = ORIGIN (APPLET)
                0x00000000d00822d8                __stack_end__ = .
'''
matches=dict((m.group(2),int(m.group(1),16)) for m in re.finditer(
    r'^\s*0x([0-9a-fA-F]+)\s+(_appstart|__stack_end__)\s*=',text,re.M))
used=matches['__stack_end__']-matches['_appstart']
assert used==369368
# Budget excess: 369,368 > 320*1024. Minimum 361 KiB;
# at least 10% free in a 16 KiB-aligned recommendation => 416 KiB.
min_kb=(used+1023)//1024
headroom_kb=(used*10+(9*1024-1))//(9*1024)
recommended=((headroom_kb+15)//16)*16
assert (min_kb,recommended)==(361,416)
assert 416<=6144-128-160 # game's physical SDRAM reserve, not the project limit
assert used<=416*1024*0.9
for small in [16*1024,320*1024,4096*1024]:
    min_kb=(small+1023)//1024
    headroom_kb=(small*10+(9*1024-1))//(9*1024)
    rec=((headroom_kb+15)//16)*16
    assert rec*1024>=small
assert 'Build: 5.166.14.271026' in (ROOT/'splashscreenwidget.cpp').read_text()
print('PASS Stage 5.166.14 V1 game RAM budget overrun prompts before .app packaging; map fallback + recommended headroom')
