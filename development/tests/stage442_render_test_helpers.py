"""Native C test staging for IDE @IDE{...} templates.

The real renderer is C++/Qt in gamehelpertemplates.h. This helper only
materializes sample rendered C/H for the host-based regression tests.
"""
from pathlib import Path
import re


def render_adventure_runtime(repo_root: Path, destination: Path, items: int = 64,
                             overrides: dict | None = None) -> Path:
    if not 0 <= items <= 64:
        raise ValueError('items must be 0..64')
    origin = repo_root / 'idelibs/codehelpers/game'
    destination.mkdir(parents=True, exist_ok=True)
    values = {
        'MAX_ITEMCOUNT': '64',
        'ITEM_COUNT': str(items),
        'GA_COLS': '54',
        'GA_LINES': '6',
        'DIALOG_X': '20',
        'DIALOG_Y': '148',
        'DIALOG_WIDTH': '440',
        'DIALOG_HEIGHT': '162',
        'TEXT_COLOUR_INDEX': '15',
        'TEXT_OUTLINE_ENABLED': '0',
        'OUTLINE_COLOUR_INDEX': '1',
        'TILE_SIZE': '8',
        'FRAMES_PER_CHAR': '2',
    }
    if overrides:
        invalid = set(overrides) - set(values)
        if invalid:
            raise ValueError(f'Unknown override(s): {sorted(invalid)}')
        values.update({key: str(value) for key, value in overrides.items()})
    for ext, rule in (('.c', '.rulec'), ('.h', '.ruleh')):
        contents = (origin / ('adventureruntime' + rule)).read_text()
        def substitute(match):
            name = match.group(1)
            if name not in values:
                raise ValueError(f'Unknown @IDE{{{name}}} in adventure runtime{ext}')
            return values[name]
        contents = re.sub(r'@IDE\{([^{}]*)\}', substitute, contents)
        if '@IDE{' in contents:
            raise ValueError(f'Unresolved placeholder in runtime{ext}')
        (destination / ('adventureruntime' + ext)).write_text(contents)
    return destination
