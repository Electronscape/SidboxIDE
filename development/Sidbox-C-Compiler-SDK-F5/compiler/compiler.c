#include "compiler.h"
#include "apicore.h"
#include "applet_v2_format.h"
#include "generated_runtime.h"

#include <stddef.h>
#include <string.h>

enum {
    TOK_END = 256, TOK_NAME, TOK_NUMBER, TOK_UNSIGNED_NUMBER, TOK_STRING,
    TOK_UNSUPPORTED, TOK_APIS_INCLUDE,
    TOK_INT, TOK_VOID, TOK_EXTERN, TOK_CONST, TOK_CHAR,
    TOK_IF, TOK_ELSE, TOK_WHILE, TOK_RETURN, TOK_STATIC, TOK_BREAK, TOK_CONTINUE, TOK_FOR,
    TOK_SWITCH, TOK_CASE, TOK_DEFAULT, TOK_STRUCT, TOK_UNION, TOK_TYPEDEF, TOK_SIZEOF, TOK_ENUM,
    TOK_EQ, TOK_NE, TOK_LE, TOK_GE, TOK_AND, TOK_OR, TOK_ARROW,
    TOK_INC, TOK_DEC, TOK_ADD_ASSIGN, TOK_SUB_ASSIGN, TOK_SHL, TOK_SHR,
    TOK_BAND_ASSIGN, TOK_BOR_ASSIGN, TOK_BXOR_ASSIGN, TOK_SHL_ASSIGN, TOK_SHR_ASSIGN, TOK_SKIP
};

enum {
    /* The 128 KiB source is lexed in place: no full token array is needed. */
    IMAGE_LIMIT = 65536, STRING_LIMIT = 16384, LOCAL_LIMIT = 64,
    FUNCTION_LIMIT = 256, CALL_LIMIT = 2048, RETURN_LIMIT = 1024,
    ADDRESS_LIMIT = 2048, GLOBAL_LIMIT = 128, FUNCTION_PARAMS = 5,
    NESTING_LIMIT = 32, LOOP_LIMIT = 32, LOOP_JUMP_LIMIT = 512,
    CALLBACK_STACK_BYTES = 8192, BYTE_ARRAY_LIMIT = 256 * 1024,
    HEADER_POOL_LIMIT = 32 * 1024, HEADER_LIMIT = 32,
    HEADER_PATH_LIMIT = 256, INCLUDE_DEPTH_LIMIT = 12,
    MACRO_LIMIT = 128, MACRO_NAME_LIMIT = 64, CONDITIONAL_LIMIT = 32,
    SWITCH_CASE_LIMIT = 256, SWITCH_BREAK_LIMIT = 512,
    CONTROL_LIMIT = 64, STRUCT_LIMIT = 24, STRUCT_FIELDS = 16, TYPEDEF_LIMIT = 64,
    INITIAL_WORD_LIMIT = 1024, PRIVATE_ARENA_BYTES = 32768,
    ENUM_TAG_LIMIT = 32, ENUM_CONSTANT_LIMIT = 160
};

enum { BUILTIN_MESSAGE = 4, BUILTIN_TICKS = 8, BUILTIN_BUTTONS = 12 };
enum {
    LOCAL_INT, LOCAL_GADGET, LOCAL_POINTER, LOCAL_S32, LOCAL_ARGV, LOCAL_WINDOW, LOCAL_MESSAGE,
    GLOBAL_BYTE_ARRAY, GLOBAL_INT_ARRAY, LOCAL_INT_ARRAY, LOCAL_INT_POINTER, LOCAL_PADDING,
    LOCAL_FUNCTION_POINTER, LOCAL_STRUCT, LOCAL_STRUCT_POINTER, GLOBAL_STRUCT,
    LOCAL_STRUCT_ARRAY, GLOBAL_STRUCT_ARRAY, LOCAL_STRUCT_DOUBLE_POINTER, LOCAL_INT_DOUBLE_POINTER
};
enum { RETURN_INT, RETURN_VOID, RETURN_WINDOW, RETURN_INT_POINTER, RETURN_RECORD, RETURN_STRUCT_POINTER };
enum { VALUE_INT, VALUE_UNSIGNED, VALUE_VOID, VALUE_POINTER, VALUE_INT_POINTER, VALUE_STRUCT_DOUBLE_POINTER, VALUE_RECORD, VALUE_INT_DOUBLE_POINTER };
enum { DISCARD_VALUE, REQUIRE_INTEGER, REQUIRE_SCALAR, STATEMENT_VALUE, REQUIRE_INT_POINTER };
enum { ADDRESS_STRING, ADDRESS_GLOBAL, ADDRESS_FUNCTION };

typedef struct {
    const char *text;
    uint32_t length;
    uint32_t number;
    uint32_t line;
    uint32_t column;
    int kind;
    uint8_t file_index;
    const char *path; /* NULL for original source, path for included .h */
} Token;

typedef struct {
    Token name;
    uint32_t entry;
    uint8_t arity;
    uint8_t builtin;
    uint8_t defined;
    uint8_t return_type;
    uint8_t is_static;
    uint8_t unit;
    uint8_t return_struct_id;
    uint8_t param_types[FUNCTION_PARAMS];
    uint8_t param_struct_ids[FUNCTION_PARAMS];
} Function;

typedef struct {
    Token name;
    uint32_t initial;
    uint32_t offset;
    uint8_t type;
    uint8_t unit;
    uint8_t struct_id;
    uint8_t in_data;
    uint8_t is_const;
    uint16_t init_offset;
    uint16_t init_count;
    uint32_t array_count;
} Global;

typedef struct {
    uint8_t arity;
    uint8_t return_type;
    uint8_t params[FUNCTION_PARAMS];
} FunctionPointerSignature;

typedef struct {
    Token name;
    uint8_t scope;
    uint8_t type;
    uint8_t struct_id;
    FunctionPointerSignature callback;
    uint16_t array_count;
    uint8_t is_const;
} Local;

typedef struct {
    Token name;
    uint8_t record_id;          /* 255 = scalar int, otherwise record type */
    uint8_t is_pointer;         /* pointer fields occupy one word, including self links */
    uint16_t offset_words;      /* unions place every member at word zero */
} RecordField;

typedef struct {
    Token name;                 /* tag name, or anonymous typedef's name */
    RecordField fields[STRUCT_FIELDS];
    uint16_t size_words;
    uint8_t count;
    uint8_t is_union;
    uint8_t anonymous;
    uint8_t complete;
    uint8_t unit;
} StructDef;

typedef struct {
    Token name;
    uint8_t record_id;          /* 255 = int */
    uint8_t unit;
} TypeAlias;

typedef struct {
    Token name;
    uint32_t value;
    uint8_t unit;
} EnumConstant;

typedef struct {
    Token name;
    uint8_t unit;
} EnumTag;

typedef struct {
    uint32_t at;
    uint16_t target;
} Reference;

typedef struct {
    uint32_t at;
    uint16_t target;
    uint8_t kind;
} AddressReference;

typedef struct {
    uint32_t at;
    uint8_t is_break;
} LoopJump;

typedef struct {
    uint32_t target;
    uint32_t value;
} SwitchCase;

typedef struct {
    char path[HEADER_PATH_LIMIT];
    uint32_t offset, length;
    uint16_t visited_units;
    uint8_t pragma_once;
    char guard[MACRO_NAME_LIMIT];
} IncludeHeader;

typedef struct {
    const char *source;
    const char *path;
    uint32_t length, pos, line, column;
    int header_index;
    unsigned conditional_depth;
} IncludeFrame;

typedef struct {
    char name[MACRO_NAME_LIMIT];
    int64_t value;
} PreprocMacro;

typedef struct {
    uint8_t parent_active;
    uint8_t active;
    uint8_t branch_taken;
    uint8_t seen_else;
} Conditional;


typedef struct {
    const char *source;
    uint32_t length;
    uint8_t file_index;
    uint32_t pos;
    uint32_t line;
    uint32_t column;
    Token token;
    Token lookahead;
    SidcDiagnostic diagnostic;
    SidcReadHeader header_reader;
    SidcReadApiCore api_reader;
    const char *active_path;
    int current_header;
    IncludeFrame include_stack[INCLUDE_DEPTH_LIMIT];
    unsigned include_depth;
    IncludeHeader headers[HEADER_LIMIT];
    unsigned header_count;
    uint32_t header_bytes;
    char header_pool[HEADER_POOL_LIMIT];
    PreprocMacro macros[MACRO_LIMIT];
    unsigned macro_count;
    Conditional conditional[CONDITIONAL_LIMIT];
    unsigned conditional_depth;
    SidcApiHeader api;
    SidcApiCall api_calls[SIDC_API_CALLS];
    SidcApiConstant api_constants[SIDC_API_CONSTANTS];
    SidcApiMessage message;

    uint32_t pc;
    uint32_t string_bytes;
    uint8_t strings[STRING_LIMIT];
    AddressReference addresses[ADDRESS_LIMIT];
    unsigned address_count;
    Global globals[GLOBAL_LIMIT];
    unsigned global_count;
    StructDef structs[STRUCT_LIMIT];
    unsigned struct_count;
    TypeAlias aliases[TYPEDEF_LIMIT];
    unsigned alias_count;
    EnumConstant enum_constants[ENUM_CONSTANT_LIMIT];
    unsigned enum_constant_count;
    EnumTag enum_tags[ENUM_TAG_LIMIT];
    unsigned enum_tag_count;
    uint32_t global_bytes;
    uint32_t array_bytes;
    uint32_t initial_values[INITIAL_WORD_LIMIT];
    unsigned initial_used;
    Function functions[FUNCTION_LIMIT];
    unsigned function_count;
    Reference calls[CALL_LIMIT];
    unsigned call_count;
    uint32_t returns[RETURN_LIMIT];
    unsigned return_count;
    uint8_t return_type;
    uint8_t return_struct_id;
    uint8_t return_buffer_slot;
    Local locals[LOCAL_LIMIT];
    unsigned local_count;
    unsigned local_peak;
    unsigned scope;
    unsigned nesting;
    unsigned value_record_id;   /* the type of the last record-pointer expression */
    unsigned loop_depth;
    unsigned loop_jump_count;
    LoopJump loop_jumps[LOOP_JUMP_LIMIT];
    unsigned control_depth;
    uint8_t control_kind[CONTROL_LIMIT]; /* 1=loop, 2=switch */
    unsigned switch_break_count;
    uint32_t switch_breaks[SWITCH_BREAK_LIMIT];
    SwitchCase switch_cases[SWITCH_CASE_LIMIT];
    unsigned switch_case_count;
    uint16_t heap_global_index;
    uint8_t heap_used;
} Compiler;

/* Freestanding Thumb-2 allocator, built without libc or external relocations. */
/* Generated from tests/heap_runtime_reference.c with freestanding Thumb-2 clang.
   Both embedded sections have no external relocations or libc calls. */
static const uint8_t sidc_heap_alloc_code[] = {71,246,241,114,72,242,16,3,130,26,207,246,255,115,154,66,1,210,0,32,112,71,240,181,3,175,77,248,4,189,10,104,3,70,0,42,71,246,248,112,8,191,8,34,162,241,8,14,134,69,79,240,0,0,50,216,18,240,7,5,47,209,216,29,79,246,248,115,9,42,0,234,3,12,43,211,8,35,4,224,24,25,0,241,8,3,147,66,36,210,205,88,0,32,37,240,0,68,8,44,27,211,21,240,7,6,24,209,174,235,3,6,180,66,20,216,0,45,235,212,100,69,233,211,164,235,12,2,200,24,16,42,6,211,0,235,12,1,100,70,8,58,0,35,193,233,2,35,4,241,0,65,0,34,224,232,2,18,93,248,4,187,240,189,71,246,248,112,128,26,132,69,79,240,0,0,245,216,139,24,12,241,0,70,142,80,98,68,88,96,2,241,8,0,8,96,3,241,8,0,93,248,4,187,240,189};
static const uint8_t sidc_heap_free_code[] = {0,40,117,208,1,241,16,2,130,66,113,216,1,245,0,66,130,66,109,217,66,26,80,7,24,191,112,71,240,181,3,175,77,248,4,189,8,104,71,246,248,115,160,241,8,14,158,69,90,216,16,240,7,3,87,209,9,40,85,211,162,241,8,3,79,240,1,12,8,34,141,88,37,240,0,68,8,44,75,211,21,240,7,6,72,209,174,235,2,6,180,66,68,216,154,66,4,208,34,68,8,50,130,66,237,211,9,224,181,241,255,63,58,220,34,68,79,240,0,12,8,50,130,66,227,211,2,224,95,234,204,114,48,209,202,88,9,40,34,240,0,66,202,80,42,211,79,240,8,12,4,224,131,66,35,208,131,66,156,70,34,210,81,248,12,48,12,241,8,2,35,240,0,68,0,43,4,235,2,3,242,212,131,66,238,210,205,88,0,45,235,212,8,45,17,211,21,240,7,6,14,209,174,235,3,3,157,66,10,216,99,25,3,241,8,4,65,248,12,64,163,24,131,66,235,211,217,231,193,248,0,192,93,248,4,187,189,232,240,64,112,71};
static Compiler compiler;
static struct {
    SBV2Header header;
    uint8_t image[IMAGE_LIMIT];
} output;
static uint8_t api_file[sizeof(SidcApiHeader) + SIDC_API_CALLS * sizeof(SidcApiCall) +
                        SIDC_API_CONSTANTS * sizeof(SidcApiConstant) + sizeof(SidcApiMessage) +
                        sizeof(uint32_t)];

static void error_at(Compiler *c, Token token, const char *message)
{
    if (c->diagnostic.message)
        return;
    c->diagnostic = (SidcDiagnostic){message, token.line, token.column, token.file_index, token.path};
}

static void error(Compiler *c, const char *message)
{
    error_at(c, c->token, message);
}

static int name_is(Token token, const char *name)
{
    size_t length = strlen(name);
    return token.length == length && memcmp(token.text, name, length) == 0;
}

static int same_name(Token a, Token b)
{
    return a.length == b.length && memcmp(a.text, b.text, a.length) == 0;
}

static unsigned peek(const Compiler *c, uint32_t ahead)
{
    uint32_t at = c->pos + ahead;
    return at < c->length ? (unsigned char)c->source[at] : 0u;
}

static unsigned read_char(Compiler *c)
{
    if (c->pos == c->length)
        return 0;
    unsigned ch = (unsigned char)c->source[c->pos++];
    if (ch == '\n' || (ch == '\r' && peek(c, 0) != '\n')) {
        ++c->line;
        c->column = 1;
    } else {
        ++c->column;
    }
    return ch;
}

static int letter(unsigned ch)
{
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_';
}

static int digit(unsigned ch)
{
    return ch >= '0' && ch <= '9';
}

static unsigned hex_digit(unsigned ch)
{
    if (digit(ch))
        return ch - '0';
    ch |= 32;
    return ch >= 'a' && ch <= 'f' ? ch - 'a' + 10 : 16u;
}

static Token here(const Compiler *c)
{
    return (Token){
        .text = c->source + c->pos, .line = c->line,
        .column = c->column, .kind = TOK_END, .file_index = c->file_index,
        .path = c->current_header < 0 ? NULL : c->active_path
    };
}

/* The compiler does not use the host preprocessor. Its local include reader
   keeps the original source file/line mapping intact for diagnostics. */
static Token scan(Compiler *c);

static int enter_header(Compiler *c, Token directive, const char *name,
                        unsigned name_length)
{
    if (!c->header_reader) {
        error_at(c, directive, "Local #include needs a project header reader");
        return 0;
    }
    if (name_length == 0 || name_length >= HEADER_PATH_LIMIT) {
        error_at(c, directive, "Invalid included header name");
        return 0;
    }
    char name_copy[HEADER_PATH_LIMIT];
    memcpy(name_copy, name, name_length);
    name_copy[name_length] = 0;
    size_t name_len = strlen(name_copy);
    if (name_len < 3 || strcmp(name_copy + name_len - 2, ".h") != 0) {
        error_at(c, directive, "Only quoted .h project headers are supported");
        return 0;
    }
    char path[HEADER_PATH_LIMIT];
    uint32_t bytes = 0;
    if (!c->header_reader(c->active_path, name_copy, NULL, 0, &bytes,
                          path, sizeof(path))) {
        error_at(c, directive, "Could not resolve included header path");
        return 0;
    }
    unsigned index = 0;
    for (; index < c->header_count; ++index)
        if (strcmp(c->headers[index].path, path) == 0)
            break;
    if (index == c->header_count) {
        if (c->header_count == HEADER_LIMIT) {
            error_at(c, directive, "Too many unique project headers");
            return 0;
        }
        uint32_t available = HEADER_POOL_LIMIT - c->header_bytes;
        if (available == 0) {
            error_at(c, directive, "Included header text exceeds 32 KiB");
            return 0;
        }
        if (!c->header_reader(c->active_path, name_copy,
                              c->header_pool + c->header_bytes, available, &bytes,
                              path, sizeof(path))) {
            error_at(c, directive, "Could not open header or header exceeds 32 KiB");
            return 0;
        }
        if (bytes > available || memchr(c->header_pool + c->header_bytes, 0, bytes)) {
            error_at(c, directive, "Included header is invalid or exceeds 32 KiB");
            return 0;
        }
        IncludeHeader *h = &c->headers[c->header_count++];
        memcpy(h->path, path, strlen(path) + 1u);
        h->offset = c->header_bytes;
        h->length = bytes;
        h->visited_units = 0;
        h->pragma_once = 0;
        h->guard[0] = 0;
        /* Recognise a conventional first #ifndef guard even if the file
           starts with copyright comments or blank lines. */
        const char *s = c->header_pool + h->offset;
        const char *end = s + bytes;
        for (;;) {
            while (s < end && (*s == ' ' || *s == '\t' || *s == '\r' || *s == '\n')) ++s;
            if (end - s >= 2 && s[0] == '/' && s[1] == '/') {
                s += 2;
                while (s < end && *s != '\n') ++s;
            } else if (end - s >= 2 && s[0] == '/' && s[1] == '*') {
                s += 2;
                while (s + 1 < end && !(s[0] == '*' && s[1] == '/')) ++s;
                if (s + 1 >= end) break;
                s += 2;
            } else break;
        }
        if (end - s >= 7 && memcmp(s, "#ifndef", 7) == 0 &&
            (s + 7 == end || s[7] == ' ' || s[7] == '\t')) {
            s += 7;
            while (s < end && (*s == ' ' || *s == '\t')) ++s;
            const char *name_start = s;
            while (s < end && (letter((unsigned char)*s) || digit((unsigned char)*s))) ++s;
            size_t guard_bytes = (size_t)(s - name_start);
            if (guard_bytes && letter((unsigned char)*name_start) &&
                guard_bytes < MACRO_NAME_LIMIT) {
                memcpy(h->guard, name_start, guard_bytes);
                h->guard[guard_bytes] = 0;
            }
        }
        c->header_bytes += bytes;
    }
    IncludeHeader *header = &c->headers[index];
    uint16_t unit = (uint16_t)(1u << c->file_index);
    if (header->pragma_once && (header->visited_units & unit))
        return 1;
    if (c->include_depth == INCLUDE_DEPTH_LIMIT) {
        error_at(c, directive, "Nested include depth exceeds 12");
        return 0;
    }
    if (header->guard[0]) {
        for (unsigned m = 0; m < c->macro_count; ++m)
            if (strcmp(c->macros[m].name, header->guard) == 0)
                return 1;
    }
    if (c->current_header == (int)index) {
        error_at(c, directive, "Recursive header include (use #pragma once or a guard)");
        return 0;
    }
    for (unsigned i = 0; i < c->include_depth; ++i)
        if (c->include_stack[i].header_index == (int)index) {
            error_at(c, directive, "Recursive header include (use #pragma once or a guard)");
            return 0;
        }
    c->include_stack[c->include_depth++] = (IncludeFrame){
        c->source, c->active_path, c->length, c->pos,
        c->line, c->column, c->current_header, c->conditional_depth
    };
    header->visited_units |= unit;
    c->source = c->header_pool + header->offset;
    c->length = header->length;
    c->pos = 0;
    c->line = c->column = 1;
    c->active_path = header->path;
    c->current_header = (int)index;
    return 1;
}

static Token scan_include(Compiler *c, Token token);

/* A deliberately bounded integer-only preprocessor. Numeric definitions can
   be used by #if and in simple C expressions. Function-like macros and text
   substitution are not part of this compiler subset. */
static int macro_index(const Compiler *c, const char *name, size_t length)
{
    for (unsigned i = 0; i < c->macro_count; ++i)
        if (strlen(c->macros[i].name) == length &&
            memcmp(c->macros[i].name, name, length) == 0)
            return (int)i;
    return -1;
}

static int enum_constant_lookup(const Compiler *c, const char *name, size_t length)
{
    for (int i = (int)c->enum_constant_count - 1; i >= 0; --i)
        if (c->enum_constants[i].unit == c->file_index &&
            c->enum_constants[i].name.length == length &&
            !memcmp(c->enum_constants[i].name.text, name, length)) return i;
    return -1;
}

static int preproc_active(const Compiler *c)
{
    return !c->conditional_depth || c->conditional[c->conditional_depth - 1u].active;
}

typedef struct {
    Compiler *c;
    Token token;
    const char *at;
    const char *end;
    unsigned nesting;
    int bad;
    int evaluate;
} PreprocExpr;

static void pp_space(PreprocExpr *e)
{
    while (e->at < e->end && (*e->at == ' ' || *e->at == '\t'))
        ++e->at;
}

static int pp_take(PreprocExpr *e, const char *word)
{
    pp_space(e);
    size_t count = strlen(word);
    if ((size_t)(e->end - e->at) < count || memcmp(e->at, word, count))
        return 0;
    e->at += count;
    return 1;
}

static int64_t pp_or(PreprocExpr *e);

static int64_t pp_atom(PreprocExpr *e)
{
    pp_space(e);
    if (++e->nesting > 32u) { e->bad = 1; --e->nesting; return 0; }
    int64_t result = 0;
    if (pp_take(e, "(")) {
        result = pp_or(e);
        if (!pp_take(e, ")")) e->bad = 1;
    } else if (e->at < e->end && digit((unsigned char)*e->at)) {
        unsigned base = 10;
        if (e->end - e->at > 2 && e->at[0] == '0' &&
            (e->at[1] == 'x' || e->at[1] == 'X')) { e->at += 2; base = 16; }
        else if (e->at[0] == '0') base = 8;
        unsigned got = 0;
        while (e->at < e->end && hex_digit((unsigned char)*e->at) < base) {
            unsigned n = hex_digit((unsigned char)*e->at++);
            if ((uint32_t)result > (UINT32_MAX - n) / base) e->bad = 1;
            result = result * base + n;
            ++got;
        }
        if (!got) e->bad = 1;
        if (e->at < e->end && (*e->at == 'U' || *e->at == 'u')) ++e->at;
    } else if (e->at < e->end && letter((unsigned char)*e->at)) {
        const char *first = e->at;
        while (e->at < e->end && (letter((unsigned char)*e->at) || digit((unsigned char)*e->at)))
            ++e->at;
        size_t length = (size_t)(e->at - first);
        if (length == 7 && memcmp(first, "defined", 7) == 0) {
            int paren = pp_take(e, "(");
            pp_space(e);
            const char *name = e->at;
            if (e->at == e->end || !letter((unsigned char)*e->at)) e->bad = 1;
            while (e->at < e->end && (letter((unsigned char)*e->at) || digit((unsigned char)*e->at)))
                ++e->at;
            result = macro_index(e->c, name, (size_t)(e->at - name)) >= 0;
            if (paren && !pp_take(e, ")")) e->bad = 1;
        } else {
            int i = macro_index(e->c, first, length);
            result = i < 0 ? 0 : e->c->macros[i].value;
        }
    } else e->bad = 1;
    --e->nesting;
    return result;
}

static int64_t pp_unary(PreprocExpr *e)
{
    if (++e->nesting > 32u) {
        e->bad = 1;
        --e->nesting;
        return 0;
    }
    int64_t value;
    if (pp_take(e, "!")) value = !pp_unary(e);
    else if (pp_take(e, "~")) value = ~pp_unary(e);
    else if (pp_take(e, "+")) value = pp_unary(e);
    else if (pp_take(e, "-")) value = -pp_unary(e);
    else value = pp_atom(e);
    --e->nesting;
    return value;
}

static int64_t pp_mul(PreprocExpr *e)
{
    int64_t value = pp_unary(e);
    for (;;) {
        if (pp_take(e, "*")) {
            value *= pp_unary(e);
        } else {
            int divide = pp_take(e, "/");
            if (!divide && !pp_take(e, "%")) return value;
            int64_t rhs = pp_unary(e);
            if (rhs == 0) {
                if (e->evaluate) e->bad = 1;
                value = 0;
                continue;
            }

            /* 64-bit software division using only shifts and subtraction.
               CGARM's runtime has no __aeabi_ldivmod/__aeabi_uldivmod. */
            uint64_t a = value < 0 ? 0u - (uint64_t)value : (uint64_t)value;
            uint64_t b = rhs < 0 ? 0u - (uint64_t)rhs : (uint64_t)rhs;
            uint64_t q = 0, r = 0;
            for (int bit = 63; bit >= 0; --bit) {
                r = (r << 1) | ((a >> bit) & 1u);
                if (r >= b) {
                    r -= b;
                    q |= (uint64_t)1 << bit;
                }
            }
            if (divide) {
                int negative = (value < 0) != (rhs < 0);
                if (q > (uint64_t)INT64_MAX + (unsigned)negative) {
                    e->bad = 1;
                    value = 0;
                } else if (negative) {
                    value = -(int64_t)(q - 1u) - 1;
                } else {
                    value = (int64_t)q;
                }
            } else {
                value = value < 0 ? -(int64_t)r : (int64_t)r;
            }
        }
    }
}

