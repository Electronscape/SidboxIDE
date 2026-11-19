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
    TOK_SWITCH, TOK_CASE, TOK_DEFAULT,
    TOK_EQ, TOK_NE, TOK_LE, TOK_GE, TOK_AND, TOK_OR, TOK_ARROW,
    TOK_INC, TOK_DEC, TOK_ADD_ASSIGN, TOK_SUB_ASSIGN, TOK_SKIP
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
    CONTROL_LIMIT = 64
};

enum { BUILTIN_MESSAGE = 4, BUILTIN_TICKS = 8, BUILTIN_BUTTONS = 12 };
enum {
    LOCAL_INT, LOCAL_GADGET, LOCAL_POINTER, LOCAL_S32, LOCAL_ARGV, LOCAL_WINDOW, LOCAL_MESSAGE,
    GLOBAL_BYTE_ARRAY, GLOBAL_INT_ARRAY, LOCAL_INT_ARRAY, LOCAL_INT_POINTER, LOCAL_PADDING,
    LOCAL_FUNCTION_POINTER
};
enum { RETURN_INT, RETURN_VOID, RETURN_WINDOW, RETURN_INT_POINTER };
enum { VALUE_INT, VALUE_UNSIGNED, VALUE_VOID, VALUE_POINTER, VALUE_INT_POINTER };
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
    uint8_t param_types[FUNCTION_PARAMS];
} Function;

