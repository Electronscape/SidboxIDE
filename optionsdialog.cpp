#include "optionsdialog.h"

#include <QDialogButtonBox>
#include <QFormLayout>
#include <QSpinBox>
#include <QVBoxLayout>

OptionsDialog::OptionsDialog(QWidget *parent)
    : QDialog(parent)
    , m_fontSizeSpinBox(new QSpinBox(this))
{
    setWindowTitle(tr("Options"));

    m_fontSizeSpinBox->setRange(6, 36);
    m_fontSizeSpinBox->setSuffix(tr(" pt"));

    auto *formLayout = new QFormLayout;
    formLayout->addRow(tr("Editor font size"), m_fontSizeSpinBox);

    auto *buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(buttons, &QDialogButtonBox::accepted, this, &OptionsDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, this, &OptionsDialog::reject);

    auto *layout = new QVBoxLayout(this);
    layout->addLayout(formLayout);
    layout->addWidget(buttons);
}

int OptionsDialog::editorFontPointSize() const
{
    return m_fontSizeSpinBox->value();
}

void OptionsDialog::setEditorFontPointSize(int pointSize)
{
    m_fontSizeSpinBox->setValue(pointSize);
}
