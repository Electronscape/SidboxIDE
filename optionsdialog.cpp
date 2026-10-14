#include "optionsdialog.h"

#include <QColorDialog>
#include <QComboBox>
#include <QDir>
#include <QSignalBlocker>
#include <QSizePolicy>
#include <QDialogButtonBox>
#include <QFileDialog>
#include <QFileInfo>
#include <QFrame>
#include <QFormLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QScrollArea>
#include <QSettings>
#include <QSpinBox>
#include <QTabWidget>
#include <QVBoxLayout>

namespace {
QString themeFilter()
{
    return QObject::tr("Sidbox themes (*.sidtheme);;All files (*)");
}
}

OptionsDialog::OptionsDialog(QWidget *parent)
    : QDialog(parent)
    , m_fontSizeSpinBox(new QSpinBox(this))
    , m_tabs(new QTabWidget(this))
    , m_theme(defaultIDETheme())
{
    setWindowTitle(tr("Options"));
    resize(760, 650);
    setMinimumSize(680, 560);

    m_fontSizeSpinBox->setRange(6, 36);
    m_fontSizeSpinBox->setSuffix(tr(" pt"));

    auto *generalPage = new QWidget(this);
    auto *generalLayout = new QFormLayout(generalPage);
    generalLayout->setContentsMargins(12, 12, 12, 12);
    generalLayout->addRow(tr("Editor font size"), m_fontSizeSpinBox);

    // Themes are ordinary .sidtheme INI files shipped beside the SDK.
    // Choosing a preset only changes this dialog's working copy; pressing
    // Cancel leaves all IDE colours and the editor font unchanged.
    m_themePresetCombo = new QComboBox(generalPage);
    m_themePresetCombo->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_themePresetCombo->setMinimumContentsLength(28);
    generalLayout->addRow(tr("Theme preset"), m_themePresetCombo);
    connect(m_themePresetCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, [this](int index) {
        if (index <= 0) return; // Current custom theme is the initial choice.
        const QString filePath = m_themePresetCombo->itemData(index).toString();
        if (!filePath.isEmpty() && !applyThemeFile(filePath, true)) {
            const QSignalBlocker blocker(m_themePresetCombo);
            m_themePresetCombo->setCurrentIndex(0);
        }
    });

    auto *presetNote = new QLabel(
        tr("Theme packs are loaded from idelibs/themes. You can edit individual "
           "colours below, then Save to apply. Cancel keeps your existing theme."),
        generalPage);
    presetNote->setWordWrap(true);
    generalLayout->addRow(presetNote);

    auto *generalNote = new QLabel(
        tr("Theme colours are applied to all open editors when you press Save."),
        generalPage);
    generalNote->setWordWrap(true);
    generalLayout->addRow(generalNote);

    m_tabs->addTab(generalPage, tr("General"));

    m_tabs->addTab(
        createColorPage({
            {"Window background", "windowBackground"},
            {"Panel background", "panelBackground"},
            {"Input / tree background", "inputBackground"},
            {"Alternate row background", "alternateBackground"},
            {"Menu background", "menuBackground"},
            {"Normal text", "text"},
            {"Bright text", "brightText"},
            {"Muted text", "mutedText"},
            {"Accent / selection", "accent"},
            {"Hover", "hover"},
            {"Border", "border"},
            {"Tree / pane border", "treeBorder"},
            {"Scroll handle", "scrollHandle"},
            {"Scroll handle hover", "scrollHandleHover"},
            {"Tooltip background", "tooltipBackground"},
            {"Tooltip text", "tooltipText"}
        }),
        tr("Interface"));

    m_tabs->addTab(
        createColorPage({
            {"Editor background", "editorBackground"},
            {"Editor text", "editorText"},
            {"Current line", "currentLine"},
            {"Gutter background", "gutterBackground"},
            {"Line numbers", "lineNumber"},
            {"Indent guides", "indentGuide"},
            {"Selection background", "selectionBackground"},
            {"Selection text", "selectionText"}
        }),
        tr("Editor"));

    m_tabs->addTab(
        createColorPage({
            {"Keywords", "syntaxKeyword"},
            {"STM32 / alignment", "syntaxSTM32"},
            {"Sidbox API", "syntaxAPI"},
            {"typedef / user types", "syntaxType"},
            {"Preprocessor", "syntaxPreprocessor"},
            {"Strings / chars", "syntaxString"},
            {"Numbers", "syntaxNumber"},
            {"Functions", "syntaxFunction"},
            {"Single-line comments", "syntaxComment"},
            {"Multi-line comments", "syntaxMultiComment"}
        }),
        tr("Syntax"));

    m_tabs->addTab(
        createColorPage({
            {"Error", "diagnosticError"},
            {"Warning", "diagnosticWarning"},
            {"Popup background", "diagnosticPopupBackground"},
            {"Popup text", "diagnosticPopupText"},
            {"Column text", "diagnosticColumn"}
        }),
        tr("Diagnostics"));

    m_tabs->addTab(
        createColorPage({
            {"Background", "minimapBackground"},
            {"Normal source", "minimapText"},
            {"Comments", "minimapComment"},
            {"Preprocessor", "minimapPreprocessor"},
            {"Types", "minimapType"},
            {"Strings", "minimapString"},
            {"Functions", "minimapFunction"},
            {"Viewport fill", "minimapViewportFill"},
            {"Viewport border", "minimapViewportBorder"},
            {"Divider", "minimapDivider"}
        }),
        tr("Minimap"));

    m_tabs->addTab(
        createColorPage({
            {"Output background", "outputBackground"},
            {"Normal output", "outputNormal"},
            {"Header", "outputHeader"},
            {"Path", "outputPath"},
            {"Success", "outputSuccess"},
            {"Error", "outputError"},
            {"Warning", "outputWarning"},
            {"Muted", "outputMuted"},
            {"Quick-tip background", "quickTipBackground"},
            {"Quick-tip text", "quickTipText"},
            {"Quick-tip border", "quickTipBorder"}
        }),
        tr("Output"));

    auto *loadButton = new QPushButton(tr("Load Theme..."), this);
    auto *saveThemeButton = new QPushButton(tr("Save Theme..."), this);
    auto *defaultsButton = new QPushButton(tr("Defaults"), this);
    auto *refreshPresetsButton = new QPushButton(tr("Refresh Presets"), this);
    connect(refreshPresetsButton, &QPushButton::clicked,
            this, &OptionsDialog::refreshThemePresets);

    connect(loadButton, &QPushButton::clicked,
            this, &OptionsDialog::loadThemeFromFile);
    connect(saveThemeButton, &QPushButton::clicked,
            this, &OptionsDialog::saveThemeToFile);
    connect(defaultsButton, &QPushButton::clicked,
            this, &OptionsDialog::resetDefaults);

    auto *themeButtons = new QHBoxLayout;
    themeButtons->addWidget(loadButton);
    themeButtons->addWidget(saveThemeButton);
    themeButtons->addWidget(defaultsButton);
    themeButtons->addWidget(refreshPresetsButton);
    themeButtons->addStretch(1);

    auto *buttons = new QDialogButtonBox(
        QDialogButtonBox::Save | QDialogButtonBox::Cancel,
        this);
    buttons->button(QDialogButtonBox::Save)->setText(tr("Save"));
    connect(buttons, &QDialogButtonBox::accepted,
            this, &OptionsDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected,
            this, &OptionsDialog::reject);

    auto *layout = new QVBoxLayout(this);
    layout->addWidget(m_tabs, 1);
    layout->addLayout(themeButtons);
    layout->addWidget(buttons);

    refreshThemePresets();
    refreshColorButtons();
}

