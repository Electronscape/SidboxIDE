#include "csyntaxhighlighter.h"

#include <QColor>
#include <QFont>
#include <QStringList>
#include <QTextDocument>
#include <QTimer>

namespace {
const QSet<QString> &cKeywordSet()
{
    static const QSet<QString> keywords = {
        QStringLiteral("auto"),
        QStringLiteral("break"),
        QStringLiteral("case"),
        QStringLiteral("char"),
        QStringLiteral("const"),
        QStringLiteral("continue"),
        QStringLiteral("default"),
        QStringLiteral("do"),
        QStringLiteral("double"),
        QStringLiteral("else"),
        QStringLiteral("enum"),
        QStringLiteral("extern"),
        QStringLiteral("float"),
        QStringLiteral("for"),
        QStringLiteral("goto"),
        QStringLiteral("if"),
        QStringLiteral("inline"),
        QStringLiteral("int"),
        QStringLiteral("long"),
        QStringLiteral("register"),
        QStringLiteral("restrict"),
        QStringLiteral("return"),
        QStringLiteral("short"),
        QStringLiteral("signed"),
        QStringLiteral("sizeof"),
        QStringLiteral("static"),
        QStringLiteral("struct"),
        QStringLiteral("switch"),
        QStringLiteral("typedef"),
        QStringLiteral("union"),
        QStringLiteral("unsigned"),
        QStringLiteral("void"),
        QStringLiteral("volatile"),
        QStringLiteral("while"),
        QStringLiteral("_Bool"),
        QStringLiteral("_Complex"),
        QStringLiteral("_Imaginary"),
        QStringLiteral("int8_t"),
        QStringLiteral("int16_t"),
        QStringLiteral("int32_t"),
        QStringLiteral("int64_t"),
        QStringLiteral("uint8_t"),
        QStringLiteral("uint16_t"),
        QStringLiteral("uint32_t"),
        QStringLiteral("uint64_t")
    };

    return keywords;
}

const QSet<QString> &stmNameSet()
{
    static const QSet<QString> names = {
        QStringLiteral("MEMALIGN32"),
        QStringLiteral("MEMALIGN16"),
        QStringLiteral("MEMALIGN8"),
        QStringLiteral("MEMALIGN4")
    };

    return names;
}
}

CSyntaxHighlighter::CSyntaxHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
    , m_commentStartExpression(QStringLiteral("/\\*"))
    , m_commentEndExpression(QStringLiteral("\\*/"))
    , m_theme(defaultIDETheme())
{
    rebuildRules();
    rebuildLocalTypeNames();

    /*
     * typedefNames() scans the whole document. Even once per keystroke is
     * unnecessarily expensive in a 32 KB+ source file, so keep ordinary
     * per-block syntax highlighting immediate and debounce only the full-file
     * typedef catalogue refresh.
     */
    m_localTypeRefreshTimer = new QTimer(this);
    m_localTypeRefreshTimer->setSingleShot(true);
    /*
     * Typedef/local-type discovery is a current-document pass. Delay it until
     * typing has been quiet for half a second.
     */
    m_localTypeRefreshTimer->setInterval(500);

    connect(m_localTypeRefreshTimer, &QTimer::timeout,
            this, &CSyntaxHighlighter::rebuildLocalTypeNames);

}

void CSyntaxHighlighter::refreshLocalTypeNamesNow()
{
    if (m_localTypeRefreshTimer) {
        m_localTypeRefreshTimer->stop();
    }

    rebuildLocalTypeNames();
}


void CSyntaxHighlighter::setTheme(const IDETheme &theme)
{
    m_theme = theme;
    rebuildRules();
    rehighlight();
}

void CSyntaxHighlighter::setExternalTypeNames(const QStringList &names)
{
    QStringList clean = names;
    clean.removeAll(QString());
    clean.removeDuplicates();
    clean.sort(Qt::CaseInsensitive);

    if (clean == m_externalTypeNames) {
        return;
    }

    m_externalTypeNames = clean;
    rebuildKnownTypeNameSet();
    rehighlight();
}

void CSyntaxHighlighter::setExternalApiNames(const QStringList &names)
{
    QStringList clean = names;
    clean.removeAll(QString());
    clean.removeDuplicates();
    clean.sort(Qt::CaseSensitive);

    if (clean == m_externalApiNames) {
        return;
    }

    m_externalApiNames = clean;

    m_externalApiNameSet.clear();
    m_externalApiNameSet.reserve(m_externalApiNames.size());
    for (const QString &name : std::as_const(m_externalApiNames)) {
        if (!name.isEmpty()) {
            m_externalApiNameSet.insert(name);
        }
    }

    rehighlight();
}


