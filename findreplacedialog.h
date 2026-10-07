#ifndef FINDREPLACEDIALOG_H
#define FINDREPLACEDIALOG_H

#include <QDialog>
#include <QList>
#include <QString>

class QCheckBox;
class QLineEdit;
class QPushButton;
class QTreeWidget;
class QTreeWidgetItem;

struct ProjectSearchResult
{
    QString filePath;
    int line = -1;       // zero-based
    int column = -1;     // zero-based
    int start = -1;      // absolute character offset in the searched text
    int length = 0;
    QString preview;
};

class FindReplaceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FindReplaceDialog(QWidget *parent = nullptr);

    QString findText() const;
    QString replaceText() const;
    void setFindText(const QString &text);
    void focusFindText();
    bool matchCase() const;
    bool wholeWord() const;

    void setResults(const QList<ProjectSearchResult> &results);
    const QList<ProjectSearchResult> &results() const;
    QList<int> selectedResultIndexes() const;
    int resultIndexForItem(QTreeWidgetItem *item) const;

signals:
    void findAllRequested();
    void replaceSelectedRequested();
    void replaceAllRequested();
    void resultActivated(int resultIndex);

private:
    void updateButtonStates();

    QLineEdit *m_findEdit;
    QLineEdit *m_replaceEdit;
    QCheckBox *m_matchCaseCheck;
    QCheckBox *m_wholeWordCheck;
    QTreeWidget *m_resultsTree;
    QPushButton *m_findAllButton;
    QPushButton *m_replaceSelectedButton;
    QPushButton *m_replaceAllButton;
    QList<ProjectSearchResult> m_results;
};

#endif // FINDREPLACEDIALOG_H
