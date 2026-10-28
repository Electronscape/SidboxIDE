#!/usr/bin/env python3
"""Read-only V1 .app and generated embedded-tilemap footprint summary.

Usage: python development/tools/audit_v1_project_size.py /path/to/game
This is a DATA inventory, not a linker map; --gc-sections can discard arrays.
"""
import argparse
import re
from pathlib import Path

ARRAY_RE = re.compile(
    r'\bconst\s+(uint8_t|uint16_t)\s+game_([A-Za-z_][A-Za-z_0-9]*)_'
    r'(graphics|collisions|flips|shape_refs)\[\]'
    r'\s*(?:__attribute__\s*\(\(\s*aligned\(\d+\)\s*\)\))?\s*=\s*\{([^}]*)\}',
    re.S,
)
NUM_RE = re.compile(r'(?<![\w])(?:0x[0-9A-Fa-f]+|\d+)(?![\w])')

def summary(root):
    result = []
    print(f'Project: {root}')
    apps = sorted(root.glob('*.app'))
    for app in apps:
        print(f'Applet: {app.name} = {app.stat().st_size:,} bytes ({app.stat().st_size/1024:.1f} KiB)')
    if not apps:
        print('Applet: none in this project folder')
    print('Embedded tilemap arrays (raw array bytes, not proven .app contribution):')
    for path in sorted(root.glob('worlds/*/gamelevels/*.c')):
        world = path.parents[1].name
        found = {}
        for m in ARRAY_RE.finditer(path.read_text(errors='replace')):
            type_name, symbol_world, kind, initializer = m.groups()
            if symbol_world != world: continue
            count = len(NUM_RE.findall(initializer))
            found[kind] = count * (2 if type_name == 'uint16_t' else 1)
        if found:
            total = sum(found.values())
            result.append((world,total))
            print(f'  {world}: {total:,} bytes = ' + ', '.join(f'{k} {v:,}' for k,v in sorted(found.items())))
    print(f'  TOTAL: {sum(n for _,n in result):,} bytes ({sum(n for _,n in result)/1024:.1f} KiB)')
    print('Note: static arrays may be garbage-collected by the linker. '
          'Use the V1 linker .map and a before/after .app build for exact savings.')

if __name__ == '__main__':
    p=argparse.ArgumentParser(description=__doc__)
    p.add_argument('project',type=Path)
    args=p.parse_args()
    if not args.project.is_dir(): p.error('Project directory does not exist')
    summary(args.project)