void CSyntaxHighlighter::setResourceMode(bool enabled)
{
    if (m_resourceMode == enabled) {
        return;
    }

    m_resourceMode = enabled;

    if (m_resourceMode) {
        if (m_localTypeRefreshTimer) {
            m_localTypeRefreshTimer->stop();
        }

        m_localTypeNames.clear();
        m_externalTypeNames.clear();
        m_externalApiNames.clear();
        m_knownTypeNameSet.clear();
        m_externalApiNameSet.clear();
    } else {
        rebuildLocalTypeNames();
    }

    rebuildRules();
    rehighlight();
}

void CSyntaxHighlighter::rebuildLocalTypeNames()
{
    if (m_resourceMode) {
        return;
    }

    const QStringList discovered = typedefNames();

    if (discovered == m_localTypeNames) {
        return;
    }

    m_localTypeNames = discovered;
    rebuildKnownTypeNameSet();

    /*
     * A typedef can affect highlighting on lines other than the edited one,
     * so rehighlight once only when the discovered type list actually changed.
     */
    rehighlight();
}

void CSyntaxHighlighter::rebuildKnownTypeNameSet()
{
    m_knownTypeNameSet.clear();
    m_knownTypeNameSet.reserve(
        m_localTypeNames.size()
        + m_externalTypeNames.size());

    for (const QString &name : std::as_const(m_localTypeNames)) {
        if (!name.isEmpty()) {
            m_knownTypeNameSet.insert(name);
        }
    }

    for (const QString &name : std::as_const(m_externalTypeNames)) {
        if (!name.isEmpty()) {
            m_knownTypeNameSet.insert(name);
        }
    }
}

void CSyntaxHighlighter::rebuildRules()
{
    m_highlightingRules.clear();

    /*
     * Keywords are recognised by the linear identifier scanner in
     * highlightBlock(). Avoid running a whole-line regex just to rediscover the
     * same identifier boundaries needed for typedef/API highlighting.
     */
    m_keywordFormat.setForeground(
        m_theme.syntaxKeyword);

    /*
     * .res files deliberately use the lightest possible highlighting path.
     * They are C source for GCC, but resource data should not pay the cost of
     * typedef discovery, API colouring, function detection or other semantic
     * highlighting. C keywords are enough to keep the file readable.
     */
    if (m_resourceMode) {
        return;
    }

    m_stm32Format.setForeground(
        m_theme.syntaxSTM32);

    QTextCharFormat apiFormat;
    apiFormat.setForeground(m_theme.syntaxAPI);
    m_customAPIFormat = apiFormat;

    m_typedefFormat.setForeground(m_theme.syntaxType);

    m_preprocessorFormat.setForeground(
        m_theme.syntaxPreprocessor);

    // Muted code is blended with the current editor background so every theme
    // gets a legible but clearly inactive #if 0 branch.
    const QColor &foreground = m_theme.editorText;
    const QColor &background = m_theme.editorBackground;
    m_disabledCodeFormat.setForeground(QColor(
        (foreground.red() * 35 + background.red() * 65) / 100,
        (foreground.green() * 35 + background.green() * 65) / 100,
        (foreground.blue() * 35 + background.blue() * 65) / 100));

    m_stringFormat.setForeground(m_theme.syntaxString);

    QTextCharFormat numberFormat;
    numberFormat.setForeground(m_theme.syntaxNumber);
    m_highlightingRules.append({
        QRegularExpression(
            QStringLiteral("\\b(0[xX][0-9A-Fa-f]+|\\d+(\\.\\d+)?([eE][+-]?\\d+)?)[uUlLfF]*\\b")),
        numberFormat
    });

    QTextCharFormat functionFormat;
    functionFormat.setForeground(m_theme.syntaxFunction);
    m_highlightingRules.append({
        QRegularExpression(
            QStringLiteral("\\b(?!(?:return|if|for|while|switch|sizeof)\\b)[A-Za-z_][A-Za-z0-9_]*(?=\\s*\\()")),
        functionFormat
    });

    m_singleLineCommentFormat.setForeground(m_theme.syntaxComment);
    m_multiLineCommentFormat.setForeground(m_theme.syntaxMultiComment);
}

