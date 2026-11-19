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
    TOK_IF, TOK_ELSE, TOK_WHILE, TOK_RETURN, TOK_STATIC, TOK_BREAK, TOK_CONTINUE,
    TOK_EQ, TOK_NE, TOK_LE, TOK_GE, TOK_AND, TOK_OR, TOK_ARROW
};

enum {
    /* The 128 KiB source is lexed in place: no full token array is needed. */
    IMAGE_LIMIT = 65536, STRING_LIMIT = 16384, LOCAL_LIMIT = 64,
    FUNCTION_LIMIT = 256, CALL_LIMIT = 2048, RETURN_LIMIT = 1024,
    ADDRESS_LIMIT = 2048, GLOBAL_LIMIT = 128, FUNCTION_PARAMS = 5,
    NESTING_LIMIT = 32, LOOP_LIMIT = 32, LOOP_JUMP_LIMIT = 512,
    CALLBACK_STACK_BYTES = 8192, BYTE_ARRAY_LIMIT = 256 * 1024
};

enum { BUILTIN_MESSAGE = 4, BUILTIN_TICKS = 8, BUILTIN_BUTTONS = 12 };
enum {
    LOCAL_INT, LOCAL_GADGET, LOCAL_POINTER, LOCAL_S32, LOCAL_ARGV, LOCAL_WINDOW, LOCAL_MESSAGE,
    GLOBAL_BYTE_ARRAY
};
enum { RETURN_INT, RETURN_VOID, RETURN_WINDOW };
enum { VALUE_INT, VALUE_UNSIGNED, VALUE_VOID, VALUE_POINTER };
enum { DISCARD_VALUE, REQUIRE_INTEGER, REQUIRE_SCALAR, STATEMENT_VALUE };
enum { ADDRESS_STRING, ADDRESS_GLOBAL, ADDRESS_FUNCTION };

typedef struct {
    const char *text;
    uint32_t length;
    uint32_t number;
    uint32_t line;
    uint32_t column;
    int kind;
    uint8_t file_index;
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
    Token name;
    uint8_t scope;
    uint8_t type;
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
    const char *source;
    uint32_t length;
    uint8_t file_index;
    uint32_t pos;
    uint32_t line;
    uint32_t column;
    Token token;
    Token lookahead;
    SidcDiagnostic diagnostic;
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
    c->diagnostic = (SidcDiagnostic){message, token.line, token.column, token.file_index};
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
        .column = c->column, .kind = TOK_END, .file_index = c->file_index
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

static unsigned escape_byte(Compiler *c, Token token, const char **p, const char *end);

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
            "int", "void", "extern", "const", "char", "if", "else", "while", "return", "static", "break", "continue"
        };
        static const char *const reserved[] = {
            "auto", "case", "default", "do", "double",
            "enum", "float", "for", "goto", "inline", "long", "register",
            "restrict", "short", "signed", "sizeof", "struct",
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
    if (next == '=' && (ch == '=' || ch == '!' || ch == '<' || ch == '>')) {
        read_char(c);
        token.kind = ch == '=' ? TOK_EQ : ch == '!' ? TOK_NE : ch == '<' ? TOK_LE : TOK_GE;
    } else if (ch == next && (ch == '&' || ch == '|')) {
        read_char(c);
        token.kind = ch == '&' ? TOK_AND : TOK_OR;
    } else if (ch == '-' && next == '>') {
        read_char(c);
        token.kind = TOK_ARROW;
    } else if (ch == 0 ||
               (ch == next && (ch == '+' || ch == '-' || ch == '<' || ch == '>')) ||
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
            if (type == LOCAL_POINTER || type == LOCAL_MESSAGE) {
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
    return fn->return_type == RETURN_VOID ? VALUE_VOID : VALUE_INT;
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
    } else if (accept(c, TOK_NAME)) {
        if (accept(c, '(')) {
            type = call(c, token);
        } else {
            int slot = find_local(c, token);
            const SidcApiConstant *value = find_api_constant(c, token);
            if (value)
                constant(c, value->value);
            else if (slot >= 0) {
                uint8_t local_type = c->locals[slot].type;
                if (local_type == LOCAL_POINTER || local_type == LOCAL_ARGV) {
                    error_at(c, token, "Pointer expressions are outside this C subset");
                } else {
                    load_local(c, (unsigned)slot, 0);
                    if (local_type == LOCAL_MESSAGE)
                        type = accept(c, TOK_ARROW) ? message_member(c) : VALUE_POINTER;
                    else
                        type = local_type == LOCAL_GADGET ? VALUE_UNSIGNED : VALUE_INT;
                }
            } else {
                int global = find_global(c, token);
                if (global >= 0) {
                    uint8_t global_type = c->globals[global].type;
                    if (global_type == GLOBAL_BYTE_ARRAY) {
                        type = byte_array_element(c, (unsigned)global, allow_store);
                    } else {
                        emit_address(c, ADDRESS_GLOBAL, (unsigned)global);
                        emit(c, 0x6808);                       /* ldr r0, [r1] */
                        type = global_type == LOCAL_GADGET ? VALUE_UNSIGNED : VALUE_INT;
                    }
                } else if (c->api.call_count && name_is(token, "NULL")) {
                    constant(c, 0);
                    type = VALUE_POINTER;
                } else {
                    error_at(c, token, "Unknown variable or SDK constant");
                }
            }
        }
    } else if (accept(c, '(')) {
        type = expression(c, 1, DISCARD_VALUE);
        expect(c, ')', "Expected ')'");
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
            if (type == VALUE_POINTER && !equality) {
                error_at(c, start, "Expected an integer operand, got a pointer");
                break;
            }
            emit(c, 0xb403);                                   /* push {r0, r1} */
            int rhs_type = expression(c, next_precedence, equality ? REQUIRE_SCALAR : REQUIRE_INTEGER);
            if (equality && (type == VALUE_POINTER) != (rhs_type == VALUE_POINTER))
                error_at(c, start, "Compare a message pointer with NULL or another message pointer");
            emit(c, 0xbc06);                                   /* pop {r1, r2} */
            type = binary(c, op, type == VALUE_UNSIGNED || rhs_type == VALUE_UNSIGNED)
                ? VALUE_UNSIGNED : VALUE_INT;
        }
    }
    if ((requirement == REQUIRE_INTEGER || requirement == REQUIRE_SCALAR) && type == VALUE_VOID)
        error_at(c, start, "Expected an integer value, got void");
    if (requirement == REQUIRE_INTEGER && type == VALUE_POINTER)
        error_at(c, start, "Expected an integer value, got a pointer");
    --c->nesting;
    return type;
}

