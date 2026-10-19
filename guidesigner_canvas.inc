// Stage 3.71: moved intact from guidesigner.cpp; included once inside GuiDesignerDetail.
class GuiDesignerCanvas : public QWidget
{
public:
    GuiDesignerCanvas(GuiDesignerWindow *windowModel,
                      QList<GuiDesignerGadget> *gadgets,
                      QList<GuiDesignerMenuTitle> *menus,
                      QWidget *parent = nullptr)
        : QWidget(parent)
        , m_window(windowModel)
        , m_gadgets(gadgets)
        , m_menus(menus)
    {
        setMouseTracking(true);
        setAcceptDrops(true);
        setFocusPolicy(Qt::StrongFocus);
        setZoomPercent(200);
    }

    std::function<void(int)> selectionChanged;
    std::function<void()> geometryChangeStarted;
    std::function<void()> geometryCommitted;
    std::function<void(const QString &, const QPoint &)> gadgetDropped;
    std::function<void(int)> gadgetDoubleClicked;
    std::function<void(int, int)> menuItemActivated;
    std::function<void()> copyRequested;
    std::function<void()> pasteRequested;
    std::function<void()> deleteRequested;
    std::function<void()> undoRequested;
    std::function<void(int, int, bool)> nudgeRequested;
    std::function<void(int, int, bool)> resizeRequested;
    std::function<void(bool)> layerRequested;
    // Printable canvas keys edit a selected gadget's Text without taking focus
    // away from the designer. The owner handles Undo and property synchronisation.
    std::function<void(const QString &, bool)> textInputRequested;
    std::function<bool()> textEditingFinished;

    int selectedIndex() const { return m_selected; }

    // Only the canvas selection is multi-valued; the property editor retains
    // the current/primary gadget, and .sbui serialization remains unchanged.
    int selectionCount() const { return m_multiSelected.size(); }

    QList<int> selectedGroupIndices() const { return m_multiSelected; }

    // Return the single shared translation that fits every selected gadget
    // inside the SIDBOX client area. Do not clamp gadgets individually: that
    // would silently change the spacing between them at window boundaries.
    QPoint boundedGroupTranslation(const QPoint &requested) const
    {
        if (!m_gadgets || m_multiSelected.size() < 2)
            return QPoint();

        const QSize client = clientViewportSize();
        int minDx = -200000, minDy = -200000;
        int maxDx = 200000, maxDy = 200000;
        for (int index : m_multiSelected) {
            if (index < 0 || index >= m_gadgets->size())
                return QPoint();
            const GuiDesignerGadget &g = m_gadgets->at(index);
            if (!visibleOnTab(g) || !canGroupMove(g))
                return QPoint();
            const QRect &r = g.rect;
            minDx = qMax(minDx, -r.left());
            minDy = qMax(minDy, -r.top());
            maxDx = qMin(maxDx, client.width() - r.right() - 1);
            maxDy = qMin(maxDy, client.height() - r.bottom() - 1);
        }
        return QPoint(minDx <= maxDx ? qBound(minDx, requested.x(), maxDx) : 0,
                      minDy <= maxDy ? qBound(minDy, requested.y(), maxDy) : 0);
    }

    void translateSelectedGroup(const QPoint &delta)
    {
        if (!m_gadgets || m_multiSelected.size() < 2 || delta.isNull())
            return;
        for (int index : m_multiSelected)
            (*m_gadgets)[index].rect.translate(delta);
        update();
    }

    // The undo history stores the selected group along with the geometry.
    // The .sbui file format is NOT affected; this is editor-only state.
    void restoreGroupSelection(const QList<int> &indices)
    {
        m_multiSelected.clear();
        if (!m_gadgets || indices.size() < 2)
            return;
        for (int index : indices) {
            if (index < 0 || index >= m_gadgets->size()
                || m_multiSelected.contains(index))
                continue;
            const GuiDesignerGadget &g = m_gadgets->at(index);
            if (visibleOnTab(g) && canGroupMove(g))
                m_multiSelected.append(index);
        }
        if (m_multiSelected.size() < 2) {
            m_multiSelected.clear();
        } else if (!m_multiSelected.contains(m_selected)) {
            m_selected = m_multiSelected.first();
        }
        update();
    }

    void setGridSnap(int pixels)
    {
        m_gridSnap =
            qMax(
                0,
                pixels);

        update();
    }

    int gridSnap() const
    {
        return m_gridSnap;
    }

    // Render the SAME CoderGirl gadget artwork used on the canvas, at the
    // current zoom. Painting at native resolution first keeps 150% sharp and
    // ensures the drag ghost has the actual new gadget dimensions.
    QPixmap gadgetDragPixmap(const GuiDesignerGadget &g) const
    {
        const QSize logicalSize = g.rect.size();
        if (logicalSize.isEmpty())
            return QPixmap();

        QImage logical(logicalSize, QImage::Format_ARGB32_Premultiplied);
        logical.fill(Qt::transparent);
        {
            QPainter painter(&logical);
            painter.setRenderHint(QPainter::Antialiasing, false);
            drawGadget(painter, g, QRect(QPoint(0, 0), logicalSize),
                       m_window->backPen);
        }
        const QSize zoomed((logicalSize.width() * m_zoomPercent) / 100,
                           (logicalSize.height() * m_zoomPercent) / 100);
        return QPixmap::fromImage(logical.scaled(zoomed,
                                  Qt::IgnoreAspectRatio,
                                  Qt::FastTransformation));
    }

    QSize clientViewportSize() const
    {
        return clientViewportRect().size();
    }

    // Inclusive range of legal top-left positions for a virtual TabGroup.
    // All pages share this movement limit, including pages not in preview.
    QRect tabGroupPositionBounds(int index) const
    {
        if (!m_gadgets || index < 0 || index >= m_gadgets->size()
            || m_gadgets->at(index).type != QStringLiteral("TabGroup"))
            return QRect();
        const GuiDesignerGadget &group = m_gadgets->at(index);
        const QSize client = clientViewportSize();
        int lowX = -group.rect.left();
        int lowY = -group.rect.top();
        int highX = client.width() - group.rect.right() - 1;
        int highY = client.height() - group.rect.bottom() - 1;
        for (int i = 0; i < m_gadgets->size(); ++i) {
            if (i == index || m_gadgets->at(i).tabOwner != group.name)
                continue;
            const QRect r = m_gadgets->at(i).rect;
            lowX = qMax(lowX, -r.left());
            lowY = qMax(lowY, -r.top());
            highX = qMin(highX, client.width() - r.right() - 1);
            highY = qMin(highY, client.height() - r.bottom() - 1);
        }
        const QPoint pos = group.rect.topLeft();
        // An old design might contain an off-screen gadget; don't let
        // incompatible constraints unexpectedly move anything.
        if (lowX > highX || lowY > highY)
            return QRect(pos, QSize(1, 1));
        return QRect(QPoint(pos.x() + lowX, pos.y() + lowY),
                     QPoint(pos.x() + highX, pos.y() + highY));
    }

    // Move the selected virtual TabGroup and ALL its member gadgets. These
    // stay window-relative: no new parent-coordinate system is introduced.
    bool moveTabGroupWithMembers(int index, const QPoint &wanted)
    {
        if (!m_gadgets || index < 0 || index >= m_gadgets->size()
            || m_gadgets->at(index).type != QStringLiteral("TabGroup"))
            return false;
        const GuiDesignerGadget &group = m_gadgets->at(index);
        const QRect bounds = tabGroupPositionBounds(index);
        const QPoint position(qBound(bounds.left(), wanted.x(), bounds.right()),
                              qBound(bounds.top(), wanted.y(), bounds.bottom()));
        const QPoint delta = position - group.rect.topLeft();
        if (delta.isNull()) return false;

        const QString owner = group.name;
        for (int i = 0; i < m_gadgets->size(); ++i) {
            GuiDesignerGadget &g = (*m_gadgets)[i];
            if (i == index || g.tabOwner == owner)
                g.rect.translate(delta);
        }
        update();
        return true;
    }

    /*
     * Public bridge used by the designer property panel.
     * clampWindowToScreen() itself remains an internal Canvas helper.
     */
    void enforceWindowScreenBounds()
    {
        clampWindowToScreen();
        update();
    }

    void setSelectedIndex(int index)
    {
        // A normal click or a programmatic selection starts a new selection.
        // This also invalidates group indices when deleting/reordering gadgets.
        m_multiSelected.clear();
        m_selected = index;
        update();
        if (selectionChanged) {
            selectionChanged(index);
        }
    }

    void setZoomPercent(int percent)
    {
        /*
         * Keep zoom as an INTEGER percentage. The preview is always rendered at
         * the native 480x320 CoderGirl resolution first, then stretched with
         * nearest-neighbour pixels. Logical gadget/window coordinates therefore
         * never become fractional at 150%.
         */
        switch (percent) {
        case 100:
        case 150:
        case 200:
        case 400:
            m_zoomPercent = percent;
            break;
        default:
            m_zoomPercent = 100;
            break;
        }

        setFixedSize(
            (480 * m_zoomPercent) / 100,
            (320 * m_zoomPercent) / 100);

        update();
    }

