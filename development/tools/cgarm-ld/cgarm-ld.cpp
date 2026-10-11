/*
 * cgarm-ld — SIDBOX CGARM ELF linker project, Stage 10.
 *
 * This experimental build adds a minimal ELF32/ARM ET_DYN writer with
 * PT_LOAD, PT_DYNAMIC, .rel.dyn R_ARM_RELATIVE, .dynamic and .stack.
 * It is independent of LLVM, Qt, libelf and the ARM GNU toolchain.
 *
 * IMPORTANT: the ELF is a validation artifact, NOT production-ready.
 * Preserve the existing LLVM-based linker for all real SIDBOX applets.
 * Production builds must continue using LLVM ld.lld.
 *
 * Copyright: reserved to the project owner. No third-party code used.
 */

#include <algorithm>
#include <cctype>
#include <cstdint>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <deque>
#include <filesystem>
#include <tuple>
#include <vector>

namespace {

struct Error : std::runtime_error { using std::runtime_error::runtime_error; };
using Bytes = std::vector<uint8_t>;

constexpr uint32_t SHT_SYMTAB = 2, SHT_RELA = 4, SHT_REL = 9, SHT_NOBITS = 8;
constexpr uint32_t SHF_WRITE = 1, SHF_ALLOC = 2, SHF_EXECINSTR = 4, SHF_LINK_ORDER = 128;
constexpr uint32_t SHT_GROUP = 17;
constexpr uint16_t SHN_UNDEF = 0, SHN_ABS = 0xfff1, SHN_COMMON = 0xfff2;
constexpr uint8_t STB_LOCAL = 0, STB_GLOBAL = 1, STB_WEAK = 2;

uint64_t sum(uint64_t a, uint64_t b) {
    if (b > std::numeric_limits<uint64_t>::max() - a) throw Error("Integer overflow in input size");
    return a + b;
}
void check(const Bytes &b, uint64_t offset, uint64_t count, const std::string &where) {
    if (sum(offset, count) > b.size()) throw Error(where + ": truncated/corrupt file");
}
uint8_t u8(const Bytes &b, uint64_t pos, const std::string &who) {
    check(b, pos, 1, who); return b[static_cast<size_t>(pos)];
}
uint16_t u16(const Bytes &b, uint64_t pos, const std::string &who) {
    check(b, pos, 2, who);
    return static_cast<uint16_t>(b[static_cast<size_t>(pos)] | (uint16_t(b[static_cast<size_t>(pos+1)]) << 8));
}
uint32_t u32(const Bytes &b, uint64_t pos, const std::string &who) {
    check(b, pos, 4, who);
    return uint32_t(b[static_cast<size_t>(pos)]) | (uint32_t(b[static_cast<size_t>(pos+1)]) << 8)
        | (uint32_t(b[static_cast<size_t>(pos+2)]) << 16) | (uint32_t(b[static_cast<size_t>(pos+3)]) << 24);
}
std::string stringAt(const Bytes &b, uint64_t begin, uint64_t length, uint64_t offset, const std::string &where) {
    if (offset >= length) throw Error(where + ": invalid string-table offset");
    check(b, begin, length, where);
    const uint64_t first = begin + offset, end = begin + length;
    uint64_t p = first;
    while (p < end && b[static_cast<size_t>(p)] != 0) ++p;
    if (p == end) throw Error(where + ": unterminated string-table entry");
    return std::string(b.begin() + static_cast<ptrdiff_t>(first), b.begin() + static_cast<ptrdiff_t>(p));
}
Bytes load(const std::string &filename) {
    std::ifstream f(filename, std::ios::binary | std::ios::ate);
    if (!f) throw Error("Cannot open " + filename);
    auto n = f.tellg();
    if (n < 0) throw Error("Cannot read file size of " + filename);
    if (uint64_t(n) > uint64_t(std::numeric_limits<size_t>::max())) throw Error("File too large: " + filename);
    f.seekg(0);
    Bytes b(static_cast<size_t>(n));
    if (!b.empty() && !f.read(reinterpret_cast<char *>(b.data()), n)) throw Error("Cannot read " + filename);
    return b;
}
std::string trim(std::string s) {
    while (!s.empty() && std::isspace(static_cast<unsigned char>(s.back()))) s.pop_back();
    size_t p = 0;
    while (p < s.size() && std::isspace(static_cast<unsigned char>(s[p]))) ++p;
    return s.substr(p);
}
uint64_t parseDecimal(const std::string &s, const std::string &where) {
    const std::string t = trim(s);
    if (t.empty()) throw Error(where + ": empty decimal number");
    uint64_t n = 0;
    for (char c : t) {
        if (c < '0' || c > '9') throw Error(where + ": malformed decimal number: " + t);
        if (n > (std::numeric_limits<uint64_t>::max() - uint64_t(c-'0'))/10) throw Error(where + ": decimal overflow");
        n = n*10 + uint64_t(c-'0');
    }
    return n;
}

struct Section {
    std::string name;
    uint32_t type = 0, flags = 0, offset = 0, size = 0, link = 0, info = 0, align = 0, entsize = 0;
    int group = -1;
};
struct Symbol {
    std::string name;
    uint32_t value = 0, size = 0;
    uint16_t shndx = 0;
    uint8_t binding = 0, type = 0;
};
struct Reloc {
    uint32_t type = 0, offset = 0, symbolIndex = 0, targetIndex = 0;
    uint16_t symbolSection = SHN_UNDEF;
    uint8_t symbolBinding = STB_GLOBAL;
    std::string symbol, section;
    uint32_t symbolValue = 0;
    uint8_t symbolType = 0;
    bool isRela = false;
    int32_t explicitAddend = 0;
    bool alloc = false;
};
struct Object {
    std::string label;
    Bytes elfData;  // Original bytes retained for scratch relocation and ELF output.
    uint32_t elfFlags = 0;
    std::vector<Section> sections;
    std::vector<Symbol> symbols;
    std::vector<Reloc> relocs;
    uint64_t code = 0, ro = 0, data = 0, bss = 0;
    std::set<std::string> strongDefs, weakDefs, commonDefs, strongUndefs, weakUndefs;
};
struct Input {
    std::string path;
    bool archive = false;
    std::vector<Object> members;
};

Object parseElf(const Bytes &b, const std::string &label) {
    if (b.size() < 52 || b[0] != 0x7f || b[1] != 'E' || b[2] != 'L' || b[3] != 'F')
        throw Error(label + ": not an ELF object");
    if (b[4] != 1 || b[5] != 1 || b[6] != 1) throw Error(label + ": expected 32-bit little-endian ELF");
    if (u16(b, 16, label) != 1) throw Error(label + ": expected ET_REL object (not executable/shared ELF)");
    if (u16(b, 18, label) != 40) throw Error(label + ": expected ARM ELF (e_machine 40)");
    const uint32_t off = u32(b, 32, label);
    const uint16_t entSize = u16(b, 46, label);
    const uint16_t count = u16(b, 48, label);
    const uint16_t nameIndex = u16(b, 50, label);
    if (!count || entSize < 40 || nameIndex >= count) throw Error(label + ": unsupported/corrupt section header table");
    check(b, off, uint64_t(entSize) * count, label + ": section table");
    Object obj; obj.label = label; obj.elfData = b; obj.elfFlags = u32(b, 36, label);
    obj.sections.resize(count);
    std::vector<uint32_t> nameOffsets(count);
    for (size_t i=0; i<count; ++i) {
        uint64_t p = uint64_t(off) + uint64_t(i) * entSize;
        nameOffsets[i] = u32(b, p, label);
        auto &s = obj.sections[i];
        s.type = u32(b, p+4, label); s.flags = u32(b,p+8,label);
        s.offset = u32(b,p+16,label); s.size = u32(b,p+20,label);
        s.link = u32(b,p+24,label); s.info = u32(b,p+28,label);
        s.align = u32(b,p+32,label); s.entsize = u32(b,p+36,label);
        if (s.type != SHT_NOBITS) check(b, s.offset, s.size, label + ": section contents");
    }
    const auto &ns = obj.sections[nameIndex];
    if (ns.type != 3) throw Error(label + ": invalid section-name table");
    for (size_t i=0; i<count; ++i) {
        obj.sections[i].name = stringAt(b, ns.offset, ns.size, nameOffsets[i], label+": shstrtab");
        const auto &s = obj.sections[i];
        if (!(s.flags & SHF_ALLOC) || s.size == 0) continue;
        if (s.type == SHT_NOBITS) obj.bss += s.size;
        else if (s.flags & SHF_EXECINSTR) obj.code += s.size;
        else if (s.flags & SHF_WRITE) obj.data += s.size;
        else obj.ro += s.size;
    }
    // Read symbol tables independently; relocation sections specify their own
    // symbol table via sh_link. A regular GNU ARM GCC object has one .symtab.
    std::map<uint32_t, std::vector<Symbol>> symbolTables;
    for (uint32_t si=0; si<count; ++si) {
        const auto &s = obj.sections[si];
        if (s.type != SHT_SYMTAB) continue;
        if (s.link >= count || obj.sections[s.link].type != 3 || s.entsize < 16 || s.size % s.entsize)
            throw Error(label + ": invalid .symtab or associated .strtab");
        const auto &str = obj.sections[s.link];
        auto &syms = symbolTables[si];
        syms.reserve(s.size/s.entsize);
        for (uint32_t n=0;n<s.size/s.entsize;++n) {
            const uint64_t p = uint64_t(s.offset)+uint64_t(n)*s.entsize;
            Symbol v;
            v.name = stringAt(b, str.offset, str.size, u32(b,p,label), label+": strtab");
            v.value=u32(b,p+4,label); v.size=u32(b,p+8,label);
            const uint8_t info = u8(b,p+12,label);
            v.binding = info >> 4; v.type=info & 15; v.shndx=u16(b,p+14,label);
            syms.push_back(std::move(v));
        }
        // Store the first symbol table for diagnostics and link-plan symbol
        // extraction. Relocations below still reference their own tables.
        if (obj.symbols.empty()) obj.symbols = syms;
    }
    for (const auto &sym : obj.symbols) {
        if (sym.name.empty() || (sym.binding != STB_GLOBAL && sym.binding != STB_WEAK)) continue;
        if (sym.shndx == SHN_UNDEF) {
            (sym.binding == STB_WEAK ? obj.weakUndefs : obj.strongUndefs).insert(sym.name);
        } else if (sym.shndx == SHN_COMMON) {
            obj.commonDefs.insert(sym.name);
        } else if (sym.binding == STB_WEAK) {
            obj.weakDefs.insert(sym.name);
        } else {
            obj.strongDefs.insert(sym.name);
        }
    }
    // In COMDAT section groups, reachability of one member retains its peers.
    // This is a conservative model; production ELF group selection will need
    // duplicate group-signature and archive-order handling.
    for (uint32_t gi=0;gi<count;++gi) {
        const auto &g = obj.sections[gi];
        if(g.type != SHT_GROUP) continue;
        if(g.size < 4 || (g.size % 4)) throw Error(label+": invalid ELF group");
        for(uint32_t offGroup=4;offGroup<g.size;offGroup+=4) {
            const uint32_t mi = u32(b,uint64_t(g.offset)+offGroup,label);
            if(mi>=count) throw Error(label+": group contains invalid section index");
            obj.sections[mi].group=static_cast<int>(gi);
        }
    }
    for (uint32_t ri=0;ri<count;++ri) {
        const auto &s = obj.sections[ri];
        if (s.type != SHT_REL && s.type != SHT_RELA) continue;
        const uint32_t relSize = s.type == SHT_REL ? 8 : 12;
        if (s.entsize < relSize || s.size % s.entsize || s.info >= count)
            throw Error(label + ": invalid relocation section " + s.name);
        auto symIt = symbolTables.find(s.link);
        if (symIt == symbolTables.end()) throw Error(label + ": relocation with missing symbol table: " + s.name);
        const auto &tgt = obj.sections[s.info];
        for (uint32_t n=0;n<s.size/s.entsize;++n) {
            uint64_t p=uint64_t(s.offset)+uint64_t(n)*s.entsize;
            const uint32_t rinfo=u32(b,p+4,label), symbolIndex=rinfo>>8;
            if (symbolIndex>=symIt->second.size()) throw Error(label + ": relocation symbol index out of bounds");
            const auto &sym=symIt->second[symbolIndex];
            Reloc r;
            r.type=rinfo & 255u; r.symbolIndex=symbolIndex; r.targetIndex=s.info;
            r.symbolSection=sym.shndx; r.symbolBinding=sym.binding;
            r.symbolValue=sym.value; r.symbolType=sym.type;
            r.isRela = s.type == SHT_RELA;
            if(r.isRela) r.explicitAddend=static_cast<int32_t>(u32(b,p+8,label));
            r.offset=u32(b,p,label); r.symbol=sym.name;
            r.section=tgt.name; r.alloc=(tgt.flags & SHF_ALLOC)!=0;
            if (r.offset >= tgt.size && tgt.size != 0) throw Error(label + ": relocation offset outside target section " + tgt.name);
            obj.relocs.push_back(std::move(r));
        }
    }
    return obj;
}

std::vector<Object> parseAr(const Bytes &b, const std::string &filename) {
    static const std::string magic="!<arch>\n";
    if (b.size()<8 || std::string(reinterpret_cast<const char*>(b.data()),8)!=magic)
        throw Error(filename+": invalid archive header");
    uint64_t pos=8;
    Bytes longNames;
    std::vector<Object> entries;
    while (pos < b.size()) {
        check(b,pos,60,filename+": archive member header");
        if (b[static_cast<size_t>(pos+58)]!='`' || b[static_cast<size_t>(pos+59)]!='\n')
            throw Error(filename+": invalid archive member trailer");
        std::string name(reinterpret_cast<const char *>(b.data()+pos),16);
        name=trim(name);
        const auto size=parseDecimal(std::string(reinterpret_cast<const char *>(b.data()+pos+48),10),filename);
        uint64_t data=pos+60;
        check(b,data,size,filename+": archive member contents");
        uint64_t start=data, length=size;
        if (name=="//") {
            longNames.assign(b.begin()+static_cast<ptrdiff_t>(data),b.begin()+static_cast<ptrdiff_t>(data+size));
        } else if (name=="/" || name=="/SYM64/" || name=="__.SYMDEF" || name=="__.SYMDEF SORTED") {
            // GNU/BSD archive index, not an object.
        } else {
            if (name.rfind("#1/",0)==0) {
                const uint64_t n=parseDecimal(name.substr(3),filename);
                if (n>length) throw Error(filename+": invalid BSD archive name size");
                name=std::string(b.begin()+static_cast<ptrdiff_t>(data),b.begin()+static_cast<ptrdiff_t>(data+n));
                start+=n;length-=n;
            } else if (!name.empty() && name[0]=='/' && name.size()>1 && std::isdigit(static_cast<unsigned char>(name[1]))) {
                const uint64_t idx=parseDecimal(name.substr(1),filename);
                if (idx>=longNames.size()) throw Error(filename+": archive long-name offset out of bounds");
                size_t end=static_cast<size_t>(idx);
                while(end<longNames.size() && longNames[end]!='\n' && longNames[end]!=0) ++end;
                name=std::string(longNames.begin()+static_cast<ptrdiff_t>(idx),longNames.begin()+static_cast<ptrdiff_t>(end));
            }
            if (!name.empty() && name.back()=='/') name.pop_back();
            if (length<4 || b[static_cast<size_t>(start)]!=0x7f || b[static_cast<size_t>(start+1)]!='E'
                || b[static_cast<size_t>(start+2)]!='L' || b[static_cast<size_t>(start+3)]!='F')
                throw Error(filename+": archive member is not an ELF object: " + name);
            Bytes member(b.begin()+static_cast<ptrdiff_t>(start),b.begin()+static_cast<ptrdiff_t>(start+length));
            entries.push_back(parseElf(member,filename+"("+name+")"));
        }
        pos=data+size+(size & 1u);
    }
    return entries;
}
Input parseInput(const std::string &filename) {
    Bytes b=load(filename);
    Input input; input.path=filename;
    if (b.size()>=8 && std::string(reinterpret_cast<const char*>(b.data()),8)=="!<arch>\n") {
        input.archive=true;input.members=parseAr(b,filename);
    } else input.members.push_back(parseElf(b,filename));
    return input;
}

const char *relName(uint32_t t) {
    switch(t) {
        case 0:return "R_ARM_NONE";
        case 2:return "R_ARM_ABS32";
        case 3:return "R_ARM_REL32";
        case 10:return "R_ARM_THM_CALL";
        case 23:return "R_ARM_RELATIVE";
        case 25:return "R_ARM_BASE_PREL";
        case 26:return "R_ARM_GOT_BREL";
        case 28:return "R_ARM_CALL";
        case 29:return "R_ARM_JUMP24";
        case 30:return "R_ARM_THM_JUMP24";
        case 42:return "R_ARM_PREL31";
        case 43:return "R_ARM_MOVW_ABS_NC";
        case 44:return "R_ARM_MOVT_ABS";
        case 47:return "R_ARM_THM_MOVW_ABS_NC";
        case 48:return "R_ARM_THM_MOVT_ABS";
        default:return nullptr;
    }
}
bool initialSupported(uint32_t t) {
    return t==0 || t==2 || t==3 || t==10 || t==25 || t==26 || t==30 || t==42;
}
std::string typeName(uint32_t t) {
    if (const char *v=relName(t)) return v;
    return "R_ARM_UNKNOWN_"+std::to_string(t);
}

struct Plan {
    std::vector<const Object *> selected;
    std::map<std::string,const Object*> strongDef, anyDef;
    std::set<std::string> unresolved;
    size_t pulled = 0;
};
void add(Object const *o,Plan &p) {
    p.selected.push_back(o);
    for(const auto &s:o->weakDefs) if(!p.anyDef.count(s)) p.anyDef[s]=o;
    for(const auto &s:o->commonDefs) if(!p.anyDef.count(s)) p.anyDef[s]=o;
    for(const auto &s:o->strongDefs) {
        auto it=p.strongDef.find(s);
        if(it!=p.strongDef.end()) throw Error("Duplicate strong symbol '"+s+"' in "+it->second->label+" and "+o->label);
        p.strongDef[s]=o;p.anyDef[s]=o;
    }
    for(const auto &s:o->strongUndefs) p.unresolved.insert(s);
    for(const auto &s:o->strongDefs) p.unresolved.erase(s);
    for(const auto &s:o->weakDefs) p.unresolved.erase(s);
    for(const auto &s:o->commonDefs) p.unresolved.erase(s);
    for(auto it=p.unresolved.begin();it!=p.unresolved.end();) {
        if(p.anyDef.count(*it)) it=p.unresolved.erase(it);
        else ++it;
    }
}
Plan createPlan(const std::vector<Input> &inputs) {
    Plan p;
    for(const auto &in:inputs) if(!in.archive) for(const auto &m:in.members) add(&m,p);
    // Linker archive extraction is demand-driven. Repeat until neither archive
    // adds a member. This models a --start-group pass but deliberately does NOT
    // perform section garbage collection yet (that is a later linker stage).
    std::set<const Object*> extracted;
    bool progress;
    do {
        progress=false;
        for(const auto &in:inputs) if(in.archive) for(const auto &m:in.members) {
            if (extracted.count(&m)) continue;
            bool wanted=false;
            for (const auto &sym:m.strongDefs) if(p.unresolved.count(sym)) {wanted=true;break;}
            if (!wanted) for(const auto &sym:m.commonDefs) if(p.unresolved.count(sym)) {wanted=true;break;}
            if (!wanted) for(const auto &sym:m.weakDefs) if(p.unresolved.count(sym)) {wanted=true;break;}
            if (wanted) {
                add(&m,p);extracted.insert(&m);++p.pulled;progress=true;
            }
        }
    } while(progress);
    return p;
}

// Stage 2 is a read-only preview. In particular, LLD may fold/merge sections,
// choose different archive members after GC, and generate its own dynamic ELF
// sections. Nothing below is allowed to write into a project directory.
struct Settings {
    std::string entry = "applet_entry";
    uint64_t base = 0xD0010000u;
    uint64_t app = 128u*1024u;
    uint64_t heap = 16u*1024u;
    uint64_t stack = 8u*1024u;
};
struct Node {
    const Object *object = nullptr;
    uint32_t section = 0;
    bool operator<(const Node &b) const {
        return std::tie(object,section) < std::tie(b.object,b.section);
    }
};
struct LayoutItem {
    Node node;
    uint64_t address = 0;
};
struct Analysis {
    std::set<Node> live;
    std::set<std::string> unresolved;
    std::set<std::string> gotSymbols;
    std::map<std::string,std::pair<uint64_t,uint64_t>> commons; // size, alignment
    uint64_t aliveRelocs = 0, basePrelRelocs = 0;
    uint64_t code = 0, ro = 0, data = 0, bss = 0;
    bool foundEntry = false;
    std::map<uint32_t,size_t> liveRelocTypes;
};

uint64_t aligned(uint64_t n,uint64_t align) {
    if(!align || (align & (align-1))) throw Error("Invalid ELF section alignment");
    if(n > std::numeric_limits<uint64_t>::max() - (align-1)) throw Error("Layout address overflow");
    return (n + align - 1) & ~(align-1);
}
bool begins(const std::string &s,const std::string &p) {return s.compare(0,p.size(),p)==0;}
bool builtin(const std::string &s) {
    static const std::set<std::string> linkerSymbols = {
        "_GLOBAL_OFFSET_TABLE_", "__v2_heap_start__", "_appstart", "__app_start",
        "__app_end", "__app_end_clear", "__bss_start__", "__bss_end__",
        "__stack_start__", "__stack_end__", "_end", "_estack",
        "_v2_link_base", "_v2_app_limit", "_v2_heap_bytes", "_v2_stack_bytes"
    };
    return linkerSymbols.count(s)!=0;
}
// Strong > common > weak. The selected-archive approximation comes from Stage 1.
const Symbol *definedSymbol(const Object *o,const std::string &name) {
    const Symbol *weak=nullptr,*common=nullptr;
    for(const auto &s:o->symbols) {
        if(s.name!=name || s.shndx==SHN_UNDEF || s.binding==STB_LOCAL) continue;
        if(s.shndx==SHN_COMMON) common=&s;
        else if(s.binding==STB_WEAK) weak=&s;
        else return &s;
    }
    return common ? common : weak;
}

Analysis analyze(const Plan &plan,const Settings &settings) {
    Analysis a;
    std::deque<Node> waiting;
    auto retain=[&](const Object *o,uint32_t idx) {
        if(idx>=o->sections.size()) throw Error(o->label+": invalid referenced section");
        if(!(o->sections[idx].flags & SHF_ALLOC)) return;
        Node n{o,idx};
        if(a.live.insert(n).second) waiting.push_back(n);
    };
    // KEEP semantics from gui_v2.ld, plus C init/fini tables.
    for(const Object *o:plan.selected) {
        for(uint32_t i=1;i<o->sections.size();++i) {
            const auto &s=o->sections[i];
            if(begins(s.name,".text.applet_entry") || begins(s.name,".init_array") ||
               begins(s.name,".fini_array")) retain(o,i);
        }
        for(const auto &sym:o->symbols) {
            if(sym.name==settings.entry && sym.shndx>0 && sym.shndx<o->sections.size()) {
                a.foundEntry=true;retain(o,sym.shndx);
            }
        }
    }
    if(!a.foundEntry) throw Error("Entry symbol '"+settings.entry+"' not defined in selected object files");
    const auto followGlobal=[&](const std::string &name)->std::pair<const Object*,const Symbol*> {
        const Object *o=nullptr;
        const auto strong=plan.strongDef.find(name);
        if(strong!=plan.strongDef.end()) o=strong->second;
        else {
            const auto any=plan.anyDef.find(name);
            if(any!=plan.anyDef.end()) o=any->second;
        }
        return {o, o?definedSymbol(o,name):nullptr};
    };
    auto followSymbol=[&](const Node &n,const Reloc &r) {
        if(r.symbolSection != SHN_UNDEF && r.symbolSection != SHN_ABS && r.symbolSection != SHN_COMMON) {
            retain(n.object,r.symbolSection);
            return;
        }
        if(r.symbolSection==SHN_ABS) return;
        if(r.symbol.empty() || builtin(r.symbol)) return;
        const auto resolved=followGlobal(r.symbol);
        if(resolved.second) {
            if(resolved.second->shndx==SHN_COMMON) {
                auto &v=a.commons[r.symbol];
                v.first=std::max<uint64_t>(v.first,resolved.second->size);
                v.second=std::max<uint64_t>(v.second,resolved.second->value?resolved.second->value:1);
            } else if(resolved.second->shndx!=SHN_ABS) retain(resolved.first,resolved.second->shndx);
        } else if(r.symbolBinding != STB_WEAK) {
            a.unresolved.insert(r.symbol);
        }
    };
    // This fixed-point walk also accounts for SHF_LINK_ORDER (.ARM.exidx)
    // and conservatively retains companion sections of ELF section groups.
    while(!waiting.empty()) {
        const Node n=waiting.front();waiting.pop_front();
        const Section &section=n.object->sections[n.section];
        if(section.group>=0) {
            for(uint32_t i=1;i<n.object->sections.size();++i)
                if(n.object->sections[i].group==section.group) retain(n.object,i);
        }
        for(const Object *o:plan.selected) {
            for(uint32_t i=1;i<o->sections.size();++i) {
                const auto &s=o->sections[i];
                if(o==n.object && (s.flags & SHF_LINK_ORDER) && s.link==n.section) retain(o,i);
            }
        }
        for(const auto &r:n.object->relocs) {
            if(!r.alloc || r.targetIndex!=n.section) continue;
            ++a.aliveRelocs; ++a.liveRelocTypes[r.type];
            if(r.type==25) ++a.basePrelRelocs;
            if(r.type==26) {
                // Deduplicate by global name; local and anonymous entries
                // need the object + symbol index as part of their identity.
                if(r.symbolBinding!=STB_LOCAL && !r.symbol.empty())
                    a.gotSymbols.insert("global:"+r.symbol);
                else a.gotSymbols.insert("local:"+n.object->label+":"+std::to_string(r.symbolIndex));
            }
            followSymbol(n,r);
        }
    }
    for(const auto &n:a.live) {
        const Section &s=n.object->sections[n.section];
        if(s.type==SHT_NOBITS) a.bss+=s.size;
        else if(s.flags & SHF_EXECINSTR) a.code+=s.size;
        else if(s.flags & SHF_WRITE) a.data+=s.size;
        else a.ro+=s.size;
    }
    return a;
}

std::string hex64(uint64_t value) {
    std::ostringstream ss;ss<<"0x"<<std::hex<<std::uppercase<<value;
    return ss.str();
}
int sectionBucket(const Section &s) {
    if(s.type==SHT_NOBITS) return 7;
    if(begins(s.name,".init_array")) return 5;
    if(begins(s.name,".fini_array")) return 6;
    if(begins(s.name,".got")) return 3;
    if(begins(s.name,".data")) return 4;
    if(begins(s.name,".ARM.exidx") || begins(s.name,".ARM.extab")) return 1;
    if(begins(s.name,".text") || begins(s.name,".rodata") || (s.flags & SHF_EXECINSTR)) return 0;
    if(s.flags & SHF_WRITE) return 4;
    return 2;
}
void layout(const Plan &p,const Settings &settings,const Analysis &a,bool verbose) {
    if(settings.app==0 || settings.app>512u*1024u || settings.app%32u!=0)
        throw Error("CGARM allowance must be 32-byte aligned, 1..512 KiB");
    const std::vector<std::string> bucketNames={
        ".text + .rodata", ".ARM.exidx/extab", "other read-only (orphan estimate)",
        ".got", ".data", ".init_array", ".fini_array", ".bss"
    };
    std::vector<std::vector<Node>> buckets(bucketNames.size());
    for(const Object *o:p.selected) {
        for(uint32_t i=1;i<o->sections.size();++i) {
            Node n{o,i};
            if(a.live.count(n)) buckets[sectionBucket(o->sections[i])].push_back(n);
        }
    }
    uint64_t cursor=settings.base;
    std::vector<uint64_t> bucketSize(buckets.size(),0);
    std::vector<LayoutItem> items;
    uint64_t bssStart=0,bssEnd=0,gotStart=0,stackStart=0,stackEnd=0;
    std::cout<<"\nStage 2/3: reachable-section layout preview (NOT final linked ELF)\n";
    std::cout<<"  Retained sections: "<<a.live.size()<<" across "<<p.selected.size()<<" selected objects\n";
    std::cout<<"  Live relocations: "<<a.aliveRelocs<<" | GOT entries: "<<a.gotSymbols.size()
             <<" ("<<(a.gotSymbols.size()*4)<<" bytes) | BASE_PREL: "<<a.basePrelRelocs<<"\n";
    for(size_t bi=0;bi<buckets.size();++bi) {
        if(bi==3) {
            cursor=aligned(cursor,4);gotStart=cursor;
            const uint64_t gotBytes=a.gotSymbols.size()*4u;
            cursor=sum(cursor,gotBytes);bucketSize[bi]+=gotBytes;
        }
        if(bi==7) {cursor=aligned(cursor,8);bssStart=cursor;}
        const uint64_t start=cursor;
        for(const Node &n:buckets[bi]) {
            const auto &s=n.object->sections[n.section];
            cursor=aligned(cursor,s.align?s.align:1);
            items.push_back({n,cursor});
            cursor=sum(cursor,s.size);
        }
        bucketSize[bi]+=cursor-start;
        if(bi==7) {cursor=aligned(cursor,8);bssEnd=cursor;}
    }
    cursor=aligned(cursor,8);stackStart=cursor;
    stackEnd=aligned(sum(stackStart,settings.stack),8);
    const uint64_t heapEnd=sum(stackEnd,settings.heap);
    const uint64_t limitEnd=sum(settings.base,settings.app);
    if(settings.base>0xffffffffULL || limitEnd>0x100000000ULL)
        throw Error("Virtual ARM ELF address range exceeds 32-bit address space");
    for(const auto &kv:a.liveRelocTypes) {
        std::cout<<"  Live "<<std::left<<std::setw(24)<<typeName(kv.first)
                 <<std::right<<std::setw(6)<<kv.second
                 <<(initialSupported(kv.first)?" [planned]":" [NOT YET SUPPORTED]")<<"\n";
    }
    if(verbose) for(const auto &s:a.gotSymbols)
        std::cout<<"    GOT ENTRY "<<s<<"\n";
    for(size_t bi=0;bi<buckets.size();++bi) {
        if(bucketSize[bi] || !buckets[bi].empty())
            std::cout<<"  "<<std::left<<std::setw(32)<<bucketNames[bi]
                     <<std::right<<std::setw(10)<<bucketSize[bi]<<" bytes (with intra-group alignment)\n";
    }
    std::cout<<"  __bss_start__  = "<<hex64(bssStart)<<"\n"
             <<"  __bss_end__    = "<<hex64(bssEnd)<<"\n"
             <<"  _GLOBAL_OFFSET_TABLE_ approx = "<<hex64(gotStart)<<"\n"
             <<"  __stack_start__= "<<hex64(stackStart)<<"\n"
             <<"  __stack_end__ / __v2_heap_start__ = "<<hex64(stackEnd)<<"\n"
             <<"  Stack reserved = "<<settings.stack<<" bytes; heap reserved = "<<settings.heap<<" bytes\n"
             <<"  Estimated footprint = "<<(heapEnd-settings.base)<<" / "<<settings.app<<" bytes"
             <<(heapEnd<=limitEnd?" [within allowance]":" [EXCEEDS allowance]")<<"\n";
    if(verbose) for(const auto &item:items) {
        const auto &s=item.node.object->sections[item.node.section];
        std::cout<<"    "<<hex64(item.address)<<" +"<<s.size<<" "<<item.node.object->label<<" :: "<<s.name<<"\n";
    }
    if(!a.unresolved.empty()) {
        std::cout<<"  References without a definition in the selected objects: "<<a.unresolved.size()<<"\n";
        for(const auto &sym:a.unresolved) std::cout<<"    UNRESOLVED (live) "<<sym<<"\n";
    }
    std::cout<<"  IMPORTANT: estimated addresses only. LLVM may GC/extract/merge differently and\n"
             <<"  adds dynamic ELF tables, relocation records and program headers.\n"
             <<"  Use --relocate for scratch patching; --emit-elf generates separate experimental ELF.\n";
}

// Stage 10: provenance is emitted ONLY with a successful diagnostic ELF.
// The section locations are taken from the SAME RelocationLayout that wrote
// the ELF, not a speculative second layout pass.
uint64_t provenanceHash(const Bytes &b) {
    uint64_t h=14695981039346656037ULL;
    for(uint8_t c:b) h=(h^c)*1099511628211ULL;
    return h;
}
std::string provenanceHex(uint64_t value) {
    std::ostringstream out;out<<std::hex<<std::uppercase<<value;return out.str();
}
// Stage 3: scratch relocation engine, reused by Stage 4 ELF writer.
// Code/data sections are copied into per-section buffers; SHT_NOBITS is never
// materialised, so large app heaps cannot consume host memory during auditing.
struct RelocationLayout {
    std::map<Node,uint64_t> sectionAddress;
    std::map<Node,Bytes> images;
    std::map<std::string,uint64_t> gotAddress;
    std::map<std::string,uint64_t> commonAddress;
    uint64_t gotBase=0, gotSize=0, bssStart=0, bssEnd=0, stackStart=0, stackEnd=0;
    uint64_t dynstrBase=0, dynsymBase=0, relBase=0, relSize=0, dynamicBase=0, dynamicSize=0;
    uint64_t end=0;
};
std::string gotKey(const Object &o,const Reloc &r) {
    if(r.symbolBinding!=STB_LOCAL && !r.symbol.empty()) return "global:"+r.symbol;
    return "local:"+o.label+":"+std::to_string(r.symbolIndex);
}
uint32_t addr32(uint64_t n,const std::string &label) {
    if(n>0xffffffffULL) throw Error(label+": address exceeds ARM 32-bit limit");
    return static_cast<uint32_t>(n);
}
RelocationLayout makeRelocLayout(const Plan &p,const Analysis &a,const Settings &settings,
                                uint64_t relCount=0, bool emit=false) {
    RelocationLayout l;
    if(!settings.app || settings.app>512u*1024u || settings.app%32)
        throw Error("Allowance must be 32-byte aligned, 1..512 KiB");
    uint64_t endLimit=sum(settings.base,settings.app);
    if(endLimit>0x100000000ULL) throw Error("ARM applet address limit overflows 32 bits");
    std::vector<std::vector<Node>> buckets(8);
    for(const Object *o:p.selected) for(uint32_t si=1;si<o->sections.size();++si) {
        Node n{o,si}; if(a.live.count(n)) buckets[sectionBucket(o->sections[si])].push_back(n);
    }
    uint64_t cursor=settings.base;
    for(size_t bi=0;bi<buckets.size();++bi) {
        if(bi==3) {
            cursor=aligned(cursor,4);l.gotBase=cursor;
            for(const auto &key:a.gotSymbols) {
                l.gotAddress[key]=cursor;
                cursor=sum(cursor,4);
            }
            l.gotSize=cursor-l.gotBase;
        }
        if(bi==7 && emit) {
            // Keep generated dynamic metadata inside the initialized PT_LOAD
            // image, immediately before BSS. All addresses are recomputed
            // before applying any relocation.
            cursor=aligned(cursor,4); l.dynstrBase=cursor; cursor=sum(cursor,1);
            cursor=aligned(cursor,4); l.dynsymBase=cursor; cursor=sum(cursor,16);
            cursor=aligned(cursor,4); l.relBase=cursor; l.relSize=relCount*8;
            cursor=sum(cursor,l.relSize);
            cursor=aligned(cursor,4); l.dynamicBase=cursor; l.dynamicSize=8*8;
            cursor=sum(cursor,l.dynamicSize);
        }
        if(bi==7) {cursor=aligned(cursor,8);l.bssStart=cursor;}
        for(const Node &n:buckets[bi]) {
            const auto &s=n.object->sections[n.section];
            cursor=aligned(cursor,s.align?s.align:1);
            l.sectionAddress[n]=cursor;
            if(s.type != SHT_NOBITS) {
                check(n.object->elfData,s.offset,s.size,n.object->label+":"+s.name);
                Bytes data(n.object->elfData.begin()+static_cast<ptrdiff_t>(s.offset),
                           n.object->elfData.begin()+static_cast<ptrdiff_t>(s.offset+s.size));
                l.images.emplace(n,std::move(data));
            }
            cursor=sum(cursor,s.size);
        }
        if(bi==7) {
            // COMMON symbols are tentative storage allocations not assigned
            // to a regular ELF section; reserve them after .bss output sections.
            for(const auto &kv:a.commons) {
                cursor=aligned(cursor,kv.second.second);
                l.commonAddress[kv.first]=cursor;
                cursor=sum(cursor,kv.second.first);
            }
            cursor=aligned(cursor,8);l.bssEnd=cursor;
        }
    }
    l.stackStart=aligned(cursor,8);
    l.stackEnd=aligned(sum(l.stackStart,settings.stack),8);
    l.end=sum(l.stackEnd,settings.heap);
    if(l.end>endLimit) throw Error("Relocation preview exceeds CGARM RAM allowance by "+std::to_string(l.end-endLimit)+" bytes");
    return l;
}

uint64_t specialSymbol(const std::string &name,const Settings &cfg,const RelocationLayout &l) {
    if(name=="_GLOBAL_OFFSET_TABLE_") return l.gotBase;
    if(name=="_appstart" || name=="__app_start" || name=="_v2_link_base") return cfg.base;
    if(name=="__app_end" || name=="__app_end_clear" || name=="__stack_end__" || name=="_end" || name=="_estack" || name=="__v2_heap_start__") return l.stackEnd;
    if(name=="__stack_start__") return l.stackStart;
    if(name=="__bss_start__") return l.bssStart;
    if(name=="__bss_end__") return l.bssEnd;
    if(name=="_v2_app_limit") return cfg.app;
    if(name=="_v2_heap_bytes") return cfg.heap;
    if(name=="_v2_stack_bytes") return cfg.stack;
    throw Error("Unknown built-in linker symbol '"+name+"'");
}

// Returns (link-time value, true if it is an address requiring dynamic rebasing).
std::pair<uint64_t,bool> resolveSymbol(const Node &from,const Reloc &r,
                                         const Plan &p,const RelocationLayout &l,const Settings &cfg) {
    const auto &o=*from.object;
    if(r.symbolSection==SHN_ABS) return {r.symbolValue,false};
    if(r.symbolSection!=SHN_UNDEF && r.symbolSection!=SHN_COMMON) {
        const Node owner{&o,r.symbolSection};
        auto si=l.sectionAddress.find(owner);
        if(si==l.sectionAddress.end()) throw Error(o.label+": reference to discarded section "+std::to_string(r.symbolSection));
        return {sum(si->second,r.symbolValue),true};
    }
    if(!r.symbol.empty() && builtin(r.symbol)) {
        const bool absoluteSize=begins(r.symbol,"_v2_") && r.symbol!="_v2_link_base";
        return {specialSymbol(r.symbol,cfg,l),!absoluteSize};
    }
    if(r.symbolSection==SHN_COMMON) {
        auto c=l.commonAddress.find(r.symbol);
        if(c==l.commonAddress.end()) throw Error(o.label+": COMMON symbol not allocated: "+r.symbol);
        return {c->second,true};
    }
    if(r.symbol.empty()) return {0,false};
    const Object *target=nullptr;
    auto strong=p.strongDef.find(r.symbol);
    if(strong!=p.strongDef.end()) target=strong->second;
    else {
        auto any=p.anyDef.find(r.symbol);
        if(any!=p.anyDef.end()) target=any->second;
    }
    if(!target) {
        if(r.symbolBinding==STB_WEAK) return {0,false};
        throw Error(o.label+": undefined symbol '"+r.symbol+"'");
    }
    const Symbol *sym=definedSymbol(target,r.symbol);
    if(!sym) throw Error(o.label+": selected provider does not define '"+r.symbol+"'");
    if(sym->shndx==SHN_ABS) return {sym->value,false};
    if(sym->shndx==SHN_COMMON) {
        auto c=l.commonAddress.find(r.symbol);
        if(c==l.commonAddress.end()) throw Error("COMMON symbol missing from memory layout: "+r.symbol);
        return {c->second,true};
    }
    const Node n{target,sym->shndx};
    auto it=l.sectionAddress.find(n);
    if(it==l.sectionAddress.end()) throw Error(o.label+": definition of '"+r.symbol+"' is discarded");
    return {sum(it->second,sym->value),true};
}

void put16(Bytes &b,size_t off,uint16_t v,const std::string &who) {
    check(b,off,2,who);
    b[off]=static_cast<uint8_t>(v);b[off+1]=static_cast<uint8_t>(v>>8);
}
void put32(Bytes &b,size_t off,uint32_t v,const std::string &who) {
    check(b,off,4,who);
    for(unsigned i=0;i<4;++i) b[off+i]=static_cast<uint8_t>(v>>(i*8));
}
int64_t signedWord(uint32_t v) {return static_cast<int32_t>(v);}
int64_t signExtend25(uint32_t v) {return (v & 0x1000000u) ? int64_t(v)-0x2000000LL : int64_t(v);}

// B.W (T4) and BL (T1) encode S:J1:J2:imm10:imm11; the effective
// I1/I2 bits are !(J1 XOR S), !(J2 XOR S). These are halfwords in
// little-endian memory, NOT a conventional 32-bit bitfield.
int64_t decodeThumbBranch(uint16_t hi,uint16_t lo,const std::string &loc,uint32_t type) {
    if((hi&0xf800u)!=0xf000u)
        throw Error(loc+": expected first halfword of a 32-bit Thumb branch");
    if(type==10 && (lo&0xd000u)!=0xd000u)
        throw Error(loc+": R_ARM_THM_CALL requires Thumb BL (BLX unsupported for M-profile)");
    if(type==30 && (lo&0xd000u)!=0x9000u)
        throw Error(loc+": R_ARM_THM_JUMP24 requires Thumb B.W (T4), not BL");
    const uint32_t s=(hi>>10)&1u,j1=(lo>>13)&1u,j2=(lo>>11)&1u;
    const uint32_t i1=!(j1^s), i2=!(j2^s);
    uint32_t bits=(s<<24)|(i1<<23)|(i2<<22)|((hi&0x3ffu)<<12)|((lo&0x7ffu)<<1);
    return signExtend25(bits);
}
std::pair<uint16_t,uint16_t> encodeThumbBranch(uint16_t hi,uint16_t lo,int64_t displacement,
                                               const std::string &loc) {
    if((displacement & 1)!=0 || displacement<-(1LL<<24) || displacement>((1LL<<24)-2))
        throw Error(loc+": Thumb branch displacement outside signed +/-16 MiB reach: "+std::to_string(displacement));
    const uint32_t d=static_cast<uint32_t>(displacement)&0x1ffffffu;
    const uint32_t s=(d>>24)&1u,i1=(d>>23)&1u,i2=(d>>22)&1u;
    const uint32_t j1=!(i1^s),j2=!(i2^s);
    hi=static_cast<uint16_t>((hi&0xf800u)|(s<<10)|((d>>12)&0x3ffu));
    lo=static_cast<uint16_t>((lo&0xd000u)|(j1<<13)|(j2<<11)|((d>>1)&0x7ffu));
    return {hi,lo};
}
// Stage 4: minimal ELF32/ARM ET_DYN emitter, formatted for SIDBOX's existing
// strict V2 packer. This output must be considered EXPERIMENTAL.
struct OutSection {
    std::string name;
    uint32_t type=1, flags=0, address=0, fileOff=0, size=0;
    uint32_t link=0, info=0, align=1, entsize=0, nameOff=0;
};
void emitProvenance10(const Plan &p,const Analysis &a,const RelocationLayout &l,
                      const std::string &elfPath,const std::string &mapPath) {
    namespace fs=std::filesystem;
    if(mapPath.empty())return;
    if(fs::exists(mapPath))throw Error("Refusing to overwrite provenance file: "+mapPath);
    const Bytes elf=load(elfPath);
    std::ostringstream rows;
    rows<<"CGARM_PROVENANCE_V1\n";
    rows<<"ELF\t"<<provenanceHex(provenanceHash(elf))<<"\n";
    size_t retained=0,discarded=0;
    for(const Object *o:p.selected){
        rows<<"OBJECT\t"<<std::quoted(o->label)<<"\t"
            <<provenanceHex(provenanceHash(o->elfData))<<"\n";
        for(uint32_t i=1;i<o->sections.size();++i){
            const auto &sec=o->sections[i];
            if(!(sec.flags&SHF_ALLOC) || !sec.size)continue;
            const Node node{o,i};const bool live=a.live.count(node)!=0;
            if(live)++retained;else ++discarded;
            rows<<"SECTION\t"<<std::quoted(o->label)<<"\t"<<i<<"\t"
                <<std::quoted(sec.name)<<"\t"<<(live?"LIVE":"DISCARDED")<<"\t"
                <<(live?provenanceHex(l.sectionAddress.at(node)):"-")<<"\t"
                <<sec.size<<"\t"<<sec.flags<<"\n";
        }
    }
    const fs::path tmp=mapPath+".cgarm-ld-tmp";
    if(fs::exists(tmp))throw Error("Provenance temporary output exists: "+tmp.string());
    try {
        std::ofstream out(tmp,std::ios::binary|std::ios::trunc);
        if(!out)throw Error("Cannot create provenance file: "+tmp.string());
        out<<rows.str();out.close();
        if(!out)throw Error("Provenance write failed: "+tmp.string());
        if(fs::exists(mapPath))throw Error("Provenance output appeared during write: "+mapPath);
        fs::rename(tmp,mapPath);
    }catch(...){std::error_code ec;fs::remove(tmp,ec);throw;}
    std::cout<<"\nStage 10: section provenance emitted\n"
             <<"  Map:                "<<mapPath<<"\n"
             <<"  Retained sections:  "<<retained<<"\n"
             <<"  Discarded sections: "<<discarded<<" (among selected inputs)\n";
}

void emitElf(const Plan &p,const Settings &cfg,
             const RelocationLayout &l,const std::map<std::string,uint32_t> &gotContents,
             const std::set<uint64_t> &relativeSites,const std::string &path) {
    namespace fs=std::filesystem;
    if(relativeSites.empty()) throw Error("Cannot emit PIE: no R_ARM_RELATIVE runtime relocations for SIDBOX packer");
    if(cfg.stack<4096 || cfg.stack%32 || cfg.heap%32)
        throw Error("V2 packer requires a >=4096-byte 32-byte-aligned stack and a 32-byte-aligned heap");
    if(l.relSize!=relativeSites.size()*8 || l.dynamicSize!=64)
        throw Error("Dynamic relocation layout mismatch");
    if(l.stackEnd>cfg.base+cfg.app || l.bssStart<cfg.base || l.dynstrBase<cfg.base)
        throw Error("Invalid ELF memory layout");
    const uint32_t base=addr32(cfg.base,"ELF load base");
    const uint32_t fileSpan=addr32(l.dynamicBase+l.dynamicSize-cfg.base,"ELF image span");
    const uint32_t memorySpan=addr32(l.stackEnd-cfg.base,"ELF memory span");
    if(fileSpan>256u*1024u) throw Error("Initialized ELF image exceeds SIDBOX packer's 256 KiB limit");
    if(memorySpan>512u*1024u) throw Error("ELF memory span exceeds V2 512 KiB limit");
    const uint32_t imageOff=0x1000u;
    Bytes elf(imageOff+fileSpan,0);
    auto region=[&](uint64_t address,uint64_t length,const std::string &label)->size_t {
        if(address<cfg.base || address-cfg.base>fileSpan || length>fileSpan-(address-cfg.base))
            throw Error(label+": lies outside initialized image");
        return imageOff+static_cast<size_t>(address-cfg.base);
    };
    auto imagePut=[&](uint64_t address,const Bytes &contents,const std::string &label) {
        const size_t off=region(address,contents.size(),label);
        std::copy(contents.begin(),contents.end(),elf.begin()+static_cast<ptrdiff_t>(off));
    };
    std::vector<OutSection> secs;
    OutSection nullSection; nullSection.type=0; nullSection.align=0;
    secs.push_back(nullSection); // ELF section header #0 (SHT_NULL)
    std::map<Node,uint32_t> outSectionIndices;
    for(const auto &kv:l.sectionAddress) {
        const Node n=kv.first;
        const auto &s=n.object->sections[n.section];
        OutSection sh;
        sh.name=s.name; sh.type=s.type; sh.flags=s.flags;
        sh.address=addr32(kv.second,"section "+s.name);
        sh.size=s.size; sh.align=s.align?s.align:1;sh.entsize=s.entsize;
        if(s.type==SHT_NOBITS) sh.fileOff=imageOff+fileSpan;
        else {
            sh.fileOff=static_cast<uint32_t>(region(kv.second,s.size,s.name));
            auto contents=l.images.find(n);
            if(contents==l.images.end()) throw Error("Retained initialized section missing patched bytes: "+s.name);
            imagePut(kv.second,contents->second,s.name);
        }
        secs.push_back(sh);
        outSectionIndices[n]=static_cast<uint32_t>(secs.size()-1);
    }
    for(const auto &kv:outSectionIndices) {
        const Section &original=kv.first.object->sections[kv.first.section];
        if(original.flags & SHF_LINK_ORDER) {
            const Node linked{kv.first.object,original.link};
            const auto found=outSectionIndices.find(linked);
            if(found==outSectionIndices.end())
                throw Error(original.name+": SHF_LINK_ORDER target was discarded");
            secs[kv.second].link=found->second;
        }
        // We do not output COMDAT SHT_GROUP tables. Strip membership flag;
        // the group members have already been resolved by reachability.
        secs[kv.second].flags &= ~uint32_t(0x200);
    }
    auto addGenerated=[&](const std::string &name,uint32_t type,uint32_t flags,
                          uint64_t addr,uint32_t size,uint32_t align,uint32_t entsize=0)->uint32_t {
        OutSection sh;
        sh.name=name;sh.type=type;sh.flags=flags;sh.address=addr32(addr,"generated section "+name);
        sh.fileOff=(type==SHT_NOBITS) ? imageOff+fileSpan
                   : static_cast<uint32_t>(region(addr,size,name));
        sh.size=size;sh.align=align;sh.entsize=entsize;
        secs.push_back(sh);return static_cast<uint32_t>(secs.size()-1);
    };
    if(l.gotSize) {
        addGenerated(".got",1,SHF_ALLOC|SHF_WRITE,l.gotBase,addr32(l.gotSize,"GOT size"),4,4);
        for(const auto &kv:l.gotAddress) {
            auto v=gotContents.find(kv.first);
            if(v==gotContents.end()) throw Error("Missing GOT contents for "+kv.first);
            put32(elf,region(kv.second,4,"GOT cell"),v->second,"GOT cell");
        }
    }
    addGenerated(".dynstr",3,SHF_ALLOC,l.dynstrBase,1,1);
    const uint32_t dynsymIndex=addGenerated(".dynsym",11,SHF_ALLOC,l.dynsymBase,16,4,16);
    const uint32_t relIndex=addGenerated(".rel.dyn",9,SHF_ALLOC,l.relBase,addr32(l.relSize,"rel.dyn size"),4,8);
    const uint32_t dynIndex=addGenerated(".dynamic",6,SHF_ALLOC|SHF_WRITE,l.dynamicBase,64,4,8);
    const uint32_t bssIndex=addGenerated(".bss",SHT_NOBITS,SHF_ALLOC|SHF_WRITE,l.bssStart,
                                       addr32(l.bssEnd-l.bssStart,"bss size"),8);
    (void)bssIndex;
    addGenerated(".stack",SHT_NOBITS,SHF_ALLOC|SHF_WRITE,l.stackStart,
                 addr32(l.stackEnd-l.stackStart,"stack size"),8);
    // Section headers are diagnostic/packer metadata. The single PT_LOAD
    // includes all initialized sections, including generated dynamic tables.
    secs[dynsymIndex].link=dynsymIndex-1; // preceding .dynstr
    secs[relIndex].link=dynsymIndex;
    secs[dynIndex].link=dynsymIndex-1;
    size_t relPos=region(l.relBase,l.relSize,".rel.dyn");
    for(uint64_t site:relativeSites) {
        if(site%4) throw Error("Unaligned R_ARM_RELATIVE relocation site: "+hex64(site));
        if(site<cfg.base || site+4>cfg.base+fileSpan) throw Error("R_ARM_RELATIVE site not in initialized image");
        const uint32_t raw=u32(elf,region(site,4,"runtime relocation site"),"runtime target");
        if(uint64_t(raw &~uint32_t(1))<cfg.base || uint64_t(raw&~uint32_t(1))>=l.stackEnd+cfg.heap)
            throw Error("R_ARM_RELATIVE points outside applet memory: site "+hex64(site)+" target "+hex64(raw));
        put32(elf,relPos,addr32(site,"runtime relocation site"),".rel.dyn");
        put32(elf,relPos+4,23,".rel.dyn R_ARM_RELATIVE");
        relPos+=8;
    }
    const std::vector<std::pair<uint32_t,uint32_t>> tags={
        {5,addr32(l.dynstrBase,"DT_STRTAB")}, {6,addr32(l.dynsymBase,"DT_SYMTAB")},
        {10,1}, {11,16}, {17,addr32(l.relBase,"DT_REL")},
        {18,addr32(l.relSize,"DT_RELSZ")}, {19,8}, {0,0}
    };
    size_t dp=region(l.dynamicBase,64,".dynamic");
    for(const auto &tag:tags) {put32(elf,dp,tag.first,".dynamic");put32(elf,dp+4,tag.second,".dynamic");dp+=8;}
    // The packer validates .stack ends at the PT_LOAD memory limit.
    // Keep in-memory reservations (BSS, stack) out of initialized file bytes.
    if(!(l.stackStart>=cfg.base+fileSpan && l.stackEnd>l.stackStart))
        throw Error(".stack reservation overlaps initialized image or is empty");
    if(l.bssEnd>l.stackStart) throw Error("BSS overlaps stack");
    // ELF section names and headers can follow file image outside PT_LOAD.
    Bytes shstr{0};
    for(size_t i=1;i<secs.size();++i) {
        secs[i].nameOff=static_cast<uint32_t>(shstr.size());
        for(char c:secs[i].name) shstr.push_back(static_cast<uint8_t>(c));
        shstr.push_back(0);
    }
    const uint32_t shstrName=static_cast<uint32_t>(shstr.size());
    for(char c:std::string(".shstrtab")) shstr.push_back(static_cast<uint8_t>(c));
    shstr.push_back(0);
    const uint32_t shstrOff=static_cast<uint32_t>(elf.size());
    elf.insert(elf.end(),shstr.begin(),shstr.end());
    secs.push_back({".shstrtab",3,0,0,shstrOff,static_cast<uint32_t>(shstr.size()),0,0,1,0,shstrName});
    const uint32_t shOff=addr32(aligned(elf.size(),4),"section table offset");
    elf.resize(shOff,0);
    if(secs.size()>65535) throw Error("Too many sections for ELF32");
    const uint16_t shNum=static_cast<uint16_t>(secs.size());
    const uint16_t shstrIndex=shNum-1;
    elf.resize(elf.size()+secs.size()*40,0);
    for(size_t i=0;i<secs.size();++i) {
        const auto &sh=secs[i];const size_t q=shOff+i*40;
        put32(elf,q,sh.nameOff,"sh_name");put32(elf,q+4,sh.type,"sh_type");
        put32(elf,q+8,sh.flags,"sh_flags");put32(elf,q+12,sh.address,"sh_addr");
        put32(elf,q+16,sh.fileOff,"sh_offset");put32(elf,q+20,sh.size,"sh_size");
        put32(elf,q+24,sh.link,"sh_link");put32(elf,q+28,sh.info,"sh_info");
        put32(elf,q+32,sh.align,"sh_addralign");put32(elf,q+36,sh.entsize,"sh_entsize");
    }
    // Resolve applet entry using its exact definition (including Thumb bit).
    uint64_t entry=0;bool found=false;
    for(const auto *o:p.selected) for(const auto &sym:o->symbols) {
        if(sym.name!=cfg.entry || sym.shndx==SHN_UNDEF || sym.shndx==SHN_COMMON) continue;
        if(sym.shndx==SHN_ABS) throw Error("Applet entry cannot be SHN_ABS");
        auto it=l.sectionAddress.find({o,sym.shndx});
        if(it==l.sectionAddress.end()) continue;
        if(found) throw Error("Multiple live definitions of entry "+cfg.entry);
        entry=it->second+sym.value; found=true;
    }
    if(!found) throw Error("Cannot locate applet_entry in linked image");
    if((entry&~uint64_t(1))<cfg.base || (entry&~uint64_t(1))>=cfg.base+fileSpan)
        throw Error("Applet entry is outside initialized image");
    // ELF32 EABI5, little-endian ARM ET_DYN. e_flags copied from first
    // selected input to preserve hard-float flags (BE8 unsupported).
    uint32_t flags=p.selected.front()->elfFlags;
    for(const Object *o:p.selected) {
        if((o->elfFlags & 0x600)!= (flags & 0x600))
            throw Error("Mixed ARM ABI float calling convention in linked objects");
    }
    if(flags&0x00800000u) throw Error("BE8 ARM objects are unsupported");
    elf[0]=0x7f;elf[1]='E';elf[2]='L';elf[3]='F';elf[4]=1;elf[5]=1;elf[6]=1;
    elf[7]=0; // ELFOSABI_NONE
    put16(elf,16,3,"e_type ET_DYN");put16(elf,18,40,"e_machine ARM");
    put32(elf,20,1,"e_version");put32(elf,24,addr32(entry,"entry"),"e_entry");
    put32(elf,28,52,"e_phoff");put32(elf,32,shOff,"e_shoff");
    put32(elf,36,flags,"e_flags");put16(elf,40,52,"e_ehsize");
    put16(elf,42,32,"e_phentsize");put16(elf,44,2,"e_phnum");
    put16(elf,46,40,"e_shentsize");put16(elf,48,shNum,"e_shnum");
    put16(elf,50,shstrIndex,"e_shstrndx");
    // PT_LOAD must preserve congruence: p_offset % p_align == p_vaddr % p_align.
    // V2 virtual base 0xD0010000 is page-aligned.
    if(base%4096u) throw Error("ELF base must be 4 KiB aligned for PT_LOAD");
    const size_t ph=52;
    put32(elf,ph,1,"PT_LOAD");put32(elf,ph+4,imageOff,"PT_LOAD offset");
    put32(elf,ph+8,base,"PT_LOAD vaddr");put32(elf,ph+12,base,"PT_LOAD paddr");
    put32(elf,ph+16,fileSpan,"PT_LOAD filesz");put32(elf,ph+20,memorySpan,"PT_LOAD memsz");
    put32(elf,ph+24,7,"PT_LOAD flags RWX");put32(elf,ph+28,4096,"PT_LOAD align");
    const size_t dynph=84;
    put32(elf,dynph,2,"PT_DYNAMIC");put32(elf,dynph+4,addr32(region(l.dynamicBase,64,"PT_DYNAMIC"),"PT_DYNAMIC offset"),"dynamic p_offset");
    put32(elf,dynph+8,addr32(l.dynamicBase,"PT_DYNAMIC vaddr"),"dynamic p_vaddr");
    put32(elf,dynph+12,addr32(l.dynamicBase,"PT_DYNAMIC paddr"),"dynamic p_paddr");
    put32(elf,dynph+16,64,"PT_DYNAMIC filesz");put32(elf,dynph+20,64,"PT_DYNAMIC memsz");
    put32(elf,dynph+24,6,"PT_DYNAMIC flags RW");put32(elf,dynph+28,4,"PT_DYNAMIC align");
    // Refuse to overwrite files. Only publish after complete in-memory validation.
    if(fs::exists(path)) throw Error("Output already exists: "+path);
    const fs::path out(path);
    const fs::path tmp=path+".cgarm-ld-tmp";
    if(fs::exists(tmp)) throw Error("Temporary ELF output already exists: "+tmp.string());
    try {
        std::ofstream stream(tmp,std::ios::binary|std::ios::trunc);
        if(!stream) throw Error("Cannot open ELF destination: "+tmp.string());
        stream.write(reinterpret_cast<const char*>(elf.data()),static_cast<std::streamsize>(elf.size()));
        if(!stream) throw Error("ELF write failed");
        stream.close();if(!stream) throw Error("ELF close failed");
        if(fs::exists(out)) throw Error("Output appeared while writing: "+out.string());
        fs::rename(tmp,out);
    } catch(...) {std::error_code ec;fs::remove(tmp,ec);throw;}
    std::cout<<"\nStage 4: experimental ELF32 ARM ET_DYN created\n"
             <<"  ELF output:              "<<path<<"\n"
             <<"  ELF file bytes:          "<<elf.size()<<"\n"
             <<"  Entry:                   "<<hex64(entry)<<"\n"
             <<"  PT_LOAD initialized:     "<<fileSpan<<" bytes\n"
             <<"  PT_LOAD memory:          "<<memorySpan<<" bytes\n"
             <<"  Dynamic R_ARM_RELATIVE:  "<<relativeSites.size()<<"\n"
             <<"  Stack reserved:          "<<cfg.stack<<" bytes\n"
             <<"  EXPERIMENTAL: inspect with readelf + V2 packer, do NOT deploy to hardware yet.\n";
}

uint64_t fnvMix(uint64_t v,uint8_t b) {return (v^b)*1099511628211ULL;}
void relocate(const Plan &p,const Analysis &a,const Settings &cfg,bool verbose,
              const std::string &elfOutput="",const std::string &mapOutput="") {
    // Count dynamic sites before placing metadata. A symbol's *value* may
    // shift after metadata placement, but whether it is rebased does not.
    RelocationLayout preview=makeRelocLayout(p,a,cfg);
    std::set<uint64_t> prelimSites;
    for(const auto &n:a.live) for(const auto &r:n.object->relocs) {
        if(!r.alloc || r.targetIndex!=n.section) continue;
        if(r.type==2 && resolveSymbol(n,r,p,preview,cfg).second)
            prelimSites.insert(preview.sectionAddress.at(n)+r.offset);
        else if(r.type==26 && resolveSymbol(n,r,p,preview,cfg).second)
            prelimSites.insert(preview.gotAddress.at(gotKey(*n.object,r)));
    }
    const bool emitting=!elfOutput.empty();
    RelocationLayout l=emitting ? makeRelocLayout(p,a,cfg,prelimSites.size(),true) : std::move(preview);
    std::map<uint32_t,size_t> applied;
    std::set<uint64_t> futureRuntimeRelocs;
    size_t fixes=0;
    std::map<std::string,uint32_t> gotContents;
    // Initialise the GOT with resolved virtual addresses. Every such pointer
    // needs R_ARM_RELATIVE in the future ET_DYN unless it is an absolute value.
    for(const auto &n:a.live) for(const auto &r:n.object->relocs) {
        if(!r.alloc || r.targetIndex!=n.section || r.type!=26) continue;
        const auto identity=gotKey(*n.object,r);
        const auto resolved=resolveSymbol(n,r,p,l,cfg);
        const uint32_t value=addr32(resolved.first,"GOT target "+identity);
        if(!gotContents.count(identity)) {
            gotContents[identity]=value;
            if(resolved.second) futureRuntimeRelocs.insert(l.gotAddress.at(identity));
        } else if(gotContents.at(identity)!=value) throw Error("Inconsistent GOT entries for "+identity);
    }
    uint64_t digest=14695981039346656037ULL;
    for(const auto &kv:l.gotAddress) {
        const auto it=gotContents.find(kv.first);
        if(it==gotContents.end()) throw Error("GOT entry was not initialised: "+kv.first);
        for(unsigned i=0;i<4;++i) digest=fnvMix(digest,static_cast<uint8_t>(it->second>>(i*8)));
    }
    for(const auto &n:a.live) {
        const auto &section=n.object->sections[n.section];
        for(const auto &r:n.object->relocs) {
            if(!r.alloc || r.targetIndex!=n.section || r.type==0) continue;
            const std::string where=n.object->label+":"+section.name+"+"+hex64(r.offset)+" "+typeName(r.type);
            if(r.isRela) throw Error(where+": explicit-addend RELA is not supported in Stage 3 (REL only)");
            auto dest=l.images.find(n);
            if(dest==l.images.end()) throw Error(where+": cannot apply relocation into SHT_NOBITS section");
            Bytes &buffer=dest->second;
            check(buffer,r.offset,4,where);
            const uint64_t P=sum(l.sectionAddress.at(n),r.offset);
            const auto resolved=resolveSymbol(n,r,p,l,cfg);
            // In Thumb branches strip the Thumb code-state bit from the function
            // symbol; all CGARM Cortex-M targets execute only Thumb code.
            const uint64_t S=resolved.first;
            if(r.type==2 || r.type==3 || r.type==25 || r.type==26 || r.type==42) {
                const uint32_t word=u32(buffer,r.offset,where);
                const int64_t A=(r.type==42)
                    ? ((word&0x40000000u) ? int64_t(word&0x7fffffffu)-0x80000000LL : int64_t(word&0x7fffffffu))
                    : signedWord(word);
                int64_t result=0;
                if(r.type==2) {
                    result=static_cast<int64_t>(S)+A;
                    if(resolved.second) futureRuntimeRelocs.insert(P);
                } else if(r.type==3) result=static_cast<int64_t>(S)+A-static_cast<int64_t>(P);
                else if(r.type==25 || r.type==42) result=static_cast<int64_t>(S)+A-static_cast<int64_t>(P);
                else result=static_cast<int64_t>(l.gotAddress.at(gotKey(*n.object,r)))+A-static_cast<int64_t>(l.gotBase);
                if(r.type==42 && (result<-(1LL<<30) || result>((1LL<<30)-1)))
                    throw Error(where+": R_ARM_PREL31 result outside signed 31-bit range");
                if(r.type!=42 && (result<INT32_MIN || result>INT32_MAX)) {
                    // ABS32 can legitimately contain an unsigned address (0xD...).
                    if(r.type!=2 || result<0 || result>UINT32_MAX)
                        throw Error(where+": 32-bit relocation result overflow: "+std::to_string(result));
                }
                const uint32_t finalWord=(r.type==42)
                    ? ((word&0x80000000u)|(static_cast<uint32_t>(result)&0x7fffffffu))
                    : static_cast<uint32_t>(result);
                put32(buffer,r.offset,finalWord,where);
            } else if(r.type==10 || r.type==30) {
                const uint16_t hi=u16(buffer,r.offset,where),lo=u16(buffer,r.offset+2,where);
                const int64_t A=decodeThumbBranch(hi,lo,where,r.type);
                const int64_t delta=static_cast<int64_t>(S&~1ULL)+A-static_cast<int64_t>(P);
                const auto patched=encodeThumbBranch(hi,lo,delta,where);
                put16(buffer,r.offset,patched.first,where);
                put16(buffer,r.offset+2,patched.second,where);
            } else throw Error(where+": relocation handler not implemented (cannot silently skip)");
            ++fixes;++applied[r.type];
            if(verbose && fixes<=24) {
                std::cout<<"    PATCH "<<hex64(P)<<" "<<std::left<<std::setw(20)<<typeName(r.type)
                         <<std::right<<" symbol="<<(r.symbol.empty()?"<unnamed>":r.symbol)
                         <<" S="<<hex64(S)<<" word="<<hex64(u32(buffer,r.offset,where))<<"\n";
            }
        }
    }
    // Digest actual patched bytes, not the original ELF bytes. For reproducibility
    // traverse sections in deterministic input order, then include each address.
    for(const auto &kv:l.images) {
        uint64_t addr=l.sectionAddress.at(kv.first);
        for(unsigned i=0;i<8;++i) digest=fnvMix(digest,static_cast<uint8_t>(addr>>(i*8)));
        for(uint8_t byte:kv.second) digest=fnvMix(digest,byte);
    }
    std::cout<<"\nStage 4: ARM relocation engine (scratch section images)\n"
             <<"  Scratch sections:        "<<l.images.size()<<" (no input files changed)\n"
             <<"  GOT entries initialised: "<<gotContents.size()<<" / "<<l.gotAddress.size()<<"\n"
             <<"  Applied relocations:     "<<fixes<<"\n";
    for(const auto &kv:applied)
        std::cout<<"    "<<std::left<<std::setw(24)<<typeName(kv.first)<<std::right<<kv.second<<" patched\n";
    std::cout<<"  Candidate R_ARM_RELATIVE locations: "<<futureRuntimeRelocs.size()
             <<(emitting?" (to be emitted)":" (not emitted without --emit-elf)")<<"\n"
             <<"  Patched-image FNV64: "<<hex64(digest)<<"\n"
             <<"  Estimated virtual SDRAM used: "<<(l.end-cfg.base)<<" / "<<cfg.app<<" bytes\n"
             <<"  LLVM remains required for all real builds.\n";
    if(emitting) {
        if(futureRuntimeRelocs.size()!=prelimSites.size())
            throw Error("Internal error: dynamic relocation reservation count changed");
        emitElf(p,cfg,l,gotContents,futureRuntimeRelocs,elfOutput);
        emitProvenance10(p,a,l,elfOutput,mapOutput);
    }
}

uint64_t parseUint(const std::string &s,const std::string &flag) {
    if(s.empty() || s[0]=='-') throw Error(flag+": expected nonnegative integer");
    size_t used=0;
    unsigned long long n=0;
    try {n=std::stoull(s,&used,0);} catch(...) {throw Error(flag+": invalid integer "+s);}
    if(used!=s.size()) throw Error(flag+": invalid integer "+s);
    return static_cast<uint64_t>(n);
}
uint64_t asKiB(const std::string &s,const std::string &flag) {
    const auto k=parseUint(s,flag);
    if(k>std::numeric_limits<uint64_t>::max()/1024u) throw Error(flag+": size overflow");
    return k*1024u;
}

void usage() {
    std::cout <<
      "cgarm-ld — SIDBOX custom ARM linker, Stage 4 (EXPERIMENTAL ELF writer)\n\n"
      "Usage: cgarm-ld [--verbose] [--plan] [--layout] [--relocate] [--emit-elf OUTPUT.elf] [--emit-map OUTPUT.cgmap] [--strict] [settings] FILE.o ... LIB.a ...\n\n"
      "  --layout     Plan kept sections, symbol references, GOT and SDRAM addresses\n"
      "  --relocate   Apply ARM relocations to temporary in-memory section copies\n"
      "  --emit-elf X  Write experimental ARM ET_DYN ELF at new path X (never .app)\n"
      "  --emit-map X  With --emit-elf, write linked section provenance to X.cgmap\n"
      "  --entry X   Entry symbol (default applet_entry)\n"
      "  --app-kb N  Applet allowance in KiB (default 128, max 512)\n"
      "  --heap-kb N Reserved heap in KiB (default 16)\n"
      "  --stack-kb N Private callback stack in KiB (default 8)\n"
      "  --base N    Virtual ELF base, decimal or 0xHEX (default 0xD0010000)\n"
      "  --verbose    Show all object/archive member information\n"
      "  --plan       Simulate archive extraction and report unresolved symbols\n"
      "  --strict     Exit nonzero if any ALLOC relocation type is outside planning set\n"
      "  --help       Show help\n\n"
      "IMPORTANT: --emit-elf creates only an experimental ELF, NEVER an .app.\n"
      "Current production builds must still use LLVM ld.lld.\n";
}

} // namespace

