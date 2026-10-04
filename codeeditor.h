#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QPlainTextEdit>
#include <QString>
#include <QStringList>

class CSyntaxHighlighter;
class QCompleter;
class QStringListModel;

class CodeEditor : public QPlainTextEdit
{
    Q_OBJECT

public:
    explicit CodeEditor(QWidget *parent = nullptr);
    ~CodeEditor() override;

    QString filePath() const;
    void setFilePath(const QString &path);
    void setFunctionCompletions(const QStringList &signatures);

    bool loadFromFile(const QString &path);
    bool save();
    bool saveAs(const QString &path);

protected:
    void focusInEvent(QFocusEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    QString textUnderCursor() const;
    void insertFunctionCompletion(const QString &signature);
    void selectArgument(int index);

    QString m_filePath;
    CSyntaxHighlighter *m_highlighter;
    QCompleter *m_completer;
    QStringListModel *m_completionModel;
    QList<QPair<int, int>> m_argumentRanges;
    int m_selectedArgument;
};

#endif // CODEEDITOR_H