QWidget *OptionsDialog::createColorPage(
    const QList<QPair<QString, QString>> &entries)
{
    auto *contents = new QWidget(this);
    auto *form = new QFormLayout(contents);
    form->setContentsMargins(12, 12, 12, 12);
    form->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);

    for (const auto &entry : entries) {
        addColorRow(form, entry.first, entry.second);
    }

    auto *scroll = new QScrollArea(this);
    scroll->setWidgetResizable(true);
    scroll->setFrameShape(QFrame::NoFrame);
    scroll->setWidget(contents);
    return scroll;
}

void OptionsDialog::addColorRow(
    QFormLayout *layout,
    const QString &label,
    const QString &key)
{
    auto *button = new QPushButton(this);
    button->setMinimumWidth(190);
    button->setCursor(Qt::PointingHandCursor);

    m_colorButtons.insert(key, button);

    connect(button, &QPushButton::clicked, this, [this, key]() {
        chooseColor(key);
    });

    layout->addRow(label, button);
}

QColor *OptionsDialog::colorForKey(const QString &key)
{
    for (const IDEThemeColorField &field : ideThemeColorFields()) {
        if (key == QLatin1String(field.key)) {
            return &(m_theme.*(field.member));
        }
    }
    return nullptr;
}

const QColor *OptionsDialog::colorForKey(const QString &key) const
{
    for (const IDEThemeColorField &field : ideThemeColorFields()) {
        if (key == QLatin1String(field.key)) {
            return &(m_theme.*(field.member));
        }
    }
    return nullptr;
}

