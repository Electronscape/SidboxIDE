#include "compiler.h"
#include "apicore.h"
#include "applet_v2_format.h"
#include "generated_runtime.h"

#include <string.h>

enum {
    TOK_END = 256, TOK_NAME, TOK_NUMBER, TOK_UNSIGNED_NUMBER, TOK_STRING,
    TOK_UNSUPPORTED, TOK_APIS_INCLUDE,
    TOK_INT, TOK_VOID, TOK_EXTERN, TOK_CONST, TOK_CHAR,
    TOK_IF, TOK_ELSE, TOK_WHILE, TOK_RETURN,
    TOK_EQ, TOK_NE, TOK_LE, TOK_GE, TOK_AND, TOK_OR
};

enum {
    IMAGE_LIMIT = 24576, STRING_LIMIT = 4096, LOCAL_LIMIT = 32,
    FUNCTION_LIMIT = 48, CALL_LIMIT = 384, RETURN_LIMIT = 128,
    STRING_REF_LIMIT = 96, NESTING_LIMIT = 24
};

enum { BUILTIN_MESSAGE = 4, BUILTIN_TICKS = 8, BUILTIN_BUTTONS = 12 };
enum { LOCAL_INT, LOCAL_GADGET, LOCAL_POINTER };

typedef struct {
    const char *text;
    uint32_t length;
    uint32_t number;
    uint16_t line;
    uint16_t column;
    int kind;
} Token;

typedef struct {
    Token name;
    uint32_t entry;
    uint8_t arity;
    uint8_t builtin;
    uint8_t defined;
    uint8_t argc_argv;
} Function;

typedef struct {
    Token name;
    uint8_t scope;
    uint8_t type;
} Local;

typedef struct {
    uint32_t at;
    uint16_t target;
} Reference;

typedef struct {
    const char *source;
    uint32_t length;
    uint32_t pos;
    uint16_t line;
    uint16_t column;
    Token token;
    Token lookahead;
    SidcDiagnostic diagnostic;
    SidcApiHeader api;
    SidcApiCall api_calls[SIDC_API_CALLS];
    SidcApiConstant api_constants[SIDC_API_CONSTANTS];

    uint32_t pc;
    uint32_t string_bytes;
    uint8_t strings[STRING_LIMIT];
    Reference string_refs[STRING_REF_LIMIT];
    unsigned string_ref_count;
    Function functions[FUNCTION_LIMIT];
    unsigned function_count;
    Reference calls[CALL_LIMIT];
    unsigned call_count;
    uint32_t returns[RETURN_LIMIT];
    unsigned return_count;
    Local locals[LOCAL_LIMIT];
    unsigned local_count;
    unsigned local_peak;
    unsigned scope;
    unsigned nesting;
} Compiler;

static Compiler compiler;
static struct {
    SBV2Header header;
    uint8_t image[IMAGE_LIMIT];
} output;
static uint8_t api_file[sizeof(SidcApiHeader) + SIDC_API_CALLS * sizeof(SidcApiCall) +
                        SIDC_API_CONSTANTS * sizeof(SidcApiConstant) + sizeof(uint32_t)];

static void error_at(Compiler *c, Token token, const char *message)
{
    if (c->diagnostic.message)
        return;
    c->diagnostic = (SidcDiagnostic){message, token.line, token.column};
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
        .column = c->column, .kind = TOK_END
    };
}

static Token scan_include(Compiler *c, Token token)
{
    while (peek(c, 0) == ' ' || peek(c, 0) == '\t')
        read_char(c);
    static const char directive[] = "include";
    for (unsigned i = 0; i < sizeof(directive) - 1u; ++i) {
        if (read_char(c) != (unsigned char)directive[i]) {
            error_at(c, token, "Expected #include \"apis.h\"");
            return here(c);
        }
    }
    while (peek(c, 0) == ' ' || peek(c, 0) == '\t')
        read_char(c);
    unsigned open = read_char(c);
    unsigned close = open == '<' ? '>' : '"';
    static const char header[] = "apis.h";
    if (open == '"' || open == '<') {
        unsigned i = 0;
        while (i < sizeof(header) - 1u && peek(c, 0) == (unsigned char)header[i]) {
            read_char(c);
            ++i;
        }
        if (i == sizeof(header) - 1u && read_char(c) == close) {
            while (peek(c, 0) == ' ' || peek(c, 0) == '\t')
                read_char(c);
            unsigned next = peek(c, 0);
            if (c->pos == c->length || next == '\r' || next == '\n' ||
                (next == '/' && peek(c, 1) == '/')) {
                token.kind = TOK_APIS_INCLUDE;
                return token;
            }
        }
    }
    error_at(c, token, "Expected #include \"apis.h\" on its own line");
    return here(c);
}

