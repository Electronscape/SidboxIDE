#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include "idetheme.h"

#include <QDialog>
#include <QHash>

class QFormLayout;
class QPushButton;
class QSpinBox;
class QTabWidget;

class OptionsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OptionsDialog(QWidget *parent = nullptr);

    int editorFontPointSize() const;
    void setEditorFontPointSize(int pointSize);

    IDETheme theme() const;
    void setTheme(const IDETheme &theme);

private:
    QWidget *createColorPage(
        const QList<QPair<QString, QString>> &entries);
    void addColorRow(
        QFormLayout *layout,
        const QString &label,
        const QString &key);
    QColor *colorForKey(const QString &key);
    const QColor *colorForKey(const QString &key) const;
    void chooseColor(const QString &key);
    void refreshColorButtons();
    void resetDefaults();
    void saveThemeToFile();
    void loadThemeFromFile();

    QSpinBox *m_fontSizeSpinBox;
    QTabWidget *m_tabs;
    IDETheme m_theme;
    QHash<QString, QPushButton *> m_colorButtons;
};

#endif // OPTIONSDIALOG_H
