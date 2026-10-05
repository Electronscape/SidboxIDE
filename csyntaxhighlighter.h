#ifndef CSYNTAXHIGHLIGHTER_H
#define CSYNTAXHIGHLIGHTER_H

#include <QRegularExpression>
#include <QSyntaxHighlighter>
#include <QTextCharFormat>

class CSyntaxHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    explicit CSyntaxHighlighter(QTextDocument *parent = nullptr);

protected:
    void highlightBlock(const QString &text) override;

private:
    struct HighlightingRule {
        QRegularExpression pattern;
        QTextCharFormat format;
    };

    void applyMultiLineComments(const QString &text);

    QList<HighlightingRule> m_highlightingRules;
    QRegularExpression m_commentStartExpression;
    QRegularExpression m_commentEndExpression;
    QTextCharFormat m_multiLineCommentFormat;
    QTextCharFormat m_preprocessorFormat;
    QTextCharFormat m_customAPIFormat;
    QTextCharFormat m_stm32Format;
};

#endif // CSYNTAXHIGHLIGHTER_H
