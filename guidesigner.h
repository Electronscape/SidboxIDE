#ifndef GUIDESIGNER_H
#define GUIDESIGNER_H

#include <QString>
#include <QWidget>
#include <functional>

/*
 * Small public interface between MainWindow and the CoderGirl visual designer.
 * The actual designer/render/generator implementation lives in guidesigner.cpp.
 */
class SidboxGuiDesigner : public QWidget
{
public:
    explicit SidboxGuiDesigner(QWidget *parent = nullptr)
        : QWidget(parent)
    {
    }

    ~SidboxGuiDesigner() override = default;

    std::function<void()> tabTitleChanged;
    std::function<bool(const QString &)> beforeGenerate;
    std::function<void(const QString &, const QString &)> generatedFilesChanged;
    std::function<void(const QString &,
                       const QString &,
                       const QString &)> sourceNavigationRequested;

    virtual QString filePath() const = 0;
    virtual bool isModified() const = 0;
    virtual QString displayName() const = 0;
    virtual bool saveDesignAndGenerate() = 0;
};

SidboxGuiDesigner *createSidboxGuiDesigner(
    const QString &filePath,
    QWidget *parent = nullptr);

#endif // GUIDESIGNER_H