QStringList CSyntaxHighlighter::typedefNames() const
{
    QString source = document()->toPlainText();

    // Strip comments and quoted strings enough for typedef discovery. Newlines
    // are preserved so multi-line typedef structs still work naturally.
    bool inLineComment = false;
    bool inBlockComment = false;
    bool inString = false;
    bool inChar = false;
    bool escaped = false;

    for (int i = 0; i < source.size(); ++i) {
        const QChar ch = source.at(i);
        const QChar next = (i + 1 < source.size()) ? source.at(i + 1) : QChar();

        if (inLineComment) {
            if (ch == QLatin1Char('\n')) {
                inLineComment = false;
            } else {
                source[i] = QLatin1Char(' ');
            }
            continue;
        }

        if (inBlockComment) {
            if (ch == QLatin1Char('*') && next == QLatin1Char('/')) {
                source[i] = QLatin1Char(' ');
                if (i + 1 < source.size()) {
                    source[i + 1] = QLatin1Char(' ');
                }
                ++i;
                inBlockComment = false;
            } else if (ch != QLatin1Char('\n')) {
                source[i] = QLatin1Char(' ');
            }
            continue;
        }

        if (inString || inChar) {
            if (ch == QLatin1Char('\n')) {
                inString = false;
                inChar = false;
                escaped = false;
                continue;
            }

            source[i] = QLatin1Char(' ');

            if (escaped) {
                escaped = false;
                continue;
            }

            if (ch == QLatin1Char('\\')) {
                escaped = true;
                continue;
            }

            if ((inString && ch == QLatin1Char('"'))
                || (inChar && ch == QLatin1Char('\''))) {
                inString = false;
                inChar = false;
            }
            continue;
        }

        if (ch == QLatin1Char('/') && next == QLatin1Char('/')) {
            source[i] = QLatin1Char(' ');
            if (i + 1 < source.size()) {
                source[i + 1] = QLatin1Char(' ');
            }
            ++i;
            inLineComment = true;
            continue;
        }

        if (ch == QLatin1Char('/') && next == QLatin1Char('*')) {
            source[i] = QLatin1Char(' ');
            if (i + 1 < source.size()) {
                source[i + 1] = QLatin1Char(' ');
            }
            ++i;
            inBlockComment = true;
            continue;
        }

        if (ch == QLatin1Char('"')) {
            source[i] = QLatin1Char(' ');
            inString = true;
            continue;
        }

        if (ch == QLatin1Char('\'')) {
            source[i] = QLatin1Char(' ');
            inChar = true;
            continue;
        }
    }

    QStringList names;

    // Walk from each 'typedef' to its terminating top-level semicolon. This
    // handles both single-line aliases and multi-line typedef struct/enum/union
    // declarations without stopping at member semicolons inside the braces.
    static const QRegularExpression typedefStart(QStringLiteral(R"(\btypedef\b)"));

    int searchFrom = 0;
    while (searchFrom < source.size()) {
        const QRegularExpressionMatch startMatch = typedefStart.match(source, searchFrom);
        if (!startMatch.hasMatch()) {
            break;
        }

        const int start = startMatch.capturedStart();
        int braceDepth = 0;
        int parenDepth = 0;
        int bracketDepth = 0;
        int end = -1;

        for (int i = startMatch.capturedEnd(); i < source.size(); ++i) {
            const QChar ch = source.at(i);

            if (ch == QLatin1Char('{')) {
                ++braceDepth;
            } else if (ch == QLatin1Char('}')) {
                braceDepth = qMax(0, braceDepth - 1);
            } else if (ch == QLatin1Char('(')) {
                ++parenDepth;
            } else if (ch == QLatin1Char(')')) {
                parenDepth = qMax(0, parenDepth - 1);
            } else if (ch == QLatin1Char('[')) {
                ++bracketDepth;
            } else if (ch == QLatin1Char(']')) {
                bracketDepth = qMax(0, bracketDepth - 1);
            } else if (ch == QLatin1Char(';')
                       && braceDepth == 0
                       && parenDepth == 0
                       && bracketDepth == 0) {
                end = i;
                break;
            }
        }

        if (end < 0) {
            break;
        }

        const QString declaration = source.mid(start, end - start + 1);

        // Normal aliases:
        //   typedef unsigned int Foo;
        //   typedef struct { ... } Foo;
        //   typedef struct Tag { ... } Foo;
        static const QRegularExpression aliasExpression(
            QStringLiteral(R"(([A-Za-z_][A-Za-z0-9_]*)\s*;$)"));

        const QRegularExpressionMatch aliasMatch = aliasExpression.match(declaration);
        if (aliasMatch.hasMatch()) {
            const QString name = aliasMatch.captured(1);
            if (!name.isEmpty() && !names.contains(name)) {
                names.append(name);
            }
        }

        // Function-pointer typedef:
        //   typedef void (*Callback)(int);
        static const QRegularExpression functionPointerExpression(
            QStringLiteral(R"(\(\s*\*\s*([A-Za-z_][A-Za-z0-9_]*)\s*\))"));

        const QRegularExpressionMatch pointerMatch =
            functionPointerExpression.match(declaration);
        if (pointerMatch.hasMatch()) {
            const QString name = pointerMatch.captured(1);
            if (!name.isEmpty() && !names.contains(name)) {
                names.append(name);
            }
        }

        searchFrom = end + 1;
    }

    return names;
}

