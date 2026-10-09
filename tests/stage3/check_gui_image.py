#!/usr/bin/env python3
"""Additional GUI image checks: PIC pointers, button window demo metadata."""
import pathlib
import struct
import sys
raw = pathlib.Path(sys.argv[1]).read_bytes()
h = struct.unpack_from('<8s14I', raw)
assert h[0] == b'SBAPV2\x00\x00', h[0]
assert h[4] <= 256*1024 and h[5] <= 512*1024
assert h[9] >= 1, 'Expected at least one callback pointer relocation'
assert h[11] == 16384, 'Expected a 16 KB heap reservation'
assert b'V2 GUI BUTTON WORKS!' in raw, 'Label text not found in image'
assert b'CLICK ME!' in raw, 'Button text not found in image'
print('PASS: V2 GUI image has button, label, callback relocation and bounded heap reserve')
