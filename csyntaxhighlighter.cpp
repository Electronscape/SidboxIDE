#include "csyntaxhighlighter.h"

#include <QColor>
#include <QFont>
#include <QStringList>
#include <QTextDocument>
#include <QTimer>

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
    /* Third stage of the typing trickle. */
    m_localTypeRefreshTimer->setInterval(540);

    connect(m_localTypeRefreshTimer, &QTimer::timeout,
            this, &CSyntaxHighlighter::rebuildLocalTypeNames);

    connect(parent, &QTextDocument::contentsChanged,
            this, [this]() {
                if (!m_resourceMode
                    && m_localTypeRefreshTimer
                    && !m_localTypeRefreshTimer->isActive()) {
                    m_localTypeRefreshTimer->start();
                }
            });
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

    QTextCharFormat keywordFormat;
    keywordFormat.setForeground(m_theme.syntaxKeyword);

    /*
     * One compiled expression is substantially cheaper than running one regex
     * for every C keyword on every text block.
     */
    m_highlightingRules.append({
        QRegularExpression(
            QStringLiteral(
                R"(\b(?:auto|break|case|char|const|continue|default|do|double|else|enum|extern|float|for|goto|if|inline|int|long|register|restrict|return|short|signed|sizeof|static|struct|switch|typedef|union|unsigned|void|volatile|while|_Bool|_Complex|_Imaginary|int8_t|int16_t|int32_t|int64_t|uint8_t|uint16_t|uint32_t|uint64_t)\b)")),
        keywordFormat
    });

    /*
     * .res files deliberately use the lightest possible highlighting path.
     * They are C source for GCC, but resource data should not pay the cost of
     * typedef discovery, API colouring, function detection or other semantic
     * highlighting. C keywords are enough to keep the file readable.
     */
    if (m_resourceMode) {
        return;
    }

    QTextCharFormat stmFormat;
    stmFormat.setForeground(m_theme.syntaxSTM32);
    m_stm32Format = stmFormat;

    m_highlightingRules.append({
        QRegularExpression(
            QStringLiteral(
                R"(\b(?:MEMALIGN32|MEMALIGN16|MEMALIGN8|MEMALIGN4)\b)")),
        stmFormat
    });

    QTextCharFormat apiFormat;
    apiFormat.setForeground(m_theme.syntaxAPI);
    m_customAPIFormat = apiFormat;

    m_typedefFormat.setForeground(m_theme.syntaxType);

    QTextCharFormat preprocessorFormat;
    preprocessorFormat.setForeground(m_theme.syntaxPreprocessor);
    m_preprocessorFormat = preprocessorFormat;
    m_highlightingRules.append({
        QRegularExpression(QStringLiteral("^\\s*#\\s*\\w+.*")),
        preprocessorFormat
    });

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