static int64_t pp_add(PreprocExpr *e)
{
    int64_t value = pp_mul(e);
    for (;;) {
        if (pp_take(e, "+")) value += pp_mul(e);
        else if (pp_take(e, "-")) value -= pp_mul(e);
        else return value;
    }
}

static int64_t pp_shift(PreprocExpr *e)
{
    int64_t value = pp_add(e);
    for (;;) {
        if (pp_take(e, "<<")) {
            int64_t bits = pp_add(e);
            if (bits < 0 || bits > 31) e->bad = 1;
            else value = (int64_t)((uint32_t)value << bits);
        } else if (pp_take(e, ">>")) {
            int64_t bits = pp_add(e);
            if (bits < 0 || bits > 31) e->bad = 1;
            else value = (int64_t)((uint32_t)value >> bits);
        } else return value;
    }
}

static int64_t pp_rel(PreprocExpr *e)
{
    int64_t value = pp_shift(e);
    for (;;) {
        if (pp_take(e, "<=")) value = value <= pp_shift(e);
        else if (pp_take(e, ">=")) value = value >= pp_shift(e);
        else if (pp_take(e, "<")) value = value < pp_shift(e);
        else if (pp_take(e, ">")) value = value > pp_shift(e);
        else return value;
    }
}

static int64_t pp_eq(PreprocExpr *e)
{
    int64_t value = pp_rel(e);
    for (;;) {
        if (pp_take(e, "==")) value = value == pp_rel(e);
        else if (pp_take(e, "!=")) value = value != pp_rel(e);
        else return value;
    }
}

static int64_t pp_band(PreprocExpr *e)
{
    int64_t value = pp_eq(e);
    for (;;) {
        pp_space(e);
        if (e->at < e->end && e->at[0] == '&' &&
            !(e->at + 1 < e->end && e->at[1] == '&')) {
            ++e->at;
            value &= pp_eq(e);
        } else return value;
    }
}

static int64_t pp_xor(PreprocExpr *e)
{
    int64_t value = pp_band(e);
    while (pp_take(e, "^")) value ^= pp_band(e);
    return value;
}

static int64_t pp_bor(PreprocExpr *e)
{
    int64_t value = pp_xor(e);
    for (;;) {
        pp_space(e);
        if (e->at < e->end && e->at[0] == '|' &&
            !(e->at + 1 < e->end && e->at[1] == '|')) {
            ++e->at;
            value |= pp_xor(e);
        } else return value;
    }
}

static int64_t pp_and(PreprocExpr *e)
{
    int64_t value = pp_bor(e);
    while (pp_take(e, "&&")) {
        int saved = e->evaluate;
        e->evaluate = saved && value != 0;
        int64_t rhs = pp_bor(e);
        e->evaluate = saved;
        value = value && rhs;
    }
    return value;
}

static int64_t pp_or(PreprocExpr *e)
{
    int64_t value = pp_and(e);
    while (pp_take(e, "||")) {
        int saved = e->evaluate;
        e->evaluate = saved && value == 0;
        int64_t rhs = pp_and(e);
        e->evaluate = saved;
        value = value || rhs;
    }
    return value;
}

static int pp_value(Compiler *c, Token token, const char *start, const char *end, int64_t *value)
{
    PreprocExpr e = {c, token, start, end, 0, 0, 1};
    *value = pp_or(&e);
    pp_space(&e);
    if (e.bad || e.at != end) {
        error_at(c, token, "Unsupported or invalid #if integer expression");
        return 0;
    }
    return 1;
}

static void pp_line_end(Compiler *c)
{
    while (c->pos < c->length && peek(c, 0) != '\r' && peek(c, 0) != '\n')
        read_char(c);
}

static Token scan_directive(Compiler *c, Token token)
{
    uint32_t original_pos = c->pos;
    uint32_t original_column = c->column;
    while (peek(c, 0) == ' ' || peek(c, 0) == '\t') read_char(c);
    const char *word = c->source + c->pos;
    while (letter(peek(c, 0))) read_char(c);
    size_t n = (size_t)(c->source + c->pos - word);
    int include = n == 7 && !memcmp(word, "include", 7);
    int pragma = n == 6 && !memcmp(word, "pragma", 6);
    int define = n == 6 && !memcmp(word, "define", 6);
    int undef = n == 5 && !memcmp(word, "undef", 5);
    int ifdef = n == 5 && !memcmp(word, "ifdef", 5);
    int ifndef = n == 6 && !memcmp(word, "ifndef", 6);
    int if_expr = n == 2 && !memcmp(word, "if", 2);
    int elif = n == 4 && !memcmp(word, "elif", 4);
    int do_else = n == 4 && !memcmp(word, "else", 4);
    int endif = n == 5 && !memcmp(word, "endif", 5);
    if ((include || pragma) && preproc_active(c)) {
        c->pos = original_pos;
        c->column = original_column;
        return scan_include(c, token);
    }
    if (!define && !undef && !ifdef && !ifndef && !if_expr && !elif &&
        !do_else && !endif && !(include || pragma)) {
        if (preproc_active(c)) error_at(c, token, "Unsupported preprocessor directive");
        pp_line_end(c);
        return (Token){.kind = TOK_SKIP};
    }
    while (peek(c, 0) == ' ' || peek(c, 0) == '\t') read_char(c);
    const char *start = c->source + c->pos;
    pp_line_end(c);
    const char *end = c->source + c->pos;
    for (const char *s = start; s + 1 < end; ++s) {
        if (s[0] == '/' && s[1] == '/') { end = s; break; }
        if (s[0] == '/' && s[1] == '*') {
            const char *close = s + 2;
            while (close + 1 < end && !(close[0] == '*' && close[1] == '/')) ++close;
            if (close + 1 >= end) {
                error_at(c, token, "Unclosed comment on preprocessor directive");
            } else {
                close += 2;
                while (close < end && (*close == ' ' || *close == '\t')) ++close;
                if (close != end) error_at(c, token, "Unexpected text after directive comment");
            }
            end = s;
            break;
        }
    }
    while (end > start && (end[-1] == ' ' || end[-1] == '\t')) --end;
    int active = preproc_active(c);
    if (ifdef || ifndef || if_expr) {
        if (c->conditional_depth == CONDITIONAL_LIMIT) {
            error_at(c, token, "Too many nested #if directives");
            return (Token){.kind = TOK_SKIP};
        }
        int value = 0;
        if (active) {
            if (ifdef || ifndef) {
                const char *e = start;
                if (e == end || !letter((unsigned char)*e))
                    error_at(c, token, "Expected macro name after #ifdef/#ifndef");
                while (e < end && (letter((unsigned char)*e) || digit((unsigned char)*e))) ++e;
                if (e != end) error_at(c, token, "Invalid macro name after #ifdef/#ifndef");
                value = macro_index(c, start, (size_t)(e - start)) >= 0;
                if (ifndef) value = !value;
            } else {
                int64_t v = 0;
                if (pp_value(c, token, start, end, &v)) value = v != 0;
            }
        }
        c->conditional[c->conditional_depth++] = (Conditional){
            (uint8_t)active, (uint8_t)(active && value),
            (uint8_t)(active && value), 0
        };
    } else if (elif || do_else || endif) {
        unsigned boundary = c->include_depth ?
            c->include_stack[c->include_depth-1].conditional_depth : 0u;
        if (c->conditional_depth <= boundary) {
            error_at(c, token, "#elif/#else/#endif without matching #if");
            return (Token){.kind = TOK_SKIP};
        }
        Conditional *top = &c->conditional[c->conditional_depth-1];
        if (endif) {
            if (start != end) error_at(c, token, "Unexpected text after #endif");
            --c->conditional_depth;
        } else if (do_else) {
            if (start != end || top->seen_else) error_at(c, token, "Invalid or duplicate #else");
            top->active = (uint8_t)(top->parent_active && !top->branch_taken);
            top->branch_taken = 1;
            top->seen_else = 1;
        } else {
            if (top->seen_else) error_at(c, token, "#elif after #else");
            int64_t value = 0;
            int take = top->parent_active && !top->branch_taken;
            if (take) pp_value(c, token, start, end, &value);
            top->active = (uint8_t)(take && value != 0);
            if (top->active) top->branch_taken = 1;
        }
    } else if (active && (define || undef)) {
        const char *name = start;
        const char *e = name;
        if (e == end || !letter((unsigned char)*e)) {
            error_at(c, token, "Expected a valid #define/#undef name");
            return (Token){.kind = TOK_SKIP};
        }
        while (e < end && (letter((unsigned char)*e) || digit((unsigned char)*e))) ++e;
        size_t size = (size_t)(e - name);
        if (size >= MACRO_NAME_LIMIT) {
            error_at(c, token, "Macro name exceeds 63 characters");
            return (Token){.kind = TOK_SKIP};
        }
        int index = macro_index(c, name, size);
        if (undef) {
            while (e < end && (*e == ' ' || *e == '\t')) ++e;
            if (e != end) error_at(c, token, "Unexpected text after #undef");
            if (index >= 0) c->macros[index] = c->macros[--c->macro_count];
        } else {
            if (e < end && *e == '(') {
                error_at(c, token, "Function-like #define macros are not supported");
                return (Token){.kind = TOK_SKIP};
            }
            while (e < end && (*e == ' ' || *e == '\t')) ++e;
            int64_t value = 1;
            if (e != end && !pp_value(c, token, e, end, &value))
                return (Token){.kind = TOK_SKIP};
            if (index < 0) {
                if (c->macro_count == MACRO_LIMIT) {
                    error_at(c, token, "Too many #define macros");
                    return (Token){.kind = TOK_SKIP};
                }
                index = (int)c->macro_count++;
            }
            PreprocMacro *m = &c->macros[index];
            memcpy(m->name, name, size);
            m->name[size] = 0;
            m->value = value;
        }
    }
    return (Token){.kind = TOK_SKIP};
}

static Token scan_include(Compiler *c, Token token)
{
    while (peek(c, 0) == ' ' || peek(c, 0) == '\t')
        read_char(c);
    const char *directive_start = c->source + c->pos;
    while (letter(peek(c, 0)))
        read_char(c);
    size_t keyword_size = (size_t)(c->source + c->pos - directive_start);
    int include = keyword_size == 7 && memcmp(directive_start, "include", 7) == 0;
    int pragma = keyword_size == 6 && memcmp(directive_start, "pragma", 6) == 0;
    if (!include && !pragma) {
        error_at(c, token, "Unsupported preprocessor directive");
        return here(c);
    }
    while (peek(c, 0) == ' ' || peek(c, 0) == '\t')
        read_char(c);
    if (pragma) {
        const char *start = c->source + c->pos;
        while (letter(peek(c, 0)))
            read_char(c);
        if (c->current_header < 0 || (size_t)(c->source + c->pos - start) != 4 ||
            memcmp(start, "once", 4) != 0) {
            error_at(c, token, "Only #pragma once in project headers is supported");
            return here(c);
        }
        c->headers[c->current_header].pragma_once = 1;
    } else {
        unsigned open = read_char(c);
        if (open != '"' && open != '<') {
            error_at(c, token, "Expected #include \"header.h\"");
            return here(c);
        }
        unsigned close = open == '<' ? '>' : '"';
        const char *start = c->source + c->pos;
        while (c->pos < c->length && peek(c, 0) != close &&
               peek(c, 0) != '\r' && peek(c, 0) != '\n')
            read_char(c);
        unsigned header_length = (unsigned)(c->source + c->pos - start);
        if (peek(c, 0) != close || !header_length) {
            error_at(c, token, "Unclosed or empty included header path");
            return here(c);
        }
        read_char(c);
        /* Whitespace and // comments after a directive are accepted. */
        while (peek(c, 0) == ' ' || peek(c, 0) == '\t')
            read_char(c);
        if (c->pos != c->length && peek(c, 0) != '\r' && peek(c, 0) != '\n' &&
            !(peek(c, 0) == '/' && peek(c, 1) == '/')) {
            error_at(c, token, "Include directive must occupy its own line");
            return here(c);
        }
        if (header_length == 6u && memcmp(start, "apis.h", 6) == 0) {
            token.kind = TOK_APIS_INCLUDE;
            return token;
        }
        if (open != '"') {
            error_at(c, token, "Only quoted local project headers are supported");
            return here(c);
        }
        if (!enter_header(c, token, start, header_length))
            return here(c);
        return scan(c);
    }
    while (peek(c, 0) == ' ' || peek(c, 0) == '\t')
        read_char(c);
    if (c->pos != c->length && peek(c, 0) != '\r' && peek(c, 0) != '\n' &&
        !(peek(c, 0) == '/' && peek(c, 1) == '/')) {
        error_at(c, token, "#pragma once must occupy its own line");
        return here(c);
    }
    return scan(c);
}

static unsigned escape_byte(Compiler *c, Token token, const char **p, const char *end);

static Token scan(Compiler *c)
{
    if (c->diagnostic.message)
        return here(c);

    for (;;) {
    for (;;) {
        if (!preproc_active(c)) {
            while (peek(c, 0) == ' ' || peek(c, 0) == '\t') read_char(c);
            if (peek(c, 0) == '#' && c->pos < c->length) {
                Token token = here(c);
                read_char(c);
                Token result = scan_directive(c, token);
                if (c->diagnostic.message) return here(c);
                if (result.kind != TOK_SKIP) return result;
                continue;
            }
            if (c->pos < c->length) {
                pp_line_end(c);
                if (c->pos < c->length) read_char(c);
                continue;
            }
        }
        unsigned ch = peek(c, 0);
        if (ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n' ||
            ch == '\v' || ch == '\f') {
            read_char(c);
        } else if (ch == '/' && peek(c, 1) == '/') {
            while (c->pos != c->length && peek(c, 0) != '\n' && peek(c, 0) != '\r')
                read_char(c);
        } else if (ch == '/' && peek(c, 1) == '*') {
            Token start = here(c);
            read_char(c);
            read_char(c);
            while (c->pos != c->length && !(peek(c, 0) == '*' && peek(c, 1) == '/'))
                read_char(c);
            if (c->pos == c->length) {
                error_at(c, start, "Unclosed block comment");
                return here(c);
            }
            read_char(c);
            read_char(c);
        } else {
            break;
        }
    }

    int restored_include = 0;
    while (c->pos == c->length && c->include_depth) {
        restored_include = 1;
        if (c->conditional_depth !=
            c->include_stack[c->include_depth - 1u].conditional_depth) {
            error(c, "Unterminated #if in included header");
            return here(c);
        }
        IncludeFrame frame = c->include_stack[--c->include_depth];
        c->source = frame.source;
        c->active_path = frame.path;
        c->length = frame.length;
        c->pos = frame.pos;
        c->line = frame.line;
        c->column = frame.column;
        c->current_header = frame.header_index;
    }
    if (restored_include) continue;
    if (c->pos == c->length && c->conditional_depth) {
        error(c, "Unterminated #if/#ifdef/#ifndef");
        return here(c);
    }
    Token token = here(c);
    if (c->pos == c->length)
        return token;

    unsigned ch = read_char(c);
    if (ch == '#') {
        Token result = scan_directive(c, token);
        if (c->diagnostic.message) return here(c);
        if (result.kind == TOK_SKIP) continue;
        return result;
    }
    if (letter(ch)) {
        while (letter(peek(c, 0)) || digit(peek(c, 0)))
            read_char(c);
        token.length = (uint32_t)(c->source + c->pos - token.text);
        static const char *const keywords[] = {
            "int", "void", "extern", "const", "char", "if", "else", "while", "return", "static", "break", "continue", "for", "switch", "case", "default", "struct", "union", "typedef", "sizeof", "enum"
        };
        static const char *const reserved[] = {
            "auto", "do", "double",
            "float", "goto", "inline", "long", "register",
            "restrict", "short", "signed",
            "unsigned", "volatile", "_Alignas",
            "_Alignof", "_Atomic", "_Bool", "_Complex", "_Generic",
            "_Imaginary", "_Noreturn", "_Static_assert", "_Thread_local"
        };
        for (unsigned i = 0; i < sizeof(keywords) / sizeof(keywords[0]); ++i) {
            if (name_is(token, keywords[i])) {
                token.kind = (int)i + TOK_INT;
                return token;
            }
        }
        for (unsigned i = 0; i < sizeof(reserved) / sizeof(reserved[0]); ++i) {
            if (name_is(token, reserved[i])) {
                error_at(c, token, "C keyword outside the supported subset");
                return here(c);
            }
        }
        token.kind = TOK_NAME;
        int enum_number = enum_constant_lookup(c, token.text, token.length);
        if (enum_number >= 0) {
            token.number = c->enum_constants[enum_number].value;
            token.kind = TOK_NUMBER; /* enumerators in this subset are signed int */
            return token;
        }
        int macro = macro_index(c, token.text, token.length);
        if (macro >= 0) {
            int64_t value = c->macros[macro].value;
            if (value < INT32_MIN || value > UINT32_MAX) {
                error_at(c, token, "Macro integer value outside 32-bit range");
                return here(c);
            }
            token.kind = (value > INT32_MAX) ? TOK_UNSIGNED_NUMBER : TOK_NUMBER;
            token.number = (uint32_t)value;
        }
        return token;
    }
    if (digit(ch)) {
        unsigned base = ch == '0' ? 8u : 10u;
        uint32_t number = ch - '0';
        if (ch == '0' && (peek(c, 0) | 32u) == 'x') {
            read_char(c);
            base = 16;
            if (hex_digit(peek(c, 0)) == 16u)
                error_at(c, token, "Expected digits after 0x");
        }
        while (hex_digit(peek(c, 0)) < base) {
            unsigned next = hex_digit(read_char(c));
            if (number > (UINT32_MAX - next) / base) {
                error_at(c, token, "Integer literal exceeds 32-bit range");
                return here(c);
            }
            number = number * base + next;
        }
        int unsigned_literal = (peek(c, 0) | 32u) == 'u';
        if (unsigned_literal)
            read_char(c);
        if (digit(peek(c, 0)) || letter(peek(c, 0)) || peek(c, 0) == '.' ||
            (!unsigned_literal && base == 10 && number > INT32_MAX)) {
            error_at(c, token, "Expected a 32-bit int or unsigned int literal");
            return here(c);
        }
        token.kind = unsigned_literal || number > INT32_MAX ? TOK_UNSIGNED_NUMBER : TOK_NUMBER;
        token.number = number;
        return token;
    }
    if (ch == '"' || ch == '\'') {
        token.text = c->source + c->pos;
        while (c->pos != c->length) {
            unsigned part = read_char(c);
            if (part == ch) {
                token.length = (uint32_t)(c->source + c->pos - 1 - token.text);
                if (ch == '"') {
                    token.kind = TOK_STRING;
                } else {
                    const char *p = token.text;
                    const char *end = p + token.length;
                    if (p == end) {
                        error_at(c, token, "Expected one character in single quotes");
                        return here(c);
                    }
                    unsigned value = (unsigned char)*p++;
                    if (value == '\\' && p != end)
                        value = escape_byte(c, token, &p, end);
                    if (p != end)
                        error_at(c, token, "Expected one character in single quotes");
                    token.kind = TOK_NUMBER;
                    token.number = value;
                }
                return token;
            }
            if (part == '\\')
                part = read_char(c);
            if (part == 0 || part == '\n' || part == '\r')
                break;
        }
        error_at(c, token, ch == '"' ? "Unclosed string literal" : "Unclosed character constant");
        return here(c);
    }

    unsigned next = peek(c, 0);
    token.kind = (int)ch;
    if ((ch == '<' || ch == '>') && next == ch) {
        read_char(c);
        token.kind = ch == '<' ? TOK_SHL : TOK_SHR;
        if (peek(c, 0) == '=') {
            read_char(c);
            token.kind = ch == '<' ? TOK_SHL_ASSIGN : TOK_SHR_ASSIGN;
        }
    } else if (next == '=' && (ch == '+' || ch == '-')) {
        read_char(c);
        token.kind = ch == '+' ? TOK_ADD_ASSIGN : TOK_SUB_ASSIGN;
    } else if (next == '=' && (ch == '&' || ch == '|' || ch == '^')) {
        read_char(c);
        token.kind = ch == '&' ? TOK_BAND_ASSIGN : ch == '|' ? TOK_BOR_ASSIGN : TOK_BXOR_ASSIGN;
    } else if (next == ch && (ch == '+' || ch == '-')) {
        read_char(c);
        token.kind = ch == '+' ? TOK_INC : TOK_DEC;
    } else if (next == '=' && (ch == '=' || ch == '!' || ch == '<' || ch == '>')) {
        read_char(c);
        token.kind = ch == '=' ? TOK_EQ : ch == '!' ? TOK_NE : ch == '<' ? TOK_LE : TOK_GE;
    } else if (ch == next && (ch == '&' || ch == '|')) {
        read_char(c);
        token.kind = ch == '&' ? TOK_AND : TOK_OR;
    } else if (ch == '-' && next == '>') {
        read_char(c);
        token.kind = TOK_ARROW;
    } else if (ch == 0 || (next == '=' && strchr("*/%", (int)ch))) {
        error_at(c, token, "Token outside the supported C subset");
        token.kind = TOK_UNSUPPORTED;
    }
    return token;
    }
}

static void advance(Compiler *c)
{
    c->token = c->lookahead;
    c->lookahead = scan(c);
}

static int accept(Compiler *c, int kind)
{
    if (c->diagnostic.message || c->token.kind != kind)
        return 0;
    advance(c);
    return 1;
}

static int expect(Compiler *c, int kind, const char *message)
{
    if (accept(c, kind))
        return 1;
    error(c, message);
    return 0;
}

static int accept_sdk_type(Compiler *c, const char *name)
{
    if (!c->api.call_count || c->token.kind != TOK_NAME || !name_is(c->token, name))
        return 0;
    return accept(c, TOK_NAME);
}

static void put16(uint32_t at, uint16_t bits)
{
    output.image[at] = (uint8_t)bits;
    output.image[at + 1] = (uint8_t)(bits >> 8);
}

static void emit(Compiler *c, uint16_t bits)
{
    if (c->diagnostic.message)
        return;
    if (c->pc + 2u > IMAGE_LIMIT) {
        error(c, "Native image exceeds 64 KiB");
        return;
    }
    put16(c->pc, bits);
    c->pc += 2;
}

static void wide_immediate(uint32_t at, uint16_t op, unsigned reg, uint16_t value)
{
    /* MOVW/MOVT. */
    put16(at, (uint16_t)(op | ((value >> 1) & 0x400) | (value >> 12)));
    put16(at + 2, (uint16_t)(((value << 4) & 0x7000) | (reg << 8) | (value & 0xff)));
}

static void load_constant(Compiler *c, unsigned reg, uint32_t value)
{
    if (value <= 255u && reg < 8) {
        emit(c, (uint16_t)(0x2000 | (reg << 8) | value));     /* movs Rd, #imm */
        return;
    }
    uint32_t at = c->pc;
    emit(c, 0);
    emit(c, 0);
    if (value > 0xffffu) {
        emit(c, 0);
        emit(c, 0);
    }
    if (!c->diagnostic.message)
        wide_immediate(at, 0xf240, reg, (uint16_t)value);
    if (value > 0xffffu && !c->diagnostic.message)
        wide_immediate(at + 4u, 0xf2c0, reg, (uint16_t)(value >> 16));
}

static void constant(Compiler *c, uint32_t value)
{
    load_constant(c, 0, value);
}

static void load_local(Compiler *c, unsigned slot, unsigned reg)
{
    if (slot < 32u) {
        emit(c, (uint16_t)(0x6838u | (slot << 6) | reg));
    } else {
        emit(c, 0xf8d7u);                                  /* ldr.w Rn, [r7, #imm12] */
        emit(c, (uint16_t)((reg << 12) | (slot * 4u)));
    }
}

static void store_local(Compiler *c, unsigned slot, unsigned reg)
{
    if (slot < 32u) {
        emit(c, (uint16_t)(0x6038u | (slot << 6) | reg));
    } else {
        emit(c, 0xf8c7u);                                  /* str.w Rn, [r7, #imm12] */
        emit(c, (uint16_t)((reg << 12) | (slot * 4u)));
    }
}

static void local_address(Compiler *c, unsigned slot)
{
    load_constant(c, 0, slot * 4u);
    emit(c, 0x1838);                                         /* adds r0, r7, r0 */
}

static void emit_address(Compiler *c, uint8_t kind, unsigned target)
{
    if (c->address_count == ADDRESS_LIMIT) {
        error(c, "Too many data or callback references");
        return;
    }
    c->addresses[c->address_count++] = (AddressReference){c->pc, (uint16_t)target, kind};
    for (unsigned i = 0; i < 4; ++i)
        emit(c, 0);                                            /* movw/movt Rd, delta */
    unsigned reg = kind == ADDRESS_GLOBAL ? 1u : 0u;
    emit(c, 0xa200);                                           /* adr r2, #0 */
    emit(c, (uint16_t)(0x1810 | (reg << 6) | reg));            /* adds Rd, r2, Rd */
}

/* Function names are literal EBI field paths, never compiler-created wrappers. */
static int valid_api_name(const char *name, unsigned limit, int function_path)
{
    unsigned i = 0;
    if (function_path) {
        if (memcmp(name, "API.", 4) != 0) return 0;
        i = 4;
    }
    if (!letter((unsigned char)name[i])) return 0;
    int parts = 0;
    for (; i < limit; ++i) {
        unsigned ch = (unsigned char)name[i];
        if (ch == 0) return !function_path || parts >= 1;
        if (function_path && ch == '-' && i + 2 < limit &&
            name[i + 1] == '>' && letter((unsigned char)name[i + 2])) {
            ++parts;
            ++i;
            continue;
        }
        if (!letter(ch) && !digit(ch)) return 0;
    }
    return 0;
}

