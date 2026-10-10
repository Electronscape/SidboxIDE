// SIDBOX V2 native packer (host-side tool, not firmware).
// ELF32 ARM PIE -> SBAPV2 with only R_ARM_RELATIVE relocations.
// Deliberately rejects unsupported dynamic link dependencies and damaged ELF files.
#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits>
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif
#include <stdexcept>
#include <string>
#include <vector>

namespace {
using Byte = uint8_t;
using Bytes = std::vector<Byte>;
struct Error : std::runtime_error { using std::runtime_error::runtime_error; };
void require(bool ok, const std::string &why) { if (!ok) throw Error(why); }
uint64_t checkedPlus(uint64_t a, uint64_t b) { require(b <= UINT64_MAX-a, "Integer overflow"); return a+b; }
void bounds(const Bytes &v, uint64_t off, uint64_t length, const char *what) {
    require(off <= v.size() && length <= v.size()-off, std::string("Truncated ")+what);
}
uint16_t u16(const Bytes &v, uint64_t n) { bounds(v,n,2,"ELF field"); return uint16_t(v[n]) | (uint16_t(v[n+1])<<8); }
uint32_t u32(const Bytes &v, uint64_t n) {
    bounds(v,n,4,"ELF field");
    return uint32_t(v[n]) | (uint32_t(v[n+1])<<8) | (uint32_t(v[n+2])<<16) | (uint32_t(v[n+3])<<24);
}
void append32(Bytes &v, uint32_t n) { for (int i=0;i<4;++i) v.push_back(uint8_t(n>>(8*i))); }
uint64_t aligned(uint64_t v, uint64_t step) { return (v+step-1)&~(step-1); }
uint32_t crc32(const Bytes &v) {
    uint32_t crc=~uint32_t(0);
    for (Byte b:v) { crc^=b; for(int k=0;k<8;++k) crc=(crc>>1) ^ (0xedb88320u & -(crc&1u)); }
    return ~crc;
}
Bytes read(const std::filesystem::path &p) {
    std::ifstream in(p,std::ios::binary | std::ios::ate); require(bool(in),"Unable to read ELF: "+p.string());
    auto size=in.tellg(); require(size>0 && uint64_t(size)<=32*1024*1024,"Invalid ELF input length");
    Bytes v(static_cast<size_t>(size)); in.seekg(0); in.read(reinterpret_cast<char*>(v.data()), size);
    require(bool(in),"ELF read error"); return v;
}
struct Segment { uint32_t off, addr, fileSize, memSize; };
struct Section { uint32_t name, type, off, size, entsize; };
std::string nameOf(const Bytes &strings, uint32_t nameOff) {
    require(nameOff<strings.size(),"Bad section name offset");
    auto first=strings.begin()+nameOff;
    auto end=std::find(first,strings.end(),Byte(0));
    require(end!=strings.end(),"Unterminated section name");
    return std::string(first,end);
}
struct Image { uint32_t base, entryOffset, memSpan; Bytes data; std::vector<uint32_t> reloc; };
Image parseElf(const Bytes &elf,uint32_t heap) {
    bounds(elf,0,52,"ELF header");
    require(elf[0]==0x7f && elf[1]=='E' && elf[2]=='L' && elf[3]=='F' &&
            elf[4]==1 && elf[5]==1 && elf[6]==1,"Expected little-endian ELF32");
    require(u16(elf,16)==3 && u16(elf,18)==40,"Expected ARM ET_DYN position-independent ELF");
    const uint32_t entry=u32(elf,24), phoff=u32(elf,28), shoff=u32(elf,32);
    const uint16_t phsize=u16(elf,42), phcount=u16(elf,44), shsize=u16(elf,46), shcount=u16(elf,48), shstr=u16(elf,50);
    require(phsize==32 && shsize==40 && phcount>0 && phcount<=64 && shcount>0 && shcount<=1024,"Invalid ELF table parameters");
    bounds(elf,phoff,uint64_t(phsize)*phcount,"program headers");
    bounds(elf,shoff,uint64_t(shsize)*shcount,"section headers");
    require(shstr<shcount,"Missing ELF section-name table");
    std::vector<Segment> loads;
    uint64_t minAddr=UINT64_MAX, maxMem=0, maxFile=0;
    for(uint32_t i=0;i<phcount;++i) {
        uint64_t pos=uint64_t(phoff)+i*32;
        uint32_t type=u32(elf,pos), off=u32(elf,pos+4), addr=u32(elf,pos+8);
        uint32_t filesz=u32(elf,pos+16), memsz=u32(elf,pos+20);
        if(type==3) throw Error("PT_INTERP dynamic loader dependency not supported");
        if(type==2) {
            require(memsz>=filesz && filesz%8==0,"Bad PT_DYNAMIC"); bounds(elf,off,filesz,"dynamic entries");
            for(uint64_t p=off;p<off+uint64_t(filesz);p+=8) {
                uint32_t tag=u32(elf,p);
                require(tag!=1 && tag!=7 && tag!=23,"Unsupported dynamic loader tag "+std::to_string(tag));
            }
        }
        if(type!=1) continue;
        require(filesz<=memsz,"PT_LOAD file bytes exceed memory bytes"); bounds(elf,off,filesz,"PT_LOAD image");
        minAddr=std::min<uint64_t>(minAddr,addr);
        maxMem=std::max(maxMem,checkedPlus(addr,memsz));
        maxFile=std::max(maxFile,checkedPlus(addr,filesz));
        loads.push_back({off,addr,filesz,memsz});
    }
    require(!loads.empty() && maxMem>minAddr && maxMem-minAddr<=6*1024*1024,"Invalid applet memory span");
    require(maxFile>minAddr && maxFile-minAddr<=256*1024,"Invalid applet image span");
    Image out{}; out.base=uint32_t(minAddr); out.memSpan=uint32_t(maxMem-minAddr);
    out.data.resize(size_t(maxFile-minAddr));
    Bytes covered(out.data.size());
    for(auto s:loads) {
        uint64_t dst=uint64_t(s.addr)-minAddr;
        require(dst+s.fileSize<=out.data.size(),"PT_LOAD extends beyond image");
        for(uint64_t n=0;n<s.fileSize;++n) {
            uint64_t index=dst+n; const Byte value=elf[s.off+n];
            require(!covered[index] || out.data[index]==value,"Conflicting PT_LOAD segments");
            covered[index]=1; out.data[index]=value;
        }
    }
    std::vector<Section> sections;
    for(uint32_t i=0;i<shcount;++i) {
        uint64_t pos=uint64_t(shoff)+i*40;
        sections.push_back({u32(elf,pos),u32(elf,pos+4),u32(elf,pos+16),u32(elf,pos+20),u32(elf,pos+36)});
    }
    auto names=sections[shstr]; bounds(elf,names.off,names.size,"section name strings");
    Bytes nameBytes(elf.begin()+names.off,elf.begin()+names.off+names.size);
    for(auto s:sections) {
        const auto name=nameOf(nameBytes,s.name);
        bool dynamicRel=(name.rfind(".rel.dyn",0)==0 || name.rfind(".rela.dyn",0)==0 ||
                         name.rfind(".rel.plt",0)==0 || name.rfind(".rela.plt",0)==0);
        if(!dynamicRel) continue;
        require(name.rfind(".rel.dyn",0)==0 && s.type==9 && s.entsize==8 && s.size%8==0,
                "Unsupported dynamic relocation table "+name);
        bounds(elf,s.off,s.size,"dynamic relocation table");
        for(uint64_t p=s.off;p<s.off+uint64_t(s.size);p+=8) {
            uint32_t site=u32(elf,p), info=u32(elf,p+4);
            require((info&255u)==23 && (info>>8)==0,"Unsupported ARM relocation type="+std::to_string(info&255u));
            require(site>=minAddr,"Relocation site below image");
            uint64_t offset=site-minAddr;
            require(offset%4==0 && offset+4<=out.data.size(),"Invalid relocation site");
            uint32_t value=u32(out.data,offset);
            require(uint64_t(value&~1u)>=minAddr && uint64_t(value&~1u)<maxMem+heap,
                    "Relocation target outside allocated applet memory");
            out.reloc.push_back(uint32_t(offset));
        }
    }
    std::sort(out.reloc.begin(),out.reloc.end());
    require(!out.reloc.empty(),"Expected at least one R_ARM_RELATIVE relocation");
    require(std::adjacent_find(out.reloc.begin(),out.reloc.end())==out.reloc.end(),"Duplicate relocation sites");
    require(uint64_t(entry&~1u)>=minAddr && uint64_t(entry&~1u)<maxFile,"Entry point outside initialised image");
    out.entryOffset=entry-out.base;
    return out;
}
void publish(const std::filesystem::path &target,const Bytes &raw) {
    const auto tmp=target.string()+".v2tmp";
    { std::ofstream out(tmp,std::ios::binary|std::ios::trunc); require(bool(out),"Can't create temporary output");
      out.write(reinterpret_cast<const char*>(raw.data()),std::streamsize(raw.size()));
      if(!out) { out.close(); std::filesystem::remove(tmp); throw Error("Output write error"); }
    }
#ifdef _WIN32
    // std::filesystem::rename may not replace an existing destination on Windows.
    // Preserve the last good .app unless Windows atomically replaces it.
    if (!MoveFileExW(std::filesystem::path(tmp).c_str(), target.c_str(),
                     MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH)) {
        std::filesystem::remove(tmp);
        throw Error("Windows failed to publish output");
    }
#else
    std::error_code ec; std::filesystem::rename(tmp,target,ec);
    if(ec) { std::filesystem::remove(tmp); throw Error("Unable to publish output: "+ec.message()); }
#endif
}
void run(const std::filesystem::path &source,const std::filesystem::path &dest,uint32_t heap) {
    Image image=parseElf(read(source),heap);
    uint64_t total=aligned(uint64_t(image.memSpan)+heap,32);
    require(image.data.size()<=256u*1024u && total<=512u*1024u,"V2 loader image/RAM limit exceeded (256K/512K)");
    uint64_t relocOffset=aligned(uint64_t(64)+image.data.size(),4);
    uint64_t finalSize=relocOffset+uint64_t(image.reloc.size())*4;
    require(finalSize<=std::numeric_limits<uint32_t>::max(),"File too large");
    Bytes raw={'S','B','A','P','V','2',0,0};
    for(uint32_t x:{2u,64u,uint32_t(finalSize),uint32_t(image.data.size()),uint32_t(total),
                    image.entryOffset,image.base,uint32_t(relocOffset),uint32_t(image.reloc.size()),
                    32u,heap,0u,0u,crc32(image.data)}) append32(raw,x);
    require(raw.size()==64,"Internal header size mismatch");
    raw.insert(raw.end(),image.data.begin(),image.data.end());
    raw.resize(size_t(relocOffset),0);
    for(uint32_t site:image.reloc) append32(raw,site);
    require(raw.size()==finalSize,"Internal output size mismatch");
    publish(dest,raw);
    std::cout<<"V2 native: "<<dest.string()<<"; image "<<image.data.size()<<"B, memory "<<total
             <<"B, relocations "<<image.reloc.size()<<"\n";
}
}
int main(int argc,char **argv) {
    try {
        if(!(argc==3 || argc==5)) throw Error("Usage: sidbox-v2-packer <input.elf> <output.app> [--heap <bytes>]");
        uint32_t heap=8192;
        if(argc==5) {
            require(std::string(argv[3])=="--heap","Expected --heap <bytes>");
            const std::string argument(argv[4]);
            require(!argument.empty() && argument.find_first_not_of("0123456789")==std::string::npos,"Invalid heap allocation");
            unsigned long long n=std::stoull(argument);
            require(n<=1024*1024,"Heap request exceeds supported limit"); heap=uint32_t(n);
        }
        run(argv[1],argv[2],heap);
        return 0;
    } catch(const std::exception &e) { std::cerr<<"ERROR: V2 packer: "<<e.what()<<'\n'; return 1; }
}