void OptionsDialog::chooseColor(const QString &key)
{
    QColor *color = colorForKey(key);
    if (!color) {
        return;
    }

    QColorDialog dialog(*color, this);
    dialog.setWindowTitle(tr("Choose colour"));
    dialog.setOption(QColorDialog::ShowAlphaChannel, true);

    if (dialog.exec() != QDialog::Accepted) {
        return;
    }

    *color = dialog.selectedColor();
    if (m_themePresetCombo) {
        const QSignalBlocker blocker(m_themePresetCombo);
        m_themePresetCombo->setCurrentIndex(0);
    }
    refreshColorButtons();
}

void OptionsDialog::refreshColorButtons()
{
    for (auto it = m_colorButtons.begin();
         it != m_colorButtons.end();
         ++it) {

        const QColor *color = colorForKey(it.key());
        if (!color || !color->isValid()) {
            continue;
        }

        const QString hex = ideThemeColorName(*color);
        const QColor foreground =
            color->lightness() < 128 ? QColor(Qt::white) : QColor(Qt::black);

        it.value()->setText(hex);
        it.value()->setStyleSheet(
            QStringLiteral(
                "QPushButton {"
                " background:%1;"
                " color:%2;"
                " border:1px solid #666666;"
                " padding:5px 10px;"
                " border-radius:0px;"
                "}")
                .arg(hex, foreground.name()));
    }
}

void OptionsDialog::resetDefaults()
{
    m_theme = defaultIDETheme();
    m_fontSizeSpinBox->setValue(10);
    if (m_themePresetCombo) {
        const QSignalBlocker blocker(m_themePresetCombo);
        m_themePresetCombo->setCurrentIndex(0);
    }
    refreshColorButtons();
}

void OptionsDialog::saveThemeToFile()
{
    QString filePath = QFileDialog::getSaveFileName(
        this,
        tr("Save Theme"),
        m_themeDirectory.isEmpty()
            ? QStringLiteral("sidbox-theme.sidtheme")
            : QDir(m_themeDirectory).filePath(QStringLiteral("my-theme.sidtheme")),
        themeFilter());

    if (filePath.isEmpty()) {
        return;
    }

    if (QFileInfo(filePath).suffix().isEmpty()) {
        filePath += QStringLiteral(".sidtheme");
    }

    QSettings settings(filePath, QSettings::IniFormat);
    settings.clear();
    settings.setValue(QStringLiteral("theme/version"), 1);
    settings.setValue(QStringLiteral("theme/name"), QFileInfo(filePath).completeBaseName());
    settings.setValue(
        QStringLiteral("editor/fontPointSize"),
        m_fontSizeSpinBox->value());

    for (const IDEThemeColorField &field : ideThemeColorFields()) {
        settings.setValue(
            QStringLiteral("colours/") + QLatin1String(field.key),
            ideThemeColorName(m_theme.*(field.member)));
    }

    settings.sync();

    if (settings.status() != QSettings::NoError) {
        QMessageBox::warning(
            this,
            tr("Save Theme"),
            tr("The theme could not be saved."));
    } else {
        refreshThemePresets();
    }
}

void OptionsDialog::loadThemeFromFile()
{
    const QString filePath = QFileDialog::getOpenFileName(
        this,
        tr("Load Theme"),
        m_themeDirectory,
        themeFilter());

    if (filePath.isEmpty()) return;
    if (applyThemeFile(filePath, false) && m_themePresetCombo) {
        const QSignalBlocker blocker(m_themePresetCombo);
        m_themePresetCombo->setCurrentIndex(0);
    }
}