static int load_apicore(Compiler *c, SidcReadApiCore read_apicore)
{
    uint32_t bytes = read_apicore ? read_apicore(api_file, sizeof(api_file)) : 0;
    if (bytes == 0) {
        error(c, "Cannot read " SIDC_APICORE_PATH);
        return 0;
    }
    SidcApiHeader header;
    uint32_t crc;
    if (bytes < sizeof(header) + sizeof(crc) || bytes > sizeof(api_file))
        goto invalid;
    unsigned payload = bytes - sizeof(crc);
    memcpy(&crc, api_file + payload, sizeof(crc));
    if (SBV2_CRC32(api_file, payload) != crc)
        goto invalid;
    memcpy(&header, api_file, sizeof(header));
    if (memcmp(header.magic, SIDC_APICORE_MAGIC, sizeof(header.magic)) != 0) {
        error(c, "Old or incompatible apis.bin: rebuild SDK EBI-only SBAPI04 metadata");
        return 0;
    }
    if (
        header.base != 0x2001f000u || header.call_count == 0 ||
        header.call_count > SIDC_API_CALLS || header.constant_count > SIDC_API_CONSTANTS)
        goto invalid;

    unsigned max_params = SIDC_API_PARAMS;
    unsigned call_size = sizeof(SidcApiCall);
    unsigned calls = header.call_count * call_size;
    unsigned constants = header.constant_count * sizeof(SidcApiConstant);
    unsigned message_at = sizeof(header) + calls + constants;
    if (payload != message_at + sizeof(SidcApiMessage))
        goto invalid;
    memcpy(c->api_constants, api_file + sizeof(header) + calls, constants);
    {
        memcpy(&c->message, api_file + message_at, sizeof(c->message));
        unsigned size = c->message.size;
        if (size < 4 || size > 4096 || (size & 3u) || c->message.reserved)
            goto invalid;
        for (unsigned i = 0; i < SIDC_MSG_FIELDS; ++i) {
            unsigned width = i == SIDC_MSG_WINHND ? 1u : 4u;
            unsigned offset = c->message.offsets[i];
            if ((offset & (width - 1u)) || offset > size - width)
                goto invalid;
        }
    }
    unsigned last_param = SIDC_API_WORD_BUFFER;
    for (unsigned i = 0; i < header.call_count; ++i) {
        SidcApiCall *call = &c->api_calls[i];
        memcpy(call, api_file + sizeof(header) + i * call_size, call_size);
        if (!valid_api_name(call->name, SIDC_API_NAME, 1) || call->arity > max_params ||
            (call->result != SIDC_API_U8 && call->result != SIDC_API_U32 &&
             call->result != SIDC_API_VOID && call->result != SIDC_API_S8 &&
             call->result != SIDC_API_S32))
            goto invalid;
        /* A direct API_Root.hwl call is two dereferences rather than the
         * normal three. 0xffff is allowed ONLY as the final hop sentinel. */
        if (call->offsets[0] == 0xffffu || call->offsets[1] == 0xffffu)
            goto invalid;
        for (unsigned j = 0; j < SIDC_API_OFFSETS; ++j)
            if (call->offsets[j] != 0xffffu &&
                (call->offsets[j] > 4092 || (call->offsets[j] & 3u)))
                goto invalid;
        for (unsigned j = 0; j < call->arity; ++j)
            if (call->params[j] < SIDC_API_NULL || call->params[j] > last_param ||
                call->params[j] == SIDC_API_VOID )
                goto invalid;
        for (unsigned j = call->arity; j < SIDC_API_PARAMS; ++j)
            if (call->params[j] != 0)
                goto invalid;
    }
    for (unsigned i = 0; i < header.constant_count; ++i)
        if (!valid_api_name(c->api_constants[i].name, SIDC_API_CONST_NAME, 0))
            goto invalid;
    c->api = header;
    return 1;
invalid:
    error(c, "Invalid SDK API core file");
    return 0;
}

static const SidcApiCall *find_api_call(const Compiler *c, Token name)
{
    for (unsigned i = 0; i < c->api.call_count; ++i)
        if (name_is(name, c->api_calls[i].name))
            return &c->api_calls[i];
    return NULL;
}

static const SidcApiConstant *find_api_constant(const Compiler *c, Token name)
{
    for (unsigned i = 0; i < c->api.constant_count; ++i)
        if (name_is(name, c->api_constants[i].name))
            return &c->api_constants[i];
    return NULL;
}

static uint32_t branch(Compiler *c)
{
    uint32_t at = c->pc;
    emit(c, 0);
    emit(c, 0);
    return at;
}

static void patch_branch(Compiler *c, uint32_t at, uint32_t target, int link)
{
    if (c->diagnostic.message)
        return;
    /* Thumb-2 B.W or BL. Even the expanded 64 KiB image fits the branch range. */
    uint32_t d = target - at - 4u;
    uint32_t s = (d >> 24) & 1u;
    uint32_t j1 = ((~(d >> 23)) ^ s) & 1u;
    uint32_t j2 = ((~(d >> 22)) ^ s) & 1u;
    put16(at, (uint16_t)(0xf000 | (s << 10) | ((d >> 12) & 0x3ff)));
    put16(at + 2, (uint16_t)((link ? 0xd000 : 0x9000) | (j1 << 13) |
                             (j2 << 11) | ((d >> 1) & 0x7ff)));
}

static uint32_t branch_on_value(Compiler *c, int when_nonzero)
{
    emit(c, 0x2800);                                           /* cmp r0, #0 */
    emit(c, when_nonzero ? 0xd001 : 0xd101);                    /* skip b.w */
    return branch(c);
}

static void boolean(Compiler *c, unsigned condition)
{
    emit(c, (uint16_t)(0xd001 | (condition << 8)));             /* b<c> true */
    emit(c, 0x2000);                                           /* movs r0, #0 */
    emit(c, 0xe000);                                           /* b done */
    emit(c, 0x2001);                                           /* true: movs r0, #1 */
}

static int find_function(const Compiler *c, Token name)
{
    int external = -1;
    for (unsigned i = 0; i < c->function_count; ++i) {
        const Function *f = &c->functions[i];
        if (!same_name(f->name, name))
            continue;
        if (f->is_static) {
            if (f->unit == c->file_index)
                return (int)i;
        } else {
            external = (int)i;
        }
    }
    return external;
}

static int find_declaration(const Compiler *c, Token name, int is_static)
{
    for (unsigned i = 0; i < c->function_count; ++i) {
        const Function *f = &c->functions[i];
        if (!same_name(f->name, name))
            continue;
        if (f->is_static == (uint8_t)is_static &&
            (!is_static || f->unit == c->file_index))
            return (int)i;
    }
    return -1;
}

static int find_global(const Compiler *c, Token name)
{
    for (unsigned i = 0; i < c->global_count; ++i)
        if (c->globals[i].unit == c->file_index && same_name(c->globals[i].name, name))
            return (int)i;
    return -1;
}

static int find_local(const Compiler *c, Token name)
{
    for (unsigned i = c->local_count; i != 0; --i)
        if (same_name(c->locals[i - 1].name, name))
            return (int)(i - 1);
    return -1;
}

static int expression(Compiler *c, int minimum, int requirement);

/* Records are word-aligned, because this subset currently supports only
   integer and embedded-record members. A struct sums member sizes; a union
   overlays all members, reserving the largest member size. */
#define RECORD_INT 255u

static int find_alias(const Compiler *c, Token name)
{
    for (unsigned i = 0; i < c->alias_count; ++i)
        if (c->aliases[i].unit == c->file_index &&
            same_name(c->aliases[i].name, name)) return (int)i;
    return -1;
}

static int find_record(const Compiler *c, Token name, int is_union)
{
    for (unsigned i = 0; i < c->struct_count; ++i)
        if (!c->structs[i].anonymous && same_name(c->structs[i].name, name) &&
            c->structs[i].is_union == (uint8_t)is_union) return (int)i;
    return -1;
}

static int records_equal(const StructDef *a, const StructDef *b)
{
    if (a->count != b->count || a->size_words != b->size_words ||
        a->is_union != b->is_union) return 0;
    for (unsigned i = 0; i < a->count; ++i)
        if (!same_name(a->fields[i].name, b->fields[i].name) ||
            a->fields[i].record_id != b->fields[i].record_id ||
            a->fields[i].is_pointer != b->fields[i].is_pointer ||
            a->fields[i].offset_words != b->fields[i].offset_words) return 0;
    return 1;
}

/* Consumes either 'struct Tag', 'union Tag', or a known local typedef.
   Anonymous records appear only in a typedef definition, not as a type name. */
static int record_type(Compiler *c, unsigned *id)
{
    int is_union;
    if (c->token.kind == TOK_STRUCT || c->token.kind == TOK_UNION) {
        is_union = c->token.kind == TOK_UNION;
        advance(c);
        Token tag = c->token;
        if (!expect(c, TOK_NAME, "Expected struct or union tag")) return 0;
        int index = find_record(c, tag, is_union);
        if (index < 0) error_at(c, tag, is_union ? "Unknown union type; define it first" : "Unknown struct type; define it first");
        else *id = (unsigned)index;
        return 1;
    }
    if (c->token.kind == TOK_NAME) {
        int alias = find_alias(c, c->token);
        if (alias >= 0 && c->aliases[alias].record_id != RECORD_INT) {
            *id = c->aliases[alias].record_id;
            advance(c);
            return 1;
        }
    }
    return 0;
}

static int is_record_type(const Compiler *c)
{
    if (c->token.kind == TOK_STRUCT || c->token.kind == TOK_UNION) return 1;
    if (c->token.kind == TOK_NAME) {
        int alias = find_alias(c, c->token);
        return alias >= 0 && c->aliases[alias].record_id != RECORD_INT;
    }
    return 0;
}

/* Parses {...}, but intentionally leaves the trailing declarator/semicolon to
   the caller. An optional name is available for a tagged definition. */
static int enum_declaration(Compiler *c);

static int record_definition(Compiler *c, Token tag, int is_union,
                             int anonymous, Token alias_name)
{
    if (!expect(c, '{', "Expected '{' after record type")) return -1;
    int existing = anonymous ? -1 : find_record(c, tag, is_union);
    if (!anonymous && find_record(c, tag, !is_union) >= 0) {
        error_at(c, tag, "Struct and union tags share a name namespace");
        return -1;
    }
    /* Reserve a tagged record before its body: struct Node *next can then
       refer to this incomplete type. An embedded Node (without *) cannot. */
    int reserved = -1;
    if (existing < 0 && !anonymous) {
        if (c->struct_count == STRUCT_LIMIT) {
            error_at(c, tag, "Too many struct/union definitions"); return -1;
        }
        reserved = (int)c->struct_count++;
        c->structs[reserved] = (StructDef){.name=tag,.is_union=(uint8_t)is_union,
                                          .unit=c->file_index};
    }
    StructDef value = {.name = anonymous ? alias_name : tag,
                       .is_union = (uint8_t)is_union,
                       .anonymous = (uint8_t)anonymous,
                       .complete=1,.unit = c->file_index};
    while (!c->diagnostic.message && c->token.kind != '}' && c->token.kind != TOK_END) {
        if (value.count == STRUCT_FIELDS) {
            error(c, "Record exceeds sixteen fields"); return -1;
        }
        unsigned child = RECORD_INT;
        if (accept(c, TOK_INT)) {
            child = RECORD_INT;
        } else if (c->token.kind == TOK_NAME && find_alias(c, c->token) >= 0 &&
                   c->aliases[find_alias(c, c->token)].record_id == RECORD_INT) {
            advance(c);
        } else if (c->token.kind == TOK_ENUM && enum_declaration(c)) {
            child = RECORD_INT;
        } else if (!record_type(c, &child)) {
            error(c, is_union ? "Only int/enum fields or previously defined records are supported inside union" : "Only int/enum fields or previously defined records are supported inside struct");
            return -1;
        }
        int pointer = accept(c, '*');
        if (!pointer && child != RECORD_INT && !c->structs[child].complete) {
            error(c, "An incomplete record must be used through a pointer");
            return -1;
        }
        Token field = c->token;
        if (!expect(c, TOK_NAME, "Expected record field name") ||
            !expect(c, ';', "Expected ';' after record field")) return -1;
        for (unsigned i = 0; i < value.count; ++i)
            if (same_name(value.fields[i].name, field)) {
                error_at(c, field, is_union ? "Duplicate union field" : "Duplicate struct field");
                return -1;
            }
        unsigned words = pointer || child == RECORD_INT ? 1u : c->structs[child].size_words;
        if (!words || words > 65535u - value.size_words) {
            error_at(c, field, "Record size exceeds supported memory range");
            return -1;
        }
        value.fields[value.count++] = (RecordField){.name=field,
                    .record_id=(uint8_t)child,.is_pointer=(uint8_t)pointer,
                    .offset_words=(uint16_t)(is_union ? 0 : value.size_words)};
        if (is_union) {
            if (words > value.size_words) value.size_words = (uint16_t)words;
        } else {
            value.size_words = (uint16_t)(value.size_words + words);
        }
    }
    if (!expect(c, '}', "Expected '}' after record fields")) return -1;
    if (anonymous) value.name = c->token;
    if (!value.count) {
        error_at(c, tag, "Empty records are outside this C subset"); return -1;
    }
    if (anonymous) {
        for (unsigned i = 0; i < c->struct_count; ++i)
            if (c->structs[i].anonymous &&
                c->structs[i].unit != c->file_index &&
                same_name(c->structs[i].name, value.name) &&
                records_equal(&value, &c->structs[i])) {
                existing = (int)i; break;
            }
    }
    if (existing >= 0) {
        if (!records_equal(&value, &c->structs[existing])) {
            error_at(c, tag, is_union ? "Conflicting union definition" : "Conflicting struct definition");
            return -1;
        }
        return existing;
    }
    if (reserved >= 0) {
        c->structs[reserved] = value;
        return reserved;
    }
    if (c->struct_count == STRUCT_LIMIT) {
        error_at(c, tag, "Too many struct/union definitions"); return -1;
    }
    unsigned next = c->struct_count++;
    c->structs[next] = value;
    return (int)next;
}

/* Enum declarations use compile-time integer expressions, not emitted ARM code. */
static int enum_precedence(int op)
{
    switch (op) {
    case '|': return 1;
    case '^': return 2;
    case '&': return 3;
    case TOK_SHL: case TOK_SHR: return 4;
    case '+': case '-': return 5;
    case '*': case '/': case '%': return 6;
    default: return 0;
    }
}

static int64_t enum_expression(Compiler *c, int minimum, unsigned depth)
{
    if (depth > 24u) { error(c, "Enum expression nesting too deep"); return 0; }
    int op = c->token.kind;
    int64_t value = 0;
    if (op == '+' || op == '-' || op == '~') {
        advance(c);
        value = enum_expression(c, 7, depth + 1u);
        if (op == '-') value = -value;
        if (op == '~') value = ~value;
    } else if (accept(c, '(')) {
        value = enum_expression(c, 1, depth + 1u);
        expect(c, ')', "Expected ')' in enum constant expression");
    } else if (c->token.kind == TOK_NUMBER || c->token.kind == TOK_UNSIGNED_NUMBER) {
        value = c->token.kind == TOK_NUMBER ? (int64_t)(int32_t)c->token.number : (int64_t)c->token.number;
        advance(c);
    } else {
        error(c, "Enum initializer requires an integer constant expression");
        return 0;
    }
    while (!c->diagnostic.message && enum_precedence(c->token.kind) >= minimum) {
        op = c->token.kind;
        int prec = enum_precedence(op);
        advance(c);
        int64_t rhs = enum_expression(c, prec + 1, depth + 1u);
        if (c->diagnostic.message) return 0;
        if ((op == '/' || op == '%') && !rhs) {
            error(c, "Division by zero in enum initializer"); return 0;
        }
        if ((op == '/' || op == '%') && value == INT32_MIN && rhs == -1) {
            error(c, "Enum division overflows signed int"); return 0;
        }
        if ((op == TOK_SHL || op == TOK_SHR) && (rhs < 0 || rhs > 31)) {
            error(c, "Enum shift count must be between 0 and 31"); return 0;
        }
        switch (op) {
        case '+': value += rhs; break;
        case '-': value -= rhs; break;
        case '*': value *= rhs; break;
        case '/': value = (int32_t)value / (int32_t)rhs; break;
        case '%': value = (int32_t)value % (int32_t)rhs; break;
        case '&': value &= rhs; break;
        case '|': value |= rhs; break;
        case '^': value ^= rhs; break;
        case TOK_SHL: value = (uint32_t)value << rhs; break;
        case TOK_SHR: value = (uint32_t)value >> rhs; break;
        }
    }
    return value;
}

/* Consume enum Tag { ... } or an already declared enum Tag.
   Enum objects use the existing 32-bit int representation. */
static int enum_declaration(Compiler *c)
{
    if (!expect(c, TOK_ENUM, "Expected enum")) return 0;
    Token tag = {0};
    if (c->token.kind == TOK_NAME) {
        tag = c->token;
        advance(c);
    }
    if (accept(c, '{')) {
        if (tag.kind == TOK_NAME) {
            for (unsigned i = 0; i < c->enum_tag_count; ++i)
                if (c->enum_tags[i].unit == c->file_index &&
                    same_name(c->enum_tags[i].name, tag)) {
                    error_at(c, tag, "Duplicate enum definition"); return 0;
                }
            if (c->enum_tag_count == ENUM_TAG_LIMIT) {
                error(c, "Too many enum tags"); return 0;
            }
            c->enum_tags[c->enum_tag_count++] = (EnumTag){tag,c->file_index};
        }
        int64_t current = -1;
        unsigned members = 0;
        while (!c->diagnostic.message && c->token.kind != '}' && c->token.kind != TOK_END) {
            Token member = c->token;
            if (!expect(c, TOK_NAME, "Expected enum constant name")) return 0;
            if (enum_constant_lookup(c, member.text, member.length) >= 0 ||
                find_alias(c, member) >= 0) {
                error_at(c, member, "Duplicate enum constant"); return 0;
            }
            if (accept(c, '=')) current = enum_expression(c, 1, 0);
            else ++current;
            if (current < INT32_MIN || current > INT32_MAX) {
                error_at(c, member, "Enum constant exceeds signed 32-bit range"); return 0;
            }
            if (c->enum_constant_count == ENUM_CONSTANT_LIMIT) {
                error_at(c, member, "Too many enum constants"); return 0;
            }
            c->enum_constants[c->enum_constant_count++] =
                (EnumConstant){member, (uint32_t)current, c->file_index};
            ++members;
            if (!accept(c, ',')) break;
        }
        if (!members) { error(c, "Empty enum definitions are unsupported"); return 0; }
        return expect(c, '}', "Expected '}' after enum constants");
    }
    if (tag.kind != TOK_NAME) { error(c, "Expected enum tag or definition"); return 0; }
    for (unsigned i = 0; i < c->enum_tag_count; ++i)
        if (c->enum_tags[i].unit == c->file_index &&
            same_name(c->enum_tags[i].name, tag)) return 1;
    error_at(c, tag, "Unknown enum tag");
    return 0;
}

static void register_alias(Compiler *c, Token name, unsigned record_id)
{
    if (find_global(c, name) >= 0 || find_function(c, name) >= 0) {
        error_at(c, name, "Typedef conflicts with a file-scope declaration");
        return;
    }
    int existing = find_alias(c, name);
    if (existing >= 0) {
        if (c->aliases[existing].record_id != record_id)
            error_at(c, name, "Conflicting typedef declaration");
        return;
    }
    if (c->alias_count == TYPEDEF_LIMIT) {
        error_at(c, name, "Too many typedef declarations");
        return;
    }
    c->aliases[c->alias_count++] = (TypeAlias){.name=name,
                           .record_id=(uint8_t)record_id,.unit=c->file_index};
}

static void typedef_declaration(Compiler *c)
{
    unsigned id = RECORD_INT;
    int defining = 0, is_union = 0;
    Token tag = c->token;
    if (accept(c, TOK_INT)) {
        id = RECORD_INT;
    } else if (c->token.kind == TOK_ENUM) {
        if (!enum_declaration(c)) return;
        id = RECORD_INT;
    } else if (c->token.kind == TOK_STRUCT || c->token.kind == TOK_UNION) {
        is_union = c->token.kind == TOK_UNION;
        advance(c);
        tag = c->token;
        if (c->token.kind == TOK_NAME) advance(c);
        if (c->token.kind == '{') {
            /* Anonymous layouts are keyed by the alias token, which follows
               the closing brace. The parser defers name installation. */
            defining = 1;
        } else if (tag.kind == TOK_NAME) {
            int found = find_record(c, tag, is_union);
            if (found < 0) error_at(c, tag, "Unknown record in typedef");
            else id = (unsigned)found;
        } else {
            error(c, "Expected struct/union definition or tag");
        }
    } else if (c->token.kind == TOK_NAME) {
        int alias = find_alias(c, c->token);
        if (alias < 0) error(c, "Unknown type in typedef");
        else { id = c->aliases[alias].record_id; advance(c); }
    } else {
        error(c, "Expected type after typedef");
    }
    if (c->diagnostic.message) return;
    if (defining) {
        /* For anonymous records, the alias token is discovered after parsing
           the fields; the temporary definition first uses an empty tag. */
        int rec = record_definition(c, tag, is_union, tag.kind != TOK_NAME, tag);
        if (rec < 0 || c->diagnostic.message) return;
        id = (unsigned)rec;
    }
    Token alias_name = c->token;
    if (!expect(c, TOK_NAME, "Expected typedef alias") ||
        !expect(c, ';', "Expected ';' after typedef")) return;
    register_alias(c, alias_name, id);
}

/* sizeof operands are inspected as types, not evaluated as expressions:
   sizeof(i++) must never increment i or emit its code. */
static uint32_t sizeof_operand(Compiler *c)
{
    int parenthesized = accept(c, '(');
    int type_operand = 0;
    unsigned bytes = 0;
    if (accept(c, TOK_INT)) {
        type_operand = 1;
        bytes = 4u;
        accept(c, '*');
    } else if (accept(c, TOK_VOID)) {
        type_operand = 1;
        if (!accept(c, '*')) {
            error(c, "sizeof(void) is outside this C subset");
            return 0u;
        }
        bytes = 4u;
    } else if (c->token.kind == TOK_ENUM) {
        type_operand = 1;
        if (!enum_declaration(c)) return 0u;
        bytes = 4u;
    } else if (accept(c, TOK_CHAR)) {
        type_operand = 1;
        bytes = accept(c, '*') ? 4u : 1u;
    } else if (c->token.kind == TOK_NAME && name_is(c->token, "uint8_t")) {
        type_operand = 1;
        advance(c);
        bytes = accept(c, '*') ? 4u : 1u;
    } else if (c->token.kind == TOK_NAME && name_is(c->token, "int32_t")) {
        type_operand = 1;
        advance(c);
        bytes = 4u;
        accept(c, '*');
    } else if (is_record_type(c)) {
        type_operand = 1;
        unsigned rec = 0;
        if (!record_type(c, &rec)) return 0u;
        bytes = accept(c, '*') ? 4u : c->structs[rec].size_words * 4u;
    } else if (c->token.kind == TOK_NUMBER ||
               c->token.kind == TOK_UNSIGNED_NUMBER) {
        advance(c);
        bytes = 4u;
    } else {
        int dereference = accept(c, '*');
        Token name = c->token;
        if (!expect(c, TOK_NAME, "sizeof needs a type or declared variable")) return 0u;
        int local = find_local(c, name);
        int global = local < 0 ? find_global(c, name) : -1;
        if (local < 0 && global < 0) {
            error_at(c, name, "sizeof refers to an unknown variable or type");
            return 0u;
        }
        int kind = local >= 0 ? c->locals[local].type : c->globals[global].type;
        unsigned rec = local >= 0 ? c->locals[local].struct_id : c->globals[global].struct_id;
        unsigned count = local >= 0 ? c->locals[local].array_count : c->globals[global].array_count;
        int is_record = kind == LOCAL_STRUCT || kind == GLOBAL_STRUCT ||
                        kind == LOCAL_STRUCT_ARRAY || kind == GLOBAL_STRUCT_ARRAY ||
                        kind == LOCAL_STRUCT_POINTER;
        int is_array = kind == LOCAL_INT_ARRAY || kind == GLOBAL_INT_ARRAY ||
                       kind == GLOBAL_BYTE_ARRAY || kind == LOCAL_STRUCT_ARRAY ||
                       kind == GLOBAL_STRUCT_ARRAY;
        int is_pointer = kind == LOCAL_INT_POINTER || kind == LOCAL_STRUCT_POINTER ||
                         kind == LOCAL_FUNCTION_POINTER || kind == LOCAL_STRUCT_DOUBLE_POINTER ||
                         kind == LOCAL_INT_DOUBLE_POINTER || kind == LOCAL_ARGV ||
                         kind == LOCAL_POINTER || kind == LOCAL_MESSAGE;
        bytes = kind == GLOBAL_BYTE_ARRAY || kind == LOCAL_WINDOW ? 1u :
                is_record && !is_pointer ? c->structs[rec].size_words * 4u : 4u;
        if (dereference) {
            if (!is_pointer) { error_at(c, name, "sizeof * needs a pointer"); return 0u; }
            bytes = kind == LOCAL_STRUCT_POINTER ? c->structs[rec].size_words * 4u : 4u;
            is_record = kind == LOCAL_STRUCT_POINTER;
            is_array = 0;
            is_pointer = 0;
        } else if (is_array) {
            bytes *= count;
        }
        if (accept(c, '[')) {
            if (!is_array && !is_pointer) {
                error_at(c, name, "sizeof indexing needs an array or pointer"); return 0u;
            }
            unsigned depth = 1;
            while (depth && c->token.kind != TOK_END && !c->diagnostic.message) {
                if (c->token.kind == '[') ++depth;
                if (c->token.kind == ']') --depth;
                advance(c);
            }
            if (depth) { error(c, "Unterminated sizeof index"); return 0u; }
            bytes = is_record ? c->structs[rec].size_words * 4u : 4u;
            is_array = 0;
        }
        while (c->token.kind == '.' || c->token.kind == TOK_ARROW) {
            int member_op = c->token.kind;
            if (member_op == TOK_ARROW && !is_pointer) {
                error_at(c, name, "sizeof -> needs a record pointer"); return 0u;
            }
            if (member_op == '.' && is_pointer) {
                error_at(c, name, "sizeof pointer member needs ->"); return 0u;
            }
            advance(c);
            if (!is_record) { error_at(c, name, "sizeof member needs a struct or union"); return 0u; }
            Token field = c->token;
            if (!expect(c, TOK_NAME, "Expected member after sizeof .")) return 0u;
            const StructDef *def = &c->structs[rec];
            unsigned i = 0;
            while (i < def->count && !same_name(def->fields[i].name, field)) ++i;
            if (i == def->count) { error_at(c, field, "Unknown member in sizeof"); return 0u; }
            rec = def->fields[i].record_id;
            is_record = rec != RECORD_INT;
            is_pointer = def->fields[i].is_pointer;
            bytes = is_pointer ? 4u : is_record ? c->structs[rec].size_words * 4u : 4u;
        }
    }
    if (type_operand && accept(c, '[')) {
        Token bound = c->token;
        if ((bound.kind != TOK_NUMBER && bound.kind != TOK_UNSIGNED_NUMBER) ||
            bound.number == 0 || bound.number > UINT32_MAX / bytes) {
            error_at(c, bound, "sizeof type array needs a positive constant bound");
            return 0u;
        }
        bytes *= bound.number;
        advance(c);
        if (!expect(c, ']', "Expected ']' in sizeof array type")) return 0u;
    }
    if (parenthesized && !expect(c, ')', "Expected ')' after sizeof operand")) return 0u;
    return bytes;
}

