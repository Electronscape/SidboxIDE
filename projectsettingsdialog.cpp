#include "projectsettingsdialog.h"

#include <QComboBox>
#include <QDialogButtonBox>
#include <QDir>
#include <QFileDialog>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QVBoxLayout>

ProjectSettingsDialog::ProjectSettingsDialog(QWidget *parent)
    : QDialog(parent)
    , m_projectTypeCombo(new QComboBox(this))
    , m_modSizeSpinBox(new QSpinBox(this))
    , m_appSizeSpinBox(new QSpinBox(this))
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

    auto *formLayout = new QFormLayout;
    formLayout->addRow(tr("Project type"), m_projectTypeCombo);
    formLayout->addRow(tr("Applet size:"), m_appSizeSpinBox);
    formLayout->addRow(tr("MOD size"), m_modSizeSpinBox);
    formLayout->addRow(tr("Linker script"), linkerLayout);
    formLayout->addRow(tr("Default linker"), m_defaultLinkerLabel);

    auto *buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(buttons, &QDialogButtonBox::accepted, this, &ProjectSettingsDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, this, &ProjectSettingsDialog::reject);

    auto *layout = new QVBoxLayout(this);
    layout->addLayout(formLayout);
    layout->addWidget(buttons);
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