bool OptionsDialog::applyThemeFile(const QString &filePath, bool preset)
{
    if (!QFileInfo(filePath).isReadable()) {
        QMessageBox::warning(this, tr("Load Theme"),
                             tr("Cannot read theme:\n%1").arg(filePath));
        return false;
    }

    QSettings settings(filePath, QSettings::IniFormat);
    // Reject empty, corrupt or unrelated files rather than silently turning
    // a blank file into the Classic theme.
    if (settings.status() != QSettings::NoError ||
        !settings.contains(QStringLiteral("theme/version")) ||
        settings.value(QStringLiteral("theme/version")).toInt() != 1) {
        QMessageBox::warning(this, tr("Load Theme"),
                             tr("This is not a supported .sidtheme file:\n%1").arg(filePath));
        return false;
    }

    IDETheme loaded = preset ? defaultIDETheme() : m_theme;
    int validColours = 0;
    for (const IDEThemeColorField &field : ideThemeColorFields()) {
        const QString key = QStringLiteral("colours/") + QLatin1String(field.key);
        if (!settings.contains(key)) continue;
        const QColor colour(settings.value(key).toString());
        if (!colour.isValid()) {
            QMessageBox::warning(this, tr("Load Theme"),
                                 tr("Invalid colour '%1' in:\n%2")
                                     .arg(key, filePath));
            return false;
        }
        loaded.*(field.member) = colour;
        ++validColours;
    }
    if (!validColours) {
        QMessageBox::warning(this, tr("Load Theme"),
                             tr("No valid theme colours found in:\n%1").arg(filePath));
        return false;
    }
    const int font = settings.value(QStringLiteral("editor/fontPointSize"),
                                    m_fontSizeSpinBox->value()).toInt();
    if (settings.status() != QSettings::NoError) {
        QMessageBox::warning(this, tr("Load Theme"),
                             tr("Could not read theme:\n%1").arg(filePath));
        return false;
    }
    m_theme = loaded;
    m_fontSizeSpinBox->setValue(qBound(m_fontSizeSpinBox->minimum(), font,
                                       m_fontSizeSpinBox->maximum()));
    refreshColorButtons();
    return true;
}

void OptionsDialog::setThemeDirectory(const QString &directory)
{
    m_themeDirectory = directory;
    refreshThemePresets();
}

void OptionsDialog::refreshThemePresets()
{
    if (!m_themePresetCombo) return;
    const QSignalBlocker blocker(m_themePresetCombo);
    m_themePresetCombo->clear();
    m_themePresetCombo->addItem(tr("Current / custom colours"));

    QDir directory(m_themeDirectory);
    if (m_themeDirectory.isEmpty() || !directory.exists()) {
        m_themePresetCombo->setToolTip(
            tr("No theme folder found. Place .sidtheme files in:\n%1")
                .arg(m_themeDirectory));
        return;
    }

    const QFileInfoList files = directory.entryInfoList(
        QStringList{QStringLiteral("*.sidtheme")}, QDir::Files | QDir::Readable,
        QDir::Name | QDir::IgnoreCase);
    for (const QFileInfo &file : files) {
        QSettings ini(file.absoluteFilePath(), QSettings::IniFormat);
        if (ini.value(QStringLiteral("theme/version")).toInt() != 1 ||
            !ini.contains(QStringLiteral("colours/windowBackground")) ||
            ini.status() != QSettings::NoError)
            continue;
        QString name = ini.value(QStringLiteral("theme/name")).toString().trimmed();
        if (name.isEmpty()) name = file.completeBaseName();
        m_themePresetCombo->addItem(name, file.absoluteFilePath());
        m_themePresetCombo->setItemData(m_themePresetCombo->count() - 1,
                                         file.absoluteFilePath(), Qt::ToolTipRole);
    }
    m_themePresetCombo->setToolTip(
        tr("Choose a .sidtheme preset, customise the colours, then press Save."));
}

int OptionsDialog::editorFontPointSize() const
{
    return m_fontSizeSpinBox->value();
}

void OptionsDialog::setEditorFontPointSize(int pointSize)
{
    m_fontSizeSpinBox->setValue(pointSize);
}

IDETheme OptionsDialog::theme() const
{
    return m_theme;
}

void OptionsDialog::setTheme(const IDETheme &theme)
{
    m_theme = theme;
    refreshColorButtons();
}
