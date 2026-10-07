#include "csyntaxhighlighter.h"

#include <QColor>
#include <QFont>
#include <QStringList>
#include <QTextDocument>

CSyntaxHighlighter::CSyntaxHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
    , m_commentStartExpression(QStringLiteral("/\\*"))
    , m_commentEndExpression(QStringLiteral("\\*/"))
    , m_theme(defaultIDETheme())
{
    rebuildRules();
    rebuildLocalTypeNames();

    /*
     * typedefNames() scans the whole document, so NEVER call it from
     * highlightBlock(). highlightBlock() runs once per text block and doing a
     * whole-document scan there turns large files into an accidental O(lines ×
     * file-size) workload.
     *
     * Rebuild the local type cache once when the document actually changes.
     */
    connect(parent, &QTextDocument::contentsChanged,
            this, &CSyntaxHighlighter::rebuildLocalTypeNames);
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
    rehighlight();
}

void CSyntaxHighlighter::rebuildLocalTypeNames()
{
    const QStringList discovered = typedefNames();

    if (discovered == m_localTypeNames) {
        return;
    }

    m_localTypeNames = discovered;

    /*
     * A typedef can affect highlighting on lines other than the edited one,
     * so rehighlight once only when the discovered type list actually changed.
     */
    rehighlight();
}

void CSyntaxHighlighter::rebuildRules()
{
    m_highlightingRules.clear();

    QTextCharFormat keywordFormat;
    keywordFormat.setForeground(m_theme.syntaxKeyword);

    const QStringList keywordPatterns = {
        QStringLiteral("\\bauto\\b"), QStringLiteral("\\bbreak\\b"), QStringLiteral("\\bcase\\b"),
        QStringLiteral("\\bchar\\b"), QStringLiteral("\\bconst\\b"), QStringLiteral("\\bcontinue\\b"),
        QStringLiteral("\\bdefault\\b"), QStringLiteral("\\bdo\\b"), QStringLiteral("\\bdouble\\b"),
        QStringLiteral("\\belse\\b"), QStringLiteral("\\benum\\b"), QStringLiteral("\\bextern\\b"),
        QStringLiteral("\\bfloat\\b"), QStringLiteral("\\bfor\\b"), QStringLiteral("\\bgoto\\b"),
        QStringLiteral("\\bif\\b"), QStringLiteral("\\binline\\b"), QStringLiteral("\\bint\\b"),
        QStringLiteral("\\blong\\b"), QStringLiteral("\\bregister\\b"), QStringLiteral("\\brestrict\\b"),
        QStringLiteral("\\breturn\\b"), QStringLiteral("\\bshort\\b"), QStringLiteral("\\bsigned\\b"),
        QStringLiteral("\\bsizeof\\b"), QStringLiteral("\\bstatic\\b"), QStringLiteral("\\bstruct\\b"),
        QStringLiteral("\\bswitch\\b"), QStringLiteral("\\btypedef\\b"), QStringLiteral("\\bunion\\b"),
        QStringLiteral("\\bunsigned\\b"), QStringLiteral("\\bvoid\\b"), QStringLiteral("\\bvolatile\\b"),
        QStringLiteral("\\bwhile\\b"), QStringLiteral("\\b_Bool\\b"), QStringLiteral("\\b_Complex\\b"),
        QStringLiteral("\\b_Imaginary\\b"),
        QStringLiteral("\\bint8_t\\b"), QStringLiteral("\\bint16_t\\b"),
        QStringLiteral("\\bint32_t\\b"), QStringLiteral("\\bint64_t\\b"),
        QStringLiteral("\\buint8_t\\b"), QStringLiteral("\\buint16_t\\b"),
        QStringLiteral("\\buint32_t\\b"), QStringLiteral("\\buint64_t\\b")
    };

    for (const QString &pattern : keywordPatterns) {
        m_highlightingRules.append({QRegularExpression(pattern), keywordFormat});
    }

    QTextCharFormat stmFormat;
    stmFormat.setForeground(m_theme.syntaxSTM32);
    m_stm32Format = stmFormat;

    const QStringList stm32Patterns = {
        QStringLiteral("\\bMEMALIGN32\\b"),
        QStringLiteral("\\bMEMALIGN16\\b"),
        QStringLiteral("\\bMEMALIGN8\\b"),
        QStringLiteral("\\bMEMALIGN4\\b")
    };

    for (const QString &pattern : stm32Patterns) {
        m_highlightingRules.append({QRegularExpression(pattern), stmFormat});
    }

    QTextCharFormat apiFormat;
    apiFormat.setForeground(m_theme.syntaxAPI);
    m_customAPIFormat = apiFormat;

    const QStringList apiPatterns = {
        QStringLiteral("\\bprintf\\b")
    };

    for (const QString &pattern : apiPatterns) {
        m_highlightingRules.append({QRegularExpression(pattern), apiFormat});
    }

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
        QStringList typeNames = m_localTypeNames;
        typeNames.append(m_externalTypeNames);
        typeNames.removeDuplicates();

        for (const QString &name : std::as_const(typeNames)) {
            if (name.isEmpty()) {
                continue;
            }

            const QRegularExpression typeExpression(
                QStringLiteral("\\b%1\\b")
                    .arg(QRegularExpression::escape(name)));

            QRegularExpressionMatchIterator iterator =
                typeExpression.globalMatch(text);

            while (iterator.hasNext()) {
                const QRegularExpressionMatch match = iterator.next();
                setFormat(match.capturedStart(),
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
        static const QRegularExpression identifierExpression(
            QStringLiteral(R"(\b[A-Za-z_][A-Za-z0-9_]*\b)"));

        QRegularExpressionMatchIterator apiIterator =
            identifierExpression.globalMatch(text);

        while (apiIterator.hasNext()) {
            const QRegularExpressionMatch match = apiIterator.next();
            const QString identifier = match.captured(0);

            if (identifier == QStringLiteral("printf")
                || m_externalApiNames.contains(identifier)) {
                setFormat(match.capturedStart(),
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

    int startIndex = 0;
    if (previousBlockState() != 1) {
        startIndex = text.indexOf(m_commentStartExpression);
    }

    while (startIndex >= 0) {
        const QRegularExpressionMatch endMatch = m_commentEndExpression.match(text, startIndex);
        int commentLength = 0;

        if (endMatch.hasMatch()) {
            commentLength = endMatch.capturedEnd() - startIndex;
        } else {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        }

        setFormat(startIndex, commentLength, m_multiLineCommentFormat);
        startIndex = text.indexOf(m_commentStartExpression, startIndex + commentLength);
    }
}
