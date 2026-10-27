#!/usr/bin/env python3
"""Stage 5.164.5 local save-location and legacy recovery regression."""
from pathlib import Path
import subprocess
ROOT=Path(__file__).resolve().parents[2]
text=(ROOT/'idelibs/codehelpers/game/gameworlds.rulec').read_text()
assert 'snprintf(path,40,"%06lX%1u%c.SAV"' in text
assert 'snprintf(path,40,"/CGSAVES/%06lX%1u%c.SAV"' in text
assert "gw_save_read_bank(slot,'A',legacy" in text
assert "gw_save_read_bank(slot,'B',legacy" in text
assert '(void)sfmkdir("/CGSAVES")' not in text
assert 'Build: 5.166.12.271026' in (ROOT/'splashscreenwidget.cpp').read_text()
subprocess.run(['python3',str(ROOT/'development/tests/test_stage5164_save_load.py')],check=True)
print('PASS Stage 5.164.5: current TFCard working directory and old /CGSAVES fallback')
