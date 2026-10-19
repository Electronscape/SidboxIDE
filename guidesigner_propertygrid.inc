// Stage 3.71: moved intact from guidesigner.cpp; included once inside GuiDesignerDetail.
// bindings, gadget logic, callbacks, or generated applet code.
class GuiDesignerPropertyGrid final : public QGridLayout
{
public:
    explicit GuiDesignerPropertyGrid(QWidget *host)
        : QGridLayout(host), m_host(host)
    {
        setColumnStretch(0, 1);
        setColumnStretch(1, 1);
        setHorizontalSpacing(8);
        setVerticalSpacing(7);
        setAlignment(Qt::AlignTop);
    }

    void clearRows()
    {
        // Every cell contains a QWidget (not a bare child layout), so deleting
        // it also deletes its label and editor without leaving old connections.
        while (QLayoutItem *item = takeAt(0)) {
            delete item->widget();
            delete item;
        }
        m_row = 0;
        m_col = 0;
    }

    void addRow(const QString &title, QWidget *control)
    {
        if (!control) return;

        const bool compact = !title.isEmpty()
            && title.size() <= 16
            && (qobject_cast<QAbstractSpinBox *>(control)
                || qobject_cast<QCheckBox *>(control));

        // Avoid the minimum-size hints of long line edits and combo boxes
        // making QScrollArea acquire an unwanted horizontal scrollbar.
        if (qobject_cast<QLineEdit *>(control)
            || qobject_cast<QComboBox *>(control)) {
            control->setMinimumWidth(0);
            control->setSizePolicy(QSizePolicy::Ignored,
                                   control->sizePolicy().verticalPolicy());
        }

        auto *cell = new QWidget(m_host);
        cell->setMinimumWidth(0);
        auto *stack = new QVBoxLayout(cell);
        stack->setContentsMargins(0, 0, 0, 0);
        stack->setSpacing(3);
        if (!title.isEmpty()) {
            auto *label = new QLabel(title, cell);
            label->setTextFormat(Qt::PlainText);
            label->setWordWrap(true);
            label->setMinimumWidth(0);
            label->setToolTip(title);
            stack->addWidget(label);
        }
        stack->addWidget(control);
        addCell(cell, compact);
    }

    void addRow(const QString &title, QLayout *controls)
    {
        if (!controls) return;
        auto *holder = new QWidget(m_host);
        holder->setMinimumWidth(0);
        auto *inner = new QVBoxLayout(holder);
        inner->setContentsMargins(0, 0, 0, 0);
        inner->addLayout(controls);
        addRow(title, holder);
    }

    void addRow(QWidget *widget)
    {
        if (!widget) return;
        if (auto *label = qobject_cast<QLabel *>(widget)) {
            label->setWordWrap(true);
            label->setMinimumWidth(0);
        }
        widget->setMinimumWidth(0);
        addCell(widget, false);
    }

    void addRow(QLayout *layout)
    {
        if (!layout) return;
        auto *holder = new QWidget(m_host);
        auto *inner = new QVBoxLayout(holder);
        inner->setContentsMargins(0, 0, 0, 0);
        inner->addLayout(layout);
        addRow(holder);
    }

private:
    void addCell(QWidget *widget, bool compact)
    {
        // A wide property finishes any half-filled row before spanning both
        // columns, so long fields never squeeze short coordinate controls.
        if (!compact && m_col != 0) {
            ++m_row;
            m_col = 0;
        }
        QGridLayout::addWidget(widget, m_row, m_col, 1, compact ? 1 : 2);
        if (compact && m_col == 0) {
            m_col = 1;
        } else {
            ++m_row;
            m_col = 0;
        }
    }

    QWidget *m_host = nullptr;
    int m_row = 0;
    int m_col = 0;
};

