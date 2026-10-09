#include "guidesigner.h"

#include <algorithm>
#include <functional>
#include <utility>

#include <QAbstractItemView>
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

namespace {
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

static bool isVirtualDesignerGadget(const QString &type)
{
    return type == QStringLiteral("Timer") || type == QStringLiteral("Media")
        || type == QStringLiteral("FileRequester") || type == QStringLiteral("MessageBox");
}

static QStringList designerTabTitles(const GuiDesignerGadget &g)
{
    QStringList titles;
    for (const QString &s : g.text.split(QLatin1Char('|'))) {
        if (!s.trimmed().isEmpty()) titles << s.trimmed();
    }
    if (titles.isEmpty()) titles << QStringLiteral("Page 1");
    return titles.mid(0, 8);
}

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
static const quint32 kCoderGirlClut[256] = {
    0x00000000, 0xFFAFAFAF, 0xFFFFFFFF, 0xFF3B67A2, 0xFFAA907C, 0xFF959595, 0xFF7B7B7B, 0xFFFFA997,
    0xFF37A91D, 0xFF7CA9FF, 0xFFBF8112, 0xFFEBBF66, 0xFF78C178, 0xFF3D9318, 0xFFB33418, 0xFFD9311C,
    0xFF000000, 0xFF00000E, 0xFF00001D, 0xFF00002B, 0xFF000139, 0xFF000147, 0xFF000156, 0xFF000164,
    0xFF0001D2, 0xFF0001FF, 0xFFCECECE, 0xFF00FF00, 0xFFB2FF00, 0xFFFFE700, 0xFFFF9600, 0xFFFF1100,
    0xFF491200, 0xFF491355, 0xFF4914AA, 0xFF4916FF, 0xFF5B1700, 0xFF5B1855, 0xFF5B19AA, 0xFF5B1AFF,
    0xFF6D1B00, 0xFF6D1C55, 0xFF00E300, 0xFF85FF54, 0xFFC4FF00, 0xFFFFD900, 0xFFFFA41F, 0xFFE05400,
    0xFFFF0000, 0xFF922655, 0xFF9227AA, 0xFF9228FF, 0xFFA42900, 0xFFA42A55, 0xFFA42BAA, 0xFFA42CFF,
    0xFFB62D00, 0xFFB62F55, 0xFFB630AA, 0xFFB631FF, 0xFFC93200, 0xFFC93355, 0xFFC934AA, 0xFFC935FF,
    0xFFDB3700, 0xFFDB3855, 0xFFDB39AA, 0xFFDB3AFF, 0xFFED3B00, 0xFFED3C55, 0xFFED3DAA, 0xFFED3FFF,
    0xFFFF4000, 0xFFFF4155, 0xFFFF42AA, 0xFFFF43FF, 0xFF004400, 0xFF004555, 0xFF0046AA, 0xFF0048FF,
    0xFFFFFF00, 0xFF12FF55, 0xFF12EE55, 0xFF12B6FF, 0xFF001FFF, 0xFF9D0EC7, 0xFFF10000, 0xFFFF7700,
    0xFF375200, 0xFF375355, 0xFF3754AA, 0xFF3755FF, 0xFF495600, 0xFF495855, 0xFF4959AA, 0xFF495AFF,
    0xFF5B5B00, 0xFF5B5C55, 0xFF5B5DAA, 0xFF5B5EFF, 0xFF6D6000, 0xFF6D6155, 0xFF6D62AA, 0xFF6D63FF,
    0xFF6D6400, 0xFF806555, 0xFF8066AA, 0xFF8067FF, 0xFF926900, 0xFF926A55, 0xFF926BAA, 0xFF926CFF,
    0xFFA46D00, 0xFFA46E55, 0xFFA46FAA, 0xFFA471FF, 0xFFB67200, 0xFFB67355, 0xFFB674AA, 0xFFB675FF,
    0xFFC97600, 0xFFC97755, 0xFFC979AA, 0xFFC97AFF, 0xFFDB7B00, 0xFFDB7C55, 0xFFDB7DAA, 0xFFDB7EFF,
    0xFFED7F00, 0xFFED8055, 0xFFED82AA, 0xFFED83FF, 0xFFFF8400, 0xFFFF8555, 0xFFFF86AA, 0xFFFF87FF,
    0xFF008800, 0xFF008A55, 0xFF008BAA, 0xFF008CFF, 0xFF128D00, 0xFF128E55, 0xFF128FAA, 0xFF1290FF,
    0xFF249200, 0xFF249355, 0xFF2494AA, 0xFF2495FF, 0xFF379600, 0xFF379755, 0xFF3798AA, 0xFF3799FF,
    0xFF499B00, 0xFF499C55, 0xFF499DAA, 0xFF499EFF, 0xFF5B9F00, 0xFF5BA055, 0xFF5BA1AA, 0xFF5BA3FF,
    0xFFA4B5D5, 0xFFA0B0F8, 0xFF94A3E6, 0xFF7C89C1, 0xFF6281C0, 0xFF1C62A1, 0xFF4254EA, 0xFF62A1BD,
    0xFF7093C0, 0xFF4977A1, 0xFF003FAA, 0xFF1554FF, 0xFF1C50B9, 0xFF00B3FF, 0xFF0088AA, 0xFF00B5FF,
    0xFF0E62FF, 0xFF5EB7E3, 0xFFBDC0B9, 0xFF85B9FF, 0xFF006CAF, 0xFF1F81B9, 0xFF3F5BAA, 0xFFC9BEFF,
    0xFF5BAFCB, 0xFFDBC055, 0xFFDBC1AA, 0xFFBDC0C0, 0xFFEDC400, 0xFFEDC555, 0xFFEDC6AA, 0xFFEDC7FF,
    0xFFFFC800, 0xFFFFC955, 0xFFFFCAAA, 0xFFFFCCFF, 0xFF00CD00, 0xFF00CE55, 0xFF00CFAA, 0xFF00D0FF,
    0xFF12D100, 0xFF12D255, 0xFF12D3AA, 0xFF12D5FF, 0xFF24D600, 0xFF24D755, 0xFF24D8AA, 0xFF24D9FF,
    0xFF37DA00, 0xFF37DB55, 0xFF37DDAA, 0xFF37DEFF, 0xFF49DF00, 0xFF49E055, 0xFF49E1AA, 0xFF49E2FF,
    0xFF5BE300, 0xFF5BE555, 0xFF5BE6AA, 0xFF5BE7FF, 0xFF6DE800, 0xFF6DE955, 0xFF6DEAAA, 0xFF6DEBFF,
    0xFF6DEC00, 0xFF80EE55, 0xFF80EFAA, 0xFF80F0FF, 0xFF93CEA2, 0xFF92F255, 0xFF92F3AA, 0xFF92F4FF,
    0xFFA4F600, 0xFFA4F755, 0xFFA4F8AA, 0xFFA4F9FF, 0xFFB6FA00, 0xFFB6FB55, 0xFFB6FCAA, 0xFFB6FEFF,
    0xFFC9FF00, 0xFFC9FF55, 0xFFC9FFAA, 0xFFC9FFFF, 0xFFDBFF00, 0xFFDBFF55, 0xFFDBFFAA, 0xFFDBFFFF,
    0xFFEDFF00, 0xFFEDFF55, 0xFFEDFFAA, 0xFFEDFFFF, 0xFFFFFF00, 0xFFFFFF55, 0xFFFFFFAA, 0xFFFFFFFF
};

static quint8 nearestCoderGirlClutIndex(QRgb pixel)
{
    /*
     * Palette entry 0 is transparent. Preserve transparent PNG pixels there,
     * but never choose it accidentally for an opaque black pixel.
     */
    if (qAlpha(pixel) < 128) {
        return 0u;
    }

    const int r = qRed(pixel);
    const int g = qGreen(pixel);
    const int b = qBlue(pixel);

    quint8 bestIndex = 1u;
    quint32 bestDistance = 0xffffffffu;

    for (int i = 1; i < 256; ++i) {
        const QRgb candidate =
            static_cast<QRgb>(
                kCoderGirlClut[i]);

        const int dr = r - qRed(candidate);
        const int dg = g - qGreen(candidate);
        const int db = b - qBlue(candidate);

        const quint32 distance =
            static_cast<quint32>(
                dr * dr
                + dg * dg
                + db * db);

        if (distance < bestDistance) {
            bestDistance = distance;
            bestIndex = static_cast<quint8>(i);

            if (distance == 0u) {
                break;
            }
        }
    }

    return bestIndex;
}

static QByteArray convertImageToCoderGirlIndices(const QImage &source)
{
    if (source.isNull()) {
        return {};
    }

    const QImage image =
        source.convertToFormat(
            QImage::Format_ARGB32);

    const qsizetype pixelCount =
        static_cast<qsizetype>(image.width())
        * static_cast<qsizetype>(image.height());

    if (pixelCount <= 0) {
        return {};
    }

    QByteArray indexed;
    indexed.resize(pixelCount);

    /*
     * PNGs often contain large runs/repeated colours. Cache exact source RGBAs
     * so a 480x320 import does not perform 256 palette-distance tests for every
     * single pixel.
     */
    QHash<quint32, quint8> cache;
    cache.reserve(1024);

    qsizetype out = 0;

    for (int y = 0; y < image.height(); ++y) {
        const QRgb *row =
            reinterpret_cast<const QRgb *>(
                image.constScanLine(y));

        for (int x = 0; x < image.width(); ++x) {
            const quint32 colour =
                static_cast<quint32>(
                    row[x]);

            auto it = cache.constFind(colour);
            quint8 index = 0u;

            if (it == cache.constEnd()) {
                index =
                    nearestCoderGirlClutIndex(
                        row[x]);

                cache.insert(
                    colour,
                    index);
            } else {
                index = it.value();
            }

            indexed[out++] =
                static_cast<char>(index);
        }
    }

    return indexed;
}

/*
 * CoderGirl's actual 8x8 system glyphs. The firmware renderer stretches every
 * source glyph row to two physical rows, producing the familiar 8x16
 * Amiga/Topaz-style text used by the Sidbox GUI.
 */
static const quint8 kCoderGirlSystemFont[256][8] = {
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // (  0)   0x00
    { 0x3C, 0x42, 0x95, 0xA1, 0xA1, 0x95, 0x42, 0x3C },   // (  1)   0x01
    { 0x10, 0x30, 0x60, 0x30, 0x18, 0x0C, 0x06, 0x02 },   // (  2)   0x02
    { 0x30, 0x68, 0xF5, 0xFD, 0xFE, 0xFC, 0x78, 0x30 },   // (  3)   0x03
    { 0x7E, 0x7F, 0x7F, 0x7F, 0x7F, 0x7E, 0x00, 0x00 },   // (  4)   0x04
    { 0x00, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00 },   // (  5)   0x05
    { 0x1C, 0x22, 0x22, 0x1C, 0x1C, 0x22, 0x22, 0x1C },   // (  6)   0x06
    { 0x00, 0x81, 0x81, 0x7E, 0x81, 0x81, 0x00, 0x00 },   // (  7)   0x07
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // (  8)   0x08
    { 0x00, 0x04, 0x0A, 0x04, 0x00, 0x00, 0x00, 0x00 },   // (  9)   0x09
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // ( 10)   0x0A
    { 0x00, 0x30, 0x48, 0x4A, 0x36, 0x0E, 0x00, 0x00 },   // ( 11)   0x0B
    { 0x00, 0x06, 0x29, 0x79, 0x29, 0x06, 0x00, 0x00 },   // ( 12)   0x0C
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // ( 13)   0x0D
    { 0x00, 0x60, 0x7E, 0x0A, 0x35, 0x3F, 0x00, 0x00 },   // ( 14)   0x0E
    { 0x00, 0x2A, 0x1C, 0x36, 0x1C, 0x2A, 0x00, 0x00 },   // ( 15)   0x0F
    { 0x00, 0x00, 0x7F, 0x3E, 0x1C, 0x08, 0x00, 0x00 },   // ( 16)   0x10
    { 0x00, 0x08, 0x1C, 0x3E, 0x7F, 0x00, 0x00, 0x00 },   // ( 17)   0x11
    { 0x00, 0x14, 0x36, 0x7F, 0x36, 0x14, 0x00, 0x00 },   // ( 18)   0x12
    { 0x00, 0x00, 0x5F, 0x00, 0x5F, 0x00, 0x00, 0x00 },   // ( 19)   0x13
    { 0x00, 0x06, 0x09, 0x7F, 0x01, 0x7F, 0x00, 0x00 },   // ( 20)   0x14
    { 0x00, 0x22, 0x4D, 0x55, 0x59, 0x22, 0x00, 0x00 },   // ( 21)   0x15
    { 0x00, 0x60, 0x60, 0x60, 0x60, 0x00, 0x00, 0x00 },   // ( 22)   0x16
    { 0x00, 0x14, 0xB6, 0xFF, 0xB6, 0x14, 0x00, 0x00 },   // ( 23)   0x17
    { 0x00, 0x04, 0x06, 0x3F, 0x06, 0x04, 0x00, 0x00 },   // ( 24)   0x18
    { 0x00, 0x10, 0x30, 0x7E, 0x30, 0x10, 0x00, 0x00 },   // ( 25)   0x19
    { 0x00, 0x08, 0x08, 0x3E, 0x1C, 0x08, 0x00, 0x00 },   // ( 26)   0x1A
    { 0x00, 0x08, 0x1C, 0x3E, 0x08, 0x08, 0x00, 0x00 },   // ( 27)   0x1B
    { 0x00, 0x78, 0x40, 0x40, 0x40, 0x40, 0x00, 0x00 },   // ( 28)   0x1C
    { 0x00, 0x08, 0x3E, 0x08, 0x3E, 0x08, 0x00, 0x00 },   // ( 29)   0x1D
    { 0x00, 0x30, 0x3C, 0x3F, 0x3C, 0x30, 0x00, 0x00 },   // ( 30)   0x1E
    { 0x00, 0x03, 0x0F, 0x3F, 0x0F, 0x03, 0x00, 0x00 },   // ( 31)   0x1F
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // ( 32)  [SPACE]
    { 0x00, 0x00, 0x00, 0x5F, 0x5F, 0x00, 0x00, 0x00 },   // ( 33)  [ ! ]
    { 0x00, 0x03, 0x03, 0x00, 0x03, 0x03, 0x00, 0x00 },   // ( 34)  [ " ]
    { 0x14, 0x7F, 0x7F, 0x14, 0x7F, 0x7F, 0x14, 0x00 },   // ( 35)  [ # ]
    { 0x00, 0x24, 0x2E, 0x6B, 0x6B, 0x3A, 0x12, 0x00 },   // ( 36)  [ $ ]
    { 0x4C, 0x6A, 0x36, 0x18, 0x6C, 0x56, 0x32, 0x00 },   // ( 37)  [ % ]
    { 0x30, 0x7E, 0x4F, 0x59, 0x77, 0x3A, 0x68, 0x40 },   // ( 38)  [ & ]
    { 0x00, 0x00, 0x04, 0x07, 0x03, 0x00, 0x00, 0x00 },   // ( 39)  [ ' ]
    { 0x00, 0x00, 0x1C, 0x3E, 0x63, 0x41, 0x00, 0x00 },   // ( 40)  [ ( ]
    { 0x00, 0x00, 0x41, 0x63, 0x3E, 0x1C, 0x00, 0x00 },   // ( 41)  [ ) ]
    { 0x08, 0x2A, 0x3E, 0x1C, 0x1C, 0x3E, 0x2A, 0x08 },   // ( 42)  [ * ]
    { 0x00, 0x08, 0x08, 0x3E, 0x3E, 0x08, 0x08, 0x00 },   // ( 43)  [ + ]
    { 0x00, 0x00, 0x80, 0xE0, 0x60, 0x00, 0x00, 0x00 },   // ( 44)  [ , ]
    { 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00 },   // ( 45)  [ - ]
    { 0x00, 0x00, 0x00, 0x00, 0x60, 0x60, 0x00, 0x00 },   // ( 46)  [ . ]
    { 0x40, 0x60, 0x30, 0x18, 0x0C, 0x06, 0x03, 0x01 },   // ( 47)  [ / ]
    { 0x00, 0x3E, 0x7F, 0x59, 0x4D, 0x7F, 0x3E, 0x00 },   // ( 48)  [ 0 ]
    { 0x00, 0x04, 0x06, 0x7F, 0x7F, 0x00, 0x00, 0x00 },   // ( 49)  [ 1 ]
    { 0x00, 0x42, 0x63, 0x71, 0x59, 0x4F, 0x46, 0x00 },   // ( 50)  [ 2 ]
    { 0x00, 0x22, 0x63, 0x49, 0x49, 0x7F, 0x36, 0x00 },   // ( 51)  [ 3 ]
    { 0x18, 0x1C, 0x16, 0x13, 0x7F, 0x7F, 0x10, 0x00 },   // ( 52)  [ 4 ]
    { 0x00, 0x27, 0x67, 0x45, 0x45, 0x7D, 0x39, 0x00 },   // ( 53)  [ 5 ]
    { 0x00, 0x3C, 0x7E, 0x4B, 0x49, 0x79, 0x30, 0x00 },   // ( 54)  [ 6 ]
    { 0x00, 0x01, 0x01, 0x71, 0x79, 0x0F, 0x07, 0x00 },   // ( 55)  [ 7 ]
    { 0x00, 0x36, 0x7F, 0x49, 0x49, 0x7F, 0x36, 0x00 },   // ( 56)  [ 8 ]
    { 0x00, 0x06, 0x4F, 0x49, 0x69, 0x3F, 0x1E, 0x00 },   // ( 57)  [ 9 ]
    { 0x00, 0x00, 0x00, 0x66, 0x66, 0x00, 0x00, 0x00 },   // ( 58)  [ : ]
    { 0x00, 0x00, 0x80, 0xE6, 0x66, 0x00, 0x00, 0x00 },   // ( 59)  [ ; ]
    { 0x00, 0x08, 0x08, 0x14, 0x14, 0x22, 0x22, 0x00 },   // ( 60)  [ < ]
    { 0x00, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x00 },   // ( 61)  [ = ]
    { 0x00, 0x22, 0x22, 0x14, 0x14, 0x08, 0x08, 0x00 },   // ( 62)  [ > ]
    { 0x00, 0x02, 0x03, 0x51, 0x59, 0x0F, 0x06, 0x00 },   // ( 63)  [ ? ]
    { 0x3E, 0x7F, 0x41, 0x5D, 0x55, 0x1F, 0x1E, 0x00 },   // ( 64)  [ @ ]
    { 0x00, 0x7E, 0x7F, 0x09, 0x09, 0x7F, 0x7E, 0x00 },   // ( 65)  [ A ]
    { 0x00, 0x7F, 0x7F, 0x49, 0x49, 0x7F, 0x36, 0x00 },   // ( 66)  [ B ]
    { 0x00, 0x1C, 0x3E, 0x63, 0x41, 0x41, 0x41, 0x00 },   // ( 67)  [ C ]
    { 0x00, 0x7F, 0x7F, 0x41, 0x63, 0x3E, 0x1C, 0x00 },   // ( 68)  [ D ]
    { 0x00, 0x7F, 0x7F, 0x49, 0x49, 0x41, 0x41, 0x00 },   // ( 69)  [ E ]
    { 0x00, 0x7F, 0x7F, 0x09, 0x09, 0x01, 0x01, 0x00 },   // ( 70)  [ F ]
    { 0x00, 0x3E, 0x7F, 0x41, 0x49, 0x7B, 0x7A, 0x00 },   // ( 71)  [ G ]
    { 0x00, 0x7F, 0x7F, 0x08, 0x08, 0x7F, 0x7F, 0x00 },   // ( 72)  [ H ]
    { 0x00, 0x00, 0x41, 0x7F, 0x7F, 0x41, 0x00, 0x00 },   // ( 73)  [ I ]
    { 0x00, 0x20, 0x60, 0x40, 0x40, 0x7F, 0x3F, 0x00 },   // ( 74)  [ J ]
    { 0x7F, 0x7F, 0x08, 0x1C, 0x36, 0x63, 0x41, 0x00 },   // ( 75)  [ K ]
    { 0x00, 0x7F, 0x7F, 0x40, 0x40, 0x40, 0x40, 0x00 },   // ( 76)  [ L ]
    { 0x7F, 0x7F, 0x06, 0x0C, 0x06, 0x7F, 0x7F, 0x00 },   // ( 77)  [ M ]
    { 0x7F, 0x7F, 0x06, 0x0C, 0x18, 0x7F, 0x7F, 0x00 },   // ( 78)  [ N ]
    { 0x00, 0x3E, 0x7F, 0x41, 0x41, 0x7F, 0x3E, 0x00 },   // ( 79)  [ O ]
    { 0x00, 0x7F, 0x7F, 0x09, 0x09, 0x0F, 0x06, 0x00 },   // ( 80)  [ P ]
    { 0x3E, 0x7F, 0x41, 0x61, 0x7F, 0x7E, 0x40, 0x00 },   // ( 81)  [ Q ]
    { 0x00, 0x7F, 0x7F, 0x09, 0x19, 0x7F, 0x66, 0x00 },   // ( 82)  [ R ]
    { 0x00, 0x26, 0x6F, 0x4D, 0x59, 0x7B, 0x32, 0x00 },   // ( 83)  [ S ]
    { 0x00, 0x01, 0x01, 0x7F, 0x7F, 0x01, 0x01, 0x00 },   // ( 84)  [ T ]
    { 0x00, 0x3F, 0x7F, 0x40, 0x40, 0x7F, 0x3F, 0x00 },   // ( 85)  [ U ]
    { 0x00, 0x0F, 0x3F, 0x70, 0x70, 0x3F, 0x0F, 0x00 },   // ( 86)  [ V ]
    { 0x7F, 0x7F, 0x30, 0x18, 0x30, 0x7F, 0x7F, 0x00 },   // ( 87)  [ W ]
    { 0x41, 0x63, 0x36, 0x1C, 0x1C, 0x36, 0x63, 0x41 },   // ( 88)  [ X ]
    { 0x01, 0x03, 0x06, 0x7C, 0x7C, 0x06, 0x03, 0x01 },   // ( 89)  [ Y ]
    { 0x61, 0x71, 0x59, 0x4D, 0x47, 0x43, 0x41, 0x00 },   // ( 90)  [ Z ]
    { 0x00, 0x00, 0x7F, 0x7F, 0x41, 0x41, 0x00, 0x00 },   // ( 91)  [ [ ]
    { 0x01, 0x03, 0x06, 0x0C, 0x18, 0x30, 0x60, 0x40 },   // ( 92)  [BACKSLASH]
    { 0x00, 0x00, 0x41, 0x41, 0x7F, 0x7F, 0x00, 0x00 },   // ( 93)  [ ] ]
    { 0x08, 0x0C, 0x06, 0x03, 0x06, 0x0C, 0x08, 0x00 },   // ( 94)  [ ^ ]
    { 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80 },   // ( 95)  [ _ ]
    { 0x00, 0x00, 0x00, 0x03, 0x07, 0x04, 0x00, 0x00 },   // ( 96)  [ ` ]
    { 0x00, 0x20, 0x74, 0x54, 0x54, 0x7C, 0x78, 0x00 },   // ( 97)  [ a ]
    { 0x00, 0x7F, 0x7F, 0x44, 0x44, 0x7C, 0x38, 0x00 },   // ( 98)  [ b ]
    { 0x00, 0x38, 0x7C, 0x44, 0x44, 0x44, 0x00, 0x00 },   // ( 99)  [ c ]
    { 0x00, 0x38, 0x7C, 0x44, 0x44, 0x7F, 0x7F, 0x00 },   // (100)  [ d ]
    { 0x00, 0x38, 0x7C, 0x54, 0x54, 0x5C, 0x18, 0x00 },   // (101)  [ e ]
    { 0x00, 0x04, 0x7E, 0x7F, 0x05, 0x05, 0x00, 0x00 },   // (102)  [ f ]
    { 0x00, 0x18, 0xBC, 0xA4, 0xA4, 0xFC, 0x7C, 0x00 },   // (103)  [ g ]
    { 0x00, 0x7F, 0x7F, 0x04, 0x04, 0x7C, 0x78, 0x00 },   // (104)  [ h ]
    { 0x00, 0x00, 0x00, 0x3D, 0x7D, 0x40, 0x00, 0x00 },   // (105)  [ i ]
    { 0x00, 0x80, 0x80, 0x80, 0xFD, 0x7D, 0x00, 0x00 },   // (106)  [ j ]
    { 0x00, 0x7F, 0x7F, 0x10, 0x38, 0x6C, 0x44, 0x00 },   // (107)  [ k ]
    { 0x00, 0x00, 0x00, 0x3F, 0x7F, 0x40, 0x00, 0x00 },   // (108)  [ l ]
    { 0x7C, 0x7C, 0x0C, 0x18, 0x0C, 0x7C, 0x78, 0x00 },   // (109)  [ m ]
    { 0x00, 0x7C, 0x7C, 0x04, 0x04, 0x7C, 0x78, 0x00 },   // (110)  [ n ]
    { 0x00, 0x38, 0x7C, 0x44, 0x44, 0x7C, 0x38, 0x00 },   // (111)  [ o ]
    { 0x00, 0xFC, 0xFC, 0x24, 0x24, 0x3C, 0x18, 0x00 },   // (112)  [ p ]
    { 0x00, 0x18, 0x3C, 0x24, 0x24, 0xFC, 0xFC, 0x00 },   // (113)  [ q ]
    { 0x00, 0x7C, 0x7C, 0x04, 0x04, 0x0C, 0x08, 0x00 },   // (114)  [ r ]
    { 0x00, 0x48, 0x5C, 0x54, 0x54, 0x74, 0x20, 0x00 },   // (115)  [ s ]
    { 0x00, 0x04, 0x3F, 0x7F, 0x44, 0x44, 0x00, 0x00 },   // (116)  [ t ]
    { 0x00, 0x3C, 0x7C, 0x40, 0x40, 0x7C, 0x7C, 0x00 },   // (117)  [ u ]
    { 0x00, 0x1C, 0x3C, 0x60, 0x60, 0x3C, 0x1C, 0x00 },   // (118)  [ v ]
    { 0x3C, 0x7C, 0x60, 0x30, 0x60, 0x7C, 0x3C, 0x00 },   // (119)  [ w ]
    { 0x44, 0x6C, 0x38, 0x10, 0x38, 0x6C, 0x44, 0x00 },   // (120)  [ x ]
    { 0x00, 0x1C, 0xBC, 0xE0, 0x60, 0x3C, 0x1C, 0x00 },   // (121)  [ y ]
    { 0x00, 0x44, 0x64, 0x74, 0x5C, 0x4C, 0x44, 0x00 },   // (122)  [ z ]
    { 0x00, 0x08, 0x08, 0x3E, 0x77, 0x41, 0x41, 0x00 },   // (123)  [ { ]
    { 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x00, 0x00, 0x00 },   // (124)  [ | ]
    { 0x00, 0x41, 0x41, 0x77, 0x3E, 0x08, 0x08, 0x00 },   // (125)  [ } ]
    { 0x02, 0x01, 0x01, 0x03, 0x02, 0x02, 0x01, 0x00 },   // (126)  [ ~ ]
    { 0x4C, 0x4C, 0x66, 0x66, 0x33, 0x33, 0x19, 0x19 },   // (127)   0x7F
    { 0x00, 0x1E, 0xA1, 0xE1, 0x21, 0x12, 0x00, 0x00 },   // (128)   0x80
    { 0x00, 0x3D, 0x40, 0x20, 0x7D, 0x00, 0x00, 0x00 },   // (129)   0x81
    { 0x00, 0x38, 0x54, 0x54, 0x55, 0x09, 0x00, 0x00 },   // (130)   0x82
    { 0x00, 0x20, 0x55, 0x55, 0x55, 0x78, 0x00, 0x00 },   // (131)   0x83
    { 0x00, 0x20, 0x55, 0x54, 0x55, 0x78, 0x00, 0x00 },   // (132)   0x84
    { 0x00, 0x20, 0x55, 0x55, 0x54, 0x78, 0x00, 0x00 },   // (133)   0x85
    { 0x00, 0x20, 0x57, 0x55, 0x57, 0x78, 0x00, 0x00 },   // (134)   0x86
    { 0x00, 0x1C, 0xA2, 0xE2, 0x22, 0x14, 0x00, 0x00 },   // (135)   0x87
    { 0x00, 0x38, 0x55, 0x55, 0x55, 0x08, 0x00, 0x00 },   // (136)   0x88
    { 0x00, 0x38, 0x55, 0x54, 0x55, 0x08, 0x00, 0x00 },   // (137)   0x89
    { 0x00, 0x38, 0x55, 0x55, 0x54, 0x08, 0x00, 0x00 },   // (138)   0x8A
    { 0x00, 0x00, 0x01, 0x7C, 0x41, 0x00, 0x00, 0x00 },   // (139)   0x8B
    { 0x00, 0x00, 0x01, 0x7D, 0x41, 0x00, 0x00, 0x00 },   // (140)   0x8C
    { 0x00, 0x00, 0x01, 0x7C, 0x40, 0x00, 0x00, 0x00 },   // (141)   0x8D
    { 0x00, 0x70, 0x29, 0x24, 0x29, 0x70, 0x00, 0x00 },   // (142)   0x8E
    { 0x00, 0x78, 0x2F, 0x25, 0x2F, 0x78, 0x00, 0x00 },   // (143)   0x8F
    { 0x00, 0x08, 0x02, 0x10, 0x8A, 0xC1, 0xC1, 0xF2 },   // (144)   0x90
    { 0xF4, 0xF8, 0xF0, 0xF0, 0xC0, 0xC0, 0x80, 0x00 },   // (145)   0x91
    { 0x00, 0x00, 0x00, 0x06, 0x1F, 0x3F, 0x7E, 0x7F },   // (146)   0x92
    { 0xFF, 0xFF, 0xDF, 0x63, 0x7F, 0x3F, 0x1F, 0x06 },   // (147)   0x93
    { 0x00, 0x38, 0x45, 0x44, 0x39, 0x00, 0x00, 0x00 },   // (148)   0x94
    { 0x00, 0x39, 0x45, 0x44, 0x38, 0x00, 0x00, 0x00 },   // (149)   0x95
    { 0x00, 0x3C, 0x41, 0x21, 0x7D, 0x00, 0x00, 0x00 },   // (150)   0x96
    { 0x00, 0x3D, 0x41, 0x20, 0x7C, 0x00, 0x00, 0x00 },   // (151)   0x97
    { 0x00, 0x9C, 0xA1, 0x60, 0x3D, 0x00, 0x00, 0x00 },   // (152)   0x98
    { 0x00, 0x3D, 0x42, 0x42, 0x3D, 0x00, 0x00, 0x00 },   // (153)   0x99
    { 0x00, 0x3C, 0x41, 0x40, 0x3D, 0x00, 0x00, 0x00 },   // (154)   0x9A
    { 0x80, 0x70, 0x68, 0x58, 0x38, 0x04, 0x00, 0x00 },   // (155)   0x9B
    { 0x00, 0x48, 0x7E, 0x49, 0x49, 0x62, 0x00, 0x00 },   // (156)   0x9C
    { 0x00, 0x7E, 0x61, 0x5D, 0x43, 0x3F, 0x00, 0x00 },   // (157)   0x9D
    { 0x00, 0x22, 0x14, 0x08, 0x14, 0x22, 0x00, 0x00 },   // (158)   0x9E
    { 0x00, 0x40, 0x88, 0x7E, 0x09, 0x02, 0x00, 0x00 },   // (159)   0x9F
    { 0x00, 0x20, 0x54, 0x55, 0x55, 0x78, 0x00, 0x00 },   // (160)   0xA0
    { 0x00, 0x00, 0x00, 0x7D, 0x7D, 0x00, 0x00, 0x00 },   // (161)   0xA1
    { 0x00, 0x08, 0x1C, 0x14, 0x3E, 0x3E, 0x14, 0x00 },   // (162)   0xA2
    { 0x00, 0x48, 0x7E, 0x7F, 0x49, 0x43, 0x42, 0x00 },   // (163)   0xA3
    { 0x00, 0x15, 0x0E, 0x0A, 0x0A, 0x0E, 0x15, 0x00 },   // (164)   0xA4
    { 0x01, 0x03, 0x16, 0x7C, 0x7C, 0x16, 0x03, 0x01 },   // (165)   0xA5
    { 0x00, 0x00, 0x00, 0x77, 0x77, 0x00, 0x00, 0x00 },   // (166)   0xA6
    { 0x00, 0x0A, 0x5F, 0x55, 0x55, 0x7D, 0x28, 0x00 },   // (167)   0xA7
    { 0x00, 0x03, 0x03, 0x00, 0x00, 0x03, 0x03, 0x00 },   // (168)   0xA8
    { 0x7E, 0x81, 0x99, 0xA5, 0xA5, 0x81, 0x7E, 0x00 },   // (169)   0xA9
    { 0x00, 0x24, 0x2A, 0x29, 0x29, 0x2F, 0x20, 0x00 },   // (170)   0xAA
    { 0x08, 0x1C, 0x36, 0x22, 0x08, 0x1C, 0x36, 0x22 },   // (171)   0xAB
    { 0x00, 0x00, 0x01, 0x01, 0x01, 0x03, 0x03, 0x00 },   // (172)   0xAC
    { 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00 },   // (173)   0xAD
    { 0x7E, 0x81, 0xBD, 0x95, 0x95, 0xA9, 0x81, 0x7E },   // (174)   0xAE
    { 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00 },   // (175)   0xAF
    { 0x00, 0x02, 0x07, 0x05, 0x05, 0x07, 0x02, 0x00 },   // (176)   0xB0
    { 0x00, 0x44, 0x44, 0x5F, 0x5F, 0x44, 0x44, 0x00 },   // (177)   0xB1
    { 0x00, 0x11, 0x19, 0x1D, 0x17, 0x12, 0x00, 0x00 },   // (178)   0xB2
    { 0x00, 0x11, 0x11, 0x15, 0x1F, 0x0A, 0x00, 0x00 },   // (179)   0xB3
    { 0x00, 0x04, 0x06, 0x03, 0x01, 0x00, 0x00, 0x00 },   // (180)   0xB4
    { 0x00, 0xFC, 0x7C, 0x40, 0x40, 0x7C, 0x7C, 0x40 },   // (181)   0xB5
    { 0x00, 0x06, 0x0F, 0x0F, 0x7F, 0x01, 0x7F, 0x00 },   // (182)   0xB6
    { 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x00, 0x00, 0x00 },   // (183)   0xB7
    { 0x00, 0x00, 0x80, 0xC0, 0x40, 0x00, 0x00, 0x00 },   // (184)   0xB8
    { 0x00, 0x02, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x00 },   // (185)   0xB9
    { 0x00, 0x26, 0x29, 0x29, 0x29, 0x26, 0x00, 0x00 },   // (186)   0xBA
    { 0x22, 0x36, 0x1C, 0x08, 0x22, 0x36, 0x1C, 0x08 },   // (187)   0xBB
    { 0x42, 0x6F, 0x30, 0x18, 0x4C, 0x66, 0xF2, 0x40 },   // (188)   0xBC
    { 0x42, 0x6F, 0x30, 0x18, 0x9C, 0xD6, 0xB2, 0x00 },   // (189)   0xBD
    { 0x11, 0x55, 0x6E, 0x30, 0x18, 0x4C, 0x66, 0xF2 },   // (190)   0xBE
    { 0x42, 0x5A, 0x5A, 0x18, 0x7E, 0x3C, 0x18, 0x00 },   // (191)   0xBF
    { 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x7E, 0x3C, 0x18 },   // (192)   0xC0
    { 0xD8, 0xDC, 0xDE, 0xDF, 0xDF, 0xDE, 0xDC, 0xD8 },   // (193)   0xC1
    { 0xFF, 0xFF, 0x00, 0x18, 0x3C, 0x7E, 0xFF, 0xFF },   // (194)   0xC2
    { 0xFF, 0xFF, 0x7E, 0x3C, 0x18, 0x00, 0xFF, 0xFF },   // (195)   0xC3
    { 0x18, 0x3C, 0x7E, 0xFF, 0xFF, 0x00, 0x00, 0x00 },   // (196)   0xC4
    { 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x7E, 0x3C, 0x18 },   // (197)   0xC5
    { 0x00, 0x20, 0x56, 0x55, 0x56, 0x79, 0x00, 0x00 },   // (198)   0xC6
    { 0x00, 0x70, 0x2A, 0x25, 0x2A, 0x71, 0x00, 0x00 },   // (199)   0xC7
    { 0x1C, 0x22, 0x72, 0xFA, 0x22, 0x22, 0x22, 0x1C },   // (200)   0xC8
    { 0x55, 0x55, 0x55, 0x55, 0x44, 0x5F, 0x4E, 0x44 },   // (201)   0xC9
    { 0x82, 0xBF, 0x82, 0xA8, 0x09, 0x41, 0xFD, 0x41 },   // (202)   0xCA
    { 0x3E, 0x41, 0x41, 0x55, 0x49, 0x55, 0x41, 0x3E },   // (203)   0xCB
    { 0x0E, 0x19, 0x3D, 0x7E, 0x7E, 0x3F, 0x1F, 0x0E },   // (204)   0xCC
    { 0x28, 0x50, 0xA0, 0x50, 0x28, 0x14, 0x0A, 0x04 },   // (205)   0xCD
    { 0xFF, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0xFF },   // (206)   0xCE
    { 0xFF, 0x81, 0x91, 0xA1, 0x91, 0x89, 0x81, 0xFF },   // (207)   0xCF
    { 0x00, 0x30, 0x4E, 0x4A, 0x38, 0x00, 0x00, 0x00 },   // (208)   0xD0
    { 0x00, 0x08, 0x7F, 0x49, 0x41, 0x3E, 0x00, 0x00 },   // (209)   0xD1
    { 0x00, 0x7C, 0x55, 0x55, 0x55, 0x44, 0x00, 0x00 },   // (210)   0xD2
    { 0x00, 0x7C, 0x55, 0x54, 0x55, 0x44, 0x00, 0x00 },   // (211)   0xD3
    { 0x00, 0x7C, 0x55, 0x55, 0x54, 0x44, 0x00, 0x00 },   // (212)   0xD4
    { 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00 },   // (213)   0xD5
    { 0x00, 0x00, 0x44, 0x7D, 0x45, 0x00, 0x00, 0x00 },   // (214)   0xD6
    { 0x00, 0x00, 0x45, 0x7D, 0x45, 0x00, 0x00, 0x00 },   // (215)   0xD7
    { 0x00, 0x00, 0x45, 0x7C, 0x45, 0x00, 0x00, 0x00 },   // (216)   0xD8
    { 0x08, 0x08, 0x08, 0x0F, 0x00, 0x00, 0x00, 0x00 },   // (217)   0xD9
    { 0x00, 0x00, 0x00, 0xF8, 0x08, 0x08, 0x00, 0x00 },   // (218)   0xDA
    { 0x00, 0x7E, 0x42, 0x42, 0x7E, 0x00, 0x00, 0x00 },   // (219)   0xDB
    { 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0 },   // (220)   0xDC
    { 0x00, 0x00, 0x00, 0x77, 0x00, 0x00, 0x00, 0x00 },   // (221)   0xDD
    { 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x00 },   // (222)   0xDE
    { 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F },   // (223)   0xDF
    { 0x00, 0x3C, 0x42, 0x43, 0x3D, 0x00, 0x00, 0x00 },   // (224)   0xE0
    { 0x00, 0xFE, 0x4A, 0x4A, 0x4A, 0x34, 0x00, 0x00 },   // (225)   0xE1
    { 0x00, 0x32, 0x49, 0x49, 0x32, 0x00, 0x00, 0x00 },   // (226)   0xE2
    { 0x00, 0x31, 0x4B, 0x4A, 0x30, 0x00, 0x00, 0x00 },   // (227)   0xE3
    { 0x00, 0x32, 0x49, 0x4A, 0x31, 0x00, 0x00, 0x00 },   // (228)   0xE4
    { 0x00, 0x32, 0x49, 0x4A, 0x31, 0x00, 0x00, 0x00 },   // (229)   0xE5
    { 0x00, 0xFC, 0x20, 0x20, 0x1C, 0x00, 0x00, 0x00 },   // (230)   0xE6
    { 0x00, 0xFE, 0xAA, 0x28, 0x10, 0x00, 0x00, 0x00 },   // (231)   0xE7
    { 0x00, 0xFF, 0xA5, 0x24, 0x18, 0x00, 0x00, 0x00 },   // (232)   0xE8
    { 0x00, 0x3C, 0x40, 0x41, 0x3D, 0x00, 0x00, 0x00 },   // (233)   0xE9
    { 0x00, 0x3C, 0x41, 0x41, 0x3D, 0x00, 0x00, 0x00 },   // (234)   0xEA
    { 0x00, 0x3D, 0x41, 0x40, 0x3C, 0x00, 0x00, 0x00 },   // (235)   0xEB
    { 0x00, 0x9C, 0xA0, 0x61, 0x3D, 0x00, 0x00, 0x00 },   // (236)   0xEC
    { 0x00, 0x04, 0x08, 0x71, 0x09, 0x04, 0x00, 0x00 },   // (237)   0xED
    { 0x00, 0x00, 0x02, 0x02, 0x02, 0x00, 0x00, 0x00 },   // (238)   0xEE
    { 0x00, 0x00, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00 },   // (239)   0xEF
    { 0x00, 0x00, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00 },   // (240)   0xF0
    { 0x00, 0x00, 0x24, 0x2E, 0x24, 0x00, 0x00, 0x00 },   // (241)   0xF1
    { 0x00, 0x24, 0x24, 0x24, 0x24, 0x24, 0x00, 0x00 },   // (242)   0xF2
    { 0x05, 0x17, 0x0A, 0x34, 0x2A, 0x78, 0x00, 0x00 },   // (243)   0xF3
    { 0x00, 0x06, 0x09, 0x7F, 0x01, 0x7F, 0x00, 0x00 },   // (244)   0xF4
    { 0x00, 0x22, 0x4D, 0x55, 0x59, 0x22, 0x00, 0x00 },   // (245)   0xF5
    { 0x00, 0x08, 0x08, 0x2A, 0x08, 0x08, 0x00, 0x00 },   // (246)   0xF6
    { 0x00, 0x00, 0x08, 0x18, 0x18, 0x00, 0x00, 0x00 },   // (247)   0xF7
    { 0x00, 0x06, 0x09, 0x09, 0x06, 0x00, 0x00, 0x00 },   // (248)   0xF8
    { 0xF1, 0x11, 0x11, 0x11, 0x1F, 0x11, 0x11, 0x11 },   // (249)   0xF9
    { 0x08, 0x30, 0xC8, 0x47, 0x40, 0x40, 0x30, 0x08 },   // (250)   0xFA
    { 0xC3, 0xE7, 0x7E, 0x3C, 0x3C, 0x7E, 0xE7, 0xC3 },   // (251)   0xFB
    { 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0xF7, 0xF7, 0xF7 },   // (252)   0xFC
    { 0xF4, 0xF4, 0xF7, 0xF8, 0xFF, 0xFF, 0xBE, 0xFC },   // (253)   0xFD
    { 0x00, 0x1C, 0x1C, 0x1C, 0x00, 0x00, 0x00, 0x00 },   // (254)   0xFE
    { 0x30, 0x0E, 0x00, 0x7E, 0x00, 0x0E, 0x30, 0x40 }   // (255)   0xFF
};

QColor coderGirlPen(int pen)
{
    const int index =
        qBound(
            0,
            pen,
            255);

    return QColor::fromRgba(
        kCoderGirlClut[index]);
}

void drawCoderGirlText(
    QPainter &p,
    int x,
    int y,
    const QString &text,
    const QColor &colour)
{
    const QByteArray bytes =
        text.toLatin1();

    const int startX = x;

    for (int i = 0;
         i < bytes.size();
         ++i) {
        const unsigned char ch =
            static_cast<unsigned char>(
                bytes.at(i));

        if (ch == '\n') {
            x = startX;
            y += 16;
            continue;
        }

        const quint8 *glyph =
            kCoderGirlSystemFont[ch];

        for (int column = 0;
             column < 8;
             ++column) {
            quint8 bits =
                glyph[column];

            for (int row = 0;
                 row < 8;
                 ++row) {
                if (bits
                    & (1u << row)) {
                    p.fillRect(
                        x + column,
                        y + row * 2,
                        1,
                        2,
                        colour);
                }
            }
        }

        x += 8;
    }
}

int coderGirlTextWidth(
    const QString &text)
{
    const int newline =
        text.indexOf(
            QLatin1Char('\n'));

    const QString firstLine =
        newline >= 0
            ? text.left(newline)
            : text;

    return firstLine.toLatin1().size()
        * 8;
}

bool designerWindowFlag(
    const QString &flags,
    const QString &flag)
{
    const bool defaults =
        flags.contains(
            QStringLiteral(
                "SBX_WIN_DEFAULT"));

    if (defaults) {
        static const QStringList defaultFlags = {
            QStringLiteral("SBX_WF_VISIBLE"),
            QStringLiteral("SBX_WF_CLOSE"),
            QStringLiteral("SBX_WF_TITLE_BAR"),
            QStringLiteral("SBX_WF_ZORDER"),
            QStringLiteral("SBX_WF_MINIMISE"),
            QStringLiteral("SBX_WF_MAXRESTORE"),
            QStringLiteral("SBX_WF_SCREENBOUND"),
            QStringLiteral("SBX_WF_MOVEABLE"),
            QStringLiteral("SBX_WF_RESIZABLE")
        };

        if (defaultFlags.contains(flag)) {
            return true;
        }
    }

    return flags.contains(flag);
}

void drawCoderGirlBevel(
    QPainter &p,
    const QRect &rect,
    bool pressed)
{
    if (rect.width() <= 0
        || rect.height() <= 0) {
        return;
    }

    const QColor high =
        coderGirlPen(
            pressed
                ? 16
                : 2);

    const QColor low =
        coderGirlPen(
            pressed
                ? 2
                : 16);

    p.setPen(high);
    p.drawLine(
        rect.left(),
        rect.top(),
        rect.right(),
        rect.top());
    p.drawLine(
        rect.left(),
        rect.top(),
        rect.left(),
        rect.bottom());

    p.setPen(low);

    if (rect.width() > 1) {
        p.drawLine(
            rect.left(),
            rect.bottom(),
            rect.right() - 1,
            rect.bottom());
    }

    p.drawLine(
        rect.right(),
        rect.top(),
        rect.right(),
        rect.bottom());
}

void drawCoderGirlTitleButton(
    QPainter &p,
    const QRect &rect,
    int fillPen)
{
    p.fillRect(
        rect,
        coderGirlPen(fillPen));

    drawCoderGirlBevel(
        p,
        rect,
        false);
}

void drawCoderGirlCloseGlyph(
    QPainter &p,
    const QRect &rect)
{
    const int bx =
        rect.x() + 6;
    const int by =
        rect.y() + 6;
    const int bw =
        rect.width() - 12;
    const int bh =
        rect.height() - 12;

    if (bw <= 0 || bh <= 0) {
        return;
    }

    p.setPen(
        coderGirlPen(16));
    p.drawLine(
        bx,
        by,
        bx,
        by + bh - 1);
    p.drawLine(
        bx,
        by,
        bx + bw - 1,
        by);

    p.setPen(
        coderGirlPen(2));
    p.drawLine(
        bx + 1,
        by + bh - 1,
        bx + bw,
        by + bh - 1);
    p.drawLine(
        bx + bw,
        by,
        bx + bw,
        by + bh - 1);
}

void drawCoderGirlMinimiseGlyph(
    QPainter &p,
    const QRect &rect)
{
    p.setPen(
        coderGirlPen(16));

    p.drawLine(
        rect.x() + 6,
        rect.y() + rect.height() - 5,
        rect.x() + rect.width() - 7,
        rect.y() + rect.height() - 5);
}

void drawCoderGirlMaxGlyph(
    QPainter &p,
    const QRect &rect)
{
    const int bx =
        rect.x() + 5;
    const int by =
        rect.y() + 5;
    const int bw =
        rect.width() - 10;
    const int bh =
        rect.height() - 10;

    p.setPen(
        coderGirlPen(16));

    p.drawLine(
        bx,
        by,
        bx + bw - 1,
        by);
    p.drawLine(
        bx,
        by + 1,
        bx + bw - 1,
        by + 1);
    p.drawLine(
        bx,
        by + bh - 1,
        bx + bw - 1,
        by + bh - 1);
    p.drawLine(
        bx,
        by,
        bx,
        by + bh - 1);
    p.drawLine(
        bx + bw - 1,
        by,
        bx + bw - 1,
        by + bh - 1);
}

void drawCoderGirlZOrderGlyph(
    QPainter &p,
    const QRect &rect)
{
    const int ix =
        rect.x() + 5;
    const int iy =
        rect.y() + 5;
    const int iw =
        rect.width() - 10;

    p.setPen(
        coderGirlPen(16));

    p.drawLine(
        ix,
        iy,
        ix + iw - 1,
        iy);

    if (iw > 2) {
        p.drawLine(
            ix + 2,
            iy + 3,
            ix + iw - 1,
            iy + 3);
    }

    if (iw > 4) {
        p.drawLine(
            ix + 4,
            iy + 6,
            ix + iw - 1,
            iy + 6);
    }
}

void drawCoderGirlResizeGlyph(
    QPainter &p,
    const QRect &rect)
{
    /*
     * Exact non-zero pixels from firmware glyph_resize[].
     * CoderGirl stores its 16x16 glyph column-major.
     */
    const int x =
        rect.x();

    const int y =
        rect.y();

    p.setPen(
        coderGirlPen(16));

    for (int i = 0;
         i < 7;
         ++i) {
        p.drawPoint(
            x + 8 + i,
            y + 14 - i);
    }

    p.setPen(
        coderGirlPen(2));

    p.drawLine(
        x + 15,
        y + 8,
        x + 15,
        y + 15);

    p.drawLine(
        x + 8,
        y + 15,
        x + 15,
        y + 15);
}



QString safeCIdentifier(QString text, const QString &fallback)
{
    text = text.trimmed();
    if (text.isEmpty()) {
        text = fallback;
    }

    QString out;
    out.reserve(text.size() + 1);

    for (int i = 0; i < text.size(); ++i) {
        const QChar ch = text.at(i);
        if (ch.isLetterOrNumber() || ch == QLatin1Char('_')) {
            out += ch;
        } else {
            out += QLatin1Char('_');
        }
    }

    if (out.isEmpty()) {
        out = fallback;
    }

    if (out.at(0).isDigit()) {
        out.prepend(QLatin1Char('_'));
    }

    return out;
}

QString escapedCString(QString text)
{
    text.replace(QStringLiteral("\\"), QStringLiteral("\\\\"));
    text.replace(QStringLiteral("\""), QStringLiteral("\\\""));
    text.replace(QStringLiteral("\n"), QStringLiteral("\\n"));
    text.replace(QStringLiteral("\r"), QStringLiteral("\\r"));
    text.replace(QStringLiteral("\t"), QStringLiteral("\\t"));
    return text;
}


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
        drag->setPixmap(item->icon().pixmap(QSize(64, 24)));
        drag->setHotSpot(QPoint(32, 12));
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

