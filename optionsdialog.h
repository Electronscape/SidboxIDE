#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include "idetheme.h"

#include <QDialog>
#include <QHash>

class QComboBox;
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
    void setThemeDirectory(const QString &directory);

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
    bool applyThemeFile(const QString &filePath, bool preset);
    void refreshThemePresets();

    QSpinBox *m_fontSizeSpinBox;
    QComboBox *m_themePresetCombo = nullptr;
    QTabWidget *m_tabs;
    IDETheme m_theme;
    QString m_themeDirectory;
    QHash<QString, QPushButton *> m_colorButtons;
};

#endif // OPTIONSDIALOG_H
