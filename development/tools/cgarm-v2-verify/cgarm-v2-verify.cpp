// CGARM Stage 5: read-only host verifier for SIDBOX V2 applet ELF + packed .app.
// Purpose: check exactly what the current SIDBOX packer/loader would copy and
// relocate. This is NOT an ARM instruction emulator and not hardware approval.
// C++17, no Qt, LLVM or third-party runtime dependencies.
#include <algorithm>
#include <cstdint>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace {
using Bytes = std::vector<uint8_t>;
struct Error : std::runtime_error { using std::runtime_error::runtime_error; };
void must(bool ok,const std::string &why) { if(!ok) throw Error(why); }
std::string hex(uint32_t x) { std::ostringstream s; s << "0x" << std::uppercase << std::hex << std::setw(8) << std::setfill('0') << x; return s.str(); }
void bounds(const Bytes &v,uint64_t off,uint64_t n,const char *what) {
    must(off<=v.size() && n<=v.size()-off,std::string("Truncated ")+what);
}
uint16_t u16(const Bytes &v,uint64_t off) { bounds(v,off,2,"uint16"); return uint16_t(v[off]) | uint16_t(v[off+1])<<8; }
uint32_t u32(const Bytes &v,uint64_t off) {
    bounds(v,off,4,"uint32");
    return uint32_t(v[off]) | uint32_t(v[off+1])<<8 | uint32_t(v[off+2])<<16 | uint32_t(v[off+3])<<24;
}
void put32(Bytes &v,uint64_t off,uint32_t x) { bounds(v,off,4,"write32"); for(int i=0;i<4;++i) v[off+i]=uint8_t(x>>(i*8)); }
uint32_t crc32(const Bytes &v) {
    uint32_t c=0xffffffffu;
    for(auto b:v){ c^=b; for(int i=0;i<8;++i) c=(c>>1)^((c&1u)?0xedb88320u:0u); }
    return ~c;
}
Bytes readFile(const std::string &path) {
    std::ifstream f(path,std::ios::binary|std::ios::ate);
    must(bool(f),"Cannot open: "+path);
    auto sz=f.tellg(); must(sz>0 && uint64_t(sz)<=32u*1024u*1024u,"Invalid file size: "+path);
    Bytes b(static_cast<size_t>(sz)); f.seekg(0);
    f.read(reinterpret_cast<char*>(b.data()),std::streamsize(b.size()));
    must(bool(f),"Read error: "+path);
    return b;
}
struct Header {
    uint32_t version=0, headerSize=0, fileSize=0, imageSize=0, memorySize=0;
    uint32_t entryOffset=0, linkBase=0, relocOffset=0, relocCount=0;
    uint32_t alignment=0, heap=0, stack=0, flags=0, crc=0;
};
struct App { Header h; Bytes image; std::vector<uint32_t> sites; };
struct Elf { uint32_t base=0, entry=0, memSpan=0, stackSize=0;
    Bytes image; std::vector<uint32_t> sites; };
