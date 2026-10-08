#include "projectsettingsdialog.h"

#include <QCheckBox>
#include <QComboBox>
#include <QDialogButtonBox>
#include <QDir>
#include <QFileDialog>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSignalBlocker>
#include <QSpinBox>
#include <QTabWidget>
#include <QVBoxLayout>

ProjectSettingsDialog::ProjectSettingsDialog(QWidget *parent)
    : QDialog(parent)
    , m_tabs(new QTabWidget(this))
    , m_projectTypeCombo(new QComboBox(this))
    , m_optimizationCombo(new QComboBox(this))
    , m_suppressWarningsCheck(new QCheckBox(tr("Suppress all compiler warnings (-w)"), this))
    , m_wallCheck(new QCheckBox(tr("Common warnings (-Wall)"), this))
    , m_wextraCheck(new QCheckBox(tr("Extra warnings (-Wextra)"), this))
    , m_functionSectionsCheck(new QCheckBox(tr("Function sections (-ffunction-sections)"), this))
    , m_dataSectionsCheck(new QCheckBox(tr("Data sections (-fdata-sections)"), this))
    , m_stackUsageCheck(new QCheckBox(tr("Generate stack usage files (-fstack-usage)"), this))
    , m_extraCompilerFlagsEdit(new QLineEdit(this))
    , m_modSizeSpinBox(new QSpinBox(this))
    , m_appSizeSpinBox(new QSpinBox(this))
    , m_outputAppNameEdit(new QLineEdit(this))
    , m_linkerScriptEdit(new QLineEdit(this))
    , m_defaultLinkerLabel(new QLabel(this))
{
    setWindowTitle(tr("Project Settings"));

    m_projectTypeCombo->addItem(tr("GUI"), QStringLiteral("gui"));
    m_projectTypeCombo->addItem(tr("Game"), QStringLiteral("game"));
    connect(m_projectTypeCombo, &QComboBox::currentIndexChanged, this, [this]() {
        updateDefaultLinkerLabel();
    });

    m_modSizeSpinBox->setRange(0, 1024 * 1024);
    m_modSizeSpinBox->setSingleStep(8);
    m_modSizeSpinBox->setSuffix(tr(" KB"));
    m_modSizeSpinBox->setSpecialValueText(tr("Not set"));

    m_appSizeSpinBox->setRange(16, 1024 * 1024);
    m_appSizeSpinBox->setSingleStep(8);
    m_appSizeSpinBox->setSuffix(tr(" KB"));

    m_outputAppNameEdit->setPlaceholderText(
        tr("Leave blank to use the project name (example: run.app)"));
    m_outputAppNameEdit->setToolTip(
        tr("Filename for the compiled Sidbox .app beside the project. "
           "If .app is omitted, the IDE adds it automatically."));

    m_linkerScriptEdit->setPlaceholderText(tr("Use default for project type"));

    auto *browseButton = new QPushButton(tr("Browse"), this);
    connect(browseButton, &QPushButton::clicked, this, [this]() {
        const QString path = QFileDialog::getOpenFileName(
            this,
            tr("Select Linker Script"),
            m_linkerScriptEdit->text(),
            tr("Linker scripts (*.ld);;All files (*)"));

        if (!path.isEmpty()) {
            m_linkerScriptEdit->setText(path);
        }
    });

    auto *defaultButton = new QPushButton(tr("Default"), this);
    connect(defaultButton, &QPushButton::clicked, m_linkerScriptEdit, &QLineEdit::clear);

    auto *linkerLayout = new QHBoxLayout;
    linkerLayout->addWidget(m_linkerScriptEdit, 1);
    linkerLayout->addWidget(browseButton);
    linkerLayout->addWidget(defaultButton);

    auto *generalPage = new QWidget(this);
    auto *formLayout = new QFormLayout(generalPage);
    formLayout->setContentsMargins(12, 12, 12, 12);
    formLayout->addRow(tr("Project type"), m_projectTypeCombo);
    formLayout->addRow(tr("Applet size:"), m_appSizeSpinBox);
    formLayout->addRow(tr("Output .app name"), m_outputAppNameEdit);
    formLayout->addRow(tr("MOD size"), m_modSizeSpinBox);
    formLayout->addRow(tr("Linker script"), linkerLayout);
    formLayout->addRow(tr("Default linker"), m_defaultLinkerLabel);
    m_tabs->addTab(generalPage, tr("General"));

    m_optimizationCombo->addItem(tr("No optimisation (-O0)"), QStringLiteral("-O0"));
    m_optimizationCombo->addItem(tr("Debug-friendly (-Og)"), QStringLiteral("-Og"));
    m_optimizationCombo->addItem(tr("Level 1 (-O1)"), QStringLiteral("-O1"));
    m_optimizationCombo->addItem(tr("Level 2 (-O2)"), QStringLiteral("-O2"));
    m_optimizationCombo->addItem(tr("Level 3 (-O3)"), QStringLiteral("-O3"));
    m_optimizationCombo->addItem(tr("Optimise for size (-Os)"), QStringLiteral("-Os"));
    m_optimizationCombo->addItem(tr("Aggressive / fastest (-Ofast)"), QStringLiteral("-Ofast"));

    m_extraCompilerFlagsEdit->setPlaceholderText(
        tr("Example: -fno-strict-aliasing -Wconversion"));

    auto *compilerPage = new QWidget(this);
    auto *compilerForm = new QFormLayout(compilerPage);
    compilerForm->setContentsMargins(12, 12, 12, 12);
    compilerForm->addRow(tr("Optimisation"), m_optimizationCombo);
    compilerForm->addRow(QString(), m_functionSectionsCheck);
    compilerForm->addRow(QString(), m_dataSectionsCheck);
    compilerForm->addRow(QString(), m_stackUsageCheck);
    compilerForm->addRow(QString(), m_suppressWarningsCheck);
    compilerForm->addRow(QString(), m_wallCheck);
    compilerForm->addRow(QString(), m_wextraCheck);
    compilerForm->addRow(tr("Extra compiler flags"), m_extraCompilerFlagsEdit);

    auto *compilerNote = new QLabel(
        tr("These settings are stored in this project's .proj file. "
           "Warnings are shown in orange in the compile output; errors stay red."),
        compilerPage);
    compilerNote->setWordWrap(true);
    compilerForm->addRow(compilerNote);

    connect(m_suppressWarningsCheck, &QCheckBox::toggled,
            this, [this](bool suppressed) {
                if (!suppressed) {
                    return;
                }
                const QSignalBlocker wallBlock(m_wallCheck);
                const QSignalBlocker extraBlock(m_wextraCheck);
                m_wallCheck->setChecked(false);
                m_wextraCheck->setChecked(false);
            });

    connect(m_wallCheck, &QCheckBox::toggled,
            this, [this](bool enabled) {
                if (enabled) {
                    const QSignalBlocker blocker(m_suppressWarningsCheck);
                    m_suppressWarningsCheck->setChecked(false);
                }
            });

    connect(m_wextraCheck, &QCheckBox::toggled,
            this, [this](bool enabled) {
                if (enabled) {
                    const QSignalBlocker blocker(m_suppressWarningsCheck);
                    m_suppressWarningsCheck->setChecked(false);
                }
            });

    m_tabs->addTab(compilerPage, tr("Compiler"));

    auto *buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(buttons, &QDialogButtonBox::accepted, this, &ProjectSettingsDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, this, &ProjectSettingsDialog::reject);

    auto *layout = new QVBoxLayout(this);
    layout->addWidget(m_tabs);
    layout->addWidget(buttons);

    resize(700, 460);
}

