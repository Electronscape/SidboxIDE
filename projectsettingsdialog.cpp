#include "projectsettingsdialog.h"

#include <QCheckBox>
#include <QComboBox>
#include <QDialogButtonBox>
#include <QDir>
#include <QFileDialog>
#include <QFileInfo>
#include <QFormLayout>
#include <QGroupBox>
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
    , m_appletFormatCombo(new QComboBox(this))
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
    , m_v2HeapSpinBox(new QSpinBox(this))
    , m_v2StackSpinBox(new QSpinBox(this))
    , m_v2PlanningGroup(new QGroupBox(tr("Experimental GUI Applet V2 - memory planning only"), this))
    , m_outputAppNameEdit(new QLineEdit(this))
    , m_linkerScriptEdit(new QLineEdit(this))
    , m_defaultLinkerLabel(new QLabel(this))
{
    setWindowTitle(tr("Project Settings"));

    m_projectTypeCombo->addItem(tr("GUI"), QStringLiteral("gui"));
    m_projectTypeCombo->addItem(tr("Game"), QStringLiteral("game"));
    connect(m_projectTypeCombo, &QComboBox::currentIndexChanged, this, [this]() {
        updateDefaultLinkerLabel();
        const bool gui = projectType() == QStringLiteral("gui");
        if (!gui) {
            m_appletFormatCombo->setCurrentIndex(0); // Game is always legacy v1.
        }
        m_appletFormatCombo->setEnabled(gui);
        m_v2PlanningGroup->setEnabled(gui);
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
    m_appletFormatCombo->addItem(tr("Legacy V1 - fixed SDRAM address"), QStringLiteral("v1"));
    m_appletFormatCombo->addItem(tr("Experimental V2 - relocatable GUI"), QStringLiteral("v2"));
    m_appletFormatCombo->setToolTip(tr("V2 requires PIE code and a compatible experimental firmware loader. "
                                        "Unsupported relocations or dependencies will cause a safe build failure."));
    formLayout->addRow(tr("Applet format"), m_appletFormatCombo);
    formLayout->addRow(tr("Applet size:"), m_appSizeSpinBox);
    formLayout->addRow(tr("Output .app name"), m_outputAppNameEdit);
    formLayout->addRow(tr("MOD size"), m_modSizeSpinBox);
    formLayout->addRow(tr("Linker script"), linkerLayout);
    formLayout->addRow(tr("Default linker"), m_defaultLinkerLabel);

    // V2 uses a dedicated PIE linker and strict relocation packer.
    // Stage 6C firmware runs opted-in V2 window/timer callbacks on private PSP.
    connect(m_appletFormatCombo, &QComboBox::currentIndexChanged, this, [this]() {
        updateDefaultLinkerLabel();
        m_v2PlanningGroup->setTitle(appletFormat() == QStringLiteral("v2")
            ? tr("Experimental V2 memory requirements")
            : tr("Experimental V2 memory requirements (V1 ignores these)"));
    });
    m_v2HeapSpinBox->setRange(0, 512);
    m_v2HeapSpinBox->setSingleStep(4);
    m_v2HeapSpinBox->setSuffix(tr(" KB"));
    m_v2HeapSpinBox->setSpecialValueText(tr("No heap reserved"));
    m_v2HeapSpinBox->setValue(16);
    m_v2StackSpinBox->setRange(4, 128);
    m_v2StackSpinBox->setSingleStep(4);
    m_v2StackSpinBox->setSuffix(tr(" KB"));
    m_v2StackSpinBox->setValue(8);
    auto *v2Form = new QFormLayout(m_v2PlanningGroup);
    v2Form->addRow(tr("V2 heap allowance"), m_v2HeapSpinBox);
    v2Form->addRow(tr("V2 private callback stack"), m_v2StackSpinBox);
    auto *v2Note = new QLabel(
        tr("V2 heap is bounded within the relocated applet. "
           "Stage 6C firmware uses the reserved PSP stack for window and timer callbacks; "
           "initial applet_entry still executes on CoderGirl's MSP. "
           "Requires Stage 6C-compatible firmware. "
           "Ordinary GNU/Newlib libraries may still fail V2 relocation checks; "
           "an unsupported build stops safely. V1 and gaming builds remain unchanged."),
        m_v2PlanningGroup);
    v2Note->setWordWrap(true);
    v2Form->addRow(v2Note);
    formLayout->addRow(m_v2PlanningGroup);
    m_v2PlanningGroup->setEnabled(true);
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

    resize(760, 560);
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

QString ProjectSettingsDialog::appletFormat() const
{
    return projectType() == QStringLiteral("game")
        ? QStringLiteral("v1") : m_appletFormatCombo->currentData().toString();
}

void ProjectSettingsDialog::setAppletFormat(const QString &format)
{
    m_appletFormatCombo->setCurrentIndex(format == QStringLiteral("v2") ? 1 : 0);
    if (projectType() == QStringLiteral("game"))
        m_appletFormatCombo->setCurrentIndex(0);
}

int ProjectSettingsDialog::v2HeapKb() const
{
    return m_v2HeapSpinBox->value();
}

void ProjectSettingsDialog::setV2HeapKb(int sizeKb)
{
    m_v2HeapSpinBox->setValue(sizeKb);
}

int ProjectSettingsDialog::v2StackKb() const
{
    return m_v2StackSpinBox->value();
}

void ProjectSettingsDialog::setV2StackKb(int sizeKb)
{
    m_v2StackSpinBox->setValue(sizeKb);
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
    QString path = projectType() == QStringLiteral("game")
        ? m_gameDefaultLinkerScriptPath
        : m_guiDefaultLinkerScriptPath;
    if (projectType() == QStringLiteral("gui") && appletFormat() == QStringLiteral("v2")) {
        path = QDir(QFileInfo(path).absolutePath()).filePath(QStringLiteral("gui_v2.ld"));
    }
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
