#!/usr/bin/env bash
# Optional reproducibility build for Stage 18. Does not touch IDE or firmware.
# Usage: bash source/rebuild-on-fedora.sh /path/cgarm-ld /path/sidbox-v2-packer /path/cgarm-v2-compare
set -euo pipefail
if (($# != 3)); then
  printf 'Usage: %s /path/cgarm-ld /path/sidbox-v2-packer /path/cgarm-v2-compare\n' "$0" >&2
  exit 2
fi
CGARM=$(realpath "$1")
PACKER=$(realpath "$2")
COMPARE=$(realpath "$3")
for tool in "$CGARM" "$PACKER" "$COMPARE"; do
  test -x "$tool" || { echo "Not executable: $tool" >&2; exit 2; }
done
command -v clang >/dev/null
command -v ld.lld >/dev/null
command -v cc >/dev/null
ROOT=$(cd "$(dirname "$0")/.." && pwd)
BUILD=$(mktemp -d "${TMPDIR:-/tmp}/cgarm-stage18.XXXXXXXX")
printf 'Rebuilding into %s (will NOT overwrite package)\n' "$BUILD"
cd "$BUILD"
clang --target=arm-none-eabi -mcpu=cortex-m7 -mthumb -c "$ROOT/source/stage18_probe.S" -o stage18_probe.o
"$CGARM" --emit-elf stage18-cgarm.elf --emit-map stage18-cgarm.cgmap --heap-kb 16 --stack-kb 8 --app-kb 64 stage18_probe.o >cgarm-link.log
ld.lld -flavor gnu -m armelf -pie --gc-sections -Bsymbolic -T "$ROOT/source/gui_v2.ld" --Map=stage18-llvm.map -o stage18-llvm.elf stage18_probe.o >llvm-link.log
"$PACKER" stage18-cgarm.elf stage18-cgarm.app --heap 16384 --stack 8192
"$PACKER" stage18-llvm.elf stage18-llvm.app --heap 16384 --stack 8192
"$COMPARE" stage18-cgarm.elf stage18-cgarm.app stage18-llvm.elf stage18-llvm.app \
  --cg-map stage18-cgarm.cgmap --llvm-map stage18-llvm.map \
  --objects stage18_probe.o --min-matched 1 --strict-live --max-ram-kb 64 > stage18-strict-live.log
cc -std=c11 -O2 -Wall -Wextra -Werror -I "$ROOT/host-test" "$ROOT/host-test/stage18_host_loader_test.c" -o stage18-host-loader-test
./stage18-host-loader-test stage18-cgarm.app stage18-llvm.app | tee stage18-host-loader.log
printf '\nStage 18 strict-live and firmware-format host tests passed.\nRebuilt files: %s\n' "$BUILD"
sha256sum stage18-cgarm.app stage18-llvm.app
printf 'These are for controlled/manual tests only, not production apps.\n'
