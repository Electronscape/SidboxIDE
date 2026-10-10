#!/usr/bin/env python3
"""HOST-ONLY SIDBOX V2 RELATIVE-RELOCATION PROOF OF CONCEPT.

EXPERIMENTAL: only supported by the opt-in SIDBOX V2 test loader. Verifies ELF32 ARM PIE R_ARM_RELATIVE
relocations, emits experimental SBAPV2 binary, and can simulate relocation
at two different load addresses. It refuses unsupported dynamic relocations.
"""
import argparse
import pathlib
import struct
import zlib

MAGIC = b'SBAPV2\0\0'
HEADER = struct.Struct('<8s14I')
ELF_HEAD = struct.Struct('<16sHHIIIIIHHHHHH')
PHDR = struct.Struct('<IIIIIIII')
SHDR = struct.Struct('<IIIIIIIIII')
R_ARM_RELATIVE = 23


def align(v, n):
    return (v + n - 1) & ~(n - 1)


def check(cond, message):
    if not cond:
        raise ValueError(message)


def get_elf(path):
    raw = pathlib.Path(path).read_bytes()
    check(len(raw) >= ELF_HEAD.size, 'Truncated ELF')
    (ident, etype, machine, version, entry, phoff, shoff, flags,
     ehsize, phentsize, phnum, shentsize, shnum, shstrndx) = ELF_HEAD.unpack_from(raw)
    check(ident[:4] == b'\x7fELF' and ident[4] == 1 and ident[5] == 1,
          'Only ELF32 little-endian is supported')
    check(etype == 3 and machine == 40, 'Requires ARM ET_DYN PIE ELF (not an ET_EXEC legacy ELF)')
    check(phentsize == PHDR.size and shentsize == SHDR.size, 'Unexpected ELF record sizes')
    check(0 < phnum <= 64 and 0 < shnum <= 1024, 'Unexpected ELF table counts')
    check(phoff + phnum * PHDR.size <= len(raw), 'Truncated program headers')
    check(shoff + shnum * SHDR.size <= len(raw), 'Truncated section headers')
    ph = [PHDR.unpack_from(raw, phoff + i * PHDR.size) for i in range(phnum)]
    sh = [SHDR.unpack_from(raw, shoff + i * SHDR.size) for i in range(shnum)]
    check(shstrndx < len(sh), 'Missing section string table')
    name_sh = sh[shstrndx]
    shstr = raw[name_sh[4]:name_sh[4] + name_sh[5]]

    def name_of(row):
        p = row[0]
        check(p < len(shstr), 'Invalid section name offset')
        return shstr[p:shstr.find(b'\0', p)].decode('ascii', 'replace')

    load_segments = [s for s in ph if s[0] == 1]  # PT_LOAD
    check(load_segments, 'No loadable segments')
    base = min(s[2] for s in load_segments)
    hi = max(s[2] + s[5] for s in load_segments)
    initialized_hi = max(s[2] + s[4] for s in load_segments)
    check(hi > base and hi - base <= 6 * 1024 * 1024, 'Unreasonable applet memory span')
    check(initialized_hi >= base, 'No initialized image')
    image = bytearray(initialized_hi - base)
    covered = bytearray(len(image))
    for s in load_segments:
        _, off, va, _, filesz, memsz, _, _ = s
        check(filesz <= memsz and off + filesz <= len(raw), 'Truncated/bad PT_LOAD segment')
        offset = va - base
        check(offset + filesz <= len(image), 'Segment extends past image')
        for i in range(offset, offset + filesz):
            check(not covered[i] or image[i] == raw[off + i - offset], 'Conflicting ELF segments')
            covered[i] = 1
        image[offset:offset + filesz] = raw[off:off + filesz]

    relocations = []
    for s in sh:
        sname = name_of(s)
        if not (sname.startswith('.rel.dyn') or sname.startswith('.rela.dyn')
                or sname.startswith('.rel.plt') or sname.startswith('.rela.plt')):
            continue
        check(sname.startswith('.rel.dyn') and s[1] == 9 and s[9] == 8,
              f'Unsupported dynamic relocation table {sname}')
        off, size = s[4], s[5]
        check(off + size <= len(raw), 'Truncated relocation table')
        for rec in range(off, off + size, 8):
            site, info = struct.unpack_from('<II', raw, rec)
            rtype, symbol = info & 0xff, info >> 8
            check(rtype == R_ARM_RELATIVE and symbol == 0,
                  f'Unsupported dynamic ARM relocation type={rtype} sym={symbol}; REJECTED')
            pos = site - base
            check(site >= base and pos % 4 == 0 and pos + 4 <= len(image),
                  'Invalid relocation site')
            value = struct.unpack_from('<I', image, pos)[0]
            check(base <= (value & ~1) < hi,
                  f'Relocation target 0x{value:08X} lies outside applet image; REJECTED')
            relocations.append(pos)
    check(len(set(relocations)) == len(relocations), 'Duplicate relocation site')
    check(relocations, 'No R_ARM_RELATIVE relocations found; PoC requires at least one')
    check(base <= (entry & ~1) < initialized_hi, 'Entrypoint is outside initialized memory')
    return base, entry - base, bytes(image), hi - base, sorted(relocations)


