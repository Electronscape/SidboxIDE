#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include <QDialog>
#include <QString>

class QLineEdit;
class QSpinBox;

class OptionsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OptionsDialog(QWidget *parent = nullptr);

    QString linkerScriptPath() const;
    void setLinkerScriptPath(const QString &path);

    int modSizeKb() const;
    void setModSizeKb(int sizeKb);

private:
    QLineEdit *m_linkerScriptEdit;
    QSpinBox *m_modSizeSpinBox;
};

#endif // OPTIONSDIALOG_H
