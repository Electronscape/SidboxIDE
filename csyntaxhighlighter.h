#ifndef CSYNTAXHIGHLIGHTER_H
#define CSYNTAXHIGHLIGHTER_H

#include <QRegularExpression>
#include <QSet>
#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include "idetheme.h"

class QTimer;

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
    void rebuildKnownTypeNameSet();
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

    /*
     * highlightBlock() is called once per text block. Membership tests in a
     * QSet avoid repeatedly walking the project/API QStringLists for every
     * identifier on every line.
     */
    QSet<QString> m_knownTypeNameSet;
    QSet<QString> m_externalApiNameSet;

    QTimer *m_localTypeRefreshTimer = nullptr;
    bool m_resourceMode = false;
};

#endif // CSYNTAXHIGHLIGHTER_H
