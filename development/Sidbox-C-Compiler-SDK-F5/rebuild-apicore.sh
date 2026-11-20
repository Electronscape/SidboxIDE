#!/usr/bin/env bash
set -euo pipefail

# Run from the compiler project root (the directory containing compiler/).
# Usage: ./rebuild-apicore.sh /path/to/SidboxIDE/idelibs
project=$(cd -- "$(dirname -- "$0")" && pwd)
requested=${1:-${SIDBOX_SDK:-}}
if [[ -z "$requested" || ! -d "$requested" ]]; then
    printf '%s\n' 'Pass the path to your SidboxIDE folder or its idelibs directory.' >&2
    exit 1
fi
sdk=$(cd -- "$requested" && pwd)
if [[ -f "$sdk/idelibs/api/apis.h" ]]; then
    sdk="$sdk/idelibs"
fi
arm_gcc="$sdk/tools/bin/arm-none-eabi-gcc"
arm_objcopy="${ARM_OBJCOPY:-$sdk/tools/bin/arm-none-eabi-objcopy}"
if [[ ! -f "$sdk/api/apis.h" ]]; then
    printf 'Expected SDK header %s/api/apis.h\n' "$sdk" >&2
    printf '%s\n' 'Pass the SidboxIDE folder containing idelibs, or pass idelibs itself.' >&2
    exit 1
fi
if [[ ! -x "$arm_objcopy" && -z "${ARM_OBJCOPY:-}" ]]; then
    arm_objcopy=$(command -v arm-none-eabi-objcopy || true)
fi
if [[ ! -x "$arm_gcc" || ! -x "$arm_objcopy" ]]; then
    printf 'Expected executable tools at %s and %s\n' "$arm_gcc" \
        "${arm_objcopy:-arm-none-eabi-objcopy}" >&2
    exit 1
fi

output="$project/compiler"
if [[ ! -f "$output/export_apicore.c" || ! -f "$output/apicore.h" ]]; then
    printf '%s\n' 'Run this script from the root of the updated compiler project.' >&2
    exit 1
fi
work=$(mktemp -d "$output/.apicore-build.XXXXXXXX")
trap 'rm -rf -- "$work"' EXIT

"$arm_gcc" -mcpu=cortex-m7 -mthumb -mfpu=fpv5-d16 -mfloat-abi=hard \
    -std=gnu99 -fshort-enums --specs=nano.specs -ffreestanding -DSIDBOX_APPLET_V2 \
    -I"$sdk/api" -I"$sdk/tools/cgarm/include" -I"$project/compiler" \
    -c "$output/export_apicore.c" -o "$work/apicore.o"
"$arm_objcopy" -O binary --only-section=.sidc_apicore "$work/apicore.o" "$work/api-data"
test -s "$work/api-data"
if [[ $(head -c 7 "$work/api-data") != SBAPI05 ]]; then
    printf '%s\n' 'Refusing to install metadata with a non-SBAPI05 header.' >&2
    exit 1
fi

# The gzip trailer supplies the little-endian CRC32 expected by compiler.app.
gzip -nc "$work/api-data" > "$work/api.gz"
{
    cat "$work/api-data"
    tail -c 8 "$work/api.gz" | head -c 4
} > "$work/clibs.library"

# Generate in one temporary file and replace only after every step succeeds.
mv -- "$work/clibs.library" "$output/clibs.library"
printf 'Updated %s (%s bytes)\n' "$output/clibs.library" "$(wc -c < "$output/clibs.library" | tr -d ' ')"
printf '%s\n' 'Copy it to tfcard:/sidbox/l/clibs.library (on your SD card).'
