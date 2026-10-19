// Stage 3.71: moved intact from guidesigner.cpp; included once inside GuiDesignerDetail.
constexpr const char *GuiDesignerGadgetMimeType =
    "application/x-sidbox-codergirl-gadget";

constexpr const char *GuiDesignerClipboardMimeType =
    "application/x-sidbox-codergirl-gadget-json";

class GuiDesignerPaletteDelegate : public QStyledItemDelegate
{
public:
    explicit GuiDesignerPaletteDelegate(QObject *parent = nullptr)
        : QStyledItemDelegate(parent)
    {
    }

    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const override
    {
        Q_UNUSED(option);
        Q_UNUSED(index);
        return QSize(76, 34);
    }

    void paint(QPainter *painter,
               const QStyleOptionViewItem &option,
               const QModelIndex &index) const override
    {
        painter->save();

        const QRect rect = option.rect;
        const bool selected = (option.state & QStyle::State_Selected);
        const bool hovered = (option.state & QStyle::State_MouseOver);

        if (selected) {
            painter->fillRect(rect, option.palette.highlight());
        } else if (hovered) {
            painter->fillRect(rect, option.palette.base().color().lighter(106));
        }

        const QVariant iconVar = index.data(Qt::DecorationRole);
        const QIcon icon = qvariant_cast<QIcon>(iconVar);
        const QSize iconSize(64, 24);
        const QPixmap pix = icon.pixmap(iconSize,
                                        selected ? QIcon::Selected : QIcon::Normal,
                                        QIcon::Off);
        const QRect iconRect(rect.x() + (rect.width() - iconSize.width()) / 2,
                             rect.y() + (rect.height() - iconSize.height()) / 2,
                             iconSize.width(), iconSize.height());
        painter->drawPixmap(iconRect.topLeft(), pix);

        if (selected) {
            painter->setPen(QPen(option.palette.highlight(), 1));
            painter->drawRect(rect.adjusted(0, 0, -1, -1));
        }

        painter->restore();
    }
};

class GuiDesignerToolbox : public QListWidget
{
public:
    explicit GuiDesignerToolbox(QWidget *parent = nullptr)
        : QListWidget(parent)
    {
        // A compact, two-column graphic palette. Its labels live in UserRole
        // and tooltips rather than beneath the 64x24 artwork.
        setViewMode(QListView::IconMode);
        setFlow(QListView::LeftToRight);
        setWrapping(true);
        setResizeMode(QListView::Adjust);
        setMovement(QListView::Static);
        setIconSize(QSize(64, 24));
        setGridSize(QSize(76, 34));
        setSpacing(2);
        setUniformItemSizes(true);
        setSelectionMode(QAbstractItemView::SingleSelection);
        setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setMouseTracking(true);
        setItemDelegate(new GuiDesignerPaletteDelegate(this));
        setDragEnabled(true);
        setDragDropMode(QAbstractItemView::DragOnly);
        setDefaultDropAction(Qt::CopyAction);
    }

    // The owning Designer supplies the real, zoom-matched canvas gadget image.
    std::function<QPixmap(const QString &)> gadgetPreviewRequested;

protected:
    void startDrag(Qt::DropActions) override
    {
        QListWidgetItem *item =
            currentItem();

        if (!item) {
            return;
        }

        auto *mime =
            new QMimeData;

        mime->setData(
            QString::fromLatin1(
                GuiDesignerGadgetMimeType),
            item->data(Qt::UserRole).toString().toUtf8());

        auto *drag =
            new QDrag(this);

        drag->setMimeData(mime);
        const QString type = item->data(Qt::UserRole).toString();
        QPixmap preview = gadgetPreviewRequested
            ? gadgetPreviewRequested(type) : QPixmap();
        if (preview.isNull())
            preview = item->icon().pixmap(QSize(64, 24));
        drag->setPixmap(preview);
        // Drop points already represent the centre of the new gadget.
        drag->setHotSpot(QPoint(preview.width() / 2, preview.height() / 2));
        drag->exec(Qt::CopyAction);
    }
};