    int zoomPercent() const
    {
        return m_zoomPercent;
    }

private:
    void drawLogicalCanvas(QPainter &p)
    {
        p.setRenderHint(
            QPainter::Antialiasing,
            false);

        /*
         * Sidbox display background. The real GUI is indexed-colour; the
         * preview converts the exact supplied CLUT entry to desktop ARGB.
         */
        p.fillRect(
            QRect(
                0,
                0,
                480,
                320),
            coderGirlPen(16));

        p.setPen(
            coderGirlPen(6));

        p.drawRect(
            0,
            0,
            479,
            319);

        if (m_gridSnap > 1) {
            QColor gridColour =
                coderGirlPen(5);

            gridColour.setAlpha(70);

            p.setPen(
                gridColour);

            for (int y = 0;
                 y < 320;
                 y += m_gridSnap) {
                for (int x = 0;
                     x < 480;
                     x += m_gridSnap) {
                    p.drawPoint(
                        x,
                        y);
                }
            }
        }

        /*
         * CoderGirl menu bar:
         *   22 px total
         *   19 px fill
         *    2 px black rule at y=19
         *
         * Text is the same 8x8 bitmap stretched vertically to 8x16 that the
         * firmware renders.
         */
        if (m_menus
            && !m_menus->isEmpty()) {
            p.fillRect(
                QRect(
                    0,
                    0,
                    479,
                    19),
                coderGirlPen(2));

            p.fillRect(
                QRect(
                    0,
                    19,
                    479,
                    2),
                coderGirlPen(16));

            int x = 3;

            for (const GuiDesignerMenuTitle &menu :
                 std::as_const(*m_menus)) {
                const int width = qMax(28,
                    coderGirlTextWidth(menu.title) + 16);

                drawCoderGirlText(
                    p,
                    x + 8,
                    2,
                    menu.title,
                    coderGirlPen(16));

                x += width + 2;
            }
        }

        if (!m_window
            || !m_gadgets) {
            return;
        }

        const QRect wr =
            m_window->rect;

        const bool noBorder =
            designerWindowFlag(
                m_window->flags,
                QStringLiteral(
                    "SBX_WF_NOBORDER"));

        const bool hasTitle =
            designerWindowFlag(
                m_window->flags,
                QStringLiteral(
                    "SBX_WF_TITLE_BAR"));

        const bool hasClose =
            designerWindowFlag(
                m_window->flags,
                QStringLiteral(
                    "SBX_WF_CLOSE"));

        const bool hasMinimise =
            designerWindowFlag(
                m_window->flags,
                QStringLiteral(
                    "SBX_WF_MINIMISE"));

        const bool hasMaxRestore =
            designerWindowFlag(
                m_window->flags,
                QStringLiteral(
                    "SBX_WF_MAXRESTORE"));

        const bool hasZOrder =
            designerWindowFlag(
                m_window->flags,
                QStringLiteral(
                    "SBX_WF_ZORDER"));

        const bool resizable =
            designerWindowFlag(
                m_window->flags,
                QStringLiteral(
                    "SBX_WF_RESIZABLE"));

        constexpr int WinBorder = 4;
        constexpr int WinTitleHeight = 16;
        constexpr int TitleChromeHeight =
            WinTitleHeight + WinBorder;
        constexpr int TitleButtonWidth = 20;
        constexpr int ResizeGlyphSize = 20;

        const int borderPen =
            3; // focused PEN_WIN_BORDER_ACTIVE

        const bool dockRight =
            dockRightEnabled();

        const bool dockBottom =
            dockBottomEnabled();

        /*
         * Keep INNER and CLIENT separate just like the firmware: normal gadgets
         * are clipped to CLIENT while dock bands live in INNER.
         */
        const QRect innerRect =
            windowInnerRect();

        const QRect clientRect =
            clientViewportRect();

        /*
         * The client fill is what w->backColour paints on the hardware.
         */
        if (clientRect.width() > 0
            && clientRect.height() > 0) {
            p.fillRect(
                clientRect,
                coderGirlPen(
                    m_window->backPen));
        }

        if (!noBorder) {
            /*
             * Thick active border. The photo/reference and firmware both use
             * PEN_WIN_BORDER_ACTIVE (pen 3) for the focused window.
             */
            p.setPen(
                coderGirlPen(
                    borderPen));

            for (int i = 0;
                 i < WinBorder;
                 ++i) {
                const int left =
                    wr.left() + i;

                const int top =
                    wr.top() + i;

                const int right =
                    wr.right() - i;

                const int bottom =
                    wr.bottom() - i;

                if (left > right
                    || top > bottom) {
                    break;
                }

                p.drawLine(
                    left,
                    top,
                    right,
                    top);

                p.drawLine(
                    left,
                    bottom,
                    right,
                    bottom);

                p.drawLine(
                    left,
                    top,
                    left,
                    bottom);

                p.drawLine(
                    right,
                    top,
                    right,
                    bottom);
            }

            /*
             * CoderGirl paints a full 20px chrome strip on the physical RIGHT
             * edge when a right dock exists, while layoutWindow reserves a
             * 16px SB_SCROLL_THICK band inside INNER for the docked control.
             */
            if (dockRight) {
                const QRect rightDockChrome(
                    wr.right()
                        - ResizeGlyphSize
                        + 1,
                    wr.y(),
                    ResizeGlyphSize,
                    wr.height());

                p.fillRect(
                    rightDockChrome,
                    coderGirlPen(
                        borderPen));
            }

            if (resizable) {
                const QRect grip(
                    wr.right()
                        - ResizeGlyphSize
                        + 1,
                    wr.bottom()
                        - ResizeGlyphSize
                        + 1,
                    ResizeGlyphSize,
                    ResizeGlyphSize);

                const QRect bottomBand(
                    wr.x()
                        + WinBorder,
                    grip.y() + 1,
                    qMax(
                        0,
                        wr.width()
                            - WinBorder * 2),
                    ResizeGlyphSize - 2);

                p.fillRect(
                    bottomBand,
                    coderGirlPen(
                        borderPen));

                p.fillRect(
                    grip,
                    coderGirlPen(
                        borderPen));

                drawCoderGirlBevel(
                    p,
                    grip,
                    false);

                drawCoderGirlResizeGlyph(
                    p,
                    grip);
            }

            /*
             * Match cg_windowex.c: resize/dock chrome is painted first, then the
             * frame bevels polish the final right/bottom edges. The old preview
             * did this in the opposite order, allowing the blue gutter to cover
             * the bevel and leave an extra blue line at the bottom/right.
             */
            drawCoderGirlBevel(
                p,
                wr,
                false);

            if (clientRect.width() > 0
                && clientRect.height() > 0) {
                drawCoderGirlBevel(
                    p,
                    clientRect.adjusted(
                        -1,
                        -1,
                        1,
                        1),
                    true);
            }
        }

        if (hasTitle) {
            /*
             * The hardware title strip is 20 px high (16 font + 4 border).
             * Close is on the LEFT. Minimise, maximise and z-order are packed
             * from the right exactly like cg_windowex.c.
             */
            const QRect titleRect(
                wr.x(),
                wr.y(),
                wr.width(),
                TitleChromeHeight);

            p.fillRect(
                titleRect,
                coderGirlPen(
                    borderPen));

            int textX =
                wr.x()
                + WinBorder
                + 4;

            int textBandX =
                wr.x();

            int textBandWidth =
                wr.width();

            int right =
                wr.x()
                + wr.width();

            if (hasZOrder) {
                right -=
                    TitleButtonWidth;

                const QRect button(
                    right,
                    wr.y(),
                    TitleButtonWidth,
                    TitleChromeHeight);

                drawCoderGirlTitleButton(
                    p,
                    button,
                    borderPen);

                drawCoderGirlZOrderGlyph(
                    p,
                    button);

                textBandWidth -=
                    TitleButtonWidth;
            }

            if (hasMaxRestore) {
                right -=
                    TitleButtonWidth;

                const QRect button(
                    right,
                    wr.y(),
                    TitleButtonWidth,
                    TitleChromeHeight);

                drawCoderGirlTitleButton(
                    p,
                    button,
                    borderPen);

                drawCoderGirlMaxGlyph(
                    p,
                    button);

                textBandWidth -=
                    TitleButtonWidth;
            }

            if (hasMinimise) {
                right -=
                    TitleButtonWidth;

                const QRect button(
                    right,
                    wr.y(),
                    TitleButtonWidth,
                    TitleChromeHeight);

                drawCoderGirlTitleButton(
                    p,
                    button,
                    borderPen);

                drawCoderGirlMinimiseGlyph(
                    p,
                    button);

                textBandWidth -=
                    TitleButtonWidth;
            }

            if (hasClose) {
                const QRect button(
                    wr.x(),
                    wr.y(),
                    TitleButtonWidth,
                    TitleChromeHeight);

                drawCoderGirlTitleButton(
                    p,
                    button,
                    borderPen);

                drawCoderGirlCloseGlyph(
                    p,
                    button);

                textX =
                    wr.x()
                    + TitleButtonWidth
                    + 4;

                textBandX =
                    wr.x()
                    + TitleButtonWidth;

                textBandWidth -=
                    TitleButtonWidth;
            }

            if (textBandWidth > 0) {
                drawCoderGirlBevel(
                    p,
                    QRect(
                        textBandX,
                        wr.y(),
                        textBandWidth,
                        TitleChromeHeight),
                    false);
            }

            const int maxChars =
                qBound(
                    0,
                    (textBandWidth - 8)
                        / 8,
                    64);

            drawCoderGirlText(
                p,
                textX,
                wr.y() + 2,
                m_window->title.left(
                    maxChars),
                coderGirlPen(16));
        }

        const QPoint origin =
            clientOrigin();

        /*
         * Real CoderGirl gadgets are rendered inside w->clientrect. Clip the
         * designer the same way so controls cannot cover title/frame/resize
         * chrome when the Window is made smaller.
         */
        p.save();
        p.setClipRect(
            clientRect);

        for (int paintPass = 0; paintPass < 3; ++paintPass) {
        for (int i = 0;
             i < m_gadgets->size();
             ++i) {
            const GuiDesignerGadget &g =
                m_gadgets->at(i);
            if (!visibleOnTab(g)) continue;
            if (paintPass == 0 && g.type != QStringLiteral("TabGroup")) continue;
            if (paintPass == 1 && (g.type == QStringLiteral("TabGroup") || isVirtualDesignerGadget(g.type))) continue;
            if (paintPass == 2 && !isVirtualDesignerGadget(g.type)) continue;

            const QRect gr = gadgetPreviewRect(g);
            if (isDockedScrollbar(g)) {
                p.save();
                p.setClipRect(innerRect, Qt::ReplaceClip);
            }
            drawGadget(p, g, gr, m_window->backPen);

            if (!g.enabled) {
                /*
                 * Designer-only disabled-state cue. Runtime state is emitted
                 * through API->gui->gadgets->enabled().
                 *
                 * IMPORTANT: clip the diagonal hatch to this gadget. Without
                 * the clip the long diagonal lines escape across neighbouring
                 * gadgets, which is the visual corruption seen in V8.
                 */
                p.save();
                p.setClipRect(
                    gr,
                    Qt::IntersectClip);

                QColor disabledOverlay(
                    0,
                    0,
                    0,
                    105);

                p.fillRect(
                    gr,
                    disabledOverlay);

                p.setPen(
                    coderGirlPen(6));

                for (int line =
                         gr.left()
                         - gr.height();
                     line
                         <= gr.right();
                     line += 8) {
                    p.drawLine(
                        line,
                        gr.bottom(),
                        line
                            + gr.height(),
                        gr.top());
                }

                p.restore();
            }
            if (isDockedScrollbar(g))
                p.restore();

        }

        } // TabGroup backgrounds, ordinary contents, then non-visual timer icons

        // One outline per selected gadget. Group selection deliberately has
        // no resize handles: Shift-marquee groups MOVE as one unit, not resize.
        // Docked scrollbars keep their original, separate hit/display rules.
        p.setClipRect(innerRect, Qt::ReplaceClip);
        const QColor selectionPink(255, 90, 170);
        const bool groupSelected = m_multiSelected.size() > 1;
        const QList<int> outlined = groupSelected
            ? m_multiSelected : QList<int>{m_selected};
        for (int index : outlined) {
            if (index < 0 || index >= m_gadgets->size()
                || !visibleOnTab(m_gadgets->at(index)))
                continue;

            const GuiDesignerGadget &g = m_gadgets->at(index);
            const QRect gr = gadgetPreviewRect(g);
            p.setPen(QPen(selectionPink, 1, Qt::DashLine));
            p.setBrush(Qt::NoBrush);
            p.drawRect(gr.adjusted(-2, -2, 1, 1));

            if (!groupSelected && g.type != QStringLiteral("GridSelect")
                && !isVirtualDesignerGadget(g.type)) {
                p.setPen(coderGirlPen(16));
                p.setBrush(selectionPink);
                for (const QRect &handle : windowResizeHandles(gr)) {
                    p.drawRect(handle);
                    p.fillRect(handle.adjusted(1, 1, -1, -1), selectionPink);
                }
            }
        }

        p.restore();

        /*
         * Design-time dock indication only. The checkers make the reserved
         * 16px dock bands unmistakable without changing generated C.
         */
        constexpr int DockThickness = 16;

        if (dockRight
            && innerRect.width() > 0
            && innerRect.height() > 0) {
            drawDockChecker(
                p,
                QRect(
                    innerRect.right()
                        - DockThickness
                        + 1,
                    innerRect.top(),
                    DockThickness,
                    innerRect.height()));
        }

        if (dockBottom
            && innerRect.width() > 0
            && innerRect.height() > 0) {
            drawDockChecker(
                p,
                QRect(
                    innerRect.left(),
                    innerRect.bottom()
                        - DockThickness
                        + 1,
                    innerRect.width(),
                    DockThickness));
        }

        if (m_selected < 0) {
            const QColor anchorColour(
                255,
                90,
                170);

            p.setPen(
                QPen(
                    anchorColour,
                    1,
                    Qt::DashLine));

            p.setBrush(
                Qt::NoBrush);

            // Match gadget reticles: remove the extra right/bottom pixel.
            // No change to window geometry or the resize handles.
            p.drawRect(
                wr.adjusted(
                    -2,
                    -2,
                    1,
                    1));

            /*
             * Eight resize anchors around the actual CoderGirl window.
             * These live in logical 480x320 coordinates, so zoom never changes
             * the geometry being edited.
             */
            p.setPen(
                coderGirlPen(16));

            p.setBrush(
                anchorColour);

            for (const QRect &handle :
                 windowResizeHandles(wr)) {
                p.drawRect(handle);
                p.fillRect(
                    handle.adjusted(
                        1,
                        1,
                        -1,
                        -1),
                    anchorColour);
            }
        }
     }

protected:
    void paintEvent(QPaintEvent *) override
    {
        /*
         * Draw at true Sidbox resolution first. This avoids fractional painter
         * transforms at 150% and keeps 100/150/200/400% as pure integer-sized
         * nearest-neighbour previews.
         */
        QImage logical(
            480,
            320,
            QImage::Format_ARGB32_Premultiplied);

        logical.fill(
            Qt::transparent);

        {
            QPainter logicalPainter(
                &logical);

            drawLogicalCanvas(
                logicalPainter);

            // Show the selection marquee IN logical SIDBOX pixels, so it
            // remains crisp at all supported Designer zoom levels.
            if (m_marqueeSelecting && !m_marqueeRect.isEmpty()) {
                logicalPainter.save();
                logicalPainter.setClipRect(clientViewportRect());
                logicalPainter.fillRect(m_marqueeRect, QColor(70, 180, 255, 42));
                logicalPainter.setPen(QPen(QColor(95, 205, 255), 1, Qt::DashLine));
                logicalPainter.setBrush(Qt::NoBrush);
                logicalPainter.drawRect(m_marqueeRect);
                logicalPainter.restore();
            }
        }

        QPainter screenPainter(
            this);

        screenPainter.setRenderHint(
            QPainter::Antialiasing,
            false);

        screenPainter.setRenderHint(
            QPainter::SmoothPixmapTransform,
            false);

        screenPainter.drawImage(
            QRect(
                0,
                0,
                width(),
                height()),
            logical,
            logical.rect());
    }

    void dragEnterEvent(QDragEnterEvent *event) override
    {
        if (event->mimeData()
            && event->mimeData()->hasFormat(
                QString::fromLatin1(
                    GuiDesignerGadgetMimeType))) {
            event->setDropAction(Qt::CopyAction);
            event->accept();
            return;
        }

        QWidget::dragEnterEvent(event);
    }

