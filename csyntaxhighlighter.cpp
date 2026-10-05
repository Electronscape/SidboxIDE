#include "csyntaxhighlighter.h"

#include <QColor>
#include <QFont>
#include <QStringList>

CSyntaxHighlighter::CSyntaxHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
    , m_commentStartExpression(QStringLiteral("/\\*"))
    , m_commentEndExpression(QStringLiteral("\\*/"))
{
    QTextCharFormat keywordFormat;
    keywordFormat.setForeground(QColor(255, 200, 0));
    //keywordFormat.setFontWeight(QFont::Bold);

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
        QStringLiteral("\\bint8_t\\b"), QStringLiteral("\\bint16_t\\b"), QStringLiteral("\\bint32_t\\b"), QStringLiteral("\\bint64_t\\b"),
        QStringLiteral("\\buint8_t\\b"), QStringLiteral("\\buint16_t\\b"), QStringLiteral("\\buint32_t\\b"), QStringLiteral("\\buint64_t\\b"),
    };

    for (const QString &pattern : keywordPatterns) {
        m_highlightingRules.append({QRegularExpression(pattern), keywordFormat});
    }


    QTextCharFormat stmFormat;
    stmFormat.setForeground(QColor(72, 176, 176));
    m_stm32Format.setForeground(QColor(72, 176, 176));
    const QStringList stm32Patterns = {
        QStringLiteral("\\bMEMALIGN32\\b"), QStringLiteral("\\bMEMALIGN16\\b"), QStringLiteral("\\bMEMALIGN8\\b"), QStringLiteral("\\bMEMALIGN4\\b"),
    };

    for (const QString &pattern : stm32Patterns) {
        m_highlightingRules.append({QRegularExpression(pattern), stmFormat});
    }

    // custom API format
    QTextCharFormat APIkeywordFormat;
    APIkeywordFormat.setForeground(QColor(64, 128, 200));
    const QStringList APIkeywordPatterns = {
        QStringLiteral("\\bprintf\\b")
    };

    for (const QString &pattern : APIkeywordPatterns) {
        m_highlightingRules.append({QRegularExpression(pattern), APIkeywordFormat});
    }






    QTextCharFormat preprocessorFormat;
    preprocessorFormat.setForeground(QColor(0, 255, 255));
    m_preprocessorFormat.setForeground(QColor(0, 255, 255));
    m_highlightingRules.append({QRegularExpression(QStringLiteral("^\\s*#\\s*\\w+.*")), preprocessorFormat});

    QTextCharFormat quotationFormat;
    quotationFormat.setForeground(QColor(206, 145, 120));
    m_highlightingRules.append({QRegularExpression(QStringLiteral("\"([^\"\\\\]|\\\\.)*\"")), quotationFormat});
    m_highlightingRules.append({QRegularExpression(QStringLiteral("'([^'\\\\]|\\\\.)*'")), quotationFormat});

    QTextCharFormat numberFormat;
    numberFormat.setForeground(QColor(0, 206, 0));
    m_highlightingRules.append({
        QRegularExpression(QStringLiteral("\\b(0[xX][0-9A-Fa-f]+|\\d+(\\.\\d+)?([eE][+-]?\\d+)?)[uUlLfF]*\\b")),
        numberFormat
    });

    QTextCharFormat functionFormat;
    functionFormat.setForeground(QColor(200, 132, 192));
    m_highlightingRules.append({QRegularExpression(QStringLiteral("\\b(?!(?:return|if|for|while|switch|sizeof)\\b)[A-Za-z_][A-Za-z0-9_]*(?=\\s*\\()")), functionFormat});

    QTextCharFormat singleLineCommentFormat;
    singleLineCommentFormat.setForeground(QColor(106, 153, 85));
    m_highlightingRules.append({QRegularExpression(QStringLiteral("//[^\\n]*")), singleLineCommentFormat});

    QTextCharFormat multiLineCommentFormat;
    m_multiLineCommentFormat.setForeground(QColor(130, 150, 125));
}

void CSyntaxHighlighter::highlightBlock(const QString &text)
{
    const bool inPreprocessor = (previousBlockState() == 2);
    const bool isPreprocessorLine = inPreprocessor || text.trimmed().startsWith('#');

    if (isPreprocessorLine) {
        setFormat(0, text.length(), m_preprocessorFormat);
    } else {
        for (const HighlightingRule &rule : std::as_const(m_highlightingRules)) {
            QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
            while (matchIterator.hasNext()) {
                const QRegularExpressionMatch match = matchIterator.next();
                setFormat(match.capturedStart(), match.capturedLength(), rule.format);
            }
        }
    }

    applyMultiLineComments(text);

    if (isPreprocessorLine && text.trimmed().endsWith('\\')) {
        setCurrentBlockState(2);
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