typedef struct {
    Token name;
    uint32_t initial;
    uint32_t offset;
    uint8_t type;
    uint8_t unit;
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
    FunctionPointerSignature callback;
} Local;

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
    uint32_t global_bytes;
    uint32_t array_bytes;
    Function functions[FUNCTION_LIMIT];
    unsigned function_count;
    Reference calls[CALL_LIMIT];
    unsigned call_count;
    uint32_t returns[RETURN_LIMIT];
    unsigned return_count;
    uint8_t return_type;
    Local locals[LOCAL_LIMIT];
    unsigned local_count;
    unsigned local_peak;
    unsigned scope;
    unsigned nesting;
    unsigned loop_depth;
    unsigned loop_jump_count;
    LoopJump loop_jumps[LOOP_JUMP_LIMIT];
    unsigned control_depth;
    uint8_t control_kind[CONTROL_LIMIT]; /* 1=loop, 2=switch */
    unsigned switch_break_count;
    uint32_t switch_breaks[SWITCH_BREAK_LIMIT];
    SwitchCase switch_cases[SWITCH_CASE_LIMIT];
    unsigned switch_case_count;
} Compiler;

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
            "int", "void", "extern", "const", "char", "if", "else", "while", "return", "static", "break", "continue", "for", "switch", "case", "default"
        };
        static const char *const reserved[] = {
            "auto", "do", "double",
            "enum", "float", "goto", "inline", "long", "register",
            "restrict", "short", "signed", "sizeof", "struct",
            "typedef", "union", "unsigned", "volatile", "_Alignas",
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
    if (next == '=' && (ch == '+' || ch == '-')) {
        read_char(c);
        token.kind = ch == '+' ? TOK_ADD_ASSIGN : TOK_SUB_ASSIGN;
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
    } else if (ch == 0 ||
               (ch == next && (ch == '<' || ch == '>')) ||
               (next == '=' && strchr("*/%&|^", (int)ch))) {
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

static int valid_api_name(const char name[SIDC_API_NAME])
{
    if (!letter((unsigned char)name[0]))
        return 0;
    for (unsigned i = 1; i < SIDC_API_NAME; ++i) {
        unsigned ch = (unsigned char)name[i];
        if (ch == 0)
            return 1;
        if (!letter(ch) && !digit(ch))
            return 0;
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
    int wide_calls = memcmp(header.magic, SIDC_APICORE_MAGIC, sizeof(header.magic)) == 0;
    int has_message = wide_calls || memcmp(header.magic, SIDC_APICORE_MAGIC_V2, sizeof(header.magic)) == 0;
    if ((!has_message && memcmp(header.magic, SIDC_APICORE_MAGIC_V1, sizeof(header.magic)) != 0) ||
        header.base != 0x2001f000u || header.call_count == 0 ||
        header.call_count > SIDC_API_CALLS || header.constant_count > SIDC_API_CONSTANTS)
        goto invalid;

    unsigned max_params = wide_calls ? SIDC_API_PARAMS : SIDC_API_PARAMS_V2;
    unsigned call_size = offsetof(SidcApiCall, params) + max_params;
    unsigned calls = header.call_count * call_size;
    unsigned constants = header.constant_count * sizeof(SidcApiConstant);
    unsigned message_at = sizeof(header) + calls + constants;
    if (payload != message_at + (has_message ? sizeof(SidcApiMessage) : 0))
        goto invalid;
    memcpy(c->api_constants, api_file + sizeof(header) + calls, constants);
    if (has_message) {
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
    unsigned last_param = wide_calls ? SIDC_API_BYTE_BUFFER
                        : has_message ? SIDC_API_WINDOW_REF : SIDC_API_TIMER_CALLBACK;
    for (unsigned i = 0; i < header.call_count; ++i) {
        SidcApiCall *call = &c->api_calls[i];
        memcpy(call, api_file + sizeof(header) + i * call_size, call_size);
        if (!valid_api_name(call->name) || call->arity > max_params ||
            (call->result != SIDC_API_U8 && call->result != SIDC_API_U32 &&
             call->result != SIDC_API_VOID && call->result != SIDC_API_S8 &&
             call->result != SIDC_API_S32))
            goto invalid;
        for (unsigned j = 0; j < SIDC_API_OFFSETS; ++j)
            if (call->offsets[j] > 4092 || (call->offsets[j] & 3u))
                goto invalid;
        for (unsigned j = 0; j < call->arity; ++j)
            if (call->params[j] < SIDC_API_NULL || call->params[j] > last_param ||
                call->params[j] == SIDC_API_VOID || call->params[j] == SIDC_API_S32)
                goto invalid;
        for (unsigned j = call->arity; j < SIDC_API_PARAMS; ++j)
            if (call->params[j] != 0)
                goto invalid;
    }
    for (unsigned i = 0; i < header.constant_count; ++i)
        if (!valid_api_name(c->api_constants[i].name))
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
    if (first.kind != TOK_STRING) {
        error(c, "Expected a string literal argument");
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

static int call(Compiler *c, Token name)
{
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
    if (fn->builtin == BUILTIN_MESSAGE) {
        string_argument(c);
    } else {
        for (unsigned i = 0; i < fn->arity && !c->diagnostic.message; ++i) {
            if (i != 0)
                expect(c, ',', "Expected ',' between arguments");
            uint8_t type = fn->param_types[i];
            if (type == LOCAL_INT_POINTER) {
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
        words = prepare_call(c, fn->arity);
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
    if (!allow_store || !accept(c, '=')) {
        emit(c, 0x5c08);                                      /* ldrb r0, [r1, r0] */
        return VALUE_INT;
    }

    emit(c, 0x1808);                                          /* adds r0, r1, r0 */
    emit(c, 0xb403);                                          /* push {r0, r1} */
    expression(c, 1, REQUIRE_INTEGER);
    emit(c, 0xbc06);                                          /* pop {r1, r2} */
    emit(c, 0x7008);                                          /* strb r0, [r1] */
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
    emit(c, 0x0080);                                         /* lsls r0, r0, #2 */
    emit(c, 0x1808);                                         /* adds r0, r1, r0 */
    if (address_only) return VALUE_INT_POINTER;
    if (allow_store && accept(c, '=')) {
        emit(c, 0xb403);                                     /* preserve address */
        expression(c, 1, REQUIRE_INTEGER);
        emit(c, 0xbc06);                                     /* address -> r1 */
        emit(c, 0x6008);                                     /* str r0, [r1] */
        return VALUE_VOID;
    }
    emit(c, 0x6800);                                         /* ldr r0, [r0] */
    return VALUE_INT;
}

static int increment_scalar(Compiler *c, Token name, int op, int postfix)
{
    int slot = find_local(c, name);
    int global = slot < 0 ? find_global(c, name) : -1;
    int type = slot >= 0 ? c->locals[slot].type
                         : global >= 0 ? c->globals[global].type : -1;
    if (type < 0 || type == GLOBAL_BYTE_ARRAY || type == GLOBAL_INT_ARRAY ||
        type == LOCAL_INT_ARRAY || type == LOCAL_PADDING || type == LOCAL_POINTER ||
        type == LOCAL_ARGV || type == LOCAL_MESSAGE || type == LOCAL_FUNCTION_POINTER) {
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
        if (accept(c, '(')) {
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
        if (slot >= 0 && (c->locals[slot].type == LOCAL_INT ||
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
            load_local(c, (unsigned)slot, 0);
            if (c->token.kind != '[') error_at(c, name, "Pointer-to-pointer requires int ** support");
            else type = int_pointer_element(c, 0, 1);
        } else {
            error_at(c, name, "Address-of needs an int variable or int array element");
        }
    } else if (accept(c, '*')) {
        type = unary(c, 0);
        if (type != VALUE_INT_POINTER) {
            error_at(c, token, "Dereferencing requires int *");
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
    case '+': case '-': return 8;
    case '*': case '/': case '%': return 9;
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
            if (type == VALUE_VOID || (type == VALUE_POINTER && !equality)) {
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
            } else if (left_ptr || right_ptr || type == VALUE_POINTER || rhs_type == VALUE_POINTER) {
                int lhs_null = (start.kind == TOK_NUMBER || start.kind == TOK_UNSIGNED_NUMBER) && start.number == 0;
                int rhs_null = (rhs_start.kind == TOK_NUMBER || rhs_start.kind == TOK_UNSIGNED_NUMBER) && rhs_start.number == 0;
                int compatible = (left_ptr && right_ptr) ||
                                 (type == VALUE_POINTER && rhs_type == VALUE_POINTER) ||
                                 (left_ptr && rhs_type == VALUE_POINTER) ||
                                 (right_ptr && type == VALUE_POINTER) ||
                                 (left_ptr && rhs_type == VALUE_INT && rhs_null) ||
                                 (right_ptr && type == VALUE_INT && lhs_null);
                if (!equality || !compatible)
                    error_at(c, start, "Pointer comparisons require compatible pointer values");
                binary(c, op, 1);
                type = VALUE_INT;
            } else {
                type = binary(c, op, type == VALUE_UNSIGNED || rhs_type == VALUE_UNSIGNED)
                    ? VALUE_UNSIGNED : VALUE_INT;
            }
        }
    }
    if ((requirement == REQUIRE_INTEGER || requirement == REQUIRE_SCALAR) && type == VALUE_VOID)
        error_at(c, start, "Expected an integer value, got void");
    if (requirement == REQUIRE_INTEGER && (type == VALUE_POINTER || type == VALUE_INT_POINTER))
        error_at(c, start, "Expected an integer value, got a pointer");
    if (requirement == REQUIRE_INT_POINTER && type != VALUE_INT_POINTER && type != VALUE_POINTER &&
        !((start.kind == TOK_NUMBER || start.kind == TOK_UNSIGNED_NUMBER) && start.number == 0))
        error_at(c, start, "Expected an int * expression or NULL");
    --c->nesting;
    return type;
}

static void statement(Compiler *c);

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
    if (accept(c, TOK_INT)) {
        if (c->token.kind == '(' && c->lookahead.kind == '*') {
            local_callback_declaration(c, RETURN_INT);
            return 1;
        }
        type = accept(c, '*') ? LOCAL_INT_POINTER : LOCAL_INT;
    } else if (accept(c, TOK_VOID)) {
        if (c->token.kind == '(' && c->lookahead.kind == '*')
            local_callback_declaration(c, RETURN_VOID);
        else error(c, "Only void function pointers are valid local declarations");
        return 1;
    } else if (c->token.kind == TOK_NAME && find_local(c, c->token) < 0) {
        if (accept_sdk_type(c, "CGGadget")) type = LOCAL_GADGET;
        else if (accept_sdk_type(c, "CGWindow") || accept_sdk_type(c, "uint8_t"))
            type = LOCAL_WINDOW;
    }
    if (type < 0) return 0;
    Token name = c->token;
    if (!expect(c, TOK_NAME, "Expected a local variable name")) return 1;
    if (accept(c, '[')) {
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
        for (unsigned i = 1; i < count; ++i) {
            c->locals[c->local_count++] = (Local){.scope = (uint8_t)c->scope, .type = LOCAL_PADDING};
        }
        if (c->local_count > c->local_peak) c->local_peak = c->local_count;
        if (accept(c, '=')) {
            if (!expect(c, '{', "Local array initializer supports only {0}")) return 1;
            if ((c->token.kind != TOK_NUMBER && c->token.kind != TOK_UNSIGNED_NUMBER) ||
                c->token.number != 0) {
                error(c, "Local array initializer supports only {0}");
                return 1;
            }
            advance(c);
            accept(c, ',');
            if (!expect(c, '}', "Local array initializer supports only {0}")) return 1;
            constant(c, 0);
            for (unsigned i = 0; i < count; ++i) store_local(c, slot + i, 0);
        }
        expect(c, ';', "Expected ';' after local array declaration");
        return 1;
    }
    unsigned slot = add_local(c, name, (uint8_t)type);
    if (accept(c, '=')) {
        expression(c, 1, type == LOCAL_INT_POINTER ? REQUIRE_INT_POINTER : REQUIRE_INTEGER);
        if (type == LOCAL_WINDOW) emit(c, 0xb2c0);
        store_local(c, slot, 0);
    }
    expect(c, ';', "Expected ';' after declaration");
    return 1;
}

/* A simple expression or assignment, without consuming its terminator.
   Supports for initializers/steps as well as ordinary statements. */
static void simple_expression(Compiler *c)
{
    int assignment = c->lookahead.kind == '=' ||
                     c->lookahead.kind == TOK_ADD_ASSIGN ||
                     c->lookahead.kind == TOK_SUB_ASSIGN;
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
    if (type == GLOBAL_BYTE_ARRAY || type == GLOBAL_INT_ARRAY || type == LOCAL_INT_ARRAY) {
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
    if (op == TOK_ADD_ASSIGN || op == TOK_SUB_ASSIGN) {
        if (slot >= 0) load_local(c, (unsigned)slot, 0);
        else {
            emit_address(c, ADDRESS_GLOBAL, (unsigned)global);
            emit(c, 0x6808);
        }
        emit(c, 0xb403);                                       /* push old {r0,r1} */
    }
    expression(c, 1, type == LOCAL_INT_POINTER && op == '=' ? REQUIRE_INT_POINTER : REQUIRE_INTEGER);
    if (op == TOK_ADD_ASSIGN || op == TOK_SUB_ASSIGN) {
        emit(c, 0xbc06);                                       /* pop old into r1 */
        if (type == LOCAL_INT_POINTER) emit(c, 0x0080);        /* pointer += n scales by 4 */
        emit(c, op == TOK_ADD_ASSIGN ? 0x1808 : 0x1a08);       /* add/sub */
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
        if (c->return_type != RETURN_VOID) {
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

static void global_declaration(Compiler *c, Token name, uint8_t type)
{
    int function = find_function(c, name);
    if (find_global(c, name) >= 0 ||
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
    if (accept(c, '=')) {
        if (type == GLOBAL_BYTE_ARRAY || type == GLOBAL_INT_ARRAY) {
            const char *message = "Static array initializer must be {0}";
            if (!expect(c, '{', message))
                return;
            if ((c->token.kind != TOK_NUMBER && c->token.kind != TOK_UNSIGNED_NUMBER) ||
                c->token.number != 0) {
                error(c, message);
                return;
            }
            advance(c);
            accept(c, ',');
            if (!expect(c, '}', message))
                return;
        } else {
            int negative = accept(c, '-');
            Token token = c->token;
            const SidcApiConstant *value = token.kind == TOK_NAME ? find_api_constant(c, token) : NULL;
            if (value)
                initial = value->value;
            else if (token.kind == TOK_NUMBER || token.kind == TOK_UNSIGNED_NUMBER)
                initial = token.number;
            else {
                error(c, "Static initializer needs an integer literal or SDK constant");
                return;
            }
            advance(c);
            if (negative)
                initial = 0u - initial;
        }
    }
    if (type == LOCAL_WINDOW)
        initial &= 0xffu;
    if (!expect(c, ';', "Expected ';' after static declaration"))
        return;
    uint32_t offset;
    if (type == GLOBAL_BYTE_ARRAY || type == GLOBAL_INT_ARRAY) {
        if (type == GLOBAL_INT_ARRAY) c->array_bytes = (c->array_bytes + 3u) & ~3u;
        offset = c->array_bytes;
        c->array_bytes += count;
    } else {
        offset = c->global_bytes;
        c->global_bytes += sizeof(initial);
    }
    c->globals[c->global_count++] = (Global){name, initial, offset, type, c->file_index};
}

static void external_declaration(Compiler *c)
{
    if (accept(c, TOK_APIS_INCLUDE)) {
        /* SDK header is a built-in marker; the real SDK signatures come from apis.bin. */
        if (c->api.call_count == 0)
            load_apicore(c, c->api_reader);
        return;
    }
    int is_static = accept(c, TOK_STATIC);
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
    else if (accept(c, TOK_INT)) {
        if (accept(c, '*')) return_type = RETURN_INT_POINTER;
    } else {
        error(c, "Expected a supported function or static variable type");
        return;
    }

    Token name = c->token;
    if (!expect(c, TOK_NAME, "Expected a declaration name"))
        return;
    if (is_static && return_type == RETURN_INT &&
        (variable_type != LOCAL_INT || c->token.kind != '(')) {
        global_declaration(c, name, (uint8_t)variable_type);
        return;
    }
    if (!expect(c, '(', "Expected '(' after function name"))
        return;
    if (find_global(c, name) >= 0) {
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
            } else if (accept(c, TOK_INT)) {
                param_types[arity] = accept(c, '*') ? LOCAL_INT_POINTER : LOCAL_INT;
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
            .return_type = (uint8_t)return_type,
            .is_static = (uint8_t)is_static, .unit = c->file_index
        };
        memcpy(fn->param_types, param_types, arity);
    } else if (c->functions[index].arity != arity ||
               c->functions[index].return_type != return_type ||
               memcmp(c->functions[index].param_types, param_types, arity)) {
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

    emit(c, 0xb580);                                           /* push {r7, lr} */
    uint32_t frame = c->pc;
    emit(c, 0);
    emit(c, 0xaf00);                                           /* add r7, sp, #0 */
    uint32_t stack_arg = 0;
    for (unsigned i = 0; i < arity; ++i) {
        if (params[i].kind != TOK_NAME) {
            error_at(c, params[i], "Parameter needs a name in the function body");
            return;
        }
        unsigned slot = add_local(c, params[i], param_types[i]);
        unsigned reg = i;
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
    for (unsigned i = 0; i < c->call_count && !c->diagnostic.message; ++i) {
        Reference call_ref = c->calls[i];
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
            target = ((global->type == GLOBAL_BYTE_ARRAY || global->type == GLOBAL_INT_ARRAY) ? arrays_at : globals_at) + global->offset;
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
        if (global->type != GLOBAL_BYTE_ARRAY && global->type != GLOBAL_INT_ARRAY)
            memcpy(output.image + globals_at + global->offset, &global->initial, sizeof(uint32_t));
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