    void dragMoveEvent(QDragMoveEvent *event) override
    {
        if (!event->mimeData()
            || !event->mimeData()->hasFormat(
                QString::fromLatin1(
                    GuiDesignerGadgetMimeType))) {
            event->ignore();
            return;
        }

        const QPoint logical =
            toLogical(event->position());

        if (clientViewportRect().contains(logical)) {
            event->setDropAction(Qt::CopyAction);
            event->accept();
        } else {
            event->ignore();
        }
    }

    void dropEvent(QDropEvent *event) override
    {
        if (!event->mimeData()
            || !event->mimeData()->hasFormat(
                QString::fromLatin1(
                    GuiDesignerGadgetMimeType))) {
            event->ignore();
            return;
        }

        const QPoint logical =
            toLogical(event->position());

        const QRect client =
            clientViewportRect();

        if (!client.contains(logical)) {
            event->ignore();
            return;
        }

        const QString type =
            QString::fromUtf8(
                event->mimeData()->data(
                    QString::fromLatin1(
                        GuiDesignerGadgetMimeType)))
                .trimmed();

        if (type.isEmpty()) {
            event->ignore();
            return;
        }

        QPoint local =
            logical - clientOrigin();

        if (m_gridSnap > 1) {
            local.setX(
                snapValue(local.x()));

            local.setY(
                snapValue(local.y()));
        }

        if (gadgetDropped) {
            gadgetDropped(
                type,
                local);
        }

        event->setDropAction(Qt::CopyAction);
        event->accept();
    }

    void keyPressEvent(QKeyEvent *event) override
    {
        if (!event) {
            QWidget::keyPressEvent(event);
            return;
        }

        /*
         * Keyboard editing belongs to the design surface only. Property text
         * editors keep their normal Ctrl+C/Ctrl+V behaviour because this
         * handler only runs while the Canvas owns keyboard focus.
         */
        if (event->matches(QKeySequence::Undo)) {
            if (undoRequested) {
                undoRequested();
                event->accept();
                return;
            }
        }

        if (event->matches(QKeySequence::Copy)) {
            if (m_selected >= 0
                && copyRequested) {
                copyRequested();
                event->accept();
                return;
            }
        }

        if (event->matches(QKeySequence::Paste)) {
            if (pasteRequested) {
                pasteRequested();
                event->accept();
                return;
            }
        }

        if (event->key() == Qt::Key_Delete
            && !(event->modifiers()
                 & (Qt::ControlModifier
                    | Qt::AltModifier
                    | Qt::MetaModifier))) {
            if (m_selected >= 0
                && deleteRequested) {
                deleteRequested();
                event->accept();
                return;
            }
        }

        /*
         * Arrow keys nudge the selected gadget by one current grid unit.
         * "Snap Off" deliberately means a one-pixel nudge rather than no
         * movement, so the keyboard is always useful for precision placement.
         */
        if (m_selected >= 0
            && !(event->modifiers()
                 & (Qt::ControlModifier
                    | Qt::AltModifier
                    | Qt::MetaModifier))) {
            int dx = 0;
            int dy = 0;

            switch (event->key()) {
            case Qt::Key_Left:
                dx = -1;
                break;
            case Qt::Key_Right:
                dx = 1;
                break;
            case Qt::Key_Up:
                dy = -1;
                break;
            case Qt::Key_Down:
                dy = 1;
                break;
            default:
                break;
            }

            if ((dx != 0 || dy != 0)
                && nudgeRequested) {
                nudgeRequested(
                    dx,
                    dy,
                    event->isAutoRepeat());
                event->accept();
                return;
            }
        }

        if (m_selected >= 0
            && (event->modifiers() & Qt::ControlModifier)
            && !(event->modifiers()
                 & (Qt::ShiftModifier | Qt::AltModifier | Qt::MetaModifier))) {
            int dw = 0;
            int dh = 0;
            switch (event->key()) {
            case Qt::Key_Left:  dw = -1; break;
            case Qt::Key_Right: dw = 1; break;
            case Qt::Key_Up:    dh = -1; break;
            case Qt::Key_Down:  dh = 1; break;
            default: break;
            }
            if ((dw || dh) && resizeRequested) {
                resizeRequested(dw, dh, event->isAutoRepeat());
                event->accept();
                return;
            }
        }

        // Keep editing confined to the selected canvas gadget. Shortcuts above
        // take priority; Ctrl/Alt/Meta combinations must remain shortcuts.
        if (m_selected >= 0
            && !(event->modifiers() & (Qt::ControlModifier
                                     | Qt::AltModifier
                                     | Qt::MetaModifier))) {
            if ((event->key() == Qt::Key_Return
                 || event->key() == Qt::Key_Enter
                 || event->key() == Qt::Key_Escape)
                && textEditingFinished && textEditingFinished()) {
                event->accept();
                return;
            }

            if (event->key() == Qt::Key_Backspace && textInputRequested) {
                textInputRequested(QString(), true);
                event->accept();
                return;
            }

            const QString typed = event->text();
            bool printable = !typed.isEmpty();
            for (const QChar ch : typed) {
                if (!ch.isPrint()) {
                    printable = false;
                    break;
                }
            }
            if (printable && textInputRequested) {
                textInputRequested(typed, false);
                event->accept();
                return;
            }
        }

        QWidget::keyPressEvent(event);
    }

    void focusOutEvent(QFocusEvent *event) override
    {
        // Typing is one Undo operation until the canvas loses focus.
        if (textEditingFinished) textEditingFinished();
        QWidget::focusOutEvent(event);
    }

    void mouseDoubleClickEvent(QMouseEvent *event) override
    {
        if (!m_window
            || !m_gadgets
            || event->button() != Qt::LeftButton) {
            QWidget::mouseDoubleClickEvent(event);
            return;
        }

        const QPoint logical =
            toLogical(event->position());

        const QRect client =
            clientViewportRect();

        if (!windowInnerRect().contains(logical)) {
            QWidget::mouseDoubleClickEvent(event);
            return;
        }

        const QPoint origin =
            clientOrigin();

        for (int i = m_gadgets->size()-1; i >= 0; --i) {
            if (isVirtualDesignerGadget(m_gadgets->at(i).type)
                && m_gadgets->at(i).rect.translated(origin).contains(logical)) {
                setSelectedIndex(i);
                if (gadgetDoubleClicked) gadgetDoubleClicked(i);
                event->accept();
                return;
            }
        }

        for (int i =
                 static_cast<int>(
                     m_gadgets->size())
                 - 1;
             i >= 0;
             --i) {
            if (!visibleOnTab(m_gadgets->at(i))) continue;
            const GuiDesignerGadget &g = m_gadgets->at(i);
            const QRect gadgetRect = gadgetPreviewRect(g).intersected(
                isDockedScrollbar(g) ? windowInnerRect() : client);

            if (!gadgetRect.contains(logical)) {
                continue;
            }

            setSelectedIndex(i);

            if (gadgetDoubleClicked) {
                gadgetDoubleClicked(i);
            }

            event->accept();
            return;
        }

        QWidget::mouseDoubleClickEvent(event);
    }

    void mousePressEvent(QMouseEvent *event) override
    {
        if (event && event->button() == Qt::LeftButton) {
            setFocus(Qt::MouseFocusReason);
        }

        if (!m_window || !m_gadgets || event->button() != Qt::LeftButton) {
            QWidget::mousePressEvent(event);
            return;
        }

        const QPoint logical = toLogical(event->position());

        // The menu bar belongs to the display, not to the window/gadgets.
        // In the designer, a click previews its entries and selecting one
        // navigates to the generated user callback (it does not execute C).
        if (m_menus && !m_menus->isEmpty()
            && logical.y() >= 0 && logical.y() < 21
            && logical.x() >= 0 && logical.x() < 480) {
            int menuX = 3; // firmware layout_titles() starts at x=3
            for (int menuIndex = 0; menuIndex < m_menus->size(); ++menuIndex) {
                const GuiDesignerMenuTitle &title = m_menus->at(menuIndex);
                const int titleWidth = qMax(28, coderGirlTextWidth(title.title) + 16);
                if (logical.x() >= menuX && logical.x() < menuX + titleWidth) {
                    if (!title.items.isEmpty()) {
                        // Designer-only popup. Clicking an item still opens
                        // its generated USER callback; it does not execute it.
                        auto *popup = new GuiDesignerMenuPreviewPopup(title,
                                                                     m_zoomPercent, this);
                        popup->itemActivated = [this, menuIndex](int itemIndex) {
                            if (menuItemActivated)
                                menuItemActivated(menuIndex, itemIndex);
                        };
                        // Keep the dropdown inside the 480px firmware display.
                        const int x = qMax(0, qMin(menuX, 480 - popup->logicalWidth()));
                        popup->move(mapToGlobal(QPoint(x * m_zoomPercent / 100,
                                                       20 * m_zoomPercent / 100)));
                        popup->show();
                        popup->setFocus(Qt::PopupFocusReason);
                    }
                    event->accept();
                    return;
                }
                menuX += titleWidth + 2;
            }
        }

        const QPoint origin = clientOrigin();
        const QRect client =
            clientViewportRect();

        // SHIFT + drag in the CLIENT area is always a new marquee, even if
        // the starting point happens to be on top of an existing gadget.
        // A simple selection gesture never marks the .sbui as modified.
        if ((event->modifiers() & Qt::ShiftModifier)
            && !(event->modifiers() & (Qt::ControlModifier
                                      | Qt::AltModifier | Qt::MetaModifier))
            && client.contains(logical)) {
            m_dragging = false;
            m_resizing = false;
            m_windowDragging = false;
            m_windowResizing = false;
            m_groupDragging = false;
            m_multiSelected.clear();
            m_marqueeSelecting = true;
            m_marqueeStart = logical;
            m_marqueeRect = QRect(logical, logical);
            m_selected = -1;
            update();
            event->accept();
            return;
        }

        // Dragging any member of an existing multi-selection moves the
        // complete set. Treat it as one undoable geometry operation.
        if (m_multiSelected.size() > 1 && client.contains(logical)) {
            int groupHit = -1;
            for (int i = m_multiSelected.size() - 1; i >= 0; --i) {
                const int index = m_multiSelected.at(i);
                if (index >= 0 && index < m_gadgets->size()
                    && visibleOnTab(m_gadgets->at(index))
                    && canGroupMove(m_gadgets->at(index))
                    && gadgetPreviewRect(m_gadgets->at(index)).contains(logical)) {
                    groupHit = index;
                    break;
                }
            }
            if (groupHit >= 0) {
                m_groupStartRects.clear();
                for (int index : std::as_const(m_multiSelected)) {
                    if (index >= 0 && index < m_gadgets->size())
                        m_groupStartRects.insert(index, m_gadgets->at(index).rect);
                }
                m_groupDragAnchor = groupHit;
                m_selected = groupHit;
                m_pressLogical = logical;
                m_groupDragging = true;
                if (selectionChanged)
                    selectionChanged(groupHit);
                if (geometryChangeStarted)
                    geometryChangeStarted();
                event->accept();
                return;
            }
        }

        /*
         * Resize anchors always win before body hit-testing.
         *
         * Window selected:
         *     test the Window's 8 anchors.
         *
         * Gadget selected:
         *     test that gadget's 8 anchors before checking overlapping gadgets.
         */
        if (m_selected < 0) {
            const Qt::Edges edges =
                windowResizeEdgesAt(
                    logical,
                    m_window->rect);

            if (edges != Qt::Edges()) {
                m_dragging = false;
                m_resizing = false;
                m_windowResizing = true;
                m_windowResizeEdges = edges;
                m_gadgetResizeEdges = {};
                m_pressLogical = logical;
                m_startRect = m_window->rect;

                if (geometryChangeStarted) {
                    geometryChangeStarted();
                }

                event->accept();
                return;
            }
        } else if (m_selected < m_gadgets->size()
                   && m_gadgets->at(m_selected).type != QStringLiteral("GridSelect")
                   && !isDockedScrollbar(m_gadgets->at(m_selected))
                   && !isVirtualDesignerGadget(m_gadgets->at(m_selected).type)) {
            const QRect selectedRect =
                m_gadgets->at(m_selected)
                    .rect
                    .translated(origin);

            const Qt::Edges edges =
                windowResizeEdgesAt(
                    logical,
                    selectedRect);

            if (edges != Qt::Edges()) {
                m_dragging = false;
                m_resizing = true;
                m_windowResizing = false;
                m_windowResizeEdges = {};
                m_gadgetResizeEdges = edges;
                m_pressLogical = logical;
                m_startRect =
                    m_gadgets->at(m_selected)
                        .rect;

                if (geometryChangeStarted) {
                    geometryChangeStarted();
                }

                event->accept();
                return;
            }
        }

        /*
         * Match the real CoderGirl behaviour: MOVEABLE windows drag from the
         * title strip. This works even when a gadget was previously selected.
         */
        if (windowMoveable()
            && windowTitleDragRect().contains(logical)) {
            setSelectedIndex(-1);
            m_dragging = false;
            m_resizing = false;
            m_windowResizing = false;
            m_windowDragging = true;
            m_windowResizeEdges = {};
            m_gadgetResizeEdges = {};
            m_pressLogical = logical;
            m_startRect = m_window->rect;

            if (geometryChangeStarted) {
                geometryChangeStarted();
            }

            event->accept();
            return;
        }

        // Click a virtual TabGroup header to preview its other page.
        if (client.contains(logical)) {
            for (int i = m_gadgets->size()-1; i >= 0; --i) {
                GuiDesignerGadget &g = (*m_gadgets)[i];
                if (g.type != QStringLiteral("TabGroup")) continue;
                const QRect r = g.rect.translated(origin);
                if (!QRect(r.x(), r.y(), r.width(), 24).contains(logical)) continue;
                const QStringList titles = designerTabTitles(g);
                const int next = qBound(0, (logical.x()-r.x()) / qMax(1, r.width()/titles.size()), titles.size()-1);
                g.value = next; // preview state only: not a source modification
                setSelectedIndex(i);
                update();
                event->accept();
                return;
            }
        }
        int hit = -1;

        if (windowInnerRect().contains(logical)) {
            for (int pass = 0; pass < 3 && hit < 0; ++pass) {
            for (int i = m_gadgets->size() - 1;
                 i >= 0;
                 --i) {
                if (!visibleOnTab(m_gadgets->at(i))) continue;
                const QString &type = m_gadgets->at(i).type;
                if (pass == 0 && !isVirtualDesignerGadget(type)) continue;
                if (pass == 1 && (isVirtualDesignerGadget(type) || type == QStringLiteral("TabGroup"))) continue;
                if (pass == 2 && type != QStringLiteral("TabGroup")) continue;
                const GuiDesignerGadget &g = m_gadgets->at(i);
                const QRect gr = gadgetPreviewRect(g);
                if (gr.adjusted(-2, -2, 2, 2)
                        .intersected(isDockedScrollbar(g) ? windowInnerRect() : client)
                        .contains(logical)) {
                    hit = i;
                    break;
                }
            }
            }
        }

        setSelectedIndex(hit);
        m_dragging = false;
        m_resizing = false;
        m_windowResizing = false;
        m_windowDragging = false;
        m_windowResizeEdges = {};

        if (hit >= 0) {
            const GuiDesignerGadget &g = m_gadgets->at(hit);
            const QRect gr = gadgetPreviewRect(g);

            m_gadgetResizeEdges =
                (isVirtualDesignerGadget(g.type) || isDockedScrollbar(g))
                    ? Qt::Edges() : windowResizeEdgesAt(logical, gr);

            m_resizing =
                m_gadgetResizeEdges
                != Qt::Edges();

            // Firmware controls the position of docked scrollbars.
            m_dragging = !m_resizing && !isDockedScrollbar(g);

            m_pressLogical = logical;

            m_startRect =
                m_gadgets->at(hit)
                    .rect;

            if (geometryChangeStarted) {
                geometryChangeStarted();
            }
        } else {
            m_gadgetResizeEdges = {};
        }

        event->accept();
    }