            int x = 0;

            for (const GuiDesignerMenuTitle &menu :
                 std::as_const(*m_menus)) {
                const int width =
                    coderGirlTextWidth(
                        menu.title)
                    + 16;

                drawCoderGirlText(
                    p,
                    x + 8,
                    2,
                    menu.title,
                    coderGirlPen(16));

                x += width;
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

            const QRect gr =
                g.rect.translated(
                    origin);

            drawGadget(
                p,
                g,
                gr,
                m_window->backPen);

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

        }

        } // TabGroup backgrounds, ordinary contents, then non-visual timer icons

        // Always draw selection handles last. In particular the TabGroup
        // frame stays behind its contents, but its resize anchors must not.
        if (m_selected >= 0 && m_selected < m_gadgets->size()
            && visibleOnTab(m_gadgets->at(m_selected))) {
            const GuiDesignerGadget &g = m_gadgets->at(m_selected);
            const QRect gr = g.rect.translated(origin);
                p.setPen(
                    QPen(
                        QColor(
                            255,
                            90,
                            170),
                        1,
                        Qt::DashLine));

                p.setBrush(
                    Qt::NoBrush);

                // Cosmetic only: QRect's right/bottom pixel is inclusive.
                // Keep the selection border 1 logical pixel tighter on
                // those edges; hit testing and handle positions stay intact.
                p.drawRect(
                    gr.adjusted(
                        -2,
                        -2,
                        1,
                        1));

                const QColor anchorColour(
                    255,
                    90,
                    170);

                p.setPen(
                    coderGirlPen(16));

                p.setBrush(
                    anchorColour);

                if (g.type != QStringLiteral("GridSelect")
                    && !isVirtualDesignerGadget(g.type)) {
                    for (const QRect &handle :
                         windowResizeHandles(gr)) {
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

        if (!client.contains(logical)) {
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
            const QRect gadgetRect =
                m_gadgets->at(i)
                    .rect
                    .translated(origin)
                    .intersected(client);

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
            int menuX = 0;
            for (int menuIndex = 0; menuIndex < m_menus->size(); ++menuIndex) {
                const GuiDesignerMenuTitle &title = m_menus->at(menuIndex);
                const int titleWidth = coderGirlTextWidth(title.title) + 16;
                if (logical.x() >= menuX && logical.x() < menuX + titleWidth) {
                    QMenu dropdown(this);
                    for (int itemIndex = 0; itemIndex < title.items.size(); ++itemIndex) {
                        const GuiDesignerMenuItem &item = title.items.at(itemIndex);
                        if (item.text.trimmed() == QStringLiteral("---")
                            || item.flags.contains(QStringLiteral("CG_MENUITEMF_SEPARATOR"))) {
                            dropdown.addSeparator();
                            continue;
                        }
                        QAction *action = dropdown.addAction(item.text);
                        action->setCheckable(item.flags.contains(QStringLiteral("CG_MENUITEMF_TICKABLE")));
                        action->setChecked(item.flags.contains(QStringLiteral("CG_MENUITEMF_TICKED")));
                        connect(action, &QAction::triggered, this,
                                [this, menuIndex, itemIndex]() {
                            if (menuItemActivated)
                                menuItemActivated(menuIndex, itemIndex);
                        });
                    }
                    dropdown.exec(mapToGlobal(QPoint((menuX + 1) * m_zoomPercent / 100,
                                                        21 * m_zoomPercent / 100)));
                    event->accept();
                    return;
                }
                menuX += titleWidth;
            }
        }

        const QPoint origin = clientOrigin();
        const QRect client =
            clientViewportRect();

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

        if (client.contains(logical)) {
            for (int pass = 0; pass < 3 && hit < 0; ++pass) {
            for (int i = m_gadgets->size() - 1;
                 i >= 0;
                 --i) {
                if (!visibleOnTab(m_gadgets->at(i))) continue;
                const QString &type = m_gadgets->at(i).type;
                if (pass == 0 && !isVirtualDesignerGadget(type)) continue;
                if (pass == 1 && (isVirtualDesignerGadget(type) || type == QStringLiteral("TabGroup"))) continue;
                if (pass == 2 && type != QStringLiteral("TabGroup")) continue;
                const QRect gr =
                    m_gadgets->at(i)
                        .rect
                        .translated(origin);

                if (gr.adjusted(-2, -2, 2, 2)
                        .intersected(client)
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
            const QRect gr =
                m_gadgets->at(hit)
                    .rect
                    .translated(origin);

            m_gadgetResizeEdges =
                isVirtualDesignerGadget(m_gadgets->at(hit).type)
                    ? Qt::Edges() : windowResizeEdgesAt(logical, gr);

            m_resizing =
                m_gadgetResizeEdges
                != Qt::Edges();

            m_dragging =
                !m_resizing;

            m_pressLogical =
                logical;

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
        if (!client.contains(logical)) return;
        const QPoint origin = clientOrigin();
        int hit = -1;
        // Preserve an already selected gadget (particularly a TabGroup)
        // when the pointer is inside its bounds, even if children overlap.
        if (m_selected >= 0 && m_selected < m_gadgets->size()
            && visibleOnTab(m_gadgets->at(m_selected))
            && m_gadgets->at(m_selected).rect.translated(origin).contains(logical))
            hit = m_selected;
        if (hit < 0) {
            for (int pass = 0; pass < 2 && hit < 0; ++pass) {
                for (int i = m_gadgets->size() - 1; i >= 0; --i) {
                    const GuiDesignerGadget &g = m_gadgets->at(i);
                    if (!visibleOnTab(g) ||
                        (g.type == QStringLiteral("TabGroup")) != (pass == 1))
                        continue;
                    if (g.rect.translated(origin).contains(logical)) {
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

            // TabGroup is a virtual Canvas bevel plus ordinary Buttons.
            // Its pen colours belong to the bevel, not to the tab buttons.
            p.fillRect(bevel, coderGirlPen(windowBackPen));
            const QColor bevelFPen = coderGirlPen(
                g.fPen >= 0 ? g.fPen : defaultFPenForType(QStringLiteral("Canvas")));
            const QColor bevelBPen = coderGirlPen(
                g.bPen >= 0 ? g.bPen : windowBackPen);
            const bool inset = g.flags.contains(QStringLiteral("GAD_TOOL_INSET"));
            const QColor topLeft = inset ? bevelBPen : bevelFPen;
            const QColor bottomRight = inset ? bevelFPen : bevelBPen;
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

        if (g.type
                == QStringLiteral(
                    "Slider")
            || g.type
                == QStringLiteral(
                    "Scrollbar")) {
            const bool scrollbar =
                g.type == QStringLiteral("Scrollbar");

            p.fillRect(
                r,
                coderGirlPen(1));

            drawCoderGirlBevel(
                p,
                r,
                true);

            QRect track =
                r.adjusted(3, 3, -3, -3);

            p.fillRect(
                track,
                coderGirlPen(6));

            const int minimum =
                qMin(g.minimum, g.maximum);

            const int maximum =
                qMax(g.minimum, g.maximum);

            const qreal ratio =
                qBound(
                    0.0,
                    (g.value - minimum)
                        / qreal(qMax(1, maximum - minimum)),
                    1.0);

            QRect thumb;

            if (g.orientation == 0) {
                const int arrowBand =
                    scrollbar
                        && designerWindowFlag(
                               g.flags,
                               QStringLiteral("GAD_TOOL_SCROLLARROWS"))
                        ? qMin(12, r.height() / 4)
                        : 0;

                track.adjust(0, arrowBand, 0, -arrowBand);

                const int thumbSize =
                    qMin(12, qMax(4, track.height()));

                const int travel =
                    qMax(0, track.height() - thumbSize);

                thumb =
                    QRect(
                        track.x(),
                        track.y() + qRound(travel * ratio),
                        qMax(1, track.width()),
                        thumbSize);
            } else {
                const int arrowBand =
                    scrollbar
                        && designerWindowFlag(
                               g.flags,
                               QStringLiteral("GAD_TOOL_SCROLLARROWS"))
                        ? qMin(12, r.width() / 4)
                        : 0;

                track.adjust(arrowBand, 0, -arrowBand, 0);

                const int thumbSize =
                    qMin(12, qMax(4, track.width()));

                const int travel =
                    qMax(0, track.width() - thumbSize);

                thumb =
                    QRect(
                        track.x() + qRound(travel * ratio),
                        track.y(),
                        thumbSize,
                        qMax(1, track.height()));
            }

            p.fillRect(
                thumb,
                face);

            drawCoderGirlBevel(
                p,
                thumb,
                false);

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

        if (g.type
                == QStringLiteral(
                    "TextBox")
            || g.type
                == QStringLiteral(
                    "TextArea")) {
            p.fillRect(
                r,
                coderGirlPen(1));

            drawCoderGirlBevel(
                p,
                r,
                true);

            drawCoderGirlText(
                p,
                r.x() + 3,
                r.y() + 2,
                g.text,
                text);

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
                        : windowBackPen);

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
                    inset ? bpen : fpen;

                const QColor bottomRight =
                    inset ? fpen : bpen;

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
    int m_gridSnap = 0;
    int m_selected = -1;
    bool m_dragging = false;
    bool m_resizing = false;
    bool m_windowResizing = false;
    bool m_windowDragging = false;
    Qt::Edges m_windowResizeEdges;
    Qt::Edges m_gadgetResizeEdges;
    QPoint m_pressLogical;
    QRect m_startRect;
};

class SidboxGuiDesignerImpl final : public SidboxGuiDesigner
{
public:
    explicit SidboxGuiDesignerImpl(const QString &filePath, QWidget *parent = nullptr)
        : SidboxGuiDesigner(parent)
        , m_filePath(QFileInfo(filePath).absoluteFilePath())
    {
        setProperty("sidboxGuiDesigner", true);
        setProperty("sidboxGuiDesignerPath", m_filePath);

        // Scoped designer theme: match the main IDE without overriding the
        // native checkbox indicators or the custom-painted SIDBOX canvas.
        setStyleSheet(QStringLiteral(R"QSS(
            QToolBar {
                background-color: #101010;
                border: none;
                spacing: 1px;
                padding: 1px;
            }
            QToolButton {
                background-color: #101010;
                color: #ffffff;
                border: none;
                border-radius: 0px;
                padding: 3px;
            }
            QToolButton:hover { background-color: #202020; }
            QToolButton:pressed { background-color: #2858A8; }
            QPushButton {
                background-color: #101010;
                color: #dddddd;
                border: 1px solid #303030;
                border-radius: 0px;
                padding: 4px 8px;
            }
            QPushButton:hover {
                background-color: #202020;
                border: 1px solid #506090;
            }
            QPushButton:pressed {
                background-color: #2858A8;
                color: #ffffff;
            }
            QListWidget, QTreeWidget, QTableWidget {
                background-color: #050505;
                color: #dddddd;
                border: 1px solid #102048;
                border-radius: 0px;
                alternate-background-color: #0b0b0b;
            }
            /* Gadget artwork sits on a medium-grey palette background. */
            QListWidget#coderGirlGadgetPalette {
                background-color: #7B7B7B;
                alternate-background-color: #7B7B7B;
            }
            QTabWidget#coderGirlGadgetPaletteTabs::pane {
                border: 1px solid #303030;
                border-radius: 0px;
                background-color: #7B7B7B;
            }
            QTabWidget#coderGirlGadgetPaletteTabs QTabBar::tab {
                background: #101010;
                color: #dddddd;
                border: 1px solid #303030;
                border-radius: 0px;
                padding: 5px 4px;
                margin-right: 1px;
            }
            QTabWidget#coderGirlGadgetPaletteTabs QTabBar::tab:selected {
                background: #2858A8;
                color: #ffffff;
            }
            QTabWidget#coderGirlGadgetPaletteTabs QTabBar::tab:hover:!selected {
                background: #202020;
            }
            QListWidget::item, QTreeWidget::item, QTableWidget::item {
                border-radius: 0px;
                margin: 0px;
            }
            QListWidget::item:selected, QTreeWidget::item:selected,
            QTableWidget::item:selected {
                background-color: #2858A8;
                color: #ffffff;
                border-radius: 0px;
            }
            QTreeWidget::item:hover:!selected { background-color: #161616; }
            QCheckBox {
                color: #dddddd;
                background-color: transparent;
                spacing: 6px;
            }
            QComboBox, QSpinBox {
                background-color: #101010;
                color: #dddddd;
                border: 1px solid #303030;
                border-radius: 0px;
                padding: 4px;
            }
            QComboBox QAbstractItemView {
                background-color: #050505;
                color: #dddddd;
                selection-background-color: #2858A8;
                selection-color: #ffffff;
            }
            QLineEdit, QPlainTextEdit {
                background-color: #050505;
                color: #dddddd;
                border: 1px solid #303030;
                border-radius: 0px;
                selection-background-color: #2858A8;
                selection-color: #ffffff;
            }
            QSplitter::handle { background-color: #202020; }
            QSplitter::handle:hover { background-color: #2858A8; }
            QMenu {
                background-color: #080808;
                color: #dddddd;
                border: 1px solid #303030;
            }
            QMenu::item { padding: 5px 24px 5px 8px; }
            QMenu::item:selected {
                background-color: #2858A8;
                color: #ffffff;
            }
            QScrollBar:vertical {
                background: #080808;
                width: 12px;
                margin: 0px;
            }
            QScrollBar::handle:vertical {
                background: #303030;
                min-height: 20px;
                border-radius: 0px;
            }
            QScrollBar::handle:vertical:hover { background: #505050; }
            QScrollBar:add-line:vertical, QScrollBar:sub-line:vertical { height: 0px; }
            QScrollBar:horizontal {
                background: #080808;
                height: 12px;
                margin: 0px;
            }
            QScrollBar::handle:horizontal {
                background: #303030;
                min-width: 20px;
                border-radius: 0px;
            }
            QScrollBar::handle:horizontal:hover { background: #505050; }
            QScrollBar:add-line:horizontal, QScrollBar:sub-line:horizontal { width: 0px; }
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
                QStringLiteral("MessageBox"), QStringLiteral("TabGroup"),
                QStringLiteral("Timer")}}
        };
        for (const auto &group : paletteGroups) {
            auto *palette = new GuiDesignerToolbox(m_toolboxTabs);
            palette->setObjectName(QStringLiteral("coderGirlGadgetPalette"));
            QStringList sortedGadgets = group.second;
            sortedGadgets.sort(Qt::CaseInsensitive);
            for (const QString &type : sortedGadgets) {
                // Each palette keeps the original 64x24 artwork, tooltips,
                // drag-out behaviour and double-click to create a gadget.
                const QString resourcePath =
                    QStringLiteral(":/icons/gadget_%1.png").arg(type.toLower());
                QPixmap tile(resourcePath);
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

        // Properties -----------------------------------------------------------
        auto *rightScroll = new QScrollArea(splitter);
        rightScroll->setWidgetResizable(true);
        rightScroll->setMinimumWidth(285);
        m_propertyHost = new QWidget(rightScroll);
        m_propertyLayout = new QFormLayout(m_propertyHost);
        m_propertyLayout->setContentsMargins(8, 8, 8, 8);
        m_propertyLayout->setSpacing(6);
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
        return !regenerate || generateCFile(false);
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
        if (g.type == QStringLiteral("Timer")
            && g.onActivate == QStringLiteral("On_%1_Tick").arg(oldName)) {
            g.onActivate = QStringLiteral("On_%1_Tick").arg(g.name);
        }
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

    void addGadget(const QString &type, const QPoint &dropPosition = QPoint(-1, -1))
    {
        pushUndoSnapshot();

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
        while (m_propertyLayout->rowCount() > 0) {
            m_propertyLayout->removeRow(0);
        }
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
            if (gg.type == QStringLiteral("Timer")
                && gg.onActivate == QStringLiteral("On_%1_Tick").arg(old))
                gg.onActivate = QStringLiteral("On_%1_Tick").arg(gg.name);
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

        QStringList callbackKeys;
        callbackKeys
            << QStringLiteral(
                   "WINDOW_CLOSE");

        QStringList gadgetCallbacks;
        QStringList timerCallbacks;
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

                if (gadgetUsesDirectCallbacks(g)) {
                    directGadgetCallbacks
                        << g.onActivate;
                }
            }

            if (!g.onChange.isEmpty()) {
                callbackKeys << g.onChange;
                gadgetCallbacks << g.onChange;

                if (gadgetUsesDirectCallbacks(g)) {
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

        callbackKeys.removeDuplicates();
        gadgetCallbacks.removeDuplicates();
        timerCallbacks.removeDuplicates();
        dialogCallbackNamesForGeneration.removeDuplicates();
        directGadgetCallbacks.removeDuplicates();
        // Different callback types have incompatible C signatures.
        for (const QString &cb : std::as_const(timerCallbacks)) {
            if (gadgetCallbacks.contains(cb) || menuCallbacks.contains(cb)) {
                QMessageBox::warning(this, QObject::tr("Timer callback collision"),
                    QObject::tr("Timer callback %1 is also used by a gadget or menu. "
                                "Give it a unique name.").arg(cb));
                return false;
            }
        }
        menuCallbacks.removeDuplicates();
        for (const QString &cb : std::as_const(dialogCallbackNamesForGeneration)) {
            if (gadgetCallbacks.contains(cb) || menuCallbacks.contains(cb) || timerCallbacks.contains(cb)) {
                QMessageBox::warning(this, QObject::tr("Dialog callback collision"),
                    QObject::tr("Dialog callback %1 also belongs to another gadget/menu/timer.").arg(cb));
                return false;
            }
        }

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

        QHash<QString, QString> dialogLinkedActions;
        for (const GuiDesignerGadget &g : std::as_const(m_gadgets)) {
            if (g.type != QStringLiteral("Button") || g.dialogTarget.isEmpty()) continue;
            const QString cb = safeCIdentifier(g.onActivate, QStringLiteral("OnActivate"));
            const QString call = safeCIdentifier(g.dialogTarget, QStringLiteral("dialog")) + QStringLiteral("_Show();");
            if ((dialogLinkedActions.contains(cb) && dialogLinkedActions.value(cb) != call)
                || mediaLinkedActions.contains(cb) || linkedCallbacks.contains(cb)) {
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

        s << "#include \"apis.h\"\n"
             "#include <stddef.h>\n"
             "#include <stdint.h>\n"
             "#include <stdlib.h>\n";
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
          << "_is_open = 0u;\n";

        const bool hasDialogs = !dialogNames.isEmpty();
        if (hasDialogs) {
            s << "static CGWindow " << win << "_active_dialog = (CGWindow)0xFFu;\n"
              << "static uint8_t " << win << "_dialog_block_owner = 0u;\n";
        }
        for (const GuiDesignerGadget &g :
             m_gadgets) {
            if (g.type == QStringLiteral("Media") || g.type == QStringLiteral("FileRequester")
                || g.type == QStringLiteral("MessageBox")) continue;
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

        // Generated physical tab header buttons (the TabGroup itself is
        // virtual: a bevel and these ordinary CoderGirl buttons).
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

        for (const QString &cb : std::as_const(timerCallbacks)) {
            s << "static void " << cb << "(void *user);\n";
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
             "\t   The current public applet API does not export window_set_back_colour yet. */\n\n";

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
                      << "\", GAD_TOOL_DEFAULT | GAD_TOOL_TOGGLE);\n";
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

            if (gadgetUsesDirectCallbacks(g)
                && (!g.onActivate.isEmpty()
                    || !g.onChange.isEmpty())) {
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

        // Virtual media components optionally start after all window gadgets exist.
        for (const GuiDesignerGadget &g : std::as_const(m_gadgets)) {
            if (g.type == QStringLiteral("Media") && g.mediaAutoStart)
                s << "\t" << safeCIdentifier(g.name, QStringLiteral("media")) << "_Play();\n";
        }

        // Timers belong to the generated window, but are never GUI gadgets.
        // Allocate AFTER the window and gadgets exist, and free BEFORE close.
        for (const GuiDesignerGadget &g : std::as_const(m_gadgets)) {
            if (g.type != QStringLiteral("Timer")) continue;
            const QString n = safeCIdentifier(g.name, QStringLiteral("timer"));
            s << "\t" << n << " = SBOS_CreateTimer();\n";
            if (g.timerAutoStart && !g.onActivate.trimmed().isEmpty()) {
                s << "\tif (" << n << " != CGTIMER_INVALID) {\n"
                  << "\t\tif (SBOS_TimerSet(" << n << ", "
                  << qBound(1, g.timerDelayMs, 86400000) << "u, "
                  << (g.timerRepeat ? qBound(1, g.timerPeriodMs, 86400000) : 0)
                  << "u, " << g.onActivate << ", NULL) != 0) {\n"
                  << "\t\t\tSBOS_FreeTimer(" << n << ");\n"
                  << "\t\t\t" << n << " = CGTIMER_INVALID;\n"
                  << "\t\t}\n\t}\n";
            }
        }
        s << "}\n\n";

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
            if (isVirtualDesignerGadget(g.type) || gadgetUsesDirectCallbacks(g)) {
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

        const bool hasWindowRoutedMenu =
            m_window.callbackMode == 0
            && !m_menus.isEmpty();

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
            s << "\t\t\t/* Put close-validation/user shutdown code here. */\n";
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

        /*
         * ListBoxes do not own ItemLists_t. Detach and free designer-created
         * models before the Window destroys its gadgets.
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

            s << "\t\t\tAPI->gui->gadgets->listbox_attach_itemlist("
              << n
              << ", NULL);\n";
            s << "\t\t\tAPI->gui->gadgets->itemlist_deinit(&"
              << n
              << "_items);\n";
        }

        // Stop playback and release PCM buffers BEFORE destroying this window.
        for (const GuiDesignerGadget &g : std::as_const(m_gadgets)) {
            if (g.type != QStringLiteral("Media")) continue;
            const QString n = safeCIdentifier(g.name, QStringLiteral("media"));
            if (g.mediaMode == QStringLiteral("SFX"))
                s << "\t\t\t" << n << "_Cleanup();\n";
            else
                s << "\t\t\t" << n << "_Stop();\n";
        }

        // Cooperative timers must not fire into a window after it closes.
        for (const GuiDesignerGadget &g : std::as_const(m_gadgets)) {
            if (g.type != QStringLiteral("Timer")) continue;
            const QString n = safeCIdentifier(g.name, QStringLiteral("timer"));
            s << "\t\t\tif (" << n << " != CGTIMER_INVALID) {\n"
              << "\t\t\t\tSBOS_TimerCancel(" << n << ");\n"
              << "\t\t\t\tSBOS_FreeTimer(" << n << ");\n"
              << "\t\t\t\t" << n << " = CGTIMER_INVALID;\n"
              << "\t\t\t}\n";
        }

        // Mark the window closed before the firmware clears its handle.
        // This also allows the public _Create() function to reopen it later.
        s << "\t\t\t"
          << win
          << "_is_open = 0u;\n"
             "\t\t\tSBOS_CloseWindow(win);\n";
        if (!m_menus.isEmpty()) {
            s << "\t\t\tSBOS_DestroyMenu(&"
              << win
              << "_Menu);\n";
        }
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
                    if (gadgetUsesDirectCallbacks(g)) {
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
                         "\t\t\t    && (cg_menuitem_t)m->b == "
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

        for (const QString &cb : std::as_const(timerCallbacks)) {
            s << "static void " << cb << "(void *user)\n"
                 "{\n\t(void)user;\n"
                 "\t/* <SIDBOX-GUI:USER " << cb << "> */\n";
            const QString body = saved.value(cb);
            if (body.isEmpty()) {
                s << "\t/* TODO: timer tick; keep callbacks cooperative and short. */\n";
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
                if (i % 16 == 0) assets << "    ";
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
    QFormLayout *m_propertyLayout = nullptr;
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
