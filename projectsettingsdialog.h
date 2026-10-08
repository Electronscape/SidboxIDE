#ifndef PROJECTSETTINGSDIALOG_H
#define PROJECTSETTINGSDIALOG_H

#include <QDialog>
#include <QString>

class QCheckBox;
class QComboBox;
class QLabel;
class QLineEdit;
class QSpinBox;
class QTabWidget;

class ProjectSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProjectSettingsDialog(QWidget *parent = nullptr);

    QString projectType() const;
    void setProjectType(const QString &projectType);

    int modSizeKb() const;
    void setModSizeKb(int sizeKb);
    int appSizeKb() const;
    void setAppSizeKb(int sizeKb);

    QString outputAppName() const;
    void setOutputAppName(const QString &name);

    QString customLinkerScriptPath() const;
    void setCustomLinkerScriptPath(const QString &path);
    void setDefaultLinkerScriptPath(const QString &path);
    void setDefaultLinkerScriptPaths(const QString &guiPath, const QString &gamePath);

    QString optimizationFlag() const;
    void setOptimizationFlag(const QString &flag);
    bool suppressWarnings() const;
    void setSuppressWarnings(bool enabled);
    bool wallEnabled() const;
    void setWallEnabled(bool enabled);
    bool wextraEnabled() const;
    void setWextraEnabled(bool enabled);
    bool functionSectionsEnabled() const;
    void setFunctionSectionsEnabled(bool enabled);
    bool dataSectionsEnabled() const;
    void setDataSectionsEnabled(bool enabled);
    bool stackUsageEnabled() const;
    void setStackUsageEnabled(bool enabled);
    QString extraCompilerFlags() const;
    void setExtraCompilerFlags(const QString &flags);

private:
    void updateDefaultLinkerLabel();

    QTabWidget *m_tabs;
    QComboBox *m_projectTypeCombo;
    QComboBox *m_optimizationCombo;
    QCheckBox *m_suppressWarningsCheck;
    QCheckBox *m_wallCheck;
    QCheckBox *m_wextraCheck;
    QCheckBox *m_functionSectionsCheck;
    QCheckBox *m_dataSectionsCheck;
    QCheckBox *m_stackUsageCheck;
    QLineEdit *m_extraCompilerFlagsEdit;
    QSpinBox *m_modSizeSpinBox;
    QSpinBox *m_appSizeSpinBox;
    QLineEdit *m_outputAppNameEdit;
    QLineEdit *m_linkerScriptEdit;
    QLabel *m_defaultLinkerLabel;
    QString m_guiDefaultLinkerScriptPath;
    QString m_gameDefaultLinkerScriptPath;
};

#endif // PROJECTSETTINGSDIALOG_H