    void mouseMoveEvent(QMouseEvent *event) override
    {
        const QPoint logical =
            toLogical(event->position());

        if (m_marqueeSelecting) {
            const QPoint bounded(
                qBound(clientViewportRect().left(), logical.x(), clientViewportRect().right()),
                qBound(clientViewportRect().top(), logical.y(), clientViewportRect().bottom()));
            m_marqueeRect = QRect(m_marqueeStart, bounded).normalized();
            update();
            event->accept();
            return;
        }

        if (m_groupDragging && m_gadgets && m_groupStartRects.size() > 1) {
            const QRect client = clientViewportRect();
            const QRect anchor = m_groupStartRects.value(m_groupDragAnchor);
            const QPoint mouseDelta = logical - m_pressLogical;
            QPoint delta(snapValue(anchor.x() + mouseDelta.x()) - anchor.x(),
                         snapValue(anchor.y() + mouseDelta.y()) - anchor.y());

            // Clamp the *shared* translation, not every item independently.
            // That preserves all relative positions and ensures none leave
            // the firmware's actual client rectangle.
            int minDx = -200000, minDy = -200000;
            int maxDx = 200000, maxDy = 200000;
            for (auto it = m_groupStartRects.cbegin(); it != m_groupStartRects.cend(); ++it) {
                const QRect r = it.value();
                minDx = qMax(minDx, -r.left());
                minDy = qMax(minDy, -r.top());
                maxDx = qMin(maxDx, client.width() - r.right() - 1);
                maxDy = qMin(maxDy, client.height() - r.bottom() - 1);
            }
            delta.setX(minDx <= maxDx ? qBound(minDx, delta.x(), maxDx) : 0);
            delta.setY(minDy <= maxDy ? qBound(minDy, delta.y(), maxDy) : 0);

            for (auto it = m_groupStartRects.cbegin(); it != m_groupStartRects.cend(); ++it) {
                if (it.key() >= 0 && it.key() < m_gadgets->size())
                    (*m_gadgets)[it.key()].rect = it.value().translated(delta);
            }
            update();
            event->accept();
            return;
        }

        if (m_windowDragging
            && m_window) {
            const QPoint delta =
                logical - m_pressLogical;

            QRect r =
                m_startRect;

            r.moveTo(
                snapValue(
                    m_startRect.x()
                        + delta.x()),
                snapValue(
                    m_startRect.y()
                        + delta.y()));

            if (windowScreenBound()) {
                const int maxX =
                    qMax(
                        0,
                        480 - r.width());

                const int maxY =
                    qMax(
                        0,
                        320 - r.height());

                r.moveLeft(
                    qBound(
                        0,
                        r.x(),
                        maxX));

                r.moveTop(
                    qBound(
                        0,
                        r.y(),
                        maxY));
            }

            m_window->rect = r;
            update();
            event->accept();
            return;
        }

        if (m_windowResizing
            && m_window) {
            const QPoint delta =
                logical - m_pressLogical;

            QRect r =
                m_startRect;

            constexpr int MinimumWidth = 40;
            constexpr int MinimumHeight = 24;

            if (m_windowResizeEdges
                & Qt::LeftEdge) {
                const int newX =
                    qBound(
                        windowScreenBound() ? 0 : -2000,
                        snapValue(
                            m_startRect.x()
                                + delta.x()),
                        m_startRect.right()
                            - MinimumWidth
                            + 1);

                r.setLeft(newX);
            }

            if (m_windowResizeEdges
                & Qt::RightEdge) {
                const int newRight =
                    qBound(
                        m_startRect.left()
                            + MinimumWidth
                            - 1,
                        snapValue(
                            m_startRect.right()
                                + delta.x()),
                        windowScreenBound() ? 479 : 2000);

                r.setRight(newRight);
            }

            if (m_windowResizeEdges
                & Qt::TopEdge) {
                const int newY =
                    qBound(
                        windowScreenBound() ? 0 : -2000,
                        snapValue(
                            m_startRect.y()
                                + delta.y()),
                        m_startRect.bottom()
                            - MinimumHeight
                            + 1);

                r.setTop(newY);
            }

            if (m_windowResizeEdges
                & Qt::BottomEdge) {
                const int newBottom =
                    qBound(
                        m_startRect.top()
                            + MinimumHeight
                            - 1,
                        snapValue(
                            m_startRect.bottom()
                                + delta.y()),
                        windowScreenBound() ? 319 : 2000);

                r.setBottom(newBottom);
            }

            m_window->rect = r;
            update();
            event->accept();
            return;
        }

        if ((m_dragging || m_resizing)
            && m_selected >= 0
            && m_gadgets
            && m_selected < m_gadgets->size()) {

            const QPoint delta =
                logical - m_pressLogical;

            GuiDesignerGadget &g =
                (*m_gadgets)[m_selected];

            if (m_dragging) {
                QRect r =
                    m_startRect.translated(
                        delta);

                /*
                 * Gadget geometry is relative to the CoderGirl client viewport.
                 * Keep the full gadget inside that logical client area.
                 */
                const QRect client =
                    clientViewportRect();

                const int maxX =
                    qMax(
                        0,
                        client.width()
                            - r.width());

                const int maxY =
                    qMax(
                        0,
                        client.height()
                            - r.height());

                r.moveLeft(
                    qBound(
                        0,
                        snapValue(
                            r.left()),
                        maxX));

                r.moveTop(
                    qBound(
                        0,
                        snapValue(
                            r.top()),
                        maxY));

                if (g.type == QStringLiteral("TabGroup"))
                    moveTabGroupWithMembers(m_selected, r.topLeft());
                else
                    g.rect = r;
            } else {
                QRect r =
                    m_startRect;

                constexpr int MinimumGadgetSize = 8;

                const QRect client =
                    clientViewportRect();

                const int maxRight =
                    qMax(
                        MinimumGadgetSize - 1,
                        client.width() - 1);

                const int maxBottom =
                    qMax(
                        MinimumGadgetSize - 1,
                        client.height() - 1);

                if (m_gadgetResizeEdges
                    & Qt::LeftEdge) {
                    const int newLeft =
                        qBound(
                            0,
                            snapValue(
                                m_startRect.left()
                                    + delta.x()),
                            m_startRect.right()
                                - MinimumGadgetSize
                                + 1);

                    r.setLeft(
                        newLeft);
                }

                if (m_gadgetResizeEdges
                    & Qt::RightEdge) {
                    const int newRight =
                        qBound(
                            m_startRect.left()
                                + MinimumGadgetSize
                                - 1,
                            snapValue(
                                m_startRect.right()
                                    + delta.x()),
                            maxRight);

                    r.setRight(
                        newRight);
                }

                if (m_gadgetResizeEdges
                    & Qt::TopEdge) {
                    const int newTop =
                        qBound(
                            0,
                            snapValue(
                                m_startRect.top()
                                    + delta.y()),
                            m_startRect.bottom()
                                - MinimumGadgetSize
                                + 1);

                    r.setTop(
                        newTop);
                }

                if (m_gadgetResizeEdges
                    & Qt::BottomEdge) {
                    const int newBottom =
                        qBound(
                            m_startRect.top()
                                + MinimumGadgetSize
                                - 1,
                            snapValue(
                                m_startRect.bottom()
                                    + delta.y()),
                            maxBottom);

                    r.setBottom(
                        newBottom);
                }

                g.rect = r;
            }

            update();
            event->accept();
            return;
        }

        /*
         * Hover feedback for the selected Window OR selected Gadget anchors.
         */
        Qt::Edges hoverEdges;

        if (m_selected < 0
            && m_window) {
            hoverEdges =
                windowResizeEdgesAt(
                    logical,
                    m_window->rect);
        } else if (m_selected >= 0
                   && m_gadgets
                   && m_selected < m_gadgets->size()
                   && m_gadgets->at(m_selected).type != QStringLiteral("GridSelect")
                   && !isDockedScrollbar(m_gadgets->at(m_selected))
                   && !isVirtualDesignerGadget(m_gadgets->at(m_selected).type)) {
            const QRect selectedRect =
                m_gadgets->at(m_selected)
                    .rect
                    .translated(
                        clientOrigin());

            hoverEdges =
                windowResizeEdgesAt(
                    logical,
                    selectedRect);
        }

        if ((hoverEdges & Qt::LeftEdge)
            && (hoverEdges & Qt::TopEdge)
            || (hoverEdges & Qt::RightEdge)
               && (hoverEdges & Qt::BottomEdge)) {
            setCursor(
                Qt::SizeFDiagCursor);
        } else if ((hoverEdges & Qt::RightEdge)
                   && (hoverEdges & Qt::TopEdge)
                   || (hoverEdges & Qt::LeftEdge)
                      && (hoverEdges & Qt::BottomEdge)) {
            setCursor(
                Qt::SizeBDiagCursor);
        } else if (hoverEdges
                   & (Qt::LeftEdge
                      | Qt::RightEdge)) {
            setCursor(
                Qt::SizeHorCursor);
        } else if (hoverEdges
                   & (Qt::TopEdge
                      | Qt::BottomEdge)) {
            setCursor(
                Qt::SizeVerCursor);
        } else if (windowMoveable()
                   && windowTitleDragRect().contains(logical)) {
            setCursor(
                Qt::SizeAllCursor);
        } else {
            unsetCursor();
        }

        QWidget::mouseMoveEvent(event);
    }