// Menu editor drag/drop changes the data model, not only the tree display.
// Titles reorder as complete menus; entries may move within/between menus.
class GuiDesignerMenuTree : public QTreeWidget
{
public:
    explicit GuiDesignerMenuTree(QWidget *parent = nullptr)
        : QTreeWidget(parent)
    {
        setDragEnabled(true);
        setAcceptDrops(true);
        viewport()->setAcceptDrops(true);
        setDragDropMode(QAbstractItemView::InternalMove);
        setDefaultDropAction(Qt::MoveAction);
        setSelectionMode(QAbstractItemView::SingleSelection);
        setDropIndicatorShown(true);
    }

    // fromItem == -1 means a menu title, otherwise an item in fromMenu.
    // Destination indices are insertion positions in the original model.
    std::function<void(int, int, int, int)> reorderRequested;

protected:
    void dragMoveEvent(QDragMoveEvent *event) override
    {
        // This only paints feedback. The working dropEvent model update
        // remains the sole authority for reordering menu data.
        m_indicatorRect = QRect();
        m_indicatorLine = -1;
        QTreeWidgetItem *source = currentItem();
        QTreeWidgetItem *target = itemAt(event->position().toPoint());
        if (event->source() != this || !source || !target) {
            viewport()->update();
            event->ignore();
            return;
        }

        const bool movingTitle = !source->parent();
        if (movingTitle) {
            QTreeWidgetItem *title = target->parent() ? target->parent() : target;
            const QRect rect = visualItemRect(title);
            m_indicatorLine = event->position().y() >= rect.center().y()
                                  ? rect.bottom() + 1 : rect.top();
        } else if (target->parent()) {
            const QRect rect = visualItemRect(target);
            m_indicatorLine = event->position().y() >= rect.center().y()
                                  ? rect.bottom() + 1 : rect.top();
        } else {
            // Dropping an entry on a menu title appends it to that menu.
            m_indicatorRect = visualItemRect(target);
        }
        viewport()->update();
        event->acceptProposedAction();
    }

    void dragLeaveEvent(QDragLeaveEvent *event) override
    {
        m_indicatorRect = QRect();
        m_indicatorLine = -1;
        viewport()->update();
        QTreeWidget::dragLeaveEvent(event);
    }

    void paintEvent(QPaintEvent *event) override
    {
        QTreeWidget::paintEvent(event);
        if (m_indicatorLine < 0 && m_indicatorRect.isNull())
            return;

        QPainter painter(viewport());
        const QColor indicator = palette().color(QPalette::Highlight);
        if (!m_indicatorRect.isNull()) {
            painter.fillRect(m_indicatorRect, QColor(indicator.red(),
                             indicator.green(), indicator.blue(), 65));
            painter.setPen(QPen(indicator, 2));
            painter.drawRect(m_indicatorRect.adjusted(1, 1, -2, -2));
        } else {
            painter.setPen(QPen(indicator, 2));
            painter.drawLine(2, m_indicatorLine, viewport()->width() - 3,
                             m_indicatorLine);
        }
    }

    void dropEvent(QDropEvent *event) override
    {
        m_indicatorRect = QRect();
        m_indicatorLine = -1;
        viewport()->update();
        if (event->source() != this || !currentItem()) {
            event->ignore();
            return;
        }

        QTreeWidgetItem *source = currentItem();
        QTreeWidgetItem *target = itemAt(event->position().toPoint());
        if (!target) {
            event->ignore();
            return;
        }

        const int fromMenu = source->data(0, Qt::UserRole).toInt();
        const int fromItem = source->data(0, Qt::UserRole + 1).toInt();
        const bool movingTitle = source->parent() == nullptr;
        int toMenu = -1;
        int toIndex = -1;

        if (movingTitle) {
            // Drop anywhere on a menu title or its children to position
            // the complete menu before or after that title.
            QTreeWidgetItem *title = target->parent() ? target->parent() : target;
            const QRect rect = visualItemRect(title);
            toIndex = indexOfTopLevelItem(title)
                      + (event->position().y() >= rect.center().y() ? 1 : 0);
        } else if (target->parent()) {
            // Children can only be inserted between existing items.
            QTreeWidgetItem *parent = target->parent();
            toMenu = indexOfTopLevelItem(parent);
            const QRect rect = visualItemRect(target);
            toIndex = parent->indexOfChild(target)
                      + (event->position().y() >= rect.center().y() ? 1 : 0);
        } else {
            // Dropping on a menu heading appends the entry there,
            // including menus that have no items yet.
            toMenu = indexOfTopLevelItem(target);
            toIndex = target->childCount();
        }

        if (fromMenu < 0 || toIndex < 0
            || (!movingTitle && (fromItem < 0 || toMenu < 0))) {
            event->ignore();
            return;
        }

        // Qt must never move/reparent tree nodes itself. Apply the change
        // to the authoritative menu model after the drag has unwound.
        event->ignore();
        QTimer::singleShot(0, this, [this, fromMenu, fromItem, toMenu, toIndex]() {
            if (reorderRequested)
                reorderRequested(fromMenu, fromItem, toMenu, toIndex);
        });
    }

private:
    QRect m_indicatorRect;
    int m_indicatorLine = -1;
};


