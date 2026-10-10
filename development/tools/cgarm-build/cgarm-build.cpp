// CGARM command-line builder (Stage 4: C/RES or IDE JSON .proj -> SBAP V2 APP)
//
// Linux host tool. No Qt, shell scripts, or GNU/Newlib libc at APP link time.
// Compile with: g++ -std=c++17 -O2 -Wall -Wextra cgarm-build.cpp -o cgarm-build
// Place the resulting binary in SidboxIDE/idelibs/tools/bin/.
//
// Uses the same ARM GCC, API source set, PIC settings, LLVM ld.lld link order,
// linker template, static CGARM library and native packer as SidboxIDE V2.
// This program does NOT alter the Qt IDE or any firmware files.

#include <algorithm>
#include <cerrno>
#include <cctype>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <set>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

namespace fs = std::filesystem;

namespace {

struct Error : std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct Options {
    std::vector<fs::path> sources;
    fs::path output;
    fs::path sdkOverride;
    fs::path project;
    bool explicitOutput = false;
    bool explicitAppKb = false;
    bool explicitHeapKb = false;
    bool explicitStackKb = false;
    bool explicitOptimisation = false;
    bool projectMode = false;
    bool suppressWarnings = false;
    bool wall = true;
    bool wextra = true;
    bool functionSections = true;
    bool dataSections = true;
    bool stackUsage = false;
    std::vector<std::string> projectCompilerFlags;
    std::vector<std::string> extraCppFlags;
    unsigned appKb = 128;
    unsigned heapKb = 16;
    unsigned stackKb = 8;
    std::string optimisation = "-O2";
    bool verbose = false;
    bool dryRun = false;
    bool showHelp = false;
};

void usage(std::ostream &out) {
    out <<
        "CGARM command-line builder (SIDBOX relocatable V2)\n\n"
        "Usage: cgarm-build <source.c> [more.c ...] -o <output.app> [options]\n"
        "       cgarm-build <project.proj> [options]\n\n"
        "Options:\n"
        "  -o, --output FILE    Override output .app filename/location\n"
        "  --sdk DIR            SidboxIDE project root OR its idelibs directory\n"
        "  --app-kb N           Applet RAM allowance in KiB (32-512, default 128)\n"
        "  --heap-kb N          Bounded heap in KiB (>=4, default 16)\n"
        "  --stack-kb N         Private callback PSP stack in KiB (4-128, default 8)\n"
        "  -O0/-Og/-O1/-O2/-O3/-Os/-Ofast  GCC optimisation override\n"
        "  -I DIR, -IDIR       Extra C include directory (may repeat)\n"
        "  -D NAME, -DNAME    Extra C preprocessor definition (may repeat)\n"
        "  --verbose           Print every compiler/linker/packer command\n"
        "  --dry-run           Print planned commands without creating files\n"
        "  -h, --help          Show this help\n\n"
        "Reads IDE JSON .proj settings and source tree (already-generated GUI resources).\n"
        "Only CGARM V2 GUI projects. V1 and Gaming remain IDE-only.\n"
        "No .sbui regeneration and no interactive auto-RAM resizing in this CLI.\n";
}

unsigned number(const std::string &s, const std::string &opt) {
    if (s.empty() || !std::all_of(s.begin(), s.end(), [](unsigned char c) {
            return std::isdigit(c) != 0;
        })) {
        throw Error(opt + " requires a positive integer (KiB)");
    }
    try {
        unsigned long long value = std::stoull(s);
        if (value > std::numeric_limits<unsigned>::max()) {
            throw Error(opt + " is too large");
        }
        return static_cast<unsigned>(value);
    } catch (const std::out_of_range &) {
        throw Error(opt + " is too large");
    }
}

Options parse(int argc, char **argv) {
    Options opts;
    bool literal = false;
    for (int i = 1; i < argc; ++i) {
        const std::string arg(argv[i]);
        auto next = [&]() -> std::string {
            if (i + 1 >= argc) throw Error("Missing argument after " + arg);
            return argv[++i];
        };
        if (!literal && arg == "--") {
            literal = true;
        } else if (!literal && (arg == "-h" || arg == "--help")) {
            opts.showHelp = true;
            return opts;
        } else if (!literal && (arg == "-o" || arg == "--output")) {
            opts.output = next();
            opts.explicitOutput = true;
        } else if (!literal && arg == "--sdk") {
            opts.sdkOverride = next();
        } else if (!literal && arg == "--app-kb") {
            opts.appKb = number(next(), arg);
            opts.explicitAppKb = true;
        } else if (!literal && arg == "--heap-kb") {
            opts.heapKb = number(next(), arg);
            opts.explicitHeapKb = true;
        } else if (!literal && arg == "--stack-kb") {
            opts.stackKb = number(next(), arg);
            opts.explicitStackKb = true;
        } else if (!literal && arg == "--verbose") {
            opts.verbose = true;
        } else if (!literal && arg == "--dry-run") {
            opts.dryRun = true;
            opts.verbose = true;
        } else if (!literal && (arg == "-I" || arg == "-D")) {
            const std::string value = next();
            if (value.empty()) throw Error(arg + " needs a value");
            opts.extraCppFlags.push_back(arg + value);
        } else if (!literal && arg.size() > 2 &&
                   (arg.substr(0, 2) == "-I" || arg.substr(0, 2) == "-D")) {
            opts.extraCppFlags.push_back(arg);
        } else if (!literal && (arg == "-O0" || arg == "-O1" || arg == "-O2" ||
                                 arg == "-O3" || arg == "-Os" || arg == "-Og" || arg == "-Ofast")) {
            opts.optimisation = arg;
            opts.explicitOptimisation = true;
        } else if (!literal && !arg.empty() && arg.front() == '-') {
            throw Error("Unknown option: " + arg + " (see --help)");
        } else {
            opts.sources.emplace_back(arg);
        }
    }
    if (opts.sources.empty()) throw Error("No source or .proj file specified (see --help)");
    const bool hasProject = std::any_of(opts.sources.begin(), opts.sources.end(),
        [](const fs::path &s) { return s.extension() == ".proj"; });
    if (hasProject) {
        if (opts.sources.size() != 1 || opts.sources[0].extension() != ".proj") {
            throw Error("Pass one .proj file by itself; it supplies its own sources");
        }
        opts.projectMode = true;
        opts.project = opts.sources.front();
    } else if (!opts.explicitOutput) {
        opts.output = opts.sources.front().stem().string() + ".app";
    }
    return opts;
}

void validateMemory(const Options &opts) {
    if (opts.appKb < 32 || opts.appKb > 512)
        throw Error("--app-kb / appSizeKb must be 32–512 KiB for V2");
    if (opts.heapKb < 4 || opts.heapKb > 512)
        throw Error("--heap-kb / v2HeapKb must be 4–512 KiB");
    if (opts.stackKb < 4 || opts.stackKb > 128)
        throw Error("--stack-kb / v2StackKb must be 4–128 KiB");
    if (opts.heapKb + opts.stackKb >= opts.appKb)
        throw Error("Heap + private stack must leave room for applet code and data");
}

fs::path absolutePath(const fs::path &path) {
    return fs::absolute(path).lexically_normal();
}

// Minimal self-contained JSON reader. .proj files are JSON written by Qt's
// QJsonDocument; keeping the CLI dependency-free avoids shipping Qt with it.
// Handles normal JSON escaping, nested unknown fields and UTF-16 \u escapes.
struct Json {
    enum class Kind { Null, Bool, Number, String, Array, Object } kind = Kind::Null;
    bool boolean = false;
    std::string text;
    std::vector<Json> array;
    std::map<std::string, Json> object;
    const Json *get(const std::string &key) const {
        const auto it = object.find(key);
        return kind == Kind::Object && it != object.end() ? &it->second : nullptr;
    }
};

class JsonReader {
    const std::string &s;
    std::size_t pos = 0;
    void white() {
        while (pos < s.size() && std::isspace(static_cast<unsigned char>(s[pos]))) ++pos;
    }
    char peek() {
        white();
        if (pos >= s.size()) throw Error("Unexpected end of .proj JSON");
        return s[pos];
    }
    void expect(char c) {
        if (peek() != c) throw Error(std::string("Invalid .proj JSON: expected '") + c + "'");
        ++pos;
    }
    static void utf8(std::string &out, unsigned u) {
        if (u <= 0x7f) out += static_cast<char>(u);
        else if (u <= 0x7ff) {
            out += static_cast<char>(0xc0 | (u >> 6));
            out += static_cast<char>(0x80 | (u & 63));
        } else if (u <= 0xffff) {
            out += static_cast<char>(0xe0 | (u >> 12));
            out += static_cast<char>(0x80 | ((u >> 6) & 63));
            out += static_cast<char>(0x80 | (u & 63));
        } else {
            out += static_cast<char>(0xf0 | (u >> 18));
            out += static_cast<char>(0x80 | ((u >> 12) & 63));
            out += static_cast<char>(0x80 | ((u >> 6) & 63));
            out += static_cast<char>(0x80 | (u & 63));
        }
    }
    unsigned unicode() {
        if (pos + 4 > s.size()) throw Error("Truncated JSON Unicode escape");
        unsigned u = 0;
        for (int i = 0; i < 4; ++i) {
            const unsigned char c = s[pos++];
            u <<= 4;
            if (c >= '0' && c <= '9') u += c - '0';
            else if (c >= 'a' && c <= 'f') u += c - 'a' + 10;
            else if (c >= 'A' && c <= 'F') u += c - 'A' + 10;
            else throw Error("Bad JSON Unicode escape");
        }
        return u;
    }
    std::string string() {
        expect('"');
        std::string out;
        while (pos < s.size()) {
            unsigned char c = static_cast<unsigned char>(s[pos++]);
            if (c == '"') return out;
            if (c < 0x20) throw Error("Control character in JSON string");
            if (c != '\\') { out += static_cast<char>(c); continue; }
            if (pos >= s.size()) throw Error("Truncated JSON string escape");
            const char esc = s[pos++];
            switch (esc) {
                case '"': out += '"'; break;
                case '\\': out += '\\'; break;
                case '/': out += '/'; break;
                case 'b': out += '\b'; break;
                case 'f': out += '\f'; break;
                case 'n': out += '\n'; break;
                case 'r': out += '\r'; break;
                case 't': out += '\t'; break;
                case 'u': {
                    unsigned u = unicode();
                    if (u >= 0xd800 && u <= 0xdbff) {
                        if (pos + 2 > s.size() || s[pos] != '\\' || s[pos + 1] != 'u')
                            throw Error("Unpaired high surrogate in JSON");
                        pos += 2;
                        unsigned low = unicode();
                        if (low < 0xdc00 || low > 0xdfff) throw Error("Invalid low surrogate in JSON");
                        u = 0x10000 + ((u - 0xd800) << 10) + (low - 0xdc00);
                    } else if (u >= 0xdc00 && u <= 0xdfff) {
                        throw Error("Unpaired low surrogate in JSON");
                    }
                    utf8(out, u);
                    break;
                }
                default: throw Error("Invalid JSON string escape");
            }
        }
        throw Error("Unterminated JSON string");
    }
    Json value(unsigned depth) {
        if (depth > 64) throw Error(".proj JSON nesting is too deep");
        const char c = peek();
        Json v;
        if (c == '{') {
            v.kind = Json::Kind::Object;
            ++pos;
            if (peek() == '}') { ++pos; return v; }
            while (true) {
                if (peek() != '"') throw Error("Object key must be a string");
                std::string key = string();
                expect(':');
                v.object[std::move(key)] = value(depth + 1);
                const char next = peek();
                if (next == '}') { ++pos; break; }
                expect(',');
            }
        } else if (c == '[') {
            v.kind = Json::Kind::Array;
            ++pos;
            if (peek() == ']') { ++pos; return v; }
            while (true) {
                v.array.push_back(value(depth + 1));
                if (peek() == ']') { ++pos; break; }
                expect(',');
            }
        } else if (c == '"') {
            v.kind = Json::Kind::String;
            v.text = string();
        } else if (c == '-' || std::isdigit(static_cast<unsigned char>(c))) {
            const std::size_t first = pos;
            if (s[pos] == '-') ++pos;
            if (pos >= s.size()) throw Error("Bad JSON number");
            if (s[pos] == '0') ++pos;
            else {
                if (s[pos] < '1' || s[pos] > '9') throw Error("Bad JSON number");
                while (pos < s.size() && std::isdigit(static_cast<unsigned char>(s[pos]))) ++pos;
            }
            if (pos < s.size() && s[pos] == '.') {
                ++pos;
                if (pos == s.size() || !std::isdigit(static_cast<unsigned char>(s[pos])))
                    throw Error("Bad JSON fraction");
                while (pos < s.size() && std::isdigit(static_cast<unsigned char>(s[pos]))) ++pos;
            }
            if (pos < s.size() && (s[pos] == 'e' || s[pos] == 'E')) {
                ++pos;
                if (pos < s.size() && (s[pos] == '+' || s[pos] == '-')) ++pos;
                if (pos == s.size() || !std::isdigit(static_cast<unsigned char>(s[pos])))
                    throw Error("Bad JSON exponent");
                while (pos < s.size() && std::isdigit(static_cast<unsigned char>(s[pos]))) ++pos;
            }
            v.kind = Json::Kind::Number;
            v.text = s.substr(first, pos - first);
        } else {
            const std::string literal = s.compare(pos, 4, "true") == 0 ? "true"
                : s.compare(pos, 5, "false") == 0 ? "false" : "null";
            if (s.compare(pos, literal.size(), literal) != 0) throw Error("Unknown JSON token");
            pos += literal.size();
            v.kind = literal == "null" ? Json::Kind::Null : Json::Kind::Bool;
            v.boolean = literal == "true";
        }
        return v;
    }
public:
    explicit JsonReader(const std::string &input) : s(input) {}
    Json parse() {
        Json root = value(0);
        white();
        if (pos != s.size()) throw Error("Trailing data after .proj JSON");
        if (root.kind != Json::Kind::Object) throw Error(".proj JSON root must be an object");
        return root;
    }
};

std::string jsonString(const Json &o, const std::string &key, const std::string &def = "") {
    const Json *v = o.get(key);
    if (!v || v->kind == Json::Kind::Null) return def;
    if (v->kind != Json::Kind::String) throw Error(".proj field '" + key + "' must be a string");
    return v->text;
}

bool jsonBool(const Json &o, const std::string &key, bool def) {
    const Json *v = o.get(key);
    if (!v || v->kind == Json::Kind::Null) return def;
    if (v->kind != Json::Kind::Bool) throw Error(".proj field '" + key + "' must be true/false");
    return v->boolean;
}

unsigned jsonUnsigned(const Json &o, const std::string &key, unsigned def) {
    const Json *v = o.get(key);
    if (!v || v->kind == Json::Kind::Null) return def;
    if (v->kind != Json::Kind::Number || v->text.empty() ||
        !std::all_of(v->text.begin(), v->text.end(), [](unsigned char c) { return std::isdigit(c); })) {
        throw Error(".proj field '" + key + "' must be a non-negative integer");
    }
    return number(v->text, key);
}

// QProcess::splitCommand-like tokenisation for the IDE's extraFlags string.
// Quoting keeps spaces together. No shell is ever run or expanded.
std::vector<std::string> splitFlags(const std::string &flags) {
    std::vector<std::string> words;
    std::string current;
    bool quoted = false;
    bool started = false;
    for (std::size_t i = 0; i < flags.size(); ++i) {
        const char c = flags[i];
        if (c == '"') { quoted = !quoted; started = true; }
        else if (c == '\\' && i + 1 < flags.size() && flags[i + 1] == '"') {
            current += '"'; ++i; started = true;
        } else if (std::isspace(static_cast<unsigned char>(c)) && !quoted) {
            if (started) { words.push_back(current); current.clear(); started = false; }
        } else { current += c; started = true; }
    }
    if (quoted) throw Error("Unclosed double quote in compiler.extraFlags");
    if (started) words.push_back(current);
    return words;
}

bool sourceExtension(fs::path path) {
    std::string ext = path.extension().string();
    std::transform(ext.begin(), ext.end(), ext.begin(), [](unsigned char c) { return std::tolower(c); });
    return ext == ".c" || ext == ".cc" || ext == ".cpp" || ext == ".res";
}

void loadProject(Options &opts) {
    const fs::path project = absolutePath(opts.project);
    std::ifstream in(project, std::ios::binary);
    if (!in) throw Error("Cannot open .proj file: " + project.string());
    const std::string contents((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    if (contents.size() > 4 * 1024 * 1024) throw Error(".proj JSON exceeds 4 MiB");
    const Json root = JsonReader(contents).parse();
    const std::string kind = jsonString(root, "projectType", "gui");
    const std::string format = jsonString(root, "appletFormat", "v1");
    if (kind == "game") throw Error("Gaming project: cgarm-build supports CGARM V2 only (use Qt IDE)");
    if (format != "v2") throw Error("V1 project: cgarm-build supports CGARM V2 only (use Qt IDE)");
    if (!jsonString(root, "linkerScript").empty()) {
        throw Error("CGARM V2 requires the default gui_v2.ld linker template; clear custom linkerScript in IDE");
    }
    const fs::path projectDir = project.parent_path();
    if (!opts.explicitAppKb) opts.appKb = jsonUnsigned(root, "appSizeKb", 128);
    if (!opts.explicitHeapKb) opts.heapKb = jsonUnsigned(root, "v2HeapKb", 16);
    if (!opts.explicitStackKb) opts.stackKb = jsonUnsigned(root, "v2StackKb", 8);
    const Json *compiler = root.get("compiler");
    if (compiler && compiler->kind != Json::Kind::Object)
        throw Error(".proj compiler must be a JSON object");
    if (compiler) {
        if (!opts.explicitOptimisation) opts.optimisation = jsonString(*compiler, "optimization", "-Ofast");
        const std::set<std::string> allowed = {"-O0", "-Og", "-O1", "-O2", "-O3", "-Os", "-Ofast"};
        if (!allowed.count(opts.optimisation)) throw Error("Unsupported compiler.optimization in .proj");
        opts.suppressWarnings = jsonBool(*compiler, "suppressWarnings", true);
        opts.wall = jsonBool(*compiler, "wall", false);
        opts.wextra = jsonBool(*compiler, "wextra", false);
        opts.functionSections = jsonBool(*compiler, "functionSections", true);
        opts.dataSections = jsonBool(*compiler, "dataSections", true);
        opts.stackUsage = jsonBool(*compiler, "stackUsage", true);
        opts.projectCompilerFlags = splitFlags(jsonString(*compiler, "extraFlags"));
        // Interpret relative -I include paths from the project's location,
        // rather than from whichever terminal directory invoked cgarm-build.
        for (std::size_t i = 0; i < opts.projectCompilerFlags.size(); ++i) {
            std::string &flag = opts.projectCompilerFlags[i];
            if (flag == "-I" && i + 1 < opts.projectCompilerFlags.size()) {
                std::string &value = opts.projectCompilerFlags[++i];
                if (!value.empty() && !fs::path(value).is_absolute())
                    value = (projectDir / value).lexically_normal().string();
            } else if (flag.size() > 2 && flag.substr(0, 2) == "-I") {
                const fs::path value(flag.substr(2));
                if (!value.is_absolute()) flag = "-I" + (projectDir / value).lexically_normal().string();
            }
        }
    } else {
        if (!opts.explicitOptimisation) opts.optimisation = "-Ofast";
        opts.suppressWarnings = true;
        opts.wall = false;
        opts.wextra = false;
        opts.stackUsage = true;
    }
    if (!opts.explicitOutput) {
        std::string appName = jsonString(root, "outputAppName");
        if (appName.empty()) appName = project.stem().string() + ".app";
        // The Qt IDE limits custom output to a filename, not a path.
        appName = fs::path(appName).filename().string();
        if (appName.empty() || appName == "." || appName == "..")
            throw Error("Invalid outputAppName in .proj");
        std::string lower = appName;
        std::transform(lower.begin(), lower.end(), lower.begin(), [](unsigned char c) { return std::tolower(c); });
        if (lower.size() < 4 || lower.substr(lower.size()-4) != ".app") appName += ".app";
        opts.output = projectDir / appName;
    }
    std::set<fs::path> discovered;
    const auto append = [&](const fs::path &candidate, bool explicitEntry) {
        if (!sourceExtension(candidate)) return;
        fs::path absolute = absolutePath(candidate);
        if (explicitEntry && !fs::is_regular_file(absolute))
            throw Error("Listed project source missing: " + absolute.string());
        if (discovered.insert(absolute).second) opts.sources.push_back(absolute);
    };
    opts.sources.clear();
    const Json *files = root.get("files");
    if (files) {
        if (files->kind != Json::Kind::Array) throw Error(".proj files must be an array");
        for (const Json &file : files->array) {
            if (file.kind != Json::Kind::String) throw Error(".proj files entry must be a path string");
            if (file.text.empty()) continue;
            const fs::path path(file.text);
            append(path.is_absolute() ? path : projectDir / path, true);
        }
    }
    // Mirror projectFolderSourceFiles(): recurse below project root, except
    // build/, and include generated .c/.res even if absent from JSON files[].
    for (fs::recursive_directory_iterator it(projectDir, fs::directory_options::skip_permission_denied),
          end; it != end; ++it) {
        const fs::path rel = it->path().lexically_relative(projectDir);
        if (!rel.empty() && *rel.begin() == "build") {
            if (it->is_directory()) it.disable_recursion_pending();
            continue;
        }
        if (it->is_regular_file()) {
            const std::string ext = it->path().extension().string();
            // Qt's folder scanner sees only .c and .res automatically; explicitly
            // listed .cc/.cpp above are supported, as in the IDE.
            if (ext == ".c" || ext == ".res") append(it->path(), false);
        }
    }
    std::sort(opts.sources.begin(), opts.sources.end());
    if (opts.sources.empty()) throw Error("No C/.res sources found in .proj or project directory");
    std::cout << "Project: " << project << " (CGARM V2, " << opts.sources.size() << " sources)\n";
    std::cout << "[note] GUI Designer .sbui files are NOT regenerated here; save/generate them in the IDE first.\n";
}

bool sdkLooksValid(const fs::path &sdk) {
    return fs::is_directory(sdk / "api") && fs::is_regular_file(sdk / "gui_v2.ld");
}

fs::path fromCandidate(fs::path start) {
    if (start.empty()) return {};
    start = absolutePath(start);
    while (true) {
        if (sdkLooksValid(start)) return start;
        if (sdkLooksValid(start / "idelibs")) return start / "idelibs";
        const fs::path parent = start.parent_path();
        if (parent == start || parent.empty()) break;
        start = parent;
    }
    return {};
}

fs::path findSdk(const Options &opt) {
    if (!opt.sdkOverride.empty()) {
        fs::path path = absolutePath(opt.sdkOverride);
        if (sdkLooksValid(path)) return path;
        if (sdkLooksValid(path / "idelibs")) return path / "idelibs";
        throw Error("--sdk must point to SidboxIDE or idelibs (gui_v2.ld/api missing): " + path.string());
    }
    std::vector<fs::path> candidates;
    std::error_code ec;
    fs::path executable = fs::read_symlink("/proc/self/exe", ec);
    if (!ec) candidates.push_back(executable.parent_path());
    candidates.push_back(fs::current_path());
    for (const fs::path &src : opt.sources) candidates.push_back(absolutePath(src).parent_path());
    for (const fs::path &candidate : candidates) {
        fs::path sdk = fromCandidate(candidate);
        if (!sdk.empty()) return sdk;
    }
    throw Error("Cannot locate idelibs. Install cgarm-build in idelibs/tools/bin, "
                "or pass --sdk /path/to/SidboxIDE");
}

void requireFile(const fs::path &path, const std::string &description) {
    if (!fs::is_regular_file(path)) {
        throw Error(description + " missing: " + path.string());
    }
}

void requireExecutable(const fs::path &path, const std::string &description) {
    requireFile(path, description);
    if (::access(path.c_str(), X_OK) != 0) {
        throw Error(description + " is not executable: " + path.string());
    }
}

fs::path findLld(const fs::path &sdk) {
    for (const auto &p : {sdk / "tools/bin/ld.lld", sdk / "tools/ld.lld"}) {
        if (fs::is_regular_file(p) && ::access(p.c_str(), X_OK) == 0) return p;
    }
    const char *envPath = std::getenv("PATH");
    std::stringstream paths(envPath ? envPath : "");
    std::string item;
    while (std::getline(paths, item, ':')) {
        const fs::path p = fs::path(item.empty() ? "." : item) / "ld.lld";
        if (fs::is_regular_file(p) && ::access(p.c_str(), X_OK) == 0) return absolutePath(p);
    }
    throw Error("LLVM ld.lld not found (install lld or bundle in idelibs/tools/bin)");
}

std::string hexBytes(unsigned kib) {
    std::ostringstream os;
    os << "0x" << std::uppercase << std::hex << (static_cast<std::uint64_t>(kib) * 1024);
    return os.str();
}

std::string generatedLinkerScript(const fs::path &source, const Options &opt) {
    std::ifstream input(source);
    if (!input) throw Error("Cannot open linker template: " + source.string());
    std::ostringstream result;
    result << "/* Generated by cgarm-build; edit the options, not this file. */\n";
    const std::string keys[] = {"_v2_app_limit", "_v2_stack_bytes", "_v2_heap_bytes"};
    const unsigned values[] = {opt.appKb, opt.stackKb, opt.heapKb};
    unsigned replacements[3] = {0, 0, 0};
    std::string line;
    while (std::getline(input, line)) {
        for (int i = 0; i < 3; ++i) {
            const std::regex expression("^([[:space:]]*" + keys[i] +
                "[[:space:]]*=[[:space:]]*)(0[xX][0-9a-fA-F]+|[0-9]+)");
            std::smatch match;
            if (std::regex_search(line, match, expression)) {
                const std::string replacement = match.str(1) + hexBytes(values[i]);
                line = replacement + line.substr(match.length());
                ++replacements[i];
            }
        }
        result << line << '\n';
    }
    if (!input.eof()) throw Error("Error reading linker template: " + source.string());
    for (int i = 0; i < 3; ++i) {
        if (replacements[i] != 1) {
            throw Error("Linker template must assign " + keys[i] + " exactly once");
        }
    }
    return result.str();
}

std::string safeName(std::string name) {
    for (char &c : name) {
        if (!std::isalnum(static_cast<unsigned char>(c)) && c != '_' && c != '-') c = '_';
    }
    return name.empty() ? "applet" : name;
}

std::string quoted(const std::string &value) {
    const bool special = value.empty() || value.find_first_of(" \t\n\"'\\$;&|<>*?()[]{}!") != std::string::npos;
    if (!special) return value;
    std::string result = "'";
    for (char c : value) result += (c == '\'') ? "'\\''" : std::string(1, c);
    return result + "'";
}

void runCommand(const std::vector<std::string> &cmd, bool show) {
    if (cmd.empty()) throw Error("Internal error: empty command");
    if (show) {
        std::cout << "+";
        for (const std::string &a : cmd) std::cout << " " << quoted(a);
        std::cout << '\n' << std::flush;
    }
    // All arguments passed directly; no shell expansion or eval is involved.
    std::vector<char *> args;
    for (const std::string &item : cmd) args.push_back(const_cast<char *>(item.c_str()));
    args.push_back(nullptr);
    const pid_t child = ::fork();
    if (child < 0) throw Error("Cannot fork child process: " + std::string(std::strerror(errno)));
    if (child == 0) {
        ::execvp(args[0], args.data());
        std::cerr << "Cannot run " << cmd[0] << ": " << std::strerror(errno) << '\n';
        ::_exit(127);
    }
    int status = 0;
    pid_t waited = 0;
    do {
        waited = ::waitpid(child, &status, 0);
    } while (waited < 0 && errno == EINTR);
    if (waited < 0) throw Error("waitpid failed: " + std::string(std::strerror(errno)));
    if (WIFSIGNALED(status)) {
        throw Error(fs::path(cmd[0]).filename().string() + " terminated by signal " +
                    std::to_string(WTERMSIG(status)));
    }
    if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
        throw Error(fs::path(cmd[0]).filename().string() + " failed (exit " +
                    std::to_string(WEXITSTATUS(status)) + ")");
    }
}

// Verifies linker output before passing it to the native packer (which performs
// much stronger ELF, relocation and format validation).
void checkElf(const fs::path &file) {
    std::ifstream in(file, std::ios::binary);
    unsigned char header[20]{};
    if (!in.read(reinterpret_cast<char *>(header), sizeof(header)) ||
        header[0] != 0x7f || header[1] != 'E' || header[2] != 'L' || header[3] != 'F' ||
        header[4] != 1 || header[5] != 1 || header[6] != 1 ||
        header[16] != 3 || header[17] != 0 || header[18] != 40 || header[19] != 0) {
        throw Error("LLD output is not little-endian ARM ELF32 ET_DYN: " + file.string());
    }
}

void build(const Options &opt) {
    const fs::path sdk = findSdk(opt);
    const fs::path gcc = sdk / "tools/bin/arm-none-eabi-gcc";
    const fs::path lld = findLld(sdk);
    const fs::path packer = sdk / "tools/sidbox-v2-packer";
    const fs::path cgarm = sdk / "tools/cgarm/lib/libcgarm.a";
    const fs::path api = sdk / "api";
    const fs::path libraries = sdk / "libraries";
    const fs::path headers = sdk / "tools/cgarm/include";
    requireExecutable(gcc, "ARM GCC");
    requireExecutable(lld, "LLVM ld.lld");
    requireExecutable(packer, "V2 packer");
    requireFile(cgarm, "libcgarm.a");
    requireFile(sdk / "gui_v2.ld", "GUI V2 linker template");
    if (!fs::is_directory(headers)) throw Error("CGARM headers missing: " + headers.string());
    if (!fs::is_directory(libraries)) throw Error("SDK libraries directory missing: " + libraries.string());

    std::vector<fs::path> sources;
    sources.reserve(opt.sources.size() + 6);
    for (const fs::path &source : opt.sources) {
        fs::path path = absolutePath(source);
        requireFile(path, "Source file");
        if (!sourceExtension(path)) {
            throw Error("CGARM supports .c/.cc/.cpp/.res (or a single .proj): " + path.string());
        }
        if (std::find(sources.begin(), sources.end(), path) != sources.end()) {
            throw Error("Duplicate source: " + path.string());
        }
        sources.push_back(path);
    }
    // Matches MainWindow::sidboxApiSourceFiles() for V2: no V1 applet.s.
    for (const char *relative : {"apis.c", "syscalls.c", "crt/crt.c",
                                 "graphics/graphics.c", "audio/audio.c", "touch/touch.c"}) {
        fs::path path = api / relative;
        requireFile(path, "SDK API source");
        sources.push_back(path);
    }
    std::vector<fs::path> sdkArchives;
    for (const auto &entry : fs::recursive_directory_iterator(libraries)) {
        if (entry.is_regular_file() && entry.path().extension() == ".a") {
            sdkArchives.push_back(entry.path());
        }
    }
    std::sort(sdkArchives.begin(), sdkArchives.end());

    const fs::path output = absolutePath(opt.output);
    const std::string base = safeName(output.stem().string());
    const fs::path buildDir = output.parent_path() / "build" / "cgarm" / base;
    const fs::path linkerScript = buildDir / (base + ".ld");
    const fs::path elf = buildDir / (base + ".elf");
    const fs::path map = buildDir / (base + ".map");
    const std::string script = generatedLinkerScript(sdk / "gui_v2.ld", opt);

    std::cout << "CGARM (Beta) CLI — relocatable ARM ELF (V2)\n"
              << "SDK:     " << sdk << '\n'
              << "GCC:     " << gcc << '\n'
              << "LLD:     " << lld << '\n'
              << "Library: " << cgarm << '\n'
              << "APP:     " << output << '\n'
              << "RAM:     " << opt.appKb << " KiB allowance, "
              << opt.heapKb << " KiB heap, " << opt.stackKb << " KiB private stack\n"
              << "Sources: " << opt.sources.size() << " applet + 6 SDK API\n"
              << "Build:   " << buildDir << '\n';

    if (!opt.dryRun) {
        fs::create_directories(buildDir);
        std::ofstream out(linkerScript, std::ios::binary | std::ios::trunc);
        if (!out) throw Error("Cannot create linker script: " + linkerScript.string());
        out << script;
        if (!out) throw Error("Error writing linker script: " + linkerScript.string());
    } else {
        std::cout << "[dry-run] Would generate linker script: " << linkerScript << '\n';
    }

    std::vector<std::string> flags = {
        "-mcpu=cortex-m7", "-mthumb", "-mfpu=fpv5-d16", "-mfloat-abi=hard",
        "-std=gnu99", opt.optimisation, "--specs=nano.specs", "-mno-unaligned-access",
        "-DSIDBOX_STARTUP_HEADER_IN_ASM", "-DSIDBOX_V2_HEAP_BYTES=" + std::to_string(opt.heapKb * 1024u),
        "-DSIDBOX_APPLET_V2", "-fPIE", "-fPIC", "-fno-plt", "-fvisibility=hidden",
        "-ffreestanding", "-fno-builtin",
        "-I", api.string(), "-I", libraries.string(),
        "-I", headers.string()
    };
    if (opt.functionSections) flags.push_back("-ffunction-sections");
    if (opt.dataSections) flags.push_back("-fdata-sections");
    if (opt.stackUsage) flags.push_back("-fstack-usage");
    if (opt.suppressWarnings) flags.push_back("-w");
    else {
        if (opt.wall) flags.push_back("-Wall");
        if (opt.wextra) flags.push_back("-Wextra");
    }
    flags.insert(flags.end(), opt.projectCompilerFlags.begin(), opt.projectCompilerFlags.end());
    flags.insert(flags.end(), opt.extraCppFlags.begin(), opt.extraCppFlags.end());

    std::vector<std::string> objects;
    objects.reserve(sources.size());
    for (std::size_t i = 0; i < sources.size(); ++i) {
        const fs::path object = buildDir / ("v2_unit_" + std::to_string(i) + ".o");
        objects.push_back(object.string());
        std::vector<std::string> command = {gcc.string()};
        command.insert(command.end(), flags.begin(), flags.end());
        std::string ext = sources[i].extension().string();
        std::transform(ext.begin(), ext.end(), ext.begin(),
                       [](unsigned char c) { return std::tolower(c); });
        if (ext == ".res") {
            command.insert(command.end(), {"-x", "c"});
        }
        command.insert(command.end(), {"-c", sources[i].string(), "-o", object.string()});
        if (!opt.dryRun) {
            std::cout << "Compiling [" << (i + 1) << "/" << sources.size() << "]: "
                      << sources[i].filename() << '\n' << std::flush;
            runCommand(command, opt.verbose);
        } else {
            std::cout << "+";
            for (const std::string &a : command) std::cout << " " << quoted(a);
            std::cout << '\n';
        }
    }

    std::vector<std::string> link = {
        lld.string(), "-pie", "-Bsymbolic", "--no-undefined", "--nostdlib",
        "--gc-sections", "--entry=applet_entry", "-T", linkerScript.string(),
        "-Map=" + map.string()
    };
    link.insert(link.end(), objects.begin(), objects.end());
    link.insert(link.end(), {"--start-group", cgarm.string()});
    for (const fs::path &archive : sdkArchives) link.push_back(archive.string());
    link.insert(link.end(), {"--end-group", "-o", elf.string()});

    if (opt.dryRun) {
        std::cout << "[dry-run] Link:\n";
        for (const std::string &a : link) std::cout << quoted(a) << ' ';
        std::cout << "\n[dry-run] Pack:\n";
        std::cout << quoted(packer.string()) << " " << quoted(elf.string()) << " "
                  << quoted(output.string()) << " --heap " << opt.heapKb * 1024u
                  << " --stack " << opt.stackKb * 1024u << "\n";
        std::cout << "Dry run complete. No files were changed.\n";
        return;
    }

    std::cout << "Linking ET_DYN using LLVM LLD...\n" << std::flush;
    runCommand(link, opt.verbose);
    checkElf(elf);
    std::cout << "Packing relocatable V2 .app...\n" << std::flush;
    runCommand({packer.string(), elf.string(), output.string(), "--heap",
                std::to_string(opt.heapKb * 1024u), "--stack",
                std::to_string(opt.stackKb * 1024u)}, opt.verbose);
    requireFile(output, "Packer output");
    std::cout << "\nSUCCESS: " << output << " (" << fs::file_size(output) << " bytes)\n";
    std::cout << "ELF: " << elf << "\nMAP: " << map << '\n';
}

} // namespace

int main(int argc, char **argv) {
    try {
        Options opts = parse(argc, argv);
        if (opts.showHelp) {
            usage(std::cout);
            return 0;
        }
        if (opts.projectMode) loadProject(opts);
        validateMemory(opts);
        build(opts);
        return 0;
    } catch (const Error &error) {
        std::cerr << "cgarm-build: ERROR: " << error.what() << '\n';
        return 1;
    } catch (const std::exception &error) {
        std::cerr << "cgarm-build: ERROR: " << error.what() << '\n';
        return 1;
    }
}
