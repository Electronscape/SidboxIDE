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
    keywordFormat.setForeground(QColor(255, 255, 0));
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
        QStringLiteral("\\b_Imaginary\\b")
    };

    for (const QString &pattern : keywordPatterns) {
        m_highlightingRules.append({QRegularExpression(pattern), keywordFormat});
    }

    QTextCharFormat preprocessorFormat;
    preprocessorFormat.setForeground(QColor(0, 255, 255));
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
    functionFormat.setForeground(QColor(220, 220, 255));
    m_highlightingRules.append({QRegularExpression(QStringLiteral("\\b[A-Za-z_][A-Za-z0-9_]*(?=\\s*\\()")), functionFormat});

    QTextCharFormat singleLineCommentFormat;
    singleLineCommentFormat.setForeground(QColor(106, 153, 85));
    m_highlightingRules.append({QRegularExpression(QStringLiteral("//[^\\n]*")), singleLineCommentFormat});

    m_multiLineCommentFormat = singleLineCommentFormat;
}

void CSyntaxHighlighter::highlightBlock(const QString &text)
{
    for (const HighlightingRule &rule : std::as_const(m_highlightingRules)) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            const QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }

    applyMultiLineComments(text);
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
