#ifndef SPLASHSCREENWIDGET_H
#define SPLASHSCREENWIDGET_H

#include <QWidget>
#include "idetheme.h"

class QLabel;
class QGraphicsOpacityEffect;

class SplashScreenWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SplashScreenWidget(const IDETheme &theme, QWidget *parent = nullptr);

    void start();
    bool isFinished() const { return m_finished; }

signals:
    void splashFinished();

private:
    void buildUi();
    void centreOnPrimaryScreen();

    const IDETheme m_theme;
    QGraphicsOpacityEffect *m_opacityEffect = nullptr;
    bool m_finished = false;
};

#endif // SPLASHSCREENWIDGET_H
