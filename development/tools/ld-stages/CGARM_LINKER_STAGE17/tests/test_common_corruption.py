from pathlib import Path
import subprocess, struct
root=Path(__file__).parent
src=(root/'common-cg.elf').read_bytes()
b=bytearray(src)
shoff=struct.unpack_from('<I',b,32)[0]
shnum=struct.unpack_from('<H',b,48)[0]
shstrndx=struct.unpack_from('<H',b,50)[0]
str_h=shoff+shstrndx*40
str_off=struct.unpack_from('<I',b,str_h+16)[0]
str_size=struct.unpack_from('<I',b,str_h+20)[0]
strings=b[str_off:str_off+str_size]
for k in range(shnum):
    h=shoff+k*40
    name_off=struct.unpack_from('<I',b,h)[0]
    name=strings[name_off:strings.index(0,name_off)].decode()
    if name=='.got':
        foff=struct.unpack_from('<I',b,h+16)[0]
        old=struct.unpack_from('<I',b,foff)[0]
        struct.pack_into('<I',b,foff,old+4)
        break
else:raise Exception('Missing GOT')
(root/'common-corrupted.elf').write_bytes(b)
maptext=(root/'common-cg.cgmap').read_text()
hashval=0xcbf29ce484222325
for byte in b:hashval=((hashval ^ byte)*0x100000001b3)&((1<<64)-1)
import re
newtext=re.sub(r'(?m)^ELF\s+\S+',f'ELF\t{hashval:016X}',maptext)
(root/'common-corrupted.cgmap').write_text(newtext)
packer='/mnt/data/linker_source/idelibs/tools/sidbox-v2-packer'
subprocess.run([packer,str(root/'common-corrupted.elf'),str(root/'common-corrupted.app'),'--heap','16384','--stack','8192'],check=True)
cmd=[str(root/'cgarm-v2-compare'),str(root/'common-corrupted.elf'),str(root/'common-corrupted.app'),str(root/'common-llvm.elf'),str(root/'common-llvm.app'),'--cg-map',str(root/'common-corrupted.cgmap'),'--llvm-map',str(root/'common-llvm.map'),'--max-ram-kb','128','--objects',str(root/'common-got.o'),'--min-matched','1','--strict-live']
p=subprocess.run(cmd,capture_output=True,text=True)
(root/'common-corrupted-rejected.log').write_text(p.stdout+p.stderr)
assert p.returncode!=0 and 'GOT slot points to wrong symbol' in p.stdout+p.stderr,(p.returncode,(p.stdout+p.stderr)[-800:])
print('PASS: COMMON GOT pointer changed to another valid writable RAM address, .app CRC updated, CGARM map fingerprint refreshed; rejected exact destination')
