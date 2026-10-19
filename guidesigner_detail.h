#ifndef GUIDESIGNER_DETAIL_H
#define GUIDESIGNER_DETAIL_H

// Internal GUI Designer model and SIDBOX rendering interface.
// No changes to .sbui serialization, firmware values, or drawing algorithms.
#include <QByteArray>
#include <QColor>
#include <QImage>
#include <QList>
#include <QPainter>
#include <QRect>
#include <QString>
#include <QStringList>

namespace GuiDesignerDetail {
struct GuiDesignerGadget
{
    QString type;
    QString name;
    QRect rect;
    QString text;
    QString flags = QStringLiteral("GAD_TOOL_DEFAULT");
    int bPen = -1;
    int fPen = -1;
    int hPen = -1;
    QString onActivate;
    QString onChange;
    QString openWindowFile; // Project-relative .sbui target; empty means normal callback only.
    // Virtual TabGroup membership. A blank owner means always visible.
    QString tabOwner;
    int tabPage = 0;
    // Virtual TabGroup: page initially visible when the generated window opens.
    // This is independent of `value`, which is the designer preview page.
    int defaultTabPage = 0;

    // -1 = follow Window callback mode, 0 = WindowProc events, 1 = own direct callback.
    int callbackRoute = -1;

    int minimum = 0;
    int maximum = 100;
    int value = 0;
    int orientation = 1; // CoderGirl: 0 vertical, 1 horizontal
    int checked = 0;
    bool enabled = true;
    int group = 0;
    QString typeFlags;

    int cellWidth = 24;
    int cellHeight = 18;
    int cellsX = 4;
    int cellsY = 4;

    /*
     * GridSelect label text, one entry per cell in row-major order.
     * CoderGirl's public designer contract is four visible characters max.
     */
    QStringList gridCellText;

    int bitmapWidth = 64;
    int bitmapHeight = 64;

    /*
     * Optional applet C expression for the BitmapView's pixel source.
     * Example: canvas_pixels
     */
    QString bitmapSource;

    /*
     * Optional designer-embedded indexed bitmap. When non-empty this contains
     * one Sidbox CLUT index per source pixel, row-major. The original PNG path
     * is informational only; the converted bytes are stored in the .sbui so
     * the project stays portable.
     */
    QByteArray bitmapPixels;
    QString bitmapImagePath;

    /*
     * Designer-side initial ListBox contents.
     *
     * Generated applets create a caller-owned ItemLists_t model, add these
     * strings to it, then attach that model to the ListBox. This deliberately
     * mirrors the firmware API: the ListBox itself does not own its item list.
     */
    QStringList listItems;

    // Virtual (designer-only) cooperative timer; no on-screen SIDBOX gadget.
    // period = 0 selects a one-shot in the public CoderGirl timer API.
    int timerDelayMs = 1000;
    int timerPeriodMs = 1000;
    bool timerRepeat = true;
    bool timerAutoStart = true;
    bool timerKeepAliveOnClose = false; // Background timer survives CloseWindow().

    // Virtual Messenger: send and/or cooperative receive.  All incoming messages
    // remain in the applet-owned OS mailbox; sending never runs foreign code.
    bool ipcReceive = true;
    int ipcPollMs = 25; // 10..1000ms; drains at most eight messages each tick.
    QString ipcTargetApp; // Target applet filename, e.g. ipc_rx.app; resolved per send.
    // Ordinary Button can send text through a selected virtual Messenger.
    QString ipcSendTarget;
    int ipcSendType = 1;
    QString ipcSendText = QStringLiteral("Hello from SIDBOX!");

    // Virtual exclusive UART1 lease; defaults to manual Open() for safety.
    int uart1Baud = 9600;
    int uart1DataBits = 8;
    int uart1Parity = 0; // 0=None, 1=Even, 2=Odd
    int uart1StopBits = 1;
    int uart1PollMs = 20;
    bool uart1AutoOpen = false;