QString ProjectSettingsDialog::projectType() const
{
    return m_projectTypeCombo->currentData().toString();
}

void ProjectSettingsDialog::setProjectType(const QString &projectType)
{
    const int index = m_projectTypeCombo->findData(projectType == QStringLiteral("game")
        ? QStringLiteral("game")
        : QStringLiteral("gui"));
    m_projectTypeCombo->setCurrentIndex(index < 0 ? 0 : index);
}

int ProjectSettingsDialog::modSizeKb() const
{
    return m_modSizeSpinBox->value();
}

void ProjectSettingsDialog::setModSizeKb(int sizeKb)
{
    m_modSizeSpinBox->setValue(sizeKb);
}

int ProjectSettingsDialog::appSizeKb() const
{
    return m_appSizeSpinBox->value();
}

void ProjectSettingsDialog::setAppSizeKb(int sizeKb)
{
    m_appSizeSpinBox->setValue(qMax(16, sizeKb));
}

QString ProjectSettingsDialog::outputAppName() const
{
    return m_outputAppNameEdit->text().trimmed();
}

void ProjectSettingsDialog::setOutputAppName(const QString &name)
{
    m_outputAppNameEdit->setText(name);
}

QString ProjectSettingsDialog::customLinkerScriptPath() const
{
    return m_linkerScriptEdit->text().trimmed();
}

