// CGARM Stage 17: COMMON allocation provenance, bounded mergeable matching and strict relocation ledger.
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
#include <map>
#include <set>
#include <filesystem>
#include <cctype>

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
// Archive members are read in memory, never extracted to the filesystem.
std::map<std::string,Bytes> virtualArchiveObjects14;
Bytes readFile(const std::string &path) {
    auto virtualObject=virtualArchiveObjects14.find(path);
    if(virtualObject!=virtualArchiveObjects14.end())return virtualObject->second;
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

// Stage 6: source-object based machine-code parity (never executes ARM instructions).
// Reuse Stage 5's strictly read-only ELF/.app verification and loader rebasing.
struct Section6 {
    std::string name;
    uint32_t type=0, flags=0, address=0, offset=0, size=0, link=0, info=0, entrySize=0;
};
struct Symbol6 {
    std::string name;
    uint32_t addr=0, size=0;
    uint16_t section=0;
    uint8_t type=0;
};
struct ElfView6 {
    Bytes bytes;
    std::vector<Section6> sections;
    std::vector<Symbol6> functions;
    uint32_t entry=0;
    uint32_t type=0;
    std::string label;
};
uint8_t byte6(const Bytes& d,uint64_t p){ bounds(d,p,1,"byte");return d[size_t(p)]; }
std::string str6(const Bytes& b,uint64_t off,uint64_t size,uint32_t idx){
    must(idx<size,"ELF invalid string-table index");
    bounds(b,off,size,"ELF string table");
    uint64_t pos=off+idx,end=off+size;
    auto it=std::find(b.begin()+pos,b.begin()+end,uint8_t(0));
    must(it!=b.begin()+end,"Unterminated ELF name");
    return std::string(b.begin()+pos,it);
}
ElfView6 inspect6(const std::string& file,uint32_t wantType){
    ElfView6 e; e.label=file;e.bytes=readFile(file);
    const auto &b=e.bytes;
    bounds(b,0,52,"ELF32 header");
    must(b[0]==127 && b[1]=='E' && b[2]=='L' && b[3]=='F' && b[4]==1 && b[5]==1 && b[6]==1,
         file+": expected little-endian ELF32");
    e.type=u16(b,16);e.entry=u32(b,24);
    must(e.type==wantType && u16(b,18)==40,file+": wrong ELF type/CPU");
    const uint32_t off=u32(b,32);
    const uint16_t stride=u16(b,46),count=u16(b,48),nameIndex=u16(b,50);
    must(stride==40 && count>0 && count<4096 && nameIndex<count,file+": invalid sections");
    bounds(b,off,uint64_t(count)*stride,"ELF section headers");
    for(unsigned i=0;i<count;++i){
        uint64_t h=uint64_t(off)+i*40u;
        Section6 s;
        s.name=std::to_string(u32(b,h)); // replace with resolved name below
        s.type=u32(b,h+4);s.flags=u32(b,h+8);s.address=u32(b,h+12);
        s.offset=u32(b,h+16);s.size=u32(b,h+20);s.link=u32(b,h+24);
        s.info=u32(b,h+28);s.entrySize=u32(b,h+36);
        if(s.type!=8) bounds(b,s.offset,s.size,"ELF section payload");
        e.sections.push_back(s);
    }
    const Section6 &shstr=e.sections[nameIndex];
    must(shstr.type==3,file+": invalid section-name string table");
    for(auto &s:e.sections){
        uint32_t n=static_cast<uint32_t>(std::stoul(s.name));
        s.name=str6(b,shstr.offset,shstr.size,n);
    }
    for(const auto &tab:e.sections){
        if(tab.type!=2)continue; // SHT_SYMTAB; DYNSYM alone can't map local functions
        must(tab.link<e.sections.size() && e.sections[tab.link].type==3 &&
             tab.entrySize==16 && tab.size%16==0,file+": malformed symbol table");
        const auto &strings=e.sections[tab.link];
        for(uint32_t i=0;i<tab.size/16;++i){
            uint64_t o=uint64_t(tab.offset)+i*16u;
            Symbol6 s;
            s.name=str6(b,strings.offset,strings.size,u32(b,o));
            s.addr=u32(b,o+4);s.size=u32(b,o+8);
            s.type=byte6(b,o+12)&15u;s.section=u16(b,o+14);
            if(s.type==2 && s.section>0 && s.section<e.sections.size() &&
               s.size>0 && !s.name.empty())e.functions.push_back(std::move(s));
        }
    }
    return e;
}
struct Rel6{uint32_t at=0,type=0;std::string symbol;};
struct SourceFunction6{
    std::string name,section,from;
    Bytes original;
    uint32_t start=0,size=0;
    std::vector<Rel6> relocs;
};
std::vector<SourceFunction6> inputFunctions6(const ElfView6& e){
    std::map<uint32_t,std::vector<Rel6>> relocations;
    for(const auto &r:e.sections){
        if(r.type!=9 && r.type!=4)continue;
        must(r.info<e.sections.size(),e.label+": bad relocation target section");
        uint32_t sz=r.type==9 ? 8u:12u;
        must(r.entrySize>=sz && r.entrySize>0 && r.size%r.entrySize==0,
             e.label+": invalid relocation entry size");
        for(uint32_t i=0;i<r.size/r.entrySize;++i){
            uint64_t o=uint64_t(r.offset)+i*r.entrySize;
            uint32_t info=u32(e.bytes,o+4),symIndex=info>>8;
            must(r.link<e.sections.size(),e.label+": invalid relocation symbol table");
            const auto &syms=e.sections[r.link];
            must(syms.type==2 && syms.entrySize==16 && syms.link<e.sections.size(),
                 e.label+": unsupported relocation symbol table");
            must(uint64_t(symIndex)*16+16<=syms.size,e.label+": relocation symbol out of range");
            const auto &strtab=e.sections[syms.link];
            must(strtab.type==3,e.label+": invalid relocation symbol names");
            uint64_t so=uint64_t(syms.offset)+uint64_t(symIndex)*16;
            std::string target=str6(e.bytes,strtab.offset,strtab.size,u32(e.bytes,so));
            relocations[r.info].push_back({u32(e.bytes,o),info&255u,target});
        }
    }
    std::vector<SourceFunction6> funcs;
    for(const auto &sym:e.functions){
        const auto &section=e.sections[sym.section];
        if(section.type!=1 || !(section.flags&4u) || section.name.rfind(".text",0)!=0)
            continue;
        uint32_t start=sym.addr & ~1u;
        if(start>section.size || sym.size>section.size-start)continue;
        SourceFunction6 f;
        f.name=sym.name;f.section=section.name;f.from=e.label;f.start=start;f.size=sym.size;
        f.original=Bytes(e.bytes.begin()+section.offset+start,
                         e.bytes.begin()+section.offset+start+sym.size);
        for(auto r:relocations[sym.section])if(r.at>=start && uint64_t(r.at)+4<=uint64_t(start)+f.size){
            r.at-=start;f.relocs.push_back(r);
        }
        funcs.push_back(std::move(f));
    }
    return funcs;
}
struct Hit6 {uint32_t addr=0;Bytes bytes;};
std::vector<Hit6> findCg6(const ElfView6& cg,const SourceFunction6 &f){
    std::vector<Hit6> hits;
    for(const auto &s:cg.sections){
        if(s.name!=f.section || s.type!=1 || s.size<f.start+f.size || !(s.flags&4u)) continue;
        Bytes bytes(cg.bytes.begin()+s.offset+f.start,cg.bytes.begin()+s.offset+f.start+f.size);
        hits.push_back({s.address+f.start,std::move(bytes)});
    }
    return hits;
}
std::vector<Hit6> findLLVM6(const ElfView6& llvm,const SourceFunction6 &f){
    std::vector<Hit6> hits;
    for(const auto &sy:llvm.functions){
        if(sy.name!=f.name || sy.size!=f.size)continue;
        uint32_t addr=sy.addr&~1u;
        for(const auto &sec:llvm.sections){
            if(!(sec.flags&4u) || sec.type!=1 || addr<sec.address ||
               uint64_t(addr)+f.size>uint64_t(sec.address)+sec.size)continue;
            uint64_t off=uint64_t(sec.offset)+addr-sec.address;
            hits.push_back({addr,Bytes(llvm.bytes.begin()+off,llvm.bytes.begin()+off+f.size)});
        }
    }
    return hits;
}
// A function-symbol destination is stronger evidence than an executable-range check.
// Not every compiler-emitted relocation has a named function (local section
// symbols, Thumb veneers and generated stubs are possible), so count coverage.
std::vector<uint32_t> cgTargets6(const ElfView6 &e,const std::string& name){
    std::vector<uint32_t> addresses;
    if(name.empty())return addresses;
    for(const auto &s:e.sections){
        if(s.name==".text."+name && (s.flags&4u) && s.type==1)
            addresses.push_back(s.address);
    }
    return addresses;
}
std::vector<uint32_t> llvmTargets6(const ElfView6& e,const std::string& name){
    std::vector<uint32_t> addresses;
    if(name.empty())return addresses;
    for(const auto &s:e.functions){
        if(s.name==name)addresses.push_back(s.addr&~1u);
    }
    return addresses;
}
bool targetExec6(const ElfView6 &e,uint32_t target){
    for(const auto &sec:e.sections){
        if(!(sec.flags&4u) || sec.type!=1)continue;
        if(target>=sec.address && uint64_t(target)<uint64_t(sec.address)+sec.size)return true;
    }
    return false;
}
// ARM Thumb-2 T4 BL/B.W: decode signed 25-bit S:I1:I2:imm10:imm11:0.
uint32_t branchTarget6(const Bytes& b,uint32_t byteOff,uint32_t place,uint32_t kind){
    must(uint64_t(byteOff)+4<=b.size(),"Branch patch out of bounds");
    uint16_t hi=uint16_t(b[byteOff]) | uint16_t(b[byteOff+1])<<8;
    uint16_t lo=uint16_t(b[byteOff+2]) | uint16_t(b[byteOff+3])<<8;
    must((hi&0xf800u)==0xf000u,"Invalid Thumb-2 branch upper halfword");
    if(kind==10) must((lo&0xd000u)==0xd000u,"THM_CALL is not Thumb BL");
    else if(kind==30)must((lo&0xd000u)==0x9000u,"THM_JUMP24 is not Thumb B.W");
    else throw Error("Unsupported Thumb branch relocation");
    uint32_t S=(hi>>10)&1u,J1=(lo>>13)&1u,J2=(lo>>11)&1u;
    uint32_t I1=1u^(J1^S),I2=1u^(J2^S);
    uint32_t imm=(S<<24)|(I1<<23)|(I2<<22)|((hi&0x3ffu)<<12)|((lo&0x7ffu)<<1);
    int32_t delta=static_cast<int32_t>((imm^0x01000000u)-0x01000000u);
    int64_t t=int64_t(place)+4+delta;
    must(t>=0 && t<=UINT32_MAX,"Thumb branch target overflow");
    return uint32_t(t);
}
struct Gap8 {
    std::string source, name, section, reason;
    size_t cgSections=0, cgHits=0, llvmNamed=0, llvmHits=0;
};
struct Counts6{
    size_t sources=0,matched=0,unmaskedBytes=0,linkPatches=0,branches=0,namedBranches=0,skipped=0;
    std::map<std::string,size_t> problems;
    std::vector<Gap8> gaps;
};
std::vector<uint8_t> relocationMask6(const SourceFunction6& f){
    std::vector<uint8_t> mask(f.size);
    for(auto r:f.relocs){
        for(uint32_t i=0;i<4;++i)mask[r.at+i]=1;
    }
    return mask;
}
// Each supported comparison uses the SAME GCC section from the provided ET_REL.
// Linker-written bytes are masked, never mistaken for compiler-byte differences.
Counts6 compareObjects6(const ElfView6& cg,const ElfView6& llvm,
                        const std::vector<std::string>& objectFiles,bool verbose){
    Counts6 c;
    for(const auto &path:objectFiles){
        const auto object=inspect6(path,1);
        auto funcs=inputFunctions6(object);
        c.sources+=funcs.size();
        for(const auto &f:funcs){
            auto cgHits=findCg6(cg,f),llHits=findLLVM6(llvm,f);
            if(cgHits.size()!=1 || llHits.size()!=1){
                ++c.skipped;
                Gap8 gap;
                gap.source=path;gap.name=f.name;gap.section=f.section;
                gap.cgHits=cgHits.size();gap.llvmHits=llHits.size();
                for(const auto& s:cg.sections)
                    if(s.name==f.section && s.type==1 && (s.flags&4u))++gap.cgSections;
                for(const auto& s:llvm.functions)
                    if(s.name==f.name)++gap.llvmNamed;
                if(cgHits.empty() && llHits.empty())gap.reason="neither output is matched by current methods";
                else if(cgHits.empty())gap.reason="CGARM source section not matched";
                else if(llHits.empty())gap.reason="LLVM named function not matched";
                else gap.reason="multiple possible matches (ambiguous)";
                c.problems[gap.reason]++;
                c.gaps.push_back(std::move(gap));
                continue;
            }
            const Hit6 &a=cgHits.front(),&b=llHits.front();
            const auto mask=relocationMask6(f);
            size_t unchanged=0;
            for(size_t i=0;i<f.size;++i){
                if(mask[i])continue;
                if(f.original[i]!=a.bytes[i] || f.original[i]!=b.bytes[i]){
                    throw Error("NON-RELOCATION INSTRUCTION DIFFERENCE: "+f.from+":"+f.name+
                                " at byte +"+std::to_string(i)+
                                " (requires manual inspection before hardware testing)");
                }
                ++unchanged;
            }
            c.unmaskedBytes+=unchanged;
            ++c.matched;
            for(const auto &r:f.relocs){
                ++c.linkPatches;
                if(r.type!=10 && r.type!=30)continue;
                uint32_t atCg=a.addr+r.at,atLl=b.addr+r.at;
                uint32_t destCg=branchTarget6(a.bytes,r.at,atCg,r.type);
                uint32_t destLl=branchTarget6(b.bytes,r.at,atLl,r.type);
                must(targetExec6(cg,destCg),"CGARM branch from "+f.name+
                     " to non-executable target "+hex(destCg));
                must(targetExec6(llvm,destLl),"LLVM branch from "+f.name+
                     " to non-executable target "+hex(destLl));
                ++c.branches;
                const auto cgNamed=cgTargets6(cg,r.symbol), llNamed=llvmTargets6(llvm,r.symbol);
                if(cgNamed.size()==1 && llNamed.size()==1){
                    must(destCg==cgNamed[0],"CGARM Thumb branch "+f.name+" -> "+r.symbol+
                         " landed at "+hex(destCg)+", not "+hex(cgNamed[0]));
                    must(destLl==llNamed[0],"LLVM Thumb branch "+f.name+" -> "+r.symbol+
                         " landed at "+hex(destLl)+", not "+hex(llNamed[0]));
                    ++c.namedBranches;
                }
                if(verbose)std::cout<<"  branch "<<f.name<<" -> "<<r.symbol<<" +"<<r.at
                    <<" CGARM="<<hex(destCg)<<" LLVM="<<hex(destLl)
                    <<(cgNamed.size()==1 && llNamed.size()==1 ? " (named function OK)" : " (executable range OK)")<<"\n";
            }
            if(verbose)std::cout<<"  verified function "<<f.name<<" ("<<f.size
                    <<" bytes, "<<unchanged<<" unchanged, "<<f.relocs.size()<<" patch sites)\n";
        }
    }
    return c;
}

// Stage 7: prove that patched PC-relative values and data/GOT pointers
// actually refer to the SAME original symbol in BOTH independent links.
// A range-only check is insufficient: a wrong but in-range address is a bug.
struct Skipped8 {
    std::string source, section, anchor, target, reason;
    uint32_t offset=0, kind=0;
    uint8_t targetType=0;
};
struct Result7 {
    size_t references=0, checked=0, dataPointers=0, pcRelative=0, gotPointers=0, gotBases=0;
    size_t originalObjects=0, recoveredRawSection=0, recoveredLocal=0, recoveredHeap=0;
    std::map<std::string,size_t> skipped;
    std::map<std::string,size_t> skippedByType;
    std::vector<Skipped8> unresolved;
};
std::string relocationName8(uint32_t kind) {
    switch(kind){case 2:return "ABS32";case 3:return "REL32";
        case 25:return "BASE_PREL";case 26:return "GOT_BREL";
        default:return "ARM_"+std::to_string(kind);}
}
std::string symbolType8(uint8_t type) {
    switch(type){case 0:return "NOTYPE";case 1:return "OBJECT";
        case 2:return "FUNC";case 3:return "SECTION";
        default:return "TYPE_"+std::to_string(type);}
}
void unresolved8(Result7& result,const std::string& source,const Section6& sec,
                 uint32_t offset,uint32_t kind,const Symbol6& target,
                 const std::string& anchor,const std::string& reason) {
    ++result.skipped[reason];
    ++result.skippedByType[relocationName8(kind)+" -> "+symbolType8(target.type)];
    result.unresolved.push_back({source,sec.name,anchor,target.name,reason,
                                 offset,kind,target.type});
}
struct Ref7 { uint32_t offset=0,kind=0; Symbol6 target; };
struct Anchor7 { Symbol6 symbol; uint32_t delta=0; };
std::vector<Symbol6> symbols7(const ElfView6& obj) {
    std::vector<Symbol6> out;
    for(const auto& tab:obj.sections) {
        if(tab.type!=2)continue;
        must(tab.link<obj.sections.size() && obj.sections[tab.link].type==3 &&
             tab.entrySize==16 && tab.size%16==0,"Stage7: bad source symbol table");
        const auto& st=obj.sections[tab.link];
        for(uint32_t i=0;i<tab.size/16;++i) {
            uint64_t off=uint64_t(tab.offset)+i*16;
            Symbol6 sym;
            sym.name=str6(obj.bytes,st.offset,st.size,u32(obj.bytes,off));
            sym.addr=u32(obj.bytes,off+4);sym.size=u32(obj.bytes,off+8);
            sym.type=byte6(obj.bytes,off+12)&15u;sym.section=u16(obj.bytes,off+14);
            out.push_back(std::move(sym));
        }
    }
    return out;
}
// A source input symbol must identify a unique address in each ELF.
// CGARM preserves individual input sections; LLVM can merge them, so use
// its retained STT_FUNC/STT_OBJECT symbol (including local data symbols).
std::vector<uint32_t> locate7(const ElfView6& out,const ElfView6& src,
                              const Symbol6& symbol,bool cgarm) {
    std::vector<uint32_t> found;
    // The linker script defines this at the end of the private .stack.
    // It is NOT a normal C symbol and may be absent from either .symtab.
    if(symbol.name=="__v2_heap_start__" && symbol.section==0) {
        for(const auto &s:out.sections)if(s.name==".stack" && s.type==8 && (s.flags&2u)) {
            must(uint64_t(s.address)+s.size<=UINT32_MAX,"Stage9 heap-start address overflow");
            found.push_back(s.address+s.size);
        }
        return found;  // Do not guess if the .stack is absent or repeated.
    }
    if(symbol.section==0 || symbol.section>=src.sections.size()) {
        // Undefined named references are permitted, if the link resolves them.
        if(symbol.name.empty())return found;
        if(cgarm) {
            for(const auto& s:out.sections)
                if(s.name==".text."+symbol.name || s.name==".data."+symbol.name ||
                   s.name==".bss."+symbol.name || s.name==".rodata."+symbol.name)
                    found.push_back(s.address);
        } else {
            // Cross-object global references can have SHN_UNDEF in the source
            // but are defined by a different input object. Read the final
            // symbol table instead of assuming they must be functions.
            for(const auto& tab:out.sections)if(tab.type==2) {
                must(tab.link<out.sections.size() && tab.entrySize==16 &&
                     out.sections[tab.link].type==3 && tab.size%16==0,
                     "Stage7: invalid LLVM symbol table");
                const auto& st=out.sections[tab.link];
                for(uint32_t i=0;i<tab.size/16;++i){
                    uint64_t p=uint64_t(tab.offset)+i*16;
                    uint8_t t=byte6(out.bytes,p+12)&15u;
                    if(t!=1 && t!=2)continue;
                    if(u16(out.bytes,p+14)==0)continue;
                    if(str6(out.bytes,st.offset,st.size,u32(out.bytes,p))==symbol.name)
                        found.push_back(u32(out.bytes,p+4)&~(t==2?1u:0u));
                }
            }
        }
        std::sort(found.begin(),found.end());
        found.erase(std::unique(found.begin(),found.end()),found.end());
        return found;
    }
    const auto &section=src.sections[symbol.section];
    if(cgarm) {
        for(const auto& s:out.sections)
            if(s.name==section.name && (s.flags&2u))
                found.push_back(s.address+(symbol.addr&~(symbol.type==2?1u:0u)));
    } else {
        if(symbol.name.empty() || (symbol.type!=1 && symbol.type!=2))return found;
        // At this point only STT_FUNC is recorded in .functions. Data symbols
        // need an independent scan of the LLVM .symtab.
        for(const auto& s:out.functions)
            if(s.name==symbol.name && symbol.type==2)
                found.push_back(s.addr&~1u);
        if(symbol.type==1) {
            // Collect named STT_OBJECT symbols from the real LLVM .symtab.
            for(const auto& tab:out.sections)if(tab.type==2) {
                must(tab.link<out.sections.size() && tab.entrySize==16,
                     "Stage7: invalid LLVM symbol table");
                const auto &st=out.sections[tab.link];
                for(uint32_t i=0;i<tab.size/16;++i) {
                    uint64_t p=uint64_t(tab.offset)+i*16;
                    if((byte6(out.bytes,p+12)&15u)!=1)continue;
                    if(str6(out.bytes,st.offset,st.size,u32(out.bytes,p))==symbol.name)
                        found.push_back(u32(out.bytes,p+4));
                }
            }
        }
    }
    std::sort(found.begin(),found.end());
    found.erase(std::unique(found.begin(),found.end()),found.end());
    return found;
}
// Match input ET_REL relocation to a source function/object whose bytes
// contain the reference, so merged LLVM output can still be located.
std::vector<Anchor7> anchors7(const std::vector<Symbol6>& syms,
                              uint32_t section,uint32_t relocOffset) {
    std::vector<Anchor7> out;
    for(const auto& s:syms) {
        if(s.section!=section || (s.type!=1 && s.type!=2) || !s.size)continue;
        uint32_t value=s.addr&~(s.type==2?1u:0u);
        if(relocOffset>=value && uint64_t(relocOffset)+4<=uint64_t(value)+s.size)
            out.push_back({s,relocOffset-value});
    }
    return out;
}
uint32_t word7(const ElfView6 &elf,uint32_t addr){
    for(const auto& s:elf.sections) {
        if(s.type==1 && (s.flags&2u) && addr>=s.address &&
           uint64_t(addr)+4<=uint64_t(s.address)+s.size)
            return u32(elf.bytes,uint64_t(s.offset)+addr-s.address);
    }
    throw Error("Stage7: address "+hex(addr)+" is not initialised ELF data");
}
std::vector<uint32_t> gotBases7(const ElfView6& elf){
    std::vector<uint32_t> v;
    for(const auto &s:elf.sections)
        if(s.name==".got" && s.type==1 && (s.flags&2u))v.push_back(s.address);
    return v;
}
// With an STT_SECTION symbol, the reference identifies a section rather than
// a named variable. Find a unique object/function at the exact target offset.
std::vector<uint32_t> destinations7(const ElfView6 &out,const ElfView6 &source,
                              const std::vector<Symbol6>& syms,
                              const Symbol6 &target,uint32_t addend,bool cgarm){
    auto direct=locate7(out,source,target,cgarm);
    if(!direct.empty())return direct;
    if(target.type!=3 || target.section==0 || target.section>=source.sections.size())return {};
    std::vector<uint32_t> found;
    for(const auto& s:syms){
        if((s.type!=1 && s.type!=2) || s.section!=target.section || s.name.empty())continue;
        if((s.addr&~(s.type==2?1u:0u)) != uint32_t(target.addr+addend))continue;
        auto addr=locate7(out,source,s,cgarm);
        found.insert(found.end(),addr.begin(),addr.end());
    }
    std::sort(found.begin(),found.end());
    found.erase(std::unique(found.begin(),found.end()),found.end());
    return found;
}
// Stage 8: conservative identity recovery for anonymous STT_SECTION targets.
// The complete non-executable source section must be unmodified by linking,
// at least 16 bytes long, and occur at exactly one address in each output.
// This cannot identify linker-transformed data or sections with relocations:
// those remain UNVERIFIED. We never use a mere in-range target as proof.
struct RawMatch8 { bool unique=false; uint32_t address=0; size_t matches=0; };
bool isRelocatedInputSection8(const ElfView6& src,uint16_t index) {
    for(const auto& sec:src.sections)
        if((sec.type==9 || sec.type==4) && sec.info==index && sec.size>0)
            return true;
    return false;
}
RawMatch8 rawSection8(const ElfView6& out,const ElfView6& src,uint16_t index) {
    RawMatch8 result;
    if(index==0 || index>=src.sections.size())return result;
    const auto &needle=src.sections[index];
    if(needle.type!=1 || !(needle.flags&2u) || (needle.flags&4u) ||
       needle.size<16 || needle.size>256u*1024u || isRelocatedInputSection8(src,index))
        return result;
    bounds(src.bytes,needle.offset,needle.size,"Stage8 original section");
    std::set<uint32_t> matches;
    const auto first=src.bytes.begin()+needle.offset;
    const auto last=first+needle.size;
    for(const auto& s:out.sections){
        if(s.type!=1 || !(s.flags&2u) || s.size<needle.size)continue;
        bounds(out.bytes,s.offset,s.size,"Stage8 output section");
        auto begin=out.bytes.begin()+s.offset;
        const auto end=begin+s.size;
        for(auto p=std::search(begin,end,first,last);p!=end;
             p=std::search(p+1,end,first,last)) {
            uint64_t address=uint64_t(s.address)+static_cast<size_t>(p-begin);
            must(address<=UINT32_MAX,"Stage8 section address overflow");
            matches.insert(uint32_t(address));
            if(matches.size()>1)break;
        }
        if(matches.size()>1)break;
    }
    result.matches=matches.size();
    if(matches.size()==1){result.unique=true;result.address=*matches.begin();}
    return result;
}
bool recoverSectionTarget8(const ElfView6& cg,const ElfView6& llvm,
                           const ElfView6& src,const Symbol6& sym,uint32_t addend,
                           uint32_t& cgTarget,uint32_t& llvmTarget) {
    if(sym.type!=3 || sym.section==0 || sym.section>=src.sections.size())return false;
    uint64_t off=uint64_t(sym.addr)+addend;
    if(off>=src.sections[sym.section].size)return false;
    auto c=rawSection8(cg,src,sym.section);
    auto l=rawSection8(llvm,src,sym.section);
    if(!c.unique || !l.unique)return false;
    must(uint64_t(c.address)+off<=UINT32_MAX && uint64_t(l.address)+off<=UINT32_MAX,
         "Stage8 relocation target address overflow");
    cgTarget=c.address+uint32_t(off);llvmTarget=l.address+uint32_t(off);
    return true;
}

// Stage 9: uniquely identify the *part of a source section being referenced*.
// LLVM can merge string literals or combine independent input sections, so the
// whole original section need not occur byte-for-byte. NEVER use the patched
// pointer value to search for the expected target: that would be circular proof.
// Instead search ONLY original, linker-unmodified bytes from the ET_REL target.
struct LocalMatch9 {
    bool unique=false;
    uint32_t target=0;
    size_t matches=0;
};
bool hasInputRelocInWindow9(const ElfView6& src,uint16_t index,
                            uint32_t begin,uint32_t length){
    for(const auto &r:src.sections){
        if((r.type!=9 && r.type!=4) || r.info!=index || !r.entrySize)continue;
        const uint32_t stride=r.type==9?8u:12u;
        must(r.entrySize==stride && r.size%stride==0,
             "Stage9 invalid source relocation table stride");
        for(uint32_t i=0;i<r.size/stride;++i){
            uint32_t p=u32(src.bytes,uint64_t(r.offset)+uint64_t(i)*stride);
            if(uint64_t(p)<uint64_t(begin)+length && uint64_t(p)+4>begin)return true;
        }
    }
    return false;
}
LocalMatch9 locateWindow9(const ElfView6& out,const ElfView6& src,
                          uint16_t index,uint32_t targetOffset){
    LocalMatch9 result;
    if(!index || index>=src.sections.size())return result;
    const auto &s=src.sections[index];
    // Only immutable initialised data. Don't claim that zero-filled RAM or
    // instruction bytes have been uniquely identified through a byte search.
    if(s.type!=1 || !(s.flags&2u) || (s.flags&1u) || (s.flags&4u) ||
       s.size>256u*1024u || targetOffset>=s.size)return result;
    bounds(src.bytes,s.offset,s.size,"Stage9 source target section");
    const bool mergedString=(s.flags&0x30u)==0x30u; // SHF_MERGE|SHF_STRINGS
    // Candidate windows start at the actual referenced offset. An ELF merged
    // string section may lose neighbours or merge suffixes, so no prefix is
    // assumed to survive. For other read-only constants, also try a small
    // context window when the target is close to the section's end.
    struct Win{uint32_t begin,length;};
    std::vector<Win> windows;
    const uint32_t available=s.size-targetOffset;
    uint32_t forward=std::min<uint32_t>(available,48);
    if(mergedString){
        const auto start=src.bytes.begin()+s.offset+targetOffset;
        auto end=std::find(start,start+forward,uint8_t(0));
        if(end!=start+forward)forward=static_cast<uint32_t>(end-start)+1;
    }
    if(forward>=8)windows.push_back({targetOffset,forward});
    if(!mergedString){
        const uint32_t before=std::min<uint32_t>(targetOffset,16);
        if(before && before+forward>=12 && before+forward<=64)
            windows.push_back({targetOffset-before,before+forward});
    }
    // Longer signatures first, unique match in *both* independent outputs.
    // Never accept 1-4 byte coincidences as proof of symbol identity.
    std::sort(windows.begin(),windows.end(),[](const Win& a,const Win& b){return a.length>b.length;});
    for(const auto &w:windows){
        if(w.length<8 || hasInputRelocInWindow9(src,index,w.begin,w.length))continue;
        const auto first=src.bytes.begin()+s.offset+w.begin;
        const auto last=first+w.length;
        std::set<uint32_t> positions;
        for(const auto &output:out.sections){
            // LLVM's script merges .rodata* into executable .text.  The input
            // source is proven read-only, so searching an allocated output
            // section is safe; uniqueness remains mandatory.
            if(output.type!=1 || !(output.flags&2u) || output.size<w.length)continue;
            bounds(out.bytes,output.offset,output.size,"Stage9 output data section");
            auto b=out.bytes.begin()+output.offset,e=b+output.size;
            for(auto p=std::search(b,e,first,last);p!=e;
                p=std::search(p+1,e,first,last)){
                uint64_t addr=uint64_t(output.address)+static_cast<size_t>(p-b)+targetOffset-w.begin;
                must(addr<=UINT32_MAX,"Stage9 recovered target overflow");
                positions.insert(uint32_t(addr));
                if(positions.size()>1)break;
            }
            if(positions.size()>1)break;
        }
        // On an ambiguous window, try a different, independently anchored one.
        if(positions.size()==1){result.unique=true;result.target=*positions.begin();result.matches=1;return result;}
        result.matches=std::max(result.matches,positions.size());
    }
    return result;
}
bool recoverLocalTarget9(const ElfView6& cg,const ElfView6& llvm,
                         const ElfView6& src,const Symbol6& target,
                         uint32_t originalAddend,uint32_t& cgTarget,uint32_t& llTarget){
    // A named constant inside an input section can also have been folded away
    // from the ELF .symtab. Only use a local, defined symbol, never undefined
    // symbols or linker-provided values for this recovery path.
    if(target.section==0 || target.section>=src.sections.size())return false;
    if(target.type!=3 && target.type!=0 && target.type!=1)return false;
    const int64_t off=int64_t(target.addr)+int64_t(int32_t(originalAddend));
    if(off<0 || off>=src.sections[target.section].size)return false;
    auto c=locateWindow9(cg,src,target.section,uint32_t(off));
    auto l=locateWindow9(llvm,src,target.section,uint32_t(off));
    if(!c.unique || !l.unique)return false;
    cgTarget=c.target;llTarget=l.target;
    return true;
}

Result7 compareReferences7(const ElfView6& cg,const ElfView6& llvm,
                           const std::vector<std::string>& paths,bool verbose){
    Result7 result;
    for(const auto& path:paths){
        ElfView6 src=inspect6(path,1);++result.originalObjects;
        auto syms=symbols7(src);
        for(const auto& relsec:src.sections){
            if(relsec.type!=9 && relsec.type!=4)continue;
            must(relsec.info<src.sections.size() && relsec.link<src.sections.size(),
                 path+": relocation section indices invalid");
            const auto& input=src.sections[relsec.info];
            if(!(input.flags&2u) || input.type!=1)continue;
            const auto& symtab=src.sections[relsec.link];
            must(symtab.type==2 && symtab.entrySize==16 && symtab.link<src.sections.size(),
                 path+": invalid relocation symbol table");
            const auto& st=src.sections[symtab.link];
            uint32_t stride=relsec.type==9?8u:12u;
            must(relsec.entrySize==stride && relsec.size%stride==0,
                 path+": unexpected relocation record stride");
            for(uint32_t i=0;i<relsec.size/stride;++i){
                uint64_t ro=uint64_t(relsec.offset)+uint64_t(i)*stride;
                uint32_t offset=u32(src.bytes,ro),info=u32(src.bytes,ro+4);
                uint32_t kind=info&255u,symIndex=info>>8;
                if(kind!=2 && kind!=3 && kind!=25 && kind!=26)continue;
                ++result.references;
                must(uint64_t(offset)+4<=input.size,path+": relocation outside source section");
                must(uint64_t(symIndex)*16+16<=symtab.size,path+": symbol index outside table");
                uint64_t so=uint64_t(symtab.offset)+uint64_t(symIndex)*16;
                Symbol6 target;
                target.name=str6(src.bytes,st.offset,st.size,u32(src.bytes,so));
                target.addr=u32(src.bytes,so+4);target.size=u32(src.bytes,so+8);
                target.type=byte6(src.bytes,so+12)&15u;target.section=u16(src.bytes,so+14);
                auto anchors=anchors7(syms,relsec.info,offset);
                if(anchors.size()!=1){unresolved8(result,path,input,offset,kind,target,"",
                    "reference has no unique input function/object anchor");continue;}
                auto a=locate7(cg,src,anchors[0].symbol,true);
                auto b=locate7(llvm,src,anchors[0].symbol,false);
                if(a.size()!=1 || b.size()!=1){unresolved8(result,path,input,offset,kind,target,anchors[0].symbol.name,
                    "source anchor not uniquely resolved in both output ELFs");continue;}
                uint32_t cgPlace=a[0]+anchors[0].delta,llPlace=b[0]+anchors[0].delta;
                uint32_t cWord=word7(cg,cgPlace),lWord=word7(llvm,llPlace);
                uint32_t originalAddend=(relsec.type==9)?u32(src.bytes,uint64_t(input.offset)+offset):u32(src.bytes,ro+8);
                uint32_t cgTarget=0,llTarget=0;
                if(kind==25){
                    auto cGot=gotBases7(cg),lGot=gotBases7(llvm);
                    if(cGot.size()!=1 || lGot.size()!=1){unresolved8(result,path,input,offset,kind,target,anchors[0].symbol.name,
                        "GOT base absent or ambiguous");continue;}
                    must(uint32_t(cWord+cgPlace-originalAddend)==cGot[0],"CGARM BASE_PREL wrong in "+path+":"+anchors[0].symbol.name);
                    must(uint32_t(lWord+llPlace-originalAddend)==lGot[0],"LLVM BASE_PREL wrong in "+path+":"+anchors[0].symbol.name);
                    ++result.checked;++result.gotBases;
                    continue;
                }
                auto cDest=destinations7(cg,src,syms,target,originalAddend,true);
                auto lDest=destinations7(llvm,src,syms,target,originalAddend,false);
                bool recovered=false, recoveredByLocal=false;
                if(cDest.size()==1 && lDest.size()==1) {
                    cgTarget=cDest[0];llTarget=lDest[0];
                    if(target.name=="__v2_heap_start__")++result.recoveredHeap;
                } else if(recoverSectionTarget8(cg,llvm,src,target,originalAddend,cgTarget,llTarget)) {
                    recovered=true;
                } else if(recoverLocalTarget9(cg,llvm,src,target,originalAddend,cgTarget,llTarget)) {
                    recovered=true;recoveredByLocal=true;
                    ++result.recoveredLocal;
                } else {
                    unresolved8(result,path,input,offset,kind,target,anchors[0].symbol.name,
                        "target identity unavailable/ambiguous in output symbol tables");
                    continue;
                }
                if(recovered && !recoveredByLocal)++result.recoveredRawSection;
                if(kind==2 || kind==3){
                    uint32_t cEffective=kind==2?cWord:uint32_t(cWord+cgPlace);
                    uint32_t lEffective=kind==2?lWord:uint32_t(lWord+llPlace);
                    // A source STT_SECTION reference is resolved through the
                    // uniquely named symbol at that addend; don't add A again.
                    uint32_t expectedCg=cgTarget+((target.type==3 || recoveredByLocal)?0:originalAddend);
                    uint32_t expectedLl=llTarget+((target.type==3 || recoveredByLocal)?0:originalAddend);
                    if(target.type==2){expectedCg|=1u;expectedLl|=1u;}
                    must(cEffective==expectedCg,"CGARM "+std::string(kind==2?"ABS32":"REL32")+
                        " destination mismatch in "+path+":"+anchors[0].symbol.name+
                        " at +"+std::to_string(anchors[0].delta)+" got "+hex(cEffective)+" expected "+hex(expectedCg));
                    must(lEffective==expectedLl,"LLVM "+std::string(kind==2?"ABS32":"REL32")+
                        " destination mismatch in "+path+":"+anchors[0].symbol.name+
                        " at +"+std::to_string(anchors[0].delta)+" got "+hex(lEffective)+" expected "+hex(expectedLl));
                    ++result.checked;
                    if(kind==2)++result.dataPointers;else ++result.pcRelative;
                }else if(kind==26){
                    auto cGot=gotBases7(cg),lGot=gotBases7(llvm);
                    if(cGot.size()!=1 || lGot.size()!=1){unresolved8(result,path,input,offset,kind,target,anchors[0].symbol.name,
                        "GOT section unavailable");continue;}
                    uint32_t cIndex=cWord-originalAddend,lIndex=lWord-originalAddend;
                    bool cIn=false,lIn=false;
                    for(const auto& s:cg.sections)if(s.name==".got")cIn=uint64_t(cIndex)+4<=s.size && cIndex%4==0;
                    for(const auto& s:llvm.sections)if(s.name==".got")lIn=uint64_t(lIndex)+4<=s.size && lIndex%4==0;
                    must(cIn && lIn,"GOT_BREL references out-of-range/misaligned slot at "+path+":"+anchors[0].symbol.name);
                    uint32_t cActual=word7(cg,cGot[0]+cIndex),lActual=word7(llvm,lGot[0]+lIndex);
                    uint32_t expectedCg=cgTarget|(target.type==2?1u:0u);
                    uint32_t expectedLl=llTarget|(target.type==2?1u:0u);
                    must(cActual==expectedCg,"CGARM GOT slot targets wrong symbol at "+path+":"+anchors[0].symbol.name+
                         " got "+hex(cActual)+" expected "+hex(expectedCg));
                    must(lActual==expectedLl,"LLVM GOT slot targets wrong symbol at "+path+":"+anchors[0].symbol.name+
                         " got "+hex(lActual)+" expected "+hex(expectedLl));
                    ++result.checked;++result.gotPointers;
                }
                if(verbose)std::cout<<"  checked relocation "<<path<<":"<<anchors[0].symbol.name
                    <<" +"<<anchors[0].delta<<" type="<<kind
                    <<" cg="<<hex(cgPlace)<<" llvm="<<hex(llPlace)<<" target="<<target.name<<" OK\n";
            }
        }
    }
    return result;
}


// Stage 10: linker provenance. Each mapping is corroborated against the
// destination ELF's allocated sections. Without a map we do NOT guess.
std::string mapKey10(const std::string &path,const std::string &section) {
    const auto archive=path.rfind('(');
    std::string shortPath=path;
    if(archive!=std::string::npos && path.back()==')') {
        shortPath=std::filesystem::path(path.substr(0,archive)).filename().string()+
                  "("+path.substr(archive+1);
    } else shortPath=std::filesystem::path(path).filename().string();
    return shortPath+":"+section;
}
uint64_t hash10(const Bytes& bytes) {
    uint64_t h=14695981039346656037ULL;
    for(uint8_t c:bytes)h=(h^c)*1099511628211ULL;
    return h;
}
uint64_t number10(const std::string &x,int base) {
    size_t pos=0;uint64_t v=0;
    try{v=std::stoull(x,&pos,base);}
    catch(...){throw Error("Invalid map number: "+x);}
    must(pos==x.size(),"Invalid map number: "+x);
    return v;
}
std::string strip10(const std::string &in) {
    size_t a=0,b=in.size();
    while(a<b && std::isspace(static_cast<unsigned char>(in[a])))++a;
    while(b>a && std::isspace(static_cast<unsigned char>(in[b-1])))--b;
    return in.substr(a,b-a);
}
struct MapSection10 {
    uint32_t addr=0,size=0,flags=0;
    bool live=false;
};
struct Map10 {
    std::map<std::string,std::vector<MapSection10>> rows;
    std::map<std::string,uint64_t> objects;
    uint64_t elfHash=0;
};
void addMap10(Map10& map,const std::string& obj,const std::string& sec,const MapSection10& row){
    map.rows[mapKey10(obj,sec)].push_back(row);
}
Map10 readCgMap10(const std::string &path,const Bytes &elf){
    std::ifstream file(path);
    must(bool(file),"Cannot open CGARM provenance map: "+path);
    std::string line;
    must(bool(std::getline(file,line)) && line=="CGARM_PROVENANCE_V1",
         "Unsupported CGARM provenance format: "+path);
    Map10 map;bool hashSeen=false;
    while(std::getline(file,line)){
        if(line.empty())continue;
        std::istringstream in(line);std::string tag;in>>tag;
        if(tag=="ELF"){
            std::string v;in>>v;
            must(!hashSeen && !v.empty(),"Malformed/duplicate CGARM ELF fingerprint");
            map.elfHash=number10(v,16);hashSeen=true;
        } else if(tag=="OBJECT"){
            std::string obj,h;in>>std::quoted(obj)>>h;
            must(!obj.empty() && !h.empty(),"Malformed CGARM OBJECT entry");
            auto [it,inserted]=map.objects.emplace(mapKey10(obj,""),number10(h,16));
            must(inserted,"Ambiguous/duplicate CGARM object label: "+obj);
        } else if(tag=="SECTION"){
            std::string obj,name,status,address;uint64_t idx=0,sz=0,flags=0;
            in>>std::quoted(obj)>>idx>>std::quoted(name)>>status>>address>>sz>>flags;
            must(bool(in) && !obj.empty() && !name.empty() && idx>0 && sz>0 && sz<=UINT32_MAX && flags<=UINT32_MAX &&
                 (status=="LIVE" || status=="DISCARDED"),"Malformed CGARM SECTION entry");
            MapSection10 row;
            row.live=status=="LIVE";row.addr=row.live?uint32_t(number10(address,16)):0;
            must(!row.live || (address!="-" && number10(address,16)<=UINT32_MAX),"Bad CGARM map address");
            must(row.live || address=="-","Discarded section cannot have an address");
            row.size=uint32_t(sz);row.flags=uint32_t(flags);
            addMap10(map,obj,name,row);
        } else throw Error("Unknown CGARM map record: "+tag);
    }
    must(hashSeen && map.elfHash==hash10(elf),"CGARM map fingerprint does not match ELF (stale map?)");
    must(!map.rows.empty(),"Empty CGARM provenance map");
    return map;
}
Map10 readLldMap10(const std::string &path){
    std::ifstream file(path);
    must(bool(file),"Cannot open LLVM LLD map: "+path);
    Map10 map;std::string line;
    while(std::getline(file,line)){
        auto position=line.find(":(");
        if(position==std::string::npos)continue;
        auto end=line.find(')',position+2);
        if(end==std::string::npos)continue;
        std::istringstream in(line);
        std::string vma,lma,size,align;
        if(!(in>>vma>>lma>>size>>align))continue;
        if(vma=="VMA" || vma.size()>16)continue;
        uint64_t a=0,sz=0;
        try{a=number10(vma,16);sz=number10(size,16);}
        catch(...){continue;}
        if(a<0xD0000000u || a>UINT32_MAX || sz==0 || sz>UINT32_MAX)continue;
        std::string tail;std::getline(in,tail);
        auto token=strip10(tail);
        auto pos=token.find(":(");
        if(pos==std::string::npos)continue;
        auto close=token.find(')',pos+2);
        if(close==std::string::npos)continue;
        const std::string obj=token.substr(0,pos),sec=token.substr(pos+2,close-pos-2);
        if(obj.empty() || sec.empty() || obj=="<internal>")continue;
        addMap10(map,obj,sec,{uint32_t(a),uint32_t(sz),0,true});
    }
    must(!map.rows.empty(),"No allocated input sections found in LLVM -Map output");
    return map;
}
// Stage 15: strict, READ-ONLY System V/GNU/BSD ar archive parser. The
// archive's symbol index is metadata, NOT proof a member was selected.
// Membership is established solely by an exact, fingerprinted CGARM map
// OBJECT row. Unselected archive members are never audited as live code.
struct ArchiveMember14 {std::string name;Bytes contents;};
std::string arName14(std::string name) {
    return strip10(name);
}
uint64_t arDecimal14(const std::string& field){
    const auto trimmed=strip10(field);
    must(!trimmed.empty(),"Empty archive member size");
    return number10(trimmed,10);
}
std::vector<ArchiveMember14> readArchive14(const std::string &path){
    const auto ar=readFile(path);
    must(ar.size()>=8 && std::memcmp(ar.data(),"!<arch>\n",8)==0,
         "Stage14 expected normal ar archive (thin archives unsupported): "+path);
    std::vector<ArchiveMember14> out;
    std::string longNames;
    size_t pos=8;
    while(pos<ar.size()){
        must(pos+60<=ar.size(),"Truncated archive member header: "+path);
        must(ar[pos+58]=='`' && ar[pos+59]=='\n',"Invalid archive header delimiter: "+path);
        const std::string raw(reinterpret_cast<const char*>(ar.data()+pos),16);
        const uint64_t dataSize=arDecimal14(std::string(reinterpret_cast<const char*>(ar.data()+pos+48),10));
        must(dataSize<=32ull*1024*1024,"Archive member exceeds 32 MiB limit: "+path);
        const size_t start=pos+60;
        must(dataSize<=ar.size()-start,"Truncated archive member payload: "+path);
        std::string name=arName14(raw);
        size_t body=start;
        size_t bodySize=static_cast<size_t>(dataSize);
        bool metadata=(name=="/" || name=="//" || name=="/SYM64/" || name=="__.SYMDEF" || name=="__.SYMDEF SORTED");
        if(name=="//") {
            longNames.assign(reinterpret_cast<const char*>(ar.data()+start),bodySize);
        } else if(name.rfind("#1/",0)==0){
            const size_t length=static_cast<size_t>(arDecimal14(name.substr(3)));
            must(length<=bodySize,"BSD ar filename larger than member");
            name.assign(reinterpret_cast<const char*>(ar.data()+body),length);
            body+=length;bodySize-=length;
        } else if(name.size()>1 && name[0]=='/' &&
                  std::all_of(name.begin()+1,name.end(),[](unsigned char x){return std::isdigit(x)!=0;})){
            const uint64_t offset=arDecimal14(name.substr(1));
            must(offset<longNames.size(),"Bad GNU archive long-name offset");
            const auto end=longNames.find("/\n",size_t(offset));
            must(end!=std::string::npos,"Unterminated GNU archive filename");
            name=longNames.substr(size_t(offset),end-size_t(offset));
        } else if(!name.empty() && name.back()=='/')name.pop_back();
        if(!metadata){
            must(!name.empty() && name.find('/')==std::string::npos &&
                 name.find('(')==std::string::npos && name.find(')')==std::string::npos,
                 "Unsupported unsafe archive member name: "+name);
            out.push_back({name,Bytes(ar.begin()+body,ar.begin()+body+bodySize)});
        }
        pos=start+static_cast<size_t>(dataSize);
        if(pos&1){must(pos<ar.size(),"Missing ar alignment byte");++pos;}
    }
    return out;
}
struct ArchiveAudit14{
    size_t archives=0,selected=0,unused=0,selectedBytes=0;
    std::vector<std::string> selectedNames;
};
ArchiveAudit14 prepareArchives14(const std::vector<std::string>& archivePaths,
                                const Map10& cgMap,std::vector<std::string>& objects){
    ArchiveAudit14 report;
    std::set<std::string> archiveBasenames;
    std::set<std::string> selectedKeys;
    std::set<std::string> allInputKeys;
    for(const auto& obj:objects) {
        must(allInputKeys.insert(mapKey10(obj,"")).second,
             "Duplicate original input object label: "+obj);
    }
    for(const auto& archive:archivePaths){
        const std::string basename=std::filesystem::path(archive).filename().string();
        must(archiveBasenames.insert(basename).second,
             "Two archive paths share the same basename; map would be ambiguous: "+basename);
        ++report.archives;
        auto members=readArchive14(archive);
        std::set<std::string> memberNames;
        for(auto &member:members){
            const auto virtualPath=archive+"("+member.name+")";
            const auto key=mapKey10(virtualPath,"");
            auto it=cgMap.objects.find(key);
            if(it==cgMap.objects.end()) {++report.unused;continue;}
            must(memberNames.insert(member.name).second,
                 "Duplicate selected archive member name: "+virtualPath);
            must(selectedKeys.insert(key).second && allInputKeys.insert(key).second,
                 "Repeated selected archive member: "+virtualPath);
            must(hash10(member.contents)==it->second,
                 "Selected archive member has changed since linker map generation: "+virtualPath);
            must(member.contents.size()>=52 && member.contents[0]==127 && member.contents[1]=='E' &&
                 member.contents[2]=='L' && member.contents[3]=='F',
                 "Selected archive member is not an ELF object: "+virtualPath);
            report.selectedBytes+=member.contents.size();
            report.selectedNames.push_back(virtualPath);
            virtualArchiveObjects14.emplace(virtualPath,std::move(member.contents));
            objects.push_back(virtualPath);
            ++report.selected;
        }
    }
    // If any selected archive member is listed in the provenance evidence,
    // it MUST be supplied and fingerprinted before we claim archive coverage.
    for(const auto& [key,hash]:cgMap.objects){
        (void)hash;
        const auto name=key.substr(0,key.size()-1); // key ends in ':'
        const auto marker=name.find(".a(");
        if(marker!=std::string::npos){
            must(selectedKeys.find(key)!=selectedKeys.end(),
                 "CGARM map selected archive member not supplied via --archives: "+name);
        }
    }
    return report;
}

// Only trust a map address if it lies in a corresponding allocated ELF
// section, and (for source input) size/flags match GCC's original object.
bool existsInElf10(const ElfView6& elf,uint32_t a,uint32_t size){
    for(const auto& sec:elf.sections){
        if(!(sec.flags&2u) || !sec.size)continue;
        if(uint64_t(a)>=sec.address && uint64_t(a)+size<=uint64_t(sec.address)+sec.size)
            return true;
    }
    return false;
}
std::vector<uint32_t> addrOf10(const Map10 &m,const std::string& path,const Section6 &source,
                               const ElfView6& elf,bool isCg){
    std::vector<uint32_t> addresses;
    auto it=m.rows.find(mapKey10(path,source.name));
    if(it==m.rows.end())return addresses;
    for(const auto& row:it->second){
        if(!row.live || row.size!=source.size)continue;
        if(isCg && row.flags!=source.flags)continue;
        // LLVM may merge SHF_MERGE data; the source offset is not invariant.
        if((source.flags&16u) && !isCg)continue;
        if(!existsInElf10(elf,row.addr,row.size))continue;
        addresses.push_back(row.addr);
    }
    std::sort(addresses.begin(),addresses.end());
    addresses.erase(std::unique(addresses.begin(),addresses.end()),addresses.end());
    return addresses;
}
// Stage 11: mergeable source sections are allowed to change offsets in LLD.
// Locate the single REFERENCED string (including NUL) or fixed-size merge
// record independently in the emitted LLD ELF. Never use the observed
// relocation value to choose the destination: that would hide wrong pointers.
// The CGARM destination is supplied separately by its fingerprinted map.
// Zero or multiple viable ELF locations => NOT verified.
struct MergeTarget11 {
    bool valid=false;
    bool shortRecord=false,sourceScoped=false;
    uint32_t cgAddress=0,llvmAddress=0;
    std::string reason;
};

std::vector<uint32_t> findUniqueFragment11(const ElfView6 &elf,const Bytes &fragment,
                                           uint32_t intraRecordOffset,
                                           const std::vector<MapSection10>*sourceRanges=nullptr){
    std::vector<uint32_t> locations;
    if(fragment.empty())return locations; // a one-byte record must ALSO prove unique provenance
    for(const auto &sec:elf.sections){
        // Require actual initialised ALLOC data; do not search section headers,
        // debug information, or zero-filled BSS/stack memory.
        if(!(sec.flags&2u) || sec.type!=1 || sec.size<fragment.size())continue;
        for(uint64_t i=0;i+fragment.size()<=sec.size;++i){
            uint64_t file=uint64_t(sec.offset)+i;
            if(file>elf.bytes.size() || fragment.size()>elf.bytes.size()-file)break;
            if(!std::equal(fragment.begin(),fragment.end(),elf.bytes.begin()+file))continue;
            // For tiny NUL-terminated strings, reject matches embedded inside
            // a different string. Longer suffix strings retain suffix folding.
            if(fragment.size()<4 && fragment.back()==0 && i>0 &&
               elf.bytes[file-1]!=0)continue;
            const uint64_t recordStart=uint64_t(sec.address)+i;
            if(sourceRanges && !sourceRanges->empty()){
                bool supported=false;
                for(const auto&range:*sourceRanges) {
                    if(range.live && range.size>=fragment.size() &&
                       recordStart>=range.addr &&
                       recordStart+fragment.size()<=uint64_t(range.addr)+range.size) {
                        supported=true;break;
                    }
                }
                if(!supported)continue;
            }
            uint64_t address=recordStart+intraRecordOffset;
            if(address<=UINT32_MAX)locations.push_back(uint32_t(address));
        }
    }
    std::sort(locations.begin(),locations.end());
    locations.erase(std::unique(locations.begin(),locations.end()),locations.end());
    return locations;
}

// A REL relocation's addend is *arithmetic*, not necessarily the position
// of the mergeable record. For a local .LC symbol, st_value names the actual
// string and the addend may be -4 for an ARM PC-adjusted literal. Treating
// st_value + A as a string offset is incorrect in this case.
MergeTarget11 mapMergedTarget11(const ElfView6 &input,const Section6 &target,
                               uint8_t symType,uint32_t symbolValue,int32_t addend,
                               const std::vector<uint32_t>&cgTarget,
                               const ElfView6 &cg,const ElfView6 &llvm,
                               const std::vector<MapSection10>*llvmSourceRanges=nullptr){
    MergeTarget11 r;
    if(cgTarget.size()!=1){r.reason="CGARM section mapping ambiguous";return r;}
    if(target.type!=1 || !(target.flags&16u) || !(target.flags&2u)){
        r.reason="target is not initialised ALLOC SHF_MERGE data";return r;
    }
    if(target.entrySize==0){r.reason="mergeable section has zero sh_entsize";return r;}
    if(target.flags&32u && target.entrySize!=1){
        r.reason="multi-byte ELF mergeable string unit unsupported";return r;
    }
    const bool sectionSymbol=symType==3; // STT_SECTION
    // For an STT_SECTION relocation, the addend selects the section offset.
    // A small negative addend may name the section start with a PC bias;
    // this is only accepted at section start, never as a wild guessed offset.
    const int64_t ref=sectionSymbol ? int64_t(symbolValue)+int64_t(addend)
                                    : int64_t(symbolValue);
    int64_t position=ref;
    if(sectionSymbol && position<0 && position>=-4)position=0;
    if(position<0 || uint64_t(position)>=target.size){
        r.reason="referenced source offset outside mergeable section (S="+
                 std::to_string(symbolValue)+", A="+std::to_string(addend)+")";
        return r;
    }
    uint64_t start=0,len=0,intra=0;
    if(target.flags&32u){
        start=uint64_t(position);
        // The exact string suffix, through its NUL. Even when LLVM suffix-
        // folds it, the original symbol still identifies this suffix.
        uint64_t end=start;
        while(end<target.size && input.bytes.at(uint64_t(target.offset)+end)!=0)++end;
        if(end==target.size){r.reason="mergeable string missing terminator";return r;}
        len=end-start+1;
    }else{
        start=(uint64_t(position)/target.entrySize)*target.entrySize;
        intra=uint64_t(position)-start;
        len=target.entrySize;
        if(start+len>target.size){r.reason="incomplete mergeable record";return r;}
    }
    if(len<1 || len>4096){
        r.reason="referenced mergeable record has unsupported size "+std::to_string(len);
        return r;
    }
    bounds(input.bytes,uint64_t(target.offset)+start,len,"source mergeable fragment");
    const Bytes fragment(input.bytes.begin()+target.offset+start,
                         input.bytes.begin()+target.offset+start+len);
    const uint64_t cgRecord=uint64_t(cgTarget[0])+start;
    bool exact=false;
    for(const auto &sec:cg.sections){
        if(!(sec.flags&2u) || sec.type!=1 || cgRecord<sec.address ||
           cgRecord+len>uint64_t(sec.address)+sec.size)continue;
        uint64_t file=uint64_t(sec.offset)+(cgRecord-sec.address);
        if(file<=cg.bytes.size() && len<=cg.bytes.size()-file &&
           std::equal(fragment.begin(),fragment.end(),cg.bytes.begin()+file))exact=true;
    }
    if(!exact){r.reason="CGARM mergeable source record bytes differ";return r;}
    // LLD's map can sometimes retain a provenance range for a mergeable
    // input section. Prefer that independent range over global byte searching.
    // A one-byte NUL is NEVER a unique symbol merely because there is a NUL
    // somewhere in the ELF: require a concrete mapped input-section range.
    const bool hasSourceRange=llvmSourceRanges && !llvmSourceRanges->empty();
    if(fragment.size()==1 && !hasSourceRange){
        r.reason="one-byte record has no independent LLVM input-section range";return r;
    }
    const auto found=findUniqueFragment11(llvm,fragment,uint32_t(intra),llvmSourceRanges);
    if(found.size()!=1){
        r.reason=found.empty()?"referenced mergeable fragment absent from LLVM ELF":
                              "referenced mergeable fragment has multiple LLVM locations";
        return r;
    }
    // Source record identity was established without observing patched words.
    // Apply the original ARM addend separately (which can be negative).
    const int64_t residual=sectionSymbol ? ref-(int64_t(start)+int64_t(intra))
                                          : int64_t(addend);
    const int64_t cgAddress=int64_t(cgTarget[0])+int64_t(position)+residual;
    const int64_t llAddress=int64_t(found.front())+residual;
    if(cgAddress<0 || cgAddress>UINT32_MAX || llAddress<0 || llAddress>UINT32_MAX){
        r.reason="mergeable target plus signed addend overflows 32 bits";return r;
    }
    r.valid=true;r.shortRecord=fragment.size()==1;r.sourceScoped=hasSourceRange;
    r.cgAddress=uint32_t(cgAddress);r.llvmAddress=uint32_t(llAddress);
    return r;
}

// Stage 12: verify EVERY unchanged byte of mapped, retained input sections,
// not only the functions that happen to be uniquely named. All source
// relocation patches are excluded. Both linked ELFs must independently
// retain each remaining compiler byte exactly. BSS and mergeable sections
// are intentionally excluded (LLD may rewrite them).
struct SectionBytes12 {
    size_t sections=0,bytes=0,code=0,data=0,readOnly=0;
    size_t masked=0,discarded=0,unmapped=0,mergeable=0;
    size_t archiveSections=0,archiveBytes=0,archiveMasked=0;
};
SectionBytes12 verifySectionBytes12(const Map10 &cgMap,const Map10 &llvmMap,
                                   const ElfView6 &cg,const ElfView6 &llvm,
                                   const std::vector<std::string>&objects){
    SectionBytes12 out;
    for(const auto& path:objects){
        const auto src=inspect6(path,1);
        auto fingerprint=cgMap.objects.find(mapKey10(path,""));
        must(fingerprint!=cgMap.objects.end() && fingerprint->second==hash10(src.bytes),
             "Section-byte audit source fingerprint mismatch: "+path);
        for(size_t i=1;i<src.sections.size();++i){
            const auto& input=src.sections[i];
            if(input.type!=1 || !(input.flags&2u) || !input.size)continue;
            if(input.flags&16u){++out.mergeable;continue;}
            const auto key=mapKey10(path,input.name);
            const auto cgRow=cgMap.rows.find(key);
            if(cgRow!=cgMap.rows.end()){
                bool live=false;
                for(const auto& r:cgRow->second)live|=r.live;
                if(!live){++out.discarded;continue;}
            }
            const auto cs=addrOf10(cgMap,path,input,cg,true);
            const auto ls=addrOf10(llvmMap,path,input,llvm,false);
            if(cs.size()!=1 || ls.size()!=1){++out.unmapped;continue;}
            const bool archiveMember=virtualArchiveObjects14.find(path)!=virtualArchiveObjects14.end();
            std::vector<uint8_t> relocMask(input.size,0);
            for(const auto& rel:src.sections){
                if((rel.type!=9 && rel.type!=4) || rel.info!=i)continue;
                const uint32_t stride=rel.type==9?8u:12u;
                must(rel.entrySize==stride && rel.size%stride==0,
                     "Malformed relocation entries for section byte audit");
                for(uint32_t n=0;n<rel.size/stride;++n){
                    const uint32_t roff=u32(src.bytes,uint64_t(rel.offset)+uint64_t(n)*stride);
                    must(uint64_t(roff)+4<=input.size,"Relocation outside source section in byte audit");
                    for(uint32_t j=0;j<4;++j)relocMask[roff+j]=1;
                }
            }
            bounds(src.bytes,input.offset,input.size,"input section bytes");
            for(uint32_t n=0;n<input.size;++n){
                if(relocMask[n]){++out.masked;if(archiveMember)++out.archiveMasked;continue;}
                const uint32_t ac=cs[0]+n,al=ls[0]+n;
                const uint8_t expected=byte6(src.bytes,uint64_t(input.offset)+n);
                auto readAt=[&](const ElfView6&e,uint32_t address)->uint8_t{
                    for(const auto& sec:e.sections){
                        if(!(sec.flags&2u) || sec.type!=1 || address<sec.address ||
                           uint64_t(address)>=uint64_t(sec.address)+sec.size)continue;
                        return byte6(e.bytes,uint64_t(sec.offset)+address-sec.address);
                    }
                    throw Error("Stage 12 byte audit address outside initialised ELF: "+hex(address));
                };
                must(readAt(cg,ac)==expected && readAt(llvm,al)==expected,
                     "Stage 12 unchanged source byte differs: "+path+":"+input.name+
                     " +"+hex(n)+" (CGARM "+hex(ac)+", LLVM "+hex(al)+")");
                ++out.bytes;
                if(archiveMember)++out.archiveBytes;
                if(input.flags&4u)++out.code;
                else if(input.flags&1u)++out.data;
                else ++out.readOnly;
            }
            ++out.sections;
            if(archiveMember)++out.archiveSections;
        }
    }
    return out;
}

// Stage 17: source relocation ID (exact object/member + input section + offset + ARM type).
// Never infer coverage from totals or by examining patched output words alone.
std::string relocationKey16(const std::string&path,const std::string&section,
                            uint32_t offset,uint32_t kind){
    return path+"\x1f"+section+"\x1f"+std::to_string(offset)+"\x1f"+std::to_string(kind);
}
// Stage 15: recover a global symbol's provenance from the ORIGINAL object
// defining it, including selected archive members. The section address must
// be uniquely corroborated by BOTH linker maps; duplicate definitions do
// not become a guessed match. Never use the candidate's observed relocation
// pointer as evidence for a target address.
struct Defined14 {uint32_t cg=0,llvm=0;uint8_t type=0;};
using Definitions14=std::map<std::string,std::vector<Defined14>>;
Definitions14 collectDefinitions14(const Map10&cm,const Map10&lm,
                                  const ElfView6&cg,const ElfView6&ll,
                                  const std::vector<std::string>&objects){
    Definitions14 result;
    for(const auto& path:objects){
        const auto src=inspect6(path,1);
        for(const auto& tab:src.sections){
            if(tab.type!=2)continue;
            must(tab.entrySize==16 && tab.size%16==0 && tab.link<src.sections.size(),
                 "Stage14 bad symbol table in: "+path);
            const auto&strings=src.sections[tab.link];
            must(strings.type==3,"Stage14 bad symbol strings: "+path);
            for(uint32_t i=0;i<tab.size/16;++i){
                const uint64_t pos=uint64_t(tab.offset)+i*16;
                const uint8_t stInfo=byte6(src.bytes,pos+12);
                const uint8_t bind=stInfo>>4,kind=stInfo&15u;
                if(bind!=1 && bind!=2)continue; // GLOBAL or WEAK, not local
                const uint16_t si=u16(src.bytes,pos+14);
                if(si==0 || si>=src.sections.size())continue;
                const auto&section=src.sections[si];
                if(!(section.flags&2u))continue;
                const auto name=str6(src.bytes,strings.offset,strings.size,u32(src.bytes,pos));
                if(name.empty())continue;
                const auto cs=addrOf10(cm,path,section,cg,true);
                const auto ls=addrOf10(lm,path,section,ll,false);
                if(cs.size()!=1 || ls.size()!=1)continue;
                uint32_t offset=u32(src.bytes,pos+4);
                if(kind==2)offset&=~1u;
                if(offset>=section.size)continue;
                const Defined14 v{uint32_t(cs[0]+offset),uint32_t(ls[0]+offset),kind};
                result[name].push_back(v);
            }
        }
    }
    return result;
}
std::vector<Defined14> findDefinition14(const Definitions14&defs,const std::string& name){
    const auto it=defs.find(name);
    if(it==defs.end())return {};
    const auto&src=it->second;
    std::vector<Defined14> unique;
    for(const auto& x:src){
        const bool same=std::any_of(unique.begin(),unique.end(),[&](const Defined14& v){
            return v.cg==x.cg && v.llvm==x.llvm && v.type==x.type;
        });
        if(!same)unique.push_back(x);
    }
    return unique;
}

// Stage 15: audit Thumb-2 BL/B.W relocations in *every retained source
// section*, rather than only functions discovered by the old symbol matcher.
// Both linked instructions must point to executable memory. When the original
// ARM symbol resolves uniquely via independently recorded source sections or
// both linkers' output symbols, we additionally prove the exact destination.
// The unresolved destinations are explicitly counted, never silently passed.
struct Branch13 {
    size_t input=0,live=0,discarded=0,unmapped=0,execValid=0;
    size_t localExact=0,externalExact=0,unresolved=0;
    size_t archiveInputs=0,archiveLive=0,archiveExact=0;
    std::map<std::string,size_t> reasons;
    std::set<std::string> exactSites;
};
std::vector<uint32_t> unique13(std::vector<uint32_t> values){
    std::sort(values.begin(),values.end());
    values.erase(std::unique(values.begin(),values.end()),values.end());
    return values;
}
std::vector<uint32_t> outputFunction13(const ElfView6& elf,const std::string& name,
                                        bool cgarm){
    std::vector<uint32_t> found;
    if(name.empty())return found;
    for(const auto& f:elf.functions)if(f.name==name)found.push_back(f.addr&~1u);
    if(cgarm){
        for(const auto& s:elf.sections)
            if(s.name==".text."+name && s.type==1 && (s.flags&4u))found.push_back(s.address);
    }
    return unique13(std::move(found));
}
Branch13 verifyBranches13(const Map10& cm,const Map10& lm,
                          const ElfView6& cg,const ElfView6& llvm,
                          const std::vector<std::string>& objects,const Definitions14&defs,bool explain){
    Branch13 out;
    for(const auto& path:objects){
        const auto src=inspect6(path,1);
        const auto fingerprint=cm.objects.find(mapKey10(path,""));
        must(fingerprint!=cm.objects.end() && fingerprint->second==hash10(src.bytes),
             "Stage14 branch object fingerprint differs from CGARM map: "+path);
        for(const auto& rel:src.sections){
            if(rel.type!=9 && rel.type!=4)continue;
            if(rel.info>=src.sections.size() || rel.link>=src.sections.size())continue;
            const auto& from=src.sections[rel.info];
            const auto& tab=src.sections[rel.link];
            if(!(from.flags&2u) || !(from.flags&4u) || from.type!=1 ||
               tab.type!=2 || tab.entrySize!=16 || tab.link>=src.sections.size())continue;
            const auto& strings=src.sections[tab.link];
            const uint32_t stride=rel.type==9?8:12;
            must(rel.entrySize==stride && rel.size%stride==0,"Stage14 malformed branch relocation table");
            for(uint32_t i=0;i<rel.size/stride;++i){
                const uint64_t ro=uint64_t(rel.offset)+uint64_t(i)*stride;
                const uint32_t info=u32(src.bytes,ro+4),kind=info&255u;
                if(kind!=10 && kind!=30)continue;
                ++out.input;
                const bool archiveMember=virtualArchiveObjects14.find(path)!=virtualArchiveObjects14.end();
                if(archiveMember)++out.archiveInputs;
                const uint32_t off=u32(src.bytes,ro);
                must(uint64_t(off)+4<=from.size,"Stage14 branch relocation outside source section");
                const auto cs=addrOf10(cm,path,from,cg,true),ls=addrOf10(lm,path,from,llvm,false);
                if(cs.size()!=1 || ls.size()!=1){
                    auto c=cm.rows.find(mapKey10(path,from.name));
                    auto l=lm.rows.find(mapKey10(path,from.name));
                    const bool discarded=c!=cm.rows.end() &&
                        std::none_of(c->second.begin(),c->second.end(),
                                     [](const MapSection10& a){return a.live;});
                    if(discarded && l==lm.rows.end()){++out.discarded;continue;}
                    ++out.unmapped;++out.reasons["source mapping unresolved"];continue;
                }
                ++out.live;
                if(archiveMember)++out.archiveLive;
                // Decode the original instruction to obtain its REL addend.
                // ARM Thumb BL encodes the standard PC-bias -4 in the input.
                const uint32_t sourcePlace=0x1000u+off;
                const uint32_t oldTarget=branchTarget6(src.bytes,from.offset+off,sourcePlace,kind);
                const int64_t bias=int64_t(oldTarget)-int64_t(sourcePlace+4u)+4;
                const uint32_t pc=cs.front()+off,pl=ls.front()+off;
                auto linkedTarget=[&](const ElfView6& e,uint32_t place)->uint32_t{
                    for(const auto& sec:e.sections){
                        if(sec.type!=1 || !(sec.flags&4u) || place<sec.address ||
                           uint64_t(place)+4>uint64_t(sec.address)+sec.size)continue;
                        const uint32_t dest=branchTarget6(e.bytes,sec.offset+place-sec.address,place,kind);
                        must(targetExec6(e,dest),"Stage14 branch outside executable section at "+hex(place)+
                             " -> "+hex(dest));
                        return dest;
                    }
                    throw Error("Stage14 branch instruction not found in executable ELF at "+hex(place));
                };
                const uint32_t ac=linkedTarget(cg,pc),al=linkedTarget(llvm,pl);
                ++out.execValid;
                const uint32_t symIndex=info>>8;
                must(uint64_t(symIndex)*16+16<=tab.size,"Stage14 invalid branch target index");
                const uint64_t sp=uint64_t(tab.offset)+uint64_t(symIndex)*16;
                const uint16_t si=u16(src.bytes,sp+14);
                const uint32_t value=u32(src.bytes,sp+4);
                const uint8_t symType=byte6(src.bytes,sp+12)&15u;
                const std::string name=str6(src.bytes,strings.offset,strings.size,u32(src.bytes,sp));
                std::vector<uint32_t> cTarget,lTarget;
                bool local=false;
                if(si>0 && si<src.sections.size() && (src.sections[si].flags&4u)){
                    const auto& target=src.sections[si];
                    const auto ct=addrOf10(cm,path,target,cg,true);
                    const auto lt=addrOf10(lm,path,target,llvm,false);
                    if(ct.size()==1 && lt.size()==1){
                        cTarget.push_back(ct[0]+(value&~(symType==2?1u:0u)));
                        lTarget.push_back(lt[0]+(value&~(symType==2?1u:0u)));
                        local=true;
                    }
                }
                if(!local && !name.empty()){
                    cTarget=outputFunction13(cg,name,true);
                    lTarget=outputFunction13(llvm,name,false);
                    if(cTarget.size()!=1 || lTarget.size()!=1){
                        const auto definitions=findDefinition14(defs,name);
                        if(definitions.size()==1 && definitions[0].type==2){
                            cTarget={definitions[0].cg};
                            lTarget={definitions[0].llvm};
                        }
                    }
                }
                if(cTarget.size()!=1 || lTarget.size()!=1){
                    ++out.unresolved;
                    ++out.reasons["target symbol has no unique address in both outputs"];
                    if(explain)std::cout<<"  BRANCH DEFERRED "<<path<<":"<<from.name
                                         <<" +"<<hex(off)<<" -> "<<name<<"\n";
                    continue;
                }
                const uint32_t expectedC=uint32_t(int64_t(cTarget[0])+bias);
                const uint32_t expectedL=uint32_t(int64_t(lTarget[0])+bias);
                must(ac==expectedC && al==expectedL,
                     "Stage14 Thumb destination mismatch: "+path+":"+from.name+
                     " +"+hex(off)+" target="+name+" CGARM="+hex(ac)+" expected="+hex(expectedC)+
                     " LLVM="+hex(al)+" expected="+hex(expectedL));
                must(out.exactSites.insert(relocationKey16(path,from.name,off,kind)).second,
                     "Stage17 duplicate verified Thumb relocation site: "+path+":"+from.name);
                if(local)++out.localExact;else ++out.externalExact;
                if(archiveMember)++out.archiveExact;
            }
        }
    }
    return out;
}


// Stage 17: reconstruct GNU ELF SHN_COMMON (0xFFF2) from the original,
// fingerprinted ET_REL objects, independently of any GOT slot contents.
// CGARM's layout reserves COMMON allocations in lexical symbol-name order
// AFTER all retained NOBITS input sections. LLVM normally publishes the
// resolved named COMMON allocation in its SHT_SYMTAB. Both addresses must
// lie in the real output .bss before any site can be marked EXACT.
struct Common17 {
    std::map<std::string,std::pair<uint32_t,uint32_t>> proven;
    std::map<std::string,std::string> deferred;
    size_t relevant=0;
};
static bool writableNobits17(const ElfView6& e,uint32_t address,uint32_t size){
    for(const auto&sec:e.sections){
        if(sec.type!=8 || (sec.flags&3u)!=3u || !sec.size)continue;
        if(uint64_t(address)>=sec.address &&
           uint64_t(address)+size<=uint64_t(sec.address)+sec.size)return true;
    }
    return false;
}
static std::vector<uint32_t> namedCommonInElf17(const ElfView6& elf,const std::string& name,uint32_t size){
    std::vector<uint32_t> addresses;
    for(const auto&tab:elf.sections){
        if(tab.type!=2)continue;
        must(tab.entrySize==16 && tab.size%16==0 && tab.link<elf.sections.size(),
             "Stage17 malformed LLVM .symtab while finding COMMON allocation");
        const auto&str=elf.sections[tab.link];
        must(str.type==3,"Stage17 malformed symbol string table");
        for(uint64_t k=0;k<tab.size/16;++k){
            const uint64_t sp=uint64_t(tab.offset)+k*16;
            const uint8_t type=byte6(elf.bytes,sp+12)&15u;
            const uint16_t section=u16(elf.bytes,sp+14);
            if(type!=1 || section==0 || section>=elf.sections.size())continue;
            if(str6(elf.bytes,str.offset,str.size,u32(elf.bytes,sp))!=name)continue;
            const uint32_t addr=u32(elf.bytes,sp+4),symbolSize=u32(elf.bytes,sp+8);
            if(symbolSize && symbolSize<size)continue;
            if(!writableNobits17(elf,addr,size))continue;
            addresses.push_back(addr);
        }
    }
    std::sort(addresses.begin(),addresses.end());
    addresses.erase(std::unique(addresses.begin(),addresses.end()),addresses.end());
    return addresses;
}
Common17 mapCommon17(const Map10&cm,const Map10&lm,
                     const ElfView6&cg,const ElfView6&ll,
                     const std::vector<std::string>&objects){
    (void)lm;
    struct Decl{uint32_t size=0,align=1; bool conflict=false;};
    std::map<std::string,Decl> declared;
    std::set<std::string> strongNames;
    // First scan EVERY selected original definition; COMMON is tentative and
    // must not override a real strong definition with the same global name.
    for(const auto&path:objects){
        const auto src=inspect6(path,1);
        for(const auto&tab:src.sections){
            if(tab.type!=2)continue;
            must(tab.entrySize==16 && tab.size%16==0 && tab.link<src.sections.size(),
                 "Stage17 malformed source symbol table");
            const auto&str=src.sections[tab.link];
            for(uint64_t i=0;i<tab.size/16;++i){
                const uint64_t sp=uint64_t(tab.offset)+i*16;
                const uint8_t info=byte6(src.bytes,sp+12),binding=info>>4;
                if(binding==0)continue;
                const std::string name=str6(src.bytes,str.offset,str.size,u32(src.bytes,sp));
                if(name.empty())continue;
                const uint16_t section=u16(src.bytes,sp+14);
                if(section==0xfff2){
                    const uint32_t size=u32(src.bytes,sp+8),align=u32(src.bytes,sp+4);
                    must(align && (align&(align-1))==0,
                         "Stage17 invalid COMMON alignment "+name);
                    if(!size)continue;
                    auto&d=declared[name];
                    if(d.size && (d.size!=size || d.align!=align))d.conflict=true;
                    d.size=std::max(d.size,size);d.align=std::max(d.align,align);
                }else if(section>0 && section<src.sections.size() && binding==1){
                    strongNames.insert(name);
                }
            }
        }
    }
    Common17 out;
    // Only COMMON allocations actually REFERENCED from retained code/data are
    // laid out by the current CGARM linker. Discarded references are ignored.
    std::set<std::string> used;
    for(const auto&path:objects){
        const auto src=inspect6(path,1);
        for(const auto&rel:src.sections){
            if((rel.type!=9 && rel.type!=4) || rel.info>=src.sections.size() ||
               rel.link>=src.sections.size())continue;
            const auto&from=src.sections[rel.info],tab=src.sections[rel.link];
            if(!(from.flags&2u) || from.type!=1 || tab.type!=2 ||
               tab.entrySize!=16 || tab.link>=src.sections.size())continue;
            if(addrOf10(cm,path,from,cg,true).size()!=1)continue;
            const auto&str=src.sections[tab.link];
            const uint32_t stride=rel.type==9?8u:12u;
            must(rel.entrySize==stride && rel.size%stride==0,
                 "Stage17 malformed COMMON reference relocation table");
            for(uint64_t i=0;i<rel.size/stride;++i){
                const uint64_t rp=uint64_t(rel.offset)+i*stride;
                const uint32_t idx=u32(src.bytes,rp+4)>>8;
                must(uint64_t(idx)*16+16<=tab.size,"Stage17 invalid COMMON symbol index");
                const uint64_t sp=uint64_t(tab.offset)+uint64_t(idx)*16;
                const auto name=str6(src.bytes,str.offset,str.size,u32(src.bytes,sp));
                if(declared.count(name))used.insert(name);
            }
        }
    }
    out.relevant=used.size();
    if(used.empty())return out;
    const auto outBss=std::find_if(cg.sections.begin(),cg.sections.end(),
        [](const Section6&s){return s.name==".bss" && s.type==8 && (s.flags&3u)==3u;});
    if(outBss==cg.sections.end()){
        for(const auto&name:used)out.deferred[name]="CGARM ELF lacks writable NOBITS .bss";
        return out;
    }
    uint64_t cursor=outBss->address;
    for(const auto&path:objects){
        const auto src=inspect6(path,1);
        for(const auto&section:src.sections){
            if(section.type!=8 || !(section.flags&2u) || !section.size)continue;
            const auto locations=addrOf10(cm,path,section,cg,true);
            if(locations.size()==1){
                const uint64_t end=uint64_t(locations[0])+section.size;
                must(end<=uint64_t(outBss->address)+outBss->size,
                     "Stage17 input .bss does not fit output .bss");
                cursor=std::max(cursor,end);
            }
        }
    }
    for(const auto&name:used){
        const Decl&d=declared.at(name);
        const uint64_t expected=(cursor+d.align-1)&~uint64_t(d.align-1);
        cursor=expected+d.size;
        if(d.conflict || strongNames.count(name)){
            out.deferred[name]="multiple COMMON definitions disagree or strong definition overrides";continue;
        }
        if(expected>UINT32_MAX || !writableNobits17(cg,uint32_t(expected),d.size)){
            out.deferred[name]="computed CGARM COMMON allocation outside .bss";continue;
        }
        auto llvmAddresses=namedCommonInElf17(ll,name,d.size);
        if(llvmAddresses.size()!=1){
            out.deferred[name]="LLVM COMMON name absent or nonunique in .symtab/.bss";continue;
        }
        if(llvmAddresses.front()%d.align){
            out.deferred[name]="LLVM COMMON allocation misaligned";continue;
        }
        out.proven[name]={uint32_t(expected),llvmAddresses.front()};
    }
    return out;
}

// Stage 15: inspect every retained BASE_PREL and GOT_BREL input-site with
// input->output section provenance. Named or locally mapped GOT values are
// checked for exact symbol identity; unresolvable globals are DEFERRED.
struct Got13 {
    size_t input=0,live=0,discarded=0,unmapped=0,baseExact=0,slotExact=0,deferred=0;
    size_t archiveInputs=0,archiveLive=0,archiveExact=0;
    std::map<std::string,size_t> reasons;
    std::set<std::string> exactSites;
    std::map<std::string,std::string> unresolvedSites;
};
Got13 verifyGot13(const Map10&cm,const Map10&lm,const ElfView6&cg,
                  const ElfView6&ll,const std::vector<std::string>&objects,const Definitions14&defs,
                  const Common17&commons){
    Got13 out;
    const auto cGot=gotBases7(cg),lGot=gotBases7(ll);
    for(const auto& path:objects){
        const auto src=inspect6(path,1);
        for(const auto& rel:src.sections){
            if(rel.type!=9 && rel.type!=4)continue;
            if(rel.info>=src.sections.size() || rel.link>=src.sections.size())continue;
            const auto& from=src.sections[rel.info],tab=src.sections[rel.link];
            if(!(from.flags&2u) || from.type!=1 || tab.type!=2 ||
               tab.entrySize!=16 || tab.link>=src.sections.size())continue;
            const uint32_t stride=rel.type==9?8u:12u;
            must(rel.entrySize==stride && rel.size%stride==0,"Stage14 malformed GOT relocation table");
            for(uint32_t i=0;i<rel.size/stride;++i){
                const uint64_t rp=uint64_t(rel.offset)+uint64_t(i)*stride;
                const uint32_t info=u32(src.bytes,rp+4),kind=info&255u;
                if(kind!=25 && kind!=26)continue;
                ++out.input;
                const bool archiveMember=virtualArchiveObjects14.find(path)!=virtualArchiveObjects14.end();
                if(archiveMember)++out.archiveInputs;
                const uint32_t off=u32(src.bytes,rp);
                must(uint64_t(off)+4<=from.size,"Stage14 GOT relocation outside input section");
                const auto ca=addrOf10(cm,path,from,cg,true);
                const auto la=addrOf10(lm,path,from,ll,false);
                if(ca.size()!=1 || la.size()!=1){
                    const auto cr=cm.rows.find(mapKey10(path,from.name));
                    const auto lr=lm.rows.find(mapKey10(path,from.name));
                    bool dead=cr!=cm.rows.end() &&
                        std::none_of(cr->second.begin(),cr->second.end(),
                                     [](const MapSection10&r){return r.live;});
                    if(dead && lr==lm.rows.end()){++out.discarded;continue;}
                    ++out.unmapped;continue;
                }
                ++out.live;
                if(archiveMember)++out.archiveLive;
                if(cGot.size()!=1 || lGot.size()!=1){
                    ++out.deferred;++out.reasons["GOT base not unique"];
                    out.unresolvedSites[relocationKey16(path,from.name,off,kind)]=
                        "GOT base absent or ambiguous";continue;
                }
                const uint32_t pc=ca[0]+off,pl=la[0]+off;
                const uint32_t cv=word7(cg,pc),lv=word7(ll,pl);
                const uint32_t addend=rel.type==9?u32(src.bytes,uint64_t(from.offset)+off):u32(src.bytes,rp+8);
                if(kind==25){
                    must(uint32_t(cv+pc-addend)==cGot[0] &&
                         uint32_t(lv+pl-addend)==lGot[0],
                         "Stage14 GOT BASE_PREL relocation incorrect: "+path+":"+from.name+
                         " +"+hex(off));
                    must(out.exactSites.insert(relocationKey16(path,from.name,off,kind)).second,
                         "Stage17 duplicate GOT base reference");
                    ++out.baseExact;
                    if(archiveMember)++out.archiveExact;
                    continue;
                }
                auto validSlot=[&](const ElfView6&elf,uint32_t base,uint32_t index){
                    if(index%4)return false;
                    for(const auto&sec:elf.sections)
                        if(sec.name==".got" && sec.type==1 && sec.address==base &&
                           uint64_t(index)+4<=sec.size)return true;
                    return false;
                };
                const uint32_t ci=cv-addend,li=lv-addend;
                must(validSlot(cg,cGot[0],ci) && validSlot(ll,lGot[0],li),
                     "Stage14 GOT_BREL slot offset invalid: "+path+":"+from.name+
                     " +"+hex(off));
                const uint32_t symIndex=info>>8;
                must(uint64_t(symIndex)*16+16<=tab.size,"Stage14 GOT target symbol invalid");
                const uint64_t sp=uint64_t(tab.offset)+uint64_t(symIndex)*16;
                Symbol6 sym;
                const auto&str=src.sections[tab.link];
                sym.name=str6(src.bytes,str.offset,str.size,u32(src.bytes,sp));
                sym.addr=u32(src.bytes,sp+4);sym.size=u32(src.bytes,sp+8);
                sym.type=byte6(src.bytes,sp+12)&15u;sym.section=u16(src.bytes,sp+14);
                std::vector<uint32_t> ct,lt;
                if(sym.section>0 && sym.section<src.sections.size() &&
                   (src.sections[sym.section].flags&2u)){
                    const auto&target=src.sections[sym.section];
                    ct=addrOf10(cm,path,target,cg,true);
                    lt=addrOf10(lm,path,target,ll,false);
                    if(ct.size()==1 && lt.size()==1){
                        ct[0]+=sym.addr&~(sym.type==2?1u:0u);
                        lt[0]+=sym.addr&~(sym.type==2?1u:0u);
                    }
                }
                if((ct.size()!=1 || lt.size()!=1) && sym.section==0xfff2){
                    auto proven=commons.proven.find(sym.name);
                    if(proven!=commons.proven.end()){
                        ct={proven->second.first};lt={proven->second.second};
                    }
                }
                if(ct.size()!=1 || lt.size()!=1){
                    ct=locate7(cg,src,sym,true);
                    lt=locate7(ll,src,sym,false);
                }
                if(ct.size()!=1 || lt.size()!=1){
                    const auto definitions=findDefinition14(defs,sym.name);
                    if(definitions.size()==1){
                        ct={definitions[0].cg};
                        lt={definitions[0].llvm};
                    }
                }
                if(ct.size()!=1 || lt.size()!=1){
                    ++out.deferred;++out.reasons["GOT target symbol address not unique"];
                    out.unresolvedSites[relocationKey16(path,from.name,off,kind)]=
                        "target symbol '"+sym.name+"' (section="+std::to_string(sym.section)+
                        ") has no unique provenance in both outputs";continue;
                }
                const uint32_t expectedC=ct[0]|(sym.type==2?1u:0u);
                const uint32_t expectedL=lt[0]|(sym.type==2?1u:0u);
                const uint32_t actualC=word7(cg,cGot[0]+ci),actualL=word7(ll,lGot[0]+li);
                must(actualC==expectedC && actualL==expectedL,
                     "Stage14 GOT slot points to wrong symbol: "+path+":"+from.name+
                     " +"+hex(off)+" expected CGARM="+hex(expectedC)+
                     " got="+hex(actualC)+" LLVM="+hex(actualL)+
                     " expected="+hex(expectedL));
                must(out.exactSites.insert(relocationKey16(path,from.name,off,kind)).second,
                     "Stage17 duplicate verified GOT slot reference");
                ++out.slotExact;
                if(archiveMember)++out.archiveExact;
            }
        }
    }
    return out;
}


// Stage 15: independently count every ARM relocation from the original
// selected ELF objects, including archive members. The CGARM provenance
// records which INPUT section is retained, so a relocation in a discarded
// function must NOT be misreported as a live coverage gap. No observed
// patched ELF word is used to decide if a site is live.
struct CensusKind15 { size_t live=0,discarded=0,unknown=0; };
struct Census15 {
    size_t scanned=0,live=0,discarded=0,unmapped=0,unsupportedLive=0;
    size_t archivesLive=0,archivesDiscarded=0;
    std::map<uint32_t,CensusKind15> kinds;
    std::map<std::string,size_t> unmappedSections;
    struct Site { std::string object,section,symbol,status;uint32_t offset=0,kind=0; };
    std::map<std::string,Site> sites;
};
std::string relocationName15(uint32_t type){
    switch(type){
    case 2:return "R_ARM_ABS32";
    case 3:return "R_ARM_REL32";
    case 10:return "R_ARM_THM_CALL";
    case 25:return "R_ARM_BASE_PREL";
    case 26:return "R_ARM_GOT_BREL";
    case 30:return "R_ARM_THM_JUMP24";
    default:return "R_ARM_UNKNOWN_"+std::to_string(type);
    }
}
Census15 inventoryRelocations15(const Map10 &cm,const Map10 &lm,
                                  const std::vector<std::string>&objects){
    Census15 out;
    for(const auto& path:objects){
        const auto src=inspect6(path,1);
        const auto f=cm.objects.find(mapKey10(path,""));
        must(f!=cm.objects.end() && f->second==hash10(src.bytes),
             "Stage15 relocation census source fingerprint mismatch: "+path);
        const bool isArchive=virtualArchiveObjects14.count(path)!=0;
        for(const auto&rel:src.sections){
            if(rel.type!=9 && rel.type!=4)continue;
            must(rel.info<src.sections.size() && rel.link<src.sections.size(),
                 "Stage15 malformed input relocation section references: "+path);
            const auto& from=src.sections[rel.info];
            if(!(from.flags&2u))continue;
            const uint32_t stride=rel.type==9?8u:12u;
            must(rel.entrySize==stride && rel.size%stride==0,
                 "Stage15 malformed REL/RELA entries: "+path);
            const auto symtab=src.sections[rel.link];
            must(symtab.type==2 && symtab.entrySize==16 && symtab.size%16==0,
                 "Stage15 relocation references invalid symbol table: "+path);
            const auto key=mapKey10(path,from.name);
            const auto cr=cm.rows.find(key),lr=lm.rows.find(key);
            // An input section is live only when the CGARM map explicitly
            // marks it retained; LLVM must then map it too for a true crosscheck.
            bool cgLive=false;
            if(cr!=cm.rows.end())for(const auto& r:cr->second)cgLive|=r.live;
            bool llvmPresent=lr!=lm.rows.end() && !lr->second.empty();
            for(uint32_t i=0;i<rel.size/stride;++i){
                const uint64_t rp=uint64_t(rel.offset)+uint64_t(i)*stride;
                const uint32_t info=u32(src.bytes,rp+4);
                const uint32_t kind=info&255u,idx=info>>8,offset=u32(src.bytes,rp);
                must(uint64_t(idx)*16+16<=symtab.size && uint64_t(offset)+4<=from.size,
                     "Stage15 relocation symbol index/offset outside source: "+path+":"+from.name);
                ++out.scanned;
                const auto symOff=uint64_t(symtab.offset)+uint64_t(idx)*16u;
                std::string targetName="<anonymous>";
                if(symtab.link<src.sections.size()){
                    const auto& strings=src.sections[symtab.link];
                    if(strings.type==3){
                        const std::string named=str6(src.bytes,strings.offset,strings.size,
                                                     u32(src.bytes,symOff));
                        if(!named.empty())targetName=named;
                        else{
                            const uint16_t si=u16(src.bytes,symOff+14);
                            if(si<src.sections.size())targetName="["+src.sections[si].name+"]";
                        }
                    }
                }
                const auto siteKey=relocationKey16(path,from.name,offset,kind);
                Census15::Site site{path,from.name,targetName,"",offset,kind};
                auto &counts=out.kinds[kind];
                if(cr==cm.rows.end() || (cgLive && !llvmPresent)){
                    ++out.unmapped;++counts.unknown;site.status="UNMAPPED";
                    ++out.unmappedSections[path+":"+from.name];
                }else if(!cgLive){
                    ++out.discarded;++counts.discarded;site.status="DISCARDED";
                    if(isArchive)++out.archivesDiscarded;
                }else{
                    ++out.live;++counts.live;site.status="LIVE";
                    if(isArchive)++out.archivesLive;
                    if(kind!=2 && kind!=3 && kind!=10 && kind!=25 && kind!=26 && kind!=30)
                        ++out.unsupportedLive;
                }
                must(out.sites.emplace(siteKey,std::move(site)).second,
                     "Stage17 repeated/overlapping input relocation site: "+path+":"+from.name+
                     " +"+hex(offset));
            }
        }
    }
    must(out.scanned==out.live+out.discarded+out.unmapped,
         "Stage15 relocation census accounting error");
    return out;
}
// The ELF .got holds runtime pointers. Any nonzero slot whose address is
// inside this V2 image MUST appear in the packer's R_ARM_RELATIVE list.
// This prevents a deceptively correct CRC/ELF/.app pair from containing a
// local GOT pointer which would silently stay at the link base after loading.
struct DynamicGot15 {size_t slots=0,localPointers=0,relocatedLocal=0,zeroSlots=0,foreignSlots=0;};
DynamicGot15 auditDynamicGot15(const ElfView6&elf,const std::string&appPath){
    const auto app=parseApp(readFile(appPath));
    DynamicGot15 out;
    std::set<uint32_t> sites(app.sites.begin(),app.sites.end());
    std::set<uint32_t> seen;
    for(const auto&sec:elf.sections){
        if(sec.name!=".got" || sec.type!=1 || !(sec.flags&2u))continue;
        must(sec.size%4==0 && sec.address%4==0,
             "Stage15 .got has invalid word alignment");
        for(uint32_t i=0;i<sec.size;i+=4){
            const uint64_t vaddr=uint64_t(sec.address)+i;
            must(vaddr>=app.h.linkBase && vaddr-app.h.linkBase+4<=app.h.imageSize,
                 "Stage15 .got falls outside packed initialised image");
            const uint32_t site=uint32_t(vaddr-app.h.linkBase);
            must(seen.insert(site).second,"Stage15 overlapping duplicate .got slot");
            ++out.slots;
            const uint32_t ptr=word7(elf,uint32_t(vaddr));
            if(ptr==0){++out.zeroSlots;continue;}
            const uint64_t bare=uint64_t(ptr&~1u);
            if(bare>=app.h.linkBase && bare-app.h.linkBase<app.h.memorySize){
                ++out.localPointers;
                must(sites.count(site)!=0,
                     "Stage15 local GOT pointer lacks R_ARM_RELATIVE at +"+hex(site));
                ++out.relocatedLocal;
            }else{
                ++out.foreignSlots;
                // A relocation that the loader would treat as an internal
                // address cannot be a fixed external GOT pointer.
                must(sites.count(site)==0,
                     "Stage15 foreign/absolute GOT pointer has relative relocation at +"+hex(site));
            }
        }
    }
    return out;
}

// Stage 13 host-side loader contract review. This is NOT a simulation of
// Cortex-M7 execution, interrupts, MPU, cache effects or SDK/firmware calls.
struct Readiness13 {
    uint32_t entryCg=0,entryLl=0,memoryCg=0,memoryLl=0;
    size_t entryMapped=0,executableEntries=0,relocsCg=0,relocsLl=0;
};
Readiness13 verifyReadiness13(const Map10& cm,const Map10& lm,
                              const ElfView6& cg,const ElfView6& ll,
                              const std::vector<std::string>& objects,
                              const std::string& cgApp,const std::string& llApp, uint32_t maxRamBytes){
    Readiness13 out;
    const App ca=parseApp(readFile(cgApp)),la=parseApp(readFile(llApp));
    out.entryCg=cg.entry;out.entryLl=ll.entry;
    out.memoryCg=ca.h.memorySize;out.memoryLl=la.h.memorySize;
    out.relocsCg=ca.sites.size();out.relocsLl=la.sites.size();
    must(ca.h.heap==la.h.heap && ca.h.stack==la.h.stack,
         "Stage14 loader contract: different private stack/heap settings");
    // The current V2 packer reserves *private stack* separately from the
    // applet's startup/heap region. No C ABI emulation is implied.
    for(const auto& app:{std::cref(ca),std::cref(la)}){
        const auto& h=app.get().h;
        must(h.flags==1 && h.stack>=4096u && h.heap>=4096u,
             "Stage14 loader contract requires private-PSP stack and nonzero heap");
        must(h.imageSize<h.memorySize && h.heap+h.stack<h.memorySize,
             "Stage14 loader contract app memory reservations overlap");
        must(h.memorySize<=maxRamBytes,
             "Stage14 app exceeds configured RAM budget");
        // Perform another, distinct relocation/rebase simulation in SDRAM.
        const uint32_t alternate=0xD0200000u;
        must(alternate!=h.linkBase,"Stage14 alternate load base equals link base");
        (void)simulate(app.get(),alternate,false);
        for(const auto site:app.get().sites){
            must(site+4<=h.imageSize,"Stage14 reloc outside initialized image");
        }
    }
    // Confirm applet_entry in the original GCC .o agrees with BOTH entry
    // addresses, not merely that each entry is within executable memory.
    for(const auto& path:objects){
        const auto src=inspect6(path,1);
        for(const auto& f:src.functions){
            if(f.name!="applet_entry")continue;
            const auto& sec=src.sections[f.section];
            const auto cs=addrOf10(cm,path,sec,cg,true);
            const auto ls=addrOf10(lm,path,sec,ll,false);
            if(cs.size()!=1 || ls.size()!=1)continue;
            ++out.entryMapped;
            const uint32_t expectedCg=cs[0]+(f.addr&~1u);
            const uint32_t expectedLl=ls[0]+(f.addr&~1u);
            must((cg.entry&~1u)==expectedCg && (ll.entry&~1u)==expectedLl,
                 "Stage14 applet_entry does not resolve to original GCC entry section: "+
                 path+" expected CGARM "+hex(expectedCg)+", observed "+hex(cg.entry&~1u)+
                 "; LLVM "+hex(expectedLl)+", observed "+hex(ll.entry&~1u));
            must(targetExec6(cg,expectedCg) && targetExec6(ll,expectedLl),
                 "Stage14 applet_entry lies outside executable memory");
            ++out.executableEntries;
        }
    }
    must(out.entryMapped==1 && out.executableEntries==1,
         "Stage14 must independently map exactly one original GCC applet_entry");
    return out;
}
struct MapCounts10 {
    size_t candidates=0,verified=0,rel32=0,abs32=0,got=0;
    size_t noSource=0,noTarget=0,mergeSkipped=0,deadSource=0,unmappedLiveSource=0;
    size_t mergeCandidates=0,mergeVerified=0,mergeAmbiguous=0;
    size_t shortMergeVerified=0,rangeScopedVerified=0;
    size_t archiveCandidates=0,archiveVerified=0;
    std::map<std::string,size_t> sourceFailures,mergeReasons;
    std::set<std::string> exactSites;
    std::map<std::string,std::string> unresolvedSites;
    size_t bothDiscarded=0,onlyCgDiscarded=0,unmatchedButLive=0,unknownFunctions=0;
};
MapCounts10 verifyMaps10(const Map10& cgMap,const Map10& llvmMap,
                         const ElfView6& cg,const ElfView6& llvm,
                         const std::vector<std::string>& objects,
                         const std::vector<Gap8>& gaps,bool explain){
    MapCounts10 out;
    for(const auto& path:objects){
        auto src=inspect6(path,1);
        auto obj=cgMap.objects.find(mapKey10(path,""));
        must(obj!=cgMap.objects.end(),"CGARM map lacks input object: "+path);
        must(obj->second==hash10(src.bytes),"Input object changed since CGARM map generation: "+path);
        for(const auto& rel:src.sections){
            if(rel.type!=9 && rel.type!=4)continue;
            if(rel.info>=src.sections.size() || rel.link>=src.sections.size())continue;
            const auto& from=src.sections[rel.info];
            if(!(from.flags&2u) || from.type!=1)continue;
            const auto& symtab=src.sections[rel.link];
            if(symtab.type!=2 || symtab.entrySize!=16 || symtab.link>=src.sections.size())continue;
            const auto stride=rel.type==9?8u:12u;
            must(rel.entrySize==stride && rel.size%stride==0,"Malformed source relocation table");
            for(uint32_t n=0;n<rel.size/stride;++n){
                const uint64_t p=uint64_t(rel.offset)+n*stride;
                uint32_t off=u32(src.bytes,p),info=u32(src.bytes,p+4),kind=info&255u,index=info>>8;
                if(kind!=2 && kind!=3 && kind!=26)continue;
                must(uint64_t(index)*16+16<=symtab.size,"Malformed input symbol index");
                uint64_t symoff=uint64_t(symtab.offset)+uint64_t(index)*16;
                uint16_t targetSec=u16(src.bytes,symoff+14);
                // Independent section mappings are useful for source-local
                // symbols; globals resolved from OTHER .o files use Stage 9.
                if(targetSec==0 || targetSec>=src.sections.size())continue;
                const auto& target=src.sections[targetSec];
                if(!(target.flags&2u))continue;
                ++out.candidates;
                const bool archiveMember=virtualArchiveObjects14.find(path)!=virtualArchiveObjects14.end();
                if(archiveMember)++out.archiveCandidates;
                const auto cs=addrOf10(cgMap,path,from,cg,true);
                const auto ls=addrOf10(llvmMap,path,from,llvm,false);
                if(cs.size()!=1 || ls.size()!=1){
                    // A relocation in a section discarded by BOTH linkers
                    // should not be counted as a live coverage gap.
                    auto c=cgMap.rows.find(mapKey10(path,from.name));
                    auto l=llvmMap.rows.find(mapKey10(path,from.name));
                    bool discarded=c!=cgMap.rows.end() &&
                      std::none_of(c->second.begin(),c->second.end(),
                                   [](const MapSection10&r){return r.live;});
                    if(discarded && l==llvmMap.rows.end()){
                        ++out.deadSource;continue;
                    }
                    ++out.noSource;++out.unmappedLiveSource;
                    out.unresolvedSites[relocationKey16(path,from.name,off,kind)]=
                        "source section not uniquely mapped";
                    std::string why=(cs.size()!=1 ? "CGARM" : "LLVM");
                    why+=" cannot uniquely map "+path+":"+from.name;
                    ++out.sourceFailures[why];
                    continue;
                }
                must(uint64_t(off)+4<=from.size,"Relocation outside input section");
                uint32_t addend=rel.type==9?u32(src.bytes,uint64_t(from.offset)+off):u32(src.bytes,p+8);
                uint32_t symbolValue=u32(src.bytes,symoff+4);
                const auto ct=addrOf10(cgMap,path,target,cg,true);
                const auto lt=addrOf10(llvmMap,path,target,llvm,false);
                uint32_t sc=0,sl=0;
                bool resolvedMerge=false,matchedMergeShort=false,matchedMergeScoped=false;
                if(target.flags&16u){
                    ++out.mergeCandidates;
                    // Merged GOT records need separate addend/slot semantics.
                    // Never infer a GOT index from a string-content match.
                    if(kind==26){
                        ++out.mergeSkipped;++out.mergeAmbiguous;
                        out.unresolvedSites[relocationKey16(path,from.name,off,kind)]=
                            "mergeable GOT_BREL identity not implemented";
                        ++out.mergeReasons["mergeable GOT_BREL identity not yet implemented"];
                        continue;
                    }
                    const uint8_t symType=src.bytes.at(symoff+12)&15u;
                    const auto llvmRangeIt=llvmMap.rows.find(mapKey10(path,target.name));
                    const auto*llvmRanges=llvmRangeIt==llvmMap.rows.end() ? nullptr : &llvmRangeIt->second;
                    auto matched=mapMergedTarget11(src,target,symType,symbolValue,
                                                  int32_t(addend),ct,cg,llvm,llvmRanges);
                    if(!matched.valid){
                        ++out.mergeSkipped;++out.mergeAmbiguous;
                        out.unresolvedSites[relocationKey16(path,from.name,off,kind)]=
                            "mergeable "+target.name+": "+matched.reason;
                        ++out.mergeReasons[matched.reason];
                        continue;
                    }
                    sc=matched.cgAddress;sl=matched.llvmAddress;
                    resolvedMerge=true;
                    matchedMergeShort=matched.shortRecord;
                    matchedMergeScoped=matched.sourceScoped;
                }else{
                    if(ct.size()!=1 || lt.size()!=1){
                        ++out.noTarget;
                        out.unresolvedSites[relocationKey16(path,from.name,off,kind)]=
                            "target section "+target.name+" not uniquely mapped";
                        continue;
                    }
                    sc=ct[0]+symbolValue;sl=lt[0]+symbolValue;
                }
                uint32_t pc=cs[0]+off,pl=ls[0]+off;
                // Local Thumb functions retain bit 0 in the symbol value.
                if(kind==2 || kind==3){
                    const uint32_t expectedCg=(kind==2)?sc+(resolvedMerge?0:addend):
                                                         sc+(resolvedMerge?0:addend)-pc;
                    const uint32_t expectedLl=(kind==2)?sl+(resolvedMerge?0:addend):
                                                         sl+(resolvedMerge?0:addend)-pl;
                    uint32_t observedCg=word7(cg,pc),observedLl=word7(llvm,pl);
                    must(observedCg==expectedCg && observedLl==expectedLl,
                         "Stage 12 "+std::string(kind==2?"ABS32":"REL32")+
                         " source-section destination mismatch: "+path+":"+from.name+
                         " +"+hex(off)+" CGARM "+hex(observedCg)+" expected "+hex(expectedCg)+
                         " LLVM "+hex(observedLl)+" expected "+hex(expectedLl));
                    must(out.exactSites.insert(relocationKey16(path,from.name,off,kind)).second,
                         "Stage17 duplicate verified local relocation");
                    ++out.verified;
                    if(archiveMember)++out.archiveVerified;
                    if(resolvedMerge){
                        ++out.mergeVerified;
                        // Proof was independently obtained before the actual
                        // relocated word was read. Preserve this classification.
                        if(matchedMergeShort)++out.shortMergeVerified;
                        if(matchedMergeScoped)++out.rangeScopedVerified;
                    }
                    if(kind==2)++out.abs32;else ++out.rel32;
                }else{
                    const auto cGot=gotBases7(cg),lGot=gotBases7(llvm);
                    if(cGot.size()!=1 || lGot.size()!=1){
                        ++out.noTarget;
                        out.unresolvedSites[relocationKey16(path,from.name,off,kind)]=
                            "GOT base not uniquely mapped";continue;
                    }
                    const uint32_t offsetCg=word7(cg,pc)-(resolvedMerge?0:addend);
                    const uint32_t offsetLl=word7(llvm,pl)-(resolvedMerge?0:addend);
                    must(offsetCg%4==0 && offsetLl%4==0,
                         "GOT slot is misaligned at "+path+":"+from.name);
                    must(existsInElf10(cg,cGot[0]+offsetCg,4) &&
                         existsInElf10(llvm,lGot[0]+offsetLl,4),"GOT slot outside output section");
                    must(word7(cg,cGot[0]+offsetCg)==sc && word7(llvm,lGot[0]+offsetLl)==sl,
                         "Stage 12 GOT target mismatch: "+path+":"+from.name);
                    // GOT_BREL is independently classified by verifyGot13.
                    // Do not count the same source relocation twice even when
                    // this optional local GOT check ALSO succeeds.
                    ++out.verified;++out.got;
                    if(archiveMember)++out.archiveVerified;
                    if(resolvedMerge){
                        ++out.mergeVerified;
                        // Proof was independently obtained before the actual
                        // relocated word was read. Preserve this classification.
                        if(matchedMergeShort)++out.shortMergeVerified;
                        if(matchedMergeScoped)++out.rangeScopedVerified;
                    }
                }
            }
        }
    }
    if(explain){
        for(const auto& kv:out.sourceFailures)
            std::cout<<"  SOURCE NOT MAPPED ("<<kv.second<<") "<<kv.first<<"\n";
        for(const auto& kv:out.mergeReasons)
            std::cout<<"  MERGE DEFERRED ("<<kv.second<<") "<<kv.first<<"\n";
    }
    for(const auto& gap:gaps){
        const auto key=mapKey10(gap.source,gap.section);
        auto cgIt=cgMap.rows.find(key),llIt=llvmMap.rows.find(key);
        if(cgIt==cgMap.rows.end()){++out.unknownFunctions;continue;}
        bool live=false;
        for(const auto& row:cgIt->second)if(row.live)live=true;
        bool llvmPresent=llIt!=llvmMap.rows.end() && !llIt->second.empty();
        if(!live && !llvmPresent)++out.bothDiscarded;
        else if(!live && llvmPresent)++out.onlyCgDiscarded;
        else if(live)++out.unmatchedButLive;
        else ++out.unknownFunctions;
        if(explain)std::cout<<"  FUNCTION MAP "<<gap.name<<" ("<<gap.source<<") "
                            <<(live?"CGARM LIVE": "CGARM DISCARDED")<<", "
                            <<(llvmPresent?"LLVM MAP PRESENT":"LLVM MAP ABSENT")<<"\n";
    }
    return out;
}

// Independent whole-program per-site reconciliation. This cross-checks the
// actual identities of the source relocations, not merely the printed totals.
struct Ledger16 {size_t exact=0,deferred=0,discarded=0,unmapped=0;};
Ledger16 reconcileSites16(const Census15&census,const MapCounts10&locations,
                          const Branch13&branches,const Got13&got,
                          const std::string&outputPath){
    Ledger16 result;
    std::map<std::string,std::string> verified;
    auto add=[&](const std::set<std::string>& sites,const char*by){
        for(const auto& site:sites){
            auto f=census.sites.find(site);
            must(f!=census.sites.end(),std::string("Stage17 ")+by+
                 " verifier reported a relocation not present in original inputs");
            must(f->second.status=="LIVE",std::string("Stage17 ")+by+
                 " verifier claimed a discarded/unmapped source site");
            must(verified.emplace(site,by).second,
                 "Stage17 the same source relocation was independently counted twice");
        }
    };
    add(locations.exactSites,"REL32/ABS32");
    add(branches.exactSites,"Thumb branch");
    add(got.exactSites,"GOT/base");
    if(!outputPath.empty()){
        must(!std::filesystem::exists(outputPath),
             "Refusing to overwrite existing Stage17 ledger: "+outputPath);
    }
    std::ostringstream report;
    report<<"object\tinput_section\toffset\trelocation\ttarget_symbol\tstatus\tevidence\n";
    for(const auto& [key,site]:census.sites){
        std::string status=site.status,why="";
        const auto v=verified.find(key);
        if(site.status=="LIVE"){
            if(v!=verified.end()){status="EXACT";why=v->second;++result.exact;}
            else{
                status="DEFERRED";++result.deferred;
                auto l=locations.unresolvedSites.find(key);
                auto g=got.unresolvedSites.find(key);
                if(l!=locations.unresolvedSites.end())why=l->second;
                else if(g!=got.unresolvedSites.end())why=g->second;
                else why="source relocation identity not uniquely established";
            }
        }else if(site.status=="DISCARDED"){
            why="CGARM discarded source section";++result.discarded;
        }else{why="source mapping unresolved";++result.unmapped;}
        report<<site.object<<'\t'<<site.section<<'\t'<<hex(site.offset)
              <<'\t'<<relocationName15(site.kind)<<'\t'<<site.symbol
              <<'\t'<<status<<'\t'<<why<<'\n';
    }
    must(result.exact==verified.size() &&
         result.exact+result.deferred==census.live &&
         result.discarded==census.discarded && result.unmapped==census.unmapped,
         "Stage17 per-site census reconciliation failed");
    if(!outputPath.empty()){
        std::ofstream f(outputPath,std::ios::binary|std::ios::out|std::ios::trunc);
        must(bool(f),"Cannot create Stage17 ledger: "+outputPath);
        const std::string contents=report.str();
        f.write(contents.data(),std::streamsize(contents.size()));
        must(bool(f),"Could not write complete Stage17 ledger: "+outputPath);
    }
    return result;
}

void usage6(){
    std::cout<<"CGARM Stage 17 — per-site relocation reconciliation and readiness\n"
        <<"Usage: cgarm-v2-compare CGARM.elf CGARM.app LLVM.elf LLVM.app "
        <<"[--objects obj1.o obj2.o ...] [--archives libcgarm.a sb3dlibrary.a] [--load-base 0xD0100000] [--min-matched 1] [--max-ram-kb 352] [--verbose] [--explain] [--strict-live] [--emit-ledger path.tsv] [--cg-map X.cgmap --llvm-map Y.map]\n"
        <<"Use --objects and --archives to audit source, retained archive code, live Thumb calls and GOT references.\n"
        <<"Pass object filenames after --objects at the end of the command (wildcards expand in your shell).\n"
        <<"This tool DOES NOT execute ARM code or prove program equivalence.\n"
        <<"Use --explain for per-symbol unmatched-function and skipped-relocation diagnostics.\n"
        <<"--strict-live fails if any retained relocation identity is unverified; no hardware approval is implied.\n"
        <<"--emit-ledger path.tsv writes a full per-relocation evidence ledger (will NOT overwrite an existing file).\n"
        <<"Use both --cg-map (CGARM --emit-map file) and --llvm-map (original LLD -Map file) for Stage 17.\n"
        <<"--max-ram-kb (default 512) sets the host memory budget (use 352 for GUI test).\n";
}
} // namespace
int main(int argc,char** argv){
    try{
        if(argc==2 && std::string(argv[1])=="--help"){usage6();return 0;}
        if(argc<5){usage6();return 2;}
        const std::string cgElf=argv[1],cgApp=argv[2],llElf=argv[3],llApp=argv[4];
        uint32_t base=0xD0100000u, maxRamBytes=512u*1024u;
        size_t minMatched=1;
        bool verbose=false,explain=false,strictLive=false;
        enum class InputMode{None,Objects,Archives};
        InputMode inputMode=InputMode::None;
        std::string cgMapPath,llvmMapPath,ledgerPath;
        std::vector<std::string> objects, archives;
        for(int i=5;i<argc;++i){
            std::string arg=argv[i];
            if(arg=="--objects")inputMode=InputMode::Objects;
            else if(arg=="--archives")inputMode=InputMode::Archives;
            else if(arg=="--verbose")verbose=true;
            else if(arg=="--explain")explain=true;
            else if(arg=="--strict-live")strictLive=true;
            else if(arg=="--emit-ledger"){
                must(i+1<argc,"Missing --emit-ledger path");
                ledgerPath=argv[++i];
                must(!ledgerPath.empty(),"Empty --emit-ledger path");
            }
            else if(arg=="--cg-map") {must(i+1<argc,"Missing --cg-map path");cgMapPath=argv[++i];}
            else if(arg=="--llvm-map") {must(i+1<argc,"Missing --llvm-map path");llvmMapPath=argv[++i];}
            else if(arg=="--load-base"){
                must(i+1<argc,"Missing --load-base value");base=parseHex(argv[++i]);
            }else if(arg=="--max-ram-kb"){
                must(i+1<argc,"Missing --max-ram-kb value");
                const std::string val=argv[++i];
                size_t consumed=0;
                unsigned long long kb=0;
                try{kb=std::stoull(val,&consumed,10);}catch(...){throw Error("Invalid --max-ram-kb");}
                must(consumed==val.size() && kb>=16 && kb<=512,
                     "--max-ram-kb must be 16..512");
                maxRamBytes=uint32_t(kb*1024u);
            }else if(arg=="--min-matched"){
                must(i+1<argc,"Missing --min-matched value");
                std::string value=argv[++i];size_t used=0;
                unsigned long long count=0;
                try{count=std::stoull(value,&used,10);}catch(...){throw Error("Invalid --min-matched");}
                must(used==value.size() && count<=1000000,"Invalid --min-matched");
                minMatched=static_cast<size_t>(count);
            }else if(inputMode==InputMode::Objects && arg.size()>2 && arg.substr(arg.size()-2)==".o")objects.push_back(arg);
            else if(inputMode==InputMode::Archives && arg.size()>2 && arg.substr(arg.size()-2)==".a")archives.push_back(arg);
            else throw Error("Unknown argument or object/archive path: "+arg);
        }
        std::cout<<"CGARM Stage 17: side-by-side V2 check (READ ONLY; optional ledger output)\n";
        auto cg=inspectPair(cgElf,cgApp,base,false,"CGARM candidate");
        auto ll=inspectPair(llElf,llApp,base,false,"LLVM reference");
        must(cg.heap==ll.heap && cg.stack==ll.stack,"Heap / stack settings differ between linkers");
        const auto cgView=inspect6(cgElf,3),llView=inspect6(llElf,3);
        must((cgView.entry&1u) && (llView.entry&1u),"Applet entries must use Thumb state");
        must(!objects.empty(),"Use --objects followed by the identical GCC object files for meaningful code validation");
        must(ledgerPath.empty() || (!cgMapPath.empty() && !llvmMapPath.empty()),
             "--emit-ledger requires both source maps");
        if(!archives.empty()){
            must(!cgMapPath.empty() && !llvmMapPath.empty(),
                 "Archive-member audit requires BOTH --cg-map and --llvm-map");
            const auto map=readCgMap10(cgMapPath,cgView.bytes);
            const auto archiveAudit=prepareArchives14(archives,map,objects);
            std::cout<<"\nStage 17: fingerprinted archive selection:\n"
                     <<"  Archives inspected:        "<<archiveAudit.archives<<"\n"
                     <<"  Selected library members:  "<<archiveAudit.selected<<"\n"
                     <<"  Unselected library members:"<<archiveAudit.unused<<"\n"
                     <<"  Selected ELF object bytes: "<<archiveAudit.selectedBytes<<"\n";
            if(explain)for(const auto& name:archiveAudit.selectedNames)
                std::cout<<"  ARCHIVE SELECTED "<<name<<"\n";
        }
        const auto results=compareObjects6(cgView,llView,objects,verbose);
        std::cout<<"\nSource-object machine-code comparison:\n"
                 <<"  Function candidates:  "<<results.sources<<"\n"
                 <<"  Matched/verified:     "<<results.matched<<"\n"
                 <<"  Skipped/unmatched:    "<<results.skipped<<"\n"
                 <<"  Unchanged code bytes: "<<results.unmaskedBytes<<" (matched with identical GCC ET_REL)\n"
                 <<"  Link patch sites:     "<<results.linkPatches<<" (excluded from raw-byte comparison)\n"
                 <<"  Thumb branch targets: "<<results.branches<<" (both point into executable ELF sections)\n"
                 <<"  Named targets matched: "<<results.namedBranches<<" / "<<results.branches<<" branches\n"
                 <<"  Memory bytes:         CGARM="<<cg.memory<<" LLVM="<<ll.memory<<"\n"
                 <<"  Image bytes:          CGARM="<<cg.image<<" LLVM="<<ll.image<<"\n"
                 <<"  Runtime relocs:       CGARM="<<cg.reloc<<" LLVM="<<ll.reloc<<"\n";
        for(auto &kv:results.problems)std::cout<<"  SKIPPED "<<kv.second<<": "<<kv.first<<"\n";
        std::cout<<"\nStage 9 function coverage investigation:\n"
                 <<"  Unmatched source candidates: "<<results.gaps.size()<<"\n"
                 <<"  NOTE: 'not matched' is NOT proof of garbage collection.\n";
        if(explain)for(const auto& g:results.gaps) {
            std::cout<<"  FUNCTION "<<g.source<<" :: "<<g.name<<" ("<<g.section<<")\n"
                     <<"    "<<g.reason<<"; CGARM sections named="<<g.cgSections
                     <<", CGARM matching ranges="<<g.cgHits
                     <<", LLVM named symbols="<<g.llvmNamed
                     <<", LLVM matching ranges="<<g.llvmHits<<"\n";
        } else if(!results.gaps.empty()) {
            std::cout<<"  Run with --explain to list every unmatched function and its evidence.\n";
        }
        const auto refs=compareReferences7(cgView,llView,objects,verbose);
        std::cout<<"\nStage 9 legacy relocation-destination checks (separate from map coverage):\n"
                 <<"  Input relocations considered: "<<refs.references<<"\n"
                 <<"  Independently verified:      "<<refs.checked<<"\n"
                 <<"  ABS32/data pointers:         "<<refs.dataPointers<<"\n"
                 <<"  REL32/PC-relative targets:   "<<refs.pcRelative<<"\n"
                 <<"  GOT slot contents:           "<<refs.gotPointers<<"\n"
                 <<"  GOT base references:         "<<refs.gotBases<<"\n"
                 <<"  Anonymous full sections:    "<<refs.recoveredRawSection<<" (whole section uniquely matched)\n"
                 <<"  Local constant targets:    "<<refs.recoveredLocal<<" (unique source-byte windows)\n"
                 <<"  Linker heap-start symbols: "<<refs.recoveredHeap<<" (from .stack end)\n";
        for(const auto& kv:refs.skipped)
            std::cout<<"  UNVERIFIED "<<kv.second<<": "<<kv.first<<"\n";
        std::cout<<"  Unverified by relocation/target symbol type:\n";
        for(const auto& kv:refs.skippedByType)
            std::cout<<"    "<<std::setw(4)<<kv.second<<"  "<<kv.first<<"\n";
        if(explain){
            for(const auto& u:refs.unresolved) {
                std::cout<<"  REFERENCE "<<u.source<<" ["<<u.section
                         <<" +"<<hex(u.offset)<<"] "<<relocationName8(u.kind)
                         <<" -> "<<symbolType8(u.targetType)
                         <<" '"<<(u.target.empty()?"<anonymous>":u.target)
                         <<"' via '"<<(u.anchor.empty()?"<no anchor>":u.anchor)
                         <<"': "<<u.reason<<"\n";
            }
        }else if(!refs.unresolved.empty()){
            std::cout<<"  Run with --explain to list each unverifiable reference.\n";
        }
        must(cgMapPath.empty()==llvmMapPath.empty(),"Pass both --cg-map and --llvm-map together");
        size_t stage11Verified=0;
        if(!cgMapPath.empty()){
            const auto cgMap=readCgMap10(cgMapPath,cgView.bytes);
            const auto llvmMap=readLldMap10(llvmMapPath);
            const auto provenance=verifyMaps10(cgMap,llvmMap,cgView,llView,objects,results.gaps,explain);
            stage11Verified=provenance.verified;
            const auto sectionBytes=verifySectionBytes12(cgMap,llvmMap,cgView,llView,objects);
            std::cout<<"\nStage 17: retained source-section byte parity:\n"
                     <<"  Retained sections compared:  "<<sectionBytes.sections<<"\n"
                     <<"  Compiler bytes checked:     "<<sectionBytes.bytes<<"\n"
                     <<"  Of which library bytes:    "<<sectionBytes.archiveBytes
                     <<" ("<<sectionBytes.archiveSections<<" retained archive sections)\n"
                     <<"    Executable: "<<sectionBytes.code<<"  Writable: "<<sectionBytes.data
                     <<"  Read-only: "<<sectionBytes.readOnly<<"\n"
                     <<"  Relocation bytes excluded: "<<sectionBytes.masked
                     <<" (library="<<sectionBytes.archiveMasked<<")\n"
                     <<"  Discarded sections skipped:"<<sectionBytes.discarded<<"\n"
                     <<"  Mergeable sections skipped:"<<sectionBytes.mergeable<<"\n"
                     <<"  Unmapped/uncertain sections:"<<sectionBytes.unmapped<<"\n";
            std::cout<<"\nStage 17: source-section provenance + mergeable targets:\n"
                     <<"  Candidate local relocations:   "<<provenance.candidates<<"\n"
                     <<"  Verified through section maps:"<<provenance.verified<<"\n"
                     <<"  Of which archive references:"<<provenance.archiveVerified
                     <<" / "<<provenance.archiveCandidates<<" candidates\n"
                     <<"    REL32: "<<provenance.rel32<<"  ABS32: "<<provenance.abs32
                     <<"  GOT_BREL: "<<provenance.got<<"\n"
                     <<"  Unmapped/uncertain refs:    "<<provenance.noSource<<"\n"
                     <<"  Discarded-source refs:      "<<provenance.deadSource<<"\n"
                     <<"  Unmapped target sections:    "<<provenance.noTarget<<"\n"
                     <<"  Mergeable targets attempted:  "<<provenance.mergeCandidates<<"\n"
                     <<"  Mergeable targets verified:   "<<provenance.mergeVerified<<"\n"
                     <<"  Mergeable target deferred:    "<<provenance.mergeSkipped<<"\n"
                     <<"  One-byte records EXACT:      "<<provenance.shortMergeVerified<<"\n"
                     <<"  LLVM map-scoped EXACT:       "<<provenance.rangeScopedVerified<<"\n"
                     <<"  Unmatched functions mapped as:\n"
                     <<"    CGARM discarded / LLVM absent: "<<provenance.bothDiscarded<<"\n"
                     <<"    CGARM discarded / LLVM present:"<<provenance.onlyCgDiscarded<<"\n"
                     <<"    CGARM live but unmatched:      "<<provenance.unmatchedButLive<<"\n"
                     <<"    Unknown status:                "<<provenance.unknownFunctions<<"\n";
            // Do not conflate 'not present in LLD map' with a formal GC proof.
            if(provenance.onlyCgDiscarded)
                std::cout<<"  CAUTION: CGARM discarded sections that appear in LLVM's map. Inspect before hardware use.\n";
            std::cout<<"  NOTE: LLVM map absence is evidence, not a definitive GC certificate.\n";
            const auto originalDefinitions=collectDefinitions14(cgMap,llvmMap,cgView,llView,objects);
            const auto branches=verifyBranches13(cgMap,llvmMap,cgView,llView,objects,originalDefinitions,explain);
            std::cout<<"\nStage 17: source-defined global symbols: "<<originalDefinitions.size()
                     <<" named definition sets available for independent branch/GOT target mapping\n";
            std::cout<<"\nStage 17: supplied-object retained Thumb BL/B.W audit:\n"
                     <<"  Input branches considered: "<<branches.input<<"\n"
                     <<"  Retained branch sites:    "<<branches.live<<"\n"
                     <<"  Target in executable:    "<<branches.execValid<<"\n"
                     <<"  Exact local destinations: "<<branches.localExact<<"\n"
                     <<"  Exact named destinations: "<<branches.externalExact<<"\n"
                     <<"  Target identities deferred:"<<branches.unresolved<<"\n"
                     <<"  Archive Thumb branches:    "<<branches.archiveLive
                     <<" live, "<<branches.archiveExact<<" exact destinations\n"
                     <<"  Discarded-source branches:"<<branches.discarded<<"\n"
                     <<"  Unmapped branch sites:   "<<branches.unmapped<<"\n";
            if(explain)for(const auto& r:branches.reasons)
                std::cout<<"  BRANCH DEFERRED REASON ("<<r.second<<") "<<r.first<<"\n";
            must(branches.execValid==branches.live && branches.unmapped==0,
                 "Stage14 has unverified live Thumb branch sites");
            const auto commonAudit=mapCommon17(cgMap,llvmMap,cgView,llView,objects);
            std::cout<<"\nStage 17: SHN_COMMON independent storage audit:\n"
                     <<"  Live COMMON symbols considered: "<<commonAudit.relevant<<"\n"
                     <<"  Proven allocations:           "<<commonAudit.proven.size()<<"\n"
                     <<"  Deferred allocations:         "<<commonAudit.deferred.size()<<"\n";
            if(explain)for(const auto&entry:commonAudit.deferred)
                std::cout<<"  COMMON DEFERRED "<<entry.first<<": "<<entry.second<<"\n";
            const auto gotAudit=verifyGot13(cgMap,llvmMap,cgView,llView,objects,originalDefinitions,commonAudit);
            std::cout<<"\nStage 17: map-backed GOT and base audit:\n"
                     <<"  Input GOT/base sites:      "<<gotAudit.input<<"\n"
                     <<"  Retained GOT/base sites:   "<<gotAudit.live<<"\n"
                     <<"  Verified GOT base links:   "<<gotAudit.baseExact<<"\n"
                     <<"  Verified GOT slot targets: "<<gotAudit.slotExact<<"\n"
                     <<"  Deferred GOT identities:   "<<gotAudit.deferred<<"\n"
                     <<"  Archive GOT/base sites:    "<<gotAudit.archiveLive
                     <<" live, "<<gotAudit.archiveExact<<" exact identities\n"
                     <<"  Discarded-source GOT sites:"<<gotAudit.discarded<<"\n"
                     <<"  Unmapped GOT sites:        "<<gotAudit.unmapped<<"\n";
            if(explain)for(const auto& reason:gotAudit.reasons)
                std::cout<<"  GOT DEFERRED ("<<reason.second<<") "<<reason.first<<"\n";
            must(gotAudit.unmapped==0,"Stage14 has unmapped retained GOT sites");
            const auto census=inventoryRelocations15(cgMap,llvmMap,objects);
            const auto dynamicCg=auditDynamicGot15(cgView,cgApp);
            const auto dynamicLl=auditDynamicGot15(llView,llApp);
            std::cout<<"\nStage 17: WHOLE-PROGRAM source relocation census:\n"
                     <<"  Relocations scanned:       "<<census.scanned<<"\n"
                     <<"  Retained source sites:     "<<census.live<<"\n"
                     <<"  Discarded source sites:    "<<census.discarded<<"\n"
                     <<"  Unknown/missing map sites: "<<census.unmapped<<"\n"
                     <<"  Retained archive sites:    "<<census.archivesLive<<"\n"
                     <<"  Unsupported live types:   "<<census.unsupportedLive<<"\n";
            for(const auto& [kind,n]:census.kinds){
                std::cout<<"    "<<std::left<<std::setw(19)<<relocationName15(kind)
                         <<std::right<<" live="<<n.live
                         <<" discarded="<<n.discarded<<" unknown="<<n.unknown<<"\n";
            }
            const auto ledger=reconcileSites16(census,provenance,branches,gotAudit,ledgerPath);
            std::cout<<"\nStage 17: individual-source relocation ledger:\n"
                     <<"  Exactly verified live sites: "<<ledger.exact<<" / "<<census.live<<"\n"
                     <<"  Deferred live sites:         "<<ledger.deferred<<"\n"
                     <<"  Discarded source sites:      "<<ledger.discarded<<"\n"
                     <<"  Unmapped source sites:       "<<ledger.unmapped<<"\n";
            if(!ledgerPath.empty())std::cout<<"  Full ledger written:         "<<ledgerPath<<"\n";
            const size_t independentlyChecked=provenance.rel32+provenance.abs32+
                branches.localExact+branches.externalExact+gotAudit.baseExact+gotAudit.slotExact;
            const size_t reportedLive=provenance.rel32+provenance.abs32+
                provenance.mergeSkipped+provenance.noSource+provenance.noTarget+
                branches.live+gotAudit.live;
            must(independentlyChecked==ledger.exact,
                 "Stage17 old aggregate count disagrees with individually verified sites");
            const size_t gapCount=ledger.deferred;
            std::cout<<"\nStage 17: relocation-family coverage:\n"
                     <<"  Exact independently checked: "<<independentlyChecked
                     <<" / "<<census.live<<" live relocations\n"
                     <<"  Live identities deferred:    "<<gapCount<<"\n"
                     <<"    REL32 data:  "<<provenance.rel32<<" exact, "
                     <<(census.kinds.count(3)?census.kinds.at(3).live-provenance.rel32:0)
                     <<" deferred\n"
                     <<"    Thumb BL/B.W: "<<(branches.localExact+branches.externalExact)
                     <<" exact, "<<branches.unresolved<<" deferred\n"
                     <<"    GOT/base:    "<<(gotAudit.baseExact+gotAudit.slotExact)
                     <<" exact, "<<gotAudit.deferred<<" deferred\n"
                     <<"    ABS32:       "<<provenance.abs32<<" exact\n";
            std::cout<<"\nStage 17: dynamic GOT rebase-site audit:\n"
                     <<"  CGARM: "<<dynamicCg.localPointers<<" / "<<dynamicCg.slots
                     <<" local pointer slots have runtime relocations\n"
                     <<"  LLVM:  "<<dynamicLl.localPointers<<" / "<<dynamicLl.slots
                     <<" local pointer slots have runtime relocations\n";
            must(census.unsupportedLive==0,
                 "Stage15 found unsupported retained ARM relocation types");
            must(census.kinds.count(3)==0 ||
                 provenance.rel32<=census.kinds.at(3).live,
                 "Stage15 REL32 verifier count exceeds retained source relocations");
            const size_t liveBranches=(census.kinds.count(10)?census.kinds.at(10).live:0)+
                                      (census.kinds.count(30)?census.kinds.at(30).live:0);
            const size_t liveGot=(census.kinds.count(25)?census.kinds.at(25).live:0)+
                                 (census.kinds.count(26)?census.kinds.at(26).live:0);
            must(branches.live==liveBranches && gotAudit.live==liveGot,
                 "Stage15 branch/GOT verifier does not account for ALL retained sites");
            must(independentlyChecked<=census.live,
                 "Stage15 independently verified relocation count exceeds actual live count");
            if(reportedLive!=census.live)
                std::cout<<"  CAUTION: some retained relocations are not classified by previous identity checks ("
                         <<(reportedLive<census.live?census.live-reportedLive:reportedLive-census.live)
                         <<" site difference).\n";
            if(census.unmapped)std::cout<<"  CAVEAT: "<<census.unmapped<<" input relocations belong to sections not\n"
                <<"          corroborated by both maps (e.g. .ARM.exidx); not counted live.\n";
            if(explain)for(const auto&kv:census.unmappedSections)
                std::cout<<"  SOURCE WITHOUT MAP ("<<kv.second<<") "<<kv.first<<"\n";
            if(strictLive){
                must(census.unmapped==0 && gapCount==0 && reportedLive==census.live &&
                     ledger.deferred==0 && branches.unresolved==0 && gotAudit.deferred==0 &&
                     provenance.mergeSkipped==0 && provenance.noSource==0 &&
                     provenance.noTarget==0,
                     "Stage17 strict-live gate: unresolved retained relocation identities remain; do not deploy");
                std::cout<<"  STRICT-LIVE GATE: fully covered (host verification only)\n";
            }else if(gapCount>0){
                std::cout<<"  STATUS: partial identity coverage; strict gate would reject (use --strict-live).\n";
            }
            const auto loader=verifyReadiness13(cgMap,llvmMap,cgView,llView,objects,cgApp,llApp,maxRamBytes);
            std::cout<<"\nStage 17: host loader-readiness contract:\n"
                     <<"  Source applet_entry mapped: "<<loader.entryMapped<<" / 1\n"
                     <<"  Entries in executable code:"<<loader.executableEntries<<" / 1\n"
                     <<"  Alternate SDRAM rebases: 2 / 2 passed\n"
                     <<"  Dynamic relocation sites: CGARM="<<loader.relocsCg<<" LLVM="<<loader.relocsLl<<"\n"
                     <<"  Reserved bytes: CGARM="<<loader.memoryCg<<" LLVM="<<loader.memoryLl<<"\n"
                     <<"  Configured memory budget: "<<maxRamBytes<<" bytes\n"
                     <<"  Status: HOST CONTRACT ONLY; NOT HARDWARE CERTIFICATION\n";
            must(provenance.verified>0 || branches.localExact+branches.externalExact>0 ||
                 gotAudit.baseExact+gotAudit.slotExact>0,
                 "Stage 17 no independently verified relocation identities");
        }
        must(results.matched>=minMatched,"Not enough matched functions for --min-matched threshold");
        must(results.unmaskedBytes>0,"No unrelocated machine code bytes were verified");
        must(refs.checked>0 || stage11Verified>0,
             "No relocation destinations independently verified by Stage 9 or Stage 12");
        std::cout<<"\nPASS: Stage 5 ELF/APP parity, Stage 6 matched code, checked relocation identities"
                    <<(cgMapPath.empty()?".":", including Stage 17 COMMON-backed and individually reconciled relocation identities, archive byte parity, Thumb/GOT, full relocation census, GOT rebase-site checks and loader audits.")<<"\n"
                 <<"COVERAGE: supplied .o files and any map-selected --archives members; unique relocation identities only.\n"
                 <<"UNCHECKED: explicitly deferred live identities, untracked source sections, nonselected archive code, actual runtime execution and ABI.\n"
                 <<"NOT PROVEN: ABI/runtime equivalence, unmatched functions, real-device execution.\n";
        return 0;
    }catch(const std::exception& e){
        std::cerr<<"CGARM Stage 17 FAILED: "<<e.what()<<"\n";return 1;
    }
}