static void statement(Compiler *c);

static void block(Compiler *c)
{
    while (!c->diagnostic.message && c->token.kind != '}' && c->token.kind != TOK_END) {
        int type = -1;
        if (accept(c, TOK_INT)) {
            type = LOCAL_INT;
        } else if (c->token.kind == TOK_NAME && find_local(c, c->token) < 0) {
            if (accept_sdk_type(c, "CGGadget"))
                type = LOCAL_GADGET;
            else if (accept_sdk_type(c, "CGWindow") || accept_sdk_type(c, "uint8_t"))
                type = LOCAL_WINDOW;
        }
        if (type >= 0) {
            Token name = c->token;
            if (!expect(c, TOK_NAME, "Expected a local variable name"))
                return;
            if (c->token.kind == '[') {
                error(c, "Only file-scope static uint8_t arrays are supported");
                return;
            }
            unsigned slot = add_local(c, name, (uint8_t)type);
            if (accept(c, '=')) {
                expression(c, 1, REQUIRE_INTEGER);
                if (type == LOCAL_WINDOW)
                    emit(c, 0xb2c0);                          /* uxtb r0, r0 */
                store_local(c, slot, 0);
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
            statement(c);
            --c->loop_depth;
            patch_branch(c, branch(c), repeat, 0);
            patch_branch(c, done, c->pc, 0);
            for (unsigned i = saved_jumps; i < c->loop_jump_count; ++i)
                patch_branch(c, c->loop_jumps[i].at,
                             c->loop_jumps[i].is_break ? c->pc : repeat, 0);
            c->loop_jump_count = saved_jumps;
        }
    } else if (c->token.kind == TOK_BREAK || c->token.kind == TOK_CONTINUE) {
        int is_break = c->token.kind == TOK_BREAK;
        if (!c->loop_depth) {
            error(c, is_break ? "break outside a loop" : "continue outside a loop");
        } else if (c->loop_jump_count == LOOP_JUMP_LIMIT) {
            error(c, "Too many loop breaks or continues");
        } else {
            advance(c);
            expect(c, ';', "Expected ';' after break or continue");
            c->loop_jumps[c->loop_jump_count++] = (LoopJump){branch(c), (uint8_t)is_break};
        }
    } else if (accept(c, TOK_RETURN)) {
        if (c->return_type != RETURN_VOID) {
            expression(c, 1, REQUIRE_INTEGER);
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
        if (c->token.kind == TOK_NAME && c->lookahead.kind == '=') {
            Token name = c->token;
            int slot = find_local(c, name);
            int global = slot < 0 ? find_global(c, name) : -1;
            int type = slot >= 0 ? c->locals[slot].type
                                : global >= 0 ? c->globals[global].type : -1;
            if (type < 0) {
                error_at(c, name, "Assignment needs a declared variable");
            } else if (type == GLOBAL_BYTE_ARRAY) {
                error_at(c, name, "Assign to a single byte array element");
            } else if (type == LOCAL_POINTER || type == LOCAL_ARGV || type == LOCAL_MESSAGE) {
                error_at(c, name, "Pointer assignment is outside this C subset");
            } else {
                advance(c);
                advance(c);
                expression(c, 1, REQUIRE_INTEGER);
                if (type == LOCAL_WINDOW)
                    emit(c, 0xb2c0);                          /* uxtb r0, r0 */
                if (slot >= 0) {
                    store_local(c, (unsigned)slot, 0);
                } else {
                    emit_address(c, ADDRESS_GLOBAL, (unsigned)global);
                    emit(c, 0x6008);                           /* str r0, [r1] */
                }
            }
        } else {
            expression(c, 1, STATEMENT_VALUE);
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
        if (type != LOCAL_WINDOW) {
            error_at(c, name, "Only file-scope static uint8_t arrays are supported");
            return;
        }
        Token bound = c->token;
        if ((bound.kind != TOK_NUMBER && bound.kind != TOK_UNSIGNED_NUMBER) || bound.number == 0) {
            error_at(c, bound, "Byte array size needs a positive integer literal");
            return;
        }
        count = bound.number;
        if (count > BYTE_ARRAY_LIMIT - c->array_bytes) {
            error_at(c, bound, "Static byte arrays exceed 256 KiB");
            return;
        }
        advance(c);
        if (!expect(c, ']', "Expected ']' after the byte array size"))
            return;
        type = GLOBAL_BYTE_ARRAY;
    }
    uint32_t initial = 0;
    if (accept(c, '=')) {
        if (type == GLOBAL_BYTE_ARRAY) {
            const char *message = "Byte array initializer must be {0}";
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
    if (type == GLOBAL_BYTE_ARRAY) {
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
    else if (!expect(c, TOK_INT, "Expected a supported function or static variable type"))
        return;

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
                param_types[arity] = LOCAL_INT;
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

uint32_t sidc_compile_sources(const SidcSource *sources, uint32_t count,
                              SidcReadApiCore read_apicore,
                              const void **app, SidcDiagnostic *diagnostic)
{
    Compiler *c = &compiler;
    *app = NULL;
    *diagnostic = (SidcDiagnostic){0};
    if (!sources || count == 0 || count > SIDC_MAX_SOURCES) {
        *diagnostic = (SidcDiagnostic){"Invalid number of source files", 1, 1, 0};
        return 0;
    }
    uint32_t total = 0;
    for (uint32_t i = 0; i < count; ++i) {
        if (!sources[i].source || sources[i].length > SIDC_SOURCE_LIMIT - total) {
            *diagnostic = (SidcDiagnostic){
                count == 1 ? "Source exceeds 128 KiB" : "Combined sources exceed 128 KiB",
                1, 1, i};
            return 0;
        }
        total += sources[i].length;
    }

    memset(c, 0, sizeof(*c));
    memcpy(output.image, sidc_runtime, sizeof(sidc_runtime));
    c->pc = sizeof(sidc_runtime);
    for (uint32_t i = 0; i < count && !c->diagnostic.message; ++i) {
        c->file_index = (uint8_t)i;
        c->source = sources[i].source;
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
            target = (global->type == GLOBAL_BYTE_ARRAY ? arrays_at : globals_at) + global->offset;
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
        if (global->type != GLOBAL_BYTE_ARRAY)
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

uint32_t sidc_compile(const char *source, uint32_t length,
                      SidcReadApiCore read_apicore,
                      const void **app, SidcDiagnostic *diagnostic)
{
    const SidcSource input = {source, length};
    return sidc_compile_sources(&input, 1u, read_apicore, app, diagnostic);
}
