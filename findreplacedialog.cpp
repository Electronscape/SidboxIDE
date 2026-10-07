#include "findreplacedialog.h"

#include <QCheckBox>
#include <QDialogButtonBox>
#include <QFileInfo>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QVBoxLayout>

FindReplaceDialog::FindReplaceDialog(QWidget *parent)
    : QDialog(parent)
    , m_findEdit(new QLineEdit(this))
    , m_replaceEdit(new QLineEdit(this))
    , m_matchCaseCheck(new QCheckBox(tr("Match case"), this))
    , m_wholeWordCheck(new QCheckBox(tr("Whole word"), this))
    , m_resultsTree(new QTreeWidget(this))
    , m_findAllButton(new QPushButton(tr("Find All"), this))
    , m_replaceSelectedButton(new QPushButton(tr("Replace Selected"), this))
    , m_replaceAllButton(new QPushButton(tr("Replace All"), this))
{
    setWindowTitle(tr("Find / Replace in Project"));
    resize(900, 620);
    setMinimumSize(720, 480);
    setModal(false);

    auto *form = new QFormLayout;
    form->addRow(tr("Find"), m_findEdit);
    form->addRow(tr("Replace with"), m_replaceEdit);

    auto *options = new QHBoxLayout;
    options->addWidget(m_matchCaseCheck);
    options->addWidget(m_wholeWordCheck);
    options->addStretch(1);

    m_resultsTree->setColumnCount(3);
    m_resultsTree->setHeaderLabels({
        tr("File"),
        tr("Line"),
        tr("Match")
    });
    m_resultsTree->setRootIsDecorated(true);
    m_resultsTree->setAlternatingRowColors(true);
    m_resultsTree->setSelectionMode(QAbstractItemView::ExtendedSelection);
    m_resultsTree->setUniformRowHeights(true);
    m_resultsTree->header()->setStretchLastSection(true);
    m_resultsTree->header()->resizeSection(0, 260);
    m_resultsTree->header()->resizeSection(1, 70);

    auto *actions = new QHBoxLayout;
    actions->addWidget(m_findAllButton);
    actions->addWidget(m_replaceSelectedButton);
    actions->addWidget(m_replaceAllButton);
    actions->addStretch(1);

    auto *closeButtons = new QDialogButtonBox(QDialogButtonBox::Close, this);

    auto *layout = new QVBoxLayout(this);
    layout->addLayout(form);
    layout->addLayout(options);
    layout->addWidget(new QLabel(tr("Results"), this));
    layout->addWidget(m_resultsTree, 1);
    layout->addLayout(actions);
    layout->addWidget(closeButtons);

    connect(closeButtons, &QDialogButtonBox::rejected,
            this, &FindReplaceDialog::close);

    connect(m_findAllButton, &QPushButton::clicked,
            this, &FindReplaceDialog::findAllRequested);
    connect(m_replaceSelectedButton, &QPushButton::clicked,
            this, &FindReplaceDialog::replaceSelectedRequested);
    connect(m_replaceAllButton, &QPushButton::clicked,
            this, &FindReplaceDialog::replaceAllRequested);

    connect(m_findEdit, &QLineEdit::returnPressed,
            this, &FindReplaceDialog::findAllRequested);

    connect(m_findEdit, &QLineEdit::textChanged,
            this, [this]() {
                updateButtonStates();
            });

    connect(m_resultsTree, &QTreeWidget::itemSelectionChanged,
            this, [this]() {
                updateButtonStates();
            });

    connect(m_resultsTree, &QTreeWidget::itemDoubleClicked,
            this, [this](QTreeWidgetItem *item, int) {
                const int index = resultIndexForItem(item);
                if (index >= 0) {
                    emit resultActivated(index);
                }
            });

    updateButtonStates();
}

QString FindReplaceDialog::findText() const
{
    return m_findEdit->text();
}

QString FindReplaceDialog::replaceText() const
{
    return m_replaceEdit->text();
}

void FindReplaceDialog::setFindText(const QString &text)
{
    m_findEdit->setText(text);
    m_findEdit->selectAll();
}

void FindReplaceDialog::focusFindText()
{
    m_findEdit->setFocus();
    m_findEdit->selectAll();
}

bool FindReplaceDialog::matchCase() const
{
    return m_matchCaseCheck->isChecked();
}

bool FindReplaceDialog::wholeWord() const
{
    return m_wholeWordCheck->isChecked();
}

void FindReplaceDialog::setResults(const QList<ProjectSearchResult> &results)
{
    m_results = results;
    m_resultsTree->clear();

    QHash<QString, QTreeWidgetItem *> fileItems;

    for (int i = 0; i < m_results.size(); ++i) {
        const ProjectSearchResult &result = m_results.at(i);

        QTreeWidgetItem *fileItem =
            fileItems.value(result.filePath, nullptr);

        if (!fileItem) {
            fileItem = new QTreeWidgetItem(m_resultsTree);
            fileItem->setText(0, QFileInfo(result.filePath).fileName());
            fileItem->setToolTip(0, result.filePath);
            fileItem->setFirstColumnSpanned(false);
            fileItems.insert(result.filePath, fileItem);
        }

        auto *matchItem = new QTreeWidgetItem(fileItem);
        matchItem->setText(0, QFileInfo(result.filePath).fileName());
        matchItem->setText(1, QString::number(result.line + 1));
        matchItem->setText(2, result.preview);
        matchItem->setToolTip(0, result.filePath);
        matchItem->setToolTip(2, result.preview);
        matchItem->setData(0, Qt::UserRole, i);
    }

    for (auto it = fileItems.begin(); it != fileItems.end(); ++it) {
        it.value()->setText(
            0,
            QStringLiteral("%1  (%2)")
                .arg(QFileInfo(it.key()).fileName())
                .arg(it.value()->childCount()));
        it.value()->setExpanded(true);
    }

    updateButtonStates();
}

const QList<ProjectSearchResult> &FindReplaceDialog::results() const
{
    return m_results;
}

QList<int> FindReplaceDialog::selectedResultIndexes() const
{
    QList<int> indexes;

    for (QTreeWidgetItem *item : m_resultsTree->selectedItems()) {
        const int index = resultIndexForItem(item);
        if (index >= 0 && !indexes.contains(index)) {
            indexes.append(index);
        }
    }

    std::sort(indexes.begin(), indexes.end());
    return indexes;
}

int FindReplaceDialog::resultIndexForItem(QTreeWidgetItem *item) const
{
    if (!item || item->childCount() > 0) {
        return -1;
    }

    bool ok = false;
    const int index = item->data(0, Qt::UserRole).toInt(&ok);

    if (!ok || index < 0 || index >= m_results.size()) {
        return -1;
    }

    return index;
}

void FindReplaceDialog::updateButtonStates()
{
    const bool hasFindText = !m_findEdit->text().isEmpty();
    const bool hasResults = !m_results.isEmpty();
    const bool hasSelection = !selectedResultIndexes().isEmpty();

    m_findAllButton->setEnabled(hasFindText);
    m_replaceSelectedButton->setEnabled(
        hasFindText && hasResults && hasSelection);
    m_replaceAllButton->setEnabled(
        hasFindText && hasResults);
}