void CSyntaxHighlighter::highlightBlock(const QString &text)
{
    if (m_resourceMode) {
        setCurrentBlockState(0);
        for (const HighlightingRule &rule : m_highlightingRules) {
            QRegularExpressionMatchIterator matchIterator =
                rule.pattern.globalMatch(text);
            while (matchIterator.hasNext()) {
                const QRegularExpressionMatch match = matchIterator.next();
                setFormat(match.capturedStart(), match.capturedLength(), rule.format);
            }
        }
        return;
    }

    const bool inPreprocessor = (previousBlockState() == 2);
    const bool isPreprocessorLine = inPreprocessor || text.trimmed().startsWith('#');

    if (isPreprocessorLine) {
        setFormat(0, text.length(), m_preprocessorFormat);
    } else {
        /*
         * Apply project/local type names FIRST.
         *
         * The normal syntax rules are applied afterwards, so strings and
         * comments correctly win over the type colour. Previously a known
         * typedef such as BlobT inside:
         *
         *     // extern BlobT thing;
         *
         * was painted green after the comment rule had already run.
         */
        /*
         * Scan identifiers once and use the pre-built QSet for type lookup.
         * Previously this constructed and ran one QRegularExpression for every
         * known type name on every source line.
         */
        static const QRegularExpression identifierExpression(
            QStringLiteral(R"(\b[A-Za-z_][A-Za-z0-9_]*\b)"));

        QRegularExpressionMatchIterator typeIterator =
            identifierExpression.globalMatch(text);

        while (typeIterator.hasNext()) {
            const QRegularExpressionMatch match =
                typeIterator.next();

            if (m_knownTypeNameSet.contains(match.captured(0))) {
                setFormat(
                    match.capturedStart(),
                    match.capturedLength(),
                    m_typedefFormat);
            }
        }

        /*
         * These rules deliberately come second. In particular, quotation and
         * comment formats overwrite type colouring where appropriate.
         */
        for (const HighlightingRule &rule : std::as_const(m_highlightingRules)) {
            QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
            while (matchIterator.hasNext()) {
                const QRegularExpressionMatch match = matchIterator.next();
                setFormat(match.capturedStart(), match.capturedLength(), rule.format);
            }
        }

        /*
         * Sidbox API symbols deliberately run AFTER the generic function/type
         * rules so API calls, constants and API typedef names keep their own
         * colour instead of being repainted as ordinary C symbols.
         *
         * Scan identifiers once per line and compare against the catalog rather
         * than running one regular expression per API name.
         */
        QRegularExpressionMatchIterator apiIterator =
            identifierExpression.globalMatch(text);

        while (apiIterator.hasNext()) {
            const QRegularExpressionMatch match =
                apiIterator.next();
            const QString identifier = match.captured(0);

            if (identifier == QStringLiteral("printf")
                || m_externalApiNameSet.contains(identifier)) {
                setFormat(
                    match.capturedStart(),
                    match.capturedLength(),
                    m_customAPIFormat);
            }
        }

        /*
         * Strings and // comments are protected regions and must win over API
         * colouring. Multi-line comments are applied immediately afterwards.
         */
        applyStringsAndSingleLineComments(text);
    }

    applyMultiLineComments(text);

    if (isPreprocessorLine && text.trimmed().endsWith('\\')) {
        setCurrentBlockState(2);
    }
}

void CSyntaxHighlighter::applyStringsAndSingleLineComments(const QString &text)
{
    static const QRegularExpression doubleQuoted(
        QStringLiteral("\"([^\"\\\\]|\\\\.)*\""));
    static const QRegularExpression singleQuoted(
        QStringLiteral("'([^'\\\\]|\\\\.)*'"));
    static const QRegularExpression singleLineComment(
        QStringLiteral("//[^\\n]*"));

    QRegularExpressionMatchIterator iterator =
        doubleQuoted.globalMatch(text);
    while (iterator.hasNext()) {
        const QRegularExpressionMatch match = iterator.next();
        setFormat(match.capturedStart(),
                  match.capturedLength(),
                  m_stringFormat);
    }

    iterator = singleQuoted.globalMatch(text);
    while (iterator.hasNext()) {
        const QRegularExpressionMatch match = iterator.next();
        setFormat(match.capturedStart(),
                  match.capturedLength(),
                  m_stringFormat);
    }

    iterator = singleLineComment.globalMatch(text);
    while (iterator.hasNext()) {
        const QRegularExpressionMatch match = iterator.next();
        setFormat(match.capturedStart(),
                  match.capturedLength(),
                  m_singleLineCommentFormat);
    }
}

void CSyntaxHighlighter::applyMultiLineComments(const QString &text)
{
    setCurrentBlockState(0);

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
    if (previousBlockState() == 1) {
        const QRegularExpressionMatch endMatch =
            m_commentEndExpression.match(text, 0);

        if (!endMatch.hasMatch()) {
            setCurrentBlockState(1);
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
            setCurrentBlockState(1);
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
