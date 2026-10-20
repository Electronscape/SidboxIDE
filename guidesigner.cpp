#include "guidesigner.h"
#include "gameeditoricons.h"
#include "guidesigner_detail.h"

#include <algorithm>
#include <functional>
#include <utility>

#include <QAbstractItemView>
#include <QAbstractSpinBox>
#include <QAction>
#include <QByteArray>
#include <QCheckBox>
#include <QApplication>
#include <QClipboard>
#include <QButtonGroup>
#include <QDialog>
#include <QColor>
#include <QComboBox>
#include <QContextMenuEvent>
#include <QDir>
#include <QDirIterator>
#include <QDrag>
#include <QEvent>
#include <QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QFormLayout>
#include <QFont>
#include <QFontMetrics>
#include <QFocusEvent>
#include <QGridLayout>
#include <QHash>
#include <QHeaderView>
#include <QIcon>
#include <QHBoxLayout>
#include <QImage>
#include <QInputDialog>
#include <QIODevice>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QKeyEvent>
#include <QKeySequence>
#include <QLabel>
#include <QLineEdit>
#include <QList>
#include <QListWidget>
#include <QListView>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QMenu>
#include <QMimeData>
#include <QMouseEvent>
#include <QObject>
#include <QPaintEvent>
#include <QPainter>
#include <QPair>
#include <QPen>
#include <QPlainTextEdit>
#include <QPoint>
#include <QPointF>
#include <QPolygon>
#include <QPointer>
#include <QPixmap>
#include <QPushButton>
#include <QRect>
#include <QRegularExpression>
#include <QSaveFile>
#include <QSettings>
#include <QSignalBlocker>
#include <QScrollArea>
#include <QSizePolicy>
#include <QSet>
#include <QSize>
#include <QSpinBox>
#include <QStyle>
#include <QStyledItemDelegate>
#include <QStyleOptionViewItem>
#include <QSplitter>
#include <QTimer>
#include <QString>
#include <QStringList>
#include <QTableWidget>
#include <QTabWidget>
#include <QTextStream>
#include <QTimer>
#include <QToolBar>
#include <QToolButton>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QVBoxLayout>
#include <QWidget>


// Stage 3.71: internal editor components are kept in separate focused files.
namespace GuiDesignerDetail {
#include "guidesigner_palette_widgets.inc"
#include "guidesigner_canvas.inc"
#include "guidesigner_propertygrid.inc"
} // namespace GuiDesignerDetail

namespace {
using namespace GuiDesignerDetail;
class SidboxGuiDesignerImpl final : public SidboxGuiDesigner
{
public:
    explicit SidboxGuiDesignerImpl(const QString &filePath, QWidget *parent = nullptr)
        : SidboxGuiDesigner(parent)
        , m_filePath(QFileInfo(filePath).absoluteFilePath())
    {
        setProperty("sidboxGuiDesigner", true);
        setProperty("sidboxGuiDesignerPath", m_filePath);

        // Stage 4.14: inherit normal controls from QApplication's central
        // theme. Only the gadget-image palette needs a distinct grey surface.
        setStyleSheet(QStringLiteral(R"QSS(
            QListWidget#coderGirlGadgetPalette {
                background-color:#7B7B7B;
                alternate-background-color:#7B7B7B;
            }
            QTabWidget#coderGirlGadgetPaletteTabs::pane {
                background-color:#7B7B7B;
            }
        )QSS"));

        auto *outer = new QVBoxLayout(this);
        outer->setContentsMargins(0, 0, 0, 0);
        outer->setSpacing(0);

        auto *top = new QToolBar(this);
        top->setMovable(false);
        top->setIconSize(QSize(20, 20));
        m_undoAction =
            new QAction(
                QObject::tr("Undo"),
                this);

        m_undoAction->setShortcut(
            QKeySequence::Undo);

        m_undoAction->setShortcutContext(
            Qt::WidgetWithChildrenShortcut);

        m_undoAction->setEnabled(false);

        top->addAction(
            m_undoAction);

        QAction *save = top->addAction(QObject::tr("Save Design"));
        QAction *generate = top->addAction(QObject::tr("Generate..."));
        QAction *paletteAction = top->addAction(QObject::tr("Palette..."));
        connect(paletteAction, &QAction::triggered, this, [this]() {
            showPaletteDialog();
        });
        top->addWidget(new QLabel(QObject::tr("  Code: "), top));
        m_generationMode = new QComboBox(top);
        m_generationMode->addItem(QObject::tr("Normal (.c)"), false);
        m_generationMode->addItem(QObject::tr("Sketch / Detached (.uis)"), true);
        top->addWidget(m_generationMode);
        connect(m_generationMode, qOverload<int>(&QComboBox::currentIndexChanged),
                this, [this](int index) {
                    m_detached = m_generationMode->itemData(index).toBool();
                    setModified(true);
                });
        top->addSeparator();

        top->addWidget(
            new QLabel(
                QObject::tr("Snap:"),
                top));

        m_snapCombo =
            new QComboBox(top);

        m_snapCombo->addItem(
            QObject::tr("Off"),
            0);

        m_snapCombo->addItem(
            QObject::tr("2 px"),
            2);

        m_snapCombo->addItem(
            QObject::tr("4 px"),
            4);

        m_snapCombo->addItem(
            QObject::tr("8 px"),
            8);

        m_snapCombo->addItem(
            QObject::tr("16 px"),
            16);

        // Match the 4px default on new canvases. Loading an existing .sbui
        // overrides this with its own saved designerGridSnap setting.
        m_snapCombo->setCurrentIndex(m_snapCombo->findData(4));

        top->addWidget(
            m_snapCombo);

        top->addSeparator();
        top->addWidget(new QLabel(QObject::tr("Zoom:"), top));
        auto *zoom = new QComboBox(top);

        zoom->addItem(
            QStringLiteral("100%"),
            100);

        zoom->addItem(
            QStringLiteral("150%"),
            150);

        zoom->addItem(
            QStringLiteral("200%"),
            200);

        zoom->addItem(
            QStringLiteral("400%"),
            400);

        zoom->setCurrentIndex(
            2);

        top->addWidget(zoom);
        m_statusLabel = new QLabel(QObject::tr("480 × 320 Sidbox screen"), top);
        m_statusLabel->setContentsMargins(12, 0, 0, 0);
        top->addWidget(m_statusLabel);
        outer->addWidget(top);

        auto *splitter = new QSplitter(Qt::Horizontal, this);
        splitter->setChildrenCollapsible(false);
        outer->addWidget(splitter, 1);

        // Toolbox / menu editor ------------------------------------------------
        auto *left = new QWidget(splitter);
        left->setMinimumWidth(190);
        auto *leftLayout = new QVBoxLayout(left);
        leftLayout->setContentsMargins(6, 6, 6, 6);
        leftLayout->setSpacing(5);
        auto *toolLabel = new QLabel(QObject::tr("CoderGirl Gadget Palette"), left);
        leftLayout->addWidget(toolLabel);

        // Keep the graphic palette compact. Organise gadgets by what they do
        // rather than forcing all gadgets into a single scrolling list.
        m_toolboxTabs = new QTabWidget(left);
        m_toolboxTabs->setObjectName(QStringLiteral("coderGirlGadgetPaletteTabs"));
        m_toolboxTabs->setDocumentMode(true);

        const QHash<QString, QString> gadgetTooltips = {
            {QStringLiteral("BitmapView"), QObject::tr("Displays an indexed PNG bitmap")},
            {QStringLiteral("Button"), QObject::tr("Clickable button; supports activation callbacks")},
            {QStringLiteral("Canvas"), QObject::tr("Draws lines, rectangles and bevels")},
            {QStringLiteral("Checkbox"), QObject::tr("On/off checkbox with checked state")},
            {QStringLiteral("GridSelect"), QObject::tr("Selectable grid of text cells")},
            {QStringLiteral("Label"), QObject::tr("Static text label")},
            {QStringLiteral("ListBox"), QObject::tr("Scrollable list of selectable items")},
            {QStringLiteral("ProgressBar"), QObject::tr("Displays progress between minimum and maximum")},
            {QStringLiteral("Radio"), QObject::tr("Radio-style selection control")},
            {QStringLiteral("Scrollbar"), QObject::tr("Horizontal or vertical scrollbar")},
            {QStringLiteral("Slider"), QObject::tr("Adjustable numeric slider")},
            {QStringLiteral("TabGroup"), QObject::tr("Virtual grouped pages with selectable tabs")},
            {QStringLiteral("TextArea"), QObject::tr("Multi-line text area")},
            {QStringLiteral("TextBox"), QObject::tr("Single-line editable text")},
            {QStringLiteral("Timer"), QObject::tr("Virtual cooperative timer: callback without a visible gadget")},
            {QStringLiteral("Messenger"), QObject::tr("Virtual V2 IPC mailbox: receive applet messages through a cooperative callback")},
            {QStringLiteral("UART1"), QObject::tr("Exclusive USART1 lease: temporarily pause SIDBOX terminal, FTP and UART keyboard")},
            {QStringLiteral("KBInput"), QObject::tr("Passive key press/release events delivered to this focused window")},
            {QStringLiteral("MSInput"), QObject::tr("Passive mouse move/down/up events over this window; OS retains mouse control")},
            {QStringLiteral("Media"), QObject::tr("Virtual audio playback: sound effects or music; not a SIDBOX screen gadget")},
            {QStringLiteral("FileRequester"), QObject::tr("Non-modal CoderGirl file picker with select/cancel callbacks")},
            {QStringLiteral("MessageBox"), QObject::tr("Non-modal CoderGirl MessageBox or InfoBox with result callback")}
        };
        // Every gadget appears exactly once. The virtual components are
        // designer-only; TabGroup belongs with them, even though it creates
        // ordinary buttons and groups in generated SIDBOX code.
        const QList<QPair<QString, QStringList>> paletteGroups = {
            {QObject::tr("Controls"), {
                QStringLiteral("Button"), QStringLiteral("Checkbox"),
                QStringLiteral("GridSelect"), QStringLiteral("ListBox"),
                QStringLiteral("Radio"), QStringLiteral("Scrollbar"),
                QStringLiteral("Slider"), QStringLiteral("TextArea"),
                QStringLiteral("TextBox")}},
            {QObject::tr("Display"), {
                QStringLiteral("BitmapView"), QStringLiteral("Canvas"),
                QStringLiteral("Label"), QStringLiteral("ProgressBar")}},
            {QObject::tr("Virtual"), {
                QStringLiteral("FileRequester"), QStringLiteral("Media"),
                QStringLiteral("MessageBox"), QStringLiteral("Messenger"), QStringLiteral("TabGroup"),
                QStringLiteral("Timer"), QStringLiteral("UART1"),
                QStringLiteral("KBInput"), QStringLiteral("MSInput")}}
        };
        for (const auto &group : paletteGroups) {
            auto *palette = new GuiDesignerToolbox(m_toolboxTabs);
            palette->setObjectName(QStringLiteral("coderGirlGadgetPalette"));
            QStringList sortedGadgets = group.second;
            sortedGadgets.sort(Qt::CaseInsensitive);
            for (const QString &type : sortedGadgets) {
                // Each palette keeps the original 64x24 artwork, tooltips,
                // drag-out behaviour and double-click to create a gadget.
                const QString gadgetIconName =
                    QStringLiteral("gadget_%1.png").arg(type.toLower());
                const QString external = gameEditorIconOverride(gadgetIconName);
                QPixmap tile(external.isEmpty()
                    ? QStringLiteral(":/icons/") + gadgetIconName : external);
                if (tile.isNull()) {
                    tile = QPixmap(64, 24);
                    tile.fill(QColor(QStringLiteral("#111824")));
                    QPainter painter(&tile);
                    painter.setRenderHint(QPainter::Antialiasing, false);
                    painter.setPen(QColor(QStringLiteral("#385079")));
                    painter.drawRect(0, 0, 63, 23);
                    painter.fillRect(QRect(2, 3, 18, 18), QColor(QStringLiteral("#2858A8")));
                    painter.setPen(Qt::white);
                    if (type == QStringLiteral("Timer")) {
                        // Miniature stopwatch until user artwork is available.
                        painter.drawEllipse(QRect(5, 7, 12, 12));
                        painter.drawLine(11, 13, 11, 9);
                        painter.drawLine(11, 13, 15, 15);
                        painter.drawLine(9, 5, 13, 5);
                    } else {
                        painter.drawText(QRect(2, 3, 18, 18), Qt::AlignCenter, type.left(1));
                    }
                    QFont tileFont = painter.font();
                    tileFont.setPixelSize(9);
                    painter.setFont(tileFont);
                    painter.setPen(QColor(QStringLiteral("#E0E6F0")));
                    painter.drawText(QRect(23, 0, 39, 24), Qt::AlignVCenter | Qt::AlignLeft,
                                     painter.fontMetrics().elidedText(type, Qt::ElideRight, 39));
                }
                auto *item = new QListWidgetItem(QIcon(tile), QString(), palette);
                item->setData(Qt::UserRole, type);
                item->setToolTip(QStringLiteral("%1\n%2").arg(type, gadgetTooltips.value(type)));
                item->setSizeHint(QSize(72, 30));
            }
            connect(palette, &QListWidget::itemDoubleClicked, this,
                    [this](QListWidgetItem *item) {
                if (item) addGadget(item->data(Qt::UserRole).toString());
            });
            m_toolboxTabs->addTab(palette, group.first);
        }
        leftLayout->addWidget(m_toolboxTabs, 1);
        // Remember the selected category between designer sessions.
        QSettings paletteSettings(QStringLiteral("Sidbox"), QStringLiteral("SidboxIDE"));
        const int previousTab = paletteSettings.value(
            QStringLiteral("layout/guiDesignerPaletteTab"), 0).toInt();
        if (previousTab >= 0 && previousTab < m_toolboxTabs->count())
            m_toolboxTabs->setCurrentIndex(previousTab);
        connect(m_toolboxTabs, &QTabWidget::currentChanged, this,
                [](int index) {
            QSettings settings(QStringLiteral("Sidbox"), QStringLiteral("SidboxIDE"));
            settings.setValue(QStringLiteral("layout/guiDesignerPaletteTab"), index);
        });

        auto *addButton = new QPushButton(QObject::tr("Add Selected Gadget"), left);
        leftLayout->addWidget(addButton);

        leftLayout->addWidget(new QLabel(QObject::tr("Menus"), left));
        m_menuTree = new GuiDesignerMenuTree(left);
        m_menuTree->setHeaderHidden(true);
        m_menuTree->setMinimumHeight(120);
        leftLayout->addWidget(m_menuTree, 1);

        auto *menuButtons = new QHBoxLayout;
        auto *addMenu = new QPushButton(QObject::tr("+ Menu"), left);
        auto *addMenuItem = new QPushButton(QObject::tr("+ Item"), left);
        auto *removeMenu = new QPushButton(QObject::tr("−"), left);
        menuButtons->addWidget(addMenu);
        menuButtons->addWidget(addMenuItem);
        menuButtons->addWidget(removeMenu);
        leftLayout->addLayout(menuButtons);

        // Canvas ---------------------------------------------------------------
        auto *canvasScroll = new QScrollArea(splitter);
        canvasScroll->setWidgetResizable(false);
        canvasScroll->setAlignment(Qt::AlignCenter);
        canvasScroll->setStyleSheet(QStringLiteral("QScrollArea { background:#08090d; border:1px solid #182344; }"));
        m_canvas = new GuiDesignerCanvas(&m_window, &m_gadgets, &m_menus, canvasScroll);
        canvasScroll->setWidget(m_canvas);

        // The palette is created before the canvas. Connect its drag previews
        // now that the canvas exists so they can follow the current zoom.
        for (int i = 0; i < m_toolboxTabs->count(); ++i) {
            // Every palette tab here is constructed as a GuiDesignerToolbox.
            auto *palette = static_cast<GuiDesignerToolbox *>(m_toolboxTabs->widget(i));
            palette->gadgetPreviewRequested = [this](const QString &type) {
                return m_canvas->gadgetDragPixmap(makeDefaultGadget(type));
            };
        }

        // Properties -----------------------------------------------------------
        auto *rightScroll = new QScrollArea(splitter);
        rightScroll->setWidgetResizable(true);
        rightScroll->setMinimumWidth(285);
        m_propertyHost = new QWidget(rightScroll);
        m_propertyLayout = new GuiDesignerPropertyGrid(m_propertyHost);
        m_propertyLayout->setContentsMargins(8, 8, 8, 8);
        m_propertyLayout->setSpacing(7);
        rightScroll->setWidget(m_propertyHost);

        splitter->addWidget(left);
        splitter->addWidget(canvasScroll);
        splitter->addWidget(rightScroll);
        splitter->setStretchFactor(0, 0);
        splitter->setStretchFactor(1, 1);
        splitter->setStretchFactor(2, 0);
        splitter->setSizes({210, 900, 310});

        // Designer toolbox/canvas/properties have their own splitter state.
        // Never share this with the main window's project/editor splitter.
        QSettings designerSettings(QStringLiteral("Sidbox"), QStringLiteral("SidboxIDE"));
        const QByteArray designerState = designerSettings.value(
            QStringLiteral("layout/guiDesignerSplitter")).toByteArray();
        if (!designerState.isEmpty())
            splitter->restoreState(designerState);

        connect(splitter, &QSplitter::splitterMoved, this,
                [splitter](int, int) {
            QSettings settings(QStringLiteral("Sidbox"), QStringLiteral("SidboxIDE"));
            settings.setValue(QStringLiteral("layout/guiDesignerSplitter"),
                              splitter->saveState());
        });

        connect(addButton, &QPushButton::clicked, this, [this]() {
            // Only add the selected gadget in the *visible* palette tab.
            auto *palette = qobject_cast<QListWidget *>(m_toolboxTabs->currentWidget());
            if (!palette) return;
            QListWidgetItem *item = palette->currentItem();
            if (item) addGadget(item->data(Qt::UserRole).toString());
        });
        connect(
            m_undoAction,
            &QAction::triggered,
            this,
            [this]() {
                undoLastDesignerChange();
            });

        connect(save, &QAction::triggered, this, [this]() { saveDesignAndGenerate(); });
        connect(generate, &QAction::triggered, this, [this]() { generateCFile(true, true); });

        connect(
            m_snapCombo,
            qOverload<int>(
                &QComboBox::currentIndexChanged),
            this,
            [this](int) {
                if (!m_snapCombo) {
                    return;
                }

                m_canvas->setGridSnap(
                    m_snapCombo->currentData()
                        .toInt());

                m_statusLabel->setText(
                    m_canvas->gridSnap() > 1
                        ? QObject::tr(
                              "Grid snap: %1 px")
                              .arg(
                                  m_canvas->gridSnap())
                        : QObject::tr(
                              "Grid snap: Off"));
            });

        connect(
            zoom,
            qOverload<int>(
                &QComboBox::currentIndexChanged),
            this,
            [this, zoom](int index) {
                if (index < 0) {
                    return;
                }

                m_canvas->setZoomPercent(
                    zoom->itemData(
                        index)
                        .toInt());
            });

        connect(addMenu, &QPushButton::clicked, this, [this]() { addMenuTitle(); });
        connect(addMenuItem, &QPushButton::clicked, this, [this]() { addMenuEntry(); });
        connect(removeMenu, &QPushButton::clicked, this, [this]() { removeMenuEntry(); });
        connect(m_menuTree, &QTreeWidget::itemDoubleClicked, this,
                [this](QTreeWidgetItem *item, int) { editMenuEntry(item); });
        // Apply drag/drop to m_menus, so .sbui saving, generation and preview
        // all use the same reordered model. Keep callback names unchanged.
        static_cast<GuiDesignerMenuTree *>(m_menuTree)->reorderRequested =
            [this](int fromMenu, int fromItem, int toMenu, int toIndex) {
                if (fromMenu < 0 || fromMenu >= m_menus.size()) return;
                if (fromItem < 0) {
                    if (toIndex < 0 || toIndex > m_menus.size()) return;
                    if (toIndex == fromMenu || toIndex == fromMenu + 1) return;
                    pushUndoSnapshot();
                    const GuiDesignerMenuTitle moving = m_menus.takeAt(fromMenu);
                    if (toIndex > fromMenu) --toIndex;
                    m_menus.insert(toIndex, moving);
                } else {
                    if (fromItem >= m_menus[fromMenu].items.size()
                        || toMenu < 0 || toMenu >= m_menus.size()
                        || toIndex < 0 || toIndex > m_menus[toMenu].items.size()) return;
                    if (fromMenu == toMenu
                        && (toIndex == fromItem || toIndex == fromItem + 1)) return;
                    pushUndoSnapshot();
                    const GuiDesignerMenuItem moving = m_menus[fromMenu].items.takeAt(fromItem);
                    if (fromMenu == toMenu && toIndex > fromItem) --toIndex;
                    m_menus[toMenu].items.insert(toIndex, moving);
                }
                rebuildMenuTree();
                setModified(true);
                m_canvas->update();
            };

        m_canvas->selectionChanged = [this](int) {
            m_inlineTextEditing = false;
            rebuildProperties();
        };

        m_canvas->textInputRequested = [this](const QString &typed, bool backspace) {
            const int selected = m_canvas->selectedIndex();
            if (selected < 0 || selected >= m_gadgets.size()) return;
            GuiDesignerGadget &g = m_gadgets[selected];
            if (g.type != QStringLiteral("Button")
                && g.type != QStringLiteral("Label")
                && g.type != QStringLiteral("Checkbox")
                && g.type != QStringLiteral("Radio")
                && g.type != QStringLiteral("TextBox")
                && g.type != QStringLiteral("TextArea"))
                return;

            // A single Undo restores the original text for this typing run.
            if (!m_inlineTextEditing) {
                if (backspace && g.text.isEmpty()) return;
                pushUndoSnapshot();
                m_inlineTextEditing = true;
                m_inlineTextIndex = selected;
                m_inlineReplaceOnFirstKey = !backspace;
            }

            QString updated = g.text;
            if (backspace) {
                if (updated.isEmpty()) return;
                updated.chop(1);
            } else if (m_inlineTextIndex == selected && m_inlineReplaceOnFirstKey) {
                updated = typed;
            } else {
                updated += typed;
            }
            m_inlineReplaceOnFirstKey = false;
            if (updated == g.text) return;
            g.text = updated;
            if (m_textPropertyEdit) {
                const QSignalBlocker block(m_textPropertyEdit.data());
                m_textPropertyEdit->setText(updated);
                // Keep editingFinished from treating this programmatic update
                // as a second user edit when the field later loses focus.
                m_textPropertyEdit->setProperty("designerCommittedText", updated);
            }
            setModified(true);
            m_canvas->update();
        };

        m_canvas->textEditingFinished = [this]() -> bool {
            if (!m_inlineTextEditing) return false;
            m_inlineTextEditing = false;
            m_inlineReplaceOnFirstKey = true;
            return true;
        };

        m_canvas->gadgetDropped =
            [this](const QString &type,
                   const QPoint &localPosition) {
                addGadget(type, localPosition);
            };

        m_canvas->gadgetDoubleClicked =
            [this](int index) {
                jumpToGadgetSource(index);
            };

        m_canvas->menuItemActivated =
            [this](int menuIndex, int itemIndex) {
                jumpToMenuItemSource(menuIndex, itemIndex);
            };

        m_canvas->copyRequested =
            [this]() {
                copySelectedGadget();
            };

        m_canvas->undoRequested =
            [this]() {
                undoLastDesignerChange();
            };

        m_canvas->pasteRequested =
            [this]() {
                pasteCopiedGadget();
            };

        m_canvas->deleteRequested =
            [this]() {
                deleteSelectedGadget();
            };

        m_canvas->nudgeRequested =
            [this](int dx, int dy, bool autoRepeat) {
                m_inlineTextEditing = false;
                nudgeSelectedGadget(
                    dx,
                    dy,
                    autoRepeat);
            };

        m_canvas->resizeRequested =
            [this](int dw, int dh, bool autoRepeat) {
                m_inlineTextEditing = false;
                resizeSelectedGadget(dw, dh, autoRepeat);
            };

        m_canvas->layerRequested = [this](bool toFront) {
            changeSelectedGadgetLayer(toFront);
        };

        m_canvas->geometryChangeStarted = [this]() {
            pushUndoSnapshot();
        };

        m_canvas->geometryCommitted = [this]() {
            const int selected =
                m_canvas
                    ? m_canvas->selectedIndex()
                    : -1;

            if (selected >= 0
                && selected
                   < m_gadgets.size()) {
                syncDesignerDemoBitmapSize(
                    &m_gadgets[selected]);
            }

            setModified(true);
            rebuildProperties();
        };

        if (QFileInfo::exists(m_filePath)) {
            loadDesign();
        } else {
            // New design starts with a name derived from its filename,
            // rather than giving every new project window "MainWindow".
            m_window.name = safeCIdentifier(
                QFileInfo(m_filePath).completeBaseName(),
                QStringLiteral("MainWindow"));
            setModified(true);
        }

        rebuildMenuTree();
        rebuildProperties();
        clearUndoHistory();
    }

    QString filePath() const override { return m_filePath; }

    void setFilePath(const QString &filePath) override
    {
        const QString absolutePath = QFileInfo(filePath).absoluteFilePath();
        if (absolutePath == m_filePath)
            return;

        // A moved design must never save back to its original location:
        // that would recreate the old .sbui and yield a duplicate window.
        // Keep the in-memory gadgets, undo history and unsaved edits intact.
        m_filePath = absolutePath;
        setProperty("sidboxGuiDesignerPath", m_filePath);
        if (tabTitleChanged)
            tabTitleChanged();
    }

    bool isModified() const override { return m_modified; }

    QString displayName() const override
    {
        QString name = QFileInfo(m_filePath).fileName();
        if (name.isEmpty()) name = QObject::tr("GUI Designer");
        return m_modified ? name + QLatin1Char('*') : name;
    }

    bool saveDesignAndGenerate() override
    {
        // Compiling or saving must not overwrite a generated source that is
        // already current. Explicit Generate... remains available at any time.
        if (!validateProjectWindows(false)) return false;
        bool generatedResourceMissing = false;
        if (!m_detached) {
            const QFileInfo designInfo(m_filePath);
            const QDir resources(designInfo.dir().absoluteFilePath(
                designInfo.completeBaseName() + QStringLiteral("res")));
            const bool bitmapAvailable = QFile::exists(
                resources.filePath(QStringLiteral("bitmapview.c")));
            const bool mediaAvailable = QFile::exists(
                resources.filePath(QStringLiteral("media_sfx.c")));
            for (const GuiDesignerGadget &g : std::as_const(m_gadgets)) {
                if (g.type == QStringLiteral("Media") && g.mediaMode == QStringLiteral("SFX")
                    && g.mediaEmbedSfx && !mediaAvailable) {
                    generatedResourceMissing = true;
                    break;
                }
                if (g.type == QStringLiteral("BitmapView")
                    && (!g.bitmapPixels.isEmpty() || isDesignerDemoBitmap(g))
                    && !bitmapAvailable) {
                    generatedResourceMissing = true;
                    break;
                }
            }
        }
        const bool regenerate = m_needsGeneration || !QFile::exists(outputPath(m_detached))
                                || linkedWindowCallStale() || generatedResourceMissing;
        if (m_modified && !saveDesign())
            return false;
        if (regenerate) return generateCFile(false);

        // Upgrade an existing generated header with USER protection, or
        // create it if missing, without rewriting the .c or invalidating its
        // incremental build cache.
        // Detached .uis sketches are never compilable and need no .h.
        if (!m_detached) {
            const QString entry = windowEntryForDesign(m_filePath);
            if (entry.isEmpty()) {
                QMessageBox::warning(this, QObject::tr("GUI Designer"),
                    QObject::tr("Cannot determine the generated window entry in %1. "
                                "Regenerate its C source before creating the header.")
                        .arg(QDir::toNativeSeparators(outputPath(false))));
                return false;
            }
            bool headerChanged = false;
            if (!writeGeneratedHeader(outputPath(false), entry, &headerChanged))
                return false;
            if (headerChanged && generatedFilesChanged)
                generatedFilesChanged(m_filePath, generatedHeaderPath(outputPath(false)));
        }
        return true;
    }

private:
    // MainWindow supplies the project root; standalone designers fall back to
    // the .sbui directory. Links are stored relative to this location.
    QString designProjectRoot() const
    {
        QString supplied = property("sidboxProjectRoot").toString();
        if (supplied.isEmpty() && parentWidget())
            supplied = parentWidget()->property("sidboxProjectRoot").toString();
        return !supplied.isEmpty() && QFileInfo(supplied).isDir()
            ? QDir(supplied).absolutePath()
            : QFileInfo(m_filePath).absolutePath();
    }

    // A marked source function is the authoritative entry for linked windows.
    // Older generated sources without the marker retain the _Create convention.
    // This always reads the *compilable* .c; a detached .uis is only a sketch.
    QString windowEntryForDesign(const QString &designPath) const
    {
        QFile file(designPath);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return {};
        const QJsonDocument document = QJsonDocument::fromJson(file.readAll());
        if (!document.isObject()) return {};
        const QJsonObject root = document.object();
        const QString windowName = root.value(QStringLiteral("window"))
                                      .toObject().value(QStringLiteral("name")).toString();
        if (windowName.trimmed().isEmpty()) return {};
        const QString fallback = safeCIdentifier(windowName, QStringLiteral("MainWindow"))
                                 + QStringLiteral("_Create");
        const QFileInfo info(designPath);
        const QString sourceName = root.value(QStringLiteral("sourceFile")).toString();
        QFile source(info.dir().absoluteFilePath(sourceName.isEmpty()
            ? info.completeBaseName() + QStringLiteral(".c") : sourceName));
        if (!source.open(QIODevice::ReadOnly | QIODevice::Text)) return fallback;
        const QString code = QString::fromUtf8(source.readAll());
        if (!code.contains(QStringLiteral("$IDE:OpenWindow"))) return fallback;

        // The marker must immediately precede one exported void name(void)
        // function definition. A marker above a declaration is not sufficient.
        static const QRegularExpression entryPattern(QStringLiteral(
            R"(//[ \t]*\$IDE:OpenWindow[ \t]*//[ \t]*\r?\n[ \t]*void[ \t]+([A-Za-z_][A-Za-z_0-9]*)[ \t]*\([ \t]*(?:void[ \t]*)?\)[ \t\r\n]*\{)"));
        auto matches = entryPattern.globalMatch(code);
        if (!matches.hasNext()) return {};  // malformed marker: don't guess
        const QString name = matches.next().captured(1);
        if (matches.hasNext()) return {};   // ambiguous: don't choose randomly
        return name;
    }

    // Audit *all* saved .sbui names, not just the selected target. The current
    // editor's unsaved name replaces its disk entry in the audit.
    bool validateProjectWindows(bool requireCompiledTargets)
    {
        const QDir project(designProjectRoot());
        QHash<QString, QString> symbols;
        const QString thisFile = QFileInfo(m_filePath).absoluteFilePath();
        QDirIterator it(project.absolutePath(), {QStringLiteral("*.sbui")},
                        QDir::Files, QDirIterator::Subdirectories);
        while (it.hasNext()) {
            const QString path = QFileInfo(it.next()).absoluteFilePath();
            QString windowName;
            if (path == thisFile) {
                windowName = m_window.name;
            } else {
                QFile file(path);
                if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) continue;
                const QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
                if (!doc.isObject()) continue;
                windowName = doc.object().value(QStringLiteral("window"))
                                 .toObject().value(QStringLiteral("name")).toString();
            }
            const QString symbol = safeCIdentifier(windowName, QStringLiteral("MainWindow"));
            const QString key = symbol.toCaseFolded();
            if (symbols.contains(key)) {
                QMessageBox::warning(this, QObject::tr("Duplicate window name"),
                    QObject::tr("Both %1 and %2 use window name '%3'.\n\n"
                                "Each .sbui in the project must have a unique C window name. "
                                "Rename one in its Window properties before generating.")
                        .arg(project.relativeFilePath(symbols.value(key)),
                             project.relativeFilePath(path), symbol));
                return false;
            }
            symbols.insert(key, path);
        }
        // A new, unsaved design is not yet included by the iterator.
        if (!QFile::exists(thisFile)) {
            const QString symbol = safeCIdentifier(m_window.name, QStringLiteral("MainWindow"));
            if (symbols.contains(symbol.toCaseFolded())) {
                QMessageBox::warning(this, QObject::tr("Duplicate window name"),
                    QObject::tr("The window name '%1' is already used by %2.")
                        .arg(symbol, project.relativeFilePath(symbols.value(symbol.toCaseFolded()))));
                return false;
            }
        }

        QSet<QString> linkedCallbacks;
        for (const GuiDesignerGadget &g : std::as_const(m_gadgets)) {
            if (g.openWindowFile.isEmpty()) continue;
            const QString target = QFileInfo(project.absoluteFilePath(g.openWindowFile)).absoluteFilePath();
            const bool withinProject = target.startsWith(project.absolutePath() + QDir::separator());
            if (g.type != QStringLiteral("Button") || !withinProject || target == thisFile
                || !QFileInfo::exists(target)) {
                QMessageBox::warning(this, QObject::tr("Invalid window link"),
                    QObject::tr("Button %1 links to a missing, self-referencing or external design:\n%2")
                        .arg(g.name, g.openWindowFile));
                return false;
            }
            if (g.onActivate.trimmed().isEmpty()) {
                QMessageBox::warning(this, QObject::tr("Invalid window link"),
                    QObject::tr("Button %1 needs an On activate callback for its window link.").arg(g.name));
                return false;
            }
            // Callback names are functions, not gadget-specific dispatch keys.
            // A shared callback would otherwise open a window for unrelated buttons.
            const QString callback = safeCIdentifier(g.onActivate, QStringLiteral("OnActivate"));
            if (linkedCallbacks.contains(callback)) {
                QMessageBox::warning(this, QObject::tr("Shared linked callback"),
                    QObject::tr("Linked buttons cannot share activation callback %1.").arg(callback));
                return false;
            }
            linkedCallbacks.insert(callback);
            QFile file(target);
            if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return false;
            const QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
            const QString targetName = doc.object().value(QStringLiteral("window"))
                                            .toObject().value(QStringLiteral("name")).toString();
            if (!doc.isObject() || targetName.trimmed().isEmpty()) {
                QMessageBox::warning(this, QObject::tr("Invalid window link"),
                    QObject::tr("Target %1 has no readable window name.").arg(g.openWindowFile));
                return false;
            }
            if (windowEntryForDesign(target).isEmpty()) {
                QMessageBox::warning(this, QObject::tr("Invalid window entry"),
                    QObject::tr("%1 has an invalid or duplicate $IDE:OpenWindow marker.\n"
                                "Put // $IDE:OpenWindow // immediately above one public "
                                "void FunctionName(void) definition.")
                        .arg(g.openWindowFile));
                return false;
            }
            if (requireCompiledTargets) {
                const QString sourceName = doc.object().value(QStringLiteral("sourceFile")).toString();
                const QString source = QFileInfo(target).dir().absoluteFilePath(
                    sourceName.isEmpty() ? QFileInfo(target).completeBaseName() + QStringLiteral(".c")
                                         : sourceName);
                if (QFileInfo(source).suffix().compare(QStringLiteral("c"), Qt::CaseInsensitive) != 0
                    || !QFileInfo::exists(source)) {
                    QMessageBox::warning(this, QObject::tr("Linked source missing"),
                        QObject::tr("Generate the .c source for %1 before generating this linked applet.\n"
                                    "Expected source: %2")
                            .arg(g.openWindowFile, QDir::toNativeSeparators(source)));
                    return false;
                }
            }
        }
        for (const GuiDesignerGadget &g : std::as_const(m_gadgets)) {
            if (g.openWindowFile.isEmpty()) continue;
            const QString callback = safeCIdentifier(g.onActivate, QStringLiteral("OnActivate"));
            for (const GuiDesignerGadget &other : std::as_const(m_gadgets)) {
                if (&g != &other && (other.onActivate == callback || other.onChange == callback)) {
                    QMessageBox::warning(this, QObject::tr("Shared linked callback"),
                        QObject::tr("Button %1 shares callback %2 with another gadget. "
                                    "Assign a unique On activate callback to the linked button.")
                            .arg(g.name, callback));
                    return false;
                }
            }
        }
        // TabGroup uses the existing per-window group visibility API.
        // Group 0 is reserved for permanent/window chrome gadgets.
        int tabPageCount = 0;
        QSet<QString> tabNames;
        for (const GuiDesignerGadget &g : std::as_const(m_gadgets)) {
            if (g.type == QStringLiteral("TabGroup")) {
                const QString key = safeCIdentifier(g.name, QStringLiteral("tabs"));
                if (tabNames.contains(key)) {
                    QMessageBox::warning(this, QObject::tr("Tab Group"),
                        QObject::tr("Duplicate Tab Group name: %1").arg(key));
                    return false;
                }
                tabNames.insert(key);
                if (g.text.split(QLatin1Char('|'), Qt::SkipEmptyParts).size() > 8) {
                    QMessageBox::warning(this, QObject::tr("Tab Group"),
                        QObject::tr("%1 supports a maximum of 8 tabs.").arg(g.name));
                    return false;
                }
                if (g.rect.width() < designerTabTitles(g).size() * 24
                    || g.rect.height() < 48) {
                    QMessageBox::warning(this, QObject::tr("Tab Group"),
                        QObject::tr("Tab Group %1 is too small for its buttons (minimum 24 px per tab and 48 px tall).")
                        .arg(g.name));
                    return false;
                }
                tabPageCount += designerTabTitles(g).size();
            }
        }
        if (tabPageCount > 255) {
            QMessageBox::warning(this, QObject::tr("Tab Group"),
                QObject::tr("Tab Groups exceed the 255 available nonzero CoderGirl group IDs."));
            return false;
        }
        for (const GuiDesignerGadget &g : std::as_const(m_gadgets)) {
            if (g.tabOwner.isEmpty()) continue;
            if (g.flags.contains(QStringLiteral("GAD_TOOL_DOCKED_RIGHT"))
                || g.flags.contains(QStringLiteral("GAD_TOOL_DOCKED_BOTTOM"))) {
                QMessageBox::warning(this, QObject::tr("Tab Group"),
                    QObject::tr("Docked gadget %1 cannot be tab-controlled: the firmware intentionally keeps docked gadgets visible.")
                    .arg(g.name));
                return false;
            }
            bool valid = false;
            for (const GuiDesignerGadget &tabs : std::as_const(m_gadgets)) {
                if (tabs.type == QStringLiteral("TabGroup") && tabs.name == g.tabOwner
                    && g.tabPage >= 0 && g.tabPage < designerTabTitles(tabs).size()) {
                    valid = true; break;
                }
            }
            if (!valid) {
                QMessageBox::warning(this, QObject::tr("Tab Group"),
                    QObject::tr("Gadget %1 refers to an invalid tab or a deleted Tab Group.").arg(g.name));
                return false;
            }
        }
        return true;
    }

    // Catch a renamed linked window on the next compile, even if the linking
    // .sbui itself has not changed since the previous generation.
    bool linkedWindowCallStale() const
    {
        bool hasLinks = false;
        for (const GuiDesignerGadget &g : std::as_const(m_gadgets)) {
            if (!g.openWindowFile.isEmpty()) { hasLinks = true; break; }
        }
        if (!hasLinks) return false;
        QFile output(outputPath(m_detached));
        if (!output.open(QIODevice::ReadOnly | QIODevice::Text)) return true;
        const QString text = QString::fromUtf8(output.readAll());
        const QDir project(designProjectRoot());
        for (const GuiDesignerGadget &g : std::as_const(m_gadgets)) {
            if (g.openWindowFile.isEmpty()) continue;
            const QString symbol = windowEntryForDesign(project.absoluteFilePath(g.openWindowFile));
            if (symbol.isEmpty()) return true;
            if (!text.contains(QStringLiteral("extern void %1(void);").arg(symbol))
                || !text.contains(QStringLiteral("\t%1();").arg(symbol))) return true;
        }
        return false;
    }

    // Returns the selected pen only in picker mode. -2 means cancelled;
    // -1 means the gadget should continue using its default pen.
    int showPaletteDialog(int initialPen = -1, bool picker = false,
                          bool allowDefault = false)
    {
        // This is the 256-entry preview CLUT compiled into the designer.
        // It does not read the live CLUT from a running SIDBOX.
        QDialog dialog(this);
        dialog.setWindowTitle(picker ? QObject::tr("Choose SIDBOX pen colour")
                                     : QObject::tr("CoderGirl colour palette"));
        auto *layout = new QVBoxLayout(&dialog);
        layout->setSpacing(8);

        auto *help = new QLabel(
            picker
                ? QObject::tr("Choose a colour from the 256-entry designer CLUT, "
                              "then click Use selected pen. "
                              "The running SIDBOX may have a different palette.")
                : QObject::tr("Designer default CLUT (256 colours). "
                              "Click a swatch to see its pen index and ARGB value. "
                              "Runtime palette changes on SIDBOX are not read automatically."),
            &dialog);
        help->setWordWrap(true);
        layout->addWidget(help);

        auto *scroller = new QScrollArea(&dialog);
        scroller->setWidgetResizable(false);
        scroller->setAlignment(Qt::AlignCenter);
        auto *swatches = new QWidget(scroller);
        auto *grid = new QGridLayout(swatches);
        grid->setContentsMargins(4, 4, 4, 4);
        grid->setSpacing(2);
        auto *selection = new QButtonGroup(&dialog);
        selection->setExclusive(true);

        const int gadgetIndex = m_canvas ? m_canvas->selectedIndex() : -1;
        int currentIndex = initialPen;
        if (currentIndex < 0) {
            currentIndex = qBound(0, m_window.backPen, 255);
            if (!picker && gadgetIndex >= 0 && gadgetIndex < m_gadgets.size()
                && m_gadgets[gadgetIndex].fPen >= 0) {
                currentIndex = qBound(0, m_gadgets[gadgetIndex].fPen, 255);
            }
        }
        currentIndex = qBound(0, currentIndex, 255);

        auto *details = new QLabel(&dialog);
        const auto updateDetails = [details](int index) {
            const QString argb = QString::number(kCoderGirlClut[index], 16)
                                     .rightJustified(8, QLatin1Char('0'))
                                     .toUpper();
            details->setText(
                QObject::tr("Pen %1 (0x%2)      ARGB #%3")
                    .arg(index)
                    .arg(QString::number(index, 16)
                             .rightJustified(2, QLatin1Char('0'))
                             .toUpper())
                    .arg(argb));
        };

        for (int index = 0; index < 256; ++index) {
            // Paint the swatches ourselves so alpha=0 is visibly transparent.
            QPixmap sample(23, 23);
            sample.fill(Qt::transparent);
            {
                QPainter painter(&sample);
                for (int y = 0; y < 23; y += 6) {
                    for (int x = 0; x < 23; x += 6) {
                        painter.fillRect(QRect(x, y, 6, 6),
                            ((x + y) / 6) % 2 ? QColor(190, 190, 190)
                                               : QColor(100, 100, 100));
                    }
                }
                painter.fillRect(sample.rect(),
                    QColor::fromRgba(kCoderGirlClut[index]));
            }

            auto *button = new QToolButton(swatches);
            button->setCheckable(true);
            button->setFixedSize(28, 28);
            button->setIcon(QIcon(sample));
            button->setIconSize(QSize(23, 23));
            button->setToolTip(
                QObject::tr("Pen %1: #%2")
                    .arg(index)
                    .arg(QString::number(kCoderGirlClut[index], 16)
                             .rightJustified(8, QLatin1Char('0'))
                             .toUpper()));
            selection->addButton(button, index);
            grid->addWidget(button, index / 16, index % 16);
            button->setChecked(index == currentIndex);
            connect(button, &QToolButton::clicked, &dialog,
                    [&, index]() {
                        currentIndex = index;
                        updateDetails(index);
                    });
        }
        swatches->setStyleSheet(QStringLiteral(
            "QToolButton { border: 1px solid #303030; border-radius: 0px; "
            "padding: 1px; background: #101010; } "
            "QToolButton:checked { border: 2px solid #2858A8; } "
            "QToolButton:hover { border: 2px solid #ffffff; }"));
        scroller->setWidget(swatches);
        layout->addWidget(scroller, 1);
        updateDetails(currentIndex);
        layout->addWidget(details);

        auto *controls = new QHBoxLayout;
        auto *copyIndex = new QPushButton(QObject::tr("Copy pen index"), &dialog);
        auto *copyArgb = new QPushButton(QObject::tr("Copy ARGB"), &dialog);
        auto *close = new QPushButton(picker ? QObject::tr("Cancel")
                                              : QObject::tr("Close"), &dialog);
        controls->addWidget(copyIndex);
        controls->addWidget(copyArgb);
        controls->addStretch(1);
        if (picker) {
            if (allowDefault) {
                auto *useDefault = new QPushButton(QObject::tr("Use default (-1)"), &dialog);
                controls->addWidget(useDefault);
                connect(useDefault, &QPushButton::clicked, &dialog,
                        [&dialog, &currentIndex]() {
                            currentIndex = -1;
                            dialog.accept();
                        });
            }
            auto *usePen = new QPushButton(QObject::tr("Use selected pen"), &dialog);
            controls->addWidget(usePen);
            connect(usePen, &QPushButton::clicked, &dialog, &QDialog::accept);
        }
        controls->addWidget(close);
        layout->addLayout(controls);

        connect(copyIndex, &QPushButton::clicked, &dialog, [&currentIndex]() {
            QApplication::clipboard()->setText(QString::number(currentIndex));
        });
        connect(copyArgb, &QPushButton::clicked, &dialog, [&currentIndex]() {
            QApplication::clipboard()->setText(
                QStringLiteral("0x")
                + QString::number(kCoderGirlClut[currentIndex], 16)
                      .rightJustified(8, QLatin1Char('0'))
                      .toUpper());
        });
        connect(close, &QPushButton::clicked, &dialog, &QDialog::reject);
        dialog.resize(560, 650);
        const int result = dialog.exec();
        return picker && result == QDialog::Accepted ? currentIndex : -2;
    }

    void setModified(bool modified)
    {
        if (m_modified == modified) return;
        m_modified = modified;
        if (modified) m_needsGeneration = true;
        if (tabTitleChanged) tabTitleChanged();
    }

    static QRect defaultRectForType(const QString &type, int ordinal)
    {
        const int x = 18 + (ordinal % 5) * 14;
        const int y = 24 + (ordinal % 8) * 18;
        if (isVirtualDesignerGadget(type)) return QRect(x, y, 24, 24);
        if (type == QStringLiteral("TabGroup")) return QRect(12, 26, 310, 172);
        if (type == QStringLiteral("Label")) return QRect(x, y, 120, 18);
        if (type == QStringLiteral("Checkbox") || type == QStringLiteral("Radio")) return QRect(x, y, 130, 20);
        if (type == QStringLiteral("Slider") || type == QStringLiteral("Scrollbar")) return QRect(x, y, 150, 18);
        if (type == QStringLiteral("ProgressBar")) return QRect(x, y, 150, 24);
        if (type == QStringLiteral("TextArea") || type == QStringLiteral("ListBox")) return QRect(x, y, 170, 80);
        if (type == QStringLiteral("GridSelect")) return QRect(x, y, 98, 74);
        if (type == QStringLiteral("Canvas") || type == QStringLiteral("BitmapView")) return QRect(x, y, 120, 80);
        if (type == QStringLiteral("TextBox")) return QRect(x, y, 150, 20);
        return QRect(x, y, 90, 22);
    }

    QString uniqueGadgetName(const QString &type) const
    {
        QString stem;
        if (type == QStringLiteral("TabGroup")) stem = QStringLiteral("tabs");
        else if (type == QStringLiteral("Timer")) stem = QStringLiteral("timer");
        else if (type == QStringLiteral("Messenger")) stem = QStringLiteral("messenger");
        else if (type == QStringLiteral("UART1")) stem = QStringLiteral("uart1");
        else if (type == QStringLiteral("KBInput")) stem = QStringLiteral("kbinput");
        else if (type == QStringLiteral("MSInput")) stem = QStringLiteral("msinput");
        else if (type == QStringLiteral("Media")) stem = QStringLiteral("media");
        else if (type == QStringLiteral("FileRequester")) stem = QStringLiteral("fileRequest");
        else if (type == QStringLiteral("MessageBox")) stem = QStringLiteral("messageBox");
        else if (type == QStringLiteral("Button")) stem = QStringLiteral("btn");
        else if (type == QStringLiteral("Label")) stem = QStringLiteral("lbl");
        else if (type == QStringLiteral("Checkbox")) stem = QStringLiteral("chk");
        else if (type == QStringLiteral("Radio")) stem = QStringLiteral("rad");
        else if (type == QStringLiteral("Slider")) stem = QStringLiteral("sld");
        else if (type == QStringLiteral("ProgressBar")) stem = QStringLiteral("prg");
        else if (type == QStringLiteral("TextBox")) stem = QStringLiteral("txt");
        else if (type == QStringLiteral("TextArea")) stem = QStringLiteral("area");
        else if (type == QStringLiteral("ListBox")) stem = QStringLiteral("list");
        else if (type == QStringLiteral("Scrollbar")) stem = QStringLiteral("scroll");
        else if (type == QStringLiteral("GridSelect")) stem = QStringLiteral("grid");
        else if (type == QStringLiteral("Canvas")) stem = QStringLiteral("canvas");
        else stem = QStringLiteral("bitmap");

        for (int n = 1; n < 10000; ++n) {
            const QString candidate = stem + QString::number(n);
            bool used = false;
            for (const GuiDesignerGadget &g : m_gadgets) {
                if (g.name == candidate) { used = true; break; }
            }
            if (!used) return candidate;
        }
        return stem + QStringLiteral("X");
    }

    bool gadgetFromJsonObject(
        const QJsonObject &o,
        GuiDesignerGadget *out) const
    {
        if (!out) {
            return false;
        }

        GuiDesignerGadget g;

        g.type =
            o.value(QStringLiteral("type"))
                .toString();

        if (g.type.isEmpty()) {
            return false;
        }

        g.name =
            o.value(QStringLiteral("name"))
                .toString();

        g.rect = QRect(
            o.value(QStringLiteral("x")).toInt(),
            o.value(QStringLiteral("y")).toInt(),
            qMax(1, o.value(QStringLiteral("w")).toInt(80)),
            qMax(1, o.value(QStringLiteral("h")).toInt(20)));

        g.text = o.value(QStringLiteral("text")).toString();
        g.flags = o.value(QStringLiteral("flags")).toString(QStringLiteral("GAD_TOOL_DEFAULT"));
        g.bPen = o.value(QStringLiteral("bPen")).toInt(-1);
        g.fPen = o.value(QStringLiteral("fPen")).toInt(-1);
        g.hPen = o.value(QStringLiteral("hPen")).toInt(-1);
        g.onActivate = o.value(QStringLiteral("onActivate")).toString();
        g.onChange = o.value(QStringLiteral("onChange")).toString();
        g.openWindowFile = o.value(QStringLiteral("openWindowFile")).toString();
        g.tabOwner = o.value(QStringLiteral("tabOwner")).toString();
        g.tabPage = o.value(QStringLiteral("tabPage")).toInt(0);
        g.defaultTabPage = o.value(QStringLiteral("defaultTabPage")).toInt(0);
        g.callbackRoute = o.value(QStringLiteral("callbackRoute")).toInt(-1);
        g.minimum = o.value(QStringLiteral("minimum")).toInt(0);
        g.maximum = o.value(QStringLiteral("maximum")).toInt(100);
        g.value = o.value(QStringLiteral("value")).toInt(0);
        g.orientation = o.value(QStringLiteral("orientation")).toInt(1);
        g.checked = o.value(QStringLiteral("checked")).toInt(0);
        g.enabled = o.value(QStringLiteral("enabled")).toBool(true);
        g.group = o.value(QStringLiteral("group")).toInt(0);
        g.typeFlags = o.value(QStringLiteral("typeFlags")).toString();
        g.timerDelayMs = qBound(1, o.value(QStringLiteral("timerDelayMs")).toInt(1000), 86400000);
        g.timerPeriodMs = qBound(1, o.value(QStringLiteral("timerPeriodMs")).toInt(1000), 86400000);
        g.timerRepeat = o.value(QStringLiteral("timerRepeat")).toBool(true);
        g.timerAutoStart = o.value(QStringLiteral("timerAutoStart")).toBool(true);
        g.timerKeepAliveOnClose = o.value(QStringLiteral("timerKeepAliveOnClose")).toBool(false);
        g.ipcReceive = o.value(QStringLiteral("ipcReceive")).toBool(true);
        g.ipcPollMs = qBound(10, o.value(QStringLiteral("ipcPollMs")).toInt(25), 1000);
        g.ipcTargetApp = o.value(QStringLiteral("ipcTargetApp")).toString();
        g.ipcSendTarget = o.value(QStringLiteral("ipcSendTarget")).toString();
        g.ipcSendType = qBound(0, o.value(QStringLiteral("ipcSendType")).toInt(1), 65535);
        g.ipcSendText = o.value(QStringLiteral("ipcSendText")).toString(QStringLiteral("Hello from SIDBOX!"));
         g.uart1Baud = qBound(1200, o.value(QStringLiteral("uart1Baud")).toInt(9600), 1000000);
         g.uart1DataBits = qBound(7, o.value(QStringLiteral("uart1DataBits")).toInt(8), 8);
         g.uart1Parity = qBound(0, o.value(QStringLiteral("uart1Parity")).toInt(0), 2);
         g.uart1StopBits = qBound(1, o.value(QStringLiteral("uart1StopBits")).toInt(1), 2);
         g.uart1PollMs = qBound(10, o.value(QStringLiteral("uart1PollMs")).toInt(20), 1000);
         g.uart1AutoOpen = o.value(QStringLiteral("uart1AutoOpen")).toBool(false);
        g.mediaMode = o.value(QStringLiteral("mediaMode")).toString(QStringLiteral("SFX"));
        g.mediaFile = o.value(QStringLiteral("mediaFile")).toString();
        g.mediaEmbedSfx = o.value(QStringLiteral("mediaEmbedSfx")).toBool(false);
        g.mediaEmbeddedName = o.value(QStringLiteral("mediaEmbeddedName")).toString();
        g.mediaEmbeddedPcm = QByteArray::fromBase64(
            o.value(QStringLiteral("mediaEmbeddedPcmBase64")).toString().toLatin1());
        g.mediaChannel = o.value(QStringLiteral("mediaChannel")).toInt(0);
        g.mediaVolume = o.value(QStringLiteral("mediaVolume")).toInt(200);
        g.mediaPan = o.value(QStringLiteral("mediaPan")).toInt(0);
        g.mediaFrequency = o.value(QStringLiteral("mediaFrequency")).toInt(22050);
        g.mediaSubsong = o.value(QStringLiteral("mediaSubsong")).toInt(0);
        g.mediaLoop = o.value(QStringLiteral("mediaLoop")).toBool(false);
        g.mediaAutoStart = o.value(QStringLiteral("mediaAutoStart")).toBool(false);
        g.mediaTarget = o.value(QStringLiteral("mediaTarget")).toString();
        g.mediaAction = o.value(QStringLiteral("mediaAction")).toString(QStringLiteral("Play"));
        g.dialogTitle = o.value(QStringLiteral("dialogTitle")).toString(QStringLiteral("Select a file"));
        g.dialogMessage = o.value(QStringLiteral("dialogMessage")).toString(QStringLiteral("Are you sure?"));
        g.dialogDir = o.value(QStringLiteral("dialogDir")).toString(QStringLiteral("sdcard:/"));
        g.dialogFilter = o.value(QStringLiteral("dialogFilter")).toString(QStringLiteral("*.*"));
        g.dialogKind = o.value(QStringLiteral("dialogKind")).toString(QStringLiteral("Message"));
        g.dialogButtons = o.value(QStringLiteral("dialogButtons")).toString(QStringLiteral("OK/Cancel"));
        g.dialogBlockOwner = o.value(QStringLiteral("dialogBlockOwner")).toBool(false);
        g.dialogTarget = o.value(QStringLiteral("dialogTarget")).toString();
        g.cellWidth = o.value(QStringLiteral("cellWidth")).toInt(24);
        g.cellHeight = o.value(QStringLiteral("cellHeight")).toInt(18);
        g.cellsX = o.value(QStringLiteral("cellsX")).toInt(4);
        g.cellsY = o.value(QStringLiteral("cellsY")).toInt(4);

        for (const QJsonValue &cellValue :
             o.value(QStringLiteral("gridCellText")).toArray()) {
            g.gridCellText.append(
                cellValue.toString().left(4));
        }

        g.bitmapWidth = o.value(QStringLiteral("bitmapWidth")).toInt(64);
        g.bitmapHeight = o.value(QStringLiteral("bitmapHeight")).toInt(64);
        g.bitmapSource = o.value(QStringLiteral("bitmapSource")).toString();
        g.bitmapImagePath = o.value(QStringLiteral("bitmapImagePath")).toString();
        g.bitmapPixels = QByteArray::fromBase64(
            o.value(QStringLiteral("bitmapPixelsBase64"))
                .toString()
                .toLatin1());

        for (const QJsonValue &itemValue :
             o.value(QStringLiteral("listItems")).toArray()) {
            g.listItems.append(itemValue.toString());
        }

        normaliseGridCellText(&g);
        syncGridSelectGeometry(&g);
        normaliseBitmapView(&g);
        *out = g;
        return true;
    }

    void copySelectedGadget()
    {
        if (!m_canvas) {
            return;
        }

        const int selected =
            m_canvas->selectedIndex();

        if (selected < 0
            || selected >= m_gadgets.size()) {
            return;
        }

        QJsonObject root;
        root.insert(
            QStringLiteral("format"),
            QStringLiteral("SidboxGuiDesignerGadget"));
        root.insert(
            QStringLiteral("version"),
            1);
        root.insert(
            QStringLiteral("gadget"),
            gadgetToJson(m_gadgets.at(selected)));

        auto *mime = new QMimeData;
        mime->setData(
            QString::fromLatin1(
                GuiDesignerClipboardMimeType),
            QJsonDocument(root)
                .toJson(QJsonDocument::Compact));

        QApplication::clipboard()->setMimeData(mime);

        if (m_statusLabel) {
            m_statusLabel->setText(
                QObject::tr("Copied %1")
                    .arg(m_gadgets.at(selected).name));
        }
    }

    void pasteCopiedGadget()
    {
        if (!m_canvas) {
            return;
        }

        const QMimeData *mime =
            QApplication::clipboard()->mimeData();

        if (!mime
            || !mime->hasFormat(
                QString::fromLatin1(
                    GuiDesignerClipboardMimeType))) {
            return;
        }

        QJsonParseError error;
        const QJsonDocument doc =
            QJsonDocument::fromJson(
                mime->data(
                    QString::fromLatin1(
                        GuiDesignerClipboardMimeType)),
                &error);

        if (error.error != QJsonParseError::NoError
            || !doc.isObject()) {
            return;
        }

        const QJsonObject root =
            doc.object();

        if (root.value(QStringLiteral("format")).toString()
            != QStringLiteral("SidboxGuiDesignerGadget")) {
            return;
        }

        GuiDesignerGadget g;
        if (!gadgetFromJsonObject(
                root.value(QStringLiteral("gadget")).toObject(),
                &g)) {
            return;
        }

        const QString oldName =
            g.name;

        const QString oldAutoActivate =
            QStringLiteral("On_%1_Activate")
                .arg(oldName);

        const QString oldAutoChange =
            QStringLiteral("On_%1_Change")
                .arg(oldName);

        const QString oldDemoBitmap =
            safeCIdentifier(
                oldName,
                QStringLiteral("bitmap"))
            + QStringLiteral("_pixels");

        g.name =
            uniqueGadgetName(g.type);
        // A pasted button retains its Media link; pasted Media has a fresh name.

        /*
         * Designer-generated callback names should follow the new gadget name.
         * Explicitly shared/custom callback names are deliberately preserved.
         */
        if (g.onActivate == oldAutoActivate) {
            g.onActivate =
                QStringLiteral("On_%1_Activate")
                    .arg(g.name);
        }
        if (g.type == QStringLiteral("Messenger")
            && g.onActivate == QStringLiteral("On_%1_Message").arg(oldName)) {
            g.onActivate = QStringLiteral("On_%1_Message").arg(g.name);
        }
        if (g.type == QStringLiteral("Timer")
            && g.onActivate == QStringLiteral("On_%1_Tick").arg(oldName)) {
            g.onActivate = QStringLiteral("On_%1_Tick").arg(g.name);
        }
        if (g.type == QStringLiteral("KBInput")
            && g.onActivate == QStringLiteral("On_%1_Key").arg(oldName))
            g.onActivate = QStringLiteral("On_%1_Key").arg(g.name);
        if (g.type == QStringLiteral("MSInput")
            && g.onActivate == QStringLiteral("On_%1_Mouse").arg(oldName))
            g.onActivate = QStringLiteral("On_%1_Mouse").arg(g.name);
        if (g.type == QStringLiteral("FileRequester")) {
            if (g.onActivate == QStringLiteral("On_%1_Selected").arg(oldName))
                g.onActivate = QStringLiteral("On_%1_Selected").arg(g.name);
            if (g.onChange == QStringLiteral("On_%1_Cancelled").arg(oldName))
                g.onChange = QStringLiteral("On_%1_Cancelled").arg(g.name);
        }
        if (g.type == QStringLiteral("MessageBox")
            && g.onActivate == QStringLiteral("On_%1_Result").arg(oldName))
            g.onActivate = QStringLiteral("On_%1_Result").arg(g.name);

        if (g.onChange == oldAutoChange) {
            g.onChange =
                QStringLiteral("On_%1_Change")
                    .arg(g.name);
        }

        if (g.type == QStringLiteral("BitmapView")
            && g.bitmapSource.trimmed() == oldDemoBitmap) {
            g.bitmapSource =
                safeCIdentifier(
                    g.name,
                    QStringLiteral("bitmap"))
                + QStringLiteral("_pixels");
        }

        /*
         * Duplicating a checked radio must not silently switch the original
         * radio off. The pasted member joins the same group, but starts clear.
         */
        if (g.type == QStringLiteral("Radio")
            && g.checked) {
            g.checked = 0;
        }

        normaliseBitmapView(&g);

        const int step =
            m_canvas->gridSnap() > 1
                ? m_canvas->gridSnap()
                : 1;

        const QSize clientSize =
            m_canvas->clientViewportSize();

        const int maxX =
            qMax(
                0,
                clientSize.width()
                    - g.rect.width());

        const int maxY =
            qMax(
                0,
                clientSize.height()
                    - g.rect.height());

        QPoint pastedAt(
            qBound(
                0,
                g.rect.x() + step,
                maxX),
            qBound(
                0,
                g.rect.y() + step,
                maxY));

        /* If right/down cannot visibly offset it, try one unit left/up. */
        if (pastedAt.x() == g.rect.x()
            && g.rect.x() > 0) {
            pastedAt.setX(
                qMax(
                    0,
                    g.rect.x() - step));
        }

        if (pastedAt.y() == g.rect.y()
            && g.rect.y() > 0) {
            pastedAt.setY(
                qMax(
                    0,
                    g.rect.y() - step));
        }

        g.rect.moveTopLeft(pastedAt);

        pushUndoSnapshot();
        m_gadgets.append(g);
        normalizeRadioGroups();

        m_canvas->setSelectedIndex(
            m_gadgets.size() - 1);
        setModified(true);
        m_canvas->update();
        m_canvas->setFocus(Qt::ShortcutFocusReason);

        if (m_statusLabel) {
            m_statusLabel->setText(
                QObject::tr("Pasted %1")
                    .arg(g.name));
        }
    }

    void deleteSelectedGadget()
    {
        if (!m_canvas) {
            return;
        }

        const int selected =
            m_canvas->selectedIndex();

        if (selected < 0
            || selected >= m_gadgets.size()) {
            return;
        }

        const QString deletedName =
            m_gadgets.at(selected).name;

        pushUndoSnapshot();
        m_gadgets.removeAt(selected);
        for (GuiDesignerGadget &child : m_gadgets) {
            if (child.tabOwner == deletedName) { child.tabOwner.clear(); child.tabPage = 0; }
            if (child.mediaTarget == deletedName) child.mediaTarget.clear();
            if (child.dialogTarget == deletedName) child.dialogTarget.clear();
        }

        const int nextSelected =
            m_gadgets.isEmpty()
                ? -1
                : qMin(
                      selected,
                      static_cast<int>(m_gadgets.size()) - 1);

        m_canvas->setSelectedIndex(nextSelected);
        setModified(true);
        m_canvas->update();
        m_canvas->setFocus(Qt::ShortcutFocusReason);

        if (m_statusLabel) {
            m_statusLabel->setText(
                QObject::tr("Deleted %1")
                    .arg(deletedName));
        }
    }

    void changeSelectedGadgetLayer(bool toFront)
    {
        if (!m_canvas) return;
        const int selected = m_canvas->selectedIndex();
        if (selected < 0 || selected >= m_gadgets.size()) return;

        // TabGroup backgrounds are intentionally kept behind ordinary page
        // gadgets. Front/back therefore reorders within the same paint layer.
        const bool isTab = m_gadgets[selected].type == QStringLiteral("TabGroup");
        int other = -1;
        if (toFront) {
            for (int i = m_gadgets.size() - 1; i >= 0; --i) {
                if ((m_gadgets[i].type == QStringLiteral("TabGroup")) == isTab) {
                    other = i;
                    break;
                }
            }
        } else {
            for (int i = 0; i < m_gadgets.size(); ++i) {
                if ((m_gadgets[i].type == QStringLiteral("TabGroup")) == isTab) {
                    other = i;
                    break;
                }
            }
        }
        if (other < 0 || other == selected) return;
        pushUndoSnapshot();
        const GuiDesignerGadget moving = m_gadgets.takeAt(selected);
        const int target = toFront ? (other > selected ? other : other + 1)
                                   : (other < selected ? other : other - 1);
        m_gadgets.insert(target, moving);
        m_canvas->setSelectedIndex(target);
        setModified(true);
        m_canvas->update();
        if (m_statusLabel)
            m_statusLabel->setText(toFront
                ? QObject::tr("%1: brought to front").arg(moving.name)
                : QObject::tr("%1: sent to back").arg(moving.name));
    }

    void nudgeSelectedGadget(
        int dx,
        int dy,
        bool autoRepeat)
    {
        if (!m_canvas) {
            return;
        }

        const int selected =
            m_canvas->selectedIndex();

        if (selected < 0
            || selected >= m_gadgets.size()) {
            return;
        }

        GuiDesignerGadget &g =
            m_gadgets[selected];

        const int step =
            m_canvas->gridSnap() > 1
                ? m_canvas->gridSnap()
                : 1;

        // Shift-marquee selects a group; arrow keys now move that entire group
        // by the same snapped step, with one shared boundary clamp. The current
        // primary gadget stays selected for property editing.
        if (m_canvas->selectionCount() > 1) {
            const QPoint delta = m_canvas->boundedGroupTranslation(
                QPoint(dx * step, dy * step));
            if (delta.isNull())
                return;

            // Like single-gadget nudging: holding one arrow is one Undo step.
            if (!autoRepeat)
                pushUndoSnapshot();
            m_canvas->translateSelectedGroup(delta);
            setModified(true);
            rebuildProperties();
            if (m_statusLabel) {
                m_statusLabel->setText(
                    QObject::tr("Moved %1 gadgets by %2, %3 px (%4 px grid)")
                        .arg(m_canvas->selectionCount())
                        .arg(delta.x()).arg(delta.y()).arg(step));
            }
            return;
        }

        const QSize clientSize =
            m_canvas->clientViewportSize();

        const int maxX =
            qMax(
                0,
                clientSize.width()
                    - g.rect.width());

        const int maxY =
            qMax(
                0,
                clientSize.height()
                    - g.rect.height());

        const QPoint oldPos =
            g.rect.topLeft();

        const QPoint newPos(
            qBound(
                0,
                oldPos.x() + dx * step,
                maxX),
            qBound(
                0,
                oldPos.y() + dy * step,
                maxY));

        if (newPos == oldPos) return;
        if (g.type == QStringLiteral("TabGroup")) {
            const QRect bounds = m_canvas->tabGroupPositionBounds(selected);
            if (QPoint(qBound(bounds.left(), newPos.x(), bounds.right()),
                       qBound(bounds.top(), newPos.y(), bounds.bottom())) == oldPos)
                return;
        }

        /* One Undo step for one held-arrow movement, not every auto-repeat. */
        if (!autoRepeat) {
            pushUndoSnapshot();
        }

        if (g.type == QStringLiteral("TabGroup")) {
            m_canvas->moveTabGroupWithMembers(selected, newPos);
        } else {
            g.rect.moveTopLeft(newPos);
        }
        syncDesignerDemoBitmapSize(&g);

        setModified(true);
        m_canvas->update();
        rebuildProperties();

        if (m_statusLabel) {
            m_statusLabel->setText(
                QObject::tr("%1: %2, %3  (%4 px nudge)")
                    .arg(g.name)
                    .arg(g.rect.x())
                    .arg(g.rect.y())
                    .arg(step));
        }
    }

    void resizeSelectedGadget(int dw, int dh, bool autoRepeat)
    {
        if (!m_canvas) return;
        const int selected = m_canvas->selectedIndex();
        if (selected < 0 || selected >= m_gadgets.size()) return;

        GuiDesignerGadget &g = m_gadgets[selected];
        // GridSelect derives its dimensions from cell count and cell size.
        if (g.type == QStringLiteral("GridSelect") || isVirtualDesignerGadget(g.type)) return;

        const int step = m_canvas->gridSnap() > 1
                             ? m_canvas->gridSnap() : 1;
        const QSize clientSize = m_canvas->clientViewportSize();
        const int maxW = qMax(4, clientSize.width() - g.rect.x());
        const int maxH = qMax(4, clientSize.height() - g.rect.y());
        const int width = qBound(4, g.rect.width() + dw * step, maxW);
        const int height = qBound(4, g.rect.height() + dh * step, maxH);
        if (width == g.rect.width() && height == g.rect.height()) return;

        if (!autoRepeat) pushUndoSnapshot();
        g.rect.setSize(QSize(width, height));
        syncDesignerDemoBitmapSize(&g);
        setModified(true);
        m_canvas->update();
        rebuildProperties();
        if (m_statusLabel) {
            m_statusLabel->setText(
                QObject::tr("%1: %2 × %3 (%4 px resize)")
                    .arg(g.name).arg(width).arg(height).arg(step));
        }
    }

    static QStringList windowFlagChoices()
    {
        return {
            QStringLiteral("SBX_WF_VISIBLE"),
            QStringLiteral("SBX_WF_NOBORDER"),
            QStringLiteral("SBX_WF_CLOSE"),
            QStringLiteral("SBX_WF_TITLE_BAR"),
            QStringLiteral("SBX_WF_TITLE_BAR_FLAT"),
            QStringLiteral("SBX_WF_ZORDER"),
            QStringLiteral("SBX_WF_MINIMISE"),
            QStringLiteral("SBX_WF_MAXRESTORE"),
            QStringLiteral("SBX_WF_SCREENBOUND"),
            QStringLiteral("SBX_WF_MOVEABLE"),
            QStringLiteral("SBX_WF_RESIZABLE"),
            QStringLiteral("SBX_WF_NOFOCUS"),
            QStringLiteral("SBX_WF_NOAUTOZORDER"),
            QStringLiteral("SBX_WF_ALWAYS_TO_BACK"),
            QStringLiteral("SBX_WF_ALWAYS_TO_FRONT"),
            QStringLiteral("SBX_WF_DOCKRIGHT"),
            QStringLiteral("SBX_WF_DOCKBOTTOM"),
            QStringLiteral("SBX_WF_DISABLE")
        };
    }

    static QStringList expandedWindowFlagTokens(
        const QString &expression)
    {
        const QStringList defaultFlags = {
            QStringLiteral("SBX_WF_MOVEABLE"),
            QStringLiteral("SBX_WF_VISIBLE"),
            QStringLiteral("SBX_WF_CLOSE"),
            QStringLiteral("SBX_WF_TITLE_BAR"),
            QStringLiteral("SBX_WF_ZORDER"),
            QStringLiteral("SBX_WF_MINIMISE"),
            QStringLiteral("SBX_WF_MAXRESTORE"),
            QStringLiteral("SBX_WF_RESIZABLE"),
            QStringLiteral("SBX_WF_SCREENBOUND")
        };

        const QStringList baseZeroFlags = {
            QStringLiteral("SBX_WF_VISIBLE"),
            QStringLiteral("SBX_WF_ALWAYS_TO_BACK"),
            QStringLiteral("SBX_WF_NOBORDER"),
            QStringLiteral("SBX_WF_TITLE_BAR_FLAT")
        };

        QStringList expanded;

        for (const QString &token :
             splitFlagExpression(expression)) {
            if (token == QStringLiteral("SBX_WIN_DEFAULT")) {
                expanded.append(defaultFlags);
            } else if (token == QStringLiteral("SBX_WF_BASE_ZERO")) {
                expanded.append(baseZeroFlags);
            } else {
                expanded.append(token);
            }
        }

        expanded.removeDuplicates();
        return expanded;
    }

    static QString expandedWindowFlagExpression(
        const QString &expression)
    {
        return expandedWindowFlagTokens(expression)
            .join(QStringLiteral(" | "));
    }

    static QStringList gadgetFlagChoices(
        const QString &type)
    {
        /*
         * Only show flags that are useful to this gadget class. GAD_TOOL_MOUSEMOVE
         * is generic at the CoderGirl dispatcher level, so it is offered to all
         * interactive gadget types.
         */
        QStringList flags = {
            QStringLiteral("GAD_TOOL_DEFAULT")
        };

        if (type != QStringLiteral("Label")
            && type != QStringLiteral("ProgressBar")) {
            flags.append(
                QStringLiteral(
                    "GAD_TOOL_MOUSEMOVE"));
        }

        if (type == QStringLiteral("Button")) {
            flags.append({
                QStringLiteral("GAD_TOOL_CYCLEBUTTON"),
                QStringLiteral("GAD_TOOL_NOBORDER"),
                QStringLiteral("GAD_TOOL_ALIGN_BELOW"),
                QStringLiteral("GAD_TOOL_ALIGN_LEFT"),
                QStringLiteral("GAD_TOOL_ALIGN_RIGHT"),
                QStringLiteral("GAD_TOOL_OPAQUE_TEXT"),
                QStringLiteral("GAD_TOOL_TOGGLE")
            });
        } else if (type == QStringLiteral("Label")) {
            flags.append({
                QStringLiteral("GAD_TOOL_INSET"),
                QStringLiteral("GAD_TOOL_TRANSPARENT")
            });
        } else if (type == QStringLiteral("Canvas")) {
            flags.append(QStringLiteral("GAD_TOOL_INSET"));
        } else if (type == QStringLiteral("Slider")) {
            flags.append({
                QStringLiteral("GAD_TOOL_DOCKED_RIGHT"),
                QStringLiteral("GAD_TOOL_DOCKED_BOTTOM")
            });
        } else if (type == QStringLiteral("Scrollbar")) {
            flags.append({
                QStringLiteral("GAD_TOOL_DOCKED_RIGHT"),
                QStringLiteral("GAD_TOOL_DOCKED_BOTTOM"),
                QStringLiteral("GAD_TOOL_SCROLLARROWS")
            });
        } else if (type == QStringLiteral("ListBox")
                   || type == QStringLiteral("GridSelect")
                   || type == QStringLiteral("BitmapView")) {
            flags.append({
                QStringLiteral("GAD_TOOL_NOBORDER"),
                QStringLiteral("GAD_TOOL_INSET")
            });
        } else if (type == QStringLiteral("TextArea")) {
            flags.append(
                QStringLiteral(
                    "GAD_TOOL_NOBORDER"));
        }

        flags.removeDuplicates();
        return flags;
    }

    static QStringList splitFlagExpression(
        const QString &expression)
    {
        QStringList tokens;

        for (QString token :
             expression.split(
                 QLatin1Char('|'),
                 Qt::SkipEmptyParts)) {
            token = token.trimmed();

            while (token.startsWith(
                       QLatin1Char('('))
                   && token.endsWith(
                       QLatin1Char(')'))
                   && token.size() > 2) {
                token =
                    token.mid(
                        1,
                        token.size() - 2)
                        .trimmed();
            }

            if (!token.isEmpty()
                && token != QStringLiteral("0")
                && token != QStringLiteral("0u")
                && token != QStringLiteral("TB_SINGLELINE")
                && token != QStringLiteral("TA_DEFAULT")) {
                tokens.append(token);
            }
        }

        tokens.removeDuplicates();
        return tokens;
    }

    static int gridSelectBorder(
        const GuiDesignerGadget &g)
    {
        return g.flags.contains(
                   QStringLiteral(
                       "GAD_TOOL_NOBORDER"))
            ? 0
            : 2;
    }

    static void normaliseGridCellText(
        GuiDesignerGadget *g)
    {
        if (!g
            || g->type
               != QStringLiteral(
                   "GridSelect")) {
            return;
        }

        const int cellCount =
            qBound(
                1,
                g->cellsX * g->cellsY,
                256);

        while (g->gridCellText.size() > cellCount) {
            g->gridCellText.removeLast();
        }

        for (QString &text :
             g->gridCellText) {
            text = text.left(4);
        }
    }

    static void syncGridSelectGeometry(
        GuiDesignerGadget *g)
    {
        if (!g
            || g->type
               != QStringLiteral(
                   "GridSelect")) {
            return;
        }

        const int border =
            gridSelectBorder(
                *g);

        g->rect.setSize(
            QSize(
                qMax(
                    1,
                    g->cellWidth)
                    * qMax(
                        1,
                        g->cellsX)
                    + border,
                qMax(
                    1,
                    g->cellHeight)
                    * qMax(
                        1,
                        g->cellsY)
                    + border));
    }

    static QStringList textBoxFlagChoices()
    {
        return {
            QStringLiteral("TB_READONLY"),
            QStringLiteral("TB_MULTILINE")
        };
    }

    static QStringList textAreaFlagChoices()
    {
        return {
            QStringLiteral("TA_READONLY"),
            QStringLiteral("TA_WORDWRAP"),
            QStringLiteral("TA_NO_HSCROLL"),
            QStringLiteral("TA_NOSEL")
        };
    }

    static QStringList gridSelectFlagChoices()
    {
        return {
            QStringLiteral("GAD_GRIDSEL_JUST_ONE"),
            QStringLiteral("GAD_GRIDSEL_TEXT_INVERT"),
            QStringLiteral("GAD_GRIDSEL_NOHIGHLIGHT")
        };
    }

    static QStringList bitmapViewFlagChoices()
    {
        return {
            QStringLiteral(
                "BVF_SHOW_FRAME"),
            QStringLiteral(
                "BVF_PAN"),
            QStringLiteral(
                "BVF_SRC_ROWMAJOR"),
            QStringLiteral(
                "BVF_SRC_XMAJOR"),
            QStringLiteral(
                "BVF_WRAP"),
            QStringLiteral(
                "BVF_PERSISTANT")
        };
    }

    QByteArray designerSnapshot() const
    {
        QJsonObject window;
        window.insert(
            QStringLiteral("name"),
            m_window.name);
        window.insert(
            QStringLiteral("title"),
            m_window.title);
        window.insert(
            QStringLiteral("flags"),
            m_window.flags);
        window.insert(
            QStringLiteral("backPen"),
            m_window.backPen);
        window.insert(
            QStringLiteral("callbackMode"),
            m_window.callbackMode);
        window.insert(
            QStringLiteral("x"),
            m_window.rect.x());
        window.insert(
            QStringLiteral("y"),
            m_window.rect.y());
        window.insert(
            QStringLiteral("w"),
            m_window.rect.width());
        window.insert(
            QStringLiteral("h"),
            m_window.rect.height());

        QJsonArray gadgets;

        for (const GuiDesignerGadget &g :
             m_gadgets) {
            gadgets.append(
                gadgetToJson(g));
        }

        QJsonArray menus;

        for (const GuiDesignerMenuTitle &menu :
             m_menus) {
            QJsonObject menuObject;
            menuObject.insert(
                QStringLiteral("title"),
                menu.title);

            QJsonArray items;

            for (const GuiDesignerMenuItem &item :
                 menu.items) {
                QJsonObject itemObject;
                itemObject.insert(
                    QStringLiteral("name"),
                    item.name);
                itemObject.insert(
                    QStringLiteral("text"),
                    item.text);
                itemObject.insert(
                    QStringLiteral("callback"),
                    item.callback);
                itemObject.insert(
                    QStringLiteral("flags"),
                    item.flags);

                items.append(
                    itemObject);
            }

            menuObject.insert(
                QStringLiteral("items"),
                items);

            menus.append(
                menuObject);
        }

        QJsonObject root;
        root.insert(
            QStringLiteral("window"),
            window);
        root.insert(
            QStringLiteral("gadgets"),
            gadgets);
        root.insert(
            QStringLiteral("menus"),
            menus);
        root.insert(
            QStringLiteral("selectedIndex"),
            m_canvas
                ? m_canvas->selectedIndex()
                : -1);
        // Undo-only group state. This JSON is NOT written as a .sbui design.
        QJsonArray groupSelection;
        if (m_canvas) {
            for (int index : m_canvas->selectedGroupIndices())
                groupSelection.append(index);
        }
        root.insert(QStringLiteral("multiSelected"), groupSelection);
        root.insert(
            QStringLiteral("modified"),
            m_modified);

        return QJsonDocument(root)
            .toJson(
                QJsonDocument::Compact);
    }

    void clearUndoHistory()
    {
        m_undoStates.clear();

        if (m_undoAction) {
            m_undoAction->setEnabled(false);
        }
    }

    void pushUndoSnapshot()
    {
        if (m_restoringUndo) {
            return;
        }

        const QByteArray state =
            designerSnapshot();

        if (!m_undoStates.isEmpty()
            && m_undoStates.last()
               == state) {
            return;
        }

        m_undoStates.append(
            state);

        constexpr int MaxUndoStates = 120;

        while (m_undoStates.size()
               > MaxUndoStates) {
            m_undoStates.removeFirst();
        }

        if (m_undoAction) {
            m_undoAction->setEnabled(true);
        }
    }

    void restoreDesignerSnapshot(
        const QByteArray &state)
    {
        QJsonParseError error;

        const QJsonDocument doc =
            QJsonDocument::fromJson(
                state,
                &error);

        if (error.error
                != QJsonParseError::NoError
            || !doc.isObject()) {
            return;
        }

        const QJsonObject root =
            doc.object();

        const QJsonObject w =
            root.value(
                    QStringLiteral(
                        "window"))
                .toObject();

        m_restoringUndo = true;

        m_window.name =
            w.value(
                 QStringLiteral("name"))
                .toString(
                    QStringLiteral(
                        "MainWindow"));

        m_window.title =
            w.value(
                 QStringLiteral("title"))
                .toString();

        m_window.flags =
            w.value(
                 QStringLiteral("flags"))
                .toString(
                    QStringLiteral(
                        "SBX_WIN_DEFAULT"));

        m_window.backPen =
            w.value(
                 QStringLiteral("backPen"))
                .toInt(1);

        m_window.callbackMode =
            w.value(
                 QStringLiteral("callbackMode"))
                .toInt(1);

        m_window.rect =
            QRect(
                w.value(
                     QStringLiteral("x"))
                    .toInt(),
                w.value(
                     QStringLiteral("y"))
                    .toInt(),
                w.value(
                     QStringLiteral("w"))
                    .toInt(400),
                w.value(
                     QStringLiteral("h"))
                    .toInt(250));

        m_gadgets.clear();

        // Undo snapshots use gadgetToJson(), just like .sbui files.
        // Restore using the same complete gadget decoder as clipboard
        // paste instead of a partial field-by-field implementation.
        // In particular, BitmapView requires bitmapPixelsBase64 and
        // bitmapImagePath or undoing an unrelated edit erases its image.
        for (const QJsonValue &value :
             root.value(QStringLiteral("gadgets")).toArray()) {
            GuiDesignerGadget gadget;
            if (gadgetFromJsonObject(value.toObject(), &gadget)) {
                m_gadgets.append(gadget);
            }
        }

        normalizeRadioGroups();

        m_menus.clear();

        for (const QJsonValue &menuValue :
             root.value(
                     QStringLiteral(
                         "menus"))
                 .toArray()) {
            const QJsonObject mo =
                menuValue.toObject();

            GuiDesignerMenuTitle menu;
            menu.title =
                mo.value(
                      QStringLiteral(
                          "title"))
                    .toString();

            for (const QJsonValue &itemValue :
                 mo.value(
                       QStringLiteral(
                           "items"))
                    .toArray()) {
                const QJsonObject io =
                    itemValue.toObject();

                GuiDesignerMenuItem item;
                item.name =
                    io.value(
                          QStringLiteral(
                              "name"))
                        .toString();
                item.text =
                    io.value(
                          QStringLiteral(
                              "text"))
                        .toString();
                item.callback =
                    io.value(
                          QStringLiteral(
                              "callback"))
                        .toString();
                item.flags =
                    io.value(
                          QStringLiteral(
                              "flags"))
                        .toString();

                normaliseMenuItem(
                    &item);

                menu.items.append(
                    item);
            }

            m_menus.append(
                menu);
        }

        const int selected =
            qBound(
                -1,
                root.value(
                        QStringLiteral(
                            "selectedIndex"))
                    .toInt(-1),
                static_cast<int>(m_gadgets.size()) - 1);

        m_canvas->setSelectedIndex(
            selected);

        QList<int> restoredGroup;
        for (const QJsonValue &value :
             root.value(QStringLiteral("multiSelected")).toArray()) {
            if (value.isDouble())
                restoredGroup.append(value.toInt(-1));
        }
        m_canvas->restoreGroupSelection(restoredGroup);

        rebuildMenuTree();
        rebuildProperties();
        m_canvas->update();

        setModified(
            root.value(
                    QStringLiteral(
                        "modified"))
                .toBool(true));

        m_restoringUndo = false;
    }

    void undoLastDesignerChange()
    {
        m_inlineTextEditing = false;
        m_inlineReplaceOnFirstKey = true;
        if (m_undoStates.isEmpty()) {
            return;
        }

        const QByteArray state =
            m_undoStates.takeLast();

        restoreDesignerSnapshot(
            state);

        if (m_undoAction) {
            m_undoAction->setEnabled(
                !m_undoStates.isEmpty());
        }

        if (m_statusLabel) {
            m_statusLabel->setText(
                QObject::tr(
                    "Undo"));
        }
    }

    void jumpToMenuItemSource(int menuIndex, int itemIndex)
    {
        if (menuIndex < 0 || menuIndex >= m_menus.size()
            || itemIndex < 0 || itemIndex >= m_menus.at(menuIndex).items.size())
            return;

        const GuiDesignerMenuItem &item = m_menus.at(menuIndex).items.at(itemIndex);
        if (item.callback.trimmed().isEmpty())
            return;

        const QString callback = safeCIdentifier(item.callback,
                                                  QStringLiteral("MenuCallback"));
        if (m_modified && !saveDesign())
            return;
        if ((m_needsGeneration || !QFile::exists(generatedCPath()))
            && !generateCFile(false))
            return;

        if (sourceNavigationRequested)
            sourceNavigationRequested(generatedCPath(),
                QStringLiteral("/* <SIDBOX-GUI:USER %1> */").arg(callback),
                QStringLiteral("static void %1(").arg(callback));
    }

    void jumpToGadgetSource(
        int index)
    {
        if (index < 0
            || index >= m_gadgets.size()) {
            return;
        }

        if (m_modified && !saveDesign()) {
            return;
        }
        if ((m_needsGeneration || !QFile::exists(generatedCPath()))
            && !generateCFile(false)) {
            return;
        }

        const GuiDesignerGadget &g =
            m_gadgets.at(index);

        QString callback;

        const bool changeDriven =
            g.type == QStringLiteral("Checkbox")
            || g.type == QStringLiteral("Radio")
            || g.type == QStringLiteral("Slider")
            || g.type == QStringLiteral("Scrollbar")
            || g.type == QStringLiteral("ListBox")
            || g.type == QStringLiteral("GridSelect")
            || g.type == QStringLiteral("TextBox")
            || g.type == QStringLiteral("TextArea")
            || g.type == QStringLiteral("BitmapView");

        if (changeDriven
            && !g.onChange.isEmpty()) {
            callback =
                g.onChange;
        } else if (!g.onActivate.isEmpty()) {
            callback =
                g.onActivate;
        } else if (!g.onChange.isEmpty()) {
            callback =
                g.onChange;
        }

        QString preferred;

        if (g.type == QStringLiteral("FileRequester") || g.type == QStringLiteral("MessageBox")) {
            if (sourceNavigationRequested)
                sourceNavigationRequested(generatedCPath(),
                    QStringLiteral("/* <SIDBOX-GUI:USER %1> */").arg(g.onActivate), g.onActivate);
            return;
        }
        if (g.type == QStringLiteral("KBInput") || g.type == QStringLiteral("MSInput")) {
            if (sourceNavigationRequested)
                sourceNavigationRequested(generatedCPath(),
                    QStringLiteral("/* <SIDBOX-GUI:USER %1> */").arg(g.onActivate),
                    QStringLiteral("%1(CGEventType event").arg(g.onActivate));
            return;
        }
        if (g.type == QStringLiteral("UART1")) {
            if (sourceNavigationRequested)
                sourceNavigationRequested(generatedCPath(),
                    QStringLiteral("/* <SIDBOX-GUI:USER %1> */").arg(g.onActivate),
                    QStringLiteral("%1(void *user)").arg(g.onActivate));
            return;
        }
        if (g.type == QStringLiteral("Media")) {
            if (sourceNavigationRequested)
                sourceNavigationRequested(generatedCPath(),
                    QStringLiteral("static void %1_Play(void)").arg(safeCIdentifier(g.name, QStringLiteral("media"))),
                    QStringLiteral("%1_Play(void)").arg(safeCIdentifier(g.name, QStringLiteral("media"))));
            return;
        }

        if (!callback.isEmpty()) {
            preferred =
                QStringLiteral(
                    "/* <SIDBOX-GUI:USER %1> */")
                    .arg(callback);
        } else if (!gadgetUsesDirectCallbacks(g)) {
            preferred =
                QStringLiteral(
                    "if (m->gadget == %1)")
                    .arg(
                        safeCIdentifier(
                            g.name,
                            QStringLiteral(
                                "gadget")));
        }

        const QString fallback =
            safeCIdentifier(
                g.name,
                QStringLiteral(
                    "gadget"))
            + QStringLiteral(" = ");

        if (sourceNavigationRequested) {
            sourceNavigationRequested(
                generatedCPath(),
                preferred,
                fallback);
        }
    }

    // Single source of truth for a gadget's initial dimensions and appearance.
    // Calling this for a drag preview does not add it to the design or undo log.
    GuiDesignerGadget makeDefaultGadget(const QString &type) const
    {
        GuiDesignerGadget g;
        g.type = type;
        g.name = uniqueGadgetName(type);
        g.rect = defaultRectForType(type, m_gadgets.size());
        g.text = (type == QStringLiteral("TabGroup")) ? QStringLiteral("General|Advanced")
               : (type == QStringLiteral("Button")) ? QStringLiteral("Button")
               : (type == QStringLiteral("Label")) ? QStringLiteral("Label")
               : (type == QStringLiteral("Checkbox")) ? QStringLiteral("Checkbox")
               : (type == QStringLiteral("Radio")) ? QStringLiteral("Radio")
               : (type == QStringLiteral("TextBox")) ? QStringLiteral("Text")
               : (type == QStringLiteral("TextArea")) ? QStringLiteral("Text Area")
               : QString();

        if (type == QStringLiteral("Button") || type == QStringLiteral("Checkbox")
            || type == QStringLiteral("Radio") || type == QStringLiteral("Slider")
            || type == QStringLiteral("Scrollbar") || type == QStringLiteral("ListBox")
            || type == QStringLiteral("GridSelect") || type == QStringLiteral("TextBox")
            || type == QStringLiteral("TextArea") || type == QStringLiteral("Canvas")
            || type == QStringLiteral("BitmapView")) {
            g.onActivate = QStringLiteral("On_%1_Activate").arg(g.name);
        }
        if (type == QStringLiteral("Timer"))
            g.onActivate = QStringLiteral("On_%1_Tick").arg(g.name);
        if (type == QStringLiteral("Messenger"))
            g.onActivate = QStringLiteral("On_%1_Message").arg(g.name);
        if (type == QStringLiteral("UART1"))
            g.onActivate = QStringLiteral("On_%1_Data").arg(g.name);
        if (type == QStringLiteral("KBInput"))
            g.onActivate = QStringLiteral("On_%1_Key").arg(g.name);
        if (type == QStringLiteral("MSInput"))
            g.onActivate = QStringLiteral("On_%1_Mouse").arg(g.name);
        if (type == QStringLiteral("FileRequester")) {
            g.onActivate = QStringLiteral("On_%1_Selected").arg(g.name);
            g.onChange = QStringLiteral("On_%1_Cancelled").arg(g.name);
        }
        if (type == QStringLiteral("MessageBox")) {
            g.dialogTitle = QStringLiteral("Confirmation");
            g.onActivate = QStringLiteral("On_%1_Result").arg(g.name);
        }
        if (type == QStringLiteral("Checkbox") || type == QStringLiteral("Radio")
            || type == QStringLiteral("Slider") || type == QStringLiteral("Scrollbar")
            || type == QStringLiteral("ListBox") || type == QStringLiteral("GridSelect")
            || type == QStringLiteral("TextBox") || type == QStringLiteral("TextArea")
            || type == QStringLiteral("BitmapView")) {
            g.onChange = QStringLiteral("On_%1_Change").arg(g.name);
        }

        // Match the original TabGroup bevel: old designs were always inset.
        if (type == QStringLiteral("TabGroup")) g.flags = QStringLiteral("GAD_TOOL_INSET");
        if (type == QStringLiteral("TextBox")) g.typeFlags = QStringLiteral("TB_SINGLELINE");
        if (type == QStringLiteral("TextArea")) g.typeFlags = QStringLiteral("TA_DEFAULT");
        if (type == QStringLiteral("ProgressBar")) g.value = 50;
        if (type == QStringLiteral("Canvas")) g.typeFlags = QStringLiteral("CNV_RECT");
        if (type == QStringLiteral("BitmapView")) {
            g.typeFlags =
                QStringLiteral(
                    "BVF_SHOW_FRAME | BVF_SRC_ROWMAJOR");

            g.flags =
                QStringLiteral(
                    "GAD_TOOL_INSET");

            /*
             * Automatic designer demo bitmap.
             *
             * CoderGirl's BitmapView image dimensions describe the DRAWABLE
             * pixel area, not blindly the outer gadget rectangle:
             *
             *   bordered/inset gadget -> one-pixel border on each side
             *   GAD_TOOL_NOBORDER     -> full gadget rectangle is drawable
             */
            const int bitmapBorder =
                g.flags.contains(
                    QStringLiteral(
                        "GAD_TOOL_NOBORDER"))
                    ? 0
                    : 2;

            g.bitmapWidth =
                qMax(
                    1,
                    g.rect.width()
                        - bitmapBorder);

            g.bitmapHeight =
                qMax(
                    1,
                    g.rect.height()
                        - bitmapBorder);

            g.bitmapSource =
                safeCIdentifier(
                    g.name,
                    QStringLiteral(
                        "bitmap"))
                + QStringLiteral(
                    "_pixels");
        }
        if (type == QStringLiteral("GridSelect")) {
            g.typeFlags =
                QStringLiteral(
                    "GAD_GRIDSEL_JUST_ONE");

            normaliseGridCellText(
                &g);

            syncGridSelectGeometry(
                &g);
        }

        if (type == QStringLiteral("ListBox")) {
            g.listItems = {
                QStringLiteral("Item 1"),
                QStringLiteral("Item 2"),
                QStringLiteral("Item 3")
            };
        }

        return g;
    }

    void addGadget(const QString &type, const QPoint &dropPosition = QPoint(-1, -1))
    {
        pushUndoSnapshot();

        GuiDesignerGadget g = makeDefaultGadget(type);

        if (dropPosition.x() >= 0
            && dropPosition.y() >= 0) {
            QPoint topLeft(
                dropPosition.x() - g.rect.width() / 2,
                dropPosition.y() - g.rect.height() / 2);

            const int snap =
                m_canvas
                    ? m_canvas->gridSnap()
                    : 0;

            if (snap > 1) {
                topLeft.setX(
                    ((topLeft.x() + snap / 2) / snap) * snap);

                topLeft.setY(
                    ((topLeft.y() + snap / 2) / snap) * snap);
            }

            const QSize clientSize =
                m_canvas
                    ? m_canvas->clientViewportSize()
                    : QSize(480, 320);

            topLeft.setX(
                qBound(
                    0,
                    topLeft.x(),
                    qMax(0, clientSize.width() - g.rect.width())));

            topLeft.setY(
                qBound(
                    0,
                    topLeft.y(),
                    qMax(0, clientSize.height() - g.rect.height())));

            g.rect.moveTopLeft(
                topLeft);
        }

        // Creating a control while a TabGroup is selected places it on the
        // active page. Drag/drop into a TabGroup body does the same.
        if (type != QStringLiteral("TabGroup") && !isVirtualDesignerGadget(type)) {
            int owner = -1;
            if (dropPosition.x() >= 0) {
                for (int i = m_gadgets.size()-1; i >= 0; --i) {
                    if (m_gadgets[i].type == QStringLiteral("TabGroup")
                        && m_gadgets[i].rect.adjusted(0, 24, 0, 0).contains(dropPosition)) {
                        owner = i;
                        break;
                    }
                }
            }
            if (owner < 0 && m_canvas && m_canvas->selectedIndex() >= 0) {
                const int i = m_canvas->selectedIndex();
                if (m_gadgets[i].type == QStringLiteral("TabGroup")) owner = i;
            }
            if (owner >= 0) {
                const GuiDesignerGadget &tabs = m_gadgets[owner];
                g.tabOwner = tabs.name;
                g.tabPage = qBound(0, tabs.value, designerTabTitles(tabs).size()-1);
                if (dropPosition.x() < 0) {
                    g.rect.moveTopLeft(tabs.rect.topLeft() + QPoint(12, 42));
                }
            }
        }
        m_gadgets.append(g);
        m_canvas->setSelectedIndex(m_gadgets.size() - 1);
        setModified(true);
        m_canvas->update();
    }

    void clearPropertyRows()
    {
        m_textPropertyEdit.clear();
        m_propertyLayout->clearRows();
    }

    QSpinBox *addSpin(const QString &label, int value, int min, int max,
                      const std::function<void(int)> &changed)
    {
        auto *spin = new QSpinBox(m_propertyHost);
        spin->setRange(min, max);
        spin->setValue(value);
        m_propertyLayout->addRow(label, spin);
        connect(spin, qOverload<int>(&QSpinBox::valueChanged), this,
                [this, changed](int v) {
                    pushUndoSnapshot();
                    changed(v);
                    setModified(true);
                    m_canvas->update();
                });
        return spin;
    }

    void addPen(const QString &label, int value, int min,
                const std::function<void(int)> &changed)
    {
        auto *row = new QHBoxLayout;
        row->setContentsMargins(0, 0, 0, 0);
        row->setSpacing(5);

        auto *spin = new QSpinBox(m_propertyHost);
        spin->setRange(min, 255);
        spin->setValue(value);
        spin->setMinimumWidth(62);
        spin->setMaximumWidth(90);
        spin->setToolTip(QObject::tr("SIDBOX palette index; -1 uses the gadget default"));
        row->addWidget(spin);

        auto *swatch = new QLabel(m_propertyHost);
        swatch->setFixedSize(20, 20);
        swatch->setAlignment(Qt::AlignCenter);
        const auto updateSwatch = [swatch](int pen) {
            if (pen < 0) {
                swatch->setText(QStringLiteral("–"));
                swatch->setStyleSheet(QStringLiteral(
                    "QLabel { background-color: #252525; color: #dddddd; "
                    "border: 1px solid #505050; border-radius: 0px; }"));
                swatch->setToolTip(QObject::tr("Default pen"));
            } else {
                const QColor colour = coderGirlPen(pen);
                swatch->clear();
                swatch->setStyleSheet(QStringLiteral(
                    "QLabel { background-color: %1; border: 1px solid #505050; "
                    "border-radius: 0px; }").arg(colour.alpha() ? colour.name()
                                                              : QStringLiteral("#505050")));
                swatch->setToolTip(QObject::tr("Pen %1: ARGB #%2")
                    .arg(pen)
                    .arg(QString::number(kCoderGirlClut[pen], 16)
                         .rightJustified(8, QLatin1Char('0')).toUpper()));
            }
        };
        updateSwatch(value);
        row->addWidget(swatch);

        auto *choose = new QPushButton(QObject::tr("Choose"), m_propertyHost);
        choose->setToolTip(QObject::tr("Choose from the 256-colour SIDBOX CLUT"));
        row->addWidget(choose);
        row->addStretch(1);
        m_propertyLayout->addRow(label, row);

        connect(spin, qOverload<int>(&QSpinBox::valueChanged), this,
                [this, changed, updateSwatch](int v) {
                    pushUndoSnapshot();
                    changed(v);
                    setModified(true);
                    updateSwatch(v);
                    m_canvas->update();
                });
        connect(choose, &QPushButton::clicked, this, [this, spin, min]() {
            const int result = showPaletteDialog(spin->value(), true, min < 0);
            if (result >= min && result <= 255)
                spin->setValue(result); // One normal undoable property edit.
        });
    }

    QLineEdit *addLine(const QString &label, const QString &value,
                       const std::function<void(const QString &)> &changed)
    {
        auto *edit = new QLineEdit(value, m_propertyHost);
        edit->setProperty("designerCommittedText", value);
        m_propertyLayout->addRow(label, edit);
        connect(edit, &QLineEdit::editingFinished, this, [this, edit, changed]() {
            // Focus changes (for example, selecting another gadget) also emit
            // editingFinished. Only genuine changes should dirty the design;
            // inline canvas typing updates the committed baseline as well.
            if (edit->text() == edit->property("designerCommittedText").toString()) return;
            pushUndoSnapshot();
            changed(edit->text());
            setModified(true);
            m_canvas->update();
            rebuildProperties();
        });
        return edit;
    }

    QCheckBox *addCheck(
        const QString &label,
        bool checked,
        const std::function<void(bool)> &changed)
    {
        auto *check =
            new QCheckBox(
                m_propertyHost);

        check->setChecked(
            checked);

        m_propertyLayout->addRow(
            label,
            check);

        connect(
            check,
            &QCheckBox::toggled,
            this,
            [this,
             changed](bool value) {
                pushUndoSnapshot();
                changed(value);
                setModified(true);
                m_canvas->update();
            });

        return check;
    }

    QComboBox *addStringChoice(
        const QString &label,
        const QStringList &choices,
        const QString &currentValue,
        const std::function<void(const QString &)> &changed)
    {
        auto *combo =
            new QComboBox(
                m_propertyHost);

        for (const QString &choice :
             choices) {
            combo->addItem(
                choice,
                choice);
        }

        int index =
            combo->findData(
                currentValue);

        if (index < 0) {
            index =
                combo->findText(
                    currentValue);
        }

        combo->setCurrentIndex(
            index >= 0
                ? index
                : 0);

        m_propertyLayout->addRow(
            label,
            combo);

        connect(
            combo,
            qOverload<int>(
                &QComboBox::currentIndexChanged),
            this,
            [this,
             combo,
             changed](int) {
                pushUndoSnapshot();
                changed(
                    combo->currentData()
                        .toString());
                setModified(true);
                m_canvas->update();
            });

        return combo;
    }

    QComboBox *addChoice(
        const QString &label,
        const QList<QPair<QString, int>> &choices,
        int currentValue,
        const std::function<void(int)> &changed)
    {
        auto *combo =
            new QComboBox(
                m_propertyHost);

        int currentIndex = 0;

        for (int i = 0;
             i < choices.size();
             ++i) {
            combo->addItem(
                choices.at(i).first,
                choices.at(i).second);

            if (choices.at(i).second
                == currentValue) {
                currentIndex = i;
            }
        }

        combo->setCurrentIndex(
            currentIndex);

        m_propertyLayout->addRow(
            label,
            combo);

        connect(
            combo,
            qOverload<int>(
                &QComboBox::currentIndexChanged),
            this,
            [this,
             combo,
             changed](int) {
                pushUndoSnapshot();
                changed(
                    combo->currentData()
                        .toInt());
                setModified(true);
                m_canvas->update();
            });

        return combo;
    }

    bool gadgetUsesDirectCallbacks(
        const GuiDesignerGadget &g) const
    {
        if (g.callbackRoute == 1) {
            return true;
        }

        if (g.callbackRoute == 0) {
            return false;
        }

        return m_window.callbackMode == 1;
    }

    static QString directWrapperName(
        const QString &callback)
    {
        return QStringLiteral(
                   "SidboxDirect_%1")
            .arg(
                safeCIdentifier(
                    callback,
                    QStringLiteral(
                        "Callback")));
    }

    static QString changeEventForGadget(
        const GuiDesignerGadget &g)
    {
        if (g.type == QStringLiteral("Checkbox")) {
            return QStringLiteral("CGEVT_GAD_CHECKBOX_CHANGED");
        }

        if (g.type == QStringLiteral("Radio")) {
            return QStringLiteral("CGEVT_GAD_RADIO_CHANGED");
        }

        if (g.type == QStringLiteral("Slider")
            || g.type == QStringLiteral("Scrollbar")) {
            return QStringLiteral("CGEVT_GAD_SLIDERVAL_CHANGED");
        }

        if (g.type == QStringLiteral("GridSelect")) {
            return QStringLiteral("CGEVT_GAD_GRID_CHANGED");
        }

        if (g.type == QStringLiteral("ListBox")) {
            return QStringLiteral("CGEVT_GAD_LISTBOX_CHANGED");
        }

        if (g.type == QStringLiteral("BitmapView")) {
            return QStringLiteral("CGEVT_GAD_MOUSE_MOVE");
        }

        if (g.type == QStringLiteral("TextBox")
            || g.type == QStringLiteral("TextArea")) {
            return QStringLiteral("CGEVT_GAD_CARET_MOVED");
        }

        return {};
    }

    void normalizeRadioGroups()
    {
        QSet<int> groupsWithCheckedRadio;

        /*
         * Match CoderGirl creation semantics: a later checked radio clears an
         * earlier checked radio in the same group. Walk backwards so the last
         * checked radio in design order wins.
         */
        for (int i = m_gadgets.size() - 1;
             i >= 0;
             --i) {
            GuiDesignerGadget &g =
                m_gadgets[i];

            if (g.type
                    != QStringLiteral(
                        "Radio")
                || !g.checked) {
                continue;
            }

            if (groupsWithCheckedRadio.contains(
                    g.group)) {
                g.checked = 0;
            } else {
                groupsWithCheckedRadio.insert(
                    g.group);
            }
        }
    }

    void setRadioChecked(
        int index,
        int checked)
    {
        if (index < 0
            || index >= m_gadgets.size()
            || m_gadgets[index].type
               != QStringLiteral("Radio")) {
            return;
        }

        GuiDesignerGadget &radio =
            m_gadgets[index];

        radio.checked =
            checked ? 1 : 0;

        if (!radio.checked) {
            return;
        }

        for (int i = 0;
             i < m_gadgets.size();
             ++i) {
            if (i == index) {
                continue;
            }

            GuiDesignerGadget &other =
                m_gadgets[i];

            if (other.type
                    == QStringLiteral("Radio")
                && other.group
                   == radio.group) {
                other.checked = 0;
            }
        }
    }

    bool isDesignerDemoBitmap(
        const GuiDesignerGadget &g) const
    {
        if (g.type
            != QStringLiteral("BitmapView")) {
            return false;
        }

        const QString expected =
            safeCIdentifier(
                g.name,
                QStringLiteral("bitmap"))
            + QStringLiteral("_pixels");

        return g.bitmapPixels.isEmpty()
            && g.bitmapSource
                   .trimmed()
               == expected;
    }

    static int bitmapViewDrawableBorder(
        const GuiDesignerGadget &g)
    {
        return g.flags.contains(
                   QStringLiteral(
                       "GAD_TOOL_NOBORDER"))
            ? 0
            : 2;
    }

    void syncDesignerDemoBitmapSize(
        GuiDesignerGadget *g) const
    {
        if (!g
            || !isDesignerDemoBitmap(
                *g)) {
            return;
        }

        const int border =
            bitmapViewDrawableBorder(
                *g);

        g->bitmapWidth =
            qMax(
                1,
                g->rect.width()
                    - border);

        g->bitmapHeight =
            qMax(
                1,
                g->rect.height()
                    - border);
    }

    void normaliseBitmapView(
        GuiDesignerGadget *g) const
    {
        if (!g
            || g->type
               != QStringLiteral(
                   "BitmapView")) {
            return;
        }

        if (g->typeFlags.trimmed().isEmpty()) {
            g->typeFlags =
                QStringLiteral(
                    "BVF_SHOW_FRAME | BVF_SRC_ROWMAJOR");
        }

        if (g->bitmapSource.trimmed().isEmpty()) {
            g->bitmapSource =
                safeCIdentifier(
                    g->name,
                    QStringLiteral(
                        "bitmap"))
                + QStringLiteral(
                    "_pixels");
        }

        if (isDesignerDemoBitmap(*g)) {
            syncDesignerDemoBitmapSize(g);
        } else {
            g->bitmapWidth = qMax(1, g->bitmapWidth);
            g->bitmapHeight = qMax(1, g->bitmapHeight);

            const qsizetype expected =
                static_cast<qsizetype>(g->bitmapWidth)
                * static_cast<qsizetype>(g->bitmapHeight);

            if (!g->bitmapPixels.isEmpty()
                && g->bitmapPixels.size() != expected) {
                g->bitmapPixels.clear();
                g->bitmapImagePath.clear();
            }
        }
    }

    QListWidget *addFlagList(
        const QString &label,
        const QString &currentExpression,
        QStringList choices,
        const std::function<void(const QString &)> &changed)
    {
        auto *list =
            new QListWidget(
                m_propertyHost);


        list->setSelectionMode(
            QAbstractItemView::NoSelection);

        const QStringList current =
            splitFlagExpression(
                currentExpression);

        /*
         * Preserve a hand-written/older flag even if it is not one of the
         * standard choices for this gadget type.
         */
        for (const QString &flag :
             current) {
            if (!choices.contains(flag)) {
                choices.append(flag);
            }
        }

        choices.removeDuplicates();

        for (const QString &flag :
             choices) {
            auto *item =
                new QListWidgetItem(
                    flag,
                    list);

            item->setFlags(
                item->flags()
                | Qt::ItemIsUserCheckable);

            item->setData(
                Qt::UserRole,
                flag);

            item->setCheckState(
                current.contains(flag)
                    ? Qt::Checked
                    : Qt::Unchecked);
        }

        list->setMinimumHeight(
            qMin(
                190,
                qMax(
                    58,
                    choices.size() * 22 + 6)));

        m_propertyLayout->addRow(
            label,
            list);

        connect(
            list,
            &QListWidget::itemChanged,
            this,
            [this,
             list,
             changed](QListWidgetItem *) {
                QStringList enabled;

                for (int i = 0;
                     i < list->count();
                     ++i) {
                    QListWidgetItem *item =
                        list->item(i);

                    if (item
                        && item->checkState()
                           == Qt::Checked) {
                        enabled.append(
                            item->data(
                                    Qt::UserRole)
                                .toString());
                    }
                }

                pushUndoSnapshot();

                changed(
                    enabled.isEmpty()
                        ? QStringLiteral("0")
                        : enabled.join(
                              QStringLiteral(
                                  " | ")));

                setModified(true);
                m_canvas->update();
            });

        return list;
    }

    QTableWidget *addGridCellTextTable(int selected)
    {
        if (selected < 0
            || selected >= m_gadgets.size()) {
            return nullptr;
        }

        GuiDesignerGadget &g =
            m_gadgets[selected];

        const int cols =
            qMax(1, g.cellsX);

        const int rows =
            qMax(1, g.cellsY);

        auto *table =
            new QTableWidget(
                rows,
                cols,
                m_propertyHost);

        table->setMinimumHeight(120);
        table->setMaximumHeight(210);
        table->setSelectionMode(
            QAbstractItemView::SingleSelection);
        table->setSelectionBehavior(
            QAbstractItemView::SelectItems);
        table->horizontalHeader()->setDefaultSectionSize(46);
        table->verticalHeader()->setDefaultSectionSize(24);
        table->horizontalHeader()->setMinimumSectionSize(34);
        table->verticalHeader()->setMinimumSectionSize(20);
        table->setToolTip(
            QObject::tr(
                "GridSelect cell text. Maximum 4 characters per cell."));

        for (int row = 0;
             row < rows;
             ++row) {
            for (int col = 0;
                 col < cols;
                 ++col) {
                const int cell =
                    row * cols + col;

                if (cell >= 256) {
                    auto *disabled =
                        new QTableWidgetItem(
                            QStringLiteral("—"));

                    disabled->setFlags(
                        disabled->flags()
                        & ~Qt::ItemIsEditable);

                    table->setItem(
                        row,
                        col,
                        disabled);
                    continue;
                }

                auto *item =
                    new QTableWidgetItem(
                        g.gridCellText
                            .value(cell)
                            .left(4));

                table->setItem(
                    row,
                    col,
                    item);
            }
        }

        m_propertyLayout->addRow(
            QObject::tr(
                "Cell text"),
            table);

        connect(
            table,
            &QTableWidget::cellChanged,
            this,
            [this,
             table,
             selected](int row, int col) {
                if (selected < 0
                    || selected >= m_gadgets.size()) {
                    return;
                }

                GuiDesignerGadget &g =
                    m_gadgets[selected];

                const int cell =
                    row * qMax(1, g.cellsX)
                    + col;

                if (cell < 0
                    || cell >= 256) {
                    return;
                }

                QTableWidgetItem *item =
                    table->item(row, col);

                if (!item) {
                    return;
                }

                QString value =
                    item->text()
                        .left(4);

                if (item->text() != value) {
                    const QSignalBlocker blocker(table);
                    item->setText(value);
                }

                pushUndoSnapshot();

                while (g.gridCellText.size()
                       <= cell) {
                    g.gridCellText.append(
                        QString());
                }

                g.gridCellText[cell] =
                    value;

                normaliseGridCellText(
                    &g);

                setModified(true);
                m_canvas->update();
            });

        return table;
    }

    QPlainTextEdit *addStringListEditor(
        const QString &label,
        const QStringList &items,
        const std::function<void(const QStringList &)> &changed)
    {
        auto *edit =
            new QPlainTextEdit(
                m_propertyHost);

        edit->setPlainText(
            items.join(
                QLatin1Char('\n')));

        edit->setMinimumHeight(100);
        edit->setMaximumHeight(150);

        edit->setToolTip(
            QObject::tr(
                "One value per line"));

        m_propertyLayout->addRow(
            label,
            edit);

        connect(
            edit,
            &QPlainTextEdit::textChanged,
            this,
            [this,
             edit,
             changed]() {
                QStringList values =
                    edit->toPlainText()
                        .split(
                            QLatin1Char('\n'),
                            Qt::KeepEmptyParts);

                while (!values.isEmpty()
                       && values.last().isEmpty()) {
                    values.removeLast();
                }

                pushUndoSnapshot();
                changed(values);
                setModified(true);
                m_canvas->update();
            });

        return edit;
    }

    void importBitmapPng(int index)
    {
        if (index < 0
            || index >= m_gadgets.size()
            || m_gadgets[index].type
               != QStringLiteral(
                   "BitmapView")) {
            return;
        }

        const QString path =
            QFileDialog::getOpenFileName(
                this,
                QObject::tr(
                    "Attach BitmapView PNG"),
                QFileInfo(m_filePath)
                    .absolutePath(),
                QObject::tr(
                    "PNG images (*.png)"));

        if (path.isEmpty()) {
            return;
        }

        QImage image(path);

        if (image.isNull()) {
            QMessageBox::warning(
                this,
                QObject::tr(
                    "BitmapView PNG"),
                QObject::tr(
                    "Could not load the selected PNG."));
            return;
        }

        const qsizetype pixelCount =
            static_cast<qsizetype>(image.width())
            * static_cast<qsizetype>(image.height());

        if (image.width() <= 0
            || image.height() <= 0
            || image.width() > 32767
            || image.height() > 32767
            || pixelCount > 4194304) {
            QMessageBox::warning(
                this,
                QObject::tr(
                    "BitmapView PNG"),
                QObject::tr(
                    "The PNG is too large for an embedded BitmapView image. "
                    "Maximum embedded size is 4,194,304 pixels."));
            return;
        }

        const QByteArray indexed =
            convertImageToCoderGirlIndices(
                image);

        if (indexed.size() != pixelCount) {
            QMessageBox::warning(
                this,
                QObject::tr(
                    "BitmapView PNG"),
                QObject::tr(
                    "The PNG could not be converted to the Sidbox CLUT."));
            return;
        }

        pushUndoSnapshot();

        GuiDesignerGadget &g =
            m_gadgets[index];

        g.bitmapWidth = image.width();
        g.bitmapHeight = image.height();
        g.bitmapPixels = indexed;
        g.bitmapImagePath =
            QFileInfo(path)
                .absoluteFilePath();

        g.bitmapSource =
            safeCIdentifier(
                g.name,
                QStringLiteral(
                    "bitmap"))
            + QStringLiteral(
                "_pixels");

        /* Embedded PNG bytes are always written row-major. */
        QStringList bitmapFlags =
            splitFlagExpression(
                g.typeFlags);

        bitmapFlags.removeAll(
            QStringLiteral(
                "BVF_SRC_XMAJOR"));

        if (!bitmapFlags.contains(
                QStringLiteral(
                    "BVF_SRC_ROWMAJOR"))) {
            bitmapFlags.append(
                QStringLiteral(
                    "BVF_SRC_ROWMAJOR"));
        }

        g.typeFlags =
            bitmapFlags.join(
                QStringLiteral(
                    " | "));

        setModified(true);
        m_canvas->update();
        rebuildProperties();

        if (m_statusLabel) {
            m_statusLabel->setText(
                QObject::tr(
                    "PNG converted: %1 x %2 -> %3 Sidbox 8-bit pixels")
                    .arg(g.bitmapWidth)
                    .arg(g.bitmapHeight)
                    .arg(g.bitmapPixels.size()));
        }
    }

    void restoreDefaultBitmap(int index)
    {
        if (index < 0
            || index >= m_gadgets.size()
            || m_gadgets[index].type
               != QStringLiteral(
                   "BitmapView")) {
            return;
        }

        pushUndoSnapshot();

        GuiDesignerGadget &g =
            m_gadgets[index];

        g.bitmapPixels.clear();
        g.bitmapImagePath.clear();
        g.bitmapSource =
            safeCIdentifier(
                g.name,
                QStringLiteral(
                    "bitmap"))
            + QStringLiteral(
                "_pixels");

        syncDesignerDemoBitmapSize(
            &g);

        setModified(true);
        m_canvas->update();
        rebuildProperties();

        if (m_statusLabel) {
            m_statusLabel->setText(
                QObject::tr(
                    "BitmapView restored to designer demo image"));
        }
    }

    void rebuildProperties()
    {
        clearPropertyRows();
        m_propertyLayout->addRow(new QLabel(QStringLiteral("<b>%1</b>")
            .arg(m_canvas->selectedIndex() < 0 ? QObject::tr("Window")
                 : (m_canvas->selectedIndex() < m_gadgets.size()
                    && (isVirtualDesignerGadget(m_gadgets[m_canvas->selectedIndex()].type)))
                       ? QObject::tr("Virtual Component") : QObject::tr("Gadget")), m_propertyHost));

        const int selected = m_canvas->selectedIndex();
        if (selected < 0 || selected >= m_gadgets.size()) {
            addLine(QObject::tr("C variable"), m_window.name, [this](const QString &v) {
                m_window.name = safeCIdentifier(v, QStringLiteral("MainWindow"));
            });
            addLine(QObject::tr("Title"), m_window.title, [this](const QString &v) { m_window.title = v; });
            addSpin(QObject::tr("X"), m_window.rect.x(), -2000, 2000, [this](int v) {
                m_window.rect.moveLeft(v);
                m_canvas->enforceWindowScreenBounds();
            });
            addSpin(QObject::tr("Y"), m_window.rect.y(), -2000, 2000, [this](int v) {
                m_window.rect.moveTop(v);
                m_canvas->enforceWindowScreenBounds();
            });
            addSpin(QObject::tr("Width"), m_window.rect.width(), 40, 2000, [this](int v) {
                m_window.rect.setWidth(v);
                m_canvas->enforceWindowScreenBounds();
            });
            addSpin(QObject::tr("Height"), m_window.rect.height(), 24, 2000, [this](int v) {
                m_window.rect.setHeight(v);
                m_canvas->enforceWindowScreenBounds();
            });
            addFlagList(
                QObject::tr("Window flags"),
                expandedWindowFlagExpression(m_window.flags),
                windowFlagChoices(),
                [this](const QString &v) {
                    m_window.flags =
                        v.trimmed().isEmpty()
                            ? QStringLiteral("0")
                            : v.trimmed();

                    m_canvas->enforceWindowScreenBounds();
                });

            addChoice(
                QObject::tr("Event routing"),
                {
                    {QObject::tr("WindowProc events"), 0},
                    {QObject::tr("Direct callbacks"), 1}
                },
                m_window.callbackMode,
                [this](int value) {
                    m_window.callbackMode = value;
                    rebuildProperties();
                });

            addPen(QObject::tr("Back Pen"), m_window.backPen, 0, [this](int v) { m_window.backPen = v; });
            return;
        }

        GuiDesignerGadget &g = m_gadgets[selected];
        addLine(QObject::tr("C variable"), g.name, [this, selected](const QString &v) {
            if (selected >= m_gadgets.size()) return;
            GuiDesignerGadget &gg = m_gadgets[selected];
            const QString old = gg.name;
            const QString oldDemoBitmap =
                safeCIdentifier(
                    old,
                    QStringLiteral("bitmap"))
                + QStringLiteral("_pixels");

            gg.name = safeCIdentifier(v, QStringLiteral("gadget"));
            if (gg.type == QStringLiteral("TabGroup") && gg.name != old) {
                for (GuiDesignerGadget &child : m_gadgets)
                    if (child.tabOwner == old) child.tabOwner = gg.name;
            }
            if ((gg.type == QStringLiteral("FileRequester") || gg.type == QStringLiteral("MessageBox"))
                && gg.name != old) {
                for (GuiDesignerGadget &child : m_gadgets)
                    if (child.dialogTarget == old) child.dialogTarget = gg.name;
            }
            if (gg.type == QStringLiteral("Media") && gg.name != old) {
                for (GuiDesignerGadget &child : m_gadgets)
                    if (child.mediaTarget == old) child.mediaTarget = gg.name;
            }

            if (gg.type == QStringLiteral("BitmapView")
                && gg.bitmapSource == oldDemoBitmap) {
                gg.bitmapSource =
                    safeCIdentifier(
                        gg.name,
                        QStringLiteral("bitmap"))
                    + QStringLiteral("_pixels");
            }

            if (gg.onActivate == QStringLiteral("On_%1_Activate").arg(old))
                gg.onActivate = QStringLiteral("On_%1_Activate").arg(gg.name);
            if (gg.type == QStringLiteral("FileRequester")) {
                if (gg.onActivate == QStringLiteral("On_%1_Selected").arg(old))
                    gg.onActivate = QStringLiteral("On_%1_Selected").arg(gg.name);
                if (gg.onChange == QStringLiteral("On_%1_Cancelled").arg(old))
                    gg.onChange = QStringLiteral("On_%1_Cancelled").arg(gg.name);
            }
            if (gg.type == QStringLiteral("MessageBox")
                && gg.onActivate == QStringLiteral("On_%1_Result").arg(old))
                gg.onActivate = QStringLiteral("On_%1_Result").arg(gg.name);
            if (gg.type == QStringLiteral("Messenger")
                && gg.onActivate == QStringLiteral("On_%1_Message").arg(old))
                gg.onActivate = QStringLiteral("On_%1_Message").arg(gg.name);
            if (gg.type == QStringLiteral("Timer")
                && gg.onActivate == QStringLiteral("On_%1_Tick").arg(old))
                gg.onActivate = QStringLiteral("On_%1_Tick").arg(gg.name);
            if (gg.type == QStringLiteral("KBInput")
                && gg.onActivate == QStringLiteral("On_%1_Key").arg(old))
                gg.onActivate = QStringLiteral("On_%1_Key").arg(gg.name);
            if (gg.type == QStringLiteral("MSInput")
                && gg.onActivate == QStringLiteral("On_%1_Mouse").arg(old))
                gg.onActivate = QStringLiteral("On_%1_Mouse").arg(gg.name);
            if (gg.onChange == QStringLiteral("On_%1_Change").arg(old))
                gg.onChange = QStringLiteral("On_%1_Change").arg(gg.name);
        });
        auto *type = new QLabel(g.type, m_propertyHost);
        m_propertyLayout->addRow(QObject::tr("Type"), type);
        if (g.type == QStringLiteral("FileRequester") || g.type == QStringLiteral("MessageBox")) {
            auto *hint = new QLabel(g.type == QStringLiteral("FileRequester")
                ? QObject::tr("Virtual non-modal file requester. Select/cancel events return to the owner window.")
                : QObject::tr("Virtual non-modal MessageBox / InfoBox. Results return to the owner window."), m_propertyHost);
            hint->setWordWrap(true);
            m_propertyLayout->addRow(hint);
            addSpin(QObject::tr("Icon X"), g.rect.x(), 0, 2000,
                [this, selected](int v) { m_gadgets[selected].rect.moveLeft(v); });
            addSpin(QObject::tr("Icon Y"), g.rect.y(), 0, 2000,
                [this, selected](int v) { m_gadgets[selected].rect.moveTop(v); });
            addLine(QObject::tr("Dialog title"), g.dialogTitle,
                [this, selected](const QString &v) { m_gadgets[selected].dialogTitle = v; });
            if (g.type == QStringLiteral("FileRequester")) {
                addLine(QObject::tr("Initial directory"), g.dialogDir,
                    [this, selected](const QString &v) { m_gadgets[selected].dialogDir = v; });
                addLine(QObject::tr("Filter (*.wav|*.mod)"), g.dialogFilter,
                    [this, selected](const QString &v) { m_gadgets[selected].dialogFilter = v; });
                addLine(QObject::tr("On file selected (const char *path)"), g.onActivate,
                    [this, selected](const QString &v) { m_gadgets[selected].onActivate = safeCIdentifier(v, QStringLiteral("OnFileSelected")); });
                addLine(QObject::tr("On cancelled (void)"), g.onChange,
                    [this, selected](const QString &v) { m_gadgets[selected].onChange = safeCIdentifier(v, QStringLiteral("OnFileCancelled")); });
            } else {
                addStringChoice(QObject::tr("Dialog kind"),
                    {QStringLiteral("Message"), QStringLiteral("Info")}, g.dialogKind,
                    [this, selected](const QString &v) {
                        m_gadgets[selected].dialogKind = v;
                        QTimer::singleShot(0, this, [this]() { rebuildProperties(); });
                    });
                addLine(QObject::tr("Message"), g.dialogMessage,
                    [this, selected](const QString &v) { m_gadgets[selected].dialogMessage = v; });
                if (g.dialogKind == QStringLiteral("Message")) {
                    addStringChoice(QObject::tr("Buttons"),
                        {QStringLiteral("OK"), QStringLiteral("OK/Cancel"),
                         QStringLiteral("Yes/No"), QStringLiteral("Yes/No/Cancel")}, g.dialogButtons,
                        [this, selected](const QString &v) { m_gadgets[selected].dialogButtons = v; });
                }
                addLine(QObject::tr("On result (int32_t result)"), g.onActivate,
                    [this, selected](const QString &v) { m_gadgets[selected].onActivate = safeCIdentifier(v, QStringLiteral("OnMessageResult")); });
            }
            addCheck(QObject::tr("Block owner interactions"), g.dialogBlockOwner,
                [this, selected](bool v) { m_gadgets[selected].dialogBlockOwner = v; });
            return;
        }
        if (g.type == QStringLiteral("Media")) {
            auto *hint = new QLabel(QObject::tr(
                "Virtual Media: appears only in the designer. "
                "Playback uses the SIDBOX audio API; sound effects occupy a BETH PCM channel."),
                m_propertyHost);
            hint->setWordWrap(true);
            m_propertyLayout->addRow(hint);
            addSpin(QObject::tr("Icon X"), g.rect.x(), 0, 2000,
                [this, selected](int v) { m_gadgets[selected].rect.moveLeft(v); });
            addSpin(QObject::tr("Icon Y"), g.rect.y(), 0, 2000,
                [this, selected](int v) { m_gadgets[selected].rect.moveTop(v); });
            addStringChoice(QObject::tr("Media mode"),
                {QStringLiteral("SFX"), QStringLiteral("Music")}, g.mediaMode,
                [this, selected](const QString &v) {
                    m_gadgets[selected].mediaMode = v;
                    QTimer::singleShot(0, this, [this]() { rebuildProperties(); });
                });
            if (g.mediaMode == QStringLiteral("SFX")) {
                addCheck(QObject::tr("Embed WAV in applet"), g.mediaEmbedSfx,
                    [this, selected](bool v) {
                        m_gadgets[selected].mediaEmbedSfx = v;
                        QTimer::singleShot(0, this, [this]() { rebuildProperties(); });
                    });
                if (g.mediaEmbedSfx) {
                    auto *source = new QLineEdit(m_propertyHost);
                    source->setReadOnly(true);
                    source->setText(g.mediaEmbeddedPcm.isEmpty()
                        ? QObject::tr("No WAV imported")
                        : QObject::tr("%1 (%2 PCM bytes)")
                              .arg(g.mediaEmbeddedName)
                              .arg(qlonglong(g.mediaEmbeddedPcm.size())));
                    m_propertyLayout->addRow(QObject::tr("Embedded sample"), source);
                    auto *import = new QPushButton(QObject::tr("Import 8-bit WAV..."), m_propertyHost);
                    m_propertyLayout->addRow(import);
                    connect(import, &QPushButton::clicked, this, [this, selected]() {
                        if (selected < 0 || selected >= m_gadgets.size()) return;
                        const QString fileName = QFileDialog::getOpenFileName(this,
                            QObject::tr("Embed PCM WAV"), QString(),
                            QObject::tr("WAV files (*.wav);;All files (*)"));
                        if (fileName.isEmpty()) return;
                        QFile wav(fileName);
                        if (!wav.open(QIODevice::ReadOnly)) {
                            QMessageBox::warning(this, QObject::tr("Media"),
                                QObject::tr("Could not open %1").arg(fileName));
                            return;
                        }
                        const QByteArray bytes = wav.readAll();
                        auto u16 = [&bytes](qsizetype pos) -> quint32 {
                            const auto *d = reinterpret_cast<const uchar *>(bytes.constData());
                            return quint32(d[pos]) | (quint32(d[pos + 1]) << 8);
                        };
                        auto u32 = [&bytes](qsizetype pos) -> quint32 {
                            const auto *d = reinterpret_cast<const uchar *>(bytes.constData());
                            return quint32(d[pos]) | (quint32(d[pos + 1]) << 8)
                                | (quint32(d[pos + 2]) << 16) | (quint32(d[pos + 3]) << 24);
                        };
                        bool valid = bytes.size() >= 44 && bytes.mid(0, 4) == "RIFF"
                            && bytes.mid(8, 4) == "WAVE";
                        bool fmtFound = false;
                        bool dataFound = false;
                        quint32 sampleRate = 0;
                        QByteArray pcm;
                        if (valid) {
                            qsizetype pos = 12;
                            while (pos + 8 <= bytes.size()) {
                                const quint32 chunkLength = u32(pos + 4);
                                const qsizetype content = pos + 8;
                                if (chunkLength > quint64(bytes.size() - content)) {
                                    valid = false;
                                    break;
                                }
                                const QByteArray kind = bytes.mid(pos, 4);
                                if (kind == "fmt " && chunkLength >= 16) {
                                    fmtFound = u16(content) == 1 && u16(content + 2) == 1
                                        && u16(content + 14) == 8;
                                    sampleRate = u32(content + 4);
                                } else if (kind == "data") {
                                    pcm = bytes.mid(content, chunkLength);
                                    dataFound = true;
                                }
                                pos = content + qsizetype(chunkLength) + qsizetype(chunkLength & 1u);
                            }
                        }
                        if (!valid || !fmtFound || !dataFound || pcm.isEmpty() || sampleRate == 0
                            || sampleRate > 65535) {
                            QMessageBox::warning(this, QObject::tr("Unsupported WAV"),
                                QObject::tr("Select a mono, uncompressed 8-bit PCM WAV (sample rate 1..65535 Hz)."));
                            return;
                        }
                        // Preserve the existing .sbui byte encoding (PCM8 XOR 0x80).
                        // When generating media_sfx.c, reverse it for BETH's unsigned PCM8 mixer.
                        for (qsizetype i = 0; i < pcm.size(); ++i)
                            pcm[i] = char(uchar(pcm.at(i)) ^ 0x80u);
                        pushUndoSnapshot();
                        auto &media = m_gadgets[selected];
                        media.mediaEmbeddedPcm = pcm;
                        media.mediaEmbeddedName = QFileInfo(fileName).fileName();
                        media.mediaFrequency = int(sampleRate);
                        setModified(true);
                        rebuildProperties();
                    });
                    auto *info = new QLabel(QObject::tr(
                        "Compiled as unsigned PCM8 in a separate generated media_sfx.c file. "
                        "This increases the applet image size; keep samples short."), m_propertyHost);
                    info->setWordWrap(true);
                    m_propertyLayout->addRow(info);
                } else {
                    addLine(QObject::tr("SIDBOX WAV path"), g.mediaFile,
                        [this, selected](const QString &v) {
                            m_gadgets[selected].mediaFile = v.trimmed();
                        });
                }
                addSpin(QObject::tr("PCM channel (0–7)"), g.mediaChannel, 0, 7,
                    [this, selected](int v) { m_gadgets[selected].mediaChannel = v; });
                addSpin(QObject::tr("Frequency (Hz)"), g.mediaFrequency, 1, 65535,
                    [this, selected](int v) { m_gadgets[selected].mediaFrequency = v; });
                addSpin(QObject::tr("Volume (0–255)"), g.mediaVolume, 0, 255,
                    [this, selected](int v) { m_gadgets[selected].mediaVolume = v; });
                addSpin(QObject::tr("Pan (-127..127)"), g.mediaPan, -127, 127,
                    [this, selected](int v) { m_gadgets[selected].mediaPan = v; });
                addCheck(QObject::tr("Loop sound"), g.mediaLoop,
                    [this, selected](bool v) { m_gadgets[selected].mediaLoop = v; });
                auto *sfxHint = new QLabel(QObject::tr(
                    "SFX: use mono 8-bit PCM WAV. BETH mixes unsigned PCM8 "
                    "(128 = silence), so generated playback preserves WAV sample bytes. "
                    "LoadSFX requires a simple WAV header."), m_propertyHost);
                sfxHint->setWordWrap(true);
                m_propertyLayout->addRow(sfxHint);
            } else {
                addLine(QObject::tr("SIDBOX music path"), g.mediaFile,
                    [this, selected](const QString &v) {
                        m_gadgets[selected].mediaFile = v.trimmed();
                    });
                addSpin(QObject::tr("Subsong"), g.mediaSubsong, 0, 255,
                    [this, selected](int v) { m_gadgets[selected].mediaSubsong = v; });
                auto *musicHint = new QLabel(QObject::tr(
                    "Music playback uses music_play/music_stop. Your applet loop "
                    "must call music_update() often enough for the music engine."), m_propertyHost);
                musicHint->setWordWrap(true);
                m_propertyLayout->addRow(musicHint);
            }
            addCheck(QObject::tr("Start with window"), g.mediaAutoStart,
                [this, selected](bool v) { m_gadgets[selected].mediaAutoStart = v; });
            return;
        }
        if (g.type == QStringLiteral("KBInput") || g.type == QStringLiteral("MSInput")) {
            const bool keyboard = g.type == QStringLiteral("KBInput");
            auto *hint = new QLabel(keyboard
                ? QObject::tr("Passive window keyboard listener. Receives key press/release only while this window has focus. Keys still reach normal OS gadgets; no ownership or IRQ changes.")
                : QObject::tr("Passive window mouse listener. Receives move/press/release over this window, with screen coordinates and button flags. Menus and other OS controls still work normally."),
                m_propertyHost);
            hint->setWordWrap(true);
            m_propertyLayout->addRow(hint);
            addSpin(QObject::tr("Icon X"), g.rect.x(), 0, 2000,
                [this, selected](int v) { m_gadgets[selected].rect.moveLeft(v); });
            addSpin(QObject::tr("Icon Y"), g.rect.y(), 0, 2000,
                [this, selected](int v) { m_gadgets[selected].rect.moveTop(v); });
            addLine(keyboard ? QObject::tr("On key event (event, key, mods, hid)")
                             : QObject::tr("On mouse event (event, x, y, flags)"), g.onActivate,
                [this, selected](const QString &v) {
                    m_gadgets[selected].onActivate = v.trimmed().isEmpty()
                        ? QString() : safeCIdentifier(v, QStringLiteral("OnInput"));
                });
            return;
        }
        if (g.type == QStringLiteral("UART1")) {
            auto *hint = new QLabel(QObject::tr(
                "Exclusive UART1 (PA9/PA10). Borrowing it suspends the terminal, FTP, "
                "debug output and UART keyboard until uart1_Close() or applet termination. "
                "The default is manual open. The data callback is cooperative (not an IRQ)."),
                m_propertyHost);
            hint->setWordWrap(true);
            m_propertyLayout->addRow(hint);
            addSpin(QObject::tr("Icon X"), g.rect.x(), 0, 2000,
                [this, selected](int v) { m_gadgets[selected].rect.moveLeft(v); });
            addSpin(QObject::tr("Icon Y"), g.rect.y(), 0, 2000,
                [this, selected](int v) { m_gadgets[selected].rect.moveTop(v); });
            addSpin(QObject::tr("Baud rate"), g.uart1Baud, 1200, 1000000,
                [this, selected](int v) { m_gadgets[selected].uart1Baud = v; });
            addSpin(QObject::tr("Data bits (7 or 8)"), g.uart1DataBits, 7, 8,
                [this, selected](int v) { m_gadgets[selected].uart1DataBits = v; });
            addSpin(QObject::tr("Parity: 0=None 1=Even 2=Odd"), g.uart1Parity, 0, 2,
                [this, selected](int v) { m_gadgets[selected].uart1Parity = v; });
            addSpin(QObject::tr("Stop bits (1 or 2)"), g.uart1StopBits, 1, 2,
                [this, selected](int v) { m_gadgets[selected].uart1StopBits = v; });
            addSpin(QObject::tr("Receive poll (ms)"), g.uart1PollMs, 10, 1000,
                [this, selected](int v) { m_gadgets[selected].uart1PollMs = v; });
            addCheck(QObject::tr("Open when window is created"), g.uart1AutoOpen,
                [this, selected](bool v) { m_gadgets[selected].uart1AutoOpen = v; });
            addLine(QObject::tr("On data available (void *user)"), g.onActivate,
                [this, selected](const QString &v) {
                    m_gadgets[selected].onActivate = v.trimmed().isEmpty()
                        ? QString() : safeCIdentifier(v, QStringLiteral("OnUart1Data"));
                });
            return;
        }
        if (g.type == QStringLiteral("Messenger")) {
            auto *hint = new QLabel(QObject::tr(
                "Virtual V2 IPC: receive messages and/or send to an applet. "
                "Set Target applet to a unique filename (for example ipc_rx.app). "
                "On a Button choose this Messenger as its IPC target; the button "
                "will send its configured text automatically. Receiver uses "
                "a cooperative timer; no foreign callback stack."), m_propertyHost);
            hint->setWordWrap(true);
            m_propertyLayout->addRow(hint);
            addSpin(QObject::tr("Icon X"), g.rect.x(), 0, 2000,
                [this, selected](int v) { m_gadgets[selected].rect.moveLeft(v); });
            addSpin(QObject::tr("Icon Y"), g.rect.y(), 0, 2000,
                [this, selected](int v) { m_gadgets[selected].rect.moveTop(v); });
            addLine(QObject::tr("Target applet filename (to send)"), g.ipcTargetApp,
                [this, selected](const QString &v) {
                    m_gadgets[selected].ipcTargetApp = v.trimmed();
                });
            addCheck(QObject::tr("Enable receiving"), g.ipcReceive,
                [this, selected](bool v) {
                    m_gadgets[selected].ipcReceive = v;
                    QTimer::singleShot(0, this, [this]() { rebuildProperties(); });
                });
            if (g.ipcReceive) {
                addSpin(QObject::tr("Receive poll (ms)"), g.ipcPollMs, 10, 1000,
                    [this, selected](int v) { m_gadgets[selected].ipcPollMs = v; });
                addLine(QObject::tr("On message (const SIDBOX_IPC_MESSAGE *message)"), g.onActivate,
                    [this, selected](const QString &v) {
                        m_gadgets[selected].onActivate = v.trimmed().isEmpty()
                            ? QString() : safeCIdentifier(v, QStringLiteral("OnMessengerMessage"));
                    });
            }
            return;
        }
        if (g.type == QStringLiteral("Timer")) {
            auto *hint = new QLabel(QObject::tr(
                "Virtual stopwatch: visible only in the designer. "
                "Uses CoderGirl cooperative timers, not a hardware IRQ."),
                m_propertyHost);
            hint->setWordWrap(true);
            m_propertyLayout->addRow(hint);
            addSpin(QObject::tr("Icon X"), g.rect.x(), 0, 2000,
                [this, selected](int v) { m_gadgets[selected].rect.moveLeft(v); });
            addSpin(QObject::tr("Icon Y"), g.rect.y(), 0, 2000,
                [this, selected](int v) { m_gadgets[selected].rect.moveTop(v); });
            addSpin(QObject::tr("Initial delay (ms)"), g.timerDelayMs, 1, 86400000,
                [this, selected](int v) { m_gadgets[selected].timerDelayMs = v; });
            addSpin(QObject::tr("Repeat period (ms)"), g.timerPeriodMs, 1, 86400000,
                [this, selected](int v) { m_gadgets[selected].timerPeriodMs = v; });
            addCheck(QObject::tr("Repeat"), g.timerRepeat,
                [this, selected](bool v) { m_gadgets[selected].timerRepeat = v; });
            addCheck(QObject::tr("Start with window"), g.timerAutoStart,
                [this, selected](bool v) { m_gadgets[selected].timerAutoStart = v; });
            addCheck(QObject::tr("Keep running after window closes"), g.timerKeepAliveOnClose,
                [this, selected](bool v) { m_gadgets[selected].timerKeepAliveOnClose = v; });
            addLine(QObject::tr("On tick"), g.onActivate,
                [this, selected](const QString &v) {
                    m_gadgets[selected].onActivate = v.trimmed().isEmpty()
                        ? QString() : safeCIdentifier(v, QStringLiteral("OnTimerTick"));
                });
            return;
        }
        auto *layerButtons = new QWidget(m_propertyHost);
        auto *layerLayout = new QHBoxLayout(layerButtons);
        layerLayout->setContentsMargins(0, 0, 0, 0);
        auto *toFront = new QPushButton(QObject::tr("Bring to Front"), layerButtons);
        auto *toBack = new QPushButton(QObject::tr("Send to Back"), layerButtons);
        toFront->setToolTip(QObject::tr("Put this gadget in front of others of the same layer."));
        toBack->setToolTip(QObject::tr("Put this gadget behind others of the same layer."));
        layerLayout->addWidget(toFront);
        layerLayout->addWidget(toBack);
        m_propertyLayout->addRow(QObject::tr("Order"), layerButtons);
        // Rebuilding properties deletes these buttons: defer until the click
        // signal completes, just like the existing dropdown controls.
        connect(toFront, &QPushButton::clicked, this,
                [this]() { QTimer::singleShot(0, this,
                    [this]() { changeSelectedGadgetLayer(true); }); });
        connect(toBack, &QPushButton::clicked, this,
                [this]() { QTimer::singleShot(0, this,
                    [this]() { changeSelectedGadgetLayer(false); }); });
        if (g.type == QStringLiteral("TabGroup")) {
            addLine(QObject::tr("Tabs (| separated)"), g.text, [this, selected](const QString &value) {
                m_gadgets[selected].text = value;
                const int lastPage = designerTabTitles(m_gadgets[selected]).size() - 1;
                m_gadgets[selected].value = qBound(0, m_gadgets[selected].value, lastPage);
                m_gadgets[selected].defaultTabPage = qBound(
                    0, m_gadgets[selected].defaultTabPage, lastPage);
                QTimer::singleShot(0, this, [this]() { rebuildProperties(); });
            });
            auto *preview = new QComboBox(m_propertyHost);
            const QStringList pages = designerTabTitles(g);
            for (int i=0;i<pages.size();++i) preview->addItem(pages[i], i);
            preview->setCurrentIndex(qBound(0, g.value, pages.size()-1));
            m_propertyLayout->addRow(QObject::tr("Preview page"), preview);
            connect(preview, qOverload<int>(&QComboBox::currentIndexChanged), this,
                    [this, selected](int index) {
                if (selected < 0 || selected >= m_gadgets.size() || index < 0) return;
                m_gadgets[selected].value = index; // preview-only
                m_canvas->update();
            });

            // Unlike Preview page, this is saved to the .sbui and determines
            // the visible gadget group when the real SIDBOX window is created.
            auto *defaultPage = new QComboBox(m_propertyHost);
            for (int i = 0; i < pages.size(); ++i)
                defaultPage->addItem(pages.at(i), i);
            defaultPage->setCurrentIndex(qBound(0, g.defaultTabPage, pages.size()-1));
            defaultPage->setToolTip(QObject::tr(
                "The tab shown initially when this window opens on SIDBOX. "
                "Changing Preview page alone does not change this setting."));
            m_propertyLayout->addRow(QObject::tr("Default selected tab"), defaultPage);
            connect(defaultPage, qOverload<int>(&QComboBox::currentIndexChanged), this,
                    [this, selected, preview](int index) {
                if (selected < 0 || selected >= m_gadgets.size() || index < 0
                    || m_gadgets[selected].defaultTabPage == index) return;
                pushUndoSnapshot();
                m_gadgets[selected].defaultTabPage = index;
                m_gadgets[selected].value = index; // preview the new default
                setModified(true);
                // Keep the preview combobox in sync without treating its
                // change as an independent design edit.
                const QSignalBlocker block(preview);
                preview->setCurrentIndex(index);
                m_canvas->update();
            });

            addPen(QObject::tr("Bevel BPen"), g.bPen, -1, [this, selected](int pen) {
                m_gadgets[selected].bPen = pen;
            });
            addPen(QObject::tr("Bevel FPen"), g.fPen, -1, [this, selected](int pen) {
                m_gadgets[selected].fPen = pen;
            });
            addChoice(QObject::tr("Bevel direction"),
                      {{QObject::tr("Inset (GAD_TOOL_INSET)"), 1},
                       {QObject::tr("Outset (default)"), 0}},
                      g.flags.contains(QStringLiteral("GAD_TOOL_INSET")) ? 1 : 0,
                      [this, selected](int direction) {
                QStringList flags = splitFlagExpression(m_gadgets[selected].flags);
                flags.removeAll(QStringLiteral("GAD_TOOL_INSET"));
                flags.removeAll(QStringLiteral("GAD_TOOL_DEFAULT"));
                if (direction == 1) flags.prepend(QStringLiteral("GAD_TOOL_INSET"));
                if (flags.isEmpty()) flags.append(QStringLiteral("GAD_TOOL_DEFAULT"));
                m_gadgets[selected].flags = flags.join(QStringLiteral(" | "));
            });
        } else {
            auto *owner = new QComboBox(m_propertyHost);
            owner->addItem(QObject::tr("Always visible"), QString());
            for (const GuiDesignerGadget &candidate : std::as_const(m_gadgets)) {
                if (candidate.type == QStringLiteral("TabGroup"))
                    owner->addItem(candidate.name, candidate.name);
            }
            const int existing = owner->findData(g.tabOwner);
            owner->setCurrentIndex(qMax(0, existing));
            m_propertyLayout->addRow(QObject::tr("Tab group"), owner);
            connect(owner, qOverload<int>(&QComboBox::currentIndexChanged), this,
                    [this, selected, owner](int) {
                if (selected >= m_gadgets.size()) return;
                const QString next=owner->currentData().toString();
                if (m_gadgets[selected].tabOwner == next) return;
                pushUndoSnapshot();
                m_gadgets[selected].tabOwner = next;
                m_gadgets[selected].tabPage = 0;
                setModified(true);
                QTimer::singleShot(0, this, [this]() { rebuildProperties(); m_canvas->update(); });
            });
            if (!g.tabOwner.isEmpty()) {
                for (const GuiDesignerGadget &tabs : std::as_const(m_gadgets)) {
                    if (tabs.type != QStringLiteral("TabGroup") || tabs.name != g.tabOwner) continue;
                    auto *page = new QComboBox(m_propertyHost);
                    const QStringList titles = designerTabTitles(tabs);
                    for (int i=0;i<titles.size();++i) page->addItem(titles[i], i);
                    page->setCurrentIndex(qBound(0, g.tabPage, titles.size()-1));
                    m_propertyLayout->addRow(QObject::tr("Tab page"), page);
                    connect(page, qOverload<int>(&QComboBox::currentIndexChanged), this,
                            [this, selected](int index) {
                        if (selected >= m_gadgets.size() || index < 0
                            || m_gadgets[selected].tabPage == index) return;
                        pushUndoSnapshot();
                        m_gadgets[selected].tabPage = index;
                        setModified(true);
                        m_canvas->update();
                    });
                    break;
                }
            }
        }
        if (g.type == QStringLiteral("Button")) {
            auto *dialogTarget = new QComboBox(m_propertyHost);
            dialogTarget->addItem(QObject::tr("None — ordinary callback"), QString());
            for (const GuiDesignerGadget &candidate : std::as_const(m_gadgets)) {
                if (candidate.type == QStringLiteral("FileRequester") || candidate.type == QStringLiteral("MessageBox"))
                    dialogTarget->addItem(candidate.name, candidate.name);
            }
            dialogTarget->setCurrentIndex(qMax(0, dialogTarget->findData(g.dialogTarget)));
            m_propertyLayout->addRow(QObject::tr("Dialog target"), dialogTarget);
            connect(dialogTarget, qOverload<int>(&QComboBox::currentIndexChanged), this,
                    [this, selected, dialogTarget](int) {
                const QString next = dialogTarget->currentData().toString();
                if (selected >= m_gadgets.size() || m_gadgets[selected].dialogTarget == next) return;
                pushUndoSnapshot();
                GuiDesignerGadget &button = m_gadgets[selected];
                button.dialogTarget = next;
                if (!next.isEmpty() && button.onActivate.isEmpty())
                    button.onActivate = QStringLiteral("On_%1_Activate").arg(button.name);
                setModified(true);
                QTimer::singleShot(0, this, [this]() { rebuildProperties(); });
            });
            auto *mediaTarget = new QComboBox(m_propertyHost);
            mediaTarget->addItem(QObject::tr("None — ordinary callback"), QString());
            for (const GuiDesignerGadget &candidate : std::as_const(m_gadgets)) {
                if (candidate.type == QStringLiteral("Media"))
                    mediaTarget->addItem(candidate.name, candidate.name);
            }
            mediaTarget->setCurrentIndex(qMax(0, mediaTarget->findData(g.mediaTarget)));
            m_propertyLayout->addRow(QObject::tr("Media target"), mediaTarget);
            connect(mediaTarget, qOverload<int>(&QComboBox::currentIndexChanged), this,
                    [this, selected, mediaTarget](int) {
                const QString next = mediaTarget->currentData().toString();
                if (selected >= m_gadgets.size() || m_gadgets[selected].mediaTarget == next) return;
                pushUndoSnapshot();
                GuiDesignerGadget &button = m_gadgets[selected];
                button.mediaTarget = next;
                if (!next.isEmpty() && button.onActivate.isEmpty())
                    button.onActivate = QStringLiteral("On_%1_Activate").arg(button.name);
                setModified(true);
                QTimer::singleShot(0, this, [this]() { rebuildProperties(); });
            });
            if (!g.mediaTarget.isEmpty()) {
                addStringChoice(QObject::tr("Media action"),
                    {QStringLiteral("Play"), QStringLiteral("Stop")}, g.mediaAction,
                    [this, selected](const QString &v) { m_gadgets[selected].mediaAction = v; });
            }
            auto *ipcTarget = new QComboBox(m_propertyHost);
            ipcTarget->addItem(QObject::tr("None — no IPC action"), QString());
            for (const GuiDesignerGadget &candidate : std::as_const(m_gadgets)) {
                if (candidate.type == QStringLiteral("Messenger"))
                    ipcTarget->addItem(candidate.name, candidate.name);
            }
            ipcTarget->setCurrentIndex(qMax(0, ipcTarget->findData(g.ipcSendTarget)));
            m_propertyLayout->addRow(QObject::tr("IPC Messenger"), ipcTarget);
            connect(ipcTarget, qOverload<int>(&QComboBox::currentIndexChanged), this,
                    [this, selected, ipcTarget](int) {
                const QString next = ipcTarget->currentData().toString();
                if (selected >= m_gadgets.size() || m_gadgets[selected].ipcSendTarget == next) return;
                pushUndoSnapshot();
                GuiDesignerGadget &button = m_gadgets[selected];
                button.ipcSendTarget = next;
                if (!next.isEmpty() && button.onActivate.isEmpty())
                    button.onActivate = QStringLiteral("On_%1_Activate").arg(button.name);
                setModified(true);
                QTimer::singleShot(0, this, [this]() { rebuildProperties(); });
            });
            if (!g.ipcSendTarget.isEmpty()) {
                addSpin(QObject::tr("IPC message type"), g.ipcSendType, 0, 65535,
                    [this, selected](int v) { m_gadgets[selected].ipcSendType = v; });
                addLine(QObject::tr("IPC message text (max 64 UTF-8 bytes)"), g.ipcSendText,
                    [this, selected](const QString &v) { m_gadgets[selected].ipcSendText = v; });
            }
            auto *target = new QComboBox(m_propertyHost);
            target->addItem(QObject::tr("None — ordinary callback"), QString());
            target->setToolTip(QObject::tr("Choose another SBUI window to open when this button is activated."));
            const QDir root(designProjectRoot());
            const QString own = QFileInfo(m_filePath).absoluteFilePath();
            QDirIterator designs(root.absolutePath(), {QStringLiteral("*.sbui")},
                                 QDir::Files, QDirIterator::Subdirectories);
            QStringList paths;
            while (designs.hasNext()) {
                const QString path = QFileInfo(designs.next()).absoluteFilePath();
                if (path != own) paths.append(root.relativeFilePath(path));
            }
            paths.sort(Qt::CaseInsensitive);
            for (const QString &path : std::as_const(paths)) {
                QFile file(root.absoluteFilePath(path));
                QString windowName;
                if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                    const QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
                    windowName = doc.object().value(QStringLiteral("window"))
                                    .toObject().value(QStringLiteral("name")).toString();
                }
                if (!windowName.isEmpty()) {
                    target->addItem(QStringLiteral("%1  (%2)").arg(windowName, path), path);
                    const QString entry = windowEntryForDesign(root.absoluteFilePath(path));
                    target->setItemData(target->count() - 1,
                                        entry.isEmpty() ? QObject::tr("Invalid window entry marker")
                                                        : QObject::tr("Calls %1() ").arg(entry),
                                        Qt::ToolTipRole);
                }
            }
            int selectedTarget = target->findData(g.openWindowFile);
            if (selectedTarget < 0 && !g.openWindowFile.isEmpty()) {
                target->addItem(QObject::tr("Missing: %1").arg(g.openWindowFile), g.openWindowFile);
                selectedTarget = target->count() - 1;
            }
            target->setCurrentIndex(qMax(0, selectedTarget));
            m_propertyLayout->addRow(QObject::tr("Open window"), target);
            connect(target, qOverload<int>(&QComboBox::currentIndexChanged), this,
                    [this, selected, target](int) {
                if (selected < 0 || selected >= m_gadgets.size()) return;
                const QString next = target->currentData().toString();
                if (next == m_gadgets[selected].openWindowFile) return;
                pushUndoSnapshot();
                GuiDesignerGadget &button = m_gadgets[selected];
                button.openWindowFile = next;
                if (!next.isEmpty() && button.onActivate.trimmed().isEmpty())
                    button.onActivate = QStringLiteral("On_%1_Activate").arg(button.name);
                setModified(true);
                // removeRow() deletes property widgets; never destroy the
                // combo box while it is still delivering its own signal.
                QTimer::singleShot(0, this, [this]() { rebuildProperties(); });
            });
        }

        const QRect tabMoveBounds = g.type == QStringLiteral("TabGroup")
            ? m_canvas->tabGroupPositionBounds(selected) : QRect();
        addSpin(QObject::tr("X"), g.rect.x(),
                g.type == QStringLiteral("TabGroup") ? tabMoveBounds.left() : 0,
                g.type == QStringLiteral("TabGroup") ? tabMoveBounds.right() : 2000,
                [this, selected](int v) {
            if (selected < 0 || selected >= m_gadgets.size()) return;
            if (m_gadgets[selected].type == QStringLiteral("TabGroup"))
                m_canvas->moveTabGroupWithMembers(selected,
                    QPoint(v, m_gadgets[selected].rect.y()));
            else
                m_gadgets[selected].rect.moveLeft(v);
        });
        addSpin(QObject::tr("Y"), g.rect.y(),
                g.type == QStringLiteral("TabGroup") ? tabMoveBounds.top() : 0,
                g.type == QStringLiteral("TabGroup") ? tabMoveBounds.bottom() : 2000,
                [this, selected](int v) {
            if (selected < 0 || selected >= m_gadgets.size()) return;
            if (m_gadgets[selected].type == QStringLiteral("TabGroup"))
                m_canvas->moveTabGroupWithMembers(selected,
                    QPoint(m_gadgets[selected].rect.x(), v));
            else
                m_gadgets[selected].rect.moveTop(v);
        });

        if (g.type
            == QStringLiteral(
                "GridSelect")) {
            auto *derivedSize =
                new QLabel(
                    QObject::tr(
                        "%1 × %2 (derived)")
                        .arg(
                            g.rect.width())
                        .arg(
                            g.rect.height()),
                    m_propertyHost);

            m_propertyLayout->addRow(
                QObject::tr("Size"),
                derivedSize);
        } else {
            addSpin(QObject::tr("Width"), g.rect.width(), 4, 2000, [this, selected](int v) {
                m_gadgets[selected].rect.setWidth(v);
                syncDesignerDemoBitmapSize(
                    &m_gadgets[selected]);
            });

            addSpin(QObject::tr("Height"), g.rect.height(), 4, 2000, [this, selected](int v) {
                m_gadgets[selected].rect.setHeight(v);
                syncDesignerDemoBitmapSize(
                    &m_gadgets[selected]);
            });
        }

        if (g.type == QStringLiteral("Button") || g.type == QStringLiteral("Label")
            || g.type == QStringLiteral("Checkbox") || g.type == QStringLiteral("Radio")
            || g.type == QStringLiteral("TextBox") || g.type == QStringLiteral("TextArea")) {
            m_textPropertyEdit = addLine(
                QObject::tr("Text"), g.text,
                [this, selected](const QString &v) {
                    m_inlineTextEditing = false;
                    m_inlineReplaceOnFirstKey = true;
                    m_gadgets[selected].text = v;
                });
        }

        addCheck(
            QObject::tr("Enabled"),
            g.enabled,
            [this, selected](bool enabled) {
                if (selected >= 0
                    && selected < m_gadgets.size()) {
                    m_gadgets[selected].enabled =
                        enabled;
                }
            });

        if (g.type != QStringLiteral("TabGroup")) {
            addFlagList(
                QObject::tr("Gadget flags"),
                g.flags,
                gadgetFlagChoices(g.type),
                [this, selected](const QString &v) {
                    if (selected >= 0
                        && selected < m_gadgets.size()) {
                        m_gadgets[selected].flags = v;
                        syncGridSelectGeometry(&m_gadgets[selected]);
                        syncDesignerDemoBitmapSize(&m_gadgets[selected]);
                    }
                });
            addPen(QObject::tr("BPen"), g.bPen, -1, [this, selected](int v) { m_gadgets[selected].bPen = v; });
            addPen(QObject::tr("FPen"), g.fPen, -1, [this, selected](int v) { m_gadgets[selected].fPen = v; });
            addPen(QObject::tr("HPen"), g.hPen, -1, [this, selected](int v) { m_gadgets[selected].hPen = v; });
        }

        addChoice(
            QObject::tr("Callback routing"),
            {
                {QObject::tr("Follow Window"), -1},
                {QObject::tr("WindowProc event"), 0},
                {QObject::tr("Own direct callback"), 1}
            },
            g.callbackRoute,
            [this, selected](int value) {
                if (selected >= 0
                    && selected < m_gadgets.size()) {
                    m_gadgets[selected].callbackRoute = value;
                }
            });

        addLine(QObject::tr("On activate"), g.onActivate, [this, selected](const QString &v) {
            m_gadgets[selected].onActivate = v.trimmed().isEmpty() ? QString() : safeCIdentifier(v, QStringLiteral("OnActivate"));
        });
        addLine(QObject::tr("On change"), g.onChange, [this, selected](const QString &v) {
            m_gadgets[selected].onChange = v.trimmed().isEmpty() ? QString() : safeCIdentifier(v, QStringLiteral("OnChange"));
        });

        if (g.type == QStringLiteral("Slider") || g.type == QStringLiteral("Scrollbar") || g.type == QStringLiteral("ProgressBar")) {
            addSpin(QObject::tr("Minimum"), g.minimum, -32768, 32767, [this, selected](int v) { m_gadgets[selected].minimum = v; });
            addSpin(QObject::tr("Maximum"), g.maximum, -32768, 32767, [this, selected](int v) { m_gadgets[selected].maximum = v; });
            addSpin(QObject::tr("Value"), g.value, -32768, 32767, [this, selected](int v) { m_gadgets[selected].value = v; });
        }
        if (g.type == QStringLiteral("Slider") || g.type == QStringLiteral("Scrollbar")) {
            auto *orientation = new QComboBox(m_propertyHost);
            orientation->addItem(QObject::tr("Vertical"), 0);
            orientation->addItem(QObject::tr("Horizontal"), 1);
            orientation->setCurrentIndex(g.orientation == 0 ? 0 : 1);
            m_propertyLayout->addRow(QObject::tr("Orientation"), orientation);
            connect(orientation, qOverload<int>(&QComboBox::currentIndexChanged), this,
                    [this, selected, orientation](int) {
                        pushUndoSnapshot();
                        m_gadgets[selected].orientation = orientation->currentData().toInt();
                        setModified(true);
                        m_canvas->update();
                    });
        }
        if (g.type == QStringLiteral("Checkbox")) {
            addCheck(
                QObject::tr("Checked"),
                g.checked != 0,
                [this, selected](bool checked) {
                    m_gadgets[selected].checked =
                        checked ? 1 : 0;
                });
        }

        if (g.type == QStringLiteral("Radio")) {
            addCheck(
                QObject::tr("Checked"),
                g.checked != 0,
                [this, selected](bool checked) {
                    setRadioChecked(
                        selected,
                        checked ? 1 : 0);

                    QTimer::singleShot(
                        0,
                        this,
                        [this]() {
                            rebuildProperties();
                        });
                });

            addSpin(QObject::tr("Radio group"), g.group, 0, 255, [this, selected](int v) {
                m_gadgets[selected].group = v;
                normalizeRadioGroups();

                QTimer::singleShot(
                    0,
                    this,
                    [this]() {
                        rebuildProperties();
                    });
            });
        }
        if (g.type == QStringLiteral("TextBox")) {
            addFlagList(
                QObject::tr("TextBox flags"),
                g.typeFlags,
                textBoxFlagChoices(),
                [this, selected](const QString &v) {
                    m_gadgets[selected].typeFlags = v;
                });
        }

        if (g.type == QStringLiteral("TextArea")) {
            addFlagList(
                QObject::tr("TextArea flags"),
                g.typeFlags,
                textAreaFlagChoices(),
                [this, selected](const QString &v) {
                    m_gadgets[selected].typeFlags = v;
                });
        }

        if (g.type == QStringLiteral("GridSelect")) {
            addFlagList(
                QObject::tr("GridSelect flags"),
                g.typeFlags,
                gridSelectFlagChoices(),
                [this, selected](const QString &v) {
                    m_gadgets[selected].typeFlags = v;
                });
        }

        if (g.type
            == QStringLiteral(
                "BitmapView")) {
            addFlagList(
                QObject::tr(
                    "BitmapView flags"),
                g.typeFlags,
                bitmapViewFlagChoices(),
                [this, selected](const QString &v) {
                    if (selected >= 0
                        && selected < m_gadgets.size()) {
                        m_gadgets[selected].typeFlags = v;
                    }
                });
        }

        if (g.type == QStringLiteral("Canvas")) {
            QString currentMode =
                g.typeFlags.trimmed();

            if (currentMode != QStringLiteral("CNV_LINE")
                && currentMode != QStringLiteral("CNV_RECTF")
                && currentMode != QStringLiteral("CNV_BEVEL")) {
                currentMode =
                    QStringLiteral("CNV_RECT");
            }

            addStringChoice(
                QObject::tr("Canvas draw mode"),
                {
                    QStringLiteral("CNV_LINE"),
                    QStringLiteral("CNV_RECT"),
                    QStringLiteral("CNV_RECTF"),
                    QStringLiteral("CNV_BEVEL")
                },
                currentMode,
                [this, selected](const QString &v) {
                    m_gadgets[selected].typeFlags = v;
                });
        }
        if (g.type == QStringLiteral("GridSelect")) {
            addSpin(
                QObject::tr("Cell width"),
                g.cellWidth,
                1,
                255,
                [this, selected](int v) {
                    m_gadgets[selected].cellWidth = v;
                    normaliseGridCellText(
                        &m_gadgets[selected]);

                    syncGridSelectGeometry(
                        &m_gadgets[selected]);

                    QTimer::singleShot(
                        0,
                        this,
                        [this]() {
                            rebuildProperties();
                        });
                });

            addSpin(
                QObject::tr("Cell height"),
                g.cellHeight,
                1,
                255,
                [this, selected](int v) {
                    m_gadgets[selected].cellHeight = v;
                    normaliseGridCellText(
                        &m_gadgets[selected]);

                    syncGridSelectGeometry(
                        &m_gadgets[selected]);

                    QTimer::singleShot(
                        0,
                        this,
                        [this]() {
                            rebuildProperties();
                        });
                });

            addSpin(
                QObject::tr("Cells X"),
                g.cellsX,
                1,
                255,
                [this, selected](int v) {
                    m_gadgets[selected].cellsX = v;
                    normaliseGridCellText(
                        &m_gadgets[selected]);

                    syncGridSelectGeometry(
                        &m_gadgets[selected]);

                    QTimer::singleShot(
                        0,
                        this,
                        [this]() {
                            rebuildProperties();
                        });
                });

            addSpin(
                QObject::tr("Cells Y"),
                g.cellsY,
                1,
                255,
                [this, selected](int v) {
                    m_gadgets[selected].cellsY = v;
                    normaliseGridCellText(
                        &m_gadgets[selected]);

                    syncGridSelectGeometry(
                        &m_gadgets[selected]);

                    QTimer::singleShot(
                        0,
                        this,
                        [this]() {
                            rebuildProperties();
                        });
                });
            addGridCellTextTable(
                selected);
        }
        if (g.type == QStringLiteral("BitmapView")) {
            addSpin(QObject::tr("Bitmap width"), g.bitmapWidth, 1, 32767, [this, selected](int v) { m_gadgets[selected].bitmapWidth = v; });
            addSpin(QObject::tr("Bitmap height"), g.bitmapHeight, 1, 32767, [this, selected](int v) { m_gadgets[selected].bitmapHeight = v; });
            QLineEdit *bitmapSourceEdit =
                addLine(
                    QObject::tr("Bitmap source"),
                    g.bitmapSource,
                    [this, selected](const QString &v) {
                        m_gadgets[selected].bitmapSource = v.trimmed();
                    });

            if (!g.bitmapPixels.isEmpty()) {
                bitmapSourceEdit->setEnabled(false);
                bitmapSourceEdit->setToolTip(
                    QObject::tr(
                        "Attached PNGs use the designer-generated aligned pixel array."));
            }

            auto *importPng =
                new QPushButton(
                    QObject::tr("Attach PNG -> Sidbox 8-bit"),
                    m_propertyHost);

            m_propertyLayout->addRow(
                QObject::tr("Image"),
                importPng);

            connect(
                importPng,
                &QPushButton::clicked,
                this,
                [this, selected]() {
                    importBitmapPng(selected);
                });

            if (!g.bitmapPixels.isEmpty()) {
                const QString bitmapDetails =
                    QObject::tr("%1 x %2, %3 indexed bytes")
                        .arg(g.bitmapWidth)
                        .arg(g.bitmapHeight)
                        .arg(g.bitmapPixels.size());

                m_propertyLayout->addRow(
                    QObject::tr("Image size"),
                    new QLabel(bitmapDetails, m_propertyHost));

                auto *imagePath = new QLineEdit(
                    QDir::toNativeSeparators(g.bitmapImagePath),
                    m_propertyHost);
                imagePath->setReadOnly(true);
                imagePath->setCursorPosition(0);
                imagePath->setToolTip(
                    g.bitmapImagePath.isEmpty()
                        ? bitmapDetails
                        : QDir::toNativeSeparators(g.bitmapImagePath)
                              + QStringLiteral("\n") + bitmapDetails);
                m_propertyLayout->addRow(
                    QObject::tr("Attached PNG"),
                    imagePath);

                auto *useDemo =
                    new QPushButton(
                        QObject::tr("Use default demo bitmap"),
                        m_propertyHost);

                m_propertyLayout->addRow(
                    QString(),
                    useDemo);

                connect(
                    useDemo,
                    &QPushButton::clicked,
                    this,
                    [this, selected]() {
                        restoreDefaultBitmap(selected);
                    });
            }
        }

        if (g.type == QStringLiteral("ListBox")) {
            addStringListEditor(
                QObject::tr("Preloaded items"),
                g.listItems,
                [this, selected](const QStringList &items) {
                    if (selected >= 0
                        && selected < m_gadgets.size()) {
                        m_gadgets[selected].listItems =
                            items;
                    }
                });
        }

        auto *deleteButton = new QPushButton(QObject::tr("Delete Gadget"), m_propertyHost);
        m_propertyLayout->addRow(deleteButton);
        connect(deleteButton, &QPushButton::clicked, this, [this, selected]() {
            if (!m_canvas
                || selected < 0
                || selected >= m_gadgets.size()) {
                return;
            }

            m_canvas->setSelectedIndex(selected);
            deleteSelectedGadget();
        });
    }

    static bool isMenuSeparatorText(
        const QString &text)
    {
        return text.trimmed()
            == QStringLiteral("---");
    }

    static QString menuFlagsWithoutSeparator(
        const QString &flags)
    {
        QStringList parts =
            splitFlagExpression(
                flags);

        parts.removeAll(
            QStringLiteral(
                "CG_MENUITEMF_SEPARATOR"));

        return parts.join(
            QStringLiteral(" | "));
    }

    static QString menuFlagsForItem(
        const GuiDesignerMenuItem &item)
    {
        QStringList parts =
            splitFlagExpression(
                item.flags);

        if (isMenuSeparatorText(
                item.text)
            && !parts.contains(
                QStringLiteral(
                    "CG_MENUITEMF_SEPARATOR"))) {
            parts.append(
                QStringLiteral(
                    "CG_MENUITEMF_SEPARATOR"));
        }

        return parts.join(
            QStringLiteral(" | "));
    }

    static void normaliseMenuItem(
        GuiDesignerMenuItem *item)
    {
        if (!item) {
            return;
        }

        if (isMenuSeparatorText(
                item->text)) {
            item->flags =
                menuFlagsForItem(
                    *item);

            /*
             * Separators can never activate, so do not generate a dead callback.
             */
            item->callback.clear();
            return;
        }

        item->flags =
            menuFlagsWithoutSeparator(
                item->flags);
    }

    void addMenuTitle()
    {
        bool ok = false;
        const QString title = QInputDialog::getText(this, QObject::tr("Add Menu"), QObject::tr("Menu title:"),
                                                   QLineEdit::Normal, QObject::tr("File"), &ok).trimmed();
        if (!ok || title.isEmpty()) return;
        pushUndoSnapshot();
        GuiDesignerMenuTitle m; m.title = title; m_menus.append(m);
        rebuildMenuTree(); setModified(true); m_canvas->update();
    }

    void addMenuEntry()
    {
        if (m_menus.isEmpty()) { addMenuTitle(); if (m_menus.isEmpty()) return; }
        int menuIndex = 0;
        if (QTreeWidgetItem *current = m_menuTree->currentItem()) {
            menuIndex = current->data(0, Qt::UserRole).toInt();
        }
        menuIndex = qBound(0, menuIndex, static_cast<int>(m_menus.size()) - 1);
        bool ok = false;
        const QString text = QInputDialog::getText(this, QObject::tr("Add Menu Item"), QObject::tr("Item text:"),
                                                  QLineEdit::Normal, QObject::tr("Item"), &ok).trimmed();
        if (!ok || text.isEmpty()) return;
        pushUndoSnapshot();
        GuiDesignerMenuItem item;
        item.text = text;

        const QString stemText =
            isMenuSeparatorText(text)
                ? QStringLiteral("separator_%1")
                      .arg(
                          m_menus.at(menuIndex)
                              .items.size() + 1)
                : text;

        const QString stem =
            safeCIdentifier(
                m_menus.at(menuIndex).title
                    + QLatin1Char('_')
                    + stemText,
                QStringLiteral("MenuItem"));

        item.name =
            QStringLiteral("menu_%1")
                .arg(stem);

        if (!isMenuSeparatorText(text)) {
            item.callback =
                QStringLiteral("On_%1")
                    .arg(item.name);
        }

        normaliseMenuItem(&item);
        m_menus[menuIndex].items.append(item);
        rebuildMenuTree(); setModified(true); m_canvas->update();
    }

    void removeMenuEntry()
    {
        QTreeWidgetItem *current = m_menuTree->currentItem();
        if (!current) return;
        pushUndoSnapshot();
        const int mi = current->data(0, Qt::UserRole).toInt();
        const int ii = current->data(0, Qt::UserRole + 1).toInt();
        if (mi < 0 || mi >= m_menus.size()) return;
        if (ii < 0) m_menus.removeAt(mi);
        else if (ii < m_menus[mi].items.size()) m_menus[mi].items.removeAt(ii);
        rebuildMenuTree(); setModified(true); m_canvas->update();
    }

    void editMenuEntry(QTreeWidgetItem *current)
    {
        if (!current) return;

        /*
         * The dialog edits a reference directly, so keep the previous state now.
         * A cancelled dialog may leave an unused undo snapshot; pushUndoSnapshot
         * deduplicates consecutive identical states.
         */
        pushUndoSnapshot();
        const int mi = current->data(0, Qt::UserRole).toInt();
        const int ii = current->data(0, Qt::UserRole + 1).toInt();
        if (mi < 0 || mi >= m_menus.size()) return;
        bool ok = false;
        if (ii < 0) {
            QString value = QInputDialog::getText(this, QObject::tr("Edit Menu"), QObject::tr("Menu title:"),
                                                  QLineEdit::Normal, m_menus[mi].title, &ok).trimmed();
            if (ok && !value.isEmpty()) m_menus[mi].title = value;
        } else if (ii < m_menus[mi].items.size()) {
            GuiDesignerMenuItem &item = m_menus[mi].items[ii];
            QString value = QInputDialog::getText(this, QObject::tr("Edit Menu Item"),
                                                  QObject::tr("Text (callback can be edited in generated C user block):"),
                                                  QLineEdit::Normal, item.text, &ok).trimmed();
            if (ok && !value.isEmpty()) {
                const bool wasSeparator =
                    isMenuSeparatorText(
                        item.text);

                item.text = value;

                if (wasSeparator
                    && !isMenuSeparatorText(
                           item.text)
                    && item.callback.isEmpty()) {
                    item.callback =
                        QStringLiteral("On_%1")
                            .arg(
                                safeCIdentifier(
                                    item.name,
                                    QStringLiteral(
                                        "MenuItem")));
                }

                normaliseMenuItem(
                    &item);
            }
        }
        if (ok) {
            /*
             * editMenuEntry mutates through references above, so capture was
             * taken before opening the edit dialog.
             */
            rebuildMenuTree();
            setModified(true);
            m_canvas->update();
        }
    }

    void rebuildMenuTree()
    {
        m_menuTree->clear();
        for (int mi = 0; mi < m_menus.size(); ++mi) {
            const GuiDesignerMenuTitle &menu = m_menus.at(mi);
            auto *menuItem = new QTreeWidgetItem(m_menuTree);
            menuItem->setText(0, menu.title);
            menuItem->setData(0, Qt::UserRole, mi);
            menuItem->setData(0, Qt::UserRole + 1, -1);
            menuItem->setExpanded(true);
            for (int ii = 0; ii < menu.items.size(); ++ii) {
                const GuiDesignerMenuItem &entry = menu.items.at(ii);
                auto *child = new QTreeWidgetItem(menuItem);

                if (isMenuSeparatorText(
                        entry.text)) {
                    child->setText(
                        0,
                        QStringLiteral(
                            "──────── separator ────────"));
                } else {
                    child->setText(
                        0,
                        QStringLiteral("%1 → %2")
                            .arg(
                                entry.text,
                                entry.callback));
                }
                child->setData(0, Qt::UserRole, mi);
                child->setData(0, Qt::UserRole + 1, ii);
            }
        }
    }

    bool loadDesign()
    {
        QFile f(m_filePath);
        if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) return false;
        QJsonParseError error;
        const QJsonDocument doc = QJsonDocument::fromJson(f.readAll(), &error);
        if (error.error != QJsonParseError::NoError || !doc.isObject()) return false;
        const QJsonObject root = doc.object();
        m_detached = root.value(QStringLiteral("detached")).toBool(false);
        m_sourceName = root.value(QStringLiteral("sourceFile")).toString();
        m_sketchName = root.value(QStringLiteral("sketchFile")).toString();
        // Old .sbui projects without this field regenerate once, then remember.
        m_needsGeneration = root.value(QStringLiteral("needsGeneration")).toBool(true);
        if (m_generationMode) {
            const QSignalBlocker blocker(m_generationMode);
            m_generationMode->setCurrentIndex(m_detached ? 1 : 0);
        }
        const QJsonObject w = root.value(QStringLiteral("window")).toObject();
        m_window.name = w.value(QStringLiteral("name")).toString(QStringLiteral("MainWindow"));
        m_window.title = w.value(QStringLiteral("title")).toString(QStringLiteral("CoderGirl Application"));
        m_window.flags = w.value(QStringLiteral("flags")).toString(QStringLiteral("SBX_WIN_DEFAULT"));
        m_window.backPen = w.value(QStringLiteral("backPen")).toInt(1);
        m_window.callbackMode = w.value(QStringLiteral("callbackMode")).toInt(1);
        m_window.rect = QRect(w.value(QStringLiteral("x")).toInt(32), w.value(QStringLiteral("y")).toInt(38),
                              w.value(QStringLiteral("w")).toInt(400), w.value(QStringLiteral("h")).toInt(250));

        m_gadgets.clear();
        for (const QJsonValue &value : root.value(QStringLiteral("gadgets")).toArray()) {
            const QJsonObject o = value.toObject(); GuiDesignerGadget g;
            g.type=o.value(QStringLiteral("type")).toString(); g.name=o.value(QStringLiteral("name")).toString();
            g.rect=QRect(o.value(QStringLiteral("x")).toInt(),o.value(QStringLiteral("y")).toInt(),o.value(QStringLiteral("w")).toInt(80),o.value(QStringLiteral("h")).toInt(20));
            g.text=o.value(QStringLiteral("text")).toString(); g.flags=o.value(QStringLiteral("flags")).toString(QStringLiteral("GAD_TOOL_DEFAULT"));
            // Before v9 the virtual bevel was always inset regardless of its
            // saved flags. Preserve that appearance for existing .sbui files.
            if (g.type == QStringLiteral("TabGroup")
                && root.value(QStringLiteral("version")).toInt(8) < 9
                && !g.flags.contains(QStringLiteral("GAD_TOOL_INSET"))) {
                QStringList flags = splitFlagExpression(g.flags);
                flags.removeAll(QStringLiteral("GAD_TOOL_DEFAULT"));
                flags.prepend(QStringLiteral("GAD_TOOL_INSET"));
                g.flags = flags.join(QStringLiteral(" | "));
            }
            g.bPen=o.value(QStringLiteral("bPen")).toInt(-1); g.fPen=o.value(QStringLiteral("fPen")).toInt(-1); g.hPen=o.value(QStringLiteral("hPen")).toInt(-1);
            g.onActivate=o.value(QStringLiteral("onActivate")).toString(); g.onChange=o.value(QStringLiteral("onChange")).toString();
            g.tabOwner=o.value(QStringLiteral("tabOwner")).toString(); g.tabPage=o.value(QStringLiteral("tabPage")).toInt(0);
            g.defaultTabPage=o.value(QStringLiteral("defaultTabPage")).toInt(0);
            g.openWindowFile=o.value(QStringLiteral("openWindowFile")).toString();
            g.callbackRoute=o.value(QStringLiteral("callbackRoute")).toInt(-1);
            g.minimum=o.value(QStringLiteral("minimum")).toInt(0); g.maximum=o.value(QStringLiteral("maximum")).toInt(100); g.value=o.value(QStringLiteral("value")).toInt(0);
            g.orientation=o.value(QStringLiteral("orientation")).toInt(1); g.checked=o.value(QStringLiteral("checked")).toInt(0); g.enabled=o.value(QStringLiteral("enabled")).toBool(true); g.group=o.value(QStringLiteral("group")).toInt(0);
            g.typeFlags=o.value(QStringLiteral("typeFlags")).toString();
            g.timerDelayMs=qBound(1,o.value(QStringLiteral("timerDelayMs")).toInt(1000),86400000);
            g.timerPeriodMs=qBound(1,o.value(QStringLiteral("timerPeriodMs")).toInt(1000),86400000);
            g.timerRepeat=o.value(QStringLiteral("timerRepeat")).toBool(true);
            g.timerAutoStart=o.value(QStringLiteral("timerAutoStart")).toBool(true);
            g.timerKeepAliveOnClose=o.value(QStringLiteral("timerKeepAliveOnClose")).toBool(false);
            g.ipcReceive=o.value(QStringLiteral("ipcReceive")).toBool(true);
            g.ipcPollMs=qBound(10,o.value(QStringLiteral("ipcPollMs")).toInt(25),1000);
            g.ipcTargetApp=o.value(QStringLiteral("ipcTargetApp")).toString();
            g.ipcSendTarget=o.value(QStringLiteral("ipcSendTarget")).toString();
            g.ipcSendType=qBound(0,o.value(QStringLiteral("ipcSendType")).toInt(1),65535);
            g.ipcSendText=o.value(QStringLiteral("ipcSendText")).toString(QStringLiteral("Hello from SIDBOX!"));
         g.uart1Baud = qBound(1200, o.value(QStringLiteral("uart1Baud")).toInt(9600), 1000000);
         g.uart1DataBits = qBound(7, o.value(QStringLiteral("uart1DataBits")).toInt(8), 8);
         g.uart1Parity = qBound(0, o.value(QStringLiteral("uart1Parity")).toInt(0), 2);
         g.uart1StopBits = qBound(1, o.value(QStringLiteral("uart1StopBits")).toInt(1), 2);
         g.uart1PollMs = qBound(10, o.value(QStringLiteral("uart1PollMs")).toInt(20), 1000);
         g.uart1AutoOpen = o.value(QStringLiteral("uart1AutoOpen")).toBool(false);
            g.mediaMode=o.value(QStringLiteral("mediaMode")).toString(QStringLiteral("SFX"));
            g.mediaFile=o.value(QStringLiteral("mediaFile")).toString();
            g.mediaEmbedSfx=o.value(QStringLiteral("mediaEmbedSfx")).toBool(false);
            g.mediaEmbeddedName=o.value(QStringLiteral("mediaEmbeddedName")).toString();
            g.mediaEmbeddedPcm=QByteArray::fromBase64(
                o.value(QStringLiteral("mediaEmbeddedPcmBase64")).toString().toLatin1());
            g.mediaChannel=o.value(QStringLiteral("mediaChannel")).toInt(0);
            g.mediaVolume=o.value(QStringLiteral("mediaVolume")).toInt(200);
            g.mediaPan=o.value(QStringLiteral("mediaPan")).toInt(0);
            g.mediaFrequency=o.value(QStringLiteral("mediaFrequency")).toInt(22050);
            g.mediaSubsong=o.value(QStringLiteral("mediaSubsong")).toInt(0);
            g.mediaLoop=o.value(QStringLiteral("mediaLoop")).toBool(false);
            g.mediaAutoStart=o.value(QStringLiteral("mediaAutoStart")).toBool(false);
            g.mediaTarget=o.value(QStringLiteral("mediaTarget")).toString();
            g.mediaAction=o.value(QStringLiteral("mediaAction")).toString(QStringLiteral("Play"));
            g.dialogTitle = o.value(QStringLiteral("dialogTitle")).toString(QStringLiteral("Select a file"));
            g.dialogMessage = o.value(QStringLiteral("dialogMessage")).toString(QStringLiteral("Are you sure?"));
            g.dialogDir = o.value(QStringLiteral("dialogDir")).toString(QStringLiteral("sdcard:/"));
            g.dialogFilter = o.value(QStringLiteral("dialogFilter")).toString(QStringLiteral("*.*"));
            g.dialogKind = o.value(QStringLiteral("dialogKind")).toString(QStringLiteral("Message"));
            g.dialogButtons = o.value(QStringLiteral("dialogButtons")).toString(QStringLiteral("OK/Cancel"));
            g.dialogBlockOwner = o.value(QStringLiteral("dialogBlockOwner")).toBool(false);
            g.dialogTarget = o.value(QStringLiteral("dialogTarget")).toString();
            g.cellWidth=o.value(QStringLiteral("cellWidth")).toInt(24); g.cellHeight=o.value(QStringLiteral("cellHeight")).toInt(18);
            g.cellsX=o.value(QStringLiteral("cellsX")).toInt(4); g.cellsY=o.value(QStringLiteral("cellsY")).toInt(4);

            for (const QJsonValue &cellValue :
                 o.value(QStringLiteral("gridCellText")).toArray()) {
                g.gridCellText.append(
                    cellValue.toString().left(4));
            }

            g.bitmapWidth=o.value(QStringLiteral("bitmapWidth")).toInt(64); g.bitmapHeight=o.value(QStringLiteral("bitmapHeight")).toInt(64);
            g.bitmapSource =
                o.value(QStringLiteral("bitmapSource"))
                    .toString();
            g.bitmapImagePath =
                o.value(QStringLiteral("bitmapImagePath"))
                    .toString();
            g.bitmapPixels =
                QByteArray::fromBase64(
                    o.value(QStringLiteral("bitmapPixelsBase64"))
                        .toString()
                        .toLatin1());

            for (const QJsonValue &itemValue :
                 o.value(
                     QStringLiteral(
                         "listItems"))
                     .toArray()) {
                g.listItems.append(
                    itemValue.toString());
            }

            syncGridSelectGeometry(
                &g);

            normaliseBitmapView(
                &g);

            m_gadgets.append(g);
        }

        normalizeRadioGroups();
        m_canvas->enforceWindowScreenBounds();

        m_menus.clear();
        for (const QJsonValue &menuValue : root.value(QStringLiteral("menus")).toArray()) {
            const QJsonObject mo = menuValue.toObject(); GuiDesignerMenuTitle menu; menu.title = mo.value(QStringLiteral("title")).toString();
            for (const QJsonValue &itemValue : mo.value(QStringLiteral("items")).toArray()) {
                const QJsonObject io = itemValue.toObject(); GuiDesignerMenuItem item;
                item.name=io.value(QStringLiteral("name")).toString(); item.text=io.value(QStringLiteral("text")).toString();
                item.callback=io.value(QStringLiteral("callback")).toString(); item.flags=io.value(QStringLiteral("flags")).toString();
                normaliseMenuItem(&item);
                menu.items.append(item);
            }
            m_menus.append(menu);
        }
        const int snap =
            root.value(
                    QStringLiteral(
                        "designerGridSnap"))
                .toInt(0);

        m_canvas->setGridSnap(
            snap);

        if (m_snapCombo) {
            const int index =
                m_snapCombo->findData(
                    snap);

            if (index >= 0) {
                m_snapCombo->setCurrentIndex(
                    index);
            }
        }

        setModified(false);
        return true;
    }

    QJsonObject gadgetToJson(const GuiDesignerGadget &g) const
    {
        QJsonObject o; o.insert(QStringLiteral("type"),g.type); o.insert(QStringLiteral("name"),g.name);
        o.insert(QStringLiteral("x"),g.rect.x()); o.insert(QStringLiteral("y"),g.rect.y()); o.insert(QStringLiteral("w"),g.rect.width()); o.insert(QStringLiteral("h"),g.rect.height());
        o.insert(QStringLiteral("text"),g.text); o.insert(QStringLiteral("flags"),g.flags); o.insert(QStringLiteral("bPen"),g.bPen); o.insert(QStringLiteral("fPen"),g.fPen); o.insert(QStringLiteral("hPen"),g.hPen);
        o.insert(QStringLiteral("onActivate"),g.onActivate); o.insert(QStringLiteral("onChange"),g.onChange); o.insert(QStringLiteral("openWindowFile"),g.openWindowFile); o.insert(QStringLiteral("tabOwner"),g.tabOwner); o.insert(QStringLiteral("tabPage"),g.tabPage); o.insert(QStringLiteral("defaultTabPage"),g.defaultTabPage); o.insert(QStringLiteral("callbackRoute"),g.callbackRoute); o.insert(QStringLiteral("minimum"),g.minimum); o.insert(QStringLiteral("maximum"),g.maximum); o.insert(QStringLiteral("value"),g.value);
        o.insert(QStringLiteral("orientation"),g.orientation); o.insert(QStringLiteral("checked"),g.checked); o.insert(QStringLiteral("enabled"),g.enabled); o.insert(QStringLiteral("group"),g.group); o.insert(QStringLiteral("typeFlags"),g.typeFlags);
        o.insert(QStringLiteral("timerDelayMs"),g.timerDelayMs);
        o.insert(QStringLiteral("timerPeriodMs"),g.timerPeriodMs);
        o.insert(QStringLiteral("timerRepeat"),g.timerRepeat);
        o.insert(QStringLiteral("timerAutoStart"),g.timerAutoStart);
        o.insert(QStringLiteral("timerKeepAliveOnClose"),g.timerKeepAliveOnClose);
        o.insert(QStringLiteral("ipcReceive"),g.ipcReceive);
        o.insert(QStringLiteral("ipcPollMs"),g.ipcPollMs);
        o.insert(QStringLiteral("ipcTargetApp"),g.ipcTargetApp);
        o.insert(QStringLiteral("ipcSendTarget"),g.ipcSendTarget);
        o.insert(QStringLiteral("ipcSendType"),g.ipcSendType);
        o.insert(QStringLiteral("ipcSendText"),g.ipcSendText);
        o.insert(QStringLiteral("uart1Baud"),g.uart1Baud);
        o.insert(QStringLiteral("uart1DataBits"),g.uart1DataBits);
        o.insert(QStringLiteral("uart1Parity"),g.uart1Parity);
        o.insert(QStringLiteral("uart1StopBits"),g.uart1StopBits);
        o.insert(QStringLiteral("uart1PollMs"),g.uart1PollMs);
        o.insert(QStringLiteral("uart1AutoOpen"),g.uart1AutoOpen);
        o.insert(QStringLiteral("mediaMode"),g.mediaMode);
        o.insert(QStringLiteral("mediaFile"),g.mediaFile);
        o.insert(QStringLiteral("mediaEmbedSfx"),g.mediaEmbedSfx);
        o.insert(QStringLiteral("mediaEmbeddedName"),g.mediaEmbeddedName);
        o.insert(QStringLiteral("mediaEmbeddedPcmBase64"),
                 QString::fromLatin1(g.mediaEmbeddedPcm.toBase64()));
        o.insert(QStringLiteral("mediaChannel"),g.mediaChannel);
        o.insert(QStringLiteral("mediaVolume"),g.mediaVolume);
        o.insert(QStringLiteral("mediaPan"),g.mediaPan);
        o.insert(QStringLiteral("mediaFrequency"),g.mediaFrequency);
        o.insert(QStringLiteral("mediaSubsong"),g.mediaSubsong);
        o.insert(QStringLiteral("mediaLoop"),g.mediaLoop);
        o.insert(QStringLiteral("mediaAutoStart"),g.mediaAutoStart);
        o.insert(QStringLiteral("mediaTarget"),g.mediaTarget);
        o.insert(QStringLiteral("mediaAction"),g.mediaAction);
        o.insert(QStringLiteral("dialogTitle"),g.dialogTitle);
        o.insert(QStringLiteral("dialogMessage"),g.dialogMessage);
        o.insert(QStringLiteral("dialogDir"),g.dialogDir);
        o.insert(QStringLiteral("dialogFilter"),g.dialogFilter);
        o.insert(QStringLiteral("dialogKind"),g.dialogKind);
        o.insert(QStringLiteral("dialogButtons"),g.dialogButtons);
        o.insert(QStringLiteral("dialogBlockOwner"),g.dialogBlockOwner);
        o.insert(QStringLiteral("dialogTarget"),g.dialogTarget);
        o.insert(QStringLiteral("cellWidth"),g.cellWidth); o.insert(QStringLiteral("cellHeight"),g.cellHeight); o.insert(QStringLiteral("cellsX"),g.cellsX); o.insert(QStringLiteral("cellsY"),g.cellsY);

        QJsonArray gridCellText;
        for (const QString &cellText : g.gridCellText) {
            gridCellText.append(cellText.left(4));
        }
        o.insert(QStringLiteral("gridCellText"), gridCellText);

        o.insert(QStringLiteral("bitmapWidth"),g.bitmapWidth); o.insert(QStringLiteral("bitmapHeight"),g.bitmapHeight);
        o.insert(QStringLiteral("bitmapSource"), g.bitmapSource);
        o.insert(QStringLiteral("bitmapImagePath"), g.bitmapImagePath);
        o.insert(QStringLiteral("bitmapPixelsBase64"),
                 QString::fromLatin1(g.bitmapPixels.toBase64()));

        QJsonArray listItems;
        for (const QString &item : g.listItems) {
            listItems.append(item);
        }
        o.insert(QStringLiteral("listItems"), listItems);

        return o;
    }

    bool saveDesign()
    {
        if (!validateProjectWindows(false)) return false;
        QJsonObject w; w.insert(QStringLiteral("name"),m_window.name); w.insert(QStringLiteral("title"),m_window.title); w.insert(QStringLiteral("flags"),m_window.flags); w.insert(QStringLiteral("backPen"),m_window.backPen); w.insert(QStringLiteral("callbackMode"),m_window.callbackMode);
        w.insert(QStringLiteral("x"),m_window.rect.x()); w.insert(QStringLiteral("y"),m_window.rect.y()); w.insert(QStringLiteral("w"),m_window.rect.width()); w.insert(QStringLiteral("h"),m_window.rect.height());
        QJsonArray gadgets; for (const GuiDesignerGadget &g : std::as_const(m_gadgets)) gadgets.append(gadgetToJson(g));
        QJsonArray menus; for (const GuiDesignerMenuTitle &menu : std::as_const(m_menus)) { QJsonObject mo; mo.insert(QStringLiteral("title"),menu.title); QJsonArray items; for (const GuiDesignerMenuItem &item : menu.items) { QJsonObject io; io.insert(QStringLiteral("name"),item.name); io.insert(QStringLiteral("text"),item.text); io.insert(QStringLiteral("callback"),item.callback); io.insert(QStringLiteral("flags"),item.flags); items.append(io); } mo.insert(QStringLiteral("items"),items); menus.append(mo); }
        QJsonObject root; root.insert(QStringLiteral("format"),QStringLiteral("SidboxGUI")); root.insert(QStringLiteral("version"),9); root.insert(QStringLiteral("screenWidth"),480); root.insert(QStringLiteral("screenHeight"),320); root.insert(QStringLiteral("designerGridSnap"),m_canvas ? m_canvas->gridSnap() : 0); root.insert(QStringLiteral("window"),w); root.insert(QStringLiteral("gadgets"),gadgets); root.insert(QStringLiteral("menus"),menus);
        root.insert(QStringLiteral("detached"), m_detached);
        root.insert(QStringLiteral("sourceFile"), m_sourceName);
        root.insert(QStringLiteral("sketchFile"), m_sketchName);
        root.insert(QStringLiteral("needsGeneration"), m_needsGeneration);
        QSaveFile file(m_filePath); if (!file.open(QIODevice::WriteOnly|QIODevice::Text)) { QMessageBox::warning(this,QObject::tr("GUI Designer"),QObject::tr("Could not save %1").arg(QDir::toNativeSeparators(m_filePath))); return false; }
        file.write(QJsonDocument(root).toJson(QJsonDocument::Indented)); if (!file.commit()) return false;
        setModified(false); return true;
    }

    static QString normalisePreservedUserBlock(const QString &raw)
    {
        QString text = raw;
        text.replace(QStringLiteral("\r\n"), QStringLiteral("\n"));
        text.replace(QLatin1Char('\r'), QLatin1Char('\n'));

        QStringList lines =
            text.split(
                QLatin1Char('\n'),
                Qt::KeepEmptyParts);

        while (!lines.isEmpty()
               && lines.first().trimmed().isEmpty()) {
            lines.removeFirst();
        }

        while (!lines.isEmpty()
               && lines.last().trimmed().isEmpty()) {
            lines.removeLast();
        }

        int commonIndent = -1;

        for (const QString &line :
             lines) {
            if (line.trimmed().isEmpty()) {
                continue;
            }

            int indent = 0;

            while (indent < line.size()
                   && (line.at(indent) == QLatin1Char(' ')
                       || line.at(indent) == QLatin1Char('\t'))) {
                ++indent;
            }

            if (commonIndent < 0
                || indent < commonIndent) {
                commonIndent = indent;
            }
        }

        if (commonIndent > 0) {
            for (QString &line :
                 lines) {
                int remove = 0;

                while (remove < commonIndent
                       && remove < line.size()
                       && (line.at(remove) == QLatin1Char(' ')
                           || line.at(remove) == QLatin1Char('\t'))) {
                    ++remove;
                }

                line.remove(0, remove);
            }
        }

        return lines.join(
            QLatin1Char('\n'));
    }

    QHash<QString, QString> preservedUserBlocks(const QString &oldSource, const QStringList &keys) const
    {
        Q_UNUSED(keys);

        /*
         * Read EVERY old USER block, not only callbacks which still exist in the
         * design. Deleted/renamed gadgets therefore cannot silently destroy the
         * programmer's callback body; orphaned blocks are appended under #if 0.
         */
        QHash<QString, QString> result;
        const QString prefix = QStringLiteral("/* <SIDBOX-GUI:USER ");
        int searchFrom = 0;

        while (searchFrom < oldSource.size()) {
            const int begin = oldSource.indexOf(prefix, searchFrom);
            if (begin < 0) break;

            const int keyStart = begin + prefix.size();
            const int keyEnd = oldSource.indexOf(QStringLiteral("> */"), keyStart);
            if (keyEnd < 0) break;

            const QString key = oldSource.mid(keyStart, keyEnd - keyStart).trimmed();
            if (key.isEmpty()) {
                searchFrom = keyEnd + 4;
                continue;
            }

            const QString beginMarker = QStringLiteral("/* <SIDBOX-GUI:USER %1> */").arg(key);
            const QString endMarker = QStringLiteral("/* </SIDBOX-GUI:USER %1> */").arg(key);
            const int contentStart = begin + beginMarker.size();
            const int end = oldSource.indexOf(endMarker, contentStart);
            if (end < 0) break;

            result.insert(
                key,
                normalisePreservedUserBlock(
                    oldSource.mid(
                        contentStart,
                        end - contentStart)));
            searchFrom = end + endMarker.size();
        }

        return result;
    }

    QString generatedCPath() const
    {
        const QFileInfo info(m_filePath);
        const QString name = m_detached
            ? (m_sketchName.isEmpty() ? info.completeBaseName() + QStringLiteral(".uis") : m_sketchName)
            : (m_sourceName.isEmpty() ? info.completeBaseName() + QStringLiteral(".c") : m_sourceName);
        return info.dir().absoluteFilePath(name);
    }

    QString outputPath(bool sketch) const
    {
        const QFileInfo info(m_filePath);
        const QString name = sketch
            ? (m_sketchName.isEmpty() ? info.completeBaseName() + QStringLiteral(".uis") : m_sketchName)
            : (m_sourceName.isEmpty() ? info.completeBaseName() + QStringLiteral(".c") : m_sourceName);
        return info.dir().absoluteFilePath(name);
    }

    // A generated window has exactly one public entry point.  Keep every
    // callback, gadget and window handle private to its .c translation unit.
    QString generatedHeaderPath(const QString &cPath) const
    {
        const QFileInfo info(cPath);
        return info.dir().filePath(info.completeBaseName() + QStringLiteral(".h"));
    }

    QByteArray generatedHeaderMarker() const
    {
        return (QStringLiteral("/* SIDBOX-IDE GENERATED GUI HEADER: ")
                + QFileInfo(m_filePath).fileName() + QStringLiteral(" */\n")).toUtf8();
    }

    QString generatedHeaderGuard(const QString &cPath) const
    {
        // Project-relative path keeps guards unique across similarly named windows.
        const QString relativeHeader = QDir(designProjectRoot()).relativeFilePath(
            generatedHeaderPath(cPath));
        return QStringLiteral("SIDBOX_GUI_")
            + safeCIdentifier(relativeHeader, QStringLiteral("WINDOW_H")).toUpper()
            + QStringLiteral("_INCLUDED");
    }

    static QString headerUserBeginMarker()
    {
        return QStringLiteral("/* <SIDBOX-GUI:USER HEADER> */");
    }

    static QString headerUserEndMarker()
    {
        return QStringLiteral("/* </SIDBOX-GUI:USER HEADER> */");
    }

    static QString defaultHeaderUserBlock()
    {
        return QStringLiteral("\n/* Add custom C declarations, types or macros here. */\n");
    }

    QString generatedHeaderContents(const QString &cPath,
                                    const QString &windowEntry,
                                    const QString &userBlock,
                                    bool legacy = false,
                                    const QString &ownerOverride = QString(),
                                    const QString &guardOverride = QString()) const
    {
        const QString guard = guardOverride.isEmpty()
            ? generatedHeaderGuard(cPath) : guardOverride;
        const QString owner = ownerOverride.isEmpty()
            ? QString::fromUtf8(generatedHeaderMarker()) : ownerOverride;
        // The legacy rendering is EXACTLY the Stage 21 header format.  This
        // allows a safe one-time upgrade; a hand-edited legacy header will be
        // rejected rather than overwritten.
        // Identity overrides are for validating a moved/renamed generated
        // header against its ORIGINAL identity. Normal output always uses
        // the current .sbui name and current project-relative include guard.
        QString contents = owner
            + (legacy
                ? QStringLiteral("/* Auto-generated declarations. Edit the .sbui, not this file. */\n")
                : QStringLiteral("/* Generated declarations: edit the .sbui. Custom C declarations: edit the USER block. */\n"))
            + QStringLiteral("#ifndef ") + guard + QStringLiteral("\n#define ")
            + guard + QStringLiteral("\n\n#ifdef __cplusplus\nextern \"C\" {\n#endif\n\n")
            + QStringLiteral("void ") + windowEntry + QStringLiteral("(void);\n\n");
        if (!legacy) {
            contents += headerUserBeginMarker() + userBlock
                      + headerUserEndMarker() + QStringLiteral("\n\n");
        }
        contents += QStringLiteral("#ifdef __cplusplus\n}\n#endif\n\n#endif /* ")
                    + guard + QStringLiteral(" */\n");
        return contents;
    }

    // Return the sole designer-generated entry point from the *generated*
    // portion of an existing header, never from the user-controlled block.
    static QString entryFromGeneratedHeader(const QString &prefix)
    {
        const QRegularExpression declaration(QStringLiteral(
            "\\bvoid\\s+([A-Za-z_][A-Za-z_0-9]*)\\s*\\(void\\)\\s*;"));
        auto matches = declaration.globalMatch(prefix);
        if (!matches.hasNext()) return {};
        const QString entry = matches.next().captured(1);
        return matches.hasNext() ? QString() : entry;
    }

    // Do not overwrite a programmer-owned header, a damaged protected block,
    // or edits made outside a protected block.  Accept the exact old generated
    // header from Stage 21 and upgrade it with a new protected USER section.
    bool canWriteGeneratedHeader(const QString &cPath, QString *preservedUserBlock = nullptr)
    {
        if (preservedUserBlock) *preservedUserBlock = defaultHeaderUserBlock();
        const QString headerPath = generatedHeaderPath(cPath);
        const QFileInfo headerInfo(headerPath);
        if (headerInfo.isSymLink()) {
            QMessageBox::warning(this, QObject::tr("Generated header conflict"),
                QObject::tr("Refusing to overwrite a symbolic-link header:\n%1")
                    .arg(QDir::toNativeSeparators(headerPath)));
            return false;
        }
        if (!headerInfo.exists()) return true;

        QFile existing(headerPath);
        if (!existing.open(QIODevice::ReadOnly)) {
            QMessageBox::warning(this, QObject::tr("Generated header error"),
                QObject::tr("Cannot read the existing header:\n%1\n\n"
                            "Nothing was overwritten.")
                    .arg(QDir::toNativeSeparators(headerPath)));
            return false;
        }
        const QByteArray originalBytes = existing.readAll();
        const QString oldHeader = QString::fromUtf8(originalBytes);
        // Reject non-UTF-8 edits instead of silently replacing characters.
        if (oldHeader.toUtf8() != originalBytes) {
            QMessageBox::warning(this, QObject::tr("Generated header conflict"),
                QObject::tr("%1 is not valid UTF-8 and will not be overwritten.")
                    .arg(QDir::toNativeSeparators(headerPath)));
            return false;
        }
        const QString begin = headerUserBeginMarker();
        const QString end = headerUserEndMarker();
        const int beginAt = oldHeader.indexOf(begin);
        const int endAt = oldHeader.indexOf(end);

        // The original ownership line and include guard may describe the OLD
        // path of a .sbui/.h that was moved or renamed within the project.
        // Never use current names to validate an OLD intact generated header.
        // Instead, render the complete expected template with the ORIGINAL
        // identity, and compare everything outside the protected USER block.
        // On a match, normal writing migrates to the current identity and
        // carries over the USER block byte-for-byte (as UTF-8 text).
        const int firstLineEnd = oldHeader.indexOf(QLatin1Char('\n'));
        const QString originalOwner = firstLineEnd >= 0
            ? oldHeader.left(firstLineEnd + 1) : QString();
        const bool ownedByDesigner = originalOwner.startsWith(
                QStringLiteral("/* SIDBOX-IDE GENERATED GUI HEADER: "))
            && originalOwner.endsWith(QStringLiteral(".sbui */\n"));

        static const QRegularExpression guardPattern(QStringLiteral(
            R"((?m)^#ifndef (SIDBOX_GUI_[A-Z0-9_]+_INCLUDED)$)"));
        const QRegularExpressionMatch guardMatch = guardPattern.match(oldHeader);
        const QString originalGuard = guardMatch.hasMatch()
            ? guardMatch.captured(1) : QString();

        if (ownedByDesigner && !originalGuard.isEmpty()) {
            if (beginAt >= 0 && endAt > beginAt
                && oldHeader.count(begin) == 1 && oldHeader.count(end) == 1) {
                const QString originalEntry = entryFromGeneratedHeader(oldHeader.left(beginAt));
                const int userStart = beginAt + begin.size();
                const QString userBody = oldHeader.mid(userStart, endAt - userStart);
                if (!originalEntry.isEmpty()
                    && oldHeader == generatedHeaderContents(
                        cPath, originalEntry, userBody, false,
                        originalOwner, originalGuard)) {
                    if (preservedUserBlock) *preservedUserBlock = userBody;
                    return true;
                }
            } else if (beginAt < 0 && endAt < 0) {
                const QString originalEntry = entryFromGeneratedHeader(oldHeader);
                if (!originalEntry.isEmpty()
                    && oldHeader == generatedHeaderContents(
                        cPath, originalEntry, QString(), true,
                        originalOwner, originalGuard)) {
                    // Intact legacy header: add a protected USER block.
                    return true;
                }
            }
        }

        QMessageBox::warning(this,
            QObject::tr("Generated header conflict"),
            QObject::tr("Cannot safely regenerate %1.\n\n"
                        "The header is not recognised as an intact CoderGirl "
                        "generated header, or its USER markers/generated "
                        "sections were changed.\n\n"
                        "Your file was NOT overwritten. Restore the protected "
                        "markers and generated sections, or copy your declarations "
                        "to a separate programmer-owned header before continuing.")
                .arg(QDir::toNativeSeparators(headerPath)));
        return false;
    }

    bool writeGeneratedHeader(const QString &cPath, const QString &windowEntry,
                              bool *changed = nullptr)
    {
        if (changed) *changed = false;
        QString savedUserBlock;
        if (!canWriteGeneratedHeader(cPath, &savedUserBlock)) return false;
        const QString headerPath = generatedHeaderPath(cPath);
        const QByteArray bytes = generatedHeaderContents(
            cPath, windowEntry, savedUserBlock).toUtf8();
        QFile previous(headerPath);
        if (previous.open(QIODevice::ReadOnly) && previous.readAll() == bytes)
            return true; // Preserve timestamps when the content has not changed.
        if (!QDir().mkpath(QFileInfo(headerPath).absolutePath())) {
            QMessageBox::warning(this, QObject::tr("GUI Designer"),
                QObject::tr("Cannot create header directory: %1")
                    .arg(QDir::toNativeSeparators(QFileInfo(headerPath).absolutePath())));
            return false;
        }
        QSaveFile header(headerPath);
        if (!header.open(QIODevice::WriteOnly | QIODevice::Text)
            || header.write(bytes) != bytes.size() || !header.commit()) {
            QMessageBox::warning(this, QObject::tr("GUI Designer"),
                QObject::tr("Cannot write generated header: %1")
                    .arg(QDir::toNativeSeparators(headerPath)));
            return false;
        }
        if (changed) *changed = true;
        return true;
    }

    QString appletTypeFlagExpression(
        const GuiDesignerGadget &g) const
    {
        QString value =
            g.typeFlags.trimmed();

        if (value.isEmpty()) {
            if (g.type
                == QStringLiteral(
                    "GridSelect")) {
                return QStringLiteral(
                    "1u");
            }

            return QStringLiteral(
                "0u");
        }

        /*
         * These names exist in the firmware-side CoderGirl headers but are not
         * exported by the current applet API headers. Translate the known ones
         * to their wire values so generated applet code still compiles today.
         */
        const QHash<QString, QString> known = {
            {QStringLiteral("TB_SINGLELINE"), QStringLiteral("0u")},
            {QStringLiteral("TB_READONLY"), QStringLiteral("1u")},
            {QStringLiteral("TB_MULTILINE"), QStringLiteral("4u")},
            {QStringLiteral("TA_DEFAULT"), QStringLiteral("0u")},
            {QStringLiteral("TA_READONLY"), QStringLiteral("1u")},
            {QStringLiteral("TA_WORDWRAP"), QStringLiteral("2u")},
            {QStringLiteral("TA_NO_HSCROLL"), QStringLiteral("4u")},
            {QStringLiteral("TA_NOSEL"), QStringLiteral("8u")},
            {QStringLiteral("GAD_GRIDSEL_JUST_ONE"), QStringLiteral("1u")},
            {QStringLiteral("GAD_GRIDSEL_TEXT_INVERT"), QStringLiteral("2u")},
            {QStringLiteral("GAD_GRIDSEL_NOHIGHLIGHT"), QStringLiteral("4u")}
        };

        /*
         * Support simple OR expressions such as:
         *
         *     TA_READONLY | TA_NO_HSCROLL
         *
         * by replacing each exported-missing symbolic token individually.
         */
        for (auto it =
                 known.constBegin();
             it !=
                 known.constEnd();
             ++it) {
            value.replace(
                QRegularExpression(
                    QStringLiteral(
                        R"(\b%1\b)")
                        .arg(
                            QRegularExpression::escape(
                                it.key()))),
                QStringLiteral(
                    "(%1)")
                    .arg(
                        it.value()));
        }

        return value;
    }


    QString creationExpression(
        const GuiDesignerGadget &g,
        const QString &win) const
    {
        const QRect r =
            g.rect;

        const QString flags =
            g.flags.trimmed().isEmpty()
                ? QStringLiteral(
                      "GAD_TOOL_DEFAULT")
                : g.flags.trimmed();

        const QString text =
            escapedCString(
                g.text);

        const QString typeFlags =
            appletTypeFlagExpression(
                g);

        /*
         * Generate against the APPLET API table from api/apis.h, not the
         * firmware's private cg_codergirl.h functions.
         *
         * Some convenience SBOS_CreateX macros do not exist in the current
         * public gadgets.h yet, but every creator IS already exported in
         * API_GUI_GADGETS. Calling the API table directly keeps generated code
         * compiling without waiting for wrapper macros.
         */
        if (g.type == QStringLiteral("TabGroup")) {
            return QStringLiteral(
                "API->gui->gadgets->canvas_create(%1, %2, %3, %4, %5, CNV_BEVEL, %6)")
                .arg(win).arg(r.x()).arg(r.y()+24).arg(r.width())
                .arg(qMax(1,r.height()-24)).arg(flags);
        }
        if (g.type
            == QStringLiteral(
                "Button")) {
            return QStringLiteral(
                "API->gui->gadgets->button_create(%1, %2, %3, %4, %5, \"%6\", %7)")
                .arg(win)
                .arg(r.x())
                .arg(r.y())
                .arg(r.width())
                .arg(r.height())
                .arg(text, flags);
        }

        if (g.type
            == QStringLiteral(
                "Label")) {
            return QStringLiteral(
                "API->gui->gadgets->label_create(%1, %2, %3, %4, %5, \"%6\", %7)")
                .arg(win)
                .arg(r.x())
                .arg(r.y())
                .arg(r.width())
                .arg(r.height())
                .arg(text, flags);
        }

        if (g.type
            == QStringLiteral(
                "Checkbox")) {
            return QStringLiteral(
                "API->gui->gadgets->checkbox_create(%1, %2, %3, %4, %5, \"%6\", %7, %8)")
                .arg(win)
                .arg(r.x())
                .arg(r.y())
                .arg(r.width())
                .arg(r.height())
                .arg(text)
                .arg(g.checked)
                .arg(flags);
        }

        if (g.type
            == QStringLiteral(
                "Radio")) {
            return QStringLiteral(
                "API->gui->gadgets->radiobutton_create(%1, %2, %3, %4, %5, \"%6\", %7, %8, %9)")
                .arg(win)
                .arg(r.x())
                .arg(r.y())
                .arg(r.width())
                .arg(r.height())
                .arg(text)
                .arg(g.group)
                .arg(g.checked)
                .arg(flags);
        }

        if (g.type
            == QStringLiteral(
                "Slider")) {
            return QStringLiteral(
                "API->gui->gadgets->slider_create(%1, %2, %3, %4, %5, %6, %7, %8, %9)")
                .arg(win)
                .arg(r.x())
                .arg(r.y())
                .arg(r.width())
                .arg(r.height())
                .arg(g.orientation)
                .arg(g.minimum)
                .arg(g.maximum)
                .arg(flags);
        }

        if (g.type
            == QStringLiteral(
                "Scrollbar")) {
            return QStringLiteral(
                "API->gui->gadgets->scrollbar_create(%1, %2, %3, %4, %5, %6, %7, %8, 1, 10, %9)")
                .arg(win)
                .arg(r.x())
                .arg(r.y())
                .arg(r.width())
                .arg(r.height())
                .arg(g.orientation)
                .arg(g.minimum)
                .arg(g.maximum)
                .arg(flags);
        }

        if (g.type
            == QStringLiteral(
                "ProgressBar")) {
            return QStringLiteral(
                "API->gui->gadgets->progbar_create(%1, %2, %3, %4, %5, %6)")
                .arg(win)
                .arg(r.x())
                .arg(r.y())
                .arg(r.width())
                .arg(r.height())
                .arg(flags);
        }

        if (g.type
            == QStringLiteral(
                "TextBox")) {
            return QStringLiteral(
                "API->gui->gadgets->textbox_create(%1, %2, %3, %4, %5, \"%6\", %7, %8)")
                .arg(win)
                .arg(r.x())
                .arg(r.y())
                .arg(r.width())
                .arg(r.height())
                .arg(text)
                .arg(typeFlags)
                .arg(flags);
        }

        if (g.type
            == QStringLiteral(
                "TextArea")) {
            return QStringLiteral(
                "API->gui->gadgets->textarea_create(%1, %2, %3, %4, %5, \"%6\", %7, %8)")
                .arg(win)
                .arg(r.x())
                .arg(r.y())
                .arg(r.width())
                .arg(r.height())
                .arg(text)
                .arg(typeFlags)
                .arg(flags);
        }

        if (g.type
            == QStringLiteral(
                "ListBox")) {
            return QStringLiteral(
                "API->gui->gadgets->listbox_create(%1, %2, %3, %4, %5, %6)")
                .arg(win)
                .arg(r.x())
                .arg(r.y())
                .arg(r.width())
                .arg(r.height())
                .arg(flags);
        }

        if (g.type
            == QStringLiteral(
                "Canvas")) {
            const QString drawType =
                g.typeFlags.trimmed().isEmpty()
                    ? QStringLiteral(
                          "CNV_RECT")
                    : g.typeFlags.trimmed();

            return QStringLiteral(
                "API->gui->gadgets->canvas_create(%1, %2, %3, %4, %5, %6, %7)")
                .arg(win)
                .arg(r.x())
                .arg(r.y())
                .arg(r.width())
                .arg(r.height())
                .arg(drawType)
                .arg(flags);
        }

        if (g.type
            == QStringLiteral(
                "GridSelect")) {
            return QStringLiteral(
                "API->gui->gadgets->gridselect_create(%1, %2, %3, %4, %5, %6, %7, %8, %9)")
                .arg(win)
                .arg(r.x())
                .arg(r.y())
                .arg(g.cellWidth)
                .arg(g.cellHeight)
                .arg(g.cellsX)
                .arg(g.cellsY)
                .arg(typeFlags)
                .arg(flags);
        }

        if (g.type
            == QStringLiteral(
                "BitmapView")) {
            const QString bitmapFlags =
                g.typeFlags.trimmed().isEmpty()
                    ? QStringLiteral(
                          "BVF_SHOW_FRAME | BVF_SRC_ROWMAJOR")
                    : g.typeFlags.trimmed();

            return QStringLiteral(
                "API->gui->gadgets->bitmapview_create(%1, %2, %3, %4, %5, %6, %7, %8, %9)")
                .arg(win)
                .arg(r.x())
                .arg(r.y())
                .arg(r.width())
                .arg(r.height())
                .arg(g.bitmapWidth)
                .arg(g.bitmapHeight)
                .arg(bitmapFlags)
                .arg(flags);
        }

        return QStringLiteral(
            "API->gui->gadgets->button_create(%1, %2, %3, %4, %5, \"%6\", %7)")
            .arg(win)
            .arg(r.x())
            .arg(r.y())
            .arg(r.width())
            .arg(r.height())
            .arg(text, flags);
    }

    bool generateCFile(bool showMessage, bool chooseDestination = false)
    {
        bool sketch = m_detached;
        if (chooseDestination) {
            QMessageBox box(QMessageBox::Question, QObject::tr("Generate GUI Source"),
                QObject::tr("Where should the generated source go?"),
                QMessageBox::NoButton, this);
            QPushButton *sketchButton = box.addButton(QObject::tr("Create / Update Sketch (.uis)"), QMessageBox::AcceptRole);
            QPushButton *sourceButton = box.addButton(QObject::tr("Overwrite / Generate C (.c)"), QMessageBox::AcceptRole);
            box.addButton(QMessageBox::Cancel);
            box.setDefaultButton(m_detached ? sketchButton : sourceButton);
            box.exec();
            if (box.clickedButton() == sketchButton) sketch = true;
            else if (box.clickedButton() == sourceButton) sketch = false;
            else return false;
        }
        if (!sketch && chooseDestination) {
            const QString chosen = QFileDialog::getSaveFileName(this,
                QObject::tr("Choose C source file"), outputPath(false),
                QObject::tr("C source (*.c)"));
            if (chosen.isEmpty()) return false;
            if (QFileInfo(chosen).suffix().compare(QStringLiteral("c"), Qt::CaseInsensitive) != 0) {
                QMessageBox::warning(this, QObject::tr("GUI Designer"), QObject::tr("Choose a .c filename."));
                return false;
            }
            m_sourceName = QDir(QFileInfo(m_filePath).absolutePath()).relativeFilePath(chosen);
            setModified(true);
        }
        if (!validateProjectWindows(!sketch)) return false;
        for (const GuiDesignerGadget &g : std::as_const(m_gadgets)) {
            if (g.type == QStringLiteral("Timer") && g.timerAutoStart
                && g.onActivate.trimmed().isEmpty()) {
                QMessageBox::warning(this, QObject::tr("Timer callback required"),
                    QObject::tr("Timer %1 starts with the window, so it requires an On tick callback.")
                        .arg(g.name));
                return false;
            }
        }
        // IPC is one OS-owned mailbox per applet; multiple Messenger timers in
        // the same window would race each other while consuming messages.
        int messengerCount = 0;
        QHash<QString, QString> ipcMessengerTargets;
        for (const GuiDesignerGadget &g : std::as_const(m_gadgets)) {
            if (g.type != QStringLiteral("Messenger")) continue;
            ipcMessengerTargets.insert(g.name, g.ipcTargetApp.trimmed());
            if (!g.ipcReceive) continue;
            ++messengerCount;
            if (g.onActivate.trimmed().isEmpty()) {
                QMessageBox::warning(this, QObject::tr("Messenger callback required"),
                    QObject::tr("Receiver Messenger %1 needs an On message callback.").arg(g.name));
                return false;
            }
        }
        if (messengerCount > 1) {
            QMessageBox::warning(this, QObject::tr("Multiple Messenger receivers"),
                QObject::tr("Use one receiving Messenger per design. IPC has one mailbox per applet."));
            return false;
        }
        for (const GuiDesignerGadget &g : std::as_const(m_gadgets)) {
            if (g.type != QStringLiteral("Button") || g.ipcSendTarget.isEmpty()) continue;
            if (!ipcMessengerTargets.contains(g.ipcSendTarget)
                || ipcMessengerTargets.value(g.ipcSendTarget).isEmpty()) {
                QMessageBox::warning(this, QObject::tr("Missing IPC target"),
                    QObject::tr("Button %1 needs a Messenger with a Target applet filename.").arg(g.name));
                return false;
            }
            if (g.onActivate.isEmpty()) {
                QMessageBox::warning(this, QObject::tr("Missing IPC button callback"),
                    QObject::tr("Button %1 needs an activation callback to send IPC.").arg(g.name));
                return false;
            }
            if (g.ipcSendText.toUtf8().size() > 64) {
                QMessageBox::warning(this, QObject::tr("IPC text too long"),
                    QObject::tr("Button %1 message exceeds 64 UTF-8 bytes.").arg(g.name));
                return false;
            }
        }
        // UART1 is physically a single serial port; don't generate duplicate leases.
        int uart1Components = 0;
        for (const GuiDesignerGadget &g : std::as_const(m_gadgets)) {
            if (g.type == QStringLiteral("UART1")) {
                ++uart1Components;
                if (g.onActivate.isEmpty()) {
                    QMessageBox::warning(this, QObject::tr("UART1 callback required"),
                        QObject::tr("UART1 %1 requires an On data callback.").arg(g.name));
                    return false;
                }
            }
        }
        if (uart1Components > 1) {
            QMessageBox::warning(this, QObject::tr("UART1 conflict"),
                QObject::tr("Only one virtual UART1 controller belongs in a window."));
            return false;
        }
        // Passive window input listeners use exactly one callback per type;
        // their event routing is through the window proc (never an IRQ).
        for (const QString &kind : {QStringLiteral("KBInput"), QStringLiteral("MSInput")}) {
            int count = 0;
            for (const GuiDesignerGadget &g : std::as_const(m_gadgets)) {
                if (g.type != kind) continue;
                ++count;
                if (g.onActivate.trimmed().isEmpty()) {
                    QMessageBox::warning(this, QObject::tr("Input callback required"),
                        QObject::tr("%1 %2 requires an input callback.").arg(kind, g.name));
                    return false;
                }
            }
            if (count > 1) {
                QMessageBox::warning(this, QObject::tr("Duplicate input listener"),
                    QObject::tr("Only one %1 listener is needed per window.").arg(kind));
                return false;
            }
        }
        // The sample data and music player are global resources on SIDBOX.
        // Within one design, a PCM channel must have a single owner.
        QSet<int> usedSfxChannels;
        QSet<QString> mediaNames;
        for (const GuiDesignerGadget &g : std::as_const(m_gadgets)) {
            if (g.type != QStringLiteral("Media")) continue;
            mediaNames.insert(g.name);
            if (g.mediaMode == QStringLiteral("SFX") && g.mediaEmbedSfx) {
                if (g.mediaEmbeddedPcm.isEmpty()) {
                    QMessageBox::warning(this, QObject::tr("Embedded sound required"),
                        QObject::tr("Import a WAV into Media %1 before generating.").arg(g.name));
                    return false;
                }
            } else if (g.mediaFile.trimmed().isEmpty()) {
                QMessageBox::warning(this, QObject::tr("Media source required"),
                    QObject::tr("Media %1 needs a SIDBOX filename before generating.").arg(g.name));
                return false;
            }
            if (g.mediaMode == QStringLiteral("SFX")) {
                if (g.mediaChannel < 0 || g.mediaChannel > 7 || usedSfxChannels.contains(g.mediaChannel)) {
                    QMessageBox::warning(this, QObject::tr("SFX channel conflict"),
                        QObject::tr("Each SFX Media object needs a unique channel (0–7). Check %1.").arg(g.name));
                    return false;
                }
                usedSfxChannels.insert(g.mediaChannel);
            }
        }
        for (const GuiDesignerGadget &g : std::as_const(m_gadgets)) {
            if (g.type == QStringLiteral("Button") && !g.mediaTarget.isEmpty()) {
                if (!mediaNames.contains(g.mediaTarget)) {
                    QMessageBox::warning(this, QObject::tr("Missing Media target"),
                        QObject::tr("Button %1 references a missing Media object: %2")
                            .arg(g.name, g.mediaTarget));
                    return false;
                }
                if (g.onActivate.isEmpty()) {
                    QMessageBox::warning(this, QObject::tr("Missing callback"),
                        QObject::tr("Button %1 must have an On activate callback for its Media action.").arg(g.name));
                    return false;
                }
            }
        }
        QSet<QString> dialogNames;
        QSet<QString> dialogCallbackNames;
        for (const GuiDesignerGadget &g : std::as_const(m_gadgets)) {
            if (g.type != QStringLiteral("FileRequester") && g.type != QStringLiteral("MessageBox")) continue;
            dialogNames.insert(g.name);
            if (g.onActivate.trimmed().isEmpty()
                || (g.type == QStringLiteral("FileRequester") && g.onChange.trimmed().isEmpty())
                || dialogCallbackNames.contains(g.onActivate)
                || (!g.onChange.isEmpty() && dialogCallbackNames.contains(g.onChange))
                || g.onActivate == g.onChange) {
                QMessageBox::warning(this, QObject::tr("Dialog callbacks"),
                    QObject::tr("Dialog %1 needs unique, non-empty result callbacks.").arg(g.name));
                return false;
            }
            dialogCallbackNames.insert(g.onActivate);
            if (g.type == QStringLiteral("FileRequester")) dialogCallbackNames.insert(g.onChange);
        }
        for (const GuiDesignerGadget &g : std::as_const(m_gadgets)) {
            if (g.type == QStringLiteral("Button") && !g.dialogTarget.isEmpty()) {
                if (!dialogNames.contains(g.dialogTarget) || g.onActivate.isEmpty()) {
                    QMessageBox::warning(this, QObject::tr("Missing dialog target"),
                        QObject::tr("Button %1 needs an existing dialog target and an activation callback.").arg(g.name));
                    return false;
                }
            }
        }
        const QString cPath = outputPath(sketch);
        if (!sketch && !canWriteGeneratedHeader(cPath)) return false;
        if (sketch && m_sketchName.isEmpty()) {
            m_sketchName = QFileInfo(cPath).fileName();
            setModified(true);
        }
        if (!sketch && !m_detached && m_sourceName.isEmpty()) {
            m_sourceName = QFileInfo(cPath).fileName();
            setModified(true);
        }

        QString oldSource;

        if (beforeGenerate
            && !beforeGenerate(cPath)) {
            return false;
        }

        if (!sketch && QFile::exists(cPath)) {
            if (QMessageBox::warning(this, QObject::tr("Overwrite custom source?"),
                    QObject::tr("Generating will replace %1. Custom code outside protected USER blocks may be lost. A .bak copy will be saved first.")
                        .arg(QDir::toNativeSeparators(cPath)),
                    QMessageBox::Yes | QMessageBox::Cancel, QMessageBox::Cancel) != QMessageBox::Yes)
                return false;
            QFile::remove(cPath + QStringLiteral(".bak"));
            if (!QFile::copy(cPath, cPath + QStringLiteral(".bak"))) {
                QMessageBox::warning(this, QObject::tr("Backup failed"), QObject::tr("Source was not overwritten because the backup failed."));
                return false;
            }
        }

        QFile old(cPath);
        if (old.open(
                QIODevice::ReadOnly
                | QIODevice::Text)) {
            oldSource =
                QString::fromUtf8(
                    old.readAll());
        }

        /*
         * Build the routing plan ONCE for this generation. Every ordinary
         * gadget is assigned to exactly one delivery mechanism:
         *   WindowProc: CGMSG_GADGET / CGEVT_* dispatch
         *   Direct:     API->gui->gadgets->set_callback() wrapper
         *
         * Per-gadget -1 inherits the window default; 0 and 1 override it.
         * Timers, dialogs, Media, and TabGroup's private header buttons have
         * their own event mechanisms and must not enter either collection.
         * Keeping one plan for prototypes, registration and dispatch prevents
         * those stages from drifting apart as the generator evolves.
         */
        QSet<const GuiDesignerGadget *> windowProcGadgets;
        QSet<const GuiDesignerGadget *> directCallbackGadgets;
        for (const GuiDesignerGadget &g : std::as_const(m_gadgets)) {
            if (isVirtualDesignerGadget(g.type)
                || g.type == QStringLiteral("TabGroup"))
                continue;
            if (gadgetUsesDirectCallbacks(g))
                directCallbackGadgets.insert(&g);
            else
                windowProcGadgets.insert(&g);
        }

        QStringList callbackKeys;
        callbackKeys
            << QStringLiteral(
                   "WINDOW_CLOSE");

        QStringList gadgetCallbacks;
        QStringList timerCallbacks;
        QStringList messengerCallbacks;
        QStringList uart1DataCallbacks;   // Only these need the UART RX usage memo.
        QStringList inputCallbacks;      // Virtual keyboard/mouse events (shared signature).
        QStringList dialogCallbackNamesForGeneration;
        QStringList directGadgetCallbacks;
        QStringList menuCallbacks;

        for (const GuiDesignerGadget &g :
             std::as_const(m_gadgets)) {
            if (g.type == QStringLiteral("Media")) continue;
            if (g.type == QStringLiteral("FileRequester") || g.type == QStringLiteral("MessageBox")) {
                callbackKeys << g.onActivate;
                dialogCallbackNamesForGeneration << g.onActivate;
                if (g.type == QStringLiteral("FileRequester")) {
                    callbackKeys << g.onChange;
                    dialogCallbackNamesForGeneration << g.onChange;
                }
                continue;
            }
            if (g.type == QStringLiteral("KBInput") || g.type == QStringLiteral("MSInput")) {
                if (!g.onActivate.isEmpty()) {
                    callbackKeys << g.onActivate;
                    inputCallbacks << g.onActivate;
                }
                continue;
            }
            if (g.type == QStringLiteral("UART1")) {
                if (!g.onActivate.isEmpty()) {
                    callbackKeys << g.onActivate;
                    timerCallbacks << g.onActivate;
                    uart1DataCallbacks << g.onActivate;
                }
                continue;
            }
            if (g.type == QStringLiteral("Messenger")) {
                if (g.ipcReceive && !g.onActivate.isEmpty()) {
                    callbackKeys << g.onActivate;
                    messengerCallbacks << g.onActivate;
                }
                continue;
            }
            if (g.type == QStringLiteral("Timer")) {
                if (!g.onActivate.isEmpty()) {
                    callbackKeys << g.onActivate;
                    timerCallbacks << g.onActivate;
                }
                continue;
            }
            if (!g.onActivate.isEmpty()) {
                callbackKeys << g.onActivate;
                gadgetCallbacks << g.onActivate;

                if (directCallbackGadgets.contains(&g)) {
                    directGadgetCallbacks
                        << g.onActivate;
                }
            }

            if (!g.onChange.isEmpty()) {
                callbackKeys << g.onChange;
                gadgetCallbacks << g.onChange;

                if (directCallbackGadgets.contains(&g)) {
                    directGadgetCallbacks
                        << g.onChange;
                }
            }
        }

        for (const GuiDesignerMenuTitle &menu :
             std::as_const(m_menus)) {
            for (const GuiDesignerMenuItem &item :
                 menu.items) {
                if (!isMenuSeparatorText(
                        item.text)
                    && !item.callback.isEmpty()) {
                    callbackKeys
                        << item.callback;
                    menuCallbacks
                        << item.callback;
                }
            }
        }

        // These sections are generated by the Designer, not callbacks.
        // Keep them among the active USER keys so preserved custom functions
        // and variables never get put into the orphan-callback #if 0 block.
        if (callbackKeys.contains(QStringLiteral("GLOBAL_VARIABLES"))
            || callbackKeys.contains(QStringLiteral("BEFORE_CLOSE"))
            || callbackKeys.contains(QStringLiteral("custom_code"))) {
            QMessageBox::warning(this, QObject::tr("Reserved callback name"),
                QObject::tr("GLOBAL_VARIABLES, BEFORE_CLOSE and custom_code "
                            "are reserved for protected generated sections. "
                            "Rename this callback to avoid a user-block collision."));
            return false;
        }
        callbackKeys << QStringLiteral("GLOBAL_VARIABLES")
                     << QStringLiteral("BEFORE_CLOSE")
                     << QStringLiteral("custom_code");

        callbackKeys.removeDuplicates();
        gadgetCallbacks.removeDuplicates();
        timerCallbacks.removeDuplicates();
        messengerCallbacks.removeDuplicates();
        uart1DataCallbacks.removeDuplicates();
        inputCallbacks.removeDuplicates();
        dialogCallbackNamesForGeneration.removeDuplicates();
        directGadgetCallbacks.removeDuplicates();
        // The generated helper is file-local and is intended to be CALLED
        // from callbacks, not declared as one. Prevent duplicate C symbols.
        if (gadgetCallbacks.contains(QStringLiteral("CloseWindow"))
            || timerCallbacks.contains(QStringLiteral("CloseWindow"))
            || messengerCallbacks.contains(QStringLiteral("CloseWindow"))
            || menuCallbacks.contains(QStringLiteral("CloseWindow"))
            || dialogCallbackNamesForGeneration.contains(QStringLiteral("CloseWindow"))
            || inputCallbacks.contains(QStringLiteral("CloseWindow"))) {
            QMessageBox::warning(this, QObject::tr("Reserved callback name"),
                QObject::tr("CloseWindow is the generated window cleanup helper. "
                            "Choose another callback name, then call CloseWindow() "
                            "from its USER block."));
            return false;
        }
        // Different callback types have incompatible C signatures.
        for (const QString &cb : std::as_const(timerCallbacks)) {
            if (gadgetCallbacks.contains(cb) || menuCallbacks.contains(cb) || messengerCallbacks.contains(cb)) {
                QMessageBox::warning(this, QObject::tr("Timer callback collision"),
                    QObject::tr("Timer callback %1 is also used by a gadget or menu. "
                                "Give it a unique name.").arg(cb));
                return false;
            }
        }
        menuCallbacks.removeDuplicates();
        for (const QString &cb : std::as_const(inputCallbacks)) {
            if (gadgetCallbacks.contains(cb) || menuCallbacks.contains(cb)
                || timerCallbacks.contains(cb) || messengerCallbacks.contains(cb) || dialogCallbackNamesForGeneration.contains(cb)) {
                QMessageBox::warning(this, QObject::tr("Input callback collision"),
                    QObject::tr("Input callback %1 conflicts with a gadget, menu, timer, or dialog callback.").arg(cb));
                return false;
            }
        }
        for (const QString &cb : std::as_const(dialogCallbackNamesForGeneration)) {
            if (gadgetCallbacks.contains(cb) || menuCallbacks.contains(cb) || timerCallbacks.contains(cb) || messengerCallbacks.contains(cb)) {
                QMessageBox::warning(this, QObject::tr("Dialog callback collision"),
                    QObject::tr("Dialog callback %1 also belongs to another gadget/menu/timer.").arg(cb));
                return false;
            }
        }

        for (const QString &cb : std::as_const(messengerCallbacks)) {
            if (gadgetCallbacks.contains(cb) || menuCallbacks.contains(cb)
                || timerCallbacks.contains(cb) || inputCallbacks.contains(cb)
                || dialogCallbackNamesForGeneration.contains(cb)) {
                QMessageBox::warning(this, QObject::tr("Messenger callback collision"),
                    QObject::tr("Messenger callback %1 conflicts with another callback type.").arg(cb));
                return false;
            }
        }

        // Preserve this entire section without indentation/whitespace
        // normalisation: it may contain preprocessor directives, declarations,
        // and user comments.  A damaged marker must never erase user globals.
        const QString globalsBegin =
            QStringLiteral("/* <SIDBOX-GUI:USER GLOBAL_VARIABLES> */");
        const QString globalsEnd =
            QStringLiteral("/* </SIDBOX-GUI:USER GLOBAL_VARIABLES> */");
        const int globalsStart = oldSource.indexOf(globalsBegin);
        const int globalsFinish = oldSource.indexOf(globalsEnd);
        const bool brokenGlobals =
            oldSource.count(globalsBegin) > 1
            || oldSource.count(globalsEnd) > 1
            || (globalsStart < 0) != (globalsFinish < 0)
            || (globalsStart >= 0 && globalsFinish <= globalsStart)
            || (globalsStart < 0 && oldSource.contains(
                    QStringLiteral("SIDBOX-GUI:USER GLOBAL_VARIABLES")))
            || (globalsFinish < 0 && oldSource.contains(
                    QStringLiteral("/SIDBOX-GUI:USER GLOBAL_VARIABLES")));
        if (brokenGlobals) {
            QMessageBox::warning(this, QObject::tr("Protected variables section"),
                QObject::tr("The custom-variable USER markers in %1 are "
                            "missing, duplicated, or damaged.\n\n"
                            "Generation was cancelled to protect your code. "
                            "Please restore both markers from your backup.")
                    .arg(QDir::toNativeSeparators(cPath)));
            return false;
        }
        const QString preservedGlobals = globalsStart >= 0
            ? oldSource.mid(globalsStart + globalsBegin.size(),
                            globalsFinish - (globalsStart + globalsBegin.size()))
            : QStringLiteral(
                "\n/* Private to this .c: static int local_count = 0; */\n"
                "/* Shared with other .c files: int shared_count = 0; */\n"
                "/* For shared variables, add extern declarations inside the "
                "matching .h USER HEADER block. */\n");

        // A protected close hook must never be silently dropped because
        // one of its markers was edited, copied, or removed by accident.
        const QString beforeCloseBegin =
            QStringLiteral("/* <SIDBOX-GUI:USER BEFORE_CLOSE> */");
        const QString beforeCloseEnd =
            QStringLiteral("/* </SIDBOX-GUI:USER BEFORE_CLOSE> */");
        const int beforeCloseStart = oldSource.indexOf(beforeCloseBegin);
        const int beforeCloseFinish = oldSource.indexOf(beforeCloseEnd);
        if (oldSource.count(beforeCloseBegin) > 1
            || oldSource.count(beforeCloseEnd) > 1
            || (beforeCloseStart < 0) != (beforeCloseFinish < 0)
            || (beforeCloseStart >= 0 && beforeCloseFinish <= beforeCloseStart)
            || (beforeCloseStart < 0 && oldSource.contains(
                QStringLiteral("SIDBOX-GUI:USER BEFORE_CLOSE")))
            || (beforeCloseFinish < 0 && oldSource.contains(
                QStringLiteral("/SIDBOX-GUI:USER BEFORE_CLOSE")))) {
            QMessageBox::warning(this, QObject::tr("Protected window close section"),
                QObject::tr("The BEFORE_CLOSE USER markers in %1 are "
                            "missing, duplicated, or damaged.\n\n"
                            "Generation was cancelled to protect your code.")
                    .arg(QDir::toNativeSeparators(cPath)));
            return false;
        }

        // User helper functions belong at the very end of each generated .c.
        // Unlike callback bodies, keep this section exactly as written:
        // indentation, preprocessor directives and blank lines matter.
        // A partial or duplicated marker must not silently erase user code.
        const QString customCodeBegin =
            QStringLiteral("/* <SIDBOX-GUI:USER custom_code> */");
        const QString customCodeEnd =
            QStringLiteral("/* </SIDBOX-GUI:USER custom_code> */");
        const int customCodeStart = oldSource.indexOf(customCodeBegin);
        const int customCodeFinish = oldSource.indexOf(customCodeEnd);
        if (oldSource.count(customCodeBegin) > 1
            || oldSource.count(customCodeEnd) > 1
            || (customCodeStart < 0) != (customCodeFinish < 0)
            || (customCodeStart >= 0 && customCodeFinish <= customCodeStart)
            || (customCodeStart < 0 && oldSource.contains(
                    QStringLiteral("SIDBOX-GUI:USER custom_code")))
            || (customCodeFinish < 0 && oldSource.contains(
                    QStringLiteral("/SIDBOX-GUI:USER custom_code")))) {
            QMessageBox::warning(this, QObject::tr("Protected custom code section"),
                QObject::tr("The custom_code USER markers in %1 are "
                            "missing, duplicated or damaged.\n\n"
                            "Generation was cancelled to protect your code. "
                            "Restore both markers from your backup.")
                    .arg(QDir::toNativeSeparators(cPath)));
            return false;
        }
        const QString preservedCustomCode = customCodeStart >= 0
            ? oldSource.mid(customCodeStart + customCodeBegin.size(),
                            customCodeFinish - (customCodeStart + customCodeBegin.size()))
            : QStringLiteral("\n/* TODO: programmer callback code */\n");

        const QHash<QString, QString> saved =
            preservedUserBlocks(
                oldSource,
                callbackKeys);

        const QString win =
            safeCIdentifier(
                m_window.name,
                QStringLiteral(
                    "MainWindow"));

        const QString proc =
            win
            + QStringLiteral(
                "_WindowProc");

        // Resolve linked windows from their saved .sbui, not a cached C name.
        // This keeps the generated call aligned when a target window is renamed.
        QHash<QString, QString> linkedCallbacks;
        QSet<QString> linkedFunctions;
        const QDir root(designProjectRoot());
        for (const GuiDesignerGadget &g : std::as_const(m_gadgets)) {
            if (g.type != QStringLiteral("Button") || g.openWindowFile.isEmpty()) continue;
            QFile file(root.absoluteFilePath(g.openWindowFile));
            if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return false;
            const QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
            const QString targetName = doc.object().value(QStringLiteral("window"))
                                        .toObject().value(QStringLiteral("name")).toString();
            if (!doc.isObject() || targetName.isEmpty()) return false;
            const QString createFunction = windowEntryForDesign(root.absoluteFilePath(g.openWindowFile));
            if (createFunction.isEmpty()) return false;
            linkedCallbacks.insert(safeCIdentifier(g.onActivate, QStringLiteral("OnActivate")),
                                   createFunction);
            linkedFunctions.insert(createFunction);
        }

        QHash<QString, QString> mediaLinkedActions;
        for (const GuiDesignerGadget &g : std::as_const(m_gadgets)) {
            if (g.type != QStringLiteral("Button") || g.mediaTarget.isEmpty()) continue;
            const QString cb = safeCIdentifier(g.onActivate, QStringLiteral("OnActivate"));
            const QString name = safeCIdentifier(g.mediaTarget, QStringLiteral("media"));
            const QString call = name + (g.mediaAction == QStringLiteral("Stop")
                ? QStringLiteral("_Stop();") : QStringLiteral("_Play();"));
            if (mediaLinkedActions.contains(cb) && mediaLinkedActions.value(cb) != call) {
                QMessageBox::warning(this, QObject::tr("Shared callback conflict"),
                    QObject::tr("Callback %1 is used by buttons with different Media actions. "
                                "Give those buttons separate callback names.").arg(cb));
                return false;
            }
            mediaLinkedActions.insert(cb, call);
        }

        QHash<QString, QString> ipcLinkedActions;
        for (const GuiDesignerGadget &g : std::as_const(m_gadgets)) {
            if (g.type != QStringLiteral("Button") || g.ipcSendTarget.isEmpty()) continue;
            const QString cb = safeCIdentifier(g.onActivate, QStringLiteral("OnActivate"));
            const QString name = safeCIdentifier(g.ipcSendTarget, QStringLiteral("messenger"));
            const QString call = QStringLiteral("(void)%1_SendText(%2u, \"%3\");")
                .arg(name).arg(qBound(0, g.ipcSendType, 65535))
                .arg(escapedCString(g.ipcSendText));
            if ((ipcLinkedActions.contains(cb) && ipcLinkedActions.value(cb) != call)
                || linkedCallbacks.contains(cb) || mediaLinkedActions.contains(cb)) {
                QMessageBox::warning(this, QObject::tr("Conflicting IPC button actions"),
                    QObject::tr("Button callback %1 has incompatible built-in actions. Use a separate callback name.").arg(cb));
                return false;
            }
            ipcLinkedActions.insert(cb, call);
        }

        QHash<QString, QString> dialogLinkedActions;
        for (const GuiDesignerGadget &g : std::as_const(m_gadgets)) {
            if (g.type != QStringLiteral("Button") || g.dialogTarget.isEmpty()) continue;
            const QString cb = safeCIdentifier(g.onActivate, QStringLiteral("OnActivate"));
            const QString call = safeCIdentifier(g.dialogTarget, QStringLiteral("dialog")) + QStringLiteral("_Show();");
            if ((dialogLinkedActions.contains(cb) && dialogLinkedActions.value(cb) != call)
                || mediaLinkedActions.contains(cb) || ipcLinkedActions.contains(cb)
                || linkedCallbacks.contains(cb)) {
                QMessageBox::warning(this, QObject::tr("Shared callback conflict"),
                    QObject::tr("Button callback %1 has conflicting built-in actions. Give the buttons separate callbacks.").arg(cb));
                return false;
            }
            dialogLinkedActions.insert(cb, call);
        }

        // Each virtual TabGroup reserves a separate 1..255 CoderGirl group
        // for every page. Group 0 remains visible at all times.
        QHash<QString,int> tabBase;
        int nextTabGroupId = 1;
        for (const GuiDesignerGadget &g : std::as_const(m_gadgets)) {
            if (g.type == QStringLiteral("TabGroup")) {
                tabBase.insert(g.name, nextTabGroupId);
                nextTabGroupId += designerTabTitles(g).size();
            }
        }

        QString out;
        QTextStream s(&out);

        s << "/* AUTO-GENERATED by Sidbox IDE GUI Designer.\n"
             "   Target: SIDBOX applet API (apis.h), not firmware-private CoderGirl headers.\n"
             "   Edit USER blocks only; designer regeneration replaces generated sections. */\n\n";

        s << "#include \"apis.h\"\n";
        if (!sketch)
            s << "#include \"" << QFileInfo(cPath).completeBaseName() << ".h\"\n";
        s << "#include <stddef.h>\n"
             "#include <stdint.h>\n"
             "#include <stdlib.h>\n"
             "#include <string.h>\n";
        if (!dialogNames.isEmpty())
            s << "#include <stdio.h>\n"; // printf() in generated dialog demos.
        s << "\n";

        // The designer may be updated before the applet SDK has acquired the
        // new flag. Define the agreed-upon bit only for generated windows that
        // actually use it. Once the SDK defines it, that definition wins.
        for (const GuiDesignerGadget &g : std::as_const(m_gadgets)) {
            if (g.type == QStringLiteral("Label")
                && designerWindowFlag(g.flags, QStringLiteral("GAD_TOOL_TRANSPARENT"))) {
                s << "#ifndef GAD_TOOL_TRANSPARENT\n"
                     "#define GAD_TOOL_TRANSPARENT (1u << 16)\n"
                     "#endif\n\n";
                break;
            }
        }

        // Embedded samples live in <design>res/media_sfx.c, not this source.
        // .sbui stores PCM8 XOR 0x80 for compatibility; generated media_sfx.c
        // reverses that encoding to the unsigned PCM8 bytes BETH actually mixes.
        const QString samplePrefix = safeCIdentifier(
            QFileInfo(m_filePath).completeBaseName(), QStringLiteral("window"));
        const QString bitmapPrefix = samplePrefix;
        // Keep generated binary assets out of the human-readable window C file.
        const QFileInfo designInfo(m_filePath);
        const QString resourceDir = designInfo.dir().absoluteFilePath(
            designInfo.completeBaseName() + QStringLiteral("res"));
        const QString bitmapResourcePath = QDir(resourceDir).filePath(QStringLiteral("bitmapview.c"));
        const QString mediaResourcePath = QDir(resourceDir).filePath(QStringLiteral("media_sfx.c"));
        for (const GuiDesignerGadget &g : std::as_const(m_gadgets)) {
            if (g.type != QStringLiteral("Media") || g.mediaMode != QStringLiteral("SFX")
                || !g.mediaEmbedSfx) continue;
            const QString symbol = samplePrefix + QStringLiteral("_")
                + safeCIdentifier(g.name, QStringLiteral("media")) + QStringLiteral("_pcm");
            s << "extern const uint8_t " << symbol << "[];\n"
              << "extern const uint32_t " << symbol << "_length;\n";
        }
        // Embedded and demo BitmapView storage lives in bitmapview.c.
        // A design-specific prefix prevents cross-window global symbol clashes.
        for (const GuiDesignerGadget &g : std::as_const(m_gadgets)) {
            if (g.type != QStringLiteral("BitmapView")) continue;
            const QString n = safeCIdentifier(g.name, QStringLiteral("bitmap"));
            const QString source = bitmapPrefix + QStringLiteral("_")
                + safeCIdentifier(g.bitmapSource, n + QStringLiteral("_pixels"));
            if (!g.bitmapPixels.isEmpty() || isDesignerDemoBitmap(g)) {
                s << "extern uint8_t " << source << "[];\n";
            }
            if (isDesignerDemoBitmap(g)) {
                s << "extern void " << bitmapPrefix << "_" << n << "_InitDemoBitmap(void);\n";
            }
        }
        s << "\n";

        QStringList sortedFunctions = linkedFunctions.values();
        sortedFunctions.sort();
        for (const QString &create : std::as_const(sortedFunctions)) {
            s << "extern void " << create << "(void);\n";
        }
        if (!linkedFunctions.isEmpty()) s << "\n";

        /*
         * Application GUI handles are deliberately file-local. The real applet
         * examples also keep Window/Gadget/Menu state static.
         */
        s << "static CGWindow "
          << win
          << ";\n"
             "static uint8_t "
          << win
          << "_is_open = 0u;\n"
             "static uint8_t " << win << "_is_closing = 0u;\n";

        const bool hasDialogs = !dialogNames.isEmpty();
        if (hasDialogs) {
            s << "static CGWindow " << win << "_active_dialog = (CGWindow)0xFFu;\n"
              << "static uint8_t " << win << "_dialog_block_owner = 0u;\n";
        }
        for (const GuiDesignerGadget &g :
             m_gadgets) {
            if (g.type == QStringLiteral("Media") || g.type == QStringLiteral("FileRequester")
                || g.type == QStringLiteral("MessageBox") || g.type == QStringLiteral("UART1")
                || g.type == QStringLiteral("Messenger")
                || g.type == QStringLiteral("KBInput") || g.type == QStringLiteral("MSInput")) continue;
            if (g.type == QStringLiteral("Timer")) {
                s << "static CGTimer " << safeCIdentifier(g.name, QStringLiteral("timer"))
                  << " = CGTIMER_INVALID;\n";
                continue;
            }
            s << "static CGGadget "
              << safeCIdentifier(
                     g.name,
                     QStringLiteral(
                         "gadget"))
              << ";\n";
        }

        for (const GuiDesignerGadget &g : std::as_const(m_gadgets)) {
            if (g.type == QStringLiteral("Messenger") && g.ipcReceive) {
                s << "static CGTimer " << safeCIdentifier(g.name, QStringLiteral("messenger"))
                  << "_poll_timer = CGTIMER_INVALID;\n";
            }
        }

        // Generated physical tab header buttons (the TabGroup itself is
        // virtual: a bevel and manually managed toggle CoderGirl buttons).
        for (const GuiDesignerGadget &g : std::as_const(m_gadgets)) {
            if (g.type != QStringLiteral("TabGroup")) continue;
            const QString n = safeCIdentifier(g.name, QStringLiteral("tabs"));
            for (int page = 0; page < designerTabTitles(g).size(); ++page)
                s << "static CGGadget " << n << "_tab_" << page << ";\n";
        }

        /*
         * ListBox data lives in a separate caller-owned ItemLists_t model.
         * Keep the model static so it remains alive for as long as the Window
         * and its ListBox gadget are alive.
         */
        for (const GuiDesignerGadget &g :
             m_gadgets) {
            if (g.type != QStringLiteral("ListBox")
                || g.listItems.isEmpty()) {
                continue;
            }

            const QString n =
                safeCIdentifier(
                    g.name,
                    QStringLiteral("listbox"));

            s << "static ItemLists_t "
              << n
              << "_items;\n";
        }

        if (!m_menus.isEmpty()) {
            s << "static cg_menu_t "
              << win
              << "_Menu;\n";

            for (const GuiDesignerMenuTitle &menu :
                 m_menus) {
                for (const GuiDesignerMenuItem &item :
                     menu.items) {
                    s << "static cg_menuitem_t "
                      << safeCIdentifier(
                             item.name,
                             QStringLiteral(
                                 "menuItem"))
                      << ";\n";
                }
            }
        }

        // File-scope state is accessible by every callback in this GUI
        // translation unit.  Non-static definitions can also be shared with
        // other .c files using an extern declaration in the generated header's
        // protected USER HEADER section. Never define storage in a header.
        s << "\n" << globalsBegin << preservedGlobals << globalsEnd << "\n\n";

        QList<GuiDesignerGadget> demoBitmaps;
        QString bitmapText;
        QTextStream bitmaps(&bitmapText);
        bitmaps << "/* SIDBOX-IDE GENERATED BITMAPVIEW: "
                << designInfo.fileName() << " */\n"
                << "/* Auto-generated CLUT bitmap data. Do not hand-edit. */\n"
                << "#include \"apis.h\"\n\n";

        for (const GuiDesignerGadget &g :
             m_gadgets) {
            if (g.type
                    != QStringLiteral("BitmapView")
                || g.bitmapPixels.isEmpty()) {
                continue;
            }

            const QString n =
                safeCIdentifier(
                    g.name,
                    QStringLiteral("bitmap"));

            const QString source = bitmapPrefix + QStringLiteral("_")
                + safeCIdentifier(g.bitmapSource, n + QStringLiteral("_pixels"));

            const QString macro =
                n.toUpper();

            bitmaps << "\n#define "
              << macro
              << "_BITMAP_W "
              << qMax(1, g.bitmapWidth)
              << "u\n";

            bitmaps << "#define "
              << macro
              << "_BITMAP_H "
              << qMax(1, g.bitmapHeight)
              << "u\n";

            bitmaps << "/* PNG converted by the Sidbox GUI Designer to exact 8-bit CLUT indices. */\n";
            bitmaps << "uint8_t MEMALIGN32 "
              << source
              << "["
              << macro
              << "_BITMAP_W * "
              << macro
              << "_BITMAP_H] = {\n";

            for (qsizetype i = 0;
                 i < g.bitmapPixels.size();
                 ++i) {
                if ((i % 16) == 0) {
                    bitmaps << "\t";
                }

                const quint8 value =
                    static_cast<quint8>(
                        g.bitmapPixels.at(i));

                bitmaps << QStringLiteral("0x%1")
                         .arg(value, 2, 16, QLatin1Char('0'))
                         .toUpper();

                if (i + 1 < g.bitmapPixels.size()) {
                    bitmaps << ", ";
                }

                if ((i % 16) == 15
                    || i + 1 == g.bitmapPixels.size()) {
                    bitmaps << "\n";
                }
            }

            bitmaps << "};\n";
        }

        for (const GuiDesignerGadget &g :
             m_gadgets) {
            if (!isDesignerDemoBitmap(g)) {
                continue;
            }

            demoBitmaps.append(g);

            const QString n =
                safeCIdentifier(
                    g.name,
                    QStringLiteral(
                        "bitmap"));

            const QString source = bitmapPrefix + QStringLiteral("_")
                + safeCIdentifier(g.bitmapSource, n + QStringLiteral("_pixels"));

            const QString macro =
                n.toUpper();

            bitmaps << "\n#define "
              << macro
              << "_BITMAP_W "
              << qMax(1, g.bitmapWidth)
              << "u\n";

            bitmaps << "#define "
              << macro
              << "_BITMAP_H "
              << qMax(1, g.bitmapHeight)
              << "u\n";

            bitmaps << "/* Designer demo bitmap for "
              << n
              << ": storage exactly matches the generated BitmapView dimensions. */\n";

            bitmaps << "uint8_t MEMALIGN32 "
              << source
              << "["
              << macro
              << "_BITMAP_W * "
              << macro
              << "_BITMAP_H];\n";
        }

        // Dialogs are virtual objects; only their CoderGirl system requesters have window handles.
        if (hasDialogs) {
            for (const GuiDesignerGadget &g : std::as_const(m_gadgets)) {
                if (g.type != QStringLiteral("FileRequester") && g.type != QStringLiteral("MessageBox")) continue;
                const QString n = safeCIdentifier(g.name, QStringLiteral("dialog"));
                s << "static CGWindow " << n << "_requester = (CGWindow)0xFFu;\n";
            }
            for (const GuiDesignerGadget &g : std::as_const(m_gadgets)) {
                if (g.type == QStringLiteral("FileRequester")) {
                    const QString n = safeCIdentifier(g.name, QStringLiteral("fileRequest"));
                    s << "static char " << n << "_initial_dir[] = \"" << escapedCString(g.dialogDir)
                      << "\";\nstatic char " << n << "_selected_path[FILERQ_OUTCAP];\n";
                }
            }
            // Use CoderGirl's real window disable flag, not per-gadget enabled()
            // calls (which would erase applet-managed enabled/disabled states).
            // Window messages still reach the owner while input is disabled.
            s << "\nstatic void " << win << "_SetDialogOwnerBlocked(uint8_t blocked)\n{\n"
              << "\tif (" << win << "_dialog_block_owner == (blocked ? 1u : 0u)) return;\n"
              << "\t" << win << "_dialog_block_owner = blocked ? 1u : 0u;\n"
              << "\tif (blocked) SBOS_WindowDisable(" << win << ");\n"
              << "\telse SBOS_WindowEnable(" << win << ");\n"
              << "}\n\n";
            for (const GuiDesignerGadget &g : std::as_const(m_gadgets)) {
                if (g.type != QStringLiteral("FileRequester") && g.type != QStringLiteral("MessageBox")) continue;
                const QString n = safeCIdentifier(g.name, QStringLiteral("dialog"));
                s << "static void " << n << "_Show(void)\n{\n"
                  << "\tif (" << win << "_active_dialog != (CGWindow)0xFFu) return;\n"
                  << "\tCGWindow requester;\n";
                if (g.type == QStringLiteral("FileRequester")) {
                    s << "\trequester = SBOS_FileRequestFilter(" << win << ", \""
                      << escapedCString(g.dialogTitle) << "\", " << n << "_initial_dir, \""
                      << escapedCString(g.dialogFilter) << "\");\n";
                } else if (g.dialogKind == QStringLiteral("Info")) {
                    s << "\trequester = SBOS_InfoBox(" << win << ", \""
                      << escapedCString(g.dialogTitle) << "\", \""
                      << escapedCString(g.dialogMessage) << "\");\n";
                } else {
                    QString flags = QStringLiteral("MSGBOXF_OKCANCEL");
                    if (g.dialogButtons == QStringLiteral("OK")) flags = QStringLiteral("MSGBOXF_OK");
                    if (g.dialogButtons == QStringLiteral("Yes/No")) flags = QStringLiteral("MSGBOXF_YESNO");
                    if (g.dialogButtons == QStringLiteral("Yes/No/Cancel")) flags = QStringLiteral("MSGBOXF_YESNOCANCEL");
                    s << "\trequester = SBOS_MessageBox(" << win << ", \""
                      << escapedCString(g.dialogTitle) << "\", \""
                      << escapedCString(g.dialogMessage) << "\", " << flags << ");\n";
                }
                s << "\tif (requester == (CGWindow)0xFFu) return;\n"
                  << "\t" << win << "_active_dialog = requester;\n"
                  << "\t" << n << "_requester = requester;\n";
                if (g.dialogBlockOwner)
                    s << "\t" << win << "_SetDialogOwnerBlocked(1u);\n";
                s << "}\n\n";
            }
        }

        // Virtual keyboard/mouse event callbacks are invoked from WindowProc.
        for (const QString &cb : std::as_const(inputCallbacks)) {
            s << "static void " << cb
              << "(CGEventType event, int32_t a, int32_t b, int32_t c);\n";
        }

        // Declare timer and UART1 Data callbacks BEFORE any generated helper
        // (in particular UART1's cooperative _Poll() function) calls them.
        // GCC must not see an implicit declaration followed by static linkage.
        for (const QString &cb : std::as_const(timerCallbacks)) {
            s << "static void " << cb << "(void *user);\n";
        }

        for (const QString &cb : std::as_const(messengerCallbacks)) {
            s << "static void " << cb << "(const SIDBOX_IPC_MESSAGE *message);\n";
        }

        // Send-side helpers resolve the target on EACH send; this handles
        // receiver shutdown/relaunch without caching stale instance IDs.
        // These are file-local functions: Button actions or USER callbacks
        // can call them without any changes to the firmware or IPC API table.
        for (const GuiDesignerGadget &g : std::as_const(m_gadgets)) {
            if (g.type != QStringLiteral("Messenger") || g.ipcTargetApp.trimmed().isEmpty()) continue;
            const QString n = safeCIdentifier(g.name, QStringLiteral("messenger"));
            s << "\nstatic int32_t __attribute__((unused)) " << n << "_Send(uint32_t type, const void *data, uint32_t length)\n{\n"
              << "\tif (length > SIDBOX_IPC_MAX_DATA || (length && !data)) return SIDBOX_IPC_BAD_ARG;\n"
              << "\tif (!API->ipc) return SIDBOX_IPC_NO_CONTEXT;\n"
              << "\tuint32_t target = API->ipc->find(\"" << escapedCString(g.ipcTargetApp.trimmed()) << "\");\n"
              << "\tif (!target) return SIDBOX_IPC_NO_RECIPIENT;\n"
              << "\treturn API->ipc->send(target, type, data, length);\n}\n\n"
              << "static int32_t __attribute__((unused)) " << n << "_SendText(uint32_t type, const char *text)\n{\n"
              << "\tif (!text) return SIDBOX_IPC_BAD_ARG;\n"
              << "\tsize_t length = strlen(text);\n"
              << "\tif (length > SIDBOX_IPC_MAX_DATA) return SIDBOX_IPC_BAD_ARG;\n"
              << "\treturn " << n << "_Send(type, text, (uint32_t)length);\n}\n";
        }

        // Messenger: a cooperative poll invokes only this applet's callback.
        // The kernel copies IPC payloads; no cross-applet callback or GUI queue.
        for (const GuiDesignerGadget &g : std::as_const(m_gadgets)) {
            if (g.type != QStringLiteral("Messenger") || !g.ipcReceive) continue;
            const QString n = safeCIdentifier(g.name, QStringLiteral("messenger"));
            s << "\nstatic void " << n << "_Poll(void *user)\n{\n"
              << "\t(void)user;\n"
              << "\tif (!" << win << "_is_open || " << win << "_is_closing || !API->ipc) return;\n"
              << "\tfor (uint32_t i = 0u; i < SIDBOX_IPC_QUEUE_DEPTH; ++i) {\n"
              << "\t\tSIDBOX_IPC_MESSAGE message;\n"
              << "\t\tif (API->ipc->receive(&message) != SIDBOX_IPC_OK) break;\n"
              << "\t\t" << g.onActivate << "(&message);\n"
              << "\t\tif (!" << win << "_is_open || " << win << "_is_closing) break;\n"
              << "\t}\n}\n";
        }

        // UART1 virtual component. No interrupt ever invokes applet code:
        // an ordinary CoderGirl cooperative timer detects queued RX bytes.
        // Applet unload also forcibly returns UART1 to the OS in firmware.
        for (const GuiDesignerGadget &g : std::as_const(m_gadgets)) {
            if (g.type != QStringLiteral("UART1")) continue;
            const QString n = safeCIdentifier(g.name, QStringLiteral("uart1"));
            const QString onData = g.onActivate;
            s << "\nstatic CGTimer " << n << "_poll_timer = CGTIMER_INVALID;\n"
              << "static void " << n << "_Poll(void *user)\n{\n"
              << "\t(void)user;\n"
              << "\tif (SBOS_UART1_Available() > 0) " << onData << "(NULL);\n"
              << "}\n\n"
              << "static int32_t " << n << "_Open(uint32_t baud)\n{\n"
              << "\tint32_t status = SBOS_UART1_Open(baud, "
              << qBound(7,g.uart1DataBits,8) << "u, " << qBound(0,g.uart1Parity,2)
              << "u, " << qBound(1,g.uart1StopBits,2) << "u);\n"
              << "\tif (status != SIDBOX_UART1_OK) return status;\n"
              << "\t" << n << "_poll_timer = SBOS_CreateTimer();\n"
              << "\tif (" << n << "_poll_timer == CGTIMER_INVALID ||\n"
              << "\t\tSBOS_TimerSet(" << n << "_poll_timer, "
              << qBound(10,g.uart1PollMs,1000) << "u, " << qBound(10,g.uart1PollMs,1000)
              << "u, " << n << "_Poll, NULL) != 0) {\n"
              << "\t\tif (" << n << "_poll_timer != CGTIMER_INVALID) {\n"
              << "\t\t\tSBOS_FreeTimer(" << n << "_poll_timer);\n"
              << "\t\t\t" << n << "_poll_timer = CGTIMER_INVALID;\n\t\t}\n"
              << "\t\t(void)SBOS_UART1_Close();\n"
              << "\t\treturn SIDBOX_UART1_HARDWARE_ERROR;\n\t}\n"
              << "\treturn SIDBOX_UART1_OK;\n}\n\n"
              << "static int32_t " << n << "_Close(void)\n{\n"
              << "\tif (" << n << "_poll_timer != CGTIMER_INVALID) {\n"
              << "\t\tSBOS_TimerCancel(" << n << "_poll_timer);\n"
              << "\t\tSBOS_FreeTimer(" << n << "_poll_timer);\n"
              << "\t\t" << n << "_poll_timer = CGTIMER_INVALID;\n\t}\n"
              << "\treturn SBOS_UART1_Close();\n}\n";
        }

        // Media playback helpers are independent of the callback routing mode.
        // Samples belong to the generated window and are released on close.
        for (const GuiDesignerGadget &g : std::as_const(m_gadgets)) {
            if (g.type != QStringLiteral("Media")) continue;
            const QString n = safeCIdentifier(g.name, QStringLiteral("media"));
            const bool embedded = g.mediaMode == QStringLiteral("SFX") && g.mediaEmbedSfx;
            if (!embedded)
                s << "\nstatic char " << n << "_file[] = \""
                  << escapedCString(g.mediaFile) << "\";\n";
            if (g.mediaMode == QStringLiteral("SFX")) {
                if (embedded) {
                    const QString symbol = samplePrefix + QStringLiteral("_") + n
                        + QStringLiteral("_pcm");
                    s << "\nstatic void " << n << "_Play(void)\n{\n"
                      << "\tsound_stop(" << g.mediaChannel << "u);\n"
                      << "\tsound_assign(" << g.mediaChannel << "u, " << symbol << ", "
                      << symbol << "_length, SAMP_S8);\n";
                } else {
                    s << "static uint8_t *" << n << "_data = NULL;\n"
                      << "static uint32_t " << n << "_size = 0u;\n";
                    s << "static void " << n << "_Play(void)\n{\n"
                      << "\tif (!" << n << "_data) {\n"
                      << "\t\t" << n << "_size = LoadSFX(" << n << "_file, &" << n << "_data);\n"
                      << "\t\tif (!" << n << "_size || !" << n << "_data) return;\n"
                      << "\t\t/* Keep WAV PCM8 unsigned: BETH subtracts 128 in its mixer. */\n"
                      << "\t}\n"
                      << "\tsound_stop(" << g.mediaChannel << "u);\n"
                      << "\tsound_assign(" << g.mediaChannel << "u, " << n << "_data, "
                      << n << "_size, SAMP_S8);\n";
                }
                s << "\tsound_setfrequency(" << g.mediaChannel << "u, "
                  << qBound(1, g.mediaFrequency, 65535) << "u);\n"
                  << "\tsound_setvolume(" << g.mediaChannel << "u, "
                  << qBound(0, g.mediaVolume, 255) << "u);\n"
                  << "\tsound_setpanning(" << g.mediaChannel << "u, "
                  << qBound(-127, g.mediaPan, 127) << ");\n";
                if (g.mediaLoop)
                    s << "\tsound_setloop(" << g.mediaChannel << "u, 0u, "
                      << (embedded
                            ? (samplePrefix + QStringLiteral("_") + n + QStringLiteral("_pcm_length"))
                            : (n + QStringLiteral("_size"))) << ");\n"
                      << "\tsound_enableloop(" << g.mediaChannel << "u, 1u);\n";
                else
                    s << "\tsound_enableloop(" << g.mediaChannel << "u, 0u);\n";
                s << "\tsound_play(" << g.mediaChannel << "u);\n}\n";
                s << "static void " << n << "_Stop(void)\n{\n"
                  << "\tsound_stop(" << g.mediaChannel << "u);\n}\n";
                s << "static void " << n << "_Cleanup(void)\n{\n";
                if (!embedded) s << "\tif (!" << n << "_data) return;\n";
                s << "\tsound_stop(" << g.mediaChannel << "u);\n"
                  << "\tsound_assign(" << g.mediaChannel << "u, NULL, 0u, SAMP_S8);\n";
                if (!embedded)
                    s << "\tfree(" << n << "_data);\n"
                      << "\t" << n << "_data = NULL;\n"
                      << "\t" << n << "_size = 0u;\n";
                s << "}\n";
            } else {
                s << "static uint8_t " << n << "_active = 0u;\n"
                  << "static void " << n << "_Play(void)\n{\n"
                  << "\tmusic_play(" << n << "_file, "
                  << qBound(0, g.mediaSubsong, 255) << "u);\n"
                  << "\t" << n << "_active = 1u;\n}\n"
                  << "static void " << n << "_Stop(void)\n{\n"
                  << "\tif (!" << n << "_active) return;\n"
                  << "\tmusic_stop();\n"
                  << "\t" << n << "_active = 0u;\n}\n"
                  << "/* NOTE: call music_update() from your applet's cooperative main loop. */\n";
            }
        }

        s << "\nstatic CGWindowProcRes "
          << proc
          << "(CGWindow win, const CGMessage_t *m);\n";

        for (const GuiDesignerGadget &g : std::as_const(m_gadgets)) {
            if (g.type != QStringLiteral("TabGroup")) continue;
            const QString n = safeCIdentifier(g.name, QStringLiteral("tabs"));
            s << "static void " << win << "_" << n
              << "_SIDBOX_OnTab(void *source, int32_t a, int32_t b, int32_t c, int32_t d);\n";
        }

        for (const GuiDesignerGadget &g : std::as_const(m_gadgets)) {
            if (g.type == QStringLiteral("FileRequester")) {
                s << "static void " << g.onActivate << "(const char *path);\n"
                  << "static void " << g.onChange << "(void);\n";
            } else if (g.type == QStringLiteral("MessageBox")) {
                s << "static void " << g.onActivate << "(int32_t result);\n";
            }
        }
        for (const QString &cb :
             gadgetCallbacks) {
            s << "static void "
              << cb
              << "(CGGadget gadget, int32_t a, int32_t b, int32_t c, int32_t d);\n";
        }

        for (const QString &cb :
             menuCallbacks) {
            s << "static void "
              << cb
              << "(cg_menu_t menu, cg_menuitem_t item, void *userdata);\n";
        }

        for (const QString &cb :
             directGadgetCallbacks) {
            s << "static void "
              << directWrapperName(cb)
              << "(void *source, int32_t a, int32_t b, int32_t c, int32_t d);\n";
        }

        for (const GuiDesignerGadget &g :
             demoBitmaps) {
            const QString n =
                safeCIdentifier(
                    g.name,
                    QStringLiteral(
                        "bitmap"));

            const QString source = bitmapPrefix + QStringLiteral("_")
                + safeCIdentifier(g.bitmapSource, n + QStringLiteral("_pixels"));

            const QString macro =
                n.toUpper();

            bitmaps << "void "
              << bitmapPrefix << "_" << n
              << "_InitDemoBitmap(void)\n"
                 "{\n"
                 "\tfor (uint16_t y = 0; y < "
              << macro
              << "_BITMAP_H; ++y) {\n"
                 "\t\tfor (uint16_t x = 0; x < "
              << macro
              << "_BITMAP_W; ++x) {\n"
                 "\t\t\tconst uint8_t tile = (uint8_t)(((x >> 3) + (y >> 3)) & 0x0Fu);\n"
                 "\t\t\t"
              << source
              << "[((uint32_t)y * "
              << macro
              << "_BITMAP_W) + x] = (uint8_t)(3u + tile);\n"
                 "\t\t}\n"
                 "\t}\n"
                 "}\n\n";
        }

        for (const QString &cb :
             directGadgetCallbacks) {
            s << "static void "
              << directWrapperName(cb)
              << "(void *source, int32_t a, int32_t b, int32_t c, int32_t d)\n"
                 "{\n"
                 "\tconst CGGadget gadget = source\n"
                 "\t\t? API->gui->gadgets->get_id(source)\n"
                 "\t\t: (CGGadget)0u;\n"
                 "\t"
              << cb
              << "(gadget, a, b, c, d);\n"
                 "}\n\n";
        }

        for (const GuiDesignerGadget &g : std::as_const(m_gadgets)) {
            if (g.type != QStringLiteral("TabGroup")) continue;
            const QString n = safeCIdentifier(g.name, QStringLiteral("tabs"));
            const int base = tabBase.value(g.name);
            const int count = designerTabTitles(g).size();
            s << "static void " << win << "_" << n
              << "_SIDBOX_OnTab(void *source, int32_t a, int32_t b, int32_t c, int32_t d)\n"
                 "{\n"
                 "\t(void)a; (void)b; (void)c; (void)d;\n"
                 "\tconst CGGadget clicked = API->gui->gadgets->get_id(source);\n";
            for (int page=0; page<count; ++page) {
                s << (page == 0 ? "\tif" : "\telse if")
                  << " (clicked == " << n << "_tab_" << page << ") {\n";
                for (int group=0; group<count; ++group)
                    s << "\t\tAPI->gui->gadgets->set_group_visible(" << win << ", "
                      << (base+group) << "u, " << (group == page ? "1u" : "0u") << ");\n";
                for (int other=0; other<count; ++other)
                    s << "\t\tAPI->gui->gadgets->button_set_toggle(" << n
                      << "_tab_" << other << ", " << (other == page ? "1u" : "0u")
                      << ");\n";
                s << "\t}\n";
            }
            s << "}\n\n";
        }

        s << "// $IDE:OpenWindow //\n"
             "void "
          << win
          << "_Create(void)\n"
             "{\n";

        // A CoderGirl window ID of 0 is valid. Do not use the handle as a
        // boolean: the firmware also clears a destroyed window handle to 0.
        s << "\tif ("
          << win
          << "_is_open) {\n"
             "\t\tSBOS_WindowToFront("
          << win
          << ");\n"
             "\t\tSBOS_WindowSetFocus("
          << win
          << ");\n"
             "\t\treturn;\n"
             "\t}\n\n";

        s << "\t"
          << win
          << " = SBOS_CreateWindow(&"
          << win
          << ", "
          << m_window.rect.x()
          << ", "
          << m_window.rect.y()
          << ", "
          << m_window.rect.width()
          << ", "
          << m_window.rect.height()
          << ", \""
          << escapedCString(
                 m_window.title)
          << "\", "
          << (m_window.flags.trimmed().isEmpty()
                  ? QStringLiteral(
                        "SBX_WIN_DEFAULT")
                  : m_window.flags)
          << ");\n";

        // Public apis.h does not expose SBW_INVALID_ID; the firmware uses
        // 0xFF. Failed creation must not mark this window as open.
        s << "\tif ("
          << win
          << " == (CGWindow)0xFFu) {\n"
             "\t\treturn;\n"
             "\t}\n"
             "\t"
          << win
          << "_is_open = 1u;\n";
        if (hasDialogs) {
            s << "\t" << win << "_active_dialog = (CGWindow)0xFFu;\n"
              << "\t" << win << "_dialog_block_owner = 0u;\n";
            for (const GuiDesignerGadget &g : std::as_const(m_gadgets)) {
                if (g.type == QStringLiteral("FileRequester") || g.type == QStringLiteral("MessageBox"))
                    s << "\t" << safeCIdentifier(g.name, QStringLiteral("dialog"))
                      << "_requester = (CGWindow)0xFFu;\n";
            }
        }

        s << "\tSBOS_SetWindowProc("
          << win
          << ", "
          << proc
          << ");\n";

        s << "\t/* Window background pen "
          << m_window.backPen
          << " is stored by the designer.\n"
             "\t\tThe current public applet API does not export window_set_back_colour yet. */\n\n";

        if (!m_menus.isEmpty()) {
            QStringList titles;

            for (const GuiDesignerMenuTitle &menu :
                 m_menus) {
                titles << menu.title;
            }

            s << "\t"
              << win
              << "_Menu = SBOS_CreateMenuTitle(\""
              << escapedCString(
                     titles.join(
                         QLatin1Char('|')))
              << "\");\n";

            int menuIndex = 0;

            for (const GuiDesignerMenuTitle &menu :
                 m_menus) {
                for (const GuiDesignerMenuItem &item :
                     menu.items) {
                    const QString name =
                        safeCIdentifier(
                            item.name,
                            QStringLiteral(
                                "menuItem"));

                    s << "\t"
                      << name
                      << " = SBOS_CreateMenuItem(&"
                      << win
                      << "_Menu, "
                      << menuIndex
                      << ", \""
                      << escapedCString(
                             item.text)
                      << "\");\n";

                    const QString menuFlags =
                        menuFlagsForItem(
                            item);

                    if (!menuFlags.isEmpty()) {
                        s << "\tSBOS_MenuSetFlags(&"
                          << name
                          << ", 0, "
                          << menuFlags
                          << ");\n";
                    }

                    if (m_window.callbackMode == 1
                        && !isMenuSeparatorText(
                            item.text)
                        && !item.callback.isEmpty()) {
                        s << "\tSBOS_MenuCallBack("
                          << name
                          << ", "
                          << item.callback
                          << ", NULL);\n";
                    }
                }

                ++menuIndex;
            }

            s << "\tSBOS_AttachMenuToWindow("
              << win
              << "_Menu, "
              << win
              << ");\n\n";
        }

        for (int groupPass = 0; groupPass < 2; ++groupPass) {
        for (const GuiDesignerGadget &g :
             m_gadgets) {
            if (isVirtualDesignerGadget(g.type)) continue;
            if ((g.type == QStringLiteral("TabGroup")) != (groupPass == 0)) continue;
            const QString n =
                safeCIdentifier(
                    g.name,
                    QStringLiteral(
                        "gadget"));

            if (isDesignerDemoBitmap(g)) {
                s << "\t" << bitmapPrefix << "_" << n
                  << "_InitDemoBitmap();\n";
            }

            s << "\t"
              << n
              << " = "
              << creationExpression(
                     g,
                     win)
              << ";\n";

            if (g.type == QStringLiteral("TabGroup")) {
                s << "\tAPI->gui->gadgets->set_group_id(" << n << ", 0u);\n";
                const QStringList titles = designerTabTitles(g);
                const int width = qMax(1, g.rect.width()/titles.size());
                for (int page = 0; page < titles.size(); ++page) {
                    const int cellWidth = page == titles.size()-1
                        ? g.rect.width() - page*width : width;
                    const QString handle = n + QStringLiteral("_tab_%1").arg(page);
                    s << "\t" << handle
                      << " = API->gui->gadgets->button_create(" << win << ", "
                      << (g.rect.x()+page*width) << ", " << g.rect.y()
                      << ", " << cellWidth << ", 24, \""
                      << escapedCString(titles.at(page))
                      << "\", GAD_TOOL_DEFAULT | GAD_TOOL_TOGGLE | GAD_TOOL_MANUAL_TOGGLE);\n";
                    s << "\tAPI->gui->gadgets->set_group_id(" << handle << ", 0u);\n";
                    s << "\tAPI->gui->gadgets->set_callback(" << handle
                      << ", " << win << "_" << n
                      << "_SIDBOX_OnTab, NULL);\n";
                }
            }

            if (g.type == QStringLiteral("BitmapView")
                && !g.bitmapSource.trimmed().isEmpty()) {
                const QString bitmapSourceSymbol =
                    (!g.bitmapPixels.isEmpty() || isDesignerDemoBitmap(g))
                        ? bitmapPrefix + QStringLiteral("_")
                              + safeCIdentifier(g.bitmapSource, n + QStringLiteral("_pixels"))
                        : g.bitmapSource.trimmed();
                s << "\tSBOS_BitmapviewSetBitmap("
                  << n
                  << ", "
                  << bitmapSourceSymbol
                  << ");\n";

                s << "\tSBOS_BitmapviewSetImageSize("
                  << n
                  << ", "
                  << qMax(1, g.bitmapWidth)
                  << ", "
                  << qMax(1, g.bitmapHeight)
                  << ");\n";
            }

            if (g.bPen >= 0) {
                s << "\tAPI->gui->gadgets->set_bpen("
                  << n
                  << ", "
                  << g.bPen
                  << ");\n";
            }

            if (g.fPen >= 0) {
                s << "\tAPI->gui->gadgets->set_fpen("
                  << n
                  << ", "
                  << g.fPen
                  << ");\n";
            }

            if (g.hPen >= 0) {
                s << "\tAPI->gui->gadgets->set_hpen("
                  << n
                  << ", "
                  << g.hPen
                  << ");\n";
            }

            // Group 0 always stays visible. Assign it explicitly even if
            // another window left CoderGirl's global creation group nonzero.
            if (!tabBase.isEmpty()) {
                const int groupId = (!g.tabOwner.isEmpty() && tabBase.contains(g.tabOwner))
                    ? tabBase.value(g.tabOwner) + g.tabPage : 0;
                s << "\tAPI->gui->gadgets->set_group_id(" << n
                  << ", " << groupId << "u);\n";
            }

            s << "\tAPI->gui->gadgets->enabled("
              << n
              << ", "
              << (g.enabled
                      ? QStringLiteral("1u")
                      : QStringLiteral("0u"))
              << ");\n";

            if (g.type == QStringLiteral("GridSelect")) {
                const int cellCount =
                    qMin(
                        256,
                        qMax(1, g.cellsX * g.cellsY));

                for (int cell = 0;
                     cell < cellCount
                     && cell < g.gridCellText.size();
                     ++cell) {
                    const QString cellText =
                        g.gridCellText
                            .at(cell)
                            .left(4);

                    if (cellText.isEmpty()) {
                        continue;
                    }

                    s << "\tAPI->gui->gadgets->gridselect_set_cell_text("
                      << n
                      << ", \""
                      << escapedCString(cellText)
                      << "\", "
                      << cell
                      << ");\n";
                }
            }

            if (g.type == QStringLiteral("ProgressBar")) {
                const int minimum =
                    qMin(g.minimum, g.maximum);

                const int maximum =
                    qMax(g.minimum, g.maximum);

                const int value =
                    qBound(
                        minimum,
                        g.value,
                        maximum);

                s << "\tAPI->gui->gadgets->progressbar_set_minmax("
                  << n
                  << ", "
                  << minimum
                  << ", "
                  << maximum
                  << ");\n";

                s << "\tAPI->gui->gadgets->progressbar_set_value("
                  << n
                  << ", "
                  << value
                  << ");\n";
            }

            if (g.type == QStringLiteral("Slider")
                || g.type == QStringLiteral("Scrollbar")) {
                s << "\t/* Initial value "
                  << g.value
                  << " is stored in the .sbui; current applet API has no exported value setter yet. */\n";
            }

            if (directCallbackGadgets.contains(&g)
                && (!g.onActivate.isEmpty()
                    || !g.onChange.isEmpty())) {
                s << "\t/* Direct callback route for " << n << ". */\n";
                s << "\tAPI->gui->gadgets->set_callback("
                  << n
                  << ", "
                  << (g.onActivate.isEmpty()
                          ? QStringLiteral("NULL")
                          : directWrapperName(
                                g.onActivate))
                  << ", "
                  << (g.onChange.isEmpty()
                          ? QStringLiteral("NULL")
                          : directWrapperName(
                                g.onChange))
                  << ");\n";
            }

            if (g.type == QStringLiteral("ListBox")
                && !g.listItems.isEmpty()) {
                const QString itemList =
                    n + QStringLiteral("_items");

                s << "\t/* ListBox owns no strings/model: build a caller-owned ItemList and attach it. */\n";
                s << "\tAPI->gui->gadgets->itemlist_init(&"
                  << itemList
                  << ");\n";

                for (int itemIndex = 0;
                     itemIndex < g.listItems.size();
                     ++itemIndex) {
                    s << "\tAPI->gui->gadgets->itemlist_add(&"
                      << itemList
                      << ", \""
                      << escapedCString(
                             g.listItems.at(
                                 itemIndex))
                      << "\", 0u);\n";
                }

                s << "\tAPI->gui->gadgets->listbox_attach_itemlist("
                  << n
                  << ", &"
                  << itemList
                  << ");\n";
            }

            s << "\tAPI->gui->gadgets->repaint("
              << n
              << ");\n\n";
        }
        } // create tab chrome before ordinary page gadgets

        // Make only the configured initial page visible for each TabGroup.
        // Group zero still holds the bevel and the permanent tab buttons.
        for (const GuiDesignerGadget &g : std::as_const(m_gadgets)) {
            if (g.type != QStringLiteral("TabGroup")) continue;
            const int base = tabBase.value(g.name);
            const int count = designerTabTitles(g).size();
            const int initialPage = qBound(0, g.defaultTabPage, count - 1);
            for (int page = 0; page < count; ++page) {
                s << "\tAPI->gui->gadgets->set_group_visible(" << win << ", "
                  << (base+page) << "u, " << (page == initialPage ? "1u" : "0u") << ");\n";
                s << "\tAPI->gui->gadgets->button_set_toggle("
                  << safeCIdentifier(g.name, QStringLiteral("tabs"))
                  << "_tab_" << page << ", " << (page == initialPage ? "1u" : "0u") << ");\n";
            }
        }

        s << "\tSBOS_WindowToFront("
          << win
          << ");\n";

        s << "\tSBOS_WindowSetFocus("
          << win
          << ");\n";

        for (const GuiDesignerGadget &g :
             m_gadgets) {
            if (g.type
                != QStringLiteral(
                    "BitmapView")) {
                continue;
            }

            const QString n =
                safeCIdentifier(
                    g.name,
                    QStringLiteral(
                        "bitmapview"));

            s << "\tAPI->gui->gadgets->repaint("
              << n
              << ");\n";
        }

        // UART1 is leased only by explicit programmer call unless Auto Open was chosen.
        for (const GuiDesignerGadget &g : std::as_const(m_gadgets)) {
            if (g.type == QStringLiteral("UART1") && g.uart1AutoOpen)
                s << "\t(void)" << safeCIdentifier(g.name, QStringLiteral("uart1"))
                  << "_Open(" << qBound(1200,g.uart1Baud,1000000) << "u);\n";
        }

        // Virtual media components optionally start after all window gadgets exist.
        for (const GuiDesignerGadget &g : std::as_const(m_gadgets)) {
            if (g.type == QStringLiteral("Media") && g.mediaAutoStart)
                s << "\t" << safeCIdentifier(g.name, QStringLiteral("media")) << "_Play();\n";
        }

        // Messenger starts after the window is open; the callback runs on the
        // normal V2 cooperative timer PSP, never on another applet's stack.
        for (const GuiDesignerGadget &g : std::as_const(m_gadgets)) {
            if (g.type != QStringLiteral("Messenger") || !g.ipcReceive) continue;
            const QString n = safeCIdentifier(g.name, QStringLiteral("messenger"));
            const int pollMs = qBound(10, g.ipcPollMs, 1000);
            s << "\tif (" << n << "_poll_timer == CGTIMER_INVALID && API->ipc) {\n"
              << "\t\t" << n << "_poll_timer = SBOS_CreateTimer();\n"
              << "\t\tif (" << n << "_poll_timer != CGTIMER_INVALID &&\n"
              << "\t\t\tSBOS_TimerSet(" << n << "_poll_timer, " << pollMs << "u, "
              << pollMs << "u, " << n << "_Poll, NULL) != 0) {\n"
              << "\t\t\tSBOS_FreeTimer(" << n << "_poll_timer);\n"
              << "\t\t\t" << n << "_poll_timer = CGTIMER_INVALID;\n"
              << "\t\t}\n\t}\n";
        }

        // Timers are allocated only when their handle is invalid. With the
        // opt-in background lifetime, reopening a window must NOT create a
        // second timer or restart the still-running one.
        for (const GuiDesignerGadget &g : std::as_const(m_gadgets)) {
            if (g.type != QStringLiteral("Timer")) continue;
            const QString n = safeCIdentifier(g.name, QStringLiteral("timer"));
            s << "\tif (" << n << " == CGTIMER_INVALID) {\n"
              << "\t\t" << n << " = SBOS_CreateTimer();\n";
            if (g.timerAutoStart && !g.onActivate.trimmed().isEmpty()) {
                s << "\t\tif (" << n << " != CGTIMER_INVALID) {\n"
                  << "\t\t\tif (SBOS_TimerSet(" << n << ", "
                  << qBound(1, g.timerDelayMs, 86400000) << "u, "
                  << (g.timerRepeat ? qBound(1, g.timerPeriodMs, 86400000) : 0)
                  << "u, " << g.onActivate << ", NULL) != 0) {\n"
                  << "\t\t\t\tSBOS_FreeTimer(" << n << ");\n"
                  << "\t\t\t\t" << n << " = CGTIMER_INVALID;\n"
                  << "\t\t\t}\n\t\t}\n";
            }
            s << "\t}\n";
        }
        s << "}\n\n";

        /*
         * Single, file-local close path for title-bar close requests and
         * programmer callbacks. Call CloseWindow(), never SBOS_CloseWindow()
         * directly, when a generated window owns timers/models/menus/media.
         * Deliberately persistent timers are NOT cancelled here.
         */
        s << "static void CloseWindow(void)\n{\n"
          << "\tif (!" << win << "_is_open || " << win << "_is_closing) return;\n";
        if (hasDialogs)
            s << "\tif (" << win << "_active_dialog != (CGWindow)0xFFu) return;\n";
        s << "\t" << win << "_is_closing = 1u;\n"
          << "\t/* <SIDBOX-GUI:USER BEFORE_CLOSE> */\n";
        const QString beforeCloseBody = saved.value(QStringLiteral("BEFORE_CLOSE"));
        if (beforeCloseBody.isEmpty()) {
            s << "\t/* Shared shutdown hook. Avoid returning early from this block. */\n";
        } else {
            for (const QString &line : beforeCloseBody.split(QLatin1Char('\n')))
                s << "\t" << line << "\n";
        }
        s << "\t/* </SIDBOX-GUI:USER BEFORE_CLOSE> */\n";

        // Cancel IPC polling before any window resources disappear.
        for (const GuiDesignerGadget &g : std::as_const(m_gadgets)) {
            if (g.type != QStringLiteral("Messenger") || !g.ipcReceive) continue;
            const QString n = safeCIdentifier(g.name, QStringLiteral("messenger"));
            s << "\tif (" << n << "_poll_timer != CGTIMER_INVALID) {\n"
              << "\t\tSBOS_TimerCancel(" << n << "_poll_timer);\n"
              << "\t\tSBOS_FreeTimer(" << n << "_poll_timer);\n"
              << "\t\t" << n << "_poll_timer = CGTIMER_INVALID;\n\t}\n";
        }

        // Restore OS UART1 before freeing this window's other resources.
        for (const GuiDesignerGadget &g : std::as_const(m_gadgets)) {
            if (g.type == QStringLiteral("UART1"))
                s << "\t" << safeCIdentifier(g.name, QStringLiteral("uart1")) << "_Close();\n";
        }
        for (const GuiDesignerGadget &g : std::as_const(m_gadgets)) {
            if (g.type != QStringLiteral("ListBox") || g.listItems.isEmpty()) continue;
            const QString n = safeCIdentifier(g.name, QStringLiteral("listbox"));
            s << "\tAPI->gui->gadgets->listbox_attach_itemlist(" << n << ", NULL);\n"
              << "\tAPI->gui->gadgets->itemlist_deinit(&" << n << "_items);\n";
        }
        for (const GuiDesignerGadget &g : std::as_const(m_gadgets)) {
            if (g.type != QStringLiteral("Media")) continue;
            const QString n = safeCIdentifier(g.name, QStringLiteral("media"));
            if (g.mediaMode == QStringLiteral("SFX"))
                s << "\t" << n << "_Cleanup();\n";
            else
                s << "\t" << n << "_Stop();\n";
        }
        for (const GuiDesignerGadget &g : std::as_const(m_gadgets)) {
            if (g.type != QStringLiteral("Timer")) continue;
            const QString n = safeCIdentifier(g.name, QStringLiteral("timer"));
            if (g.timerKeepAliveOnClose) {
                s << "\t/* " << n << ": persistent background timer, retained. */\n";
                continue;
            }
            s << "\tif (" << n << " != CGTIMER_INVALID) {\n"
              << "\t\tSBOS_TimerCancel(" << n << ");\n"
              << "\t\tSBOS_FreeTimer(" << n << ");\n"
              << "\t\t" << n << " = CGTIMER_INVALID;\n"
              << "\t}\n";
        }
        // Set the guard before closing: the OS may synchronously send more
        // window messages during destruction. As in the old generator, menu
        // teardown follows SBOS_CloseWindow() to preserve API ordering.
        s << "\t" << win << "_is_open = 0u;\n"
          << "\tSBOS_CloseWindow(" << win << ");\n";
        if (!m_menus.isEmpty())
            s << "\tSBOS_DestroyMenu(&" << win << "_Menu);\n";
        s << "\t" << win << "_is_closing = 0u;\n"
          << "}\n\n";

        /*
         * Generate WindowProc as a real message/event dispatcher.
         *
         * The older generator emitted a chain of top-level if statements.
         * CoderGirl messages are already categorical, so nested switch blocks
         * make the generated applet much easier to read and extend.
         */
        bool hasBitmapView = false;

        for (const GuiDesignerGadget &g :
             m_gadgets) {
            if (g.type
                == QStringLiteral(
                    "BitmapView")) {
                hasBitmapView = true;
                break;
            }
        }

        QStringList gadgetEventClasses;

        for (const GuiDesignerGadget &g :
             m_gadgets) {
            if (!windowProcGadgets.contains(&g)) {
                continue;
            }

            if (g.type
                == QStringLiteral(
                    "Radio")) {
                if (!g.onActivate.isEmpty()
                    || !g.onChange.isEmpty()) {
                    gadgetEventClasses.append(
                        QStringLiteral(
                            "CGEVT_GAD_RADIO_CHANGED"));
                }

                continue;
            }

            if (!g.onActivate.isEmpty()) {
                gadgetEventClasses.append(
                    QStringLiteral(
                        "CGEVT_GAD_ACTIVATED"));
            }

            if (!g.onChange.isEmpty()) {
                const QString changeEvent =
                    changeEventForGadget(g);

                if (!changeEvent.isEmpty()) {
                    gadgetEventClasses.append(
                        changeEvent);
                }
            }
        }

        gadgetEventClasses.removeDuplicates();

        const bool hasWindowRoutedGadget =
            !gadgetEventClasses.isEmpty();

        // Don't generate an empty menu dispatcher for separator-only menus.
        const bool hasWindowRoutedMenu =
            m_window.callbackMode == 0
            && !menuCallbacks.isEmpty();

        s << "/* WindowProc always handles window lifecycle and system events.\n"
             " * Only gadgets routed through WindowProc appear in CGMSG_GADGET;\n"
             " * direct gadget callbacks are registered in Create() instead.\n"
             " */\n";
        s << "static CGWindowProcRes "
          << proc
          << "(CGWindow win, const CGMessage_t *m)\n"
             "{\n"
             "\tif (!m) {\n"
             "\t\treturn CGPROC_DEFAULT;\n"
             "\t}\n\n"
             "\tswitch (m->mtype) {\n"
             "\tcase CGMSG_WINDOW:\n"
             "\t\tswitch (m->eventClass) {\n"
             "\t\tcase CGEVT_WIN_CLOSE_REQUEST:\n";
        if (hasDialogs)
            s << "\t\t\t/* Keep the owner alive until its non-modal dialog completes. */\n"
              << "\t\t\tif (" << win << "_active_dialog != (CGWindow)0xFFu) return CGPROC_HANDLED;\n";
        s << "\t\t\t/* <SIDBOX-GUI:USER WINDOW_CLOSE> */\n";

        const QString closeBody =
            saved.value(
                QStringLiteral(
                    "WINDOW_CLOSE"));

        if (closeBody.isEmpty()) {
            s << "\t\t\t/* Legacy title-bar close validation here; "
                 "shared cleanup belongs in BEFORE_CLOSE below. */\n";
        } else {
            for (const QString &line :
                 closeBody.split(
                     QLatin1Char('\n'))) {
                s << "\t\t\t"
                  << line
                  << "\n";
            }
        }

        s << "\t\t\t/* </SIDBOX-GUI:USER WINDOW_CLOSE> */\n";

        s << "\t\t\tCloseWindow();\n";
        s << "\t\t\treturn CGPROC_HANDLED;\n";

        if (hasBitmapView) {
            s << "\n"
                 "\t\tcase CGEVT_SYS_REPAINT:\n"
                 "\t\t\t/* BitmapViews must be restored after a system/window repaint. */\n";

            for (const GuiDesignerGadget &g :
                 m_gadgets) {
                if (g.type
                    != QStringLiteral(
                        "BitmapView")) {
                    continue;
                }

                const QString n =
                    safeCIdentifier(
                        g.name,
                        QStringLiteral(
                            "bitmapview"));

                s << "\t\t\tAPI->gui->gadgets->repaint("
                  << n
                  << ");\n";
            }

            s << "\t\t\t/* Keep CoderGirl default dirty-rect/compositor processing. */\n"
                 "\t\t\treturn CGPROC_DEFAULT;\n";
        }

        if (hasDialogs) {
            // Dialog libraries post CGMSG_WINDOW events using CG_PostWindowMsg().
            s << "\n\t\tcase CGEVT_SYS_FILERQ_DONE:\n";
            for (const GuiDesignerGadget &g : std::as_const(m_gadgets)) {
                if (g.type != QStringLiteral("FileRequester")) continue;
                const QString n = safeCIdentifier(g.name, QStringLiteral("fileRequest"));
                s << "\t\t\tif (" << win << "_active_dialog == (CGWindow)m->d"
                  << " && " << n << "_requester == (CGWindow)m->d) {\n"
                  << "\t\t\t\t" << win << "_active_dialog = (CGWindow)0xFFu;\n"
                  << "\t\t\t\t" << n << "_requester = (CGWindow)0xFFu;\n"
                  << "\t\t\t\tif (" << win << "_dialog_block_owner) " << win << "_SetDialogOwnerBlocked(0u);\n"
                  << "\t\t\t\tif (m->a && m->c) {\n"
                  << "\t\t\t\t\tconst char *src = MSG_AS_PTR(const char, m->c);\n"
                  << "\t\t\t\t\tuint32_t i = 0u;\n"
                  << "\t\t\t\t\tfor (; i + 1u < sizeof(" << n << "_selected_path) && src[i]; ++i)\n"
                  << "\t\t\t\t\t\t" << n << "_selected_path[i] = src[i];\n"
                  << "\t\t\t\t\t" << n << "_selected_path[i] = 0;\n"
                  << "\t\t\t\t\t" << g.onActivate << "(" << n << "_selected_path);\n"
                  << "\t\t\t\t} else { " << g.onChange << "(); }\n"
                  << "\t\t\t\treturn CGPROC_HANDLED;\n\t\t\t}\n";
            }
            s << "\t\t\tbreak;\n\t\tcase CGEVT_SYS_MSGBOX_DONE:\n";
            for (const GuiDesignerGadget &g : std::as_const(m_gadgets)) {
                if (g.type != QStringLiteral("MessageBox") || g.dialogKind == QStringLiteral("Info")) continue;
                const QString n = safeCIdentifier(g.name, QStringLiteral("dialog"));
                s << "\t\t\tif (" << win << "_active_dialog == (CGWindow)m->d"
                  << " && " << n << "_requester == (CGWindow)m->d) {\n"
                  << "\t\t\t\t" << win << "_active_dialog = (CGWindow)0xFFu;\n"
                  << "\t\t\t\t" << n << "_requester = (CGWindow)0xFFu;\n"
                  << "\t\t\t\tif (" << win << "_dialog_block_owner) " << win << "_SetDialogOwnerBlocked(0u);\n"
                  << "\t\t\t\t" << g.onActivate << "(m->a);\n"
                  << "\t\t\t\treturn CGPROC_HANDLED;\n\t\t\t}\n";
            }
            s << "\t\t\tbreak;\n\t\tcase CGEVT_SYS_INFOBOX_DONE:\n";
            for (const GuiDesignerGadget &g : std::as_const(m_gadgets)) {
                if (g.type != QStringLiteral("MessageBox") || g.dialogKind != QStringLiteral("Info")) continue;
                const QString n = safeCIdentifier(g.name, QStringLiteral("dialog"));
                s << "\t\t\tif (" << win << "_active_dialog == (CGWindow)m->d"
                  << " && " << n << "_requester == (CGWindow)m->d) {\n"
                  << "\t\t\t\t" << win << "_active_dialog = (CGWindow)0xFFu;\n"
                  << "\t\t\t\t" << n << "_requester = (CGWindow)0xFFu;\n"
                  << "\t\t\t\tif (" << win << "_dialog_block_owner) " << win << "_SetDialogOwnerBlocked(0u);\n"
                  << "\t\t\t\t" << g.onActivate << "(m->a);\n"
                  << "\t\t\t\treturn CGPROC_HANDLED;\n\t\t\t}\n";
            }
            s << "\t\t\tbreak;\n";
        }

        s << "\n"
             "\t\tdefault:\n"
             "\t\t\tbreak;\n"
             "\t\t}\n"
             "\t\tbreak;\n";

        if (hasWindowRoutedGadget) {
            s << "\n"
                 "\tcase CGMSG_GADGET:\n";
            if (hasDialogs) s << "\t\tif (" << win << "_dialog_block_owner) return CGPROC_HANDLED;\n";
            s << "\t\tswitch (m->eventClass) {\n";

            for (const QString &eventClass :
                 gadgetEventClasses) {
                s << "\t\tcase "
                  << eventClass
                  << ":\n";

                for (const GuiDesignerGadget &g :
                     m_gadgets) {
                    if (!windowProcGadgets.contains(&g)) {
                        continue;
                    }

                    bool handlesEvent = false;
                    bool callActivate = false;
                    bool callChange = false;

                    if (g.type
                        == QStringLiteral(
                            "Radio")) {
                        handlesEvent =
                            eventClass
                            == QStringLiteral(
                                "CGEVT_GAD_RADIO_CHANGED")
                            && (!g.onActivate.isEmpty()
                                || !g.onChange.isEmpty());

                        callActivate =
                            handlesEvent
                            && !g.onActivate.isEmpty();

                        callChange =
                            handlesEvent
                            && !g.onChange.isEmpty();
                    } else {
                        if (eventClass
                                == QStringLiteral(
                                    "CGEVT_GAD_ACTIVATED")
                            && !g.onActivate.isEmpty()) {
                            handlesEvent = true;
                            callActivate = true;
                        }

                        const QString changeEvent =
                            changeEventForGadget(g);

                        if (!g.onChange.isEmpty()
                            && !changeEvent.isEmpty()
                            && eventClass
                               == changeEvent) {
                            handlesEvent = true;
                            callChange = true;
                        }
                    }

                    if (!handlesEvent) {
                        continue;
                    }

                    const QString n =
                        safeCIdentifier(
                            g.name,
                            QStringLiteral(
                                "gadget"));

                    s << "\t\t\tif (m->gadget == "
                      << n
                      << ") {\n";

                    if (callActivate) {
                        s << "\t\t\t\t"
                          << g.onActivate
                          << "(m->gadget, m->a, m->b, m->c, m->d);\n";
                    }

                    if (callChange) {
                        s << "\t\t\t\t"
                          << g.onChange
                          << "(m->gadget, m->a, m->b, m->c, m->d);\n";
                    }

                    s << "\t\t\t\treturn CGPROC_HANDLED;\n"
                         "\t\t\t}\n";
                }

                s << "\t\t\tbreak;\n\n";
            }

            s << "\t\tdefault:\n"
                 "\t\t\tbreak;\n"
                 "\t\t}\n"
                 "\t\tbreak;\n";
        }

        // Passive virtual listeners observe events without swallowing them.
        // Keyboard already comes through the OS key queue; mouse is a copied
        // window-level notification. DEFAULT preserves normal OS behaviour.
        for (const GuiDesignerGadget &g : std::as_const(m_gadgets)) {
            if (g.type != QStringLiteral("KBInput") || g.onActivate.isEmpty()) continue;
            s << "\n\tcase CGMSG_KEY:\n";
            if (hasDialogs) s << "\t\tif (" << win << "_dialog_block_owner) break;\n";
            s << "\t\tif (m->eventClass == CGEVT_KEY_PRESSED || m->eventClass == CGEVT_KEY_RELEASED)\n"
                 "\t\t\t" << g.onActivate << "(m->eventClass, m->a, m->b, m->c);\n"
                 "\t\tbreak;\n";
        }
        for (const GuiDesignerGadget &g : std::as_const(m_gadgets)) {
            if (g.type != QStringLiteral("MSInput") || g.onActivate.isEmpty()) continue;
            s << "\n\tcase CGMSG_MOUSE:\n";
            if (hasDialogs) s << "\t\tif (" << win << "_dialog_block_owner) break;\n";
            s << "\t\tif (m->eventClass == CGEVT_MOUSE_MOVED || m->eventClass == CGEVT_MOUSE_PRESSED\n"
                 "\t\t\t|| m->eventClass == CGEVT_MOUSE_RELEASED)\n"
                 "\t\t\t" << g.onActivate << "(m->eventClass, m->a, m->b, m->c);\n"
                 "\t\tbreak;\n";
        }

        if (hasWindowRoutedMenu) {
            s << "\n"
                 "\tcase CGMSG_MENU:\n";
            if (hasDialogs) s << "\t\tif (" << win << "_dialog_block_owner) return CGPROC_HANDLED;\n";
            s << "\t\tswitch (m->eventClass) {\n"
                 "\t\tcase CGEVT_MENU_SELECTED:\n";

            for (const GuiDesignerMenuTitle &menu :
                 m_menus) {
                for (const GuiDesignerMenuItem &item :
                     menu.items) {
                    if (isMenuSeparatorText(
                            item.text)
                        || item.callback.isEmpty()) {
                        continue;
                    }

                    const QString itemName =
                        safeCIdentifier(
                            item.name,
                            QStringLiteral(
                                "menuItem"));

                    s << "\t\t\tif ((cg_menu_t)m->a == "
                      << win
                      << "_Menu\n"
                         "\t\t\t\t&& (cg_menuitem_t)m->b == "
                      << itemName
                      << ") {\n"
                         "\t\t\t\t"
                      << item.callback
                      << "((cg_menu_t)m->a, (cg_menuitem_t)m->b, NULL);\n"
                         "\t\t\t\treturn CGPROC_HANDLED;\n"
                         "\t\t\t}\n";
                }
            }

            s << "\t\t\tbreak;\n\n"
                 "\t\tdefault:\n"
                 "\t\t\tbreak;\n"
                 "\t\t}\n"
                 "\t\tbreak;\n";
        }

        s << "\n"
             "\tdefault:\n"
             "\t\tbreak;\n"
             "\t}\n\n"
             "\t/* Returning DEFAULT lets CoderGirl perform its normal window behaviour. */\n"
             "\treturn CGPROC_DEFAULT;\n"
             "}\n\n";

        for (const QString &cb :
             gadgetCallbacks) {
            s << "static void "
              << cb
              << "(CGGadget gadget, int32_t a, int32_t b, int32_t c, int32_t d)\n"
                 "{\n"
                 "\t(void)gadget; (void)a; (void)b; (void)c; (void)d;\n";
            if (hasDialogs) s << "\tif (" << win << "_dialog_block_owner) return;\n";
            if (linkedCallbacks.contains(cb)) {
                s << "\t" << linkedCallbacks.value(cb) << "();\n";
            }
            if (mediaLinkedActions.contains(cb)) {
                s << "\t" << mediaLinkedActions.value(cb) << "\n";
            }
            if (dialogLinkedActions.contains(cb)) {
                s << "\t" << dialogLinkedActions.value(cb) << "\n";
            }
            if (ipcLinkedActions.contains(cb)) {
                s << "\t" << ipcLinkedActions.value(cb) << "\n";
            }
            s << "\t/* <SIDBOX-GUI:USER "
              << cb
              << "> */\n";

            const QString body =
                saved.value(cb);

            if (body.isEmpty()) {
                s << "\t/* TODO: programmer callback code */\n";
            } else {
                for (const QString &line :
                     body.split(
                         QLatin1Char('\n'))) {
                    s << "\t"
                      << line
                      << "\n";
                }
            }

            s << "\t/* </SIDBOX-GUI:USER "
              << cb
              << "> */\n"
                 "}\n\n";
        }

        for (const QString &cb : std::as_const(inputCallbacks)) {
            s << "static void " << cb
              << "(CGEventType event, int32_t a, int32_t b, int32_t c)\n"
                 "{\n\t(void)event; (void)a; (void)b; (void)c;\n"
                 "\t/* <SIDBOX-GUI:USER " << cb << "> */\n";
            const QString body = saved.value(cb);
            if (body.isEmpty()) {
                bool kb = false;
                for (const GuiDesignerGadget &g : std::as_const(m_gadgets))
                    if (g.type == QStringLiteral("KBInput") && g.onActivate == cb) kb = true;
                if (kb) {
                    s << "\t/* KEYBOARD INPUT EXAMPLE (uncomment to use):\n"
                         "\tif (event == CGEVT_KEY_PRESSED)\n"
                         "\t\tprintf(\"Key: %ld mods: %ld\\n\", (long)a, (long)b);\n"
                         "\telse if (event == CGEVT_KEY_RELEASED)\n"
                         "\t\tprintf(\"Released: %ld\\n\", (long)a);\n"
                         "\t\ta=key/ASCII, b=modifiers, c=HID usage (USB key releases).\n"
                         "\t*/\n";
                } else {
                    s << "\t/* MOUSE INPUT EXAMPLE (uncomment to use):\n"
                         "\tif (event == CGEVT_MOUSE_PRESSED && (c & SBINPUT_MOUSE_LEFT))\n"
                         "\t\tprintf(\"Left down at %ld,%ld\\n\", (long)a, (long)b);\n"
                         "\tif (event == CGEVT_MOUSE_MOVED)\n"
                         "\t\tprintf(\"Move: %ld,%ld\\n\", (long)a, (long)b);\n"
                         "\t\tc includes LEFT/RIGHT and optional TOUCH source flags.\n"
                         "\t*/\n";
                }
            } else {
                for (const QString &line : body.split(QLatin1Char('\n')))
                    s << "\t" << line << "\n";
            }
            s << "\t/* </SIDBOX-GUI:USER " << cb << "> */\n}\n\n";
        }

        for (const QString &cb : std::as_const(timerCallbacks)) {
            s << "static void " << cb << "(void *user)\n"
                 "{\n\t(void)user;\n"
                 "\t/* <SIDBOX-GUI:USER " << cb << "> */\n";
            const QString body = saved.value(cb);
            if (body.isEmpty()) {
                if (uart1DataCallbacks.contains(cb)) {
                    // In the protected USER block, ship a *commented-out* example.
                    // Read() consumes RX bytes, otherwise _Poll keeps firing for
                    // the same unread data. `user` is NOT an incoming byte string.
                    s << "\t/* UART1 RECEIVE EXAMPLE (uncomment to use):\n"
                         "\t\tThe callback means RX data is waiting; `user` is not the data.\n"
                         "\t\tReading consumes bytes so the callback won't repeat for them.\n"
                         "\n"
                         "\tuint8_t data[32];\n"
                         "\tint32_t received = SBOS_UART1_Read(data, sizeof(data));\n"
                         "\n"
                         "\tif (received > 0) {\n"
                         "\t\tfor (int32_t i = 0; i < received; i++) {\n"
                         "\t\t\tprintf(\"Serial in: '%c' (0x%02X)\\n\",\n"
                         "\t\t\t\t(data[i] >= 32 && data[i] <= 126) ? data[i] : '.',\n"
                         "\t\t\t\t(unsigned int)data[i]);\n"
                         "\t\t}\n"
                         "\t}\n"
                         "\t*/\n";
                } else {
                    s << "\t/* TODO: timer tick; keep callbacks cooperative and short. */\n";
                }
            } else {
                // NEVER replace handwritten protected callback content.
                for (const QString &line : body.split(QLatin1Char('\n')))
                    s << "\t" << line << "\n";
            }
            s << "\t/* </SIDBOX-GUI:USER " << cb << "> */\n}\n\n";
        }

        // Messenger callbacks are applet-owned, automatically invoked by the
        // cooperative receiver poll. Their message pointer is valid only here.
        for (const QString &cb : std::as_const(messengerCallbacks)) {
            s << "static void " << cb << "(const SIDBOX_IPC_MESSAGE *message)\n{\n"
              << "\t(void)message;\n"
              << "\t/* <SIDBOX-GUI:USER " << cb << "> */\n";
            const QString body = saved.value(cb);
            if (body.isEmpty()) {
                s << "\t/* Received: message->sender, message->type, "
                     "message->length, message->data[0..length-1].\n"
                     "\t * Reply example (uncomment):\n"
                     "\t * (void)API->ipc->send(message->sender, 2u, message->data, message->length);\n"
                     "\t * Do not save the message pointer beyond this callback. */\n";
            } else {
                for (const QString &line : body.split(QLatin1Char('\n')))
                    s << "\t" << line << "\n";
            }
            s << "\t/* </SIDBOX-GUI:USER " << cb << "> */\n}\n\n";
        }

        for (const QString &cb :
             menuCallbacks) {
            s << "static void "
              << cb
              << "(cg_menu_t menu, cg_menuitem_t item, void *userdata)\n"
                 "{\n"
                 "\t(void)menu; (void)item; (void)userdata;\n";
            if (hasDialogs) s << "\tif (" << win << "_dialog_block_owner) return;\n";
            s << "\t/* <SIDBOX-GUI:USER "
              << cb
              << "> */\n";

            const QString body =
                saved.value(cb);

            if (body.isEmpty()) {
                s << "\t/* TODO: programmer callback code */\n";
            } else {
                for (const QString &line :
                     body.split(
                         QLatin1Char('\n'))) {
                    s << "\t"
                      << line
                      << "\n";
                }
            }

            s << "\t/* </SIDBOX-GUI:USER "
              << cb
              << "> */\n"
                 "}\n\n";
        }

        for (const GuiDesignerGadget &g : std::as_const(m_gadgets)) {
            if (g.type != QStringLiteral("FileRequester") && g.type != QStringLiteral("MessageBox")) continue;
            const auto userBody = [&saved, &s](const QString &cb) {
                s << "\t/* <SIDBOX-GUI:USER " << cb << "> */\n";
                const QString body = saved.value(cb);
                if (body.isEmpty()) s << "\t/* TODO: handle dialog result here. */\n";
                else for (const QString &line : body.split(QLatin1Char('\n')))
                    s << "\t" << line << "\n";
                s << "\t/* </SIDBOX-GUI:USER " << cb << "> */\n";
            };
            const QString n = safeCIdentifier(g.name, QStringLiteral("dialog"));
            if (g.type == QStringLiteral("FileRequester")) {
                s << "static void " << g.onActivate << "(const char *path)\n{\n"
                  << "\t/*\n"
                     "\t * EXAMPLE ONLY (documentation; does not execute).\n"
                     "\t * The selected filename is supplied in 'path'.\n"
                     "\t * Copy the string to your own buffer if it must survive\n"
                     "\t * beyond this callback or after another file request.\n"
                     "\t *\n"
                  << "\tif (path && path[0] != '\\0') {\n"
                  << "\t\tprintf(\"[" << n << "] Selected file: %s\\n\", path);\n"
                  << "\t} else {\n"
                  << "\t\tprintf(\"[" << n << "] Empty filename returned\\n\");\n"
                  << "\t}\n"
                  << "\t */\n";
                userBody(g.onActivate);
                s << "}\n\nstatic void " << g.onChange << "(void)\n{\n"
                  << "\t/*\n"
                     "\t * EXAMPLE ONLY (documentation; does not execute).\n"
                     "\t * Cancel was pressed; no filename is returned.\n"
                  << "\tprintf(\"[" << n << "] File selection cancelled\\n\");\n"
                  << "\t */\n";
                userBody(g.onChange);
                s << "}\n\n";
            } else {
                s << "static void " << g.onActivate << "(int32_t result)\n{\n"
                  << "\t/*\n"
                     "\t * EXAMPLE ONLY (documentation; does not execute).\n"
                     "\t * The user's button choice is supplied in 'result'.\n"
                     "\t * Put your actual logic in the USER block below.\n"
                     "\t *\n";
                if (g.dialogKind == QStringLiteral("Info")) {
                    s << "\tif (result == INFOBOX_OK) {\n"
                      << "\t\tprintf(\"[" << n << "] InfoBox acknowledged (OK)\\n\");\n"
                      << "\t} else {\n"
                      << "\t\tprintf(\"[" << n << "] InfoBox result: %ld\\n\", (long)result);\n"
                      << "\t}\n";
                } else {
                    s << "\tswitch (result) {\n"
                      << "\tcase MSGBOX_OK:\n"
                      << "\t\tprintf(\"[" << n << "] OK pressed\\n\");\n"
                      << "\t\tbreak;\n"
                      << "\tcase MSGBOX_YES:\n"
                      << "\t\tprintf(\"[" << n << "] YES pressed\\n\");\n"
                      << "\t\tbreak;\n"
                      << "\tcase MSGBOX_NO:\n"
                      << "\t\tprintf(\"[" << n << "] NO pressed\\n\");\n"
                      << "\t\tbreak;\n"
                      << "\tcase MSGBOX_CANCEL:\n"
                      << "\t\tprintf(\"[" << n << "] CANCEL pressed\\n\");\n"
                      << "\t\tbreak;\n"
                      << "\tdefault:\n"
                      << "\t\tprintf(\"[" << n << "] Unknown result: %ld\\n\", (long)result);\n"
                      << "\t\tbreak;\n"
                      << "\t}\n";
                }
                s << "\t */\n";
                userBody(g.onActivate);
                s << "}\n\n";
            }
        }

        QStringList orphanKeys =
            saved.keys();

        for (const QString &key :
             callbackKeys) {
            orphanKeys.removeAll(key);
        }

        orphanKeys.removeDuplicates();
        orphanKeys.sort(
            Qt::CaseInsensitive);

        if (!orphanKeys.isEmpty()) {
            s << "/*\n"
                 " * Preserved callbacks no longer referenced by the visual design.\n"
                 " * They are disabled so deleting/renaming a gadget never destroys user code.\n"
                 " */\n"
                 "#if 0\n";

            for (const QString &key :
                 orphanKeys) {
                s << "/* <SIDBOX-GUI:USER "
                  << key
                  << "> */\n";

                s << saved.value(key)
                  << "\n";

                s << "/* </SIDBOX-GUI:USER "
                  << key
                  << "> */\n\n";
            }

            s << "#endif\n";
        }

        // Keep this last in the generated .c file so programmers can add
        // file-local helper function definitions without touching generated
        // callbacks. Call cleanup helpers explicitly from BEFORE_CLOSE.
        s << "\n/* <SIDBOX-GUI:USER custom_code> */"
          << preservedCustomCode;
        if (!preservedCustomCode.endsWith(QLatin1Char('\n')))
            s << "\n";
        s << "/* </SIDBOX-GUI:USER custom_code> */\n";

        // Resource sources are generated beside this .sbui in <name>res/.
        // The project's recursive .c discovery picks up both source files.
        const QByteArray bitmapMarker("/* SIDBOX-IDE GENERATED BITMAPVIEW: ");
        const QByteArray sfxMarker("/* SIDBOX-IDE GENERATED EMBEDDED SFX: ");
        const QByteArray ownerName = designInfo.fileName().toUtf8();
        QString assetText;
        QTextStream assets(&assetText);
        assets << "/* SIDBOX-IDE GENERATED EMBEDDED SFX: "
               << designInfo.fileName() << " */\n"
               << "/* Auto-generated unsigned PCM8 data. Do not hand-edit. */\n"
               << "#include \"apis.h\"\n\n";
        bool anyEmbedded = false;
        for (const GuiDesignerGadget &g : std::as_const(m_gadgets)) {
            if (g.type != QStringLiteral("Media") || g.mediaMode != QStringLiteral("SFX")
                || !g.mediaEmbedSfx) continue;
            anyEmbedded = true;
            const QString symbol = samplePrefix + QStringLiteral("_")
                + safeCIdentifier(g.name, QStringLiteral("media")) + QStringLiteral("_pcm");
            assets << "/* " << g.mediaEmbeddedPcm.size() << " unsigned PCM8 samples */\n"
                   << "const uint8_t MEMALIGN32 " << symbol << "[] = {\n";
            for (qsizetype i = 0; i < g.mediaEmbeddedPcm.size(); ++i) {
                if (i % 16 == 0) assets << "\t";
                assets << "0x" << QStringLiteral("%1").arg(
                    (uchar(g.mediaEmbeddedPcm.at(i)) ^ 0x80u), 2, 16, QLatin1Char('0'));
                if (i + 1 != g.mediaEmbeddedPcm.size()) assets << ", ";
                if (i % 16 == 15 || i + 1 == g.mediaEmbeddedPcm.size()) assets << "\n";
            }
            assets << "};\n"
                   << "const uint32_t " << symbol << "_length = "
                   << g.mediaEmbeddedPcm.size() << "u;\n\n";
        }
        const bool anyBitmap = !demoBitmaps.isEmpty() || std::any_of(
            m_gadgets.cbegin(), m_gadgets.cend(), [](const GuiDesignerGadget &g) {
                return g.type == QStringLiteral("BitmapView") && !g.bitmapPixels.isEmpty();
            });
        const QString oldSfxPath = designInfo.dir().absoluteFilePath(
            designInfo.completeBaseName() + QStringLiteral("_sfx.c"));

        // Validate ALL destinations before writing any generated source.
        // Never overwrite a programmer-owned .c file in a resources folder.
        if (!sketch) {
            for (const auto &entry : {
                 qMakePair(bitmapResourcePath, bitmapMarker),
                 qMakePair(mediaResourcePath, sfxMarker),
                 qMakePair(oldSfxPath, sfxMarker) }) {
                if (!QFile::exists(entry.first)) continue;
                QFile previous(entry.first);
                if (!previous.open(QIODevice::ReadOnly) ||
                    !previous.read(256).startsWith(entry.second + ownerName)) {
                    QMessageBox::warning(this, QObject::tr("Generated resource conflict"),
                        QObject::tr("%1 already exists but is not recognised as a generated "
                                    "resource for this design. It will not be overwritten.")
                            .arg(QDir::toNativeSeparators(entry.first)));
                    return false;
                }
            }
        }

        // Preserve tracked generated sources when assets are removed: an empty
        // generated unit cannot leave stale linker symbols behind.
        const auto writeResource = [this](const QString &path, const QString &contents,
                                          bool createIfMissing) -> bool {
            const QFileInfo fileInfo(path);
            if (!createIfMissing && !fileInfo.exists()) return true;
            QFile old(path);
            if (old.open(QIODevice::ReadOnly) && old.readAll() == contents.toUtf8())
                return true;
            if (!QDir().mkpath(fileInfo.absolutePath())) {
                QMessageBox::warning(this, QObject::tr("Resource directory error"),
                    QObject::tr("Cannot create directory %1").arg(fileInfo.absolutePath()));
                return false;
            }
            QSaveFile target(path);
            const QByteArray bytes = contents.toUtf8();
            if (!target.open(QIODevice::WriteOnly | QIODevice::Text)
                || target.write(bytes) != bytes.size() || !target.commit()) {
                QMessageBox::warning(this, QObject::tr("Generated resource error"),
                    QObject::tr("Cannot write %1").arg(QDir::toNativeSeparators(path)));
                return false;
            }
            return true;
        };

        // Generating a .uis sketch must not mutate compilable resources:
        // Detached mode belongs to the programmer, not the code generator.
        if (!sketch &&
            (!writeResource(bitmapResourcePath, bitmapText, anyBitmap) ||
             !writeResource(mediaResourcePath, assetText, anyEmbedded)))
            return false;

        // The old <design>_sfx.c lived alongside the .sbui. Retain a harmless
        // marked stub instead of deleting it (it may be listed in .proj).
        // This prevents duplicate PCM definitions after migration.
        const QString migratedSfxStub = QStringLiteral(
            "/* SIDBOX-IDE GENERATED EMBEDDED SFX: %1 */\n"
            "/* Migrated to %2res/media_sfx.c. Kept for existing .proj references. */\n")
            .arg(designInfo.fileName(), designInfo.completeBaseName());
        if (!sketch && !writeResource(oldSfxPath, migratedSfxStub, false))
            return false;

        // The header must exist before the new .c starts including it.
        // The preflight above prevents overwriting an unrelated programmer header.
        if (!sketch && !writeGeneratedHeader(cPath, win + QStringLiteral("_Create")))
            return false;

        QSaveFile file(cPath);
        if (!file.open(
                QIODevice::WriteOnly
                | QIODevice::Text)) {
            QMessageBox::warning(
                this,
                QObject::tr(
                    "GUI Designer"),
                QObject::tr(
                    "Could not generate %1")
                    .arg(
                        QDir::toNativeSeparators(
                            cPath)));
            return false;
        }

        file.write(
            out.toUtf8());

        if (!file.commit()) {
            return false;
        }

        // Only mark the default destination current. Generating to the other
        // destination must not suppress the next normal automatic generation.
        if (sketch == m_detached) m_needsGeneration = false;
        if (!saveDesign()) return false;
        if (generatedFilesChanged) {
            generatedFilesChanged(
                m_filePath,
                cPath);
            if (!sketch && (anyBitmap || QFile::exists(bitmapResourcePath)))
                generatedFilesChanged(m_filePath, bitmapResourcePath);
            if (!sketch && (anyEmbedded || QFile::exists(mediaResourcePath)))
                generatedFilesChanged(m_filePath, mediaResourcePath);
        }

        m_statusLabel->setText(
            QObject::tr(
                "Generated %1")
                .arg(
                    QFileInfo(cPath)
                        .fileName()));

        /*
         * Successful generation is deliberately non-modal. MainWindow receives
         * generatedFilesChanged and reports success in the IDE status bar.
         */
        if (showMessage) {
            m_statusLabel->setText(
                QObject::tr("Generated %1")
                    .arg(
                        QFileInfo(cPath)
                            .fileName()));
        }

        return true;
    }

    QString m_filePath;
    bool m_detached = false;
    QString m_sourceName;
    QString m_sketchName;
    QComboBox *m_generationMode = nullptr;
    bool m_modified = false;
    bool m_needsGeneration = true;
    GuiDesignerWindow m_window;
    QList<GuiDesignerGadget> m_gadgets;
    QList<GuiDesignerMenuTitle> m_menus;
    QTabWidget *m_toolboxTabs = nullptr;
    QTreeWidget *m_menuTree = nullptr;
    GuiDesignerCanvas *m_canvas = nullptr;
    QWidget *m_propertyHost = nullptr;
    GuiDesignerPropertyGrid *m_propertyLayout = nullptr;
    QLabel *m_statusLabel = nullptr;
    QAction *m_undoAction = nullptr;
    QComboBox *m_snapCombo = nullptr;
    QList<QByteArray> m_undoStates;
    QPointer<QLineEdit> m_textPropertyEdit;
    bool m_inlineTextEditing = false;
    bool m_inlineReplaceOnFirstKey = true;
    int m_inlineTextIndex = -1;
    bool m_restoringUndo = false;
};


} // namespace

SidboxGuiDesigner *createSidboxGuiDesigner(
    const QString &filePath,
    QWidget *parent)
{
    return new SidboxGuiDesignerImpl(
        filePath,
        parent);
}