    // Designer-only Media object. The firmware sees only ordinary audio API calls.
    QString mediaMode = QStringLiteral("SFX"); // SFX or Music
    QString mediaFile;
    // For compatibility, .sbui stores imported PCM8 bytes XOR 0x80.
    // The generated media_sfx.c reverses that transformation: BETH mixes unsigned PCM8.
    // The generated <design>res/media_sfx.c is compilable data, separate from the window source.
    bool mediaEmbedSfx = false;
    QString mediaEmbeddedName;
    QByteArray mediaEmbeddedPcm;
    int mediaChannel = 0;    // BETH: 8 PCM voices, 0..7
    int mediaVolume = 200;   // documented default range 0..255
    int mediaPan = 0;        // -127..127
    int mediaFrequency = 22050;
    int mediaSubsong = 0;
    bool mediaLoop = false;  // PCM only; music looping is engine/format-specific
    bool mediaAutoStart = false;
    // Buttons may target a named virtual Media component.
    QString mediaTarget;
    QString mediaAction = QStringLiteral("Play");

    // Virtual non-blocking CoderGirl dialogs; no physical canvas gadget.
    QString dialogTitle = QStringLiteral("Select a file");
    QString dialogMessage = QStringLiteral("Are you sure?");
    QString dialogDir = QStringLiteral("sdcard:/");
    QString dialogFilter = QStringLiteral("*.*");
    QString dialogKind = QStringLiteral("Message"); // Message / Info
    QString dialogButtons = QStringLiteral("OK/Cancel");
    bool dialogBlockOwner = false;
    QString dialogTarget; // Button -> virtual FileRequester/MessageBox name
};

struct GuiDesignerWindow
{
    QString name = QStringLiteral("MainWindow");
    QRect rect = QRect(32, 38, 400, 250);
    QString title = QStringLiteral("CoderGirl Application");
    QString flags = QStringLiteral("SBX_WIN_DEFAULT");
    int backPen = 1; // PEN_WIN_BG in the supplied DEFAULT_THEME

    // 0 = WindowProc event manager, 1 = direct gadget/menu callbacks.
    // Direct is the compatibility default for existing .sbui designs.
    int callbackMode = 1;
};

struct GuiDesignerMenuItem
{
    QString name;
    QString text;
    QString callback;
    QString flags;
};

struct GuiDesignerMenuTitle
{
    QString title;
    QList<GuiDesignerMenuItem> items;
};

/*
 * Exact Sidbox 256-entry ARGB CLUT supplied with the hardware/application
 * sources. Keeping the palette here makes the visual designer preview use the
 * same pen numbers CoderGirl renders on the real Sidbox.
*/

extern const quint32 kCoderGirlClut[256];
bool isVirtualDesignerGadget(const QString &type);
QStringList designerTabTitles(const GuiDesignerGadget &g);
QByteArray convertImageToCoderGirlIndices(const QImage &source);
QColor coderGirlPen(int pen);
void drawCoderGirlText(QPainter &p, int x, int y, const QString &text, const QColor &colour);
int coderGirlTextWidth(const QString &text);
bool designerWindowFlag(const QString &flags, const QString &flag);
void drawCoderGirlBevel(QPainter &p, const QRect &rect, bool pressed);
void drawCoderGirlScrollbarArrow(QPainter &p, int x, int y, int dir);
void drawCoderGirlTitleButton(QPainter &p, const QRect &rect, int fillPen);
void drawCoderGirlCloseGlyph(QPainter &p, const QRect &rect);
void drawCoderGirlMinimiseGlyph(QPainter &p, const QRect &rect);
void drawCoderGirlMaxGlyph(QPainter &p, const QRect &rect);
void drawCoderGirlZOrderGlyph(QPainter &p, const QRect &rect);
void drawCoderGirlResizeGlyph(QPainter &p, const QRect &rect);
QString safeCIdentifier(QString text, const QString &fallback);
QString escapedCString(QString text);
} // namespace GuiDesignerDetail
#endif // GUIDESIGNER_DETAIL_H
