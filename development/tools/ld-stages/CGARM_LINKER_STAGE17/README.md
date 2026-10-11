# CGARM Linker — Stage 17

**Final planned host-side relocation-coverage push: COMMON storage identity and bounded mergeable records.**

This package contains ONE complete replacement file:
`development/tools/cgarm-v2-compare/cgarm-v2-compare.cpp`.

**Keep using LLVM for production.** This verifier is READ ONLY for input ELF/.app files and does **not** modify the custom linker, CGARM build tool, CoderGirl IDE, firmware or libraries. Do not place the experimental CGARM `.app` on the SIDBOX TFCard yet.

## Stage 16 results that motivated this stage

Your real GUI test counted **392 original relocations: 326 retained, 66 discarded**. The individually reconciled ledger proved **317 / 326 live destinations exactly**. All nine unproved sites are known:

- Eight `R_ARM_REL32` from the selected `libcgarm.a(cgarm_printf.o)` member: five one-byte empty strings and three strings with multiple possible LLVM addresses.
- One `R_ARM_GOT_BREL` in `v2_unit_7.o`, inside `.text.applet_entry +0x24`, targeting `heap_size`, a tentative `SHN_COMMON` allocation.

The previous checks reported 154721 unchanged compiler bytes, 65/65 live Thumb targets, 8/8 dynamic local GOT relocation sites. These are **host-side tests**, not proof of ABI/runtime equivalence.

## Stage 17 changes

1. **SHN_COMMON memory reconstruction.** Reads original GCC ELF32 symbol definitions from fingerprinted source `.o` files and selected archive members. Tracks COMMON symbols referenced from retained sections, measures symbol size and alignment, derives their CGARM addresses *after retained `.bss`* in lexical order, and checks the independently named LLVM `.symtab` allocation is inside writable NOBITS memory. Checks the exact pointer in each `.got` slot against those independently reconstructed addresses. If declarations conflict or LLVM provenance is not unique, reports `DEFERRED` instead of inventing an address.
2. **Conservative one-byte mergeable records.** An empty string has exactly one byte (`00`), which is too common to identify by scanning all memory. Only accepts an exact match when the LLVM linker map independently supplies a concrete source-section range and the fragment has exactly one valid location in that range. Otherwise it is `DEFERRED`, never a guessed `EXACT`.
3. **Source-scoped merge searches.** When the LLVM map does identify an input mergeable section range, use it to narrow fragment matches. This may recover some formerly ambiguous matches. Merged LLVM strings often reside in an `<internal>` pool with NO per-input-section mapping; in that case the checker refuses to infer a source identity.
4. **Clearer evidence counters** for one-byte records and LLVM map-scoped matches; the existing byte, branch, archive, GOT, dynamic-rebase, and individual relocation ledger audits remain.
5. **Fix for legitimate GOT-only fixtures:** if no ordinary section-local relocation exists but GOT/base identities are independently proved, that counts as meaningful verified coverage. The old final `provenance.verified>0` check no longer incorrectly rejects such a fully checked program.

**Crucial:** Stage 17 might NOT resolve the eight `cgarm_printf.o` entries in the real application, because multiple identical string destinations really can be unprovable using the existing LLVM ELF and map. If the strict gate still rejects, that is correct: it means that final host-side *exact* identity coverage is not yet established. Do not change the gate simply to reach 326/326.

## Replace and compile

Replace only:

`/mnt/LinuxDatas/work/SidboxIDE/SidboxIDE/development/tools/cgarm-v2-compare/cgarm-v2-compare.cpp`

```bash
cd /mnt/LinuxDatas/work/SidboxIDE/SidboxIDE

g++ -std=c++17 -O2 -Wall -Wextra -Werror \
  development/tools/cgarm-v2-compare/cgarm-v2-compare.cpp \
  -o idelibs/tools/bin/cgarm-v2-compare
```

## Run on the unchanged Stage 10 GUI build

The `.o`, `.elf`, `.app`, `.map` and archives **must all belong to the exact same build**. If you have rebuilt any source, regenerate BOTH linker outputs and corresponding maps first.

```bash
cd /home/kbox/ACoderGUIdesigner1/build/cgarm/designer

/mnt/LinuxDatas/work/SidboxIDE/SidboxIDE/idelibs/tools/bin/cgarm-v2-compare \
  ./stage10-experimental.elf ./stage10-DIAGNOSTIC-DO-NOT-RUN.app \
  ./designer.elf ./stage10-LLVM-DIAGNOSTIC-DO-NOT-RUN.app \
  --cg-map ./stage10-experimental.cgmap --llvm-map ./designer.map \
  --max-ram-kb 352 \
  --archives \
    /mnt/LinuxDatas/work/SidboxIDE/SidboxIDE/idelibs/tools/cgarm/lib/libcgarm.a \
    /mnt/LinuxDatas/work/SidboxIDE/SidboxIDE/idelibs/libraries/sb3dlibrary.a \
  --objects v2_unit_*.o --min-matched 1 \
  --emit-ledger ./stage17-ledger.tsv \
  | tee stage17-result.txt
```

If `stage17-ledger.tsv` already exists, choose a NEW name; the verifier will not overwrite it.

After reviewing the report, run the same verification without `--emit-ledger` and WITH `--strict-live`, saving the output as `stage17-strict-result.txt`. The strict gate is expected to PASS only when **every retained relocation site is exact**, and all required map evidence is present. It is possible, perhaps likely, the full GUI will still defer some mergeable strings. A strict failure is NOT a confirmed linker bug.

Please send both `stage17-result.txt` and `stage17-ledger.tsv`, and (if run) `stage17-strict-result.txt`.

## Tests run for this package

Compiled as specified above with `-Werror`.

- **Real LLVM + CGARM COMMON fixture:** `SHN_COMMON heap_size` allocated independently in each ELF; Stage 17 verified its GOT slot and GOT base, `--strict-live` passed **2/2** source relocations.
- **Two COMMON symbols + `.bss` fixture:** independent allocations for `aaa` and `heap_size`, both GOT slots checked; `--strict-live` passed **3/3** source relocations.
- **Bad COMMON GOT pointer:** mutated a GOT slot to a *different valid writable SDRAM address*, repacked the `.app` with a valid CRC and refreshed the CGARM map fingerprint. **Rejected** for wrong destination.
- **Ambiguous one-byte strings:** ARM fixture with two empty strings; all ambiguous mergeable addresses remain deferred; `--strict-live` **rejected**.
- **Stage 16 regression suite:** preserved archive-selection/fingerprint rejection, live branch accuracy and corruption detection, short merge records, and runtime-library auditing.

All these tests used small ARM fixtures. **The user's complete GUI `.o` and ELF files were not present locally**; only the user's Stage 16 logs and ledger were available. The effect on the nine real-world unresolved identities cannot be claimed until the user runs Stage 17.

## After Stage 17

If strict host coverage passes, do NOT immediately launch the full GUI application on the STM32H743. First design a recoverable, minimal applet trial with the original LLVM path as fallback and separately check loader/ABI/startup, BSS zeroing, heap/stack boundaries, rebase, and clean return. Hardware approval is a separate decision.