static Token scan(Compiler *c)
{
    if (c->diagnostic.message)
        return here(c);

    for (;;) {
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

    Token token = here(c);
    if (c->pos == c->length)
        return token;

    unsigned ch = read_char(c);
    if (ch == '#')
        return scan_include(c, token);
    if (letter(ch)) {
        while (letter(peek(c, 0)) || digit(peek(c, 0)))
            read_char(c);
        token.length = (uint32_t)(c->source + c->pos - token.text);
        static const char *const keywords[] = {
            "int", "void", "extern", "const", "char", "if", "else", "while", "return"
        };
        static const char *const reserved[] = {
            "auto", "break", "case", "continue", "default", "do", "double",
            "enum", "float", "for", "goto", "inline", "long", "register",
            "restrict", "short", "signed", "sizeof", "static", "struct",
            "switch", "typedef", "union", "unsigned", "volatile", "_Alignas",
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
    if (ch == '"') {
        token.text = c->source + c->pos;
        while (c->pos != c->length) {
            unsigned part = read_char(c);
            if (part == '"') {
                token.length = (uint32_t)(c->source + c->pos - 1 - token.text);
                token.kind = TOK_STRING;
                return token;
            }
            if (part == '\\')
                part = read_char(c);
            if (part == 0 || part == '\n' || part == '\r')
                break;
        }
        error_at(c, token, "Unclosed string literal");
        return here(c);
    }

    unsigned next = peek(c, 0);
    token.kind = (int)ch;
    if (next == '=' && (ch == '=' || ch == '!' || ch == '<' || ch == '>')) {
        read_char(c);
        token.kind = ch == '=' ? TOK_EQ : ch == '!' ? TOK_NE : ch == '<' ? TOK_LE : TOK_GE;
    } else if (ch == next && (ch == '&' || ch == '|')) {
        read_char(c);
        token.kind = ch == '&' ? TOK_AND : TOK_OR;
    } else if (ch == 0 || ch == '\'' ||
               (ch == next && (ch == '+' || ch == '-' || ch == '<' || ch == '>')) ||
               (ch == '-' && next == '>') ||
               (next == '=' && strchr("+-*/%&|^", (int)ch))) {
        error_at(c, token, "Token outside the supported C subset");
        token.kind = TOK_UNSUPPORTED;
    }
    return token;
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
        error(c, "Native image exceeds 24 KiB");
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
    if (memcmp(header.magic, SIDC_APICORE_MAGIC, sizeof(header.magic)) != 0 ||
        header.base != 0x2001f000u || header.call_count == 0 ||
        header.call_count > SIDC_API_CALLS || header.constant_count > SIDC_API_CONSTANTS)
        goto invalid;

    unsigned calls = header.call_count * sizeof(SidcApiCall);
    unsigned constants = header.constant_count * sizeof(SidcApiConstant);
    if (payload != sizeof(header) + calls + constants)
        goto invalid;
    memcpy(c->api_calls, api_file + sizeof(header), calls);
    memcpy(c->api_constants, api_file + sizeof(header) + calls, constants);
    for (unsigned i = 0; i < header.call_count; ++i) {
        const SidcApiCall *call = &c->api_calls[i];
        if (!valid_api_name(call->name) || call->arity > SIDC_API_PARAMS ||
            (call->result != SIDC_API_U8 && call->result != SIDC_API_U32) || call->reserved)
            goto invalid;
        for (unsigned j = 0; j < SIDC_API_OFFSETS; ++j)
            if (call->offsets[j] > 4092 || (call->offsets[j] & 3u))
                goto invalid;
        for (unsigned j = 0; j < call->arity; ++j)
            if (call->params[j] < SIDC_API_NULL || call->params[j] > SIDC_API_U8)
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
    /* Thumb-2 B.W or BL. The image limit keeps every displacement in range. */
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
    for (unsigned i = 0; i < c->function_count; ++i)
        if (same_name(c->functions[i].name, name))
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
    c->locals[next] = (Local){name, (uint8_t)c->scope, type};
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
                error_at(c, token, "String escape exceeds one byte");
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
    error_at(c, token, "Invalid or unsupported string escape");
    return 0;
}

static void string_argument(Compiler *c)
{
    Token first = c->token;
    if (first.kind != TOK_STRING) {
        error(c, "Expected a string literal argument");
        return;
    }
    if (c->string_ref_count == STRING_REF_LIMIT) {
        error(c, "Too many string references");
        return;
    }
    if (c->string_bytes == STRING_LIMIT) {
        error(c, "String data exceeds 4 KiB");
        return;
    }
    unsigned start = c->string_bytes;
    do {
        Token token = c->token;
        const char *p = token.text;
        const char *end = p + token.length;
        while (p != end) {
            if (c->string_bytes + 1u >= STRING_LIMIT) {
                error_at(c, token, "String data exceeds 4 KiB");
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

    c->string_refs[c->string_ref_count++] = (Reference){c->pc, (uint16_t)start};
    for (unsigned i = 0; i < 4; ++i)
        emit(c, 0);                                            /* movw/movt r0, delta */
    emit(c, 0xa100);                                           /* adr r1, #0 */
    emit(c, 0x1808);                                           /* adds r0, r1, r0 */
}

/* Returns whether the expression produced an unsigned 32-bit value in r0. */
static int expression(Compiler *c, int minimum);

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
            if (((c->token.kind == TOK_NUMBER || c->token.kind == TOK_UNSIGNED_NUMBER) &&
                 c->token.number == 0) ||
                (c->token.kind == TOK_NAME && name_is(c->token, "NULL"))) {
                advance(c);
                constant(c, 0);
            } else {
                error(c, "This pointer argument supports NULL");
            }
            break;
        default:
            expression(c, 1);
            switch (api->params[i]) {
            case SIDC_API_S16: emit(c, 0xb200); break;          /* sxth r0, r0 */
            case SIDC_API_U16: emit(c, 0xb280); break;          /* uxth r0, r0 */
            case SIDC_API_U8:  emit(c, 0xb2c0); break;          /* uxtb r0, r0 */
            }
            break;
        }
        emit(c, 0xb403);                                       /* push {r0, r1} */
    }
    if (!expect(c, ')', "Wrong SDK argument count or missing ')'"))
        return;

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

    load_constant(c, 12, c->api.base);
    for (unsigned i = 0; i < SIDC_API_OFFSETS; ++i) {
        emit(c, 0xf8dc);                                      /* ldr.w ip, [ip, #offset] */
        emit(c, (uint16_t)(0xc000 | api->offsets[i]));
    }
    emit(c, 0x47e0);                                          /* blx ip */
    if (arity != 0)
        emit(c, (uint16_t)(0xb000 | (stack_words + 2u * arity)));
    if (api->result == SIDC_API_U8)
        emit(c, 0xb2c0);                                      /* promote uint8_t to int */
}

static int call(Compiler *c, Token name)
{
    const SidcApiCall *api = find_api_call(c, name);
    if (api) {
        api_call(c, api);
        return api->result == SIDC_API_U32;
    }
    int index = find_function(c, name);
    if (index < 0 || find_local(c, name) >= 0) {
        error_at(c, name, "Call needs a visible function declaration");
        return 0;
    }
    Function *fn = &c->functions[index];
    if (fn->argc_argv) {
        error_at(c, name, "The Sidbox loader supplies main's arguments");
        return 0;
    }
    if (fn->builtin == BUILTIN_MESSAGE) {
        string_argument(c);
    } else {
        for (unsigned i = 0; i < fn->arity && !c->diagnostic.message; ++i) {
            if (i != 0)
                expect(c, ',', "Expected ',' between arguments");
            expression(c, 1);
            emit(c, 0xb403);                                   /* push {r0, r1} */
        }
        for (unsigned i = 0; i < fn->arity; ++i)
            emit(c, (uint16_t)(0x9800 | (i << 8) | (2 * (fn->arity - 1 - i))));
        if (fn->arity != 0)
            emit(c, (uint16_t)(0xb000 | (fn->arity * 2)));      /* discard saved args */
    }
    if (!expect(c, ')', "Wrong argument count or missing ')'"))
        return 0;
    if (c->call_count == CALL_LIMIT) {
        error_at(c, name, "Too many function calls");
        return 0;
    }
    c->calls[c->call_count++] = (Reference){branch(c), (uint16_t)index};
    return 0;
}

static int unary(Compiler *c)
{
    Token token = c->token;
    int unsigned_word = 0;
    if (c->diagnostic.message)
        return 0;
    if (++c->nesting > NESTING_LIMIT) {
        error(c, "Expression or block nesting is too deep");
    } else if (accept(c, TOK_NUMBER) || accept(c, TOK_UNSIGNED_NUMBER)) {
        constant(c, token.number);
        unsigned_word = token.kind == TOK_UNSIGNED_NUMBER;
    } else if (accept(c, TOK_NAME)) {
        if (accept(c, '(')) {
            unsigned_word = call(c, token);
        } else {
            int slot = find_local(c, token);
            const SidcApiConstant *value = find_api_constant(c, token);
            if (value)
                constant(c, value->value);
            else if (slot < 0)
                error_at(c, token, "Unknown local variable or SDK constant");
            else if (c->locals[slot].type == LOCAL_POINTER)
                error_at(c, token, "Pointer expressions are outside this C subset");
            else {
                emit(c, (uint16_t)(0x6838 | ((unsigned)slot << 6)));
                unsigned_word = c->locals[slot].type == LOCAL_GADGET;
            }
        }
    } else if (accept(c, '(')) {
        unsigned_word = expression(c, 1);
        expect(c, ')', "Expected ')'");
    } else if (accept(c, '+') || accept(c, '-') || accept(c, '!') || accept(c, '~')) {
        unsigned_word = unary(c);
        if (token.kind == '-')
            emit(c, 0x4240);                                   /* rsbs r0, r0, #0 */
        else if (token.kind == '~')
            emit(c, 0x43c0);                                   /* mvns r0, r0 */
        else if (token.kind == '!') {
            emit(c, 0x2800);
            boolean(c, 0);                                    /* eq */
            unsigned_word = 0;
        }
    } else {
        error(c, "Expected an integer expression");
    }
    --c->nesting;
    return unsigned_word;
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

static int expression(Compiler *c, int minimum)
{
    if (++c->nesting > NESTING_LIMIT)
        error(c, "Expression or block nesting is too deep");
    int unsigned_word = unary(c);
    while (!c->diagnostic.message && precedence(c->token.kind) >= minimum) {
        int op = c->token.kind;
        int next_precedence = precedence(op) + 1;
        advance(c);
        if (op == TOK_AND || op == TOK_OR) {
            uint32_t short_circuit = branch_on_value(c, op == TOK_OR);
            expression(c, next_precedence);
            emit(c, 0x2800);
            boolean(c, 1);                                    /* ne */
            uint32_t done = branch(c);
            patch_branch(c, short_circuit, c->pc, 0);
            constant(c, op == TOK_OR);
            patch_branch(c, done, c->pc, 0);
            unsigned_word = 0;
        } else {
            emit(c, 0xb403);                                   /* push {r0, r1} */
            int rhs_unsigned = expression(c, next_precedence);
            emit(c, 0xbc06);                                   /* pop {r1, r2} */
            unsigned_word = binary(c, op, unsigned_word || rhs_unsigned);
        }
    }
    --c->nesting;
    return unsigned_word;
}

static void statement(Compiler *c);

static void block(Compiler *c)
{
    while (!c->diagnostic.message && c->token.kind != '}' && c->token.kind != TOK_END) {
        int gadget = c->api.call_count && c->token.kind == TOK_NAME &&
            name_is(c->token, "CGGadget") && find_local(c, c->token) < 0;
        if (gadget || accept(c, TOK_INT)) {
            if (gadget)
                advance(c);
            Token name = c->token;
            if (!expect(c, TOK_NAME, "Expected a local variable name"))
                return;
            unsigned slot = add_local(c, name, gadget ? LOCAL_GADGET : LOCAL_INT);
            if (accept(c, '=')) {
                expression(c, 1);
                emit(c, (uint16_t)(0x6038 | (slot << 6)));
            }
            expect(c, ';', "Expected ';' after declaration");
        } else {
            statement(c);
        }
    }
    expect(c, '}', "Expected '}' at end of block");
}

static void condition(Compiler *c)
{
    expect(c, '(', "Expected '(' before condition");
    expression(c, 1);
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
        uint32_t repeat = c->pc;
        condition(c);
        uint32_t done = branch_on_value(c, 0);
        statement(c);
        patch_branch(c, branch(c), repeat, 0);
        patch_branch(c, done, c->pc, 0);
    } else if (accept(c, TOK_RETURN)) {
        expression(c, 1);
        expect(c, ';', "Expected ';' after return");
        if (c->return_count == RETURN_LIMIT)
            error(c, "Too many returns in one function");
        else
            c->returns[c->return_count++] = branch(c);
    } else if (!accept(c, ';')) {
        if (c->token.kind == TOK_NAME && c->lookahead.kind == '=') {
            Token name = c->token;
            int slot = find_local(c, name);
            if (slot < 0) {
                error_at(c, name, "Assignment needs a declared local variable");
            } else if (c->locals[slot].type == LOCAL_POINTER) {
                error_at(c, name, "Pointer assignment is outside this C subset");
            } else {
                advance(c);
                advance(c);
                expression(c, 1);
                emit(c, (uint16_t)(0x6038 | ((unsigned)slot << 6)));
            }
        } else {
            expression(c, 1);
        }
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

static void function(Compiler *c)
{
    accept(c, TOK_EXTERN);
    if (!expect(c, TOK_INT, "Expected an int function declaration"))
        return;
    Token name = c->token;
    if (!expect(c, TOK_NAME, "Expected a function name") ||
        !expect(c, '(', "Expected '(' after function name"))
        return;

    unsigned builtin = builtin_entry(name);
    unsigned arity = 0;
    uint8_t argc_argv = 0;
    Token params[4];
    if (builtin == BUILTIN_MESSAGE) {
        if (!expect(c, TOK_CONST, "Expected 'const char *' for sidbox_message") ||
            !expect(c, TOK_CHAR, "Expected 'const char *' for sidbox_message") ||
            !expect(c, '*', "Expected 'const char *' for sidbox_message"))
            return;
        accept(c, TOK_NAME);
        arity = 1;
    } else if (!accept(c, TOK_VOID)) {
        do {
            if (arity == 4) {
                error(c, "A function can have up to four int parameters");
                return;
            }
            if (arity == 1 && name_is(name, "main") && accept(c, TOK_CHAR)) {
                if (!expect(c, '*', "Expected char ** for main's second parameter") ||
                    !expect(c, '*', "Expected char ** for main's second parameter"))
                    return;
                argc_argv = 1;
            } else if (!expect(c, TOK_INT, "Expected an int parameter or 'void'")) {
                return;
            }
            params[arity++] = c->token;
            accept(c, TOK_NAME);
        } while (!argc_argv && accept(c, ','));
    }
    if (!expect(c, ')', "Expected ')' after parameter list"))
        return;
    if (builtin && builtin != BUILTIN_MESSAGE && arity != 0) {
        error_at(c, name, "This Sidbox API takes no arguments");
        return;
    }

    int index = find_function(c, name);
    if (index < 0) {
        if (c->function_count == FUNCTION_LIMIT) {
            error_at(c, name, "Too many functions");
            return;
        }
        index = (int)c->function_count++;
        c->functions[index] = (Function){name, builtin, (uint8_t)arity,
                                         (uint8_t)builtin, builtin != 0u, argc_argv};
    } else if (c->functions[index].arity != arity ||
               c->functions[index].argc_argv != argc_argv) {
        error_at(c, name, "Function parameters differ from its declaration");
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

    emit(c, 0xb580);                                           /* push {r7, lr} */
    uint32_t frame = c->pc;
    emit(c, 0);
    emit(c, 0xaf00);                                           /* add r7, sp, #0 */
    for (unsigned i = 0; i < arity; ++i) {
        if (params[i].kind != TOK_NAME) {
            error_at(c, params[i], "Parameter needs a name in the function body");
            return;
        }
        unsigned slot = add_local(c, params[i], argc_argv && i == 1 ? LOCAL_POINTER : LOCAL_INT);
        emit(c, (uint16_t)(0x6038 | (slot << 6) | i));
    }
    block(c);
    constant(c, 0);                                           /* fallthrough from main */
    uint32_t epilogue = c->pc;
    unsigned words = (c->local_peak + 1u) & ~1u;
    emit(c, (uint16_t)(0xb000 | words));                        /* add sp, #frame */
    emit(c, 0xbd80);                                           /* pop {r7, pc} */
    if (c->diagnostic.message)
        return;
    put16(frame, (uint16_t)(0xb080 | words));                   /* sub sp, #frame */
    for (unsigned i = 0; i < c->return_count; ++i)
        patch_branch(c, c->returns[i], epilogue, 0);
}

uint32_t sidc_compile(const char *source, uint32_t length,
                      SidcReadApiCore read_apicore,
                      const void **app, SidcDiagnostic *diagnostic)
{
    Compiler *c = &compiler;
    *app = NULL;
    *diagnostic = (SidcDiagnostic){0};
    if (length > SIDC_SOURCE_LIMIT) {
        *diagnostic = (SidcDiagnostic){"Source exceeds 8 KiB", 1, 1};
        return 0;
    }

    memset(c, 0, sizeof(*c));
    c->source = source;
    c->length = length;
    c->line = c->column = 1;
    memcpy(output.image, sidc_runtime, sizeof(sidc_runtime));
    c->pc = sizeof(sidc_runtime);
    advance(c);
    advance(c);
    while (c->token.kind == TOK_APIS_INCLUDE && !c->diagnostic.message) {
        if (c->api.call_count == 0 && !load_apicore(c, read_apicore))
            break;
        advance(c);
    }
    while (!c->diagnostic.message && c->token.kind != TOK_END)
        function(c);

    if (!c->diagnostic.message) {
        Token main_name = {.text = "main", .length = 4};
        int main_index = find_function(c, main_name);
        if (main_index < 0 || !c->functions[main_index].defined ||
            (c->functions[main_index].arity != 0 && !c->functions[main_index].argc_argv)) {
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
    if (c->pc + c->string_bytes > IMAGE_LIMIT)
        error(c, "Native image and strings exceed 24 KiB");
    if (c->diagnostic.message) {
        *diagnostic = c->diagnostic;
        return 0;
    }
    for (unsigned i = 0; i < c->string_ref_count; ++i) {
        Reference ref = c->string_refs[i];
        uint32_t adr_pc = (ref.at + 12u) & ~3u;
        uint32_t delta = c->pc + ref.target - adr_pc;
        wide_immediate(ref.at, 0xf240, 0, (uint16_t)delta);
        wide_immediate(ref.at + 4u, 0xf2c0, 0, (uint16_t)(delta >> 16));
    }
    memcpy(output.image + c->pc, c->strings, c->string_bytes);
    uint32_t image_size = c->pc + c->string_bytes;
    uint32_t padded_size = (image_size + 3u) & ~3u;
    memset(output.image + image_size, 0, padded_size - image_size);

    SBV2Header h = {0};
    memcpy(h.magic, SBV2_MAGIC_BYTES, sizeof(h.magic));
    h.version = SBV2_VERSION;
    h.header_size = SBV2_HEADER_SIZE;
    h.file_size = SBV2_HEADER_SIZE + padded_size;
    h.image_size = image_size;
    h.memory_size = (image_size + SBV2_ALIGN - 1u) & ~(SBV2_ALIGN - 1u);
    h.entry_offset = 1;                                       /* offset zero, Thumb bit set */
    h.link_base = 0xd0010000u;
    h.relocation_offset = h.file_size;
    h.alignment = SBV2_ALIGN;
    h.image_crc32 = SBV2_CRC32(output.image, image_size);
    output.header = h;
    *app = &output;
    return h.file_size;
}