    void contextMenuEvent(QContextMenuEvent *event) override
    {
        if (!m_gadgets || !m_window || !event) {
            QWidget::contextMenuEvent(event);
            return;
        }
        const QPoint logical = toLogical(event->pos());
        const QRect client = clientViewportRect();
        if (!windowInnerRect().contains(logical)) return;
        const QPoint origin = clientOrigin();
        int hit = -1;
        // Preserve an already selected gadget (particularly a TabGroup)
        // when the pointer is inside its bounds, even if children overlap.
        if (m_selected >= 0 && m_selected < m_gadgets->size()
            && visibleOnTab(m_gadgets->at(m_selected))
            && gadgetPreviewRect(m_gadgets->at(m_selected)).contains(logical))
            hit = m_selected;
        if (hit < 0) {
            for (int pass = 0; pass < 2 && hit < 0; ++pass) {
                for (int i = m_gadgets->size() - 1; i >= 0; --i) {
                    const GuiDesignerGadget &g = m_gadgets->at(i);
                    if (!visibleOnTab(g) ||
                        (g.type == QStringLiteral("TabGroup")) != (pass == 1))
                        continue;
                    if (gadgetPreviewRect(g).contains(logical)
                        && (isDockedScrollbar(g) || client.contains(logical))) {
                        hit = i;
                        break;
                    }
                }
            }
        }
        if (hit < 0) return;
        if (hit != m_selected) setSelectedIndex(hit);

        QMenu menu(this);
        QAction *front = menu.addAction(QObject::tr("Bring Gadget to Front"));
        QAction *back = menu.addAction(QObject::tr("Send Gadget to Back"));
        QAction *chosen = menu.exec(event->globalPos());
        if (chosen == front && layerRequested) layerRequested(true);
        else if (chosen == back && layerRequested) layerRequested(false);
        event->accept();
    }

    void mouseReleaseEvent(QMouseEvent *event) override
    {
        if (event && event->button() == Qt::LeftButton && m_marqueeSelecting) {
            m_marqueeSelecting = false;
            m_multiSelected.clear();
            const QRect client = clientViewportRect();
            const QRect selectionRect = m_marqueeRect.intersected(client);
            if (!selectionRect.isEmpty() && m_gadgets) {
                for (int i = 0; i < m_gadgets->size(); ++i) {
                    const GuiDesignerGadget &g = m_gadgets->at(i);
                    if (!visibleOnTab(g) || !canGroupMove(g))
                        continue;
                    const QRect visibleGadget = gadgetPreviewRect(g).intersected(client);
                    if (visibleGadget.intersects(selectionRect))
                        m_multiSelected.append(i);
                }
            }
            m_selected = m_multiSelected.isEmpty() ? -1 : m_multiSelected.first();
            m_marqueeRect = {};
            if (selectionChanged)
                selectionChanged(m_selected);
            update();
            event->accept();
            return;
        }

        if (event && event->button() == Qt::LeftButton && m_groupDragging) {
            bool changed = false;
            if (m_gadgets) {
                for (auto it = m_groupStartRects.cbegin(); it != m_groupStartRects.cend(); ++it) {
                    if (it.key() >= 0 && it.key() < m_gadgets->size()
                        && m_gadgets->at(it.key()).rect != it.value()) {
                        changed = true;
                        break;
                    }
                }
            }
            m_groupDragging = false;
            m_groupStartRects.clear();
            m_groupDragAnchor = -1;
            if (changed && geometryCommitted)
                geometryCommitted();
            event->accept();
            return;
        }

        if ((m_dragging
             || m_resizing
             || m_windowResizing
             || m_windowDragging)
            && event->button()
               == Qt::LeftButton) {
            // A click selects a gadget but must not modify the design.
            // Only commit if the drag/resize actually changed geometry.
            const bool windowGesture = m_windowResizing || m_windowDragging;
            const bool geometryChanged = windowGesture
                ? (m_window && m_window->rect != m_startRect)
                : (m_gadgets && m_selected >= 0
                   && m_selected < m_gadgets->size()
                   && m_gadgets->at(m_selected).rect != m_startRect);

            m_dragging = false;
            m_resizing = false;
            m_windowResizing = false;
            m_windowDragging = false;
            m_windowResizeEdges = {};
            m_gadgetResizeEdges = {};

            if (geometryChanged && geometryCommitted) {
                geometryCommitted();
            }

            event->accept();
            return;
        }

        QWidget::mouseReleaseEvent(event);
    }

private:
    static QList<QRect> windowResizeHandles(
        const QRect &r)
    {
        constexpr int HandleSize = 7;
        constexpr int Half = HandleSize / 2;

        const QPoint topLeft =
            r.topLeft();

        const QPoint topCentre(
            r.center().x(),
            r.top());

        const QPoint topRight =
            r.topRight();

        const QPoint rightCentre(
            r.right(),
            r.center().y());

        const QPoint bottomRight =
            r.bottomRight();

        const QPoint bottomCentre(
            r.center().x(),
            r.bottom());

        const QPoint bottomLeft =
            r.bottomLeft();

        const QPoint leftCentre(
            r.left(),
            r.center().y());

        const QList<QPoint> points = {
            topLeft,
            topCentre,
            topRight,
            rightCentre,
            bottomRight,
            bottomCentre,
            bottomLeft,
            leftCentre
        };

        QList<QRect> result;
        result.reserve(
            points.size());

        for (const QPoint &point :
             points) {
            result.append(
                QRect(
                    point.x() - Half,
                    point.y() - Half,
                    HandleSize,
                    HandleSize));
        }

        return result;
    }

    static Qt::Edges windowResizeEdgesAt(
        const QPoint &point,
        const QRect &r)
    {
        const QList<QRect> handles =
            windowResizeHandles(r);

        if (handles.size() != 8) {
            return {};
        }

        if (handles.at(0).contains(point)) {
            return Qt::TopEdge
                | Qt::LeftEdge;
        }

        if (handles.at(1).contains(point)) {
            return Qt::TopEdge;
        }

        if (handles.at(2).contains(point)) {
            return Qt::TopEdge
                | Qt::RightEdge;
        }

        if (handles.at(3).contains(point)) {
            return Qt::RightEdge;
        }

        if (handles.at(4).contains(point)) {
            return Qt::BottomEdge
                | Qt::RightEdge;
        }

        if (handles.at(5).contains(point)) {
            return Qt::BottomEdge;
        }

        if (handles.at(6).contains(point)) {
            return Qt::BottomEdge
                | Qt::LeftEdge;
        }

        if (handles.at(7).contains(point)) {
            return Qt::LeftEdge;
        }

        return {};
    }

    bool visibleOnTab(const GuiDesignerGadget &g) const
    {
        if (g.tabOwner.isEmpty() || !m_gadgets) return true;
        for (const GuiDesignerGadget &tabs : std::as_const(*m_gadgets)) {
            if (tabs.type == QStringLiteral("TabGroup") && tabs.name == g.tabOwner)
                return g.tabPage == qBound(0, tabs.value, designerTabTitles(tabs).size()-1);
        }
        return true; // Missing owner: keep content editable, validation rejects generation.
    }

    QPoint toLogical(const QPointF &pos) const
    {
        const int deviceX =
            qRound(
                pos.x());

        const int deviceY =
            qRound(
                pos.y());

        return QPoint(
            (deviceX * 100
             + m_zoomPercent / 2)
                / m_zoomPercent,
            (deviceY * 100
             + m_zoomPercent / 2)
                / m_zoomPercent);
    }

    bool dockRightEnabled() const
    {
        if (!m_window) {
            return false;
        }

        if (designerWindowFlag(
                m_window->flags,
                QStringLiteral(
                    "SBX_WF_DOCKRIGHT"))) {
            return true;
        }

        if (m_gadgets) {
            for (const GuiDesignerGadget &g :
                 std::as_const(*m_gadgets)) {
                if (g.flags.contains(
                        QStringLiteral(
                            "GAD_TOOL_DOCKED_RIGHT"))) {
                    return true;
                }
            }
        }

        return false;
    }

    bool dockBottomEnabled() const
    {
        if (!m_window) {
            return false;
        }

        if (designerWindowFlag(
                m_window->flags,
                QStringLiteral(
                    "SBX_WF_DOCKBOTTOM"))) {
            return true;
        }

        if (m_gadgets) {
            for (const GuiDesignerGadget &g :
                 std::as_const(*m_gadgets)) {
                if (g.flags.contains(
                        QStringLiteral(
                            "GAD_TOOL_DOCKED_BOTTOM"))) {
                    return true;
                }
            }
        }

        return false;
    }

    QRect windowInnerRect() const
    {
        if (!m_window) {
            return {};
        }

        const QRect wr =
            m_window->rect;

        const bool noBorder =
            designerWindowFlag(
                m_window->flags,
                QStringLiteral(
                    "SBX_WF_NOBORDER"));

        const bool hasTitle =
            designerWindowFlag(
                m_window->flags,
                QStringLiteral(
                    "SBX_WF_TITLE_BAR"));

        constexpr int WinBorder = 4;
        constexpr int WinTitleHeight = 16;
        constexpr int TitleChromeHeight =
            WinTitleHeight + WinBorder;

        if (noBorder) {
            return QRect(
                wr.x(),
                wr.y()
                    + (hasTitle
                           ? TitleChromeHeight
                           : 0),
                wr.width(),
                qMax(
                    0,
                    wr.height()
                        - (hasTitle
                               ? TitleChromeHeight
                               : 0)));
        }

        return QRect(
            wr.x() + WinBorder,
            wr.y()
                + WinBorder
                + (hasTitle
                       ? WinTitleHeight
                       : 0),
            qMax(
                0,
                wr.width()
                    - WinBorder * 2),
            qMax(
                0,
                wr.height()
                    - WinBorder * 2
                    - (hasTitle
                           ? WinTitleHeight
                           : 0)));
    }

    QRect clientViewportRect() const
    {
        if (!m_window) {
            return {};
        }

        QRect client =
            windowInnerRect();

        const bool noBorder =
            designerWindowFlag(
                m_window->flags,
                QStringLiteral(
                    "SBX_WF_NOBORDER"));

        const bool resizable =
            designerWindowFlag(
                m_window->flags,
                QStringLiteral(
                    "SBX_WF_RESIZABLE"));

        constexpr int WinBorder = 4;
        constexpr int ResizeGlyphSize = 20;
        constexpr int ScrollThickness = 16;

        /*
         * Match CoderGirl layoutWindow():
         *
         * - resize gutter inside INNER is 20 - 4 = 16 pixels
         * - a bottom dock owns that edge, so it replaces the resize reserve
         * - right/bottom dock bands each reserve SB_SCROLL_THICK (16 px)
         */
        if (resizable
            && !noBorder
            && !dockBottomEnabled()) {
            client.setHeight(
                qMax(
                    0,
                    client.height()
                        - (ResizeGlyphSize
                           - WinBorder)));
        }

        if (dockRightEnabled()) {
            client.setWidth(
                qMax(
                    0,
                    client.width()
                        - ScrollThickness));
        }

        if (dockBottomEnabled()) {
            client.setHeight(
                qMax(
                    0,
                    client.height()
                        - ScrollThickness));
        }

        return client;
    }

    // Firmware draw_scrollbar() anchors docked bars in WINDOW INNER,
    // NOT in the ordinary client viewport.  The saved gadget rectangle
    // remains untouched: only its canvas preview/hit-test position changes.
    QRect gadgetPreviewRect(const GuiDesignerGadget &g) const
    {
        const QPoint origin = clientOrigin();
        if (g.type != QStringLiteral("Scrollbar") || !m_window)
            return g.rect.translated(origin);

        const QRect inner = windowInnerRect();
        const bool resizeReserve = designerWindowFlag(
            m_window->flags, QStringLiteral("SBX_WF_RESIZABLE"))
            && !designerWindowFlag(m_window->flags, QStringLiteral("SBX_WF_NOBORDER"));
        // These are firmware win_inner_reserve_right/bottom() rules.
        const int reserveRight = resizeReserve ? 16 : 0;
        const int reserveBottom = resizeReserve ? 19 : 0;
        if (g.orientation == 0 && g.flags.contains(QStringLiteral("GAD_TOOL_DOCKED_RIGHT")))
            return QRect(inner.x() + inner.width() - 16 + 2, inner.y() + 1,
                         16, qMax(0, inner.height() - reserveBottom));
        if (g.orientation == 1 && g.flags.contains(QStringLiteral("GAD_TOOL_DOCKED_BOTTOM")))
            return QRect(inner.x() - 2, inner.y() + inner.height() - 16 + 2,
                         qMax(0, inner.width() - reserveRight), 16);
        return g.rect.translated(origin);
    }

    bool isDockedScrollbar(const GuiDesignerGadget &g) const
    {
        return g.type == QStringLiteral("Scrollbar")
            && ((g.orientation == 0 && g.flags.contains(QStringLiteral("GAD_TOOL_DOCKED_RIGHT")))
                || (g.orientation == 1 && g.flags.contains(QStringLiteral("GAD_TOOL_DOCKED_BOTTOM"))));
    }