/* r0 contains the base address of a local/global struct or struct pointer. */
/* r0 contains the address of a record. Pointer members use one word, and
   -> follows the pointer stored in that word rather than embedding its target. */
static int call(Compiler *c, Token name);
static void record_value_address(Compiler *c, unsigned id);
static int null_argument(Compiler *c);
static void struct_pointer_value(Compiler *c, unsigned struct_id);
static void struct_double_pointer_value(Compiler *c, unsigned struct_id);
static void int_double_pointer_value(Compiler *c);
static int struct_member(Compiler *c, unsigned struct_id, int allow_store, int address_only)
{
    Token member = c->token;
    if (!expect(c, TOK_NAME, "Expected record member name")) return VALUE_INT;
    const StructDef *def = &c->structs[struct_id];
    unsigned field = 0;
    while (field < def->count && !same_name(def->fields[field].name, member)) ++field;
    if (field == def->count) {
        error_at(c, member, def->is_union ? "Unknown union field" : "Unknown struct field");
        return VALUE_INT;
    }
    RecordField f = def->fields[field];
    if (f.offset_words) {
        load_constant(c, 1, f.offset_words * 4u);
        emit(c, 0x1840);                    /* add address + member offset */
    }
    if (f.is_pointer) {
        if (accept(c, TOK_ARROW)) {
            if (f.record_id == RECORD_INT) {
                error_at(c, member, "int * field has no record members");
                return VALUE_INT;
            }
            emit(c, 0x6800);                /* follow linked record pointer */
            return struct_member(c, f.record_id, allow_store, address_only);
        }
        if (c->token.kind == '.') {
            error_at(c, member, "Use -> to follow a pointer field");
            return VALUE_POINTER;
        }
        if (address_only) {
            error_at(c, member, "Pointer-to-pointer member addresses are not supported");
            return VALUE_POINTER;
        }
        if (allow_store && accept(c, '=')) {
            emit(c, 0xb403);               /* preserve target member address */
            if (f.record_id == RECORD_INT)
                expression(c, 1, REQUIRE_INT_POINTER);
            else
                struct_pointer_value(c, f.record_id);
            emit(c, 0xbc06);               /* target address -> r1 */
            emit(c, 0x6008);               /* str r0, [r1] */
            return VALUE_VOID;
        }
        if (c->token.kind == TOK_ADD_ASSIGN || c->token.kind == TOK_SUB_ASSIGN ||
            c->token.kind == TOK_BAND_ASSIGN || c->token.kind == TOK_BOR_ASSIGN ||
            c->token.kind == TOK_BXOR_ASSIGN || c->token.kind == TOK_SHL_ASSIGN ||
            c->token.kind == TOK_SHR_ASSIGN)
            error_at(c, member, "Record pointer fields only support =");
        emit(c, 0x6800);                   /* ldr pointer from field */
        c->value_record_id = f.record_id;
        return f.record_id == RECORD_INT ? VALUE_INT_POINTER : VALUE_POINTER;
    }
    if (f.record_id != RECORD_INT) {
        if (accept(c, '.'))
            return struct_member(c, f.record_id, allow_store, address_only);
        if (address_only) return VALUE_POINTER;
        error_at(c, member, "Use .field to access an embedded record");
        return VALUE_POINTER;
    }
    if (c->token.kind == '.' || c->token.kind == TOK_ARROW) {
        error(c, "Integer record fields have no nested members");
        return VALUE_INT;
    }
    if (address_only) return VALUE_INT_POINTER;
    if (allow_store && (c->token.kind == '=' ||
                        c->token.kind == TOK_ADD_ASSIGN || c->token.kind == TOK_SUB_ASSIGN ||
                        c->token.kind == TOK_BAND_ASSIGN || c->token.kind == TOK_BOR_ASSIGN ||
                        c->token.kind == TOK_BXOR_ASSIGN || c->token.kind == TOK_SHL_ASSIGN ||
                        c->token.kind == TOK_SHR_ASSIGN)) {
        int op = c->token.kind;
        advance(c);
        emit(c, 0xb403);
        if (op != '=') {
            emit(c, 0x6800);
            emit(c, 0xb403);
        }
        expression(c, 1, REQUIRE_INTEGER);
        if (op != '=') {
            emit(c, 0xbc06);
            switch (op) {
            case TOK_ADD_ASSIGN: emit(c, 0x1808); break;
            case TOK_SUB_ASSIGN: emit(c, 0x1a08); break;
            case TOK_BAND_ASSIGN: emit(c, 0x4008); break;
            case TOK_BOR_ASSIGN: emit(c, 0x4308); break;
            case TOK_BXOR_ASSIGN: emit(c, 0x4048); break;
            case TOK_SHL_ASSIGN: case TOK_SHR_ASSIGN:
                emit(c, 0x4602); emit(c, 0x4608);
                emit(c, op == TOK_SHL_ASSIGN ? 0x4090 : 0x4110);
                break;
            }
        }
        emit(c, 0xbc06);
        emit(c, 0x6008);
        return VALUE_VOID;
    }
    emit(c, 0x6800);
    return VALUE_INT;
}

/* r0 holds the array base. A struct element occupies count * 4 bytes.
   The computed address may be used with .member or passed as a struct *. */
static int struct_array_element(Compiler *c, unsigned struct_id, int allow_store,
                                int address_only)
{
    if (!expect(c, '[', "Expected '[' after struct array")) return VALUE_POINTER;
    emit(c, 0xb403);                       /* save base {r0,r1} */
    expression(c, 1, REQUIRE_INTEGER);
    if (!expect(c, ']', "Expected ']' after struct array index")) return VALUE_POINTER;
    emit(c, 0xbc06);                       /* base -> r1 */
    load_constant(c, 2, c->structs[struct_id].size_words * 4u);
    emit(c, 0x4350);                       /* muls r0, r2 */
    emit(c, 0x1840);                       /* adds r0, r0, r1 */
    if (address_only) return VALUE_POINTER;
    if (accept(c, '.')) return struct_member(c, struct_id, allow_store, 0);
    error(c, "Use array[index].field to access a struct element");
    return VALUE_POINTER;
}

/* Resolve a by-value nested member address. r0 holds the outer record.
   This deliberately accepts only paths that end at a compatible record,
   not an int or a structurally similar but distinct record type. */
static void record_member_pointer(Compiler *c, unsigned root, unsigned expected)
{
    for (;;) {
        Token field = c->token;
        if (!expect(c, TOK_NAME, "Expected nested record member")) return;
        const StructDef *def = &c->structs[root];
        unsigned idx = 0;
        while (idx < def->count && !same_name(field, def->fields[idx].name)) ++idx;
        if (idx == def->count) {
            error_at(c, field, "Unknown struct/union field");
            return;
        }
        RecordField member = def->fields[idx];
        if (member.offset_words) {
            load_constant(c, 1, member.offset_words * 4u);
            emit(c, 0x1840);
        }
        if (member.record_id == RECORD_INT || member.is_pointer) {
            error_at(c, field, "Nested member is not an embedded record");
            return;
        }
        if (!accept(c, '.')) {
            if (member.record_id != expected)
                error_at(c, field, "Struct pointer requires the same struct type");
            return;
        }
        root = member.record_id;
    }
}

/* Accept compatible record pointers, addresses of records or nested
   by-value members, arrays (decaying to pointers), and NULL. */
static void struct_pointer_value(Compiler *c, unsigned struct_id)
{
    if (c->token.kind == TOK_NAME && c->lookahead.kind == '(') {
        Token name = c->token;
        advance(c);
        if (!expect(c, '(', "Expected '(' after function name")) return;
        int returned = call(c, name);
        if (!((name_is(name, "malloc") || name_is(name, "sidbox_malloc")) &&
              returned == VALUE_POINTER) &&
            !(returned == VALUE_POINTER && c->value_record_id == struct_id))
            error_at(c, name, "Expected matching record pointer return type");
        return;
    }
    if (accept(c, '*')) {
        Token name = c->token;
        int slot = name.kind == TOK_NAME ? find_local(c, name) : -1;
        if (slot < 0 || c->locals[slot].type != LOCAL_STRUCT_DOUBLE_POINTER ||
            c->locals[slot].struct_id != struct_id) {
            error_at(c, name, "Expected a matching record ** for dereference");
            return;
        }
        advance(c);
        load_local(c, (unsigned)slot, 0);
        emit(c, 0x6800);
        return;
    }
    int address = accept(c, '&');
    if (c->token.kind == TOK_NAME) {
        Token name = c->token;
        int local = find_local(c, name);
        int global = local < 0 ? find_global(c, name) : -1;
        if (!address && name_is(name, "NULL") && local < 0 && global < 0) {
            advance(c); constant(c, 0); return;
        }
        advance(c);
        uint8_t kind = local >= 0 ? c->locals[local].type :
                       global >= 0 ? c->globals[global].type : LOCAL_PADDING;
        unsigned root = local >= 0 ? c->locals[local].struct_id :
                        global >= 0 ? c->globals[global].struct_id : RECORD_INT;
        if (kind == LOCAL_STRUCT || kind == GLOBAL_STRUCT) {
            if (local >= 0) local_address(c, (unsigned)local);
            else { emit_address(c, ADDRESS_GLOBAL, (unsigned)global); emit(c, 0x4608); }
            if (accept(c, '.')) {
                /* A by-value nested record needs &, but a pointer field
                   already holds an address and must not have &. */
                if (address) record_member_pointer(c, root, struct_id);
                else {
                    int type = struct_member(c, root, 0, 0);
                    if (type != VALUE_POINTER || c->value_record_id != struct_id)
                        error_at(c, name, "Struct pointer requires the same struct type");
                }
            } else if (!address || root != struct_id)
                error_at(c, name, "Struct pointer requires the same struct type");
        } else if (kind == LOCAL_STRUCT_ARRAY || kind == GLOBAL_STRUCT_ARRAY) {
            if (local >= 0) local_address(c, (unsigned)local);
            else { emit_address(c, ADDRESS_GLOBAL, (unsigned)global); emit(c, 0x4608); }
            if (c->token.kind == '[') {
                if (address) {
                    struct_array_element(c, root, 0, 1);
                    if (accept(c, '.')) record_member_pointer(c, root, struct_id);
                    else if (root != struct_id)
                        error_at(c, name, "Struct pointer requires the same struct type");
                } else {
                    struct_array_element(c, root, 0, 1);
                    if (accept(c, '.')) {
                        int type = struct_member(c, root, 0, 0);
                        if (type != VALUE_POINTER || c->value_record_id != struct_id)
                            error_at(c, name, "Struct pointer requires the same struct type");
                    } else {
                        error_at(c, name, "Use &array[index] when passing an element");
                    }
                }
            } else if (address || root != struct_id) {
                error_at(c, name, "Struct pointer requires the same struct type");
            }
        } else if (kind == LOCAL_STRUCT_POINTER && local >= 0) {
            load_local(c, (unsigned)local, 0);
            if (accept(c, TOK_ARROW)) {
                if (address) {
                    record_member_pointer(c, root, struct_id);
                } else {
                    int type = struct_member(c, root, 0, 0);
                    if (type != VALUE_POINTER || c->value_record_id != struct_id)
                        error_at(c, name, "Struct pointer requires the same struct type");
                }
            } else if (address || root != struct_id) {
                error_at(c, name, "Struct pointer requires the same struct type");
            }
        } else {
            error_at(c, name, "Struct pointer requires the same struct type");
        }
    } else if (!address && (c->token.kind == TOK_NUMBER ||
                            c->token.kind == TOK_UNSIGNED_NUMBER) &&
               c->token.number == 0) {
        advance(c); constant(c, 0);
    } else {
        error(c, "Expected matching struct pointer, &struct, array, or NULL");
    }
}

/* r0 addresses a record; walk to a typed pointer field and leave its
   *storage address* in r0, suitable for a T **. */
static void int_double_pointer_value(Compiler *c)
{
    if (null_argument(c)) return;
    int address = accept(c, '&');
    Token name = c->token;
    if (!expect(c, TOK_NAME, "Expected int ** or &int pointer")) return;
    int slot = find_local(c, name);
    if (slot < 0) { error_at(c, name, "Expected declared int pointer"); return; }
    if (address && c->locals[slot].type == LOCAL_INT_POINTER)
        local_address(c, (unsigned)slot);
    else if (!address && c->locals[slot].type == LOCAL_INT_DOUBLE_POINTER)
        load_local(c, (unsigned)slot, 0);
    else error_at(c, name, "int ** requires &int_pointer or compatible int **");
}

static void record_pointer_field_address(Compiler *c, unsigned rec, unsigned expected)
{
    for (;;) {
        Token field = c->token;
        if (!expect(c, TOK_NAME, "Expected pointer member name")) return;
        const StructDef *def = &c->structs[rec];
        unsigned index = 0;
        while (index < def->count && !same_name(field, def->fields[index].name)) ++index;
        if (index == def->count) {
            error_at(c, field, "Unknown record field in pointer address"); return;
        }
        RecordField f = def->fields[index];
        if (f.offset_words) {
            load_constant(c, 1, f.offset_words * 4u);
            emit(c, 0x1840);
        }
        if (accept(c, TOK_ARROW)) {
            if (!f.is_pointer || f.record_id == RECORD_INT) {
                error_at(c, field, "-> needs a record pointer field"); return;
            }
            emit(c, 0x6800);
            rec = f.record_id;
        } else if (accept(c, '.')) {
            if (f.is_pointer || f.record_id == RECORD_INT) {
                error_at(c, field, ". needs an embedded record field"); return;
            }
            rec = f.record_id;
        } else {
            if (!f.is_pointer || f.record_id != expected)
                error_at(c, field, "&member needs a matching record pointer field");
            return;
        }
    }
}

/* Two-level typed record pointers: accepts &Node*, existing Node**, or NULL. */
static void struct_double_pointer_value(Compiler *c, unsigned struct_id)
{
    if (null_argument(c)) return;
    int address = accept(c, '&');
    Token name = c->token;
    if (!expect(c, TOK_NAME, "Expected matching record ** or &record pointer")) return;
    int slot = find_local(c, name);
    if (slot < 0) {
        error_at(c, name, "Struct ** requires a declared pointer or record");
        return;
    }
    unsigned root = c->locals[slot].struct_id;
    if (address && c->locals[slot].type == LOCAL_STRUCT_POINTER) {
        if (accept(c, TOK_ARROW)) {
            load_local(c, (unsigned)slot, 0);
            record_pointer_field_address(c, root, struct_id);
        } else if (root == struct_id) local_address(c, (unsigned)slot);
        else error_at(c, name, "Struct ** requires the same record type");
    } else if (address && c->locals[slot].type == LOCAL_STRUCT) {
        if (!expect(c, '.', "Use &record.pointer_member")) return;
        local_address(c, (unsigned)slot);
        record_pointer_field_address(c, root, struct_id);
    } else if (!address && c->locals[slot].type == LOCAL_STRUCT_DOUBLE_POINTER && root == struct_id)
        load_local(c, (unsigned)slot, 0);
    else
        error_at(c, name, "Struct ** requires &record_pointer or a matching record **");
}

/* r0=source, r1=destination. Copy complete 32-bit record words. */
static void copy_record(Compiler *c, unsigned words)
{
    for (unsigned i = 0; i < words; ++i) {
        unsigned offset = i * 4u;
        emit(c, 0xf8d0); emit(c, (uint16_t)(0x2000u | offset)); /* ldr.w r2,[r0,#offset] */
        emit(c, 0xf8c1); emit(c, (uint16_t)(0x2000u | offset)); /* str.w r2,[r1,#offset] */
    }
}

/* Evaluate a record lvalue or record-returning call to its address in r0.
   The callee gets a private copy; no address aliases are passed by value. */
static void record_value_address(Compiler *c, unsigned expected)
{
    Token name = c->token;
    if (!expect(c, TOK_NAME, "Expected record value or record-returning call")) return;
    if (accept(c, '(')) {
        int type = call(c, name);
        if (type != VALUE_RECORD || c->value_record_id != expected)
            error_at(c, name, "Record value requires a matching record-returning function");
        return;
    }
    int local = find_local(c, name);
    int global = local < 0 ? find_global(c, name) : -1;
    if (local < 0 && global < 0) {
        error_at(c, name, "Expected a declared record value"); return;
    }
    unsigned type = local >= 0 ? c->locals[local].type : c->globals[global].type;
    unsigned rec = local >= 0 ? c->locals[local].struct_id : c->globals[global].struct_id;
    if (type != LOCAL_STRUCT && type != GLOBAL_STRUCT &&
        type != LOCAL_STRUCT_ARRAY && type != GLOBAL_STRUCT_ARRAY) {
        error_at(c, name, "Record value requires a struct or union object"); return;
    }
    if (local >= 0) local_address(c, (unsigned)local);
    else { emit_address(c, ADDRESS_GLOBAL, (unsigned)global); emit(c, 0x4608); }
    if (type == LOCAL_STRUCT_ARRAY || type == GLOBAL_STRUCT_ARRAY) {
        if (c->token.kind != '[') {
            error_at(c, name, "Use record_array[index] for a record value"); return;
        }
        struct_array_element(c, rec, 0, 1);
    }
    if (accept(c, '.')) record_member_pointer(c, rec, expected);
    else if (rec != expected) error_at(c, name, "Record value requires the same type");
}

static unsigned reserve_record_slots(Compiler *c, unsigned id)
{
    unsigned words = c->structs[id].size_words;
    if (!words || words > LOCAL_LIMIT - c->local_count) {
        error(c, "Record temporaries exceed the 64-word local limit"); return 0;
    }
    unsigned slot = c->local_count;
    for (unsigned i = 0; i < words; ++i)
        c->locals[c->local_count++] = (Local){.scope=(uint8_t)c->scope,
                                             .type=LOCAL_PADDING};
    if (c->local_count > c->local_peak) c->local_peak = c->local_count;
    return slot;
}

static unsigned add_local(Compiler *c, Token name, uint8_t type)
{
    int slot = find_local(c, name);
    if (slot >= 0 && c->locals[slot].scope == c->scope) {
        error_at(c, name, "Duplicate local declaration");
        return 0;
    }
    if (c->local_count == LOCAL_LIMIT) {
        error_at(c, name, "Too many active local variables");
        return 0;
    }
    unsigned next = c->local_count++;
    c->locals[next] = (Local){.name = name, .scope = (uint8_t)c->scope, .type = type};
    if (c->local_count > c->local_peak)
        c->local_peak = c->local_count;
    return next;
}

static unsigned escape_byte(Compiler *c, Token token, const char **p, const char *end)
{
    unsigned ch = (unsigned char)*(*p)++;
    switch (ch) {
    case 'a': return '\a';
    case 'b': return '\b';
    case 'f': return '\f';
    case 'n': return '\n';
    case 'r': return '\r';
    case 't': return '\t';
    case 'v': return '\v';
    case '\\': case '"': case '\'': case '?': return ch;
    case 'x': {
        unsigned value = 0;
        if (*p == end || hex_digit((unsigned char)**p) == 16u)
            break;
        while (*p != end && hex_digit((unsigned char)**p) != 16u) {
            value = value * 16u + hex_digit((unsigned char)*(*p)++);
            if (value > 255u) {
                error_at(c, token, "Escape exceeds one byte");
                return 0;
            }
        }
        return value;
    }
    default:
        if (ch >= '0' && ch <= '7') {
            unsigned value = ch - '0';
            for (unsigned i = 0; i < 2 && *p != end && **p >= '0' && **p <= '7'; ++i)
                value = value * 8u + (unsigned char)*(*p)++ - '0';
            if (value <= 255u)
                return value;
        }
        break;
    }
    error_at(c, token, "Invalid or unsupported escape");
    return 0;
}

static void string_argument(Compiler *c)
{
    Token first = c->token;
    /* SDK text calls can also read a persistent, NUL-terminated byte array.
       This is for live labels; the caller owns the buffer and its lifetime. */
    if (first.kind == TOK_NAME) {
        int index = find_global(c, first);
        if (index >= 0 && find_local(c, first) < 0 &&
            c->globals[index].type == GLOBAL_BYTE_ARRAY) {
            advance(c);
            emit_address(c, ADDRESS_GLOBAL, (unsigned)index);
            emit(c, 0x4608);                    /* mov r0, r1 */
            return;
        }
    }
    if (first.kind != TOK_STRING) {
        error(c, "Expected a string literal or static uint8_t array");
        return;
    }
    if (c->string_bytes == STRING_LIMIT) {
        error(c, "String data exceeds 16 KiB");
        return;
    }
    unsigned start = c->string_bytes;
    do {
        Token token = c->token;
        const char *p = token.text;
        const char *end = p + token.length;
        while (p != end) {
            if (c->string_bytes + 1u >= STRING_LIMIT) {
                error_at(c, token, "String data exceeds 16 KiB");
                return;
            }
            unsigned ch = (unsigned char)*p++;
            if (ch == '\\')
                ch = escape_byte(c, token, &p, end);
            if (c->diagnostic.message)
                return;
            c->strings[c->string_bytes++] = (uint8_t)ch;
        }
        advance(c);
    } while (c->token.kind == TOK_STRING && !c->diagnostic.message);
    c->strings[c->string_bytes++] = 0;

    emit_address(c, ADDRESS_STRING, start);
}

/* Returns the C value type. Expression results are in r0. */
static int expression(Compiler *c, int minimum, int requirement);

static int null_argument(Compiler *c)
{
    Token token = c->token;
    if (((token.kind == TOK_NUMBER || token.kind == TOK_UNSIGNED_NUMBER) && token.number == 0) ||
        (token.kind == TOK_NAME && name_is(token, "NULL") &&
         find_local(c, token) < 0 && find_global(c, token) < 0)) {
        advance(c);
        constant(c, 0);
        return 1;
    }
    return 0;
}

static void callback_argument(Compiler *c, uint8_t kind)
{
    if (null_argument(c))
        return;
    accept(c, '&');
    Token name = c->token;
    int index = name.kind == TOK_NAME ? find_function(c, name) : -1;
    if (index < 0 || find_local(c, name) >= 0) {
        error_at(c, name, "Expected a declared callback function or NULL");
        return;
    }
    static const uint8_t gadget_params[] = {
        LOCAL_POINTER, LOCAL_S32, LOCAL_S32, LOCAL_S32, LOCAL_S32
    };
    static const uint8_t timer_params[] = {LOCAL_POINTER};
    static const uint8_t window_params[] = {LOCAL_WINDOW, LOCAL_MESSAGE};
    const uint8_t *types;
    unsigned arity;
    unsigned return_type = RETURN_VOID;
    const char *signature;
    switch (kind) {
    case SIDC_API_GADGET_CALLBACK:
        types = gadget_params;
        arity = sizeof(gadget_params);
        signature = "Gadget callback needs void (void *, int32_t, int32_t, int32_t, int32_t)";
        break;
    case SIDC_API_WINDOW_CALLBACK:
        types = window_params;
        arity = sizeof(window_params);
        return_type = RETURN_WINDOW;
        signature = "Window callback needs CGWindowProcRes (CGWindow, const CGMessage_t *)";
        break;
    default:
        types = timer_params;
        arity = sizeof(timer_params);
        signature = "Timer callback needs void (void *)";
        break;
    }
    const Function *fn = &c->functions[index];
    if (fn->return_type != return_type || fn->arity != arity || memcmp(fn->param_types, types, arity)) {
        error_at(c, name, signature);
        return;
    }
    advance(c);
    emit_address(c, ADDRESS_FUNCTION, (unsigned)index);
}