int main(int argc,char **argv) {
    try {
        bool verbose=false,plan=false,strict=false,showLayout=false,runRelocations=false;
        std::string emitOutput, emitMap;
        Settings settings;
        std::vector<std::string> files;
        for(int i=1;i<argc;++i) {
            const std::string s=argv[i];
            if(s=="--help" || s=="-h") {usage();return 0;}
            if(s=="--layout") {showLayout=true;plan=true;}
            else if(s=="--relocate") {runRelocations=true;plan=true;}
            else if(s=="--emit-elf") {
                if(i+1>=argc) throw Error("Missing filename for --emit-elf");
                emitOutput=argv[++i];runRelocations=true;plan=true;strict=true;
            }
            else if(s=="--emit-map") {
                if(i+1>=argc)throw Error("Missing filename for --emit-map");
                emitMap=argv[++i];
            }
            else if(s=="--entry" || s=="--app-kb" || s=="--heap-kb" || s=="--stack-kb" || s=="--base") {
                if(i+1>=argc) throw Error("Missing value for "+s);
                std::string value=argv[++i];
                if(s=="--entry") settings.entry=value;
                else if(s=="--app-kb") settings.app=asKiB(value,s);
                else if(s=="--heap-kb") settings.heap=asKiB(value,s);
                else if(s=="--stack-kb") settings.stack=asKiB(value,s);
                else settings.base=parseUint(value,s);
            }
            else if(s=="--verbose") verbose=true;
            else if(s=="--plan") plan=true;
            else if(s=="--strict") strict=true;
            else if(!s.empty() && s[0]=='-') throw Error("Unknown option: "+s);
            else files.push_back(s);
        }
        if(files.empty()) {usage();return 2;}
        if(!emitMap.empty() && emitOutput.empty())throw Error("--emit-map requires --emit-elf");
        if(!emitMap.empty()) {
            namespace fs=std::filesystem;
            if(fs::path(emitMap).extension()!=".cgmap")throw Error("--emit-map output must end in .cgmap");
            if(fs::exists(emitMap))throw Error("Refusing to overwrite provenance file: "+emitMap);
            if(fs::absolute(emitMap)==fs::absolute(emitOutput))throw Error("Map output equals ELF output");
            for(const auto &in:files) if(fs::absolute(in)==fs::absolute(emitMap))
                throw Error("Map output equals an input file");
        }

        if(!emitOutput.empty()) {
            namespace fs=std::filesystem;
            if(fs::path(emitOutput).extension() != ".elf") throw Error("--emit-elf destination must have .elf extension");
            if(fs::exists(emitOutput)) throw Error("Refusing to overwrite existing ELF: "+emitOutput);
            for(const auto &in:files) if(fs::absolute(in)==fs::absolute(emitOutput))
                throw Error("Refusing to overwrite input file");
        }
        std::vector<Input> inputs;
        std::map<uint32_t,size_t> relocationTotals,allocRelocationTotals;
        uint64_t code=0,ro=0,data=0,bss=0;
        size_t objects=0,archives=0,relocs=0,allocRelocs=0;
        for(const auto &file:files) {
            inputs.push_back(parseInput(file));
            const auto &in=inputs.back();
            if(in.archive) ++archives;
            else ++objects;
            if(in.archive) std::cout<<"[archive] "<<in.path<<" ("<<in.members.size()<<" members)\n";
            else std::cout<<"[object]  "<<in.path<<"\n";
            for(const auto &o:in.members) {
                code+=o.code;ro+=o.ro;data+=o.data;bss+=o.bss;
                for(const auto &r:o.relocs) {
                    ++relocs;++relocationTotals[r.type];
                    if(r.alloc) {++allocRelocs;++allocRelocationTotals[r.type];}
                }
                if(verbose) {
                    std::cout<<"    "<<o.label<<" | ELF EABI "<<((o.elfFlags>>24)&255)
                             <<" | code "<<o.code<<" ro "<<o.ro<<" data "<<o.data<<" bss "<<o.bss
                             <<" | reloc "<<o.relocs.size()<<" | global "<<o.strongDefs.size()
                             <<" | unresolved references "<<o.strongUndefs.size()<<"\n";
                }
            }
        }
        std::cout<<"\nELF32 ARM audit (all inputs, including archive members)\n"
                 <<"  Input objects:  "<<objects<<"\n  Archives:       "<<archives
                 <<"\n  Archive members:";
        size_t members=0;for(const auto &in:inputs) if(in.archive) members+=in.members.size();
        std::cout<<" "<<members<<"\n"
                 <<"  Section bytes:  code="<<code<<" ro="<<ro<<" data="<<data<<" bss="<<bss<<" (before linking/GC)\n"
                 <<"  Relocations:    "<<relocs<<" total, "<<allocRelocs<<" in SHF_ALLOC sections\n";
        bool unsupported=false;
        for(const auto &kv:allocRelocationTotals) {
            const bool known=initialSupported(kv.first);
            if(!known) unsupported=true;
            std::cout<<"    "<<std::left<<std::setw(26)<<typeName(kv.first)<<std::right<<std::setw(6)<<kv.second
                     <<(known?"  [planned support]":"  [needs investigation]")<<"\n";
        }
        if(plan) {
            Plan p=createPlan(inputs);
            size_t plannedRelocs=0;
            std::map<uint32_t,size_t> plannedTypes;
            for (const auto *o:p.selected) for(const auto &r:o->relocs) if(r.alloc) {
                ++plannedRelocs;++plannedTypes[r.type];
            }
            std::cout<<"\nArchive extraction plan (NO garbage collection yet):\n"
                     <<"  Selected objects: "<<p.selected.size()<<" ("<<p.pulled<<" archive members pulled)\n"
                     <<"  ALLOC relocations: "<<plannedRelocs<<"\n"
                     <<"  Strong unresolved symbols: "<<p.unresolved.size()<<"\n";
            if(verbose) for(const auto *o:p.selected) std::cout<<"    USE "<<o->label<<"\n";
            for(const auto &u:p.unresolved) std::cout<<"    UNRESOLVED "<<u<<"\n";
            if(!p.unresolved.empty()) std::cout<<"  Note: initial archive plan counts references from all sections.\n";
            if(!emitOutput.empty() && unsupported)
                throw Error("Cannot emit ELF: input contains unsupported ALLOC relocations");
            if(showLayout || runRelocations) {
                Analysis a=analyze(p,settings);
                if(showLayout) layout(p,settings,a,verbose);
                if(runRelocations) relocate(p,a,settings,verbose,emitOutput,emitMap);
            }
        }
        if(strict && unsupported) {
            std::cerr<<"cgarm-ld: unsupported ALLOC relocation types found; see audit above\n";
            return 3;
        }
        std::cout<<"\nStage 4 completed; "
                 <<(emitOutput.empty()?"NO files created or modified.":"Experimental ELF generated; NO .app created.")<<"\n";
        return 0;
    } catch (const std::exception &e) {
        std::cerr << "cgarm-ld: ERROR: " << e.what() << '\n';
        return 1;
    }
}
