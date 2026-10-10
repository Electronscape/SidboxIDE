#!/usr/bin/env bash
set -euo pipefail

if [ "$#" -ne 1 ]; then
    echo 'Usage: ./install_cgarm.sh /path/to/SidboxIDE' >&2
    exit 2
fi
root="$(realpath "$1")"
self="$(cd -- "$(dirname -- "$0")" && pwd)"
export CGARM_INSTALL_ROOT="$root"
export CGARM_INSTALL_SOURCE="$self"

python3 - <<'PYTHON'
from pathlib import Path
import os, shutil, re, sys, datetime

root = Path(os.environ['CGARM_INSTALL_ROOT'])
source = Path(os.environ['CGARM_INSTALL_SOURCE'])
ide = root / 'mainwindow.cpp'
api = root / 'idelibs' / 'api'
target = root / 'idelibs' / 'tools' / 'cgarm' / 'libc'
include_dir = root / 'idelibs' / 'tools' / 'cgarm' / 'include'
files = ['gclibc.c', 'gclibc.h', 'cgarm_printf.c', 'cgarm_malloc.c', 'cgarm_memory.c']
if not ide.is_file() or not (api / 'syscalls.c').is_file():
    sys.exit('ERROR: pass the root containing mainwindow.cpp and idelibs/api/syscalls.c')
for name in files:
    if not (source / 'idelibs' / 'tools' / 'cgarm' / 'libc' / name).is_file():
        sys.exit('ERROR: missing package file: ' + name)
ctype_source = source / 'idelibs' / 'tools' / 'cgarm' / 'include' / 'ctype.h'
if not ctype_source.is_file():
    sys.exit('ERROR: missing package file: include/ctype.h')

original = ide.read_text(encoding='utf-8')
# Work on the exact V2-specific registration block, including versions with or without printf.
pattern = re.compile(
    r'        // Stage 5C\'s applet-local PIC allocator and ARM EABI zero helpers\.\n'
    r'        // These do not affect V1, gaming, or the firmware\'s allocator\.\n'
    r'        for \(const QString &relative : \{\n'
    r'(?:(?:\s*QStringLiteral\("v2/v2_(?:pic_malloc|arm_eabi_mem|pic_printf)\.c"\),?\n?)+)'
    r'\s*\}\) \{\n'
    r'            const QString path = apiDir\.filePath\(relative\);\n'
    r'            if \(!QFileInfo::exists\(path\)\) \{\n'
    r'                QMessageBox::warning\(this, tr\("V2 build"\),\n'
    r'                    tr\("Missing V2-compatible runtime source:\\n%1"\)\.arg\(path\)\);\n'
    r'                return;\n'
    r'            \}\n'
    r'            apiSourceFiles\.append\(path\);\n'
    r'        \}',
    re.MULTILINE
)
replacement = """        // CGARM: freestanding PIC-compatible libc; V1 and Gaming remain unchanged.
        const QDir cgarmLibcDir(QDir(libsPath).filePath(QStringLiteral("tools/cgarm/libc")));
        for (const QString &relative : {
                 QStringLiteral("gclibc.c"),
                 QStringLiteral("cgarm_printf.c"),
                 QStringLiteral("cgarm_malloc.c"),
                 QStringLiteral("cgarm_memory.c")}) {
            const QString path = cgarmLibcDir.filePath(relative);
            if (!QFileInfo::exists(path)) {
                QMessageBox::warning(this, tr("CGARM build"),
                    tr("Missing CGARM runtime source:\\n%1").arg(path));
                return;
            }
            apiSourceFiles.append(path);
        }"""

if 'const QDir cgarmLibcDir(' in original:
    modified = original
    print('mainwindow.cpp: CGARM runtime already registered; leaving the code unchanged.')
else:
    modified, count = pattern.subn(lambda m: replacement, original, count=1)
    if count != 1:
        sys.exit('ERROR: Could not safely match the original V2 runtime list in mainwindow.cpp. Nothing changed.')

# Keep the V2 executable format label for compatibility, but call the runtime CGARM.
modified = modified.replace(
    'tr("V2 runtime: PIC SDK sources only; GNU/Newlib libc is NOT linked. "',
    'tr("CGARM runtime: freestanding PIC libc; GNU/Newlib libc is NOT linked. "')

# CGARM ctype.h deliberately overrides Newlib's table-based ctype macros in V2 only.
include_line = '''    if (v2Build) {
        arguments << QStringLiteral("-I")
                  << QDir(libsPath).filePath(QStringLiteral("tools/cgarm/include"));
    }

'''
anchor = '    // Capture compiler-only options before project and SDK inputs or linker'
if 'tools/cgarm/include' not in modified:
    if anchor not in modified:
        sys.exit('ERROR: Could not find V2 compile flags insertion point. Nothing changed.')
    modified = modified.replace(anchor, include_line + anchor, 1)

# Guard against accidentally passing the installed library into user project sources too.
old = '        m_v2CompileSources = sourceFiles;\n        m_v2CompileSources.append(apiSourceFiles);'
new = old + '\n        m_v2CompileSources.removeDuplicates();'
if 'm_v2CompileSources.removeDuplicates();' not in modified:
    if old not in modified:
        sys.exit('ERROR: Could not locate V2 compilation source list. Nothing changed.')
    modified = modified.replace(old, new, 1)

if target.exists():
    existing = [target / name for name in files if (target / name).exists()]
    if existing:
        backup_folder = target.parent / ('libc-backup-' + datetime.datetime.now().strftime('%Y%m%d-%H%M%S'))
        backup_folder.mkdir(parents=True, exist_ok=False)
        for item in existing:
            shutil.copy2(item, backup_folder / item.name)
        print('Existing CGARM files backed up to:', backup_folder)

target.mkdir(parents=True, exist_ok=True)
for name in files:
    shutil.copy2(source / 'idelibs' / 'tools' / 'cgarm' / 'libc' / name, target / name)
    print('Installed:', target / name)
include_dir.mkdir(parents=True, exist_ok=True)
if (include_dir / 'ctype.h').exists():
    backup_header = include_dir / ('ctype.h.before-cgarm-' + datetime.datetime.now().strftime('%Y%m%d-%H%M%S-%f'))
    shutil.copy2(include_dir / 'ctype.h', backup_header)
    print('Previous ctype.h backed up to:', backup_header)
shutil.copy2(ctype_source, include_dir / 'ctype.h')
print('Installed:', include_dir / 'ctype.h')

if modified != original:
    backup = ide.with_name('mainwindow.cpp.before-cgarm-' + datetime.datetime.now().strftime('%Y%m%d-%H%M%S'))
    shutil.copy2(ide, backup)
    ide.write_text(modified, encoding='utf-8')
    print('Patched:', ide)
    print('Backup:', backup)
print('CGARM Phase 1 installed. Rebuild the IDE; then compile a V2 applet.')
print('Old idelibs/api/v2/*.c files remain untouched, but are no longer built automatically.')
PYTHON
