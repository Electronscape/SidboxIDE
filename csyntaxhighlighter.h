#ifndef CSYNTAXHIGHLIGHTER_H
#define CSYNTAXHIGHLIGHTER_H

#include <QRegularExpression>
#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include "idetheme.h"

class CSyntaxHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    explicit CSyntaxHighlighter(QTextDocument *parent = nullptr);
    void setTheme(const IDETheme &theme);
    void setExternalTypeNames(const QStringList &names);
    void setExternalApiNames(const QStringList &names);
    void setResourceMode(bool enabled);

protected:
    void highlightBlock(const QString &text) override;

private:
    struct HighlightingRule {
        QRegularExpression pattern;
        QTextCharFormat format;
    };

    void applyStringsAndSingleLineComments(const QString &text);
    void applyMultiLineComments(const QString &text);
    QStringList typedefNames() const;
    void rebuildLocalTypeNames();
    void rebuildRules();

    QList<HighlightingRule> m_highlightingRules;
    QRegularExpression m_commentStartExpression;
    QRegularExpression m_commentEndExpression;
    QTextCharFormat m_multiLineCommentFormat;
    QTextCharFormat m_singleLineCommentFormat;
    QTextCharFormat m_stringFormat;
    QTextCharFormat m_preprocessorFormat;
    QTextCharFormat m_typedefFormat;
    QTextCharFormat m_customAPIFormat;
    QTextCharFormat m_stm32Format;
    IDETheme m_theme;
    QStringList m_localTypeNames;
    QStringList m_externalTypeNames;
    QStringList m_externalApiNames;
    bool m_resourceMode = false;
};

#endif // CSYNTAXHIGHLIGHTER_H
