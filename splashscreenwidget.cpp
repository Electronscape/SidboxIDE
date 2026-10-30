#include "splashscreenwidget.h"

#include <QColor>
#include <QGraphicsOpacityEffect>
#include <QGuiApplication>
#include <QHBoxLayout>
#include <QLabel>
#include <QPaintEvent>
#include <QPainter>
#include <QPen>
#include <QPixmap>
#include <QPropertyAnimation>
#include <QScreen>
#include <QSequentialAnimationGroup>
#include <QVBoxLayout>

namespace {
static constexpr int kSplashWidth = 760;
static constexpr int kSplashHeight = 420;
static constexpr int kFadeDurationMs = 300;
static constexpr int kHoldDurationMs = 3600;

// Display nagelgirl.png as a transparent background portrait, just like
// the About IDE tab.  This is not a separate icon/image box.
class SplashArtworkPanel final : public QWidget
{
public:
    explicit SplashArtworkPanel(const IDETheme &theme, QWidget *parent = nullptr)
        : QWidget(parent), m_theme(theme),
          m_portrait(QStringLiteral(":/icons/nagelgirl.png"))
    {
    }

protected:
    void paintEvent(QPaintEvent *event) override
    {
        Q_UNUSED(event);

        QPainter painter(this);
        painter.fillRect(rect(), m_theme.windowBackground);

        if (!m_portrait.isNull()) {
            const QSize imageBounds(qMax(1, width() * 49 / 100),
                                    qMax(1, height() - 4));
            const QPixmap portrait = m_portrait.scaled(imageBounds,
                                                       Qt::KeepAspectRatio,
                                                       Qt::SmoothTransformation);
            painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
            painter.drawPixmap(width() - portrait.width() - 2, 2, portrait);
        }

        // Sharp 90-degree corners throughout CoderGirl.
        painter.setPen(QPen(m_theme.accent, 2));
        painter.drawRect(rect().adjusted(1, 1, -2, -2));
    }

private:
    const IDETheme m_theme;
    const QPixmap m_portrait;
};
}

SplashScreenWidget::SplashScreenWidget(const IDETheme &theme, QWidget *parent)
    : QWidget(parent), m_theme(theme)
{
    setWindowFlags(Qt::SplashScreen | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setFixedSize(kSplashWidth, kSplashHeight);

    buildUi();
    centreOnPrimaryScreen();
}

void SplashScreenWidget::buildUi()
{
    auto *rootLayout = new QVBoxLayout(this);
    rootLayout->setContentsMargins(16, 16, 16, 16);

    auto *panel = new SplashArtworkPanel(m_theme, this);
    auto *panelLayout = new QHBoxLayout(panel);
    panelLayout->setContentsMargins(32, 30, 24, 26);

    // Place the wording directly over the painted panel, leaving the portrait
    // on the right as background artwork.  No opaque child container.
    auto *textColumn = new QVBoxLayout;
    textColumn->setSpacing(12);

    auto *titleLabel = new QLabel(QStringLiteral("Loading CoderGirl IDE"), panel);
    titleLabel->setFixedWidth(400);
    titleLabel->setWordWrap(true);
    titleLabel->setStyleSheet(QStringLiteral(
        "QLabel { background: transparent; border: none; border-radius:0px; "
        "font-size:30px; font-weight:bold; color:%1; }")
        .arg(ideThemeColorName(m_theme.brightText)));

    auto *subtitleLabel = new QLabel(QStringLiteral("Sidbox development suite V1.0"), panel);
    subtitleLabel->setWordWrap(true);
    subtitleLabel->setStyleSheet(QStringLiteral(
        "QLabel { background:transparent; border:none; border-radius:0px; "
        "font-size:19px; color:%1; }")
        .arg(ideThemeColorName(m_theme.text)));

    // Bump the stage and release date (DDMMYY) when publishing a new IDE build.
    auto *buildLabel = new QLabel(QStringLiteral("Build: 5.166.123.301026"), panel);
    buildLabel->setStyleSheet(QStringLiteral(
        "QLabel { background:transparent; border:none; border-radius:0px; "
        "font-size:15px; font-weight:bold; color:%1; }")
        .arg(ideThemeColorName(m_theme.accent)));

    auto *footerLabel = new QLabel(QStringLiteral("Preparing IDE..."), panel);
    footerLabel->setStyleSheet(QStringLiteral(
        "QLabel { background:transparent; border:none; border-radius:0px; "
        "font-size:16px; font-weight:bold; color:%1; }")
        .arg(ideThemeColorName(m_theme.accent)));

    textColumn->addWidget(titleLabel);
    textColumn->addWidget(subtitleLabel);
    textColumn->addWidget(buildLabel);
    textColumn->addStretch(1);
    textColumn->addWidget(footerLabel);

    panelLayout->addLayout(textColumn);
    panelLayout->addStretch(1);
    rootLayout->addWidget(panel);

    m_opacityEffect = new QGraphicsOpacityEffect(this);
    m_opacityEffect->setOpacity(0.0);
    setGraphicsEffect(m_opacityEffect);
}

void SplashScreenWidget::centreOnPrimaryScreen()
{
    if (QScreen *screen = QGuiApplication::primaryScreen()) {
        const QRect available = screen->availableGeometry();
        move(available.center() - rect().center());
    }
}

void SplashScreenWidget::start()
{
    m_finished = false;
    show();
    raise();

    auto *sequence = new QSequentialAnimationGroup(this);

    auto *fadeIn = new QPropertyAnimation(m_opacityEffect, "opacity", sequence);
    fadeIn->setDuration(kFadeDurationMs);
    fadeIn->setStartValue(0.0);
    fadeIn->setEndValue(1.0);

    auto *hold = new QPropertyAnimation(m_opacityEffect, "opacity", sequence);
    hold->setDuration(kHoldDurationMs);
    hold->setStartValue(1.0);
    hold->setEndValue(1.0);

    auto *fadeOut = new QPropertyAnimation(m_opacityEffect, "opacity", sequence);
    fadeOut->setDuration(kFadeDurationMs);
    fadeOut->setStartValue(1.0);
    fadeOut->setEndValue(0.0);

    sequence->addAnimation(fadeIn);
    sequence->addAnimation(hold);
    sequence->addAnimation(fadeOut);

    connect(sequence, &QSequentialAnimationGroup::finished, this, [this, sequence]() {
        m_finished = true;
        hide();
        emit splashFinished();
        sequence->deleteLater();
        deleteLater();
    });

    sequence->start();
}