void ProjectSettingsDialog::setCustomLinkerScriptPath(const QString &path)
{
    m_linkerScriptEdit->setText(path);
}

void ProjectSettingsDialog::setDefaultLinkerScriptPath(const QString &path)
{
    m_guiDefaultLinkerScriptPath = path;
    m_gameDefaultLinkerScriptPath = path;
    updateDefaultLinkerLabel();
}

void ProjectSettingsDialog::setDefaultLinkerScriptPaths(const QString &guiPath, const QString &gamePath)
{
    m_guiDefaultLinkerScriptPath = guiPath;
    m_gameDefaultLinkerScriptPath = gamePath;
    updateDefaultLinkerLabel();
}

void ProjectSettingsDialog::updateDefaultLinkerLabel()
{
    const QString path = projectType() == QStringLiteral("game")
        ? m_gameDefaultLinkerScriptPath
        : m_guiDefaultLinkerScriptPath;
    m_defaultLinkerLabel->setText(QDir::toNativeSeparators(path));
}


QString ProjectSettingsDialog::optimizationFlag() const
{
    return m_optimizationCombo->currentData().toString();
}

void ProjectSettingsDialog::setOptimizationFlag(const QString &flag)
{
    const int index = m_optimizationCombo->findData(flag);
    const int fallback = m_optimizationCombo->findData(QStringLiteral("-Ofast"));
    m_optimizationCombo->setCurrentIndex(index >= 0 ? index : fallback);
}

bool ProjectSettingsDialog::suppressWarnings() const
{
    return m_suppressWarningsCheck->isChecked();
}

void ProjectSettingsDialog::setSuppressWarnings(bool enabled)
{
    m_suppressWarningsCheck->setChecked(enabled);
}

bool ProjectSettingsDialog::wallEnabled() const
{
    return m_wallCheck->isChecked();
}

void ProjectSettingsDialog::setWallEnabled(bool enabled)
{
    m_wallCheck->setChecked(enabled);
}

bool ProjectSettingsDialog::wextraEnabled() const
{
    return m_wextraCheck->isChecked();
}

void ProjectSettingsDialog::setWextraEnabled(bool enabled)
{
    m_wextraCheck->setChecked(enabled);
}

bool ProjectSettingsDialog::functionSectionsEnabled() const
{
    return m_functionSectionsCheck->isChecked();
}

void ProjectSettingsDialog::setFunctionSectionsEnabled(bool enabled)
{
    m_functionSectionsCheck->setChecked(enabled);
}

bool ProjectSettingsDialog::dataSectionsEnabled() const
{
    return m_dataSectionsCheck->isChecked();
}

void ProjectSettingsDialog::setDataSectionsEnabled(bool enabled)
{
    m_dataSectionsCheck->setChecked(enabled);
}

bool ProjectSettingsDialog::stackUsageEnabled() const
{
    return m_stackUsageCheck->isChecked();
}

void ProjectSettingsDialog::setStackUsageEnabled(bool enabled)
{
    m_stackUsageCheck->setChecked(enabled);
}

QString ProjectSettingsDialog::extraCompilerFlags() const
{
    return m_extraCompilerFlagsEdit->text().trimmed();
}

void ProjectSettingsDialog::setExtraCompilerFlags(const QString &flags)
{
    m_extraCompilerFlagsEdit->setText(flags);
}
