#include "optionsdialog.h"

#include <QDialogButtonBox>
#include <QFileDialog>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QVBoxLayout>

OptionsDialog::OptionsDialog(QWidget *parent)
    : QDialog(parent)
    , m_linkerScriptEdit(new QLineEdit(this))
    , m_modSizeSpinBox(new QSpinBox(this))
{
    setWindowTitle(tr("Options"));

    m_linkerScriptEdit->setPlaceholderText(tr("Optional .ld linker script"));

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

    auto *linkerLayout = new QHBoxLayout;
    linkerLayout->addWidget(m_linkerScriptEdit, 1);
    linkerLayout->addWidget(browseButton);

    m_modSizeSpinBox->setRange(0, 1024 * 1024);
    m_modSizeSpinBox->setSuffix(tr(" KB"));
    m_modSizeSpinBox->setSpecialValueText(tr("Not set"));

    auto *formLayout = new QFormLayout;
    formLayout->addRow(tr("Linker script"), linkerLayout);
    formLayout->addRow(tr("MOD size"), m_modSizeSpinBox);

    auto *buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(buttons, &QDialogButtonBox::accepted, this, &OptionsDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, this, &OptionsDialog::reject);

    auto *layout = new QVBoxLayout(this);
    layout->addLayout(formLayout);
    layout->addWidget(buttons);
}

QString OptionsDialog::linkerScriptPath() const
{
    return m_linkerScriptEdit->text().trimmed();
}

void OptionsDialog::setLinkerScriptPath(const QString &path)
{
    m_linkerScriptEdit->setText(path);
}

int OptionsDialog::modSizeKb() const
{
    return m_modSizeSpinBox->value();
}

void OptionsDialog::setModSizeKb(int sizeKb)
{
    m_modSizeSpinBox->setValue(sizeKb);
}