/*
 * Stage 25E: Pixel-faithful, Designer-only preview of a CoderGirl menu.
 * Mirrors cg_menu.c: 8x16 system font, 18px item rows, 8px separators,
 * 2px dark frame, 4px interior padding, and default palette pens.
 * This is a popup in the Qt IDE; it never executes applet C callbacks.
 */
class GuiDesignerMenuPreviewPopup : public QWidget
{
public:
    explicit GuiDesignerMenuPreviewPopup(const GuiDesignerMenuTitle &menu,
                                         int zoomPercent,
                                         QWidget *parent = nullptr)
        : QWidget(parent, Qt::Popup | Qt::FramelessWindowHint)
        , m_items(menu.items)
        , m_zoomPercent(qMax(100, zoomPercent))
    {
        setAttribute(Qt::WA_DeleteOnClose);
        setFocusPolicy(Qt::StrongFocus);
        setMouseTracking(true);
        setObjectName(QStringLiteral("coderGirlMenuPreviewPopup"));

        m_width = qMax(64, qMax(28, coderGirlTextWidth(menu.title) + 16));
        m_height = 12; // 2px border * 2 + 4px vertical padding * 2

        for (const GuiDesignerMenuItem &item : std::as_const(m_items)) {
            if (isSeparator(item)) {
                m_height += 8;
                continue;
            }
            m_height += 18;
            if (item.flags.contains(QStringLiteral("CG_MENUITEMF_TICKABLE"))
                || item.flags.contains(QStringLiteral("CG_MENUITEMF_TICKED"))) {
                m_markGutter = true;
            }
        }
        for (const GuiDesignerMenuItem &item : std::as_const(m_items)) {
            if (!isSeparator(item)) {
                // Firmware stores at most 31 characters plus NUL per item.
                m_width = qMax(m_width,
                    coderGirlTextWidth(item.text.left(31)) + 18
                    + (m_markGutter ? 24 : 0));
            }
        }
        setFixedSize((m_width * m_zoomPercent + 99) / 100,
                     (m_height * m_zoomPercent + 99) / 100);
    }

    std::function<void(int)> itemActivated;
    int logicalWidth() const { return m_width; }

protected:
    void paintEvent(QPaintEvent *) override
    {
        // Paint the exact native pixels first so 150%/200%/400% zoom retains
        // the blocky CoderGirl font instead of substituting a desktop font.
        QImage image(m_width, m_height, QImage::Format_ARGB32_Premultiplied);
        QPainter cg(&image);
        cg.fillRect(QRect(0, 0, m_width, m_height), coderGirlPen(16)); // PEN_WIN_TITLE
        cg.fillRect(QRect(2, 2, m_width - 4, m_height - 4), coderGirlPen(2)); // PEN_MENU_BG

        int y = 6; // CG_MENU_DROPDOWN_BORDER + CG_MENU_DROPDOWN_PAD
        for (int index = 0; index < m_items.size(); ++index) {
            const GuiDesignerMenuItem &item = m_items.at(index);
            if (isSeparator(item)) {
                cg.fillRect(QRect(6, y + 3, m_width - 12, 2), coderGirlPen(16));
                y += 8;
                continue;
            }

            const bool disabled = item.flags.contains(QStringLiteral("CG_MENUITEMF_DISABLED"));
            const bool hover = !disabled && index == m_hoverIndex;
            cg.fillRect(QRect(2, y, m_width - 4, 18),
                        coderGirlPen(hover ? 3 : 2));
            const QColor textPen = coderGirlPen(disabled ? 6 : (hover ? 2 : 16));
            int textX = 8;

            if (m_markGutter) {
                const int iconX = 6; // border (2) + CG_MENU_ICON_PAD_X (4)
                const int iconY = y + 1;
                if (item.flags.contains(QStringLiteral("CG_MENUITEMF_TICKED"))) {
                    drawCoderGirlText(cg, iconX + 4, iconY,
                                      QString(QChar(0x02)), textPen);
                } else if (item.flags.contains(QStringLiteral("CG_MENUITEMF_TICKABLE"))) {
                    cg.fillRect(QRect(iconX + 3, iconY + 3, 10, 10), coderGirlPen(2));
                    cg.fillRect(QRect(iconX + 3, iconY + 3, 10, 1), textPen);
                    cg.fillRect(QRect(iconX + 3, iconY + 12, 10, 1), textPen);
                    cg.fillRect(QRect(iconX + 3, iconY + 3, 1, 10), textPen);
                    cg.fillRect(QRect(iconX + 12, iconY + 3, 1, 10), textPen);
                }
                textX += 24; // CG_MENU_ICON_GUTTER_W
            }
            drawCoderGirlText(cg, textX, y + 1, item.text.left(31), textPen);
            y += 18;
        }
        cg.end();

        QPainter screen(this);
        screen.setRenderHint(QPainter::SmoothPixmapTransform, false);
        screen.drawImage(rect(), image);
    }