    bool canGroupMove(const GuiDesignerGadget &g) const
    {
        // Window-chrome dock objects, virtual controls and TabGroup have
        // special firmware positioning or parent-child movement rules.
        // Their existing individual editing behaviour is unchanged.
        return !isVirtualDesignerGadget(g.type)
            && !isDockedScrollbar(g)
            && g.type != QStringLiteral("TabGroup")
            && g.type != QStringLiteral("GridSelect");
    }

    int snapValue(int value) const
    {
        if (m_gridSnap <= 1) {
            return value;
        }

        if (value >= 0) {
            return ((value + m_gridSnap / 2)
                    / m_gridSnap)
                * m_gridSnap;
        }

        return -(((-value + m_gridSnap / 2)
                  / m_gridSnap)
                 * m_gridSnap);
    }

    static void drawDockChecker(
        QPainter &p,
        const QRect &rect)
    {
        if (rect.width() <= 0
            || rect.height() <= 0) {
            return;
        }

        constexpr int Cell = 4;

        QColor a =
            coderGirlPen(3);

        QColor b =
            coderGirlPen(2);

        a.setAlpha(115);
        b.setAlpha(75);

        p.save();
        p.setClipRect(rect);
        p.setPen(Qt::NoPen);

        for (int y = rect.top();
             y <= rect.bottom();
             y += Cell) {
            for (int x = rect.left();
                 x <= rect.right();
                 x += Cell) {
                const bool alternate =
                    (((x - rect.left()) / Cell)
                     + ((y - rect.top()) / Cell))
                    & 1;

                p.fillRect(
                    QRect(
                        x,
                        y,
                        Cell,
                        Cell),
                    alternate
                        ? a
                        : b);
            }
        }

        p.restore();
    }

    QRect windowTitleDragRect() const
    {
        if (!m_window) {
            return {};
        }

        if (!designerWindowFlag(
                m_window->flags,
                QStringLiteral(
                    "SBX_WF_TITLE_BAR"))) {
            return {};
        }

        const bool noBorder =
            designerWindowFlag(
                m_window->flags,
                QStringLiteral(
                    "SBX_WF_NOBORDER"));

        const QRect wr =
            m_window->rect;

        return QRect(
            wr.x()
                + (noBorder ? 0 : 4),
            wr.y()
                + (noBorder ? 0 : 4),
            qMax(
                0,
                wr.width()
                    - (noBorder ? 0 : 8)),
            16);
    }

    bool windowScreenBound() const
    {
        return m_window
            && designerWindowFlag(
                m_window->flags,
                QStringLiteral(
                    "SBX_WF_SCREENBOUND"));
    }

    bool windowMoveable() const
    {
        return m_window
            && designerWindowFlag(
                m_window->flags,
                QStringLiteral(
                    "SBX_WF_MOVEABLE"));
    }

    void clampWindowToScreen()
    {
        if (!m_window
            || !windowScreenBound()) {
            return;
        }

        QRect r =
            m_window->rect;

        const int maxX =
            qMax(
                0,
                480 - r.width());

        const int maxY =
            qMax(
                0,
                320 - r.height());

        r.moveLeft(
            qBound(
                0,
                r.x(),
                maxX));

        r.moveTop(
            qBound(
                0,
                r.y(),
                maxY));

        m_window->rect = r;
    }

    QPoint clientOrigin() const
    {
        if (!m_window) {
            return {};
        }

        const bool hasTitle =
            designerWindowFlag(
                m_window->flags,
                QStringLiteral(
                    "SBX_WF_TITLE_BAR"));

        const bool noBorder =
            designerWindowFlag(
                m_window->flags,
                QStringLiteral(
                    "SBX_WF_NOBORDER"));

        if (noBorder) {
            return QPoint(
                m_window->rect.x(),
                m_window->rect.y()
                    + (hasTitle
                           ? 20
                           : 0));
        }

        return QPoint(
            m_window->rect.x() + 4,
            m_window->rect.y()
                + 4
                + (hasTitle
                       ? 16
                       : 0));
    }

    static QColor defaultBPenForType(
        const QString &type,
        int windowBackPen)
    {
        if (type == QStringLiteral("Button")) {
            return coderGirlPen(5);
        }

        if (type == QStringLiteral("Checkbox")
            || type == QStringLiteral("Radio")) {
            return coderGirlPen(4);
        }

        if (type == QStringLiteral("Scrollbar")) {
            return coderGirlPen(4);
        }

        // The intended CNV_BEVEL default background pen is pen 2.
        // TabGroup is backed by a CNV_BEVEL Canvas in generated C code.
        if (type == QStringLiteral("Canvas")
            || type == QStringLiteral("TabGroup")) {
            return coderGirlPen(2);
        }

        return coderGirlPen(
            windowBackPen);
    }

    static int defaultFPenForType(
        const QString &type)
    {
        if (type == QStringLiteral("TextBox")
            || type == QStringLiteral("TextArea")) {
            return 16; // PEN_WIN_TITLE is black in DEFAULT_THEME
        }

        return 16; // PEN_TEXT
    }