/* Marshal saved pairs into the AAPCS register and stack argument area. */
static unsigned prepare_call(Compiler *c, unsigned arity)
{
    unsigned overflow = arity > 4 ? arity - 4u : 0u;
    unsigned stack_words = (overflow + 1u) & ~1u;
    if (stack_words)
        emit(c, (uint16_t)(0xb080 | stack_words));             /* sub sp, #space */
    for (unsigned i = 4; i < arity; ++i) {
        unsigned word = stack_words + 2u * (arity - 1u - i);
        emit(c, (uint16_t)(0x9800 | word));                    /* ldr r0, [sp, #word*4] */
        emit(c, (uint16_t)(0x9000 | (i - 4u)));                /* str r0, [sp, #arg*4] */
    }
    for (unsigned i = 0; i < arity && i < 4; ++i) {
        unsigned word = stack_words + 2u * (arity - 1u - i);
        emit(c, (uint16_t)(0x9800 | (i << 8) | word));         /* ldr Ri, [sp, #word*4] */
    }
    if (stack_words)
        return stack_words + 2u * arity;
    if (arity)
        emit(c, (uint16_t)(0xb000 | (2u * arity)));            /* discard saved pairs */
    return 0;
}

static void api_call(Compiler *c, const SidcApiCall *api)
{
    unsigned arity = api->arity;
    for (unsigned i = 0; i < arity && !c->diagnostic.message; ++i) {
        if (i != 0)
            expect(c, ',', "Expected ',' between SDK arguments");
        switch (api->params[i]) {
        case SIDC_API_STRING:
            string_argument(c);
            break;
        case SIDC_API_NULL:
            if (!null_argument(c))
                error(c, "This pointer argument supports NULL");
            break;
        case SIDC_API_GADGET_CALLBACK:
        case SIDC_API_TIMER_CALLBACK:
        case SIDC_API_WINDOW_CALLBACK:
            callback_argument(c, api->params[i]);
            break;
        case SIDC_API_WINDOW_REF: {
            if (null_argument(c))
                break;
            const char *message = "Pass the address of a file-scope static CGWindow or NULL";
            if (!expect(c, '&', message))
                break;
            Token name = c->token;
            int index = name.kind == TOK_NAME ? find_global(c, name) : -1;
            if (index < 0 || find_local(c, name) >= 0 || c->globals[index].type != LOCAL_WINDOW) {
                error_at(c, name, message);
                break;
            }
            advance(c);
            emit_address(c, ADDRESS_GLOBAL, (unsigned)index);
            emit(c, 0x4608);                                  /* mov r0, r1 */
            break;
        }
        case SIDC_API_WORD_BUFFER: {
            if (null_argument(c)) {
                error(c, "Palette pointer cannot be NULL");
                break;
            }
            Token name = c->token;
            int index = name.kind == TOK_NAME ? find_global(c, name) : -1;
            if (index < 0 || find_local(c, name) >= 0 ||
                c->globals[index].type != GLOBAL_INT_ARRAY ||
                c->globals[index].array_count < 256u) {
                error_at(c, name, "Pass a file-scope static int[256] palette array");
                break;
            }
            advance(c);
            emit_address(c, ADDRESS_GLOBAL, (unsigned)index);
            emit(c, 0x4608);                                  /* mov r0, r1 */
            break;
        }
        case SIDC_API_BYTE_BUFFER: {
            if (null_argument(c))
                break;
            Token name = c->token;
            int index = name.kind == TOK_NAME ? find_global(c, name) : -1;
            if (index < 0 || find_local(c, name) >= 0 || c->globals[index].type != GLOBAL_BYTE_ARRAY) {
                error_at(c, name, "Pass a file-scope static uint8_t array or NULL");
                break;
            }
            advance(c);
            emit_address(c, ADDRESS_GLOBAL, (unsigned)index);
            emit(c, 0x4608);                                  /* mov r0, r1 */
            break;
        }
        default:
            expression(c, 1, REQUIRE_INTEGER);
            switch (api->params[i]) {
            case SIDC_API_S16: emit(c, 0xb200); break;          /* sxth r0, r0 */
            case SIDC_API_U16: emit(c, 0xb280); break;          /* uxth r0, r0 */
            case SIDC_API_S8:  emit(c, 0xb240); break;          /* sxtb r0, r0 */
            case SIDC_API_U8:  emit(c, 0xb2c0); break;          /* uxtb r0, r0 */
            }
            break;
        }
        emit(c, 0xb403);                                       /* push {r0, r1} */
    }
    if (!expect(c, ')', "Wrong SDK argument count or missing ')'"))
        return;

    unsigned words = prepare_call(c, arity);
    load_constant(c, 12, c->api.base);
    for (unsigned i = 0; i < SIDC_API_OFFSETS; ++i) {
        if (api->offsets[i] == 0xffffu) break; /* two-hop EBI call */
        emit(c, 0xf8dc);                                      /* ldr.w ip, [ip, #offset] */
        emit(c, (uint16_t)(0xc000 | api->offsets[i]));
    }
    emit(c, 0x47e0);                                          /* blx ip */
    if (words)
        emit(c, (uint16_t)(0xb000 | words));
    if (api->result == SIDC_API_U8)
        emit(c, 0xb2c0);                                      /* promote uint8_t to int */
    else if (api->result == SIDC_API_S8)
        emit(c, 0xb240);                                      /* promote int8_t to int */
}

/* Lazily reserve an applet-owned zero-filled arena in the output image. */
static unsigned reserve_heap(Compiler *c)
{
    if (c->heap_used) return c->heap_global_index;
    if (c->global_count >= GLOBAL_LIMIT || c->array_bytes > BYTE_ARRAY_LIMIT - PRIVATE_ARENA_BYTES) {
        error(c, "Unable to reserve 16 KiB of applet heap RAM");
        return 0;
    }
    c->array_bytes = (c->array_bytes + 7u) & ~7u;
    unsigned index = c->global_count++;
    c->globals[index] = (Global){.offset=c->array_bytes,.type=GLOBAL_BYTE_ARRAY,
          .array_count=PRIVATE_ARENA_BYTES,.unit=c->file_index};
    c->array_bytes += PRIVATE_ARENA_BYTES;
    c->heap_global_index = (uint16_t)index;
    c->heap_used = 1;
    return index;
}

static int heap_call(Compiler *c, Token name)
{
    int allocating = name_is(name, "malloc") || name_is(name, "sidbox_malloc");
    if (allocating) expression(c, 1, REQUIRE_INTEGER);
    else expression(c, 1, REQUIRE_SCALAR);
    if (!expect(c, ')', "malloc/free requires one argument")) return VALUE_VOID;
    unsigned pool = reserve_heap(c);
    if (c->diagnostic.message) return VALUE_VOID;
    emit_address(c, ADDRESS_GLOBAL, pool); /* r1 = private arena base */
    if (c->call_count == CALL_LIMIT) { error(c, "Too many function calls"); return VALUE_VOID; }
    c->calls[c->call_count++] = (Reference){branch(c), (uint16_t)(allocating ? 0xfffeu : 0xfffdu)};
    return allocating ? VALUE_POINTER : VALUE_VOID;
}

static int call(Compiler *c, Token name)
{
    if (name_is(name, "malloc") || name_is(name, "free") ||
        name_is(name, "sidbox_malloc") || name_is(name, "sidbox_free"))
        return heap_call(c, name);
    const SidcApiCall *api = find_api_call(c, name);
    if (api) {
        api_call(c, api);
        if (api->result == SIDC_API_VOID)
            return VALUE_VOID;
        return api->result == SIDC_API_U32 ? VALUE_UNSIGNED : VALUE_INT;
    }
    int index = find_function(c, name);
    if (index < 0 || find_local(c, name) >= 0 || find_global(c, name) >= 0) {
        error_at(c, name, "Call needs a visible function declaration");
        return 0;
    }
    const Function *fn = &c->functions[index];
    if (fn->param_types[1] == LOCAL_ARGV) {
        error_at(c, name, "The Sidbox loader supplies main's arguments");
        return 0;
    }
    unsigned words = 0;
    unsigned extra = fn->return_type == RETURN_RECORD ? 1u : 0u;
    unsigned returned_slot = 0;
    if (extra) {
        returned_slot = reserve_record_slots(c, fn->return_struct_id);
        if (c->diagnostic.message) return VALUE_VOID;
        local_address(c, returned_slot);
        emit(c, 0xb403);                                    /* hidden return address */
    }
    if (fn->builtin == BUILTIN_MESSAGE) {
        string_argument(c);
    } else {
        for (unsigned i = 0; i < fn->arity && !c->diagnostic.message; ++i) {
            if (i != 0)
                expect(c, ',', "Expected ',' between arguments");
            uint8_t type = fn->param_types[i];
            if (type == LOCAL_STRUCT) {
                record_value_address(c, fn->param_struct_ids[i]);
            } else if (type == LOCAL_STRUCT_POINTER) {
                struct_pointer_value(c, fn->param_struct_ids[i]);
            } else if (type == LOCAL_STRUCT_DOUBLE_POINTER) {
                struct_double_pointer_value(c, fn->param_struct_ids[i]);
            } else if (type == LOCAL_INT_DOUBLE_POINTER) {
                int_double_pointer_value(c);
            } else if (type == LOCAL_INT_POINTER) {
                expression(c, 1, REQUIRE_INT_POINTER);
            } else if (type == LOCAL_POINTER || type == LOCAL_MESSAGE) {
                if (!null_argument(c)) {
                    int slot = c->token.kind == TOK_NAME ? find_local(c, c->token) : -1;
                    if (slot < 0 || c->locals[slot].type != type) {
                        error(c, "Expected a matching pointer parameter or NULL");
                        return VALUE_VOID;
                    }
                    advance(c);
                    load_local(c, (unsigned)slot, 0);
                }
            } else {
                expression(c, 1, REQUIRE_INTEGER);
            }
            emit(c, 0xb403);                                   /* push {r0, r1} */
        }
        words = prepare_call(c, fn->arity + extra);
    }
    if (!expect(c, ')', "Wrong argument count or missing ')'"))
        return 0;
    if (c->call_count == CALL_LIMIT) {
        error_at(c, name, "Too many function calls");
        return 0;
    }
    c->calls[c->call_count++] = (Reference){branch(c), (uint16_t)index};
    if (words)
        emit(c, (uint16_t)(0xb000 | words));
    if (fn->return_type == RETURN_RECORD) {
        local_address(c, returned_slot); /* return an address to caller-owned storage */
        c->value_record_id = fn->return_struct_id;
        return VALUE_RECORD;
    }
    if (fn->return_type == RETURN_STRUCT_POINTER) {
        c->value_record_id = fn->return_struct_id;
        return VALUE_POINTER;
    }
    return fn->return_type == RETURN_VOID ? VALUE_VOID :
        fn->return_type == RETURN_INT_POINTER ? VALUE_INT_POINTER : VALUE_INT;
}

/* Current general function pointers have a checked int/void return and up to
   five int parameters. Keep the type in the declaration, never cast pointers. */
static int matching_callback(const FunctionPointerSignature *sig, const Function *fn)
{
    return !fn->builtin && fn->arity == sig->arity &&
           fn->return_type == sig->return_type &&
           memcmp(fn->param_types, sig->params, sig->arity) == 0;
}

/* Consume a function address, 0/NULL, or a compatible local function pointer.
   The chosen function must have been declared before its address is taken. */
static void function_pointer_value(Compiler *c, const FunctionPointerSignature *sig)
{
    if (null_argument(c)) return;
    accept(c, '&');
    Token name = c->token;
    if (!expect(c, TOK_NAME, "Expected a function name or compatible function pointer")) return;
    int slot = find_local(c, name);
    if (slot >= 0) {
        Local *local = &c->locals[slot];
        if (local->type != LOCAL_FUNCTION_POINTER ||
            local->callback.arity != sig->arity ||
            local->callback.return_type != sig->return_type ||
            memcmp(local->callback.params, sig->params, sig->arity)) {
            error_at(c, name, "Incompatible function pointer signature");
            return;
        }
        load_local(c, (unsigned)slot, 0);
        return;
    }
    int fn = find_function(c, name);
    if (fn < 0 || find_global(c, name) >= 0 ||
        !matching_callback(sig, &c->functions[fn])) {
        error_at(c, name, "Incompatible or undeclared function pointer target");
        return;
    }
    emit_address(c, ADDRESS_FUNCTION, (unsigned)fn);
}

/* The pointer itself lives in our r7 stack frame. Fetch it into ip only
   after AAPCS argument setup, so nested argument calls cannot overwrite it. */
static int indirect_call(Compiler *c, unsigned slot)
{
    const FunctionPointerSignature *sig = &c->locals[slot].callback;
    unsigned arity = sig->arity;
    for (unsigned i = 0; i < arity && !c->diagnostic.message; ++i) {
        if (i) expect(c, ',', "Expected ',' between function-pointer arguments");
        expression(c, 1, REQUIRE_INTEGER);
        emit(c, 0xb403);                                     /* push {r0,r1} */
    }
    unsigned words = prepare_call(c, arity);
    if (!expect(c, ')', "Wrong indirect-call argument count or missing ')'")) return VALUE_INT;
    emit(c, 0xf8d7);                                        /* ldr.w ip, [r7,#slot*4] */
    emit(c, (uint16_t)(0xc000u | (slot * 4u)));
    emit(c, 0x47e0);                                        /* blx ip */
    if (words) emit(c, (uint16_t)(0xb000 | words));
    return sig->return_type == RETURN_VOID ? VALUE_VOID : VALUE_INT;
}

static int message_member(Compiler *c)
{
    Token member = c->token;
    if (!expect(c, TOK_NAME, "Expected a CGMessage_t member name"))
        return VALUE_INT;
    static const char *const fields[SIDC_MSG_FIELDS] = {
        [SIDC_MSG_MTYPE] = "mtype", [SIDC_MSG_WINHND] = "winhnd",
        [SIDC_MSG_GADGET] = "gadget", [SIDC_MSG_EVENT] = "eventClass",
        [SIDC_MSG_A] = "a", [SIDC_MSG_B] = "b", [SIDC_MSG_C] = "c", [SIDC_MSG_D] = "d"
    };
    for (unsigned i = 0; i < SIDC_MSG_FIELDS; ++i) {
        if (name_is(member, fields[i])) {
            emit(c, i == SIDC_MSG_WINHND ? 0xf890 : 0xf8d0);   /* ldr[b].w r0, [r0, #offset] */
            emit(c, c->message.offsets[i]);
            return i == SIDC_MSG_MTYPE || i == SIDC_MSG_GADGET || i == SIDC_MSG_EVENT
                ? VALUE_UNSIGNED : VALUE_INT;
        }
    }
    error_at(c, member, "Unknown CGMessage_t member");
    return VALUE_INT;
}

static int byte_array_element(Compiler *c, unsigned index, int allow_store)
{
    if (!expect(c, '[', "Expected an index after the byte array name"))
        return VALUE_INT;
    expression(c, 1, REQUIRE_INTEGER);
    if (!expect(c, ']', "Expected ']' after byte array index"))
        return VALUE_INT;
    emit_address(c, ADDRESS_GLOBAL, index);
    int op = c->token.kind;
    int assigning = op == '=' || op == TOK_ADD_ASSIGN || op == TOK_SUB_ASSIGN ||
        op == TOK_BAND_ASSIGN || op == TOK_BOR_ASSIGN || op == TOK_BXOR_ASSIGN ||
        op == TOK_SHL_ASSIGN || op == TOK_SHR_ASSIGN;
    if (!allow_store || !assigning) {
        emit(c, 0x5c08);                                     /* ldrb r0,[r1,r0] */
        return VALUE_INT;
    }
    advance(c);
    emit(c, 0x1808);                                          /* address of byte */
    emit(c, 0xb403);                                          /* preserve address */
    if (op != '=') {
        emit(c, 0x7800);                                      /* ldrb r0,[r0] */
        emit(c, 0xb403);                                      /* preserve old byte */
    }
    expression(c, 1, REQUIRE_INTEGER);
    if (op != '=') {
        emit(c, 0xbc06);                                      /* old value in r1 */
        switch (op) {
        case TOK_ADD_ASSIGN: emit(c, 0x1808); break;
        case TOK_SUB_ASSIGN: emit(c, 0x1a08); break;
        case TOK_BAND_ASSIGN: emit(c, 0x4008); break;
        case TOK_BOR_ASSIGN: emit(c, 0x4308); break;
        case TOK_BXOR_ASSIGN: emit(c, 0x4048); break;
        case TOK_SHL_ASSIGN: case TOK_SHR_ASSIGN:
            emit(c, 0x4602); emit(c, 0x4608);
            emit(c, op == TOK_SHL_ASSIGN ? 0x4090 : 0x4110);
            break;
        }
    }
    emit(c, 0xbc06);                                          /* address in r1 */
    emit(c, 0x7008);                                          /* strb r0,[r1] */
    return VALUE_VOID;
}


/* r0 holds an int* base. Indexing is scaled by sizeof(int) == 4. */
static int int_pointer_element(Compiler *c, int allow_store, int address_only)
{
    if (!expect(c, '[', "Expected '[' after array or pointer")) return VALUE_INT;
    emit(c, 0xb403);                                         /* preserve base {r0,r1} */
    expression(c, 1, REQUIRE_INTEGER);
    if (!expect(c, ']', "Expected ']' after array index")) return VALUE_INT;
    emit(c, 0xbc06);                                         /* base -> r1 */
    emit(c, 0x0080);                                         /* lsls r0,r0,#2 */
    emit(c, 0x1808);                                         /* adds r0,r1,r0 */
    if (address_only) return VALUE_INT_POINTER;
    int op = c->token.kind;
    int assigning = op == '=' || op == TOK_ADD_ASSIGN || op == TOK_SUB_ASSIGN ||
        op == TOK_BAND_ASSIGN || op == TOK_BOR_ASSIGN || op == TOK_BXOR_ASSIGN ||
        op == TOK_SHL_ASSIGN || op == TOK_SHR_ASSIGN;
    if (!allow_store || !assigning) {
        emit(c, 0x6800);                                     /* ldr r0,[r0] */
        return VALUE_INT;
    }
    advance(c);
    emit(c, 0xb403);                                         /* preserve address */
    if (op != '=') {
        emit(c, 0x6800);                                     /* load old int */
        emit(c, 0xb403);
    }
    expression(c, 1, REQUIRE_INTEGER);
    if (op != '=') {
        emit(c, 0xbc06);                                     /* old int in r1 */
        switch (op) {
        case TOK_ADD_ASSIGN: emit(c, 0x1808); break;
        case TOK_SUB_ASSIGN: emit(c, 0x1a08); break;
        case TOK_BAND_ASSIGN: emit(c, 0x4008); break;
        case TOK_BOR_ASSIGN: emit(c, 0x4308); break;
        case TOK_BXOR_ASSIGN: emit(c, 0x4048); break;
        case TOK_SHL_ASSIGN: case TOK_SHR_ASSIGN:
            emit(c, 0x4602); emit(c, 0x4608);
            emit(c, op == TOK_SHL_ASSIGN ? 0x4090 : 0x4110);
            break;
        }
    }
    emit(c, 0xbc06);                                         /* destination in r1 */
    emit(c, 0x6008);                                         /* str r0,[r1] */
    return VALUE_VOID;
}

static int increment_scalar(Compiler *c, Token name, int op, int postfix)
{
    int slot = find_local(c, name);
    int global = slot < 0 ? find_global(c, name) : -1;
    int type = slot >= 0 ? c->locals[slot].type
                         : global >= 0 ? c->globals[global].type : -1;
    if ((slot >= 0 && c->locals[slot].is_const) ||
        (global >= 0 && c->globals[global].is_const)) {
        error_at(c, name, "Cannot increment or decrement const variable");
        return VALUE_INT;
    }
    if (type < 0 || type == GLOBAL_BYTE_ARRAY || type == GLOBAL_INT_ARRAY ||
        type == LOCAL_INT_ARRAY || type == LOCAL_PADDING || type == LOCAL_POINTER ||
        type == LOCAL_ARGV || type == LOCAL_MESSAGE || type == LOCAL_FUNCTION_POINTER ||
        type == LOCAL_STRUCT || type == LOCAL_STRUCT_POINTER || type == GLOBAL_STRUCT ||
        type == LOCAL_STRUCT_ARRAY || type == GLOBAL_STRUCT_ARRAY ||
        type == LOCAL_INT_DOUBLE_POINTER || type == LOCAL_STRUCT_DOUBLE_POINTER) {
        error_at(c, name, "Increment/decrement needs a scalar variable");
        return VALUE_INT;
    }
    if (slot >= 0) load_local(c, (unsigned)slot, 0);
    else {
        emit_address(c, ADDRESS_GLOBAL, (unsigned)global);
        emit(c, 0x6808);                                        /* ldr r0, [r1] */
    }
    if (postfix) emit(c, 0xb401);                               /* push {r0}: old value */
    emit(c, op == TOK_INC ? (type == LOCAL_INT_POINTER ? 0x3004 : 0x3001)
                            : (type == LOCAL_INT_POINTER ? 0x3804 : 0x3801));
    if (type == LOCAL_WINDOW) emit(c, 0xb2c0);                 /* uxtb */
    if (slot >= 0) store_local(c, (unsigned)slot, 0);
    else {
        emit_address(c, ADDRESS_GLOBAL, (unsigned)global);
        emit(c, 0x6008);                                        /* str r0, [r1] */
    }
    if (postfix) emit(c, 0xbc01);                               /* pop {r0}: old value */
    return type == LOCAL_INT_POINTER ? VALUE_INT_POINTER :
           type == LOCAL_GADGET ? VALUE_UNSIGNED : VALUE_INT;
}

