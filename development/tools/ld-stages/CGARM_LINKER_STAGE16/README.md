# CGARM Linker — Stage 16

**Individual source-relocation provenance, strict reconciliation, and actionable coverage ledger**

**Scope:** This is a complete, standalone replacement of `development/tools/cgarm-v2-compare/cgarm-v2-compare.cpp` only. CGARM's experimental linker, CoderGirl/Qt IDE, V1/Gaming pipeline, GCC toolchain, LLVM reference linker, SIDBOX firmware, libraries and packer are **unchanged**. This remains **host-only diagnostic software**, not permission to run an experimental `.app` on the SIDBOX TFCard.

## Why this release?

Stage 15's real GUI Designer log showed 392 scanned source relocations (326 retained, 66 discarded), with 317 exact identities and 9 deferred (8 `R_ARM_REL32` in mergeable data and 1 GOT identity). Aggregate counts alone can conceal a **double-counted relocation** or a **missing source relocation**. In particular, a local `R_ARM_GOT_BREL` site may be inspected by both the local map audit and the dedicated GOT audit. Stage 16 makes a separate reconciliation pass over the *identity of each individual site*.

## Additions

1. **Unique per-source relocation keys**: `(source object/archive member, input section, exact source offset, relocation type)`. The linker-map audit records exact `REL32` / `ABS32` sites; the Thumb audit records exact BL / B.W sites; the dedicated GOT audit records its exact BASE_PREL / GOT_BREL sites. A local GOT observation from another audit remains corroborating evidence but is **not double-counted**.
2. **Independent full-census reconciliation**: every claimed verified site must occur exactly once among the original GCC input relocations and must be classified as retained (`LIVE`) by the CGARM and LLVM maps. No discarded or unmapped relocation can become an exact pass. The exact-site count must match the existing independent per-family totals; otherwise the verifier fails.
3. **Optional `--emit-ledger PATH.tsv`**: writes one TSV row for each original source relocation, including selected `.a` members. Columns: `object`, `input_section`, `offset`, `relocation`, `target_symbol`, `status`, `evidence`. The statuses are `EXACT`, `DEFERRED`, `DISCARDED`, `UNMAPPED`. For unresolved mergeable strings the evidence gives the target section and reason (e.g. multiple matching LLVM addresses); for deferred GOT slots it names the symbol. Missing mapping evidence remains an explicit failure to prove, not a presumed success.
4. **No report overwrites**: refuses to overwrite an existing TSV, so a new run cannot destroy earlier evidence. `--emit-ledger` requires both linker maps.
5. **`--strict-live` preserved**: rejects any unresolved retained relocation or missing mapping evidence. The ledger is written *before* this strict failure, so if nine live identities remain deferred you can still send us exactly which ones.

## Install / build on Fedora

Replace **only**:

`/mnt/LinuxDatas/work/SidboxIDE/SidboxIDE/development/tools/cgarm-v2-compare/cgarm-v2-compare.cpp`

```bash
cd /mnt/LinuxDatas/work/SidboxIDE/SidboxIDE

g++ -std=c++17 -O2 -Wall -Wextra -Werror \
  development/tools/cgarm-v2-compare/cgarm-v2-compare.cpp \
  -o idelibs/tools/bin/cgarm-v2-compare
```

## Run the real GUI Designer verification

Reuse the **unchanged** Stage 10 ELFs, `.app` files, `.cgmap`, `.map`, original `.o` files and archives, which must belong to the **same build**. Check that `stage16-ledger.tsv` does not already exist, or use a new output filename.

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
  --emit-ledger ./stage16-ledger.tsv \
  | tee stage16-result.txt
```

**Please share both `stage16-result.txt` and `stage16-ledger.tsv`**. The second file lets us identify the exact 8 mergeable and 1 GOT source site rather than guessing from a count.

## Optional strict gate

Run the *same command* but replace `--emit-ledger ./stage16-ledger.tsv` with `--strict-live`, then save with `| tee stage16-strict-result.txt`. The real GUI is expected to **fail strict-live** until the nine references are resolved. A strict failure is useful evidence, not evidence of a broken executable.

On a successful strict host check, the tool still does **not** prove runtime ABI equivalence, exception/unwind behaviour, CPU cache/MPU setup, hardware loader implementation, or peripheral correctness. LLVM remains the production linker.

## Validation actually performed locally

Compiled with `g++ -std=c++17 -O2 -Wall -Wextra -Werror`.

- All existing Stage 15 archive, branch, mergeable-string, GOT and strict-gate regression cases passed.
- A real GOT fixture generated a site ledger with **two different original relocation sites**: one BASE_PREL, one GOT_BREL. Both marked `EXACT`; strict gate passed. (This caught and fixed an early duplicate-counting error in the new reconciliation logic.)
- A deliberately ambiguous mergeable-string ELF gave **4 EXACT and 2 DEFERRED live sites**, with the exact reason for each deferred target. The strict gate rejected it.
- Refused to overwrite an existing ledger; refused to write one without both source maps.
- Original deliberately redirected Thumb call and deliberately incorrect GOT pointer are still rejected.

**Stage 16 has not yet been run on the user's real 12-object GUI Designer files.** No claim of recovering the final nine is made until that test is performed.