def pack_v2(elf_path, output, heap_bytes):
    base, entry_off, image, mem_span, relocs = get_elf(elf_path)
    total_mem = align(mem_span + heap_bytes, 32)
    # 64-byte header; image begins immediately afterwards.
    reloc_off = align(HEADER.size + len(image), 4)
    file_size = reloc_off + 4 * len(relocs)
    fields = (MAGIC, 2, HEADER.size, file_size, len(image), total_mem,
              entry_off, base, reloc_off, len(relocs), 32, heap_bytes, 0, 0,
              zlib.crc32(image))
    content = bytearray(HEADER.pack(*fields))
    content.extend(image)
    content.extend(b'\0' * (reloc_off - len(content)))
    for pos in relocs:
        content.extend(struct.pack('<I', pos))
    check(len(content) == file_size, 'Bad packed file length')
    pathlib.Path(output).write_bytes(content)
    print(f'PoC: {output}; image {len(image)}B, memory {total_mem}B, relocations {len(relocs)}')
    return content


def simulate(binary, dest):
    check(len(binary) >= HEADER.size, 'Short v2 header')
    (magic, vers, head_len, file_size, image_size, memory_size, entry_off,
     base, reloc_off, reloc_count, alignment, heap_bytes,
     reserved, flags, checksum) = HEADER.unpack_from(binary)
    check(magic == MAGIC and vers == 2 and head_len == 64 and file_size == len(binary), 'Invalid v2 header')
    check(image_size <= memory_size and HEADER.size + image_size <= reloc_off,
          'Invalid v2 sizes')
    check(reloc_off + reloc_count * 4 == file_size, 'Invalid relocation table size')
    check(dest % alignment == 0 and alignment >= 32, 'Unaligned destination')
    memory = bytearray(memory_size)
    image = binary[HEADER.size:HEADER.size + image_size]
    check(zlib.crc32(image) == checksum, 'Image CRC mismatch')
    memory[:len(image)] = image
    sites = []
    for i in range(reloc_count):
        pos = struct.unpack_from('<I', binary, reloc_off + i * 4)[0]
        check(pos % 4 == 0 and pos + 4 <= image_size, 'Invalid relocation site')
        value = struct.unpack_from('<I', memory, pos)[0]
        patched = (value + (dest - base)) & 0xffffffff
        struct.pack_into('<I', memory, pos, patched)
        sites.append((pos, value, patched))
    return memory, dest + entry_off, sites


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('elf', help='ARM little-endian PIE ELF built for CoderGirl test')
    ap.add_argument('output', help='PoC v2 .app output (DO NOT deploy to firmware)')
    ap.add_argument('--heap', type=int, default=8192, help='Additional reserved bytes for heap (default: 8192)')
    args = ap.parse_args()
    check(0 <= args.heap <= 1024*1024, 'Bad heap reserve')
    binary = pack_v2(args.elf, args.output, args.heap)
    for dest in (0xD0500000, 0xD0580000):
        mem, entry, sites = simulate(binary, dest)
        print(f'  simulated load 0x{dest:08X}: entry 0x{entry:08X}; first relocation 0x{sites[0][2]:08X}')
    print('Host simulation complete. This app can execute ONLY with the experimental V2 test-loader firmware.')


if __name__ == '__main__':
    main()