static int unary(Compiler *c, int allow_store)
{
    Token token = c->token;
    int type = VALUE_INT;
    if (c->diagnostic.message)
        return 0;
    if (++c->nesting > NESTING_LIMIT) {
        error(c, "Expression or block nesting is too deep");
    } else if (accept(c, TOK_SIZEOF)) {
        constant(c, sizeof_operand(c));
        type = VALUE_UNSIGNED;
    } else if (accept(c, TOK_NUMBER) || accept(c, TOK_UNSIGNED_NUMBER)) {
        constant(c, token.number);
        type = token.kind == TOK_UNSIGNED_NUMBER ? VALUE_UNSIGNED : VALUE_INT;
    } else if (accept(c, TOK_INC) || accept(c, TOK_DEC)) {
        int op = token.kind;
        Token name = c->token;
        if (!expect(c, TOK_NAME, "Expected variable after ++ or --")) {
            --c->nesting;
            return VALUE_INT;
        }
        type = increment_scalar(c, name, op, 0);
    } else if (accept(c, TOK_NAME)) {
        if (name_is(token, "API") && c->token.kind == '.') {
            /* Follow only the actual SDK EBI chain: API.gfx->hgfx->lcdwait().
             * No synthesised SBOS_ aliases and no arbitrary pointer calls. */
            char path[SIDC_API_NAME];
            unsigned n = 3;
            memcpy(path, "API", n);
            while (c->token.kind == '.' || c->token.kind == TOK_ARROW) {
                int separator = c->token.kind;
                advance(c);
                Token field = c->token;
                if (!expect(c, TOK_NAME, "Expected SDK EBI field name")) break;
                unsigned extra = separator == '.' ? 1u : 2u;
                if (n + extra + field.length >= sizeof(path)) {
                    error_at(c, field, "SDK EBI field path exceeds metadata name limit");
                    break;
                }
                if (separator == '.') path[n++] = '.';
                else {path[n++] = '-'; path[n++] = '>';}
                memcpy(path + n, field.text, field.length);
                n += field.length;
            }
            path[n] = 0;
            if (!c->diagnostic.message && expect(c, '(', "Expected call on SDK EBI field")) {
                Token full = token;
                full.text = path;
                full.length = n;
                const SidcApiCall *ebi = find_api_call(c, full);
                if (ebi) {
                    api_call(c, ebi);
                    type = ebi->result == SIDC_API_VOID ? VALUE_VOID :
                           ebi->result == SIDC_API_U32 ? VALUE_UNSIGNED : VALUE_INT;
                } else error_at(c, token, "Unknown SDK EBI field path");
            }
        } else if (accept(c, '(')) {
            int slot = find_local(c, token);
            type = slot >= 0 && c->locals[slot].type == LOCAL_FUNCTION_POINTER
                ? indirect_call(c, (unsigned)slot) : call(c, token);
            if (type == VALUE_INT_POINTER && c->token.kind == '[')
                type = int_pointer_element(c, allow_store, 0);
        } else if (c->token.kind == TOK_INC || c->token.kind == TOK_DEC) {
            int op = c->token.kind;
            advance(c);
            type = increment_scalar(c, token, op, 1);
        } else {
            int slot = find_local(c, token);
            const SidcApiConstant *value = find_api_constant(c, token);
            if (value)
                constant(c, value->value);
            else if (slot >= 0) {
                uint8_t local_type = c->locals[slot].type;
                if (local_type == LOCAL_POINTER || local_type == LOCAL_ARGV) {
                    error_at(c, token, "This SDK pointer cannot be used in an integer expression");
                } else if (local_type == LOCAL_FUNCTION_POINTER) {
                    load_local(c, (unsigned)slot, 0);
                    type = VALUE_POINTER;
                } else if (local_type == LOCAL_INT_DOUBLE_POINTER) {
                    load_local(c, (unsigned)slot, 0);
                    type = VALUE_INT_DOUBLE_POINTER;
                } else if (local_type == LOCAL_STRUCT_DOUBLE_POINTER) {
                    load_local(c, (unsigned)slot, 0);
                    c->value_record_id = c->locals[slot].struct_id;
                    type = VALUE_STRUCT_DOUBLE_POINTER;
                } else if (local_type == LOCAL_STRUCT || local_type == LOCAL_STRUCT_POINTER) {
                    if (local_type == LOCAL_STRUCT) {
                        local_address(c, (unsigned)slot);
                        if (accept(c, '.'))
                            type = struct_member(c, c->locals[slot].struct_id, allow_store, 0);
                        else error_at(c, token, "Use .field to access a struct");
                    } else {
                        load_local(c, (unsigned)slot, 0);
                        if (accept(c, TOK_ARROW))
                            type = struct_member(c, c->locals[slot].struct_id, allow_store, 0);
                        else if (c->token.kind == '[')
                            type = struct_array_element(c, c->locals[slot].struct_id, allow_store, 0);
                        else type = VALUE_POINTER;
                    }
                } else if (local_type == LOCAL_STRUCT_ARRAY) {
                    local_address(c, (unsigned)slot);
                    if (c->token.kind == '[')
                        type = struct_array_element(c, c->locals[slot].struct_id, allow_store, 0);
                    else error_at(c, token, "Use array[index].field for struct arrays");
                } else if (local_type == LOCAL_INT_ARRAY) {
                    local_address(c, (unsigned)slot);
                    type = c->token.kind == '[' ? int_pointer_element(c, allow_store, 0) : VALUE_INT_POINTER;
                } else {
                    load_local(c, (unsigned)slot, 0);
                    if (local_type == LOCAL_MESSAGE)
                        type = accept(c, TOK_ARROW) ? message_member(c) : VALUE_POINTER;
                    else if (local_type == LOCAL_INT_POINTER)
                        type = c->token.kind == '[' ? int_pointer_element(c, allow_store, 0) : VALUE_INT_POINTER;
                    else
                        type = local_type == LOCAL_GADGET ? VALUE_UNSIGNED : VALUE_INT;
                }
            } else {
                int global = find_global(c, token);
                if (global >= 0) {
                    uint8_t global_type = c->globals[global].type;
                    if (global_type == GLOBAL_BYTE_ARRAY) {
                        type = byte_array_element(c, (unsigned)global, allow_store);
                    } else if (global_type == GLOBAL_STRUCT) {
                        emit_address(c, ADDRESS_GLOBAL, (unsigned)global);
                        emit(c, 0x4608);                        /* mov r0, r1 */
                        if (accept(c, '.'))
                            type = struct_member(c, c->globals[global].struct_id, allow_store, 0);
                        else error_at(c, token, "Use .field to access a struct");
                    } else if (global_type == GLOBAL_STRUCT_ARRAY) {
                        emit_address(c, ADDRESS_GLOBAL, (unsigned)global);
                        emit(c, 0x4608);
                        if (c->token.kind == '[')
                            type = struct_array_element(c, c->globals[global].struct_id, allow_store, 0);
                        else error_at(c, token, "Use array[index].field for struct arrays");
                    } else if (global_type == GLOBAL_INT_ARRAY) {
                        emit_address(c, ADDRESS_GLOBAL, (unsigned)global);
                        emit(c, 0x4608);                       /* mov r0, r1 */
                        type = c->token.kind == '[' ? int_pointer_element(c, allow_store, 0) : VALUE_INT_POINTER;
                    } else {
                        emit_address(c, ADDRESS_GLOBAL, (unsigned)global);
                        emit(c, 0x6808);                       /* ldr r0, [r1] */
                        type = global_type == LOCAL_GADGET ? VALUE_UNSIGNED : VALUE_INT;
                    }
                } else if (name_is(token, "NULL")) {
                    constant(c, 0);
                    type = VALUE_POINTER;
                } else {
                    error_at(c, token, "Unknown variable or SDK constant");
                }
            }
        }
    } else if (accept(c, '&')) {
        Token name = c->token;
        if (!expect(c, TOK_NAME, "Expected variable after '&'")) {
            --c->nesting;
            return VALUE_INT;
        }
        int slot = find_local(c, name);
        int global = slot < 0 ? find_global(c, name) : -1;
        if ((slot >= 0 && c->locals[slot].is_const) ||
            (global >= 0 && c->globals[global].is_const)) {
            error_at(c, name, "Address-of const variable needs const pointer support");
        } else if (slot >= 0 && c->locals[slot].type == LOCAL_STRUCT) {
            local_address(c, (unsigned)slot);
            if (expect(c, '.', "Use &struct.field to take a member address"))
                type = struct_member(c, c->locals[slot].struct_id, 0, 1);
        } else if (global >= 0 && c->globals[global].type == GLOBAL_STRUCT) {
            emit_address(c, ADDRESS_GLOBAL, (unsigned)global);
            emit(c, 0x4608);
            if (expect(c, '.', "Use &struct.field to take a member address"))
                type = struct_member(c, c->globals[global].struct_id, 0, 1);
        } else if (slot >= 0 && c->locals[slot].type == LOCAL_STRUCT_POINTER) {
            local_address(c, (unsigned)slot);
            c->value_record_id = c->locals[slot].struct_id;
            type = VALUE_STRUCT_DOUBLE_POINTER;
        } else if (slot >= 0 && (c->locals[slot].type == LOCAL_INT ||
                          c->locals[slot].type == LOCAL_INT_ARRAY)) {
            local_address(c, (unsigned)slot);
            if (c->token.kind == '[' && c->locals[slot].type == LOCAL_INT_ARRAY)
                type = int_pointer_element(c, 0, 1);
            else if (c->locals[slot].type == LOCAL_INT_ARRAY)
                error_at(c, name, "Use &array[index], not pointer-to-array &array");
            else
                type = VALUE_INT_POINTER;
        } else if (global >= 0 && (c->globals[global].type == LOCAL_INT ||
                                    c->globals[global].type == GLOBAL_INT_ARRAY)) {
            emit_address(c, ADDRESS_GLOBAL, (unsigned)global);
            emit(c, 0x4608);                                   /* mov r0, r1 */
            if (c->token.kind == '[' && c->globals[global].type == GLOBAL_INT_ARRAY)
                type = int_pointer_element(c, 0, 1);
            else if (c->globals[global].type == GLOBAL_INT_ARRAY)
                error_at(c, name, "Use &array[index], not pointer-to-array &array");
            else
                type = VALUE_INT_POINTER;
        } else if (slot >= 0 && c->locals[slot].type == LOCAL_INT_POINTER) {
            if (c->token.kind == '[') {
                load_local(c, (unsigned)slot, 0);
                type = int_pointer_element(c, 0, 1);
            } else {
                local_address(c, (unsigned)slot);
                type = VALUE_INT_DOUBLE_POINTER;
            }
        } else {
            error_at(c, name, "Address-of needs an int variable or int array element");
        }
    } else if (accept(c, '*')) {
        type = unary(c, 0);
        if (type == VALUE_INT_DOUBLE_POINTER) {
            if (allow_store && accept(c, '=')) {
                emit(c, 0xb403);
                expression(c, 1, REQUIRE_INT_POINTER);
                emit(c, 0xbc06);
                emit(c, 0x6008);
                type = VALUE_VOID;
            } else {
                emit(c, 0x6800);
                type = VALUE_INT_POINTER;
            }
        } else if (type == VALUE_STRUCT_DOUBLE_POINTER) {
            unsigned rec = c->value_record_id;
            if (allow_store && accept(c, '=')) {
                emit(c, 0xb403);
                struct_pointer_value(c, rec);
                emit(c, 0xbc06);
                emit(c, 0x6008);
                type = VALUE_VOID;
            } else {
                emit(c, 0x6800);
                c->value_record_id = rec;
                type = VALUE_POINTER;
            }
        } else if (type != VALUE_INT_POINTER) {
            error_at(c, token, "Dereferencing requires int * or matching record **");
        } else if (allow_store && accept(c, '=')) {
            emit(c, 0xb403);                                   /* preserve address */
            expression(c, 1, REQUIRE_INTEGER);
            emit(c, 0xbc06);
            emit(c, 0x6008);                                   /* str r0, [r1] */
            type = VALUE_VOID;
        } else {
            emit(c, 0x6800);                                   /* ldr r0, [r0] */
            type = VALUE_INT;
        }
    } else if (accept(c, '(')) {
        int slot = c->token.kind == '*' && c->lookahead.kind == TOK_NAME
                 ? find_local(c, c->lookahead) : -1;
        if (slot >= 0 && c->locals[slot].type == LOCAL_FUNCTION_POINTER) {
            advance(c);                                     /* '*' */
            advance(c);                                     /* pointer name */
            if (expect(c, ')', "Expected ')' after (*function pointer)") &&
                expect(c, '(', "Expected '(' after (*function pointer)"))
                type = indirect_call(c, (unsigned)slot);
        } else {
            type = expression(c, 1, DISCARD_VALUE);
            expect(c, ')', "Expected ')'");
            if (type == VALUE_POINTER && accept(c, TOK_ARROW))
                type = struct_member(c, c->value_record_id, allow_store, 0);
            else if (type == VALUE_INT_POINTER && c->token.kind == '[')
                type = int_pointer_element(c, allow_store, 0);
        }
    } else if (accept(c, '+') || accept(c, '-') || accept(c, '!') || accept(c, '~')) {
        type = unary(c, 0);
        if (type == VALUE_VOID)
            error_at(c, token, "Expected an integer operand, got void");
        else if (type == VALUE_POINTER && token.kind != '!')
            error_at(c, token, "Expected an integer operand, got a pointer");
        else if (token.kind == '-')
            emit(c, 0x4240);                                   /* rsbs r0, r0, #0 */
        else if (token.kind == '~')
            emit(c, 0x43c0);                                   /* mvns r0, r0 */
        else if (token.kind == '!') {
            emit(c, 0x2800);
            boolean(c, 0);                                    /* eq */
            type = VALUE_INT;
        }
    } else {
        error(c, "Expected an integer expression");
    }
    --c->nesting;
    return type;
}

static int precedence(int op)
{
    switch (op) {
    case TOK_OR: return 1;
    case TOK_AND: return 2;
    case '|': return 3;
    case '^': return 4;
    case '&': return 5;
    case TOK_EQ: case TOK_NE: return 6;
    case '<': case '>': case TOK_LE: case TOK_GE: return 7;
    case TOK_SHL: case TOK_SHR: return 8;
    case '+': case '-': return 9;
    case '*': case '/': case '%': return 10;
    default: return 0;
    }
}

static int binary(Compiler *c, int op, int unsigned_word)
{
    switch (op) {
    case '+': emit(c, 0x1808); return unsigned_word;            /* adds r0, r1, r0 */
    case '-': emit(c, 0x1a08); return unsigned_word;            /* subs r0, r1, r0 */
    case '*': emit(c, 0x4348); return unsigned_word;            /* muls r0, r1 */
    case '&': emit(c, 0x4008); return unsigned_word;            /* ands r0, r1 */
    case '|': emit(c, 0x4308); return unsigned_word;            /* orrs r0, r1 */
    case '^': emit(c, 0x4048); return unsigned_word;            /* eors r0, r1 */
    case TOK_SHL: case TOK_SHR:
        emit(c, 0x4602);                                      /* mov r2, r0: shift count */
        emit(c, 0x4608);                                      /* mov r0, r1: source */
        emit(c, op == TOK_SHL ? 0x4090 : unsigned_word ? 0x40d0 : 0x4110);
        return unsigned_word;                                 /* lsls/lsrs/asrs r0,r2 */
    case '/':
        emit(c, unsigned_word ? 0xfbb1 : 0xfb91);
        emit(c, 0xf0f0);                                       /* [us]div r0, r1, r0 */
        return unsigned_word;
    case '%':
        emit(c, unsigned_word ? 0xfbb1 : 0xfb91);
        emit(c, 0xf2f0);                                       /* [us]div r2, r1, r0 */
        emit(c, 0x4350);                                       /* muls r0, r2 */
        emit(c, 0x1a08);                                       /* subs r0, r1, r0 */
        return unsigned_word;
    }
    emit(c, 0x4281);                                           /* cmp r1, r0 */
    switch (op) {
    case TOK_EQ: boolean(c, 0); break;
    case TOK_NE: boolean(c, 1); break;
    case TOK_GE: boolean(c, unsigned_word ? 2 : 10); break;
    case '<':    boolean(c, unsigned_word ? 3 : 11); break;
    case '>':    boolean(c, unsigned_word ? 8 : 12); break;
    case TOK_LE: boolean(c, unsigned_word ? 9 : 13); break;
    }
    return 0;
}

static int expression(Compiler *c, int minimum, int requirement)
{
    Token start = c->token;
    if (++c->nesting > NESTING_LIMIT)
        error(c, "Expression or block nesting is too deep");
    int type = unary(c, requirement == STATEMENT_VALUE);
    while (!c->diagnostic.message && precedence(c->token.kind) >= minimum) {
        if (type == VALUE_VOID) {
            error(c, "Expected an integer operand, got void");
            break;
        }
        int op = c->token.kind;
        int next_precedence = precedence(op) + 1;
        advance(c);
        if (op == TOK_AND || op == TOK_OR) {
            uint32_t short_circuit = branch_on_value(c, op == TOK_OR);
            expression(c, next_precedence, REQUIRE_SCALAR);
            emit(c, 0x2800);
            boolean(c, 1);                                    /* ne */
            uint32_t done = branch(c);
            patch_branch(c, short_circuit, c->pc, 0);
            constant(c, op == TOK_OR);
            patch_branch(c, done, c->pc, 0);
            type = VALUE_INT;
        } else {
            int equality = op == TOK_EQ || op == TOK_NE;
            if (type == VALUE_VOID || ((type == VALUE_POINTER || type == VALUE_STRUCT_DOUBLE_POINTER || type == VALUE_INT_DOUBLE_POINTER ||
                         type == VALUE_RECORD) && !equality)) {
                error_at(c, start, "Expected an integer operand, got a pointer");
                break;
            }
            emit(c, 0xb403);                                   /* push {r0, r1} */
            Token rhs_start = c->token;
            int rhs_type = expression(c, next_precedence, REQUIRE_SCALAR);
            emit(c, 0xbc06);                                   /* pop {r1, r2} */
            int left_ptr = type == VALUE_INT_POINTER;
            int right_ptr = rhs_type == VALUE_INT_POINTER;
            if ((left_ptr || right_ptr) && (op == '+' || op == '-')) {
                if (left_ptr && right_ptr && op == '-') {
                    emit(c, 0x1a08);                           /* subs r0, r1, r0 */
                    emit(c, 0x1080);                           /* asrs r0, r0, #2 */
                    type = VALUE_INT;
                } else if (left_ptr && !right_ptr && rhs_type != VALUE_POINTER) {
                    emit(c, 0x0080);                           /* lsls integer offset, #2 */
                    emit(c, op == '+' ? 0x1808 : 0x1a08);
                    type = VALUE_INT_POINTER;
                } else if (right_ptr && !left_ptr && op == '+' && type != VALUE_POINTER) {
                    emit(c, 0x0089);                           /* lsls r1, r1, #2 */
                    emit(c, 0x1808);
                    type = VALUE_INT_POINTER;
                } else {
                    error_at(c, start, "Invalid pointer arithmetic");
                }
            } else if (left_ptr || right_ptr || type == VALUE_POINTER || rhs_type == VALUE_POINTER ||
                       type == VALUE_STRUCT_DOUBLE_POINTER || rhs_type == VALUE_STRUCT_DOUBLE_POINTER ||
                       type == VALUE_INT_DOUBLE_POINTER || rhs_type == VALUE_INT_DOUBLE_POINTER ||
                       type == VALUE_RECORD || rhs_type == VALUE_RECORD) {
                int lhs_null = (start.kind == TOK_NUMBER || start.kind == TOK_UNSIGNED_NUMBER) && start.number == 0;
                int rhs_null = (rhs_start.kind == TOK_NUMBER || rhs_start.kind == TOK_UNSIGNED_NUMBER) && rhs_start.number == 0;
                int compatible = (left_ptr && right_ptr) ||
                                 (type == VALUE_POINTER && rhs_type == VALUE_POINTER) ||
                                 (left_ptr && rhs_type == VALUE_POINTER) ||
                                 (right_ptr && type == VALUE_POINTER) ||
                                 (left_ptr && rhs_type == VALUE_INT && rhs_null) ||
                                 (right_ptr && type == VALUE_INT && lhs_null) ||
                                 (type == VALUE_POINTER && rhs_type == VALUE_INT && rhs_null) ||
                                 (rhs_type == VALUE_POINTER && type == VALUE_INT && lhs_null);
                if (!equality || !compatible)
                    error_at(c, start, "Pointer comparisons require compatible pointer values");
                binary(c, op, 1);
                type = VALUE_INT;
            } else {
                int result_unsigned = op == TOK_SHL || op == TOK_SHR
                    ? type == VALUE_UNSIGNED
                    : type == VALUE_UNSIGNED || rhs_type == VALUE_UNSIGNED;
                type = binary(c, op, result_unsigned) ? VALUE_UNSIGNED : VALUE_INT;
            }
        }
    }
    if ((requirement == REQUIRE_INTEGER || requirement == REQUIRE_SCALAR) && type == VALUE_VOID)
        error_at(c, start, "Expected an integer value, got void");
    if (requirement == REQUIRE_INTEGER && (type == VALUE_POINTER || type == VALUE_INT_POINTER ||
                                          type == VALUE_STRUCT_DOUBLE_POINTER || type == VALUE_INT_DOUBLE_POINTER ||
                                          type == VALUE_RECORD))
        error_at(c, start, "Expected an integer value, got a pointer");
    if (requirement == REQUIRE_INT_POINTER && type != VALUE_INT_POINTER && type != VALUE_POINTER &&
        !((start.kind == TOK_NUMBER || start.kind == TOK_UNSIGNED_NUMBER) && start.number == 0))
        error_at(c, start, "Expected an int * expression or NULL");
    --c->nesting;
    return type;
}

static void statement(Compiler *c);

/* Initializer backends: local values compile into stack stores; static
   values are captured as 32-bit words for inclusion in the .app image. */
static void initialize_scalar(Compiler *c, unsigned word, uint32_t *static_values,
                              int byte_value)
{
    if (!static_values) {
        expression(c, 1, REQUIRE_INTEGER);
        store_local(c, word, 0);
        return;
    }
    int negative = accept(c, '-');
    Token value = c->token;
    uint32_t number = 0;
    if (accept(c, TOK_SIZEOF)) {
        number = sizeof_operand(c);
    } else {
        const SidcApiConstant *api = value.kind == TOK_NAME ? find_api_constant(c, value) : NULL;
        if (value.kind != TOK_NUMBER && value.kind != TOK_UNSIGNED_NUMBER && !api) {
            error_at(c, value, "Static initializer needs an integer constant or sizeof");
            return;
        }
        number = api ? api->value : value.number;
        advance(c);
    }
    if (negative) number = 0u - number;
    if (byte_value && number > 255u) {
        error_at(c, value, "Static uint8_t initializer exceeds 255");
        return;
    }
    static_values[word] = number;
}

static void initialize_record(Compiler *c, unsigned rec, unsigned base,
                              uint32_t *static_values, unsigned depth)
{
    if (depth > NESTING_LIMIT) { error(c, "Initializer nesting is too deep"); return; }
    if (!expect(c, '{', "Expected '{' for record initializer")) return;
    const StructDef *def = &c->structs[rec];
    unsigned i = 0;
    while (!c->diagnostic.message && c->token.kind != '}' && c->token.kind != TOK_END) {
        if (i >= def->count || (def->is_union && i > 0)) {
            error(c, "Too many initializers for struct or union"); return;
        }
        RecordField f = def->fields[i];
        unsigned slot = base + f.offset_words;
        if (f.is_pointer) {
            if (static_values) {
                if (name_is(c->token, "NULL")) { advance(c); static_values[slot] = 0; }
                else if ((c->token.kind == TOK_NUMBER || c->token.kind == TOK_UNSIGNED_NUMBER) &&
                         c->token.number == 0) { advance(c); static_values[slot] = 0; }
                else error(c, "Static pointer field initializers only support NULL or 0");
            } else {
                if (f.record_id == RECORD_INT) expression(c, 1, REQUIRE_INT_POINTER);
                else struct_pointer_value(c, f.record_id);
                store_local(c, slot, 0);
            }
        } else if (f.record_id == RECORD_INT) {
            initialize_scalar(c, slot, static_values, 0);
        } else if (c->token.kind == '{') {
            initialize_record(c, f.record_id, slot, static_values, depth + 1);
        } else if ((c->token.kind == TOK_NUMBER || c->token.kind == TOK_UNSIGNED_NUMBER) &&
                   c->token.number == 0) {
            /* {0} is valid even when the first member is an embedded record. */
            advance(c);
        } else {
            error(c, "Embedded record initializer needs braces or zero"); return;
        }
        ++i;
        if (!accept(c, ',')) break;
    }
    expect(c, '}', "Expected '}' after record initializer");
}

static void initialize_array(Compiler *c, unsigned count, unsigned rec,
                             unsigned base, uint32_t *static_values, int byte_value)
{
    if (!expect(c, '{', "Expected '{' for array initializer")) return;
    unsigned i = 0;
    unsigned stride = rec == RECORD_INT ? 1u : c->structs[rec].size_words;
    while (!c->diagnostic.message && c->token.kind != '}' && c->token.kind != TOK_END) {
        if (i >= count) { error(c, "Too many array initializer elements"); return; }
        unsigned word = base + i * stride;
        if (rec == RECORD_INT) {
            initialize_scalar(c, word, static_values, byte_value);
        } else if (c->token.kind == '{') {
            initialize_record(c, rec, word, static_values, 1);
        } else if ((c->token.kind == TOK_NUMBER || c->token.kind == TOK_UNSIGNED_NUMBER) &&
                   c->token.number == 0) {
            advance(c);
        } else {
            error(c, "Array record element needs braces or zero"); return;
        }
        ++i;
        if (!accept(c, ',')) break;
    }
    expect(c, '}', "Expected '}' after array initializer");
}

/* Retain the old zero-only path for very large static arrays: they are BSS,
   not an enormous set of explicit initial values in the applet. */
static void initialize_large_zero(Compiler *c)
{
    if (!expect(c, '{', "Large static arrays only support {0}")) return;
    if ((c->token.kind != TOK_NUMBER && c->token.kind != TOK_UNSIGNED_NUMBER) ||
        c->token.number != 0) { error(c, "Large static arrays only support {0}"); return; }
    advance(c);
    accept(c, ',');
    expect(c, '}', "Large static arrays only support {0}");
}

/* Reserve scratch words in the compiler (not on its small ARM call stack). */
static uint32_t *initialize_static_buffer(Compiler *c, unsigned words)
{
    if (words > INITIAL_WORD_LIMIT - c->initial_used) {
        error(c, "Too many explicitly initialized static data words"); return NULL;
    }
    uint32_t *values = c->initial_values + c->initial_used;
    memset(values, 0, words * sizeof(uint32_t));
    return values;
}

static int initializer_nonzero(const uint32_t *values, unsigned count)
{
    for (unsigned i = 0; i < count; ++i)
        if (values[i] != 0) return 1;
    return 0;
}

/* A typed local function pointer: int (*fn)(int,int), or void (*fn)(void).
   This subset deliberately requires int parameters for indirect calls. */
static void local_callback_declaration(Compiler *c, uint8_t return_type)
{
    if (!expect(c, '(', "Expected '(' in function-pointer declaration") ||
        !expect(c, '*', "Expected '*' in function-pointer declaration")) return;
    Token name = c->token;
    if (!expect(c, TOK_NAME, "Expected function-pointer variable name") ||
        !expect(c, ')', "Expected ')' after function-pointer variable") ||
        !expect(c, '(', "Expected '(' before function-pointer parameter types")) return;
    FunctionPointerSignature sig = {.return_type = return_type};
    if (c->token.kind == TOK_VOID && c->lookahead.kind == ')')
        advance(c);
    else if (c->token.kind != ')') {
        do {
            if (sig.arity == FUNCTION_PARAMS) {
                error(c, "Function pointer has more than five parameters");
                return;
            }
            if (!expect(c, TOK_INT, "Function pointer parameters must have type int")) return;
            sig.params[sig.arity++] = LOCAL_INT;
            accept(c, TOK_NAME);                              /* optional prototype name */
        } while (accept(c, ','));
    }
    if (!expect(c, ')', "Expected ')' after function-pointer parameters")) return;
    unsigned slot = add_local(c, name, LOCAL_FUNCTION_POINTER);
    if (c->diagnostic.message) return;
    c->locals[slot].callback = sig;
    if (accept(c, '=')) function_pointer_value(c, &c->locals[slot].callback);
    else constant(c, 0);
    store_local(c, slot, 0);
    expect(c, ';', "Expected ';' after function-pointer declaration");
}