    void mouseMoveEvent(QMouseEvent *event) override
    {
        const int next = indexAt(event->position().toPoint());
        if (m_hoverIndex != next) {
            m_hoverIndex = next;
            update();
        }
        event->accept();
    }

    void leaveEvent(QEvent *event) override
    {
        m_hoverIndex = -1;
        update();
        QWidget::leaveEvent(event);
    }

    void mousePressEvent(QMouseEvent *event) override
    {
        if (event->button() == Qt::LeftButton) {
            event->accept();
            return;
        }
        QWidget::mousePressEvent(event);
    }

    void mouseReleaseEvent(QMouseEvent *event) override
    {
        if (event->button() == Qt::LeftButton) {
            const int index = indexAt(event->position().toPoint());
            event->accept();
            activate(index);
            return;
        }
        QWidget::mouseReleaseEvent(event);
    }

    void keyPressEvent(QKeyEvent *event) override
    {
        if (event->key() == Qt::Key_Escape) {
            close();
            event->accept();
            return;
        }
        if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
            activate(m_hoverIndex);
            event->accept();
            return;
        }
        if (event->key() == Qt::Key_Down || event->key() == Qt::Key_Up) {
            const int count = m_items.size();
            if (count) {
                const int direction = event->key() == Qt::Key_Down ? 1 : -1;
                int index = m_hoverIndex;
                for (int step = 0; step < count; ++step) {
                    index = (index + direction + count) % count;
                    if (!isSeparator(m_items.at(index))
                        && !m_items.at(index).flags.contains(QStringLiteral("CG_MENUITEMF_DISABLED"))) {
                        m_hoverIndex = index;
                        update();
                        break;
                    }
                }
            }
            event->accept();
            return;
        }
        QWidget::keyPressEvent(event);
    }

private:
    static bool isSeparator(const GuiDesignerMenuItem &item)
    {
        return item.text.trimmed() == QStringLiteral("---")
            || item.flags.contains(QStringLiteral("CG_MENUITEMF_SEPARATOR"));
    }

    int indexAt(const QPoint &devicePos) const
    {
        const int x = devicePos.x() * 100 / m_zoomPercent;
        const int ly = devicePos.y() * 100 / m_zoomPercent;
        if (x < 2 || x >= m_width - 2)
            return -1;
        int y = 6;
        for (int index = 0; index < m_items.size(); ++index) {
            const GuiDesignerMenuItem &item = m_items.at(index);
            const int height = isSeparator(item) ? 8 : 18;
            if (ly >= y && ly < y + height)
                return !isSeparator(item)
                       && !item.flags.contains(QStringLiteral("CG_MENUITEMF_DISABLED"))
                    ? index : -1;
            y += height;
        }
        return -1;
    }

    void activate(int index)
    {
        if (index < 0 || index >= m_items.size())
            return;
        const std::function<void(int)> callback = itemActivated;
        close(); // Qt::WA_DeleteOnClose defers deletion until after event handling.
        if (callback)
            callback(index);
    }

    QList<GuiDesignerMenuItem> m_items;
    int m_zoomPercent = 100;
    int m_width = 64;
    int m_height = 12;
    int m_hoverIndex = -1;
    bool m_markGutter = false;
};