uint32_t aligned32(uint64_t n) {
    must(n<=uint64_t(UINT32_MAX)-31u,"Aligned value overflow");
    return uint32_t((n+31u)&~uint64_t(31));
}
uint32_t checkedU32(uint64_t n,const std::string &name) {
    must(n<=UINT32_MAX,"Overflow: "+name); return uint32_t(n);
}
App parseApp(const Bytes &b) {
    must(b.size()>=64,"V2 .app shorter than 64-byte header");
    must(std::memcmp(b.data(),"SBAPV2\0\0",8)==0,"Not an SBAPV2 file");
    Header h;
    h.version=u32(b,8); h.headerSize=u32(b,12); h.fileSize=u32(b,16);
    h.imageSize=u32(b,20); h.memorySize=u32(b,24); h.entryOffset=u32(b,28);
    h.linkBase=u32(b,32); h.relocOffset=u32(b,36); h.relocCount=u32(b,40);
    h.alignment=u32(b,44); h.heap=u32(b,48); h.stack=u32(b,52);
    h.flags=u32(b,56); h.crc=u32(b,60);
    must(h.version==2 && h.headerSize==64 && h.fileSize==b.size() && h.alignment==32,
         "V2 header version/length/alignment invalid");
    must(h.flags==0 || h.flags==1,"Unsupported V2 header flags");
    must(h.imageSize>0 && h.imageSize<=256u*1024u && h.memorySize>0 &&
         h.memorySize<=512u*1024u && h.memorySize%32==0,"V2 image/memory limits invalid");
    must(h.imageSize<=h.memorySize && h.heap<=h.memorySize-h.imageSize,"V2 heap/image overlap");
    if(h.flags==0) must(h.stack==0,"V2 legacy header has stack reservation");
    else must(h.stack>=4096 && h.stack%32==0 && h.heap%32==0 &&
              h.stack<=h.memorySize-h.heap-h.imageSize,"Invalid private-PSP stack");
    must(h.entryOffset!=0 && (h.entryOffset&1u) &&
         (h.entryOffset&~1u)<h.imageSize,"Invalid Thumb entry offset");
    must(h.relocOffset>=64 && h.imageSize<=h.relocOffset-64 &&
         h.relocOffset<=b.size() && h.relocOffset%4==0,"Invalid relocation-table offset");
    must((b.size()-h.relocOffset)%4==0 &&
         h.relocCount==(b.size()-h.relocOffset)/4,"Invalid relocation-table count");
    must(h.linkBase>=0xD0000000u && h.linkBase<0xD0600000u &&
         h.memorySize<=0xD0600000u-h.linkBase,"Linked image outside SIDBOX SDRAM applet region");
    App a; a.h=h;
    a.image=Bytes(b.begin()+64,b.begin()+64+h.imageSize);
    must(crc32(a.image)==h.crc,"V2 image CRC32 mismatch");
    for(uint32_t i=0;i<h.relocCount;++i){
        uint32_t site=u32(b,uint64_t(h.relocOffset)+uint64_t(i)*4);
        must(site%4==0 && h.imageSize>=4 && site<=h.imageSize-4,"Invalid relocation site");
        must(a.sites.empty() || a.sites.back()<site,"Relocations not strictly sorted or duplicate");
        a.sites.push_back(site);
    }
    must(!a.sites.empty(),"V2 file has no R_ARM_RELATIVE sites");
    return a;
}
struct Sec { uint32_t name=0,type=0,addr=0,off=0,size=0,entsize=0; };
std::string nameOf(const Bytes &names,uint32_t off) {
    must(off<names.size(),"ELF bad section name index");
    auto start=names.begin()+off;
    auto end=std::find(start,names.end(),uint8_t(0));
    must(end!=names.end(),"ELF unterminated section name");
    return std::string(start,end);
}
Elf parseElf(const Bytes &b,uint32_t expectedStack) {
    bounds(b,0,52,"ELF header");
    must(b[0]==0x7f && b[1]=='E' && b[2]=='L' && b[3]=='F' &&
         b[4]==1 && b[5]==1 && b[6]==1,"Not little-endian ELF32");
    must(u16(b,16)==3 && u16(b,18)==40,"Not ARM ET_DYN ELF");
    uint32_t entry=u32(b,24),phoff=u32(b,28),shoff=u32(b,32);
    uint16_t phent=u16(b,42),phcnt=u16(b,44),shent=u16(b,46),shcnt=u16(b,48),shstr=u16(b,50);
    must(phent==32 && phcnt>0 && phcnt<=64 && shent==40 &&
         shcnt>0 && shcnt<=1024 && shstr<shcnt,"Invalid ELF table sizes");
    bounds(b,phoff,uint64_t(phent)*phcnt,"ELF program header table");
    bounds(b,shoff,uint64_t(shent)*shcnt,"ELF section header table");
    struct Load {uint32_t off,addr,file,mem;};
    std::vector<Load> loads;
    uint64_t base=UINT64_MAX, fileEnd=0, memEnd=0;
    for(uint32_t i=0;i<phcnt;++i) {
        uint64_t p=uint64_t(phoff)+32u*i;
        uint32_t type=u32(b,p),off=u32(b,p+4),addr=u32(b,p+8);
        uint32_t filesz=u32(b,p+16),memsz=u32(b,p+20);
        must(type!=3,"PT_INTERP not supported by SIDBOX");
        if(type==2){
            must(memsz>=filesz && filesz%8==0,"Invalid PT_DYNAMIC segment");
            bounds(b,off,filesz,"PT_DYNAMIC entries");
            for(uint64_t t=off;t<off+filesz;t+=8)
                must(u32(b,t)!=1 && u32(b,t)!=7 && u32(b,t)!=23,
                     "Unsupported dynamic dependency/relocation tag");
        }
        if(type!=1) continue;
        must(filesz<=memsz,"PT_LOAD filesz exceeds memsz");
        bounds(b,off,filesz,"PT_LOAD bytes");
        base=std::min(base,uint64_t(addr));
        fileEnd=std::max(fileEnd,uint64_t(addr)+filesz);
        memEnd=std::max(memEnd,uint64_t(addr)+memsz);
        loads.push_back({off,addr,filesz,memsz});
    }
    must(!loads.empty() && fileEnd>base && memEnd>base &&
         fileEnd-base<=256u*1024u && memEnd-base<=6u*1024u*1024u,
         "PT_LOAD spans violate SIDBOX limits");
    Elf elf; elf.base=checkedU32(base,"ELF link base"); elf.entry=entry;
    elf.memSpan=checkedU32(memEnd-base,"ELF mem span");
    elf.image.resize(static_cast<size_t>(fileEnd-base));
    Bytes used(elf.image.size());
    for(auto l:loads) {
        uint64_t out=uint64_t(l.addr)-base;
        must(out+l.file<=elf.image.size(),"PT_LOAD output exceeds image");
        for(uint64_t j=0;j<l.file;++j) {
            auto idx=static_cast<size_t>(out+j);
            must(!used[idx] || elf.image[idx]==b[l.off+j],"Overlapping PT_LOAD data conflict");
            used[idx]=1; elf.image[idx]=b[l.off+j];
        }
    }
    std::vector<Sec> sections;
    for(uint32_t i=0;i<shcnt;++i) {
        uint64_t p=uint64_t(shoff)+40*i;
        sections.push_back({u32(b,p),u32(b,p+4),u32(b,p+12),u32(b,p+16),u32(b,p+20),u32(b,p+36)});
    }
    const Sec &shnames=sections[shstr];
    bounds(b,shnames.off,shnames.size,"section string table");
    Bytes names(b.begin()+shnames.off,b.begin()+shnames.off+shnames.size);
    bool foundStack=false;
    for(auto s:sections) {
        std::string name=nameOf(names,s.name);
        if(name==".stack") {
            must(!foundStack,"Multiple ELF .stack sections"); foundStack=true;
            must(s.type==8 && s.size==expectedStack &&
                 uint64_t(s.addr)+s.size==memEnd && s.addr>=fileEnd,
                 "ELF .stack reservation does not match packed private-PSP stack");
            elf.stackSize=s.size;
        }
        bool rel=(name.rfind(".rel.dyn",0)==0 || name.rfind(".rela.dyn",0)==0 ||
                  name.rfind(".rel.plt",0)==0 || name.rfind(".rela.plt",0)==0);
        if(!rel) continue;
        must(name.rfind(".rel.dyn",0)==0 && s.type==9 && s.entsize==8 && s.size%8==0,
             "Unexpected dynamic relocation section "+name);
        bounds(b,s.off,s.size,"ELF .rel.dyn");
        for(uint64_t j=s.off;j<s.off+uint64_t(s.size);j+=8) {
            uint32_t addr=u32(b,j),info=u32(b,j+4);
            must(info==23,"Unsupported dynamic relocation (expected R_ARM_RELATIVE, symbol 0)");
            must(addr>=base && uint64_t(addr)+4<=fileEnd,"Dynamic relocation outside initialised image");
            uint32_t site=addr-elf.base;
            must(site%4==0,"Unaligned ELF relocation site");
            elf.sites.push_back(site);
        }
    }
    if(expectedStack>0) must(foundStack,"ELF missing private-PSP .stack");
    std::sort(elf.sites.begin(),elf.sites.end());
    must(!elf.sites.empty(),"ELF missing dynamic R_ARM_RELATIVE entries");
    must(std::adjacent_find(elf.sites.begin(),elf.sites.end())==elf.sites.end(),
         "Duplicate ELF dynamic relocation sites");
    must((entry&1u) && uint64_t(entry&~1u)>=base && uint64_t(entry&~1u)<fileEnd,
         "ELF Thumb entry point outside initialised image");
    return elf;
}
void crosscheck(const Elf &elf,const App &app) {
    auto h=app.h;
    must(elf.base==h.linkBase,"ELF/PT_LOAD base differs from SBAPV2 link base");
    must(elf.entry==uint32_t(uint64_t(elf.base)+h.entryOffset),"ELF entry differs from .app entry");
    must(elf.image==app.image,"Packed image bytes differ from ELF PT_LOAD image");
    must(elf.sites==app.sites,"Packed relocation sites differ from ELF .rel.dyn records");
    must(elf.stackSize==h.stack,"ELF private stack differs from V2 header stack");
    must(aligned32(uint64_t(elf.memSpan)+h.heap)==h.memorySize,
         "Packed memory reservation differs from ELF memspan + heap");
}
struct RebaseResult {uint32_t loadBase=0,entry=0, first=0,last=0;uint64_t hash=0;};
uint64_t fnv64(const Bytes &v) {
    uint64_t h=14695981039346656037ull;
    for(auto c:v){h^=c;h*=1099511628211ull;}
    return h;
}
RebaseResult simulate(const App &app,uint32_t loadBase,bool verbose) {
    const Header &h=app.h;
    must(loadBase%32==0,"Simulated load base must be 32-byte aligned");
    must(loadBase>=0xD0000000u && loadBase<0xD0600000u &&
         h.memorySize<=0xD0600000u-loadBase,"Simulated image does not fit SIDBOX applet SDRAM");
    Bytes memory(h.memorySize,0); // Emulate loader zeroing reserved BSS/stack/heap.
    std::copy(app.image.begin(),app.image.end(),memory.begin());
    for(uint32_t site:app.sites){
        uint32_t old=u32(memory,site),thumb=old&1u,target=old&~1u;
        must(target>=h.linkBase,"Relocation pointer below V2 link base at "+hex(site));
        uint32_t offset=target-h.linkBase;
        must(offset<h.memorySize,"Relocation pointer outside applet memory at "+hex(site));
        uint32_t relocated=(loadBase+offset)|thumb;
        put32(memory,site,relocated);
        // Undo relative to the simulated load base, checking Thumb preservation.
        must((relocated&1u)==thumb && ((relocated&~1u)-loadBase)==offset,
             "Rebased pointer changed relative target at "+hex(site));
        if(verbose) std::cout << "    +" << hex(site) << "  " << hex(old) << " -> " << hex(relocated)
                              << "  (target offset +" << hex(offset) << ")\n";
    }
    uint32_t entry=loadBase+h.entryOffset;
    must((entry&1u) && (entry&~1u)>=loadBase &&
         (entry&~1u)-loadBase<h.imageSize,"Invalid rebased Thumb entry");
    RebaseResult r; r.loadBase=loadBase; r.entry=entry;
    r.first=u32(memory,app.sites.front()); r.last=u32(memory,app.sites.back());
    r.hash=fnv64(memory); return r;
}
uint32_t parseHex(const std::string &s) {
    size_t used=0; unsigned long long n=0;
    try { n=std::stoull(s,&used,0); }
    catch(const std::exception &) { throw Error("Invalid --load-base: "+s); }
    must(used==s.size() && n<=UINT32_MAX,"Invalid --load-base: "+s);
    return uint32_t(n);
}
struct Stats { uint32_t image=0,memory=0,reloc=0,heap=0,stack=0; };
Stats inspectPair(const std::string &elfName,const std::string &appName,
                  uint32_t newBase,bool verbose,const std::string &caption) {
    App a=parseApp(readFile(appName));
    Elf e=parseElf(readFile(elfName),a.h.stack);
    crosscheck(e,a);
    must(newBase!=a.h.linkBase,"--load-base must differ from the ELF link base to test actual rebasing");
    std::cout << "\n" << caption << ": ELF + V2 .app MATCH\n"
              << "  ELF:  " << elfName << "\n"
              << "  APP:  " << appName << "\n"
              << "  Link base:     " << hex(a.h.linkBase) << "\n"
              << "  Image bytes:   " << a.h.imageSize << "  (CRC32 " << hex(a.h.crc) << ")\n"
              << "  Reserved RAM:  " << a.h.memorySize << " bytes ("
              << a.h.heap << " heap, " << a.h.stack << " private stack)\n"
              << "  Runtime relocs:" << a.h.relocCount << " x R_ARM_RELATIVE\n"
              << "  Thumb entry:   " << hex(e.entry) << "\n";
    auto original=simulate(a,a.h.linkBase,verbose);
    auto changed=simulate(a,newBase,verbose);
    std::cout << "  Loader simulation (host only):\n"
              << "    At link base " << hex(original.loadBase) << ": entry " << hex(original.entry) << "  OK\n"
              << "    At new base  " << hex(changed.loadBase) << ": entry " << hex(changed.entry) << "  OK\n"
              << "    Relocation targets/Thumb bits preserved: " << a.sites.size() << "/" << a.sites.size() << "\n"
              << "    Image CRC, section bytes, stack/heap and relocation offsets: OK\n";
    return {a.h.imageSize,a.h.memorySize,a.h.relocCount,a.h.heap,a.h.stack};
}
void usage() {
    std::cout << "CGARM Stage 5 — host-side V2 ELF/.app verification + loader-rebase simulation\n"
              << "Usage: cgarm-v2-verify ELF FILE.app [--load-base 0xD0100000] [--reference LLVM.elf LLVM.app] [--verbose]\n"
              << "Reads only. Does not generate/modify files, execute ARM code or flash SIDBOX.\n";
}
}
int main(int argc,char **argv) {
    try {
        if(argc==2 && std::string(argv[1])=="--help") {usage();return 0;}
        if(argc<3){usage();return 2;}
        std::string elfFile=argv[1],appFile=argv[2],refElf,refApp;
        uint32_t loadBase=0xD0100000u; bool verbose=false;
        for(int i=3;i<argc;++i){
            std::string s=argv[i];
            if(s=="--load-base") {must(i+1<argc,"Missing --load-base value");loadBase=parseHex(argv[++i]);}
            else if(s=="--reference") {
                must(i+2<argc,"--reference requires LLVM.elf and LLVM.app");
                refElf=argv[++i]; refApp=argv[++i];
            } else if(s=="--verbose") verbose=true;
            else throw Error("Unknown argument: "+s);
        }
        auto ours=inspectPair(elfFile,appFile,loadBase,verbose,"CGARM candidate");
        if(!refElf.empty()) {
            auto llvm=inspectPair(refElf,refApp,loadBase,verbose,"LLVM reference");
            std::cout << "\nLinker comparison (distinct layout is normal):\n"
                      << "  Image bytes:     CGARM="<<ours.image<<" LLVM="<<llvm.image<<"\n"
                      << "  Reserved memory: CGARM="<<ours.memory<<" LLVM="<<llvm.memory<<"\n"
                      << "  Relocations:     CGARM="<<ours.reloc<<" LLVM="<<llvm.reloc<<"\n";
            must(ours.heap==llvm.heap && ours.stack==llvm.stack,
                 "CGARM/LLVM requested heap or stack differs");
            std::cout << "  Heap/private stack requests: MATCH\n";
        }
        std::cout << "\nPASS: ELF/.app parity, loader rebasing and configured RAM checks.\n"
                  << "NOT PROVEN: ARM instruction semantics, ABI compatibility, real device execution.\n";
        return 0;
    } catch(const std::exception &e) {
        std::cerr << "CGARM Stage 5 verification FAILED: " << e.what() << "\n";
        return 1;
    }
}