/* Consumes the semicolon for a local declaration. Used by blocks and for(). */
static int local_declaration(Compiler *c)
{
    int type = -1;
    int is_const = accept(c, TOK_CONST);
    if (c->token.kind == TOK_ENUM) {
        if (!enum_declaration(c)) return 1;
        type = LOCAL_INT;
    } else if (accept(c, TOK_INT)) {
        if (c->token.kind == '(' && c->lookahead.kind == '*') {
            local_callback_declaration(c, RETURN_INT);
            return 1;
        }
        type = accept(c, '*') ? (accept(c, '*') ? LOCAL_INT_DOUBLE_POINTER : LOCAL_INT_POINTER) : LOCAL_INT;
    } else if (c->token.kind == TOK_NAME && find_alias(c, c->token) >= 0 &&
               c->aliases[find_alias(c, c->token)].record_id == RECORD_INT) {
        advance(c);
        type = LOCAL_INT;
    } else if (accept(c, TOK_VOID)) {
        if (c->token.kind == '(' && c->lookahead.kind == '*')
            local_callback_declaration(c, RETURN_VOID);
        else error(c, "Only void function pointers are valid local declarations");
        return 1;
    } else if (is_record_type(c)) {
        unsigned struct_id = 0;
        if (!record_type(c, &struct_id)) return 1;
        int pointer = accept(c, '*');
        int double_pointer = pointer && accept(c, '*');
        Token name = c->token;
        if (!expect(c, TOK_NAME, "Expected record variable name")) return 1;
        unsigned count = 1;
        int is_array = !pointer && accept(c, '[');
        unsigned stride = c->structs[struct_id].size_words;
        if (is_array) {
            Token bound = c->token;
            if ((bound.kind != TOK_NUMBER && bound.kind != TOK_UNSIGNED_NUMBER) ||
                bound.number == 0 || bound.number > LOCAL_LIMIT / stride) {
                error_at(c, bound, c->structs[struct_id].is_union ? "Local union array exceeds 64 stack slots" : "Local struct array exceeds 64 stack slots");
                return 1;
            }
            count = bound.number;
            advance(c);
            if (!expect(c, ']', "Expected ']' after record array size")) return 1;
        }
        unsigned words = pointer ? 1u : count * stride;
        if (words > LOCAL_LIMIT - c->local_count) {
            error_at(c, name, "Record exceeds remaining 64 local stack slots");
            return 1;
        }
        unsigned slot = add_local(c, name, double_pointer ? LOCAL_STRUCT_DOUBLE_POINTER :
                                  pointer ? LOCAL_STRUCT_POINTER :
                                  is_array ? LOCAL_STRUCT_ARRAY : LOCAL_STRUCT);
        if (c->diagnostic.message) return 1;
        c->locals[slot].struct_id = (uint8_t)struct_id;
        c->locals[slot].array_count = (uint16_t)count;
        for (unsigned i = 1; i < words; ++i)
            c->locals[c->local_count++] = (Local){.scope=(uint8_t)c->scope,.type=LOCAL_PADDING};
        if (c->local_count > c->local_peak) c->local_peak = c->local_count;
        if (pointer) {
            if (accept(c, '=')) {
                if (double_pointer) struct_double_pointer_value(c, struct_id);
                else struct_pointer_value(c, struct_id);
            } else constant(c, 0);
            store_local(c, slot, 0);
        } else if (accept(c, '=')) {
            if (!is_array && c->token.kind != '{') {
                record_value_address(c, struct_id);
                emit(c, 0xb403);                  /* push {r0,r1} preserves source */
                local_address(c, slot);
                emit(c, 0x4601);                  /* mov r1,r0 destination */
                emit(c, 0xbc05);                  /* pop {r0,r2} source */
                copy_record(c, stride);
            } else {
                constant(c, 0);
                for (unsigned i = 0; i < words; ++i) store_local(c, slot + i, 0);
                if (is_array) initialize_array(c, count, struct_id, slot, NULL, 0);
                else initialize_record(c, struct_id, slot, NULL, 1);
            }
        }
        expect(c, ';', "Expected ';' after record variable");
        return 1;
    } else if (c->token.kind == TOK_NAME && find_local(c, c->token) < 0) {
        if (accept_sdk_type(c, "CGGadget")) type = LOCAL_GADGET;
        else if (accept_sdk_type(c, "CGWindow") || accept_sdk_type(c, "uint8_t"))
            type = LOCAL_WINDOW;
    }
    if (type < 0) {
        if (is_const) { error(c, "const currently supports integer or enum scalar variables"); return 1; }
        return 0;
    }
    if (is_const && type != LOCAL_INT) {
        error(c, "const currently supports integer or enum scalar variables"); return 1;
    }
    Token name = c->token;
    if (!expect(c, TOK_NAME, "Expected a local variable name")) return 1;
    if (accept(c, '[')) {
        if (is_const) { error_at(c, name, "const arrays are not yet supported"); return 1; }
        if (type != LOCAL_INT) {
            error_at(c, name, "Only local int arrays are supported");
            return 1;
        }
        Token bound = c->token;
        if ((bound.kind != TOK_NUMBER && bound.kind != TOK_UNSIGNED_NUMBER) ||
            bound.number == 0 || bound.number > LOCAL_LIMIT - c->local_count) {
            error_at(c, bound, "Local int array exceeds remaining 64 stack slots");
            return 1;
        }
        unsigned count = bound.number;
        advance(c);
        if (!expect(c, ']', "Expected ']' after local array size")) return 1;
        unsigned slot = add_local(c, name, LOCAL_INT_ARRAY);
        if (c->diagnostic.message) return 1;
        c->locals[slot].array_count = (uint16_t)count;
        for (unsigned i = 1; i < count; ++i) {
            c->locals[c->local_count++] = (Local){.scope = (uint8_t)c->scope, .type = LOCAL_PADDING};
        }
        if (c->local_count > c->local_peak) c->local_peak = c->local_count;
        if (accept(c, '=')) {
            constant(c, 0);
            for (unsigned i = 0; i < count; ++i) store_local(c, slot + i, 0);
            initialize_array(c, count, RECORD_INT, slot, NULL, 0);
        }
        expect(c, ';', "Expected ';' after local array declaration");
        return 1;
    }
    unsigned slot = add_local(c, name, (uint8_t)type);
    if (c->diagnostic.message) return 1;
    c->locals[slot].is_const = (uint8_t)is_const;
    if (accept(c, '=')) {
        if (type == LOCAL_INT_DOUBLE_POINTER) int_double_pointer_value(c);
        else expression(c, 1, type == LOCAL_INT_POINTER ? REQUIRE_INT_POINTER : REQUIRE_INTEGER);
        if (type == LOCAL_WINDOW) emit(c, 0xb2c0);
        store_local(c, slot, 0);
    } else if (is_const) {
        error_at(c, name, "const local must be initialized");
    }
    expect(c, ';', "Expected ';' after declaration");
    return 1;
}

/* A simple expression or assignment, without consuming its terminator.
   Supports for initializers/steps as well as ordinary statements. */
static void simple_expression(Compiler *c)
{
    int assignment = c->lookahead.kind == '=' ||
                     c->lookahead.kind == TOK_ADD_ASSIGN || c->lookahead.kind == TOK_SUB_ASSIGN ||
                     c->lookahead.kind == TOK_BAND_ASSIGN || c->lookahead.kind == TOK_BOR_ASSIGN ||
                     c->lookahead.kind == TOK_BXOR_ASSIGN || c->lookahead.kind == TOK_SHL_ASSIGN ||
                     c->lookahead.kind == TOK_SHR_ASSIGN;
    if (c->token.kind != TOK_NAME || !assignment) {
        expression(c, 1, STATEMENT_VALUE);
        return;
    }
    Token name = c->token;
    int slot = find_local(c, name);
    int global = slot < 0 ? find_global(c, name) : -1;
    int type = slot >= 0 ? c->locals[slot].type
                         : global >= 0 ? c->globals[global].type : -1;
    if (type < 0) {
        error_at(c, name, "Assignment needs a declared variable");
        return;
    }
    if ((slot >= 0 && c->locals[slot].is_const) ||
        (global >= 0 && c->globals[global].is_const)) {
        error_at(c, name, "Cannot assign to const variable");
        return;
    }
    if (type == LOCAL_STRUCT || type == GLOBAL_STRUCT) {
        Token target = name;
        advance(c);
        if (!accept(c, '=')) { error_at(c, target, "Struct assignment only supports ="); return; }
        unsigned rec = slot >= 0 ? c->locals[slot].struct_id : c->globals[global].struct_id;
        record_value_address(c, rec);
        emit(c, 0xb403);
        if (slot >= 0) local_address(c, (unsigned)slot);
        else { emit_address(c, ADDRESS_GLOBAL, (unsigned)global); emit(c, 0x4608); }
        emit(c, 0x4601);
        emit(c, 0xbc05);
        copy_record(c, c->structs[rec].size_words);
        return;
    }
    if (type == GLOBAL_BYTE_ARRAY || type == GLOBAL_INT_ARRAY || type == LOCAL_INT_ARRAY ||
        type == LOCAL_STRUCT || type == GLOBAL_STRUCT ||
        type == LOCAL_STRUCT_ARRAY || type == GLOBAL_STRUCT_ARRAY) {
        error_at(c, name, "Assign to an individual array element");
        return;
    }
    if (type == LOCAL_POINTER || type == LOCAL_ARGV || type == LOCAL_MESSAGE || type == LOCAL_PADDING) {
        error_at(c, name, "Pointer assignment is outside this C subset");
        return;
    }
    advance(c);
    int op = c->token.kind;
    advance(c);
    if (type == LOCAL_FUNCTION_POINTER) {
        if (op != '=') {
            error_at(c, name, "Function pointer only supports simple assignment");
            return;
        }
        function_pointer_value(c, &c->locals[slot].callback);
        store_local(c, (unsigned)slot, 0);
        return;
    }
    if (type == LOCAL_INT_DOUBLE_POINTER) {
        if (op != '=') { error_at(c, name, "int ** only supports simple assignment"); return; }
        int_double_pointer_value(c);
        store_local(c, (unsigned)slot, 0);
        return;
    }
    if (type == LOCAL_STRUCT_DOUBLE_POINTER) {
        if (op != '=') {
            error_at(c, name, "Struct ** only supports simple assignment");
            return;
        }
        struct_double_pointer_value(c, c->locals[slot].struct_id);
        store_local(c, (unsigned)slot, 0);
        return;
    }
    if (type == LOCAL_STRUCT_POINTER) {
        if (op != '=') {
            error_at(c, name, "Struct pointer only supports simple assignment");
            return;
        }
        struct_pointer_value(c, c->locals[slot].struct_id);
        store_local(c, (unsigned)slot, 0);
        return;
    }
    if (op != '=') {
        if (type == LOCAL_INT_POINTER && op != TOK_ADD_ASSIGN && op != TOK_SUB_ASSIGN) {
            error_at(c, name, "Pointer compound assignment only supports += or -="); return;
        }
        if (slot >= 0) load_local(c, (unsigned)slot, 0);
        else {
            emit_address(c, ADDRESS_GLOBAL, (unsigned)global);
            emit(c, 0x6808);
        }
        emit(c, 0xb403);                                       /* push old {r0,r1} */
    }
    expression(c, 1, type == LOCAL_INT_POINTER && op == '=' ? REQUIRE_INT_POINTER : REQUIRE_INTEGER);
    if (op != '=') {
        emit(c, 0xbc06);                                       /* pop old into r1 */
        if (type == LOCAL_INT_POINTER) emit(c, 0x0080);        /* pointer += n scales by 4 */
        switch (op) {
        case TOK_ADD_ASSIGN: emit(c, 0x1808); break;
        case TOK_SUB_ASSIGN: emit(c, 0x1a08); break;
        case TOK_BAND_ASSIGN: emit(c, 0x4008); break;
        case TOK_BOR_ASSIGN: emit(c, 0x4308); break;
        case TOK_BXOR_ASSIGN: emit(c, 0x4048); break;
        case TOK_SHL_ASSIGN: case TOK_SHR_ASSIGN:
            emit(c, 0x4602); emit(c, 0x4608);
            emit(c, op == TOK_SHL_ASSIGN ? 0x4090 : 0x4110);
            break;
        }
    }
    if (type == LOCAL_WINDOW) emit(c, 0xb2c0);
    if (slot >= 0) store_local(c, (unsigned)slot, 0);
    else {
        emit_address(c, ADDRESS_GLOBAL, (unsigned)global);
        emit(c, 0x6008);
    }
}

static void block(Compiler *c)
{
    while (!c->diagnostic.message && c->token.kind != '}' && c->token.kind != TOK_END) {
        if (!local_declaration(c)) statement(c);
    }
    expect(c, '}', "Expected '}' at end of block");
}

static void condition(Compiler *c)
{
    expect(c, '(', "Expected '(' before condition");
    expression(c, 1, REQUIRE_SCALAR);
    expect(c, ')', "Expected ')' after condition");
}

static void statement(Compiler *c)
{
    if (c->diagnostic.message)
        return;
    if (++c->nesting > NESTING_LIMIT) {
        error(c, "Expression or block nesting is too deep");
    } else if (accept(c, '{')) {
        unsigned saved_locals = c->local_count;
        ++c->scope;
        block(c);
        --c->scope;
        c->local_count = saved_locals;
    } else if (accept(c, TOK_IF)) {
        condition(c);
        uint32_t otherwise = branch_on_value(c, 0);
        statement(c);
        if (accept(c, TOK_ELSE)) {
            uint32_t done = branch(c);
            patch_branch(c, otherwise, c->pc, 0);
            statement(c);
            patch_branch(c, done, c->pc, 0);
        } else {
            patch_branch(c, otherwise, c->pc, 0);
        }
    } else if (accept(c, TOK_WHILE)) {
        if (c->loop_depth == LOOP_LIMIT) {
            error(c, "Too many nested loops");
        } else {
            unsigned saved_jumps = c->loop_jump_count;
            uint32_t repeat = c->pc;
            condition(c);
            uint32_t done = branch_on_value(c, 0);
            ++c->loop_depth;
            if (c->control_depth == CONTROL_LIMIT) error(c, "Too many nested breakable statements");
            else {
                c->control_kind[c->control_depth++] = 1;
                statement(c);
                --c->control_depth;
            }
            --c->loop_depth;
            patch_branch(c, branch(c), repeat, 0);
            patch_branch(c, done, c->pc, 0);
            for (unsigned i = saved_jumps; i < c->loop_jump_count; ++i)
                patch_branch(c, c->loop_jumps[i].at,
                             c->loop_jumps[i].is_break ? c->pc : repeat, 0);
            c->loop_jump_count = saved_jumps;
        }
    } else if (accept(c, TOK_FOR)) {
        if (c->loop_depth == LOOP_LIMIT) {
            error(c, "Too many nested loops");
        } else if (expect(c, '(', "Expected '(' after for")) {
            unsigned saved_locals = c->local_count;
            unsigned saved_jumps = c->loop_jump_count;
            ++c->scope;
            if (!local_declaration(c) && !accept(c, ';')) {
                simple_expression(c);
                expect(c, ';', "Expected ';' after for initializer");
            }
            uint32_t test = c->pc;
            uint32_t done = 0;
            if (c->token.kind != ';') {
                expression(c, 1, REQUIRE_SCALAR);
                done = branch_on_value(c, 0);
            }
            expect(c, ';', "Expected ';' after for condition");
            uint32_t first_body = branch(c);
            uint32_t step = c->pc;
            if (c->token.kind != ')') simple_expression(c);
            expect(c, ')', "Expected ')' after for step");
            patch_branch(c, branch(c), test, 0);
            patch_branch(c, first_body, c->pc, 0);
            ++c->loop_depth;
            if (c->control_depth == CONTROL_LIMIT) error(c, "Too many nested breakable statements");
            else {
                c->control_kind[c->control_depth++] = 1;
                statement(c);
                --c->control_depth;
            }
            --c->loop_depth;
            patch_branch(c, branch(c), step, 0);
            if (done) patch_branch(c, done, c->pc, 0);
            for (unsigned i = saved_jumps; i < c->loop_jump_count; ++i)
                patch_branch(c, c->loop_jumps[i].at,
                             c->loop_jumps[i].is_break ? c->pc : step, 0);
            c->loop_jump_count = saved_jumps;
            c->local_count = saved_locals;
            --c->scope;
        }
    } else if (accept(c, TOK_SWITCH)) {
        if (c->control_depth == CONTROL_LIMIT) {
            error(c, "Too many nested breakable statements");
        } else if (c->switch_case_count == SWITCH_CASE_LIMIT) {
            error(c, "Too many switch case labels");
        } else {
            unsigned saved_locals = c->local_count;
            unsigned saved_switch_breaks = c->switch_break_count;
            unsigned saved_cases = c->switch_case_count;
            if (c->local_count == LOCAL_LIMIT) {
                error(c, "No stack slot available for switch expression");
            } else if (expect(c, '(', "Expected '(' after switch")) {
                expression(c, 1, REQUIRE_INTEGER);
                if (expect(c, ')', "Expected ')' after switch expression") &&
                    expect(c, '{', "Expected '{' after switch condition")) {
                    unsigned selector = c->local_count++;
                    if (c->local_count > c->local_peak) c->local_peak = c->local_count;
                    c->locals[selector] = (Local){.scope = (uint8_t)c->scope, .type = LOCAL_PADDING};
                    store_local(c, selector, 0);
                    uint32_t dispatch = branch(c);
                    uint32_t default_target = 0;
                    unsigned labels = 0;
                    ++c->scope;
                    c->control_kind[c->control_depth++] = 2;
                    while (!c->diagnostic.message && c->token.kind != '}' && c->token.kind != TOK_END) {
                        if (c->token.kind == TOK_CASE) {
                            advance(c);
                            Token value = c->token;
                            int negative = accept(c, '-');
                            if (c->token.kind != TOK_NUMBER && c->token.kind != TOK_UNSIGNED_NUMBER) {
                                error(c, "Case label needs an integer constant");
                                break;
                            }
                            uint32_t v = negative ? 0u - c->token.number : c->token.number;
                            advance(c);
                            if (!expect(c, ':', "Expected ':' after case value")) break;
                            for (unsigned j = saved_cases; j < c->switch_case_count; ++j)
                                if (c->switch_cases[j].value == v)
                                    error_at(c, value, "Duplicate switch case value");
                            if (c->switch_case_count == SWITCH_CASE_LIMIT)
                                error_at(c, value, "Too many switch case labels");
                            else
                                c->switch_cases[c->switch_case_count++] = (SwitchCase){c->pc, v};
                            ++labels;
                        } else if (accept(c, TOK_DEFAULT)) {
                            Token value = c->token;
                            if (!expect(c, ':', "Expected ':' after default")) break;
                            if (default_target)
                                error_at(c, value, "Duplicate switch default label");
                            else default_target = c->pc;
                            ++labels;
                        } else if (!local_declaration(c)) {
                            statement(c);
                        }
                    }
                    expect(c, '}', "Expected '}' after switch body");
                    --c->control_depth;
                    --c->scope;
                    uint32_t skip_dispatch = branch(c);    /* fallthrough exits switch */
                    patch_branch(c, dispatch, c->pc, 0);
                    for (unsigned j = saved_cases; j < c->switch_case_count; ++j) {
                        load_local(c, selector, 0);
                        load_constant(c, 1, c->switch_cases[j].value);
                        emit(c, 0x4288);                   /* cmp r0, r1 */
                        emit(c, 0xd101);                   /* bne over B.W */
                        patch_branch(c, branch(c), c->switch_cases[j].target, 0);
                    }
                    uint32_t no_match = 0;
                    if (default_target) patch_branch(c, branch(c), default_target, 0);
                    else no_match = branch(c);
                    uint32_t end = c->pc;
                    patch_branch(c, skip_dispatch, end, 0);
                    if (no_match) patch_branch(c, no_match, end, 0);
                    for (unsigned j = saved_switch_breaks; j < c->switch_break_count; ++j)
                        patch_branch(c, c->switch_breaks[j], end, 0);
                    c->switch_break_count = saved_switch_breaks;
                    c->switch_case_count = saved_cases;
                    if (!labels) error(c, "Switch needs at least one case or default");
                }
            }
            c->local_count = saved_locals;
        }
    } else if (c->token.kind == TOK_BREAK || c->token.kind == TOK_CONTINUE) {
        int is_break = c->token.kind == TOK_BREAK;
        if ((!is_break && !c->loop_depth) || (is_break && !c->control_depth)) {
            error(c, is_break ? "break outside a loop or switch" : "continue outside a loop");
        } else {
            int switch_break = is_break && c->control_kind[c->control_depth - 1u] == 2;
            if (switch_break && c->switch_break_count == SWITCH_BREAK_LIMIT)
                error(c, "Too many switch breaks");
            else if (!switch_break && c->loop_jump_count == LOOP_JUMP_LIMIT)
                error(c, "Too many loop breaks or continues");
            else {
                advance(c);
                expect(c, ';', "Expected ';' after break or continue");
                uint32_t at = branch(c);
                if (switch_break) c->switch_breaks[c->switch_break_count++] = at;
                else c->loop_jumps[c->loop_jump_count++] = (LoopJump){at, (uint8_t)is_break};
            }
        }
    } else if (accept(c, TOK_RETURN)) {
        if (c->return_type == RETURN_RECORD) {
            record_value_address(c, c->return_struct_id);
            load_local(c, c->return_buffer_slot, 1);
            copy_record(c, c->structs[c->return_struct_id].size_words);
            emit(c, 0x4608); /* r0 = destination pointer */
        } else if (c->return_type == RETURN_STRUCT_POINTER) {
            struct_pointer_value(c, c->return_struct_id);
        } else if (c->return_type != RETURN_VOID) {
            expression(c, 1, c->return_type == RETURN_INT_POINTER ? REQUIRE_INT_POINTER : REQUIRE_INTEGER);
            if (c->return_type == RETURN_WINDOW)
                emit(c, 0xb2c0);                              /* uxtb r0, r0 */
        } else if (c->token.kind != ';') {
            error(c, "A void function uses return without a value");
        }
        expect(c, ';', "Expected ';' after return");
        if (c->return_count == RETURN_LIMIT)
            error(c, "Too many returns in one function");
        else
            c->returns[c->return_count++] = branch(c);
    } else if (!accept(c, ';')) {
        simple_expression(c);
        expect(c, ';', "Expected ';' after statement");
    }
    --c->nesting;
}

static unsigned builtin_entry(Token name)
{
    if (name_is(name, "sidbox_message"))
        return BUILTIN_MESSAGE;
    if (name_is(name, "sidbox_ticks"))
        return BUILTIN_TICKS;
    if (name_is(name, "sidbox_buttons"))
        return BUILTIN_BUTTONS;
    return 0;
}

static void global_declaration(Compiler *c, Token name, uint8_t type, int is_const)
{
    int function = find_function(c, name);
    if (find_alias(c, name) >= 0 || find_global(c, name) >= 0 ||
        (function >= 0 && c->functions[function].unit == c->file_index) ||
        find_api_constant(c, name) || find_api_call(c, name)) {
        error_at(c, name, "Duplicate file-scope name");
        return;
    }
    if (c->global_count == GLOBAL_LIMIT) {
        error_at(c, name, "Too many file-scope static variables");
        return;
    }
    uint32_t count = 0;
    if (accept(c, '[')) {
        if (is_const) { error_at(c, name, "const static arrays are not yet supported"); return; }
        if (type != LOCAL_WINDOW && type != LOCAL_INT) {
            error_at(c, name, "Only static int and uint8_t arrays are supported");
            return;
        }
        Token bound = c->token;
        if ((bound.kind != TOK_NUMBER && bound.kind != TOK_UNSIGNED_NUMBER) || bound.number == 0) {
            error_at(c, bound, "Byte array size needs a positive integer literal");
            return;
        }
        count = bound.number;
        if (type == LOCAL_INT && count > BYTE_ARRAY_LIMIT / 4u) {
            error_at(c, bound, "Static int arrays exceed 256 KiB");
            return;
        }
        count *= (type == LOCAL_INT ? 4u : 1u);
        unsigned aligned = type == LOCAL_INT ? (c->array_bytes + 3u) & ~3u : c->array_bytes;
        if (aligned > BYTE_ARRAY_LIMIT || count > BYTE_ARRAY_LIMIT - aligned) {
            error_at(c, bound, "Static byte arrays exceed 256 KiB");
            return;
        }
        advance(c);
        if (!expect(c, ']', "Expected ']' after the byte array size"))
            return;
        type = type == LOCAL_INT ? GLOBAL_INT_ARRAY : GLOBAL_BYTE_ARRAY;
    }
    uint32_t initial = 0;
    uint32_t init_words = type == GLOBAL_INT_ARRAY ? count / 4u : count;
    unsigned init_at = c->initial_used;
    int initialized = 0;
    if (accept(c, '=')) {
        if (type == GLOBAL_BYTE_ARRAY || type == GLOBAL_INT_ARRAY) {
            if (init_words > INITIAL_WORD_LIMIT - c->initial_used) {
                initialize_large_zero(c);
            } else {
                uint32_t *values = initialize_static_buffer(c, init_words);
                if (!values) return;
                initialize_array(c, init_words, RECORD_INT, 0, values,
                                 type == GLOBAL_BYTE_ARRAY);
                if (initializer_nonzero(values, init_words)) {
                    initialized = 1;
                    c->initial_used += init_words;
                }
            }
        } else {
            int negative = accept(c, '-');
            Token token = c->token;
            if (accept(c, TOK_SIZEOF)) initial = sizeof_operand(c);
            else {
                const SidcApiConstant *value = token.kind == TOK_NAME ? find_api_constant(c, token) : NULL;
                if (value) initial = value->value;
                else if (token.kind == TOK_NUMBER || token.kind == TOK_UNSIGNED_NUMBER) {
                    int64_t value = enum_expression(c, 1, 0);
                    if (c->diagnostic.message) return;
                    if (value < INT32_MIN || value > UINT32_MAX) {
                        error_at(c, token, "Static initializer exceeds 32-bit range"); return;
                    }
                    initial = (uint32_t)value;
                    token.kind = TOK_END; /* expression already consumed */
                } else {
                    error(c, "Static initializer needs an integer constant or sizeof");
                    return;
                }
                if (token.kind != TOK_END) advance(c);
            }
            if (negative) initial = 0u - initial;
        }
    }
    if (type == LOCAL_WINDOW)
        initial &= 0xffu;
    if (!expect(c, ';', "Expected ';' after static declaration"))
        return;
    uint32_t offset;
    if (type == GLOBAL_BYTE_ARRAY || type == GLOBAL_INT_ARRAY) {
        if (initialized) {
            if (type == GLOBAL_INT_ARRAY) c->global_bytes = (c->global_bytes + 3u) & ~3u;
            offset = c->global_bytes;
            c->global_bytes += count;
        } else {
            if (type == GLOBAL_INT_ARRAY) c->array_bytes = (c->array_bytes + 3u) & ~3u;
            offset = c->array_bytes;
            c->array_bytes += count;
        }
    } else {
        c->global_bytes = (c->global_bytes + 3u) & ~3u;
        offset = c->global_bytes;
        c->global_bytes += sizeof(initial);
    }
    c->globals[c->global_count++] = (Global){.name=name,.initial=initial,.offset=offset,.type=type,.unit=c->file_index,
                .is_const=(uint8_t)is_const,
                .array_count=type == GLOBAL_INT_ARRAY ? count / 4u : type == GLOBAL_BYTE_ARRAY ? count : 0u,
                .in_data=(uint8_t)initialized,.init_offset=(uint16_t)init_at,
                .init_count=(uint16_t)(initialized ? init_words : 0u)};
}