void CSyntaxHighlighter::highlightBlock(
    const QString &text)
{
    if (m_resourceMode) {
        /*
         * Resource mode is intentionally tiny. Two generic rules (numbers and
         * function-ish identifiers) are enough; generated resource data avoids
         * project/API/type catalogues entirely.
         */
        setCurrentBlockState(0);

        for (const HighlightingRule &rule :
             std::as_const(m_highlightingRules)) {
            QRegularExpressionMatchIterator iterator =
                rule.pattern.globalMatch(text);

            while (iterator.hasNext()) {
                const QRegularExpressionMatch match =
                    iterator.next();

                setFormat(
                    match.capturedStart(),
                    match.capturedLength(),
                    rule.format);
            }
        }

        int i = 0;

        while (i < text.size()) {
            if (!text.at(i).isLetter()
                && text.at(i)
                    != QLatin1Char('_')) {
                ++i;
                continue;
            }

            const int start = i++;

            while (i < text.size()
                   && (text.at(i).isLetterOrNumber()
                       || text.at(i)
                          == QLatin1Char('_'))) {
                ++i;
            }

            const QString identifier =
                text.mid(
                    start,
                    i - start);

            if (cKeywordSet().contains(
                    identifier)) {
                setFormat(
                    start,
                    i - start,
                    m_keywordFormat);
            }
        }

        return;
    }

    /*
     * Preprocessor branch tracking lives in QTextBlock::userState, rather
     * than QTextBlockUserData (which the folding gutter already owns).
     *
     *   low 2 bits: existing lexer state (0=normal, 1=block-comment, 2=continued #)
     *   next 27 bits: up to nine nested #if levels, three bits per level.
     *
     * Level states: 1=unknown, 2=active/taken, 3=inactive/not taken,
     *               4=inactive/already taken.
     * Unknown conditions stay normally coloured: this is a highlighter,
     * not a C preprocessor able to evaluate project macros.
     */
    const quint32 priorState = previousBlockState() >= 0
                                   ? quint32(previousBlockState()) : 0u;
    const quint32 priorLexer = priorState & 3u;
    quint32 conditionalStack = priorState >> 2;
    const bool inPreprocessor = priorLexer == 2u;

    const auto branchDisabled = [](quint32 stack) {
        while (stack != 0u) {
            const quint32 branch = stack & 7u;
            if (branch == 3u || branch == 4u) return true;
            stack >>= 3;
        }
        return false;
    };

    // Recognise #if 0, #if(0), #if 1, their nesting and alternate arms.
    // Ignore lookalike directives within an ongoing block comment.
    static const QRegularExpression conditionalDirective(
        QStringLiteral(R"(^\s*#\s*(if|ifdef|ifndef|elif|else|endif)\b(.*)$)"));
    static const QRegularExpression literalCondition(
        QStringLiteral(R"(^\s*\(?\s*([01])\s*\)?\s*(?://.*)?$)"));

    const QRegularExpressionMatch directive = priorLexer != 1u
        ? conditionalDirective.match(text)
        : QRegularExpressionMatch();
    if (directive.hasMatch()) {
        const QString operation = directive.captured(1);
        const QString argument = directive.captured(2);
        const QRegularExpressionMatch value = literalCondition.match(argument);
        const int condition = value.hasMatch() ? value.captured(1).toInt() : -1;
        const bool inactiveParent = branchDisabled(conditionalStack >> 3);
        const bool inactiveBefore = branchDisabled(conditionalStack);
        const quint32 current = conditionalStack & 7u;

        if (operation == QStringLiteral("if")
            || operation == QStringLiteral("ifdef")
            || operation == QStringLiteral("ifndef")) {
            // 27 stack bits = 9 levels. Deeper code stays conservatively
            // coloured; we avoid overflowing the signed block-state integer.
            if (conditionalStack <= 0xFFFFFFu) {
                const quint32 branch = operation != QStringLiteral("if")
                    || condition == -1 ? 1u : (condition ? 2u : 3u);
                conditionalStack = (conditionalStack << 3) | branch;
            }
        } else if (operation == QStringLiteral("elif") && current != 0u) {
            quint32 branch = current;
            if (current == 2u || current == 4u) branch = 4u;
            else if (current == 3u) branch =
                condition == 0 ? 3u : (condition == 1 ? 2u : 1u);
            conditionalStack = (conditionalStack & ~7u) | branch;
        } else if (operation == QStringLiteral("else") && current != 0u) {
            const quint32 branch = current == 3u ? 2u
                                 : (current == 2u || current == 4u) ? 4u : 1u;
            conditionalStack = (conditionalStack & ~7u) | branch;
        } else if (operation == QStringLiteral("endif") && current != 0u) {
            conditionalStack >>= 3;
        }
        setCurrentBlockState(int(conditionalStack << 2));
        // The controlling #if/#else/#endif line remains visibly a directive;
        // only an outer disabled region dims directives nested inside it.
        setFormat(0, text.length(),
                  (inactiveParent || (inactiveBefore && operation != QStringLiteral("endif")
                   && operation != QStringLiteral("else") && operation != QStringLiteral("elif")))
                      ? m_disabledCodeFormat : m_preprocessorFormat);
        return;
    }

    setCurrentBlockState(int(conditionalStack << 2));
    if (branchDisabled(conditionalStack)) {
        // Do not parse /* or // inside skipped code. Inactive text must never
        // contaminate syntax state in the reactivated #else/#endif branch.
        setFormat(0, text.length(), m_disabledCodeFormat);
        return;
    }

    const bool isPreprocessorLine =
        inPreprocessor
        || text.trimmed()
               .startsWith(
                   QLatin1Char('#'));

    if (isPreprocessorLine) {
        setFormat(
            0,
            text.length(),
            m_preprocessorFormat);
    } else {
        /*
         * Keep regex for the two places where it is genuinely convenient:
         * numeric literals and function-call shape. Everything identifier-like
         * is handled in ONE linear pass below.
         */
        for (const HighlightingRule &rule :
             std::as_const(m_highlightingRules)) {
            QRegularExpressionMatchIterator iterator =
                rule.pattern.globalMatch(text);

            while (iterator.hasNext()) {
                const QRegularExpressionMatch match =
                    iterator.next();

                setFormat(
                    match.capturedStart(),
                    match.capturedLength(),
                    rule.format);
            }
        }

        auto isIdentifierStart =
            [](QChar ch) {
                return ch.isLetter()
                    || ch == QLatin1Char('_');
            };

        auto isIdentifierChar =
            [](QChar ch) {
                return ch.isLetterOrNumber()
                    || ch == QLatin1Char('_');
            };

        int i = 0;

        while (i < text.size()) {
            if (!isIdentifierStart(
                    text.at(i))) {
                ++i;
                continue;
            }

            const int start = i++;

            while (i < text.size()
                   && isIdentifierChar(
                       text.at(i))) {
                ++i;
            }

            const int length =
                i - start;

            const QString identifier =
                text.mid(
                    start,
                    length);

            if (identifier
                    == QStringLiteral("printf")
                || m_externalApiNameSet
                       .contains(identifier)) {
                setFormat(
                    start,
                    length,
                    m_customAPIFormat);
            } else if (m_knownTypeNameSet
                           .contains(
                               identifier)) {
                setFormat(
                    start,
                    length,
                    m_typedefFormat);
            } else if (stmNameSet()
                           .contains(
                               identifier)) {
                setFormat(
                    start,
                    length,
                    m_stm32Format);
            } else if (cKeywordSet()
                           .contains(
                               identifier)) {
                setFormat(
                    start,
                    length,
                    m_keywordFormat);
            }
        }

        /*
         * Strings/comments are applied last and therefore win over any token
         * colouring inside their text.
         */
        applyStringsAndSingleLineComments(
            text);
    }

    applyMultiLineComments(text);

    if (isPreprocessorLine
        && text.trimmed()
               .endsWith(
                   QLatin1Char('\\'))) {
        setCurrentBlockState((currentBlockState() & ~3) | 2);
    }
}

