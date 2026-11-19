#!/usr/bin/env bash
set -euo pipefail

package=$(cd -- "$(dirname -- "$0")" && pwd)
ide=$(cd -- "${1:?Pass the path to your SidboxIDE source folder}" && pwd)
if [[ -f "$ide/api/apis.h" && -d "$ide/tools/bin" ]]; then
    ide=$(dirname -- "$ide")
fi
source="$ide/development/tools/cgarm-build/cgarm-build.cpp"
bin="$ide/idelibs/tools/bin"
if [[ ! -f "$source" || ! -f "$ide/idelibs/api/apis.h" || ! -d "$bin" ]]; then
    printf 'Expected source %s and SDK %s/idelibs\n' "$source" "$ide" >&2
    exit 1
fi
work=$(mktemp -d "$bin/.apicore.XXXXXXXX")
trap 'rm -rf -- "$work"' EXIT
cp -- "$source" "$work/cgarm-build.cpp"
if ! grep -Fq 'Projects with -DSIDC_EXPORT_APICORE build apis.bin' "$work/cgarm-build.cpp"; then
    if ! patch --batch --forward --fuzz=0 "$work/cgarm-build.cpp" \
        < "$package/ide/cgarm-build-apicore.patch"; then
        printf 'The patch needs to be adapted to %s\n' "$source" >&2
        exit 1
    fi
fi
"${CXX:-g++}" -std=c++17 -O2 -Wall -Wextra \
    "$work/cgarm-build.cpp" -o "$work/cgarm-build"
"$work/cgarm-build" --help > "$work/help"
grep -Fq 'Projects with -DSIDC_EXPORT_APICORE build apis.bin' "$work/help"

tool="$bin/cgarm-build"
backup="$tool.before-apicore"
if [[ -e "$tool" && ! -e "$backup" && ! -L "$backup" ]]; then
    cp -p -- "$tool" "$backup"
fi
mv -f -- "$work/cgarm-build" "$tool"
printf 'Updated %s\n' "$tool"
