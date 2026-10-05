#ifndef PROJECTSETTINGSDIALOG_H
#define PROJECTSETTINGSDIALOG_H

#include <QDialog>
#include <QString>

class QComboBox;
class QLabel;
class QLineEdit;
class QSpinBox;

class ProjectSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProjectSettingsDialog(QWidget *parent = nullptr);

    QString projectType() const;
    void setProjectType(const QString &projectType);

    int modSizeKb() const;
    void setModSizeKb(int sizeKb);

    QString customLinkerScriptPath() const;
    void setCustomLinkerScriptPath(const QString &path);
    void setDefaultLinkerScriptPath(const QString &path);
    void setDefaultLinkerScriptPaths(const QString &guiPath, const QString &gamePath);

private:
    void updateDefaultLinkerLabel();

    QComboBox *m_projectTypeCombo;
    QSpinBox *m_modSizeSpinBox;
    QLineEdit *m_linkerScriptEdit;
    QLabel *m_defaultLinkerLabel;
    QString m_guiDefaultLinkerScriptPath;
    QString m_gameDefaultLinkerScriptPath;
};

#endif // PROJECTSETTINGSDIALOG_H