void CSyntaxHighlighter::applyStringsAndSingleLineComments(
    const QString &text)
{
    /*
     * One pass replaces three regex passes and also fixes the classic
     * "http://..."-inside-a-string problem: // is only a comment opener while
     * the scanner is actually in normal C code.
     */
    int i = 0;

    while (i < text.size()) {
        const QChar ch =
            text.at(i);

        const QChar next =
            i + 1 < text.size()
                ? text.at(i + 1)
                : QChar();

        if (ch == QLatin1Char('/')
            && next == QLatin1Char('/')) {
            setFormat(
                i,
                text.size() - i,
                m_singleLineCommentFormat);
            return;
        }

        if (ch != QLatin1Char('"')
            && ch != QLatin1Char('\'')) {
            ++i;
            continue;
        }

        const QChar quote = ch;
        const int start = i++;
        bool escaped = false;

        while (i < text.size()) {
            const QChar current =
                text.at(i);

            if (escaped) {
                escaped = false;
                ++i;
                continue;
            }

            if (current
                == QLatin1Char('\\')) {
                escaped = true;
                ++i;
                continue;
            }

            ++i;

            if (current == quote) {
                break;
            }
        }

        setFormat(
            start,
            i - start,
            m_stringFormat);
    }
}

void CSyntaxHighlighter::applyMultiLineComments(const QString &text)
{
    setCurrentBlockState(currentBlockState() & ~3);

    /*
     * Find a /* opener only when it is actually C code.
     *
     * The old implementation simply searched the raw line for "/*". That
     * meant this very common way of disabling a block comment:
     *
     *     //* disabled opener
     *
     * was incorrectly treated as the start of a multi-line comment because
     * the characters at positions 1-2 are still "/*".
     *
     * It also meant "/*" inside string/character literals could start a fake
     * block comment in the highlighter even though the compiler correctly
     * ignores it.
     */
    auto nextCommentStart =
        [&text](int from) -> int {
            bool inDoubleQuote = false;
            bool inSingleQuote = false;
            bool escaped = false;

            for (int i = qMax(0, from); i < text.size(); ++i) {
                const QChar ch = text.at(i);

                if (escaped) {
                    escaped = false;
                    continue;
                }

                if ((inDoubleQuote || inSingleQuote)
                    && ch == QLatin1Char('\\')) {
                    escaped = true;
                    continue;
                }

                if (!inSingleQuote
                    && ch == QLatin1Char('"')) {
                    inDoubleQuote = !inDoubleQuote;
                    continue;
                }

                if (!inDoubleQuote
                    && ch == QLatin1Char('\'')) {
                    inSingleQuote = !inSingleQuote;
                    continue;
                }

                if (inDoubleQuote || inSingleQuote) {
                    continue;
                }

                if (ch == QLatin1Char('/')
                    && i + 1 < text.size()) {
                    const QChar next = text.at(i + 1);

                    /*
                     * Once // begins, the rest of this physical line is a
                     * single-line comment. A later /* therefore cannot open a
                     * real block comment.
                     */
                    if (next == QLatin1Char('/')) {
                        return -1;
                    }

                    if (next == QLatin1Char('*')) {
                        return i;
                    }
                }
            }

            return -1;
        };

    int searchFrom = 0;

    /*
     * If the previous QTextBlock ended inside a block comment, this line starts
     * inside that comment regardless of any // or quote-looking characters.
     */
    if ((previousBlockState() & 3) == 1) {
        const QRegularExpressionMatch endMatch =
            m_commentEndExpression.match(text, 0);

        if (!endMatch.hasMatch()) {
            setCurrentBlockState((currentBlockState() & ~3) | 1);
            setFormat(
                0,
                text.length(),
                m_multiLineCommentFormat);
            return;
        }

        setFormat(
            0,
            endMatch.capturedEnd(),
            m_multiLineCommentFormat);

        searchFrom = endMatch.capturedEnd();
    }

    int startIndex = nextCommentStart(searchFrom);

    while (startIndex >= 0) {
        const QRegularExpressionMatch endMatch =
            m_commentEndExpression.match(
                text,
                startIndex + 2);

        if (!endMatch.hasMatch()) {
            setCurrentBlockState((currentBlockState() & ~3) | 1);
            setFormat(
                startIndex,
                text.length() - startIndex,
                m_multiLineCommentFormat);
            return;
        }

        const int commentEnd =
            endMatch.capturedEnd();

        setFormat(
            startIndex,
            commentEnd - startIndex,
            m_multiLineCommentFormat);

        startIndex =
            nextCommentStart(commentEnd);
    }
}