static void external_declaration(Compiler *c)
{
    if (accept(c, TOK_TYPEDEF)) {
        typedef_declaration(c);
        return;
    }
    if ((c->token.kind == TOK_STRUCT || c->token.kind == TOK_UNION) &&
        c->lookahead.kind == TOK_NAME) {
        int is_union = c->token.kind == TOK_UNION;
        advance(c);
        Token tag = c->token;
        if (!expect(c, TOK_NAME, "Expected struct or union tag")) return;
        if (c->token.kind == '{') {
            record_definition(c, tag, is_union, 0, tag);
            if (!c->diagnostic.message) expect(c, ';', "Expected ';' after record definition");
            return;
        }
        error_at(c, tag, "File-scope records must be static");
        return;
    }
    if (accept(c, TOK_APIS_INCLUDE)) {
        if (c->api.call_count == 0) load_apicore(c, c->api_reader);
        return;
    }
    int is_static = accept(c, TOK_STATIC);
    int is_const = accept(c, TOK_CONST);
    if (c->token.kind == TOK_ENUM) {
        if (!enum_declaration(c)) return;
        if (accept(c, ';')) return;
        Token variable = c->token;
        if (!expect(c, TOK_NAME, "Expected enum variable name")) return;
        if (!is_static && !is_const) {
            error_at(c, variable, "File-scope enum variables must be static"); return;
        }
        global_declaration(c, variable, LOCAL_INT, is_const);
        return;
    }
    unsigned record_return_id = RECORD_INT;
    unsigned record_return_type = 0;
    Token record_function_name = {0};
    if (is_record_type(c)) {
        if (is_const) { error(c, "const record declarations are not yet supported"); return; }
        unsigned index = 0;
        if (!record_type(c, &index)) return;
        int pointer_result = accept(c, '*');
        Token name = c->token;
        if (!expect(c, TOK_NAME, "Expected record declaration name")) return;
        if (c->token.kind == '(') {
            record_return_id = index;
            record_return_type = pointer_result ? RETURN_STRUCT_POINTER : RETURN_RECORD;
            record_function_name = name;
            goto parse_record_function;
        }
        if (pointer_result) {
            error_at(c, name, "Static pointer-to-record globals are not supported"); return;
        }
        if (!is_static) {
            error_at(c, name, "File-scope record variables must be static"); return;
        }
        unsigned count = 1;
        int is_array = accept(c, '[');
        unsigned stride = c->structs[index].size_words;
        if (is_array) {
            Token bound = c->token;
            if ((bound.kind != TOK_NUMBER && bound.kind != TOK_UNSIGNED_NUMBER) ||
                bound.number == 0 || bound.number > BYTE_ARRAY_LIMIT / (stride * 4u)) {
                error_at(c, bound, c->structs[index].is_union ? "Invalid static union array size" : "Invalid static struct array size");
                return;
            }
            count = bound.number;
            advance(c);
            if (!expect(c, ']', "Expected ']' after record array size")) return;
        }
        unsigned words = count * stride;
        unsigned init_at = c->initial_used;
        int initialized = 0;
        if (accept(c, '=')) {
            if (words > INITIAL_WORD_LIMIT - c->initial_used) {
                initialize_large_zero(c);
            } else {
                uint32_t *values = initialize_static_buffer(c, words);
                if (!values) return;
                if (is_array) initialize_array(c, count, index, 0, values, 0);
                else initialize_record(c, index, 0, values, 1);
                if (initializer_nonzero(values, words)) {
                    initialized = 1;
                    c->initial_used += words;
                }
            }
        }
        if (!expect(c, ';', "Expected ';' after static record declaration")) return;
        if (find_alias(c, name) >= 0 || find_global(c, name) >= 0 ||
            find_function(c, name) >= 0) {
            error_at(c, name, "Duplicate file-scope name");
            return;
        }
        uint32_t bytes = count * stride * 4u;
        if (c->global_count == GLOBAL_LIMIT ||
            (!initialized && c->array_bytes > BYTE_ARRAY_LIMIT - bytes)) {
            error_at(c, name, "Static record exceeds global array space");
            return;
        }
        uint32_t offset;
        if (initialized) {
            c->global_bytes = (c->global_bytes + 3u) & ~3u;
            offset = c->global_bytes;
            c->global_bytes += bytes;
        } else {
            c->array_bytes = (c->array_bytes + 3u) & ~3u;
            offset = c->array_bytes;
            c->array_bytes += bytes;
        }
        c->globals[c->global_count++] = (Global){.name=name,.offset=offset,
              .type=is_array ? GLOBAL_STRUCT_ARRAY : GLOBAL_STRUCT,
              .unit=c->file_index,.struct_id=(uint8_t)index,.array_count=count,
              .in_data=(uint8_t)initialized,.init_offset=(uint16_t)init_at,
              .init_count=(uint16_t)(initialized ? words : 0u)};
        return;
    }
    if (!is_static)
        accept(c, TOK_EXTERN);
    unsigned return_type = RETURN_INT;
    unsigned variable_type = LOCAL_INT;
    if (accept(c, TOK_VOID))
        return_type = RETURN_VOID;
    else if (accept_sdk_type(c, "CGWindowProcRes"))
        return_type = RETURN_WINDOW;
    else if (is_static && accept_sdk_type(c, "CGGadget"))
        variable_type = LOCAL_GADGET;
    else if (is_static && (accept_sdk_type(c, "CGWindow") || accept_sdk_type(c, "uint8_t")))
        variable_type = LOCAL_WINDOW;
    else if (accept(c, TOK_INT) ||
             (c->token.kind == TOK_NAME && find_alias(c, c->token) >= 0 &&
              c->aliases[find_alias(c, c->token)].record_id == RECORD_INT &&
              (advance(c), 1))) {
        if (accept(c, '*')) return_type = RETURN_INT_POINTER;
    } else {
        error(c, "Expected a supported function or static variable type");
        return;
    }

    Token name = c->token;
    if (!expect(c, TOK_NAME, "Expected a declaration name"))
        return;
    goto parse_function_common;
parse_record_function:
    return_type = record_return_type;
    name = record_function_name;
parse_function_common:
    if ((is_static || is_const) && return_type == RETURN_INT &&
        (variable_type != LOCAL_INT || c->token.kind != '(')) {
        if (is_const && variable_type != LOCAL_INT) {
            error_at(c, name, "const only supports integer globals"); return;
        }
        global_declaration(c, name, (uint8_t)variable_type, is_const);
        return;
    }
    if (is_const) { error_at(c, name, "const is not a function qualifier"); return; }
    if (!expect(c, '(', "Expected '(' after function name"))
        return;
    if (find_alias(c, name) >= 0 || find_global(c, name) >= 0) {
        error_at(c, name, "Duplicate file-scope name");
        return;
    }

    unsigned builtin = builtin_entry(name);
    int is_main = name_is(name, "main");
    if ((builtin || is_main) && (is_static || return_type != RETURN_INT)) {
        error_at(c, name, "This entry point requires an int function with external linkage");
        return;
    }
    unsigned arity = 0;
    uint8_t param_types[FUNCTION_PARAMS] = {0};
    uint8_t param_struct_ids[FUNCTION_PARAMS] = {0};
    Token params[FUNCTION_PARAMS];
    if (builtin == BUILTIN_MESSAGE) {
        if (!expect(c, TOK_CONST, "Expected 'const char *' for sidbox_message") ||
            !expect(c, TOK_CHAR, "Expected 'const char *' for sidbox_message") ||
            !expect(c, '*', "Expected 'const char *' for sidbox_message"))
            return;
        accept(c, TOK_NAME);
        arity = 1;
        param_types[0] = LOCAL_POINTER;
    } else if (c->token.kind == TOK_VOID && c->lookahead.kind == ')') {
        advance(c);
    } else {
        do {
            if (arity == FUNCTION_PARAMS) {
                error(c, "A function can have up to five parameters");
                return;
            }
            if (arity == 1 && is_main && param_types[0] == LOCAL_INT && accept(c, TOK_CHAR)) {
                if (!expect(c, '*', "Expected char ** for main's second parameter") ||
                    !expect(c, '*', "Expected char ** for main's second parameter"))
                    return;
                param_types[arity] = LOCAL_ARGV;
            } else if (is_record_type(c)) {
                unsigned type_id = 0;
                if (!record_type(c, &type_id)) return;
                if (accept(c, '*'))
                    param_types[arity] = accept(c, '*') ? LOCAL_STRUCT_DOUBLE_POINTER : LOCAL_STRUCT_POINTER;
                else
                    param_types[arity] = LOCAL_STRUCT;
                param_struct_ids[arity] = (uint8_t)type_id;
            } else if ((c->token.kind == TOK_ENUM && enum_declaration(c)) ||
                       accept(c, TOK_INT) ||
                       (c->token.kind == TOK_NAME && find_alias(c, c->token) >= 0 &&
                        c->aliases[find_alias(c, c->token)].record_id == RECORD_INT &&
                        (advance(c), 1))) {
                param_types[arity] = accept(c, '*') ?
                    (accept(c, '*') ? LOCAL_INT_DOUBLE_POINTER : LOCAL_INT_POINTER) : LOCAL_INT;
            } else if (accept_sdk_type(c, "int32_t")) {
                param_types[arity] = LOCAL_S32;
            } else if (accept_sdk_type(c, "CGGadget")) {
                param_types[arity] = LOCAL_GADGET;
            } else if (accept_sdk_type(c, "CGWindow") || accept_sdk_type(c, "uint8_t")) {
                param_types[arity] = LOCAL_WINDOW;
            } else if (c->api.call_count && accept(c, TOK_CONST)) {
                if (!accept_sdk_type(c, "CGMessage_t") ||
                    !expect(c, '*', "Expected '*' after const CGMessage_t")) {
                    error(c, "Expected const CGMessage_t * parameter");
                    return;
                }
                if (!c->message.size) {
                    error(c, "Window messages need a new apis.bin");
                    return;
                }
                param_types[arity] = LOCAL_MESSAGE;
            } else if (c->api.call_count && accept(c, TOK_VOID)) {
                if (!expect(c, '*', "Expected '*' after void parameter"))
                    return;
                param_types[arity] = LOCAL_POINTER;
            } else {
                error(c, "Expected a parameter type or 'void'");
                return;
            }
            params[arity] = c->token;
            accept(c, TOK_NAME);
            ++arity;
        } while (param_types[arity - 1] != LOCAL_ARGV && accept(c, ','));
    }
    if (!expect(c, ')', "Expected ')' after parameter list"))
        return;
    if (return_type == RETURN_RECORD && arity > 4u) {
        error_at(c, name, "Record-returning functions support up to four explicit parameters");
        return;
    }
    if (builtin && builtin != BUILTIN_MESSAGE && arity != 0) {
        error_at(c, name, "This Sidbox API takes no arguments");
        return;
    }

    int index = find_declaration(c, name, is_static);
    if (index < 0 && find_function(c, name) >= 0 &&
        c->functions[find_function(c, name)].unit == c->file_index) {
        error_at(c, name, "Conflicting static/external function declarations");
        return;
    }
    if (index < 0) {
        if (c->function_count == FUNCTION_LIMIT) {
            error_at(c, name, "Too many functions");
            return;
        }
        index = (int)c->function_count++;
        Function *fn = &c->functions[index];
        *fn = (Function){
            .name = name, .entry = builtin, .arity = (uint8_t)arity,
            .builtin = (uint8_t)builtin, .defined = builtin != 0u,
            .return_type = (uint8_t)return_type, .return_struct_id = (uint8_t)record_return_id,
            .is_static = (uint8_t)is_static, .unit = c->file_index
        };
        memcpy(fn->param_types, param_types, arity);
        memcpy(fn->param_struct_ids, param_struct_ids, arity);
    } else if (c->functions[index].arity != arity ||
               c->functions[index].return_type != return_type ||
               c->functions[index].return_struct_id != record_return_id ||
               memcmp(c->functions[index].param_types, param_types, arity) ||
               memcmp(c->functions[index].param_struct_ids, param_struct_ids, arity)) {
        error_at(c, name, "Function signature differs from its declaration");
        return;
    }

    if (accept(c, ';'))
        return;
    Function *fn = &c->functions[index];
    if (fn->defined) {
        error_at(c, name, "Function already defined");
        return;
    }
    if (!expect(c, '{', "Expected a function body or ';'"))
        return;
    fn->entry = c->pc;
    fn->defined = 1;
    c->local_count = c->local_peak = c->return_count = c->scope = 0;
    c->loop_depth = c->loop_jump_count = 0;
    c->control_depth = c->switch_break_count = c->switch_case_count = 0;
    c->return_type = fn->return_type;
    c->return_struct_id = fn->return_struct_id;
    c->return_buffer_slot = 0;

    emit(c, 0xb580);                                           /* push {r7, lr} */
    uint32_t frame = c->pc;
    emit(c, 0);
    emit(c, 0xaf00);                                           /* add r7, sp, #0 */
    uint32_t stack_arg = 0;
    unsigned return_extra = return_type == RETURN_RECORD ? 1u : 0u;
    if (return_extra) {
        Token hidden = {.text="__sidc_return_buffer",.length=20,.kind=TOK_NAME};
        c->return_buffer_slot = (uint8_t)add_local(c, hidden, LOCAL_PADDING);
        store_local(c, c->return_buffer_slot, 0);
    }
    unsigned parameter_slots[FUNCTION_PARAMS] = {0};
    for (unsigned i = 0; i < arity; ++i) {
        if (params[i].kind != TOK_NAME) {
            error_at(c, params[i], "Parameter needs a name in the function body");
            return;
        }
        unsigned record_words = param_types[i] == LOCAL_STRUCT ?
            c->structs[param_struct_ids[i]].size_words : 1u;
        if (!record_words || record_words > LOCAL_LIMIT - c->local_count) {
            error_at(c, params[i], "By-value struct parameters exceed 64 local words");
            return;
        }
        unsigned slot = add_local(c, params[i], param_types[i]);
        parameter_slots[i] = slot;
        if (param_types[i] == LOCAL_STRUCT || param_types[i] == LOCAL_STRUCT_POINTER ||
            param_types[i] == LOCAL_STRUCT_DOUBLE_POINTER)
            c->locals[slot].struct_id = param_struct_ids[i];
        for (unsigned j = 1; j < record_words; ++j)
            c->locals[c->local_count++] = (Local){.scope=0,.type=LOCAL_PADDING};
        if (c->local_count > c->local_peak) c->local_peak = c->local_count;
        unsigned reg = i + return_extra;
        if (i >= 4) {
            emit(c, 0xf8d7);                                   /* ldr.w r0, [r7, #frame+8] */
            stack_arg = c->pc;
            emit(c, 0);
            reg = 0;
        }
        if (param_types[i] == LOCAL_WINDOW)
            emit(c, (uint16_t)(0xb2c0 | (reg << 3) | reg));     /* uxtb Ri, Ri */
        store_local(c, slot, reg);
    }
    /* Save every incoming parameter before expanding by-value records: loads
       for a record must not overwrite a later argument in r0-r3. */
    for (unsigned i = 0; i < arity; ++i) {
        if (param_types[i] != LOCAL_STRUCT) continue;
        unsigned slot = parameter_slots[i];
        unsigned size = c->structs[param_struct_ids[i]].size_words;
        load_local(c, slot, 1); /* caller's source address */
        for (unsigned j = 0; j < size; ++j) {
            emit(c, 0xf8d1); emit(c, (uint16_t)(j * 4u)); /* ldr.w r0, [r1,#j*4] */
            store_local(c, slot + j, 0);
        }
    }
    block(c);
    if (c->return_type != RETURN_VOID)
        constant(c, 0);                                        /* fallthrough from main */
    uint32_t epilogue = c->pc;
    unsigned words = (c->local_peak + 1u) & ~1u;
    emit(c, (uint16_t)(0xb000 | words));                        /* add sp, #frame */
    emit(c, 0xbd80);                                           /* pop {r7, pc} */
    if (c->diagnostic.message)
        return;
    put16(frame, (uint16_t)(0xb080 | words));                   /* sub sp, #frame */
    if (stack_arg)
        put16(stack_arg, (uint16_t)((words + 2u) * 4u));
    for (unsigned i = 0; i < c->return_count; ++i)
        patch_branch(c, c->returns[i], epilogue, 0);
}

uint32_t sidc_compile_project(const SidcSource *sources,
                              const char *const *source_paths, uint32_t count,
                              SidcReadApiCore read_apicore,
                              SidcReadHeader read_header,
                              const void **app, SidcDiagnostic *diagnostic)
{
    Compiler *c = &compiler;
    *app = NULL;
    *diagnostic = (SidcDiagnostic){0};
    if (!sources || count == 0 || count > SIDC_MAX_SOURCES) {
        *diagnostic = (SidcDiagnostic){"Invalid number of source files", 1, 1, 0, NULL};
        return 0;
    }
    uint32_t total = 0;
    for (uint32_t i = 0; i < count; ++i) {
        if (!sources[i].source || sources[i].length > SIDC_SOURCE_LIMIT - total) {
            *diagnostic = (SidcDiagnostic){
                count == 1 ? "Source exceeds 128 KiB" : "Combined sources exceed 128 KiB",
                1, 1, i, NULL};
            return 0;
        }
        total += sources[i].length;
    }

    memset(c, 0, sizeof(*c));
    c->header_reader = read_header;
    c->api_reader = read_apicore;
    c->current_header = -1;
    memcpy(output.image, sidc_runtime, sizeof(sidc_runtime));
    c->pc = sizeof(sidc_runtime);
    for (uint32_t i = 0; i < count && !c->diagnostic.message; ++i) {
        c->file_index = (uint8_t)i;
        c->source = sources[i].source;
        c->active_path = source_paths ? source_paths[i] : NULL;
        c->current_header = -1;
        c->include_depth = 0;
        c->conditional_depth = 0;
        c->macro_count = 0;
        c->length = sources[i].length;
        c->pos = 0;
        c->line = c->column = 1;
        advance(c);
        advance(c);
        while (c->token.kind == TOK_APIS_INCLUDE && !c->diagnostic.message) {
            if (c->api.call_count == 0 && !load_apicore(c, read_apicore))
                break;
            advance(c);
        }
        while (!c->diagnostic.message && c->token.kind != TOK_END)
            external_declaration(c);
    }

    if (!c->diagnostic.message) {
        Token main_name = {.text = "main", .length = 4};
        int main_index = find_function(c, main_name);
        if (main_index < 0 || !c->functions[main_index].defined ||
            (c->functions[main_index].arity != 0 &&
             c->functions[main_index].param_types[1] != LOCAL_ARGV)) {
            error(c, "Define int main(void) or int main(int argc, char **argv)");
        } else {
            patch_branch(c, 0, c->functions[main_index].entry, 0);
        }
    }
    uint32_t alloc_entry = 0, free_entry = 0;
    if (c->heap_used && !c->diagnostic.message) {
        alloc_entry = c->pc;
        for (unsigned i = 0; i < sizeof(sidc_heap_alloc_code); i += 2)
            emit(c, (uint16_t)(sidc_heap_alloc_code[i] | ((uint16_t)sidc_heap_alloc_code[i+1] << 8)));
        free_entry = c->pc;
        for (unsigned i = 0; i < sizeof(sidc_heap_free_code); i += 2)
            emit(c, (uint16_t)(sidc_heap_free_code[i] | ((uint16_t)sidc_heap_free_code[i+1] << 8)));
    }
    for (unsigned i = 0; i < c->call_count && !c->diagnostic.message; ++i) {
        Reference call_ref = c->calls[i];
        if (call_ref.target == 0xfffeu || call_ref.target == 0xfffdu) {
            patch_branch(c, call_ref.at, call_ref.target == 0xfffeu ? alloc_entry : free_entry, 1);
            continue;
        }
        Function *fn = &c->functions[call_ref.target];
        if (!fn->defined)
            error_at(c, fn->name, "Called function has no definition");
        else
            patch_branch(c, call_ref.at, fn->entry, 1);
    }
    uint32_t strings_end = c->pc + c->string_bytes;
    uint32_t globals_at = (strings_end + 3u) & ~3u;
    uint32_t image_size = c->global_bytes ? globals_at + c->global_bytes : strings_end;
    uint32_t arrays_at = (image_size + SBV2_ALIGN - 1u) & ~(SBV2_ALIGN - 1u);
    if (image_size > IMAGE_LIMIT)
        error(c, "Native image and data exceed 64 KiB");

    uint32_t stack_bytes = 0;
    for (unsigned i = 0; i < c->address_count && !c->diagnostic.message; ++i) {
        AddressReference ref = c->addresses[i];
        uint32_t target;
        if (ref.kind == ADDRESS_STRING) {
            target = c->pc + ref.target;
        } else if (ref.kind == ADDRESS_GLOBAL) {
            const Global *global = &c->globals[ref.target];
            target = (!global->in_data &&
                      (global->type == GLOBAL_BYTE_ARRAY || global->type == GLOBAL_INT_ARRAY ||
                       global->type == GLOBAL_STRUCT || global->type == GLOBAL_STRUCT_ARRAY) ?
                      arrays_at : globals_at) + global->offset;
        } else {
            const Function *fn = &c->functions[ref.target];
            if (!fn->defined) {
                error_at(c, fn->name, "Callback function has no definition");
                break;
            }
            target = fn->entry | 1u;                          /* Thumb pointer */
            stack_bytes = CALLBACK_STACK_BYTES;
        }
        uint32_t delta = target - ((ref.at + 12u) & ~3u);
        unsigned reg = ref.kind == ADDRESS_GLOBAL ? 1u : 0u;
        wide_immediate(ref.at, 0xf240, reg, (uint16_t)delta);
        wide_immediate(ref.at + 4u, 0xf2c0, reg, (uint16_t)(delta >> 16));
    }
    if (c->diagnostic.message) {
        *diagnostic = c->diagnostic;
        return 0;
    }
    memcpy(output.image + c->pc, c->strings, c->string_bytes);
    uint32_t padded_size = (image_size + 3u) & ~3u;
    memset(output.image + strings_end, 0, padded_size - strings_end);
    for (unsigned i = 0; i < c->global_count; ++i) {
        const Global *global = &c->globals[i];
        if (global->in_data) {
            for (unsigned j = 0; j < global->init_count; ++j) {
                uint32_t value = c->initial_values[global->init_offset + j];
                if (global->type == GLOBAL_BYTE_ARRAY)
                    output.image[globals_at + global->offset + j] = (uint8_t)value;
                else
                    memcpy(output.image + globals_at + global->offset + 4u * j,
                           &value, sizeof(value));
            }
        } else if (global->type != GLOBAL_BYTE_ARRAY && global->type != GLOBAL_INT_ARRAY &&
                   global->type != GLOBAL_STRUCT && global->type != GLOBAL_STRUCT_ARRAY) {
            memcpy(output.image + globals_at + global->offset, &global->initial, sizeof(uint32_t));
        }
    }

    SBV2Header h = {0};
    memcpy(h.magic, SBV2_MAGIC_BYTES, sizeof(h.magic));
    h.version = SBV2_VERSION;
    h.header_size = SBV2_HEADER_SIZE;
    h.file_size = SBV2_HEADER_SIZE + padded_size;
    h.image_size = image_size;
    /* The V2 loader clears the arrays in RAM, so the file carries no zero-fill bytes. */
    uint32_t data_end = arrays_at + c->array_bytes;
    h.memory_size = ((data_end + SBV2_ALIGN - 1u) & ~(SBV2_ALIGN - 1u)) + stack_bytes;
    h.entry_offset = 1;                                       /* offset zero, Thumb bit set */
    h.link_base = 0xd0010000u;
    h.relocation_offset = h.file_size;
    h.alignment = SBV2_ALIGN;
    h.reserved = stack_bytes;
    h.flags = stack_bytes ? SBV2_FLAG_PRIVATE_PSP : 0u;
    h.image_crc32 = SBV2_CRC32(output.image, image_size);
    output.header = h;
    *app = &output;
    return h.file_size;
}

uint32_t sidc_compile_sources(const SidcSource *sources, uint32_t count,
                              SidcReadApiCore read_apicore,
                              const void **app, SidcDiagnostic *diagnostic)
{
    return sidc_compile_project(sources, NULL, count, read_apicore, NULL,
                                app, diagnostic);
}

uint32_t sidc_compile(const char *source, uint32_t length,
                      SidcReadApiCore read_apicore,
                      const void **app, SidcDiagnostic *diagnostic)
{
    const SidcSource input = {source, length};
    return sidc_compile_sources(&input, 1u, read_apicore, app, diagnostic);
}