    static void drawGadget(
        QPainter &p,
        const GuiDesignerGadget &g,
        const QRect &r,
        int windowBackPen)
    {
        const QColor face =
            g.bPen >= 0
                ? coderGirlPen(
                      g.bPen)
                : defaultBPenForType(
                      g.type,
                      windowBackPen);

        const QColor text =
            coderGirlPen(
                g.fPen >= 0
                    ? g.fPen
                    : defaultFPenForType(
                          g.type));

        const QColor highlight =
            coderGirlPen(
                g.hPen >= 0
                    ? g.hPen
                    : 3);

        if (g.type == QStringLiteral("FileRequester") || g.type == QStringLiteral("MessageBox")) {
            // Virtual requester glyphs: not part of the generated SIDBOX window.
            p.save();
            p.setRenderHint(QPainter::Antialiasing, false);
            p.fillRect(r, QColor(16, 24, 38));
            p.setPen(QPen(QColor(90, 164, 238), 1));
            p.drawRect(r.adjusted(0, 0, -1, -1));
            p.setPen(QPen(QColor(225, 232, 244), 1));
            if (g.type == QStringLiteral("FileRequester")) {
                p.drawRect(QRect(r.x()+4, r.y()+9, 16, 10));
                p.drawRect(QRect(r.x()+5, r.y()+6, 7, 4));
            } else {
                p.drawRect(QRect(r.x()+5, r.y()+5, 14, 12));
                p.drawLine(r.x()+9, r.y()+20, r.x()+13, r.y()+17);
                p.drawLine(r.x()+12, r.y()+8, r.x()+12, r.y()+12);
                p.drawPoint(r.x()+12, r.y()+14);
            }
            p.restore();
            return;
        }
        if (g.type == QStringLiteral("Media")) {
            // A designer-only media component; no SIDBOX gadget is created.
            // Keep the speaker and wave glyph comfortably inside the 24x24 box.
            p.save();
            p.setRenderHint(QPainter::Antialiasing, false);
            p.fillRect(r, QColor(16, 24, 38));
            p.setPen(QPen(QColor(90, 164, 238), 1));
            p.drawRect(r.adjusted(0, 0, -1, -1));
            p.setBrush(QColor(225, 232, 244));
            p.setPen(Qt::NoPen);
            const int x = r.x() + 4;
            const int y = r.y() + 4;
            QPolygon speaker;
            speaker << QPoint(x,     y + 6)
                    << QPoint(x + 4, y + 6)
                    << QPoint(x + 8, y + 2)
                    << QPoint(x + 8, y + 14)
                    << QPoint(x + 4, y + 10)
                    << QPoint(x,     y + 10);
            p.drawPolygon(speaker);
            p.setBrush(Qt::NoBrush);
            p.setPen(QPen(QColor(90, 164, 238), 1));
            p.drawArc(QRect(x + 6, y + 4, 9, 9), -60 * 16, 120 * 16);
            p.drawArc(QRect(x + 4, y + 1, 13, 13), -60 * 16, 120 * 16);
            p.restore();
            return;
        }

        if (g.type == QStringLiteral("KBInput") || g.type == QStringLiteral("MSInput")) {
            // Virtual input event source. Draw a compact glyph at design-time;
            // palette thumbnails use the user's gadget_kbinput/msinput icons.
            p.save();
            p.setRenderHint(QPainter::Antialiasing, false);
            p.fillRect(r, QColor(16, 24, 38));
            p.setPen(QPen(QColor(90, 164, 238), 1));
            p.drawRect(r.adjusted(0, 0, -1, -1));
            p.setPen(QColor(225, 232, 244));
            p.drawText(r.adjusted(1, 1, -1, -1), Qt::AlignCenter,
                       g.type == QStringLiteral("KBInput") ? QStringLiteral("KB") : QStringLiteral("MS"));
            p.restore();
            return;
        }
        if (g.type == QStringLiteral("Messenger")) {
            // Virtual Messenger: two mail envelopes, no physical SIDBOX gadget.
            p.save();
            p.setRenderHint(QPainter::Antialiasing, false);
            p.fillRect(r, QColor(16, 24, 38));
            p.setPen(QPen(QColor(90, 164, 238), 1));
            p.drawRect(r.adjusted(0, 0, -1, -1));
            p.setPen(QPen(QColor(226, 231, 239), 1));
            const int x = r.x(), y = r.y();
            p.drawRect(QRect(x + 3, y + 5, 13, 10));
            p.drawLine(x + 3, y + 5, x + 9, y + 10);
            p.drawLine(x + 9, y + 10, x + 16, y + 5);
            p.drawRect(QRect(x + 8, y + 11, 13, 9));
            p.drawLine(x + 8, y + 11, x + 14, y + 16);
            p.drawLine(x + 14, y + 16, x + 21, y + 11);
            p.restore();
            return;
        }
        if (g.type == QStringLiteral("UART1")) {
            // Virtual USART1 controller: TX and RX leads, no on-device gadget.
            p.save();
            p.setRenderHint(QPainter::Antialiasing, false);
            p.fillRect(r, QColor(16, 24, 38));
            p.setPen(QPen(QColor(90, 164, 238), 1));
            p.drawRect(r.adjusted(0, 0, -1, -1));
            p.setPen(QPen(QColor(226, 231, 239), 1));
            p.drawRect(QRect(r.x()+4,r.y()+5,16,14));
            p.drawLine(r.x()+8,r.y()+7,r.x()+8,r.y()+17);
            p.drawLine(r.x()+12,r.y()+7,r.x()+12,r.y()+17);
            p.drawLine(r.x()+16,r.y()+7,r.x()+16,r.y()+17);
            p.drawText(QRect(r.x()+1,r.y()+2,22,20), Qt::AlignBottom | Qt::AlignHCenter,
                       QStringLiteral("IO"));
            p.restore();
            return;
        }
        if (g.type == QStringLiteral("Timer")) {
            // A non-visual design-time component: a crisp 24x24 stopwatch.
            // No corresponding object is drawn on the actual SIDBOX screen.
            p.save();
            p.setRenderHint(QPainter::Antialiasing, false);
            p.fillRect(r, QColor(16, 24, 38));
            p.setPen(QPen(QColor(90, 164, 238), 1));
            p.drawRect(r.adjusted(0, 0, -1, -1));
            const int cx = r.center().x();
            const int cy = r.center().y() + 2;
            p.setPen(QPen(QColor(226, 231, 239), 2));
            p.drawEllipse(QRect(cx - 7, cy - 7, 14, 14));
            p.drawLine(cx, cy, cx, cy - 5);
            p.drawLine(cx, cy, cx + 4, cy + 2);
            p.setPen(QPen(QColor(90, 164, 238), 2));
            p.drawLine(cx - 3, cy - 10, cx + 3, cy - 10);
            p.drawLine(cx, cy - 10, cx, cy - 8);
            p.drawLine(cx + 6, cy - 7, cx + 8, cy - 9);
            p.restore();
            return;
        }

        if (g.type == QStringLiteral("TabGroup")) {
            const QStringList tabs = designerTabTitles(g);
            const int header = 24;
            const QRect bevel = r.adjusted(0, header, 0, 0);

            // TabGroup is a virtual Canvas bevel plus manually managed toggle Buttons.
            // Its pen colours belong to the bevel, not to the tab buttons.
            p.fillRect(bevel, coderGirlPen(windowBackPen));
            const QColor bevelFPen = coderGirlPen(
                g.fPen >= 0 ? g.fPen : defaultFPenForType(QStringLiteral("Canvas")));
            const QColor bevelBPen = coderGirlPen(
                g.bPen >= 0 ? g.bPen : 2);
            const bool inset = g.flags.contains(QStringLiteral("GAD_TOOL_INSET"));
            // With default FPen=16 (dark) and BPen=2 (light), inset must
            // shade the top/left dark and bottom/right light. An outset
            // bevel uses the opposite order. Keep this aligned with the
            // firmware's CNV_BEVEL renderer once its pen order is corrected.
            const QColor topLeft = inset ? bevelFPen : bevelBPen;
            const QColor bottomRight = inset ? bevelBPen : bevelFPen;
            if (bevel.width() > 1 && bevel.height() > 1) {
                p.setPen(topLeft);
                p.drawLine(bevel.left(), bevel.top(), bevel.right(), bevel.top());
                p.drawLine(bevel.left(), bevel.top(), bevel.left(), bevel.bottom());
                p.setPen(bottomRight);
                p.drawLine(bevel.left(), bevel.bottom(), bevel.right() - 1, bevel.bottom());
                p.drawLine(bevel.right(), bevel.top(), bevel.right(), bevel.bottom());
            }

            const QColor buttonFace = defaultBPenForType(QStringLiteral("Button"), windowBackPen);
            const QColor buttonText = coderGirlPen(defaultFPenForType(QStringLiteral("Button")));
            const int tabWidth = qMax(1, r.width() / tabs.size());
            for (int i = 0; i < tabs.size(); ++i) {
                const QRect button(r.x() + i * tabWidth, r.y(),
                                   (i == tabs.size() - 1 ? r.width() - i * tabWidth : tabWidth),
                                   header);
                p.fillRect(button, buttonFace);
                drawCoderGirlBevel(p, button, i == qBound(0, g.value, tabs.size()-1));
                drawCoderGirlText(p, button.x()+4, button.y()+7,
                                  tabs.at(i).left(qMax(1, (button.width()-8)/8)), buttonText);
            }
            return;
        }

        if (g.type
            == QStringLiteral(
                "Label")) {
            // Transparent labels leave the already-rendered window / underlying
            // bitmap untouched. Only the label glyphs (and optional bevel)
            // are drawn, mirroring GAD_TOOL_TRANSPARENT in CoderGirl.
            if (!designerWindowFlag(g.flags, QStringLiteral("GAD_TOOL_TRANSPARENT"))) {
                p.fillRect(r, face);
            }

            if (g.flags.contains(QStringLiteral("GAD_TOOL_INSET"))) {
                drawCoderGirlBevel(p, r, true);
            }

            drawCoderGirlText(
                p,
                r.x(),
                r.y(),
                g.text,
                text);
            return;
        }

        if (g.type
            == QStringLiteral(
                "Checkbox")) {
            constexpr int Box = 16;

            const QRect box(
                r.x(),
                r.y()
                    + qMax(
                        0,
                        (r.height()
                             - Box)
                            / 2),
                Box,
                Box);

            p.fillRect(
                box,
                face);

            drawCoderGirlBevel(
                p,
                box,
                false);

            if (g.checked) {
                p.setPen(text);

                int cx =
                    box.x() + 4;

                const int cy =
                    box.y() + 8;

                for (int i = 0;
                     i < 2;
                     ++i) {
                    p.drawPoint(
                        cx,
                        cy);
                    p.drawPoint(
                        cx + 1,
                        cy + 1);
                    p.drawPoint(
                        cx + 2,
                        cy + 2);
                    p.drawPoint(
                        cx + 3,
                        cy + 1);
                    p.drawPoint(
                        cx + 4,
                        cy);
                    p.drawPoint(
                        cx + 5,
                        cy - 1);
                    p.drawPoint(
                        cx + 6,
                        cy - 2);

                    ++cx;
                }
            }

            drawCoderGirlText(
                p,
                box.x()
                    + Box
                    + 6,
                r.y()
                    + (r.height()
                           - 16)
                        / 2,
                g.text,
                text);

            return;
        }

        if (g.type
            == QStringLiteral(
                "Radio")) {
            constexpr int Box = 16;

            const QRect box(
                r.x(),
                r.y()
                    + qMax(
                        0,
                        (r.height()
                             - Box)
                            / 2),
                Box,
                Box);

            p.fillRect(
                box,
                face);

            drawCoderGirlBevel(
                p,
                box,
                false);

            if (g.checked) {
                p.fillRect(
                    box.adjusted(
                        4,
                        4,
                        -4,
                        -4),
                    highlight);
            }

            drawCoderGirlText(
                p,
                box.x()
                    + Box
                    + 6,
                r.y()
                    + (r.height()
                           - 16)
                        / 2,
                g.text,
                text);

            return;
        }

        if (g.type == QStringLiteral("Slider")) {
            // Mirrors Core/codergirl/gadgets/cg_gad_slider.c. Unlike a
            // scrollbar, the slider has NO outer frame: a thin 6px track,
            // value-fill and an 18px knob with a recessed centre.
            const QRect content = r.adjusted(4, 4, -4, -4);
            if (content.width() <= 0 || content.height() <= 0)
                return;

            const bool vertical = g.orientation == 0;
            const int trackThickness = 6;
            const QRect track = vertical
                ? QRect(content.x() + (content.width() - trackThickness) / 2,
                        content.y(), trackThickness, content.height())
                : QRect(content.x(),
                        content.y() + (content.height() - trackThickness) / 2,
                        content.width(), trackThickness);
            const int axisLen = vertical ? content.height() : content.width();
            int knobLen = qMin(18, axisLen);
            if (knobLen < 6)
                knobLen = axisLen;
            const int travel = qMax(0, axisLen - knobLen);
            const int range = g.maximum - g.minimum;
            const int offset = (range > 0 && travel > 0)
                ? int((qint64(qBound(g.minimum, g.value, g.maximum) - g.minimum)
                      * travel + range / 2) / range)
                : 0;

            p.fillRect(track, coderGirlPen(16)); // PEN_SCROLLBAR_TRACK
            const QRect well = track.adjusted(1, 1, -1, -1);
            if (well.width() > 0 && well.height() > 0) {
                if (!vertical) {
                    const int centre = content.x() + offset + knobLen / 2;
                    p.fillRect(QRect(well.x(), well.y(),
                                     qBound(0, centre - well.x(), well.width()),
                                     well.height()), coderGirlPen(4));
                } else {
                    const int centre = content.y() + offset + knobLen / 2;
                    const int fillHeight = qBound(0, well.y() + well.height() - centre,
                                                   well.height());
                    p.fillRect(QRect(well.x(), well.y() + well.height() - fillHeight,
                                     well.width(), fillHeight), coderGirlPen(4));
                }
            }
            drawCoderGirlBevel(p, track, true);

            const QRect knob = vertical
                ? QRect(content.x(), content.y() + offset, content.width(), knobLen)
                : QRect(content.x() + offset, content.y(), knobLen, content.height());
            p.fillRect(knob, coderGirlPen(4));
            drawCoderGirlBevel(p, knob, false);
            const QRect innerKnob = knob.adjusted(4, 4, -4, -4);
            if (innerKnob.width() > 0 && innerKnob.height() > 0)
                drawCoderGirlBevel(p, innerKnob, true);
            return;
        }

        if (g.type == QStringLiteral("Scrollbar")) {
            // Mirrors Core/codergirl/gadgets/cg_gad_scrollbar.c.  The
            // firmware uses inset=2, 16px arrow buttons and a page-size
            // thumb (minimum 24px, step_large=10 in generated C source).
            const bool vertical = g.orientation == 0;
            const bool docked = g.flags.contains(QStringLiteral("GAD_TOOL_DOCKED_RIGHT"))
                || g.flags.contains(QStringLiteral("GAD_TOOL_DOCKED_BOTTOM"));
            const bool arrows = g.flags.contains(QStringLiteral("GAD_TOOL_SCROLLARROWS"));
            if (r.width() <= 0 || r.height() <= 0)
                return;

            p.fillRect(r, coderGirlPen(docked ? windowBackPen : 6));
            if (!docked)
                drawCoderGirlBevel(p, r, false);

            QRect well = r.adjusted(2, 2, -2, -2);
            if (arrows) {
                if (vertical)
                    well.adjust(0, 16, 0, -16);
                else
                    well.adjust(16, 0, -16, 0);
            }
            if (well.width() <= 0 || well.height() <= 0)
                return;

            p.fillRect(well, coderGirlPen(6)); // PEN_DIALOG_BG
            drawCoderGirlBevel(p, well, true);
            if (!docked)
                drawCoderGirlBevel(p, well.adjusted(-2, -2, 2, 2), false);

            if (arrows) {
                if (vertical) {
                    if (!docked) {
                        drawCoderGirlBevel(p, QRect(r.x(), r.y(), r.width(), 16), false);
                        drawCoderGirlBevel(p, QRect(r.x(), r.y() + r.height() - 16,
                                                     r.width(), 16), false);
                    }
                    drawCoderGirlScrollbarArrow(p, r.x() + (r.width() - 16) / 2, r.y(), 0);
                    drawCoderGirlScrollbarArrow(p, r.x() + (r.width() - 16) / 2,
                                                  r.y() + r.height() - 16, 1);
                } else {
                    if (!docked) {
                        drawCoderGirlBevel(p, QRect(r.x(), r.y(), 16, r.height()), false);
                        drawCoderGirlBevel(p, QRect(r.x() + r.width() - 16, r.y(),
                                                     16, r.height()), false);
                    }
                    drawCoderGirlScrollbarArrow(p, r.x(), r.y() + (r.height() - 16) / 2, 2);
                    drawCoderGirlScrollbarArrow(p, r.x() + r.width() - 16,
                                                  r.y() + (r.height() - 16) / 2, 3);
                }
            }

            const int trackLen = vertical ? well.height() : well.width();
            const int range = g.maximum - g.minimum;
            // scrollbar_create(..., 1, 10, flags): step_large = 10
            const int thumbLen = range <= 0 ? trackLen :
                qMin(trackLen, qMax(24, int((10LL * trackLen + (range + 10) / 2)
                                              / (range + 10))));
            const int travel = qMax(0, trackLen - thumbLen);
            const int offset = (range > 0 && travel > 0)
                ? int((qint64(qBound(g.minimum, g.value, g.maximum) - g.minimum)
                      * travel + range / 2) / range)
                : 0;

            QRect thumb = vertical
                ? QRect(well.x(), well.y() + offset, well.width(), thumbLen)
                : QRect(well.x() + offset, well.y(), thumbLen, well.height());
            thumb = thumb.adjusted(thumb.width() > 2 ? 1 : 0,
                                   thumb.height() > 2 ? 1 : 0,
                                   thumb.width() > 2 ? -1 : 0,
                                   thumb.height() > 2 ? -1 : 0);
            if (thumb.width() > 0 && thumb.height() > 0) {
                p.fillRect(thumb, coderGirlPen(4));
                drawCoderGirlBevel(p, thumb, false);
            }
            return;
        }

        if (g.type
            == QStringLiteral(
                "ProgressBar")) {
            p.fillRect(
                r,
                coderGirlPen(16));

            drawCoderGirlBevel(
                p,
                r,
                true);

            const int minimum =
                qMin(
                    g.minimum,
                    g.maximum);

            const int maximum =
                qMax(
                    g.minimum,
                    g.maximum);

            const qreal ratio =
                qBound(
                    0.0,
                    (g.value
                     - minimum)
                        / qreal(
                            qMax(
                                1,
                                maximum
                                    - minimum)),
                    1.0);

            QRect fill =
                r.adjusted(
                    2,
                    2,
                    -2,
                    -2);

            fill.setWidth(
                qRound(
                    fill.width()
                    * ratio));

            p.fillRect(
                fill,
                coderGirlPen(3));

            return;
        }

        if (g.type == QStringLiteral("TextBox")) {
            /*
             * Mirror SIDBOX firmware Core/codergirl/gadgets/cg_gad_textbox.c
             * draw_textbox(). The old preview used a single recessed border,
             * an incorrect face pen and (3,2) text offset; the device draws
             * an outer RAISED border, an inner RECESSED border at +2, and
             * an 8x16 character viewport starting at +4,+4.
             *
             * A Designer preview is unfocused, so the runtime's optional
             * focus outline and caret are deliberately not shown here.
             */
            p.save();
            p.setClipRect(r, Qt::IntersectClip);

            // SBOS_CreateTextBox sets BPen from the parent window colour.
            p.fillRect(r, coderGirlPen(windowBackPen));
            drawCoderGirlBevel(p, r, false);
            if (r.width() > 4 && r.height() > 4)
                drawCoderGirlBevel(p, r.adjusted(2, 2, -2, -2), true);

            const QRect textArea = r.adjusted(4, 4, -4, -4);
            if (textArea.width() > 0 && textArea.height() > 0) {
                constexpr int CharWidth = 8;
                constexpr int CharHeight = 16;
                const int maxCols = qBound(1, textArea.width() / CharWidth, 511);
                const int maxLines = qMax(1, textArea.height() / CharHeight);
                const bool multiline = g.typeFlags.contains(QStringLiteral("TB_MULTILINE"));

                // The hardware TextBox draws in PEN_TEXT, not g.fPen.
                const QColor ink = coderGirlPen(16); // DEFAULT_THEME PEN_TEXT
                const QStringList lines = g.text.split(QLatin1Char('\n'), Qt::KeepEmptyParts);
                const int visibleLines = multiline ? qMin(maxLines, static_cast<int>(lines.size())) : 1;
                for (int line = 0; line < visibleLines; ++line) {
                    const QByteArray chars = lines.at(line).toLatin1().left(maxCols);
                    drawCoderGirlText(p, textArea.x(),
                                      textArea.y() + line * CharHeight,
                                      QString::fromLatin1(chars.constData(), chars.size()), ink);
                }
            }
            p.restore();
            return;
        }

        if (g.type == QStringLiteral("TextArea")) {
            // TextArea is a separate firmware gadget; keep its preview as-is.
            p.fillRect(r, coderGirlPen(1));
            drawCoderGirlBevel(p, r, true);
            drawCoderGirlText(p, r.x() + 3, r.y() + 2, g.text, text);
            return;
        }

        if (g.type
            == QStringLiteral(
                "ListBox")) {
            p.fillRect(
                r,
                coderGirlPen(
                    windowBackPen));

            if (!g.flags.contains(QStringLiteral("GAD_TOOL_NOBORDER"))) {
                drawCoderGirlBevel(
                    p,
                    r,
                    g.flags.contains(QStringLiteral("GAD_TOOL_INSET")));
            }

            int y =
                r.y() + 2;

            const QStringList rows =
                g.listItems;

            for (int row = 0;
                 row < rows.size()
                 && y + 16
                        <= r.bottom() + 1;
                 ++row) {
                const int maxChars =
                    qMax(
                        0,
                        (r.width() - 8)
                            / 8);

                drawCoderGirlText(
                    p,
                    r.x() + 3,
                    y,
                    rows.at(row).left(
                        maxChars),
                    text);

                y += 18;
            }

            return;
        }

        if (g.type
            == QStringLiteral(
                "GridSelect")) {
            p.fillRect(
                r,
                coderGirlPen(
                    windowBackPen));

            drawCoderGirlBevel(
                p,
                r,
                true);

            const int cols =
                qMax(1, g.cellsX);

            const int rows =
                qMax(1, g.cellsY);

            const int cellW =
                qMax(1, r.width() / cols);

            const int cellH =
                qMax(1, r.height() / rows);

            for (int row = 0; row < rows; ++row) {
                for (int col = 0; col < cols; ++col) {
                    QRect cell(
                        r.x() + col * cellW,
                        r.y() + row * cellH,
                        col == cols - 1
                            ? r.right() - (r.x() + col * cellW) + 1
                            : cellW,
                        row == rows - 1
                            ? r.bottom() - (r.y() + row * cellH) + 1
                            : cellH);

                    cell.adjust(1, 1, -1, -1);

                    if (cell.width() > 0
                        && cell.height() > 0) {
                        p.fillRect(
                            cell,
                            coderGirlPen(windowBackPen));

                        drawCoderGirlBevel(
                            p,
                            cell,
                            true);

                        const int index =
                            row * cols + col;

                        const QString label =
                            g.gridCellText
                                .value(index)
                                .left(4);

                        if (!label.isEmpty()) {
                            const int tx =
                                cell.x()
                                + (cell.width()
                                   - coderGirlTextWidth(label))
                                      / 2;

                            const int ty =
                                cell.y()
                                + (cell.height() - 16) / 2;

                            drawCoderGirlText(
                                p,
                                tx,
                                ty,
                                label,
                                text);
                        }
                    }
                }
            }

            return;
        }

        if (g.type
            == QStringLiteral(
                "Canvas")) {
            /*
             * Match firmware draw_canvas(): Canvas is a primitive renderer,
             * not a framed gadget. The client background was already painted
             * by the Window, so only draw the selected primitive here.
             */
            const QString mode =
                g.typeFlags.trimmed().isEmpty()
                    ? QStringLiteral("CNV_RECT")
                    : g.typeFlags.trimmed();

            const QColor fpen =
                coderGirlPen(
                    g.fPen >= 0
                        ? g.fPen
                        : defaultFPenForType(
                              g.type));

            const QColor bpen =
                coderGirlPen(
                    g.bPen >= 0
                        ? g.bPen
                        : 2); // default bevel BPen (Canvas)

            if (mode == QStringLiteral("CNV_LINE")) {
                p.setPen(fpen);
                p.drawLine(
                    r.left(),
                    r.top(),
                    r.right(),
                    r.bottom());
                return;
            }

            if (mode == QStringLiteral("CNV_RECTF")) {
                p.fillRect(
                    r,
                    fpen);
                return;
            }

            if (mode == QStringLiteral("CNV_BEVEL")) {
                const bool inset =
                    g.flags.contains(
                        QStringLiteral("GAD_TOOL_INSET"));

                const QColor topLeft =
                    inset ? fpen : bpen;

                const QColor bottomRight =
                    inset ? bpen : fpen;

                p.setPen(topLeft);
                p.drawLine(
                    r.left(),
                    r.top(),
                    r.right(),
                    r.top());
                p.drawLine(
                    r.left(),
                    r.top(),
                    r.left(),
                    r.bottom());

                p.setPen(bottomRight);
                if (r.width() > 1) {
                    p.drawLine(
                        r.left(),
                        r.bottom(),
                        r.right() - 1,
                        r.bottom());
                }
                p.drawLine(
                    r.right(),
                    r.top(),
                    r.right(),
                    r.bottom());
                return;
            }

            /* CNV_RECT (and safe fallback): one-pixel FPen outline. */
            p.setPen(fpen);
            p.drawLine(
                r.left(),
                r.top(),
                r.right(),
                r.top());

            if (r.height() > 1) {
                p.drawLine(
                    r.left(),
                    r.bottom(),
                    r.right(),
                    r.bottom());
            }

            if (r.height() > 2) {
                p.drawLine(
                    r.left(),
                    r.top() + 1,
                    r.left(),
                    r.bottom() - 1);

                if (r.width() > 1) {
                    p.drawLine(
                        r.right(),
                        r.top() + 1,
                        r.right(),
                        r.bottom() - 1);
                }
            }

            return;
        }

        if (g.type
            == QStringLiteral(
                "BitmapView")) {
            p.fillRect(
                r,
                coderGirlPen(
                    windowBackPen));

            const bool noBorder =
                designerWindowFlag(
                    g.flags,
                    QStringLiteral(
                        "GAD_TOOL_NOBORDER"));

            if (!noBorder) {
                drawCoderGirlBevel(
                    p,
                    r,
                    g.flags.contains(
                        QStringLiteral("GAD_TOOL_INSET")));
            }

            const int inset =
                noBorder
                    ? 0
                    : 1;

            const QRect imageRect =
                r.adjusted(
                    inset,
                    inset,
                    -inset,
                    -inset);

            if (!g.bitmapPixels.isEmpty()
                && g.bitmapWidth > 0
                && g.bitmapHeight > 0
                && g.bitmapPixels.size()
                   >= static_cast<qsizetype>(
                          g.bitmapWidth)
                      * static_cast<qsizetype>(
                          g.bitmapHeight)) {
                QImage image(
                    g.bitmapWidth,
                    g.bitmapHeight,
                    QImage::Format_ARGB32);

                qsizetype sourceIndex = 0;

                for (int y = 0;
                     y < g.bitmapHeight;
                     ++y) {
                    QRgb *row =
                        reinterpret_cast<QRgb *>(
                            image.scanLine(y));

                    for (int x = 0;
                         x < g.bitmapWidth;
                         ++x) {
                        const quint8 pen =
                            static_cast<quint8>(
                                g.bitmapPixels.at(
                                    sourceIndex++));

                        row[x] =
                            static_cast<QRgb>(
                                kCoderGirlClut[pen]);
                    }
                }

                p.save();
                p.setClipRect(
                    imageRect,
                    Qt::IntersectClip);
                p.drawImage(
                    imageRect.topLeft(),
                    image);
                p.restore();
                return;
            }

            const int cell = 8;

            for (int y = imageRect.top();
                 y <= imageRect.bottom();
                 y += cell) {
                for (int x = imageRect.left();
                     x <= imageRect.right();
                     x += cell) {
                    if (((x / cell)
                         + (y / cell))
                        & 1) {
                        p.fillRect(
                            QRect(
                                x,
                                y,
                                qMin(
                                    cell,
                                    imageRect.right()
                                        - x
                                        + 1),
                                qMin(
                                    cell,
                                    imageRect.bottom()
                                        - y
                                        + 1)),
                            coderGirlPen(6));
                    }
                }
            }

            return;
        }

        if (g.type == QStringLiteral("Button")) {
            // Match cg_gad_button.c::draw_button() in the SIDBOX core.
            p.fillRect(r, face);
            if (!designerWindowFlag(g.flags, QStringLiteral("GAD_TOOL_NOBORDER")))
                drawCoderGirlBevel(p, r, false);

            const bool cycle = designerWindowFlag(
                g.flags, QStringLiteral("GAD_TOOL_CYCLEBUTTON"));
            const bool below = designerWindowFlag(
                g.flags, QStringLiteral("GAD_TOOL_ALIGN_BELOW"));
            const QString caption = cycle
                ? g.text.section(QLatin1Char('|'), 0, 0)
                : g.text;
            const int charWidth = coderGirlTextWidth(caption);
            const int leftPad = cycle ? 24 : 0;

            if (cycle) {
                // Core/codergirl/graphics/cg_glyphs.c: glyph_cycle (16x16,
                // column-major CLUT indices). 0 is transparent.
                static const quint8 cycleGlyph[256] = {
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                };
                const int gx = r.x() + 4;
                const int gy = r.y() + (r.height() - 16) / 2;
                p.save();
                p.setClipRect(r, Qt::IntersectClip);
                p.setPen(coderGirlPen(16)); // PEN_WIN_BEVEL_L
                p.drawLine(gx + 21, gy - 2, gx + 21,
                           gy - 2 + qMax(0, r.height() - 7));
                p.setPen(coderGirlPen(2)); // PEN_WIN_BEVEL_H
                p.drawLine(gx + 22, gy - 2, gx + 22,
                           gy - 2 + qMax(0, r.height() - 7));
                for (int col = 0; col < 16; ++col) {
                    for (int row = 0; row < 16; ++row) {
                        const quint8 pen = cycleGlyph[col * 16 + row];
                        if (pen)
                            p.fillRect(gx + 2 + col, gy + row, 1, 1,
                                       coderGirlPen(pen));
                    }
                }
                p.restore();
            }

            int tx = r.x() + leftPad
                   + (qMax(0, r.width() - leftPad) - charWidth) / 2;
            int ty = r.y() + (r.height() - 16) / 2;
            if (below) {
                ty = r.y() + r.height() + 2;
                if (designerWindowFlag(g.flags, QStringLiteral("GAD_TOOL_ALIGN_LEFT")))
                    tx = r.x() + 2;
                else if (designerWindowFlag(g.flags, QStringLiteral("GAD_TOOL_ALIGN_RIGHT")))
                    tx = r.x() + r.width() - 2 - charWidth;
                else
                    tx = r.x() + (r.width() - charWidth) / 2;
            }
            if (designerWindowFlag(g.flags, QStringLiteral("GAD_TOOL_OPAQUE_TEXT")))
                p.fillRect(QRect(tx - 2, ty - 1, charWidth + 4, 18), face);
            drawCoderGirlText(p, tx, ty, caption, text);
            return;
        }

        /*
         * Button and future button-like controls.
         */
        p.fillRect(
            r,
            face);

        drawCoderGirlBevel(
            p,
            r,
            false);

        const QString caption =
            g.text.isEmpty()
                ? g.type
                : g.text;

        const int tx =
            r.x()
            + (r.width()
               - coderGirlTextWidth(
                   caption))
                / 2;

        const int ty =
            r.y()
            + (r.height()
               - 16)
                / 2;

        drawCoderGirlText(
            p,
            tx,
            ty,
            caption,
            text);
    }

    GuiDesignerWindow *m_window = nullptr;
    QList<GuiDesignerGadget> *m_gadgets = nullptr;
    QList<GuiDesignerMenuTitle> *m_menus = nullptr;
    int m_zoomPercent = 200;
    int m_gridSnap = 4; // Brand-new designs default to 4-pixel grid snapping.
    int m_selected = -1;
    QList<int> m_multiSelected;
    bool m_marqueeSelecting = false;
    QPoint m_marqueeStart;
    QRect m_marqueeRect;
    bool m_groupDragging = false;
    QHash<int, QRect> m_groupStartRects;
    int m_groupDragAnchor = -1;
    bool m_dragging = false;
    bool m_resizing = false;
    bool m_windowResizing = false;
    bool m_windowDragging = false;
    Qt::Edges m_windowResizeEdges;
    Qt::Edges m_gadgetResizeEdges;
    QPoint m_pressLogical;
    QRect m_startRect;
};

// Designer-only property layout: labels sit above inputs, with two compact
// columns for short fields and full-width rows for longer controls.
// This replaces the old side-by-side QFormLayout without changing any property
