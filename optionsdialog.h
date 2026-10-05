#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include <QDialog>

class QSpinBox;

class OptionsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OptionsDialog(QWidget *parent = nullptr);

    int editorFontPointSize() const;
    void setEditorFontPointSize(int pointSize);

private:
    QSpinBox *m_fontSizeSpinBox;
};

#endif // OPTIONSDIALOG_H
