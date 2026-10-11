# SIDBOX / CoderGirl CGARM — Stage 18: **first controlled STM32H743 hardware smoke test**

## READ FIRST

This is an *opt-in manual hardware trial*, not a new IDE linker configuration and not a production app. It was built from the user's uploaded firmware source dated 11 October 2026. **The uploaded source is not proof that identical firmware is currently flashed on the board.** Confirm your running firmware supports SBAPV2/Stage 6C before launching anything.

**NO firmware modifications, flashing or linker/IDE integration are required.** The existing LLVM linker remains the reliable production path. Neither applet has been executed on physical SIDBOX hardware by the author; host-side safety checks passed.

**Never put these files in `/auto/auto.app` or another autostart location. Never overwrite working applets.** Work in a new `/stage18/` directory on a backed-up TFCard and launch manually with all music/other applets stopped.

## What is in the package?

- `hardware/stage18-llvm-control.app` — first-run control: the EXACT SAME ARM source object linked with your working LLVM `ld.lld` (448 bytes).
- `hardware/stage18-cgarm-test.app` — experimental CGARM output, linked from that same ARM source object (328 bytes).
- `source/stage18_probe.c` — readable C reference describing what the test does; deliberately no firmware/SDK calls. `stage18_probe.S` is the **canonical exact input** for the tested builds, compiler-emitted ARM Thumb code with exception unwind annotations removed for a tiny freestanding smoke test.
- `source/gui_v2.ld` — copied V2 LLVM link template for reproducibility.
- `source/rebuild-on-fedora.sh` — optional complete rebuild, pack and strict-check script, from the shipped canonical assembly.
- `host-test/applet_v2_format.h` — unmodified copy of `Core/os/applet_v2_format.h` from the uploaded firmware.
- `host-test/stage18_host_loader_test.c` — host test that invokes the firmware's real header, CRC and relocation validation functions.
- `evidence/` — input `stage18_probe.o`, both linked `.elf`s, maps, strict verification log, link logs. `SHA256SUMS.txt` — manifest for critical binaries.

## Firmware compatibility findings

From the uploaded `Core/os/cmd.c`:

- `CMD_ENABLE_APPLET_V2_TEST` is defined as **1**; `CMD_ENABLE_V2_PSP_BRIDGE_TEST` is also **1** in that source (despite an older comment saying default OFF).
- `CMDLaunch` recognises `SBAPV2\0\0` and invokes `cmd_v2_launch_test` without changing the V1 path.
- `SBV2_ValidateHeader` checks image/memory/stack/heap sizes, flag combinations, relocation position/count and link-base bounds.
- The loader chooses a separate runtime address >= `0xD0500000`, below `0xD0600000` (subject to RAM-disk limit and avoiding already-registered applets).
- It clears all reserved memory, copies the applet image, verifies CRC32, reads **sorted** relocation offsets and applies exactly the packer-approved `R_ARM_RELATIVE` fixups.
- After `SCB_CleanDCache_by_Addr`, instruction-cache invalidation and barriers, it calls the applet entry as `int (*)(int argc, char **argv)`, on the **OS MSP for initial entry**; private PSP is reserved for later callback bridging.
- `dbug("launch v2 TEST: returned %d\n", result)` prints the result on **USART1**, configured for **256000 baud, 8N1**, TX=PA9 / RX=PA10 in the provided firmware.
- The test has no GUI windows/timers and should be unregistered and its memory freed on return.

This tiny test does not exercise callback PSP switching, `malloc`, OS GUI calls, hardware peripherals, or full GUI Designer integration. Those need separate follow-up testing.

## What the diagnostic actually tests

`applet_entry()` returns **`1818`** only after it has:

1. Compared a data pointer to the correct location of its initialized global variable. That pointer is inside `.data` and **MUST be rebased by one `R_ARM_RELATIVE`** when firmware selects the real SDRAM load address.
2. Read the expected initialized value `0x18C0FFEE` through that relocated pointer.
3. Verified one `.bss` word and eight `.bss` array elements are initially zero.
4. Written and read back two known patterns in writable memory.
5. Returned cleanly to the OS (indicated by firmware's own UART `returned 1818` message).

Error codes from the app: `-1801` relocated pointer wrong, `-1802` initialized data wrong, `-1803` zeroed BSS scalar wrong, `-1804` BSS array not zero, `-1805` write/readback failure. No UART result/hang/fault is not success; **stop** if that occurs.

## FIRST HARDWARE TEST — STEP BY STEP

**Preconditions:** Confirm you have a backup of current firmware and TFCard and can power-cycle/recover the board. Confirm the flashed firmware has this V2 loader enabled (the uploaded source does, but an older flash may not). Test when no other applets/music are running. Have your usual **3.3 V USART1 serial connection** ready so you can SEE the result; do not connect 5 V TTL to STM32 pins. No modifications to firmware are needed.

**1.** Copy BOTH `.app` files in `hardware/` into a NEW directory called `/stage18/` on the TFCard. Use only these two files. Do NOT put them in `/auto/` or replace `/auto/auto.app`.

**2.** Start your established UART1 terminal at **256000 baud, 8 data bits, no parity, 1 stop bit**. On Fedora, if you normally use `picocom` and your adapter is `/dev/ttyUSB0`, this is an example (use YOUR real device):

```bash
picocom -b 256000 /dev/ttyUSB0
```

**3.** Test the **LLVM reference first**, via SIDBOX's CLI:

```
launch /stage18/stage18-llvm-control.app
```

Wait for:

```
launch v2 TEST: returned 1818
```

If you do not see `1818`, **STOP** and send the UART transcript. If there is no UART attached, don't infer success from a blank screen: this test deliberately has no GUI.

**4.** Only if LLVM succeeded, launch the **CGARM experimental build**:

```
launch /stage18/stage18-cgarm-test.app
```

Expected:

```
launch v2 TEST: returned 1818
```

Both returning `1818` establishes a **real** basic load/rebase/data/BSS/write/return success on this STM32. It does NOT certify the full GUI or CGARM as a production linker.

**5.** Send the UART transcript of both launches and tell us whether SIDBOX's desktop and normal apps still work. Keep the tested files separate from your working projects.

If anything hangs or HardFaults: power-cycle to recover, **do not autostart or repeatedly relaunch the experimental file**, keep the LLVM build untouched, and send any UART fault output/J-Link PC/LR/CFSR if available.

## Local host verification ALREADY COMPLETED

- Both apps were produced from the exact same ARM `stage18_probe.o` input. `cgarm-ld` emitted PIE ELF + fingerprinted provenance and `ld.lld` emitted independent PIE + map. The production IDE was untouched.
- Both `.app` files passed the supplied firmware's C99 `SBV2_ValidateHeader()`, `SBV2_CRC32()` and `SBV2_RelocateWord()` in an independent host test, at actual SDRAM-compatible bases `0xD0500000` and `0xD05F0000`.
- Each app has exactly one runtime `R_ARM_RELATIVE` site, whose relocated pointer was checked against the **initialized signature word**. Both CRC-corrupted images and deliberately invalid relocated pointers were rejected in host tests.
- The shipping Stage 17 verifier **PASSED `--strict-live`, 5/5 live relocations exact**, 0 deferred or unmapped: 4 `R_ARM_REL32` and 1 `R_ARM_ABS32`.
- Data and retained machine-code bytes of the original source object were checked against both ELF outputs; both `.app` containers had entrypoint, stack, heap, image and rebase simulation checked.
- An optional package rebuild produced **exactly the same SHA256** for both apps.

Known limitations: The host test does **not execute ARM code**. Actual firmware flash may differ from the uploaded source. The test's C reference is explanatory; the shipped `.S`/`.o` are the byte-exact build inputs. Unwinding and exception tables are intentionally omitted in this minimal test; it is not a general C ABI validation.

### Source and binary sizes

| Binary | File | Initialized | Reserved RAM | Private callback stack | Heap | Runtime relocations |
|---|---:|---:|---:|---:|---:|---:|
| LLVM control | 448 B | 380 B | 25,024 B | 8,192 B | 16,384 B | 1 |
| CGARM experiment | 328 B | 260 B | 24,896 B | 8,192 B | 16,384 B | 1 |

### Optional: reproduce the build on Fedora

The bundle includes the final prebuilt `.app` files; rebuilding is **not necessary** for the first hardware test. To recreate the binaries independently, use clang, ld.lld, the custom linker, the V2 packer and Stage 17 verifier already installed on your development machine. This writes ONLY to a NEW temp directory (not the IDE or firmware):

```bash
bash source/rebuild-on-fedora.sh \
  /mnt/LinuxDatas/work/SidboxIDE/SidboxIDE/idelibs/tools/bin/cgarm-ld \
  /mnt/LinuxDatas/work/SidboxIDE/SidboxIDE/idelibs/tools/sidbox-v2-packer \
  /mnt/LinuxDatas/work/SidboxIDE/SidboxIDE/idelibs/tools/bin/cgarm-v2-compare
```

If the packer lives at another location, substitute its actual path. Use the shipped manifest/checksums to confirm an identical rebuild, and do not replace your working applications.

## After a real `1818 / 1818`

The next milestone is **beta IDE integration**: make CGARM an explicit opt-in linker for new V2 GUI projects, keep LLVM available as the default/fallback, maintain the user's existing 2048-KB IDE syntax threshold, and run repeated application-level tests including callbacks, complex SDK calls, private PSP, and full GUI runtime. Do not conflate this smoke test with approval of the unresolved `cgarm_printf.o` mergeable-string identities in the full GUI.
