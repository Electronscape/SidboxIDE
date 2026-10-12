// SIDBOX V2 native ELF32 ARM ET_DYN -> SBAPV2 packer.
// Self-contained C++17 host tool. No LLVM or ELF library at runtime.
// Reconstituted for the portable SDK because the 1701D archive contained
// the packer executable and CMake target, but not the original source file.
// Supports the full applet/music SDRAM range below 0xD0600000; does NOT
// bypass ELF, relocation, stack, memory-range, or CRC validation.
#include <algorithm>
#include <cstdint>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>
#if defined(_WIN32)
#include <process.h>
#define SIDBOX_GETPID _getpid
#else
#include <unistd.h>
#define SIDBOX_GETPID getpid
#endif

namespace {
using Bytes = std::vector<uint8_t>;
namespace fs = std::filesystem;
struct Error : std::runtime_error { using std::runtime_error::runtime_error; };
void require(bool good, const std::string &s) { if (!good) throw Error(s); }
constexpr uint32_t RAM_FIRST=0xD0000000u;
constexpr uint32_t RAM_END=0xD0600000u; // 6 MiB application/music area.
constexpr uint64_t ONE_MIB=1024ULL*1024ULL;
constexpr uint32_t ELF32_HEADER=52;
constexpr uint32_t APP_HEADER=64;
void span(const Bytes &v,uint64_t p,uint64_t n,const std::string &why) {
    require(p<=v.size() && n<=v.size()-p,"Truncated/corrupt "+why);
}
uint16_t word16(const Bytes &b,uint64_t o) {
    span(b,o,2,"ELF u16");return static_cast<uint16_t>(b[static_cast<size_t>(o)]|uint16_t(b[static_cast<size_t>(o+1)])<<8);
}
uint32_t word32(const Bytes &b,uint64_t o) {
    span(b,o,4,"ELF u32");
    return uint32_t(b[static_cast<size_t>(o)])|(uint32_t(b[static_cast<size_t>(o+1)])<<8)|
           (uint32_t(b[static_cast<size_t>(o+2)])<<16)|(uint32_t(b[static_cast<size_t>(o+3)])<<24);
}
void put32(Bytes &b,uint64_t o,uint32_t value) {
    span(b,o,4,"V2 header write");for(int j=0;j<4;++j)b[static_cast<size_t>(o+j)]=static_cast<uint8_t>(value>>(j*8));
}
uint32_t checked32(uint64_t n,const std::string &w) {
    require(n<=UINT32_MAX,"32-bit overflow: "+w);return static_cast<uint32_t>(n);
}
uint32_t align32(uint64_t n) {
    return checked32((n+31ULL)&~31ULL,"aligned applet bytes");
}
uint32_t align4(uint64_t n) {
    return checked32((n+3ULL)&~3ULL,"relocation offset");
}
uint32_t crc32(const Bytes &image) {
    uint32_t c=0xffffffffu;
    for(uint8_t b:image) {c^=b;for(int i=0;i<8;++i)c=(c>>1)^((c&1u)?0xedb88320u:0u);}
    return ~c;
}
Bytes readFile(const fs::path &p) {
    std::ifstream in(p,std::ios::binary|std::ios::ate);
    require(bool(in),"Cannot open ELF: "+p.string());
    const auto length=in.tellg();
    require(length>0 && uint64_t(length)<=64u*ONE_MIB,"ELF file empty or too large");
    Bytes data(static_cast<size_t>(length));in.seekg(0);
    require(bool(in.read(reinterpret_cast<char*>(data.data()),std::streamsize(data.size()))),"Cannot read ELF: "+p.string());
    return data;
}
std::string sectionName(const Bytes &b,uint64_t tableStart,uint32_t tableLength,uint32_t index) {
    require(index<tableLength,"Section name exceeds ELF string table");
    span(b,tableStart,tableLength,"ELF section name table");
    const size_t begin=static_cast<size_t>(tableStart+index);
    const size_t end=static_cast<size_t>(tableStart+tableLength);
    size_t pos=begin;while(pos<end && b[pos]!=0)++pos;
    require(pos<end,"ELF section name not terminated");
    return std::string(reinterpret_cast<const char*>(b.data()+begin),pos-begin);
}
uint32_t decimal(const std::string &s,const std::string &flag) {
    require(!s.empty() && s[0]!='-',flag+": expected a non-negative integer");
    uint64_t n=0;
    for(char c:s){require(c>='0'&&c<='9',flag+": expected a decimal integer");
        const unsigned digit=static_cast<unsigned>(c-'0');
        require(n<=(UINT32_MAX-digit)/10u,flag+": value exceeds 32-bit range");
        n=n*10u+digit;}
    return static_cast<uint32_t>(n);
}
struct Load {uint32_t offset,addr,filesz,memsz;};
struct ELF {
    uint32_t base=0, entry=0, memSpan=0;
    Bytes image;
    std::vector<uint32_t> relocs;
};
ELF parseElf(const Bytes &b,uint32_t requestedStack) {
    span(b,0,ELF32_HEADER,"ELF32 header");
    require(b[0]==0x7f && b[1]=='E' && b[2]=='L' && b[3]=='F' &&
            b[4]==1 && b[5]==1 && b[6]==1,"Expected little-endian ELF32");
    require(word16(b,16)==3 && word16(b,18)==40,"Expected ARM ET_DYN position-independent ELF");
    const uint32_t entry=word32(b,24),phoff=word32(b,28),shoff=word32(b,32);
    const uint16_t phent=word16(b,42),phcnt=word16(b,44),shent=word16(b,46),shcnt=word16(b,48),shstr=word16(b,50);
    require(phent==32 && phcnt>0 && phcnt<=64 && shent==40 && shcnt>0 && shcnt<=4096 && shstr<shcnt,
            "Invalid ELF program/section table parameters");
    span(b,phoff,uint64_t(phent)*phcnt,"ELF program headers");
    span(b,shoff,uint64_t(shent)*shcnt,"ELF section headers");
    uint64_t base=std::numeric_limits<uint64_t>::max(),fileEnd=0,memEnd=0;
    std::vector<Load> loads;
    for(uint32_t i=0;i<phcnt;++i){
        uint64_t p=uint64_t(phoff)+32*i;
        const uint32_t type=word32(b,p),off=word32(b,p+4),addr=word32(b,p+8);
        const uint32_t filesz=word32(b,p+16),memsz=word32(b,p+20);
        require(type!=3,"ELF PT_INTERP is not supported");
        if(type==2) {
            require(memsz>=filesz && filesz%8==0,"Invalid ELF PT_DYNAMIC segment");
            span(b,off,filesz,"PT_DYNAMIC data");
            for(uint64_t t=off;t<uint64_t(off)+filesz;t+=8){
                const uint32_t tag=word32(b,t);
                require(tag!=1 && tag!=7 && tag!=23,"Unsupported dynamic dependency/relocation tag");
            }
        }
        if(type!=1) continue;
        require(filesz<=memsz,"PT_LOAD file bytes exceed memory bytes");
        span(b,off,filesz,"ELF PT_LOAD bytes");
        base=std::min(base,uint64_t(addr));
        fileEnd=std::max(fileEnd,uint64_t(addr)+filesz);
        memEnd=std::max(memEnd,uint64_t(addr)+memsz);
        loads.push_back({off,addr,filesz,memsz});
    }
    require(!loads.empty() && base>=RAM_FIRST && base<RAM_END && fileEnd>base && memEnd>=fileEnd &&
            memEnd<=RAM_END,"ELF PT_LOAD exceeds SIDBOX V2 SDRAM application region");
    const uint32_t fileSpan=checked32(fileEnd-base,"ELF image length");
    const uint32_t memorySpan=checked32(memEnd-base,"ELF memory length");
    require(fileSpan>0 && fileSpan<=6u*ONE_MIB,"Invalid ELF initialized-image length");
    ELF elf;elf.base=checked32(base,"ELF link base");elf.entry=entry;elf.memSpan=memorySpan;
    elf.image.assign(fileSpan,0u);
    Bytes written(fileSpan,0u);
    for(const Load &l:loads){
        const uint64_t dst=uint64_t(l.addr)-base;
        require(dst+l.filesz<=elf.image.size(),"PT_LOAD beyond image span");
        for(uint64_t j=0;j<l.filesz;++j){
            const size_t at=static_cast<size_t>(dst+j);
            const uint8_t value=b[static_cast<size_t>(uint64_t(l.offset)+j)];
            require(!written[at] || elf.image[at]==value,"Conflicting PT_LOAD segment bytes");
            written[at]=1;elf.image[at]=value;
        }
    }
    const uint64_t namesHead=uint64_t(shoff)+uint64_t(shstr)*40;
    const uint32_t namesOffset=word32(b,namesHead+16),namesSize=word32(b,namesHead+20);
    span(b,namesOffset,namesSize,"ELF section names");
    bool stackFound=false;
    for(uint32_t i=0;i<shcnt;++i){
        const uint64_t p=uint64_t(shoff)+uint64_t(i)*40;
        const uint32_t nameOff=word32(b,p),type=word32(b,p+4),addr=word32(b,p+12),off=word32(b,p+16);
        const uint32_t size=word32(b,p+20),entrySize=word32(b,p+36);
        const std::string name=sectionName(b,namesOffset,namesSize,nameOff);
        if(name==".stack") {
            require(!stackFound,"Duplicate ELF .stack section");stackFound=true;
            require(type==8 && size==requestedStack && uint64_t(addr)+size==memEnd && addr>=fileEnd,
                    "ELF .stack section does not match the requested stack allocation");
        }
        const bool rel=name.rfind(".rel.dyn",0)==0 || name.rfind(".rela.dyn",0)==0 ||
                       name.rfind(".rel.plt",0)==0 || name.rfind(".rela.plt",0)==0;
        if(!rel) continue;
        require(name.rfind(".rel.dyn",0)==0 && type==9 && entrySize==8 && size%8==0,
                "Unsupported ELF dynamic relocation section: "+name);
        span(b,off,size,"ELF .rel.dyn data");
        for(uint64_t r=off;r<uint64_t(off)+size;r+=8){
            const uint32_t location=word32(b,r),info=word32(b,r+4);
            require(info==23u,"Only R_ARM_RELATIVE relocation with symbol zero is supported");
            require(location>=base && uint64_t(location)+4<=fileEnd,
                    "Dynamic relocation site outside the initialized image");
            const uint32_t site=location-elf.base;
            require((site&3u)==0,"Unaligned dynamic relocation site");
            elf.relocs.push_back(site);
        }
    }
    if(requestedStack) require(stackFound,"ELF lacks reserved private PSP .stack section");
    std::sort(elf.relocs.begin(),elf.relocs.end());
    require(!elf.relocs.empty(),"ELF contains no R_ARM_RELATIVE dynamic relocations");
    require(std::adjacent_find(elf.relocs.begin(),elf.relocs.end())==elf.relocs.end(),
            "Duplicate dynamic relocation site");
    require((entry&1u)!=0 && uint64_t(entry&~1u)>=base && uint64_t(entry&~1u)<fileEnd,
            "ELF Thumb entry is outside initialized image");
    return elf;
}
Bytes pack(const ELF &e,uint32_t heap,uint32_t stack){
    require((heap&31u)==0,"Heap allocation must be 32-byte aligned");
    require(!stack || (stack>=4096u && (stack&31u)==0),
            "Private PSP stack must be >=4096 bytes, 32-byte aligned");
    const uint32_t mem=align32(uint64_t(e.memSpan)+heap);
    require(e.base>=RAM_FIRST && e.base<RAM_END && mem<=RAM_END-e.base,
            "V2 applet RAM allowance exceeds the SDRAM applet/music area");
    require(heap<=mem-e.image.size() && (!stack || stack<=mem-heap-e.image.size()),
            "Heap/stack overlap the initialized image");
    const uint32_t relocationOffset=align4(uint64_t(APP_HEADER)+e.image.size());
    const uint32_t filesize=checked32(uint64_t(relocationOffset)+uint64_t(e.relocs.size())*4ULL,
                                      "packed V2 file length");
    Bytes result(filesize,0);
    std::memcpy(result.data(),"SBAPV2\0\0",8);
    const uint32_t header[14]={2u,64u,filesize,checked32(e.image.size(),"image bytes"),mem,
                               e.entry-e.base,e.base,relocationOffset,
                               checked32(e.relocs.size(),"relocation count"),32u,
                               heap,stack,stack?1u:0u,crc32(e.image)};
    for(size_t i=0;i<14;++i)put32(result,8+i*4,header[i]);
    std::copy(e.image.begin(),e.image.end(),result.begin()+APP_HEADER);
    for(size_t i=0;i<e.relocs.size();++i)put32(result,relocationOffset+i*4,e.relocs[i]);
    return result;
}
void writeOutput(const fs::path &dst,const Bytes &b) {
    require(!fs::is_symlink(dst),"Refusing to overwrite output symbolic link: "+dst.string());
    const fs::path dir=dst.has_parent_path()?dst.parent_path():fs::path(".");
    require(fs::is_directory(dir),"Output directory does not exist: "+dir.string());
    const fs::path tmp=dst.string()+".sidbox-packer-"+std::to_string(SIDBOX_GETPID())+".tmp";
    require(!fs::exists(tmp)&&!fs::is_symlink(tmp),"Temporary output already exists: "+tmp.string());
    try {
        std::ofstream out(tmp,std::ios::binary|std::ios::trunc);
        require(bool(out),"Cannot create temporary V2 .app file: "+tmp.string());
        out.write(reinterpret_cast<const char*>(b.data()),std::streamsize(b.size()));
        out.close();
        require(bool(out),"Cannot finish V2 .app file: "+tmp.string());
        require(!fs::is_symlink(dst),"Output became a symbolic link during packaging");
        fs::rename(tmp,dst);
    } catch(...) {std::error_code ec;fs::remove(tmp,ec);throw;}
}
void usage(){
    std::cerr<<"Usage: sidbox-v2-packer <input.elf> <output.app> [--heap <bytes>] [--stack <bytes>]\n";
}
} // namespace
int main(int argc,char **argv) {
    try {
        if(argc<3 || (argc==2 && std::string(argv[1])=="--help")) {usage();return argc==2?0:2;}
        const fs::path input=argv[1],output=argv[2];
        bool heapProvided=false,stackProvided=false;
        uint32_t heap=0,stack=0;
        for(int i=3;i<argc;++i){
            const std::string a=argv[i];
            require(a=="--heap"||a=="--stack","Unknown V2 packer option: "+a);
            require(i+1<argc,"Missing value for "+a);
            if(a=="--heap") {require(!heapProvided,"Duplicate --heap");heapProvided=true;heap=decimal(argv[++i],a);}
            else {require(!stackProvided,"Duplicate --stack");stackProvided=true;stack=decimal(argv[++i],a);}
        }
        const ELF elf=parseElf(readFile(input),stack);
        const Bytes app=pack(elf,heap,stack);
        writeOutput(output,app);
        std::cout<<"V2 native: "<<output<<"; image "<<elf.image.size()<<"B, memory "
                 <<word32(app,24)<<"B, relocations "<<elf.relocs.size()
                 <<", private PSP "<<stack<<"B\n";
        return 0;
    }catch(const std::exception &e){std::cerr<<"ERROR: V2 packer: "<<e.what()<<'\n';return 1;}
}
