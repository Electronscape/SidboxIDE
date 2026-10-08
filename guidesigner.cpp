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
#include <QColor>
#include <QComboBox>
#include <QDir>
#include <QDrag>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QFile>
#include <QFileInfo>
#include <QFormLayout>
#include <QHash>
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
#include <QListWidgetItem>
#include <QMessageBox>
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
#include <QPushButton>
#include <QRect>
#include <QRegularExpression>
#include <QSaveFile>
#include <QScrollArea>
#include <QSet>
#include <QSize>
#include <QSpinBox>
#include <QSplitter>
#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QTimer>
#include <QToolBar>
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
    int bitmapWidth = 64;
    int bitmapHeight = 64;

    /*
     * Optional applet C expression for the BitmapView's pixel source.
     * Example: canvas_pixels
     */
    QString bitmapSource;

    /*
     * Designer-side initial ListBox contents.
     *
     * The current public applet API exposes listbox_create(), but not the
     * ItemList attach/add functions yet. Keep these in the .sbui and preview so
     * the design is ready for that API as soon as it is exported.
     */
    QStringList listItems;
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

class GuiDesignerToolbox : public QListWidget
{
public:
    explicit GuiDesignerToolbox(QWidget *parent = nullptr)
        : QListWidget(parent)
    {
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
            item->text().toUtf8());

        auto *drag =
            new QDrag(this);

        drag->setMimeData(mime);
        drag->exec(Qt::CopyAction);
    }
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
        setZoomPercent(150);
    }

    std::function<void(int)> selectionChanged;
    std::function<void()> geometryChangeStarted;
    std::function<void()> geometryCommitted;
    std::function<void(const QString &, const QPoint &)> gadgetDropped;
    std::function<void(int)> gadgetDoubleClicked;
    std::function<void()> copyRequested;
    std::function<void()> pasteRequested;
    std::function<void()> deleteRequested;
    std::function<void(int, int, bool)> nudgeRequested;

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

        for (int i = 0;
             i < m_gadgets->size();
             ++i) {
            const GuiDesignerGadget &g =
                m_gadgets->at(i);

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
                    gr);

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

            if (i == m_selected) {
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

                p.drawRect(
                    gr.adjusted(
                        -2,
                        -2,
                        2,
                        2));

                const QColor anchorColour(
                    255,
                    90,
                    170);

                p.setPen(
                    coderGirlPen(16));

                p.setBrush(
                    anchorColour);

                if (g.type
                    != QStringLiteral(
                        "GridSelect")) {
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

            p.drawRect(
                wr.adjusted(
                    -2,
                    -2,
                    2,
                    2));

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

        QWidget::keyPressEvent(event);
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

        for (int i =
                 static_cast<int>(
                     m_gadgets->size())
                 - 1;
             i >= 0;
             --i) {
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
                   && m_gadgets->at(m_selected).type
                      != QStringLiteral(
                          "GridSelect")) {
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

        int hit = -1;

        if (client.contains(logical)) {
            for (int i = m_gadgets->size() - 1;
                 i >= 0;
                 --i) {
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
                windowResizeEdgesAt(
                    logical,
                    gr);

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
                   && m_gadgets->at(m_selected).type
                      != QStringLiteral(
                          "GridSelect")) {
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

    void mouseReleaseEvent(QMouseEvent *event) override
    {
        if ((m_dragging
             || m_resizing
             || m_windowResizing
             || m_windowDragging)
            && event->button()
               == Qt::LeftButton) {
            m_dragging = false;
            m_resizing = false;
            m_windowResizing = false;
            m_windowDragging = false;
            m_windowResizeEdges = {};
            m_gadgetResizeEdges = {};

            if (geometryCommitted) {
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

        if (g.type
            == QStringLiteral(
                "Label")) {
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

            drawCoderGirlBevel(
                p,
                r,
                true);

            int y =
                r.y() + 2;

            const QStringList rows =
                g.listItems.isEmpty()
                    ? QStringList{
                          QStringLiteral(
                              "(empty list)")
                      }
                    : g.listItems;

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
                    }
                }
            }

            return;
        }

        if (g.type
            == QStringLiteral(
                "Canvas")) {
            p.fillRect(
                r,
                coderGirlPen(
                    windowBackPen));

            drawCoderGirlBevel(
                p,
                r,
                true);

            p.setPen(
                coderGirlPen(3));

            p.drawLine(
                r.topLeft(),
                r.bottomRight());

            p.drawLine(
                r.topRight(),
                r.bottomLeft());

            return;
        }

        if (g.type
            == QStringLiteral(
                "BitmapView")) {
            p.fillRect(
                r,
                coderGirlPen(
                    windowBackPen));

            drawCoderGirlBevel(
                p,
                r,
                true);

            const int cell = 8;

            for (int y = r.top() + 2;
                 y < r.bottom() - 1;
                 y += cell) {
                for (int x = r.left() + 2;
                     x < r.right() - 1;
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
                                    r.right()
                                        - x),
                                qMin(
                                    cell,
                                    r.bottom()
                                        - y)),
                            coderGirlPen(6));
                    }
                }
            }

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
    int m_zoomPercent = 150;
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
        QAction *generate = top->addAction(QObject::tr("Generate C"));
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
            1);

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
        auto *toolLabel = new QLabel(QObject::tr("CoderGirl Gadgets"), left);
        leftLayout->addWidget(toolLabel);

        m_toolbox = new GuiDesignerToolbox(left);
        const QStringList gadgetTypes = {
            QStringLiteral("Button"), QStringLiteral("Label"), QStringLiteral("Checkbox"),
            QStringLiteral("Radio"), QStringLiteral("Slider"), QStringLiteral("ProgressBar"),
            QStringLiteral("TextBox"), QStringLiteral("TextArea"), QStringLiteral("ListBox"),
            QStringLiteral("Scrollbar"), QStringLiteral("GridSelect"), QStringLiteral("Canvas"),
            QStringLiteral("BitmapView")
        };
        m_toolbox->addItems(gadgetTypes);
        leftLayout->addWidget(m_toolbox, 1);

        auto *addButton = new QPushButton(QObject::tr("Add Selected Gadget"), left);
        leftLayout->addWidget(addButton);

        leftLayout->addWidget(new QLabel(QObject::tr("Menus"), left));
        m_menuTree = new QTreeWidget(left);
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

        connect(addButton, &QPushButton::clicked, this, [this]() {
            QListWidgetItem *item = m_toolbox->currentItem();
            if (item) addGadget(item->text());
        });
        connect(m_toolbox, &QListWidget::itemDoubleClicked, this, [this](QListWidgetItem *item) {
            if (item) addGadget(item->text());
        });
        connect(
            m_undoAction,
            &QAction::triggered,
            this,
            [this]() {
                undoLastDesignerChange();
            });

        connect(save, &QAction::triggered, this, [this]() { saveDesignAndGenerate(); });
        connect(generate, &QAction::triggered, this, [this]() { generateCFile(false); });

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

        m_canvas->selectionChanged = [this](int) { rebuildProperties(); };

        m_canvas->gadgetDropped =
            [this](const QString &type,
                   const QPoint &localPosition) {
                addGadget(type, localPosition);
            };

        m_canvas->gadgetDoubleClicked =
            [this](int index) {
                jumpToGadgetSource(index);
            };

        m_canvas->copyRequested =
            [this]() {
                copySelectedGadget();
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
                nudgeSelectedGadget(
                    dx,
                    dy,
                    autoRepeat);
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
        if (!saveDesign()) {
            return false;
        }
        return generateCFile(false);
    }

private:
    void setModified(bool modified)
    {
        if (m_modified == modified) return;
        m_modified = modified;
        if (tabTitleChanged) tabTitleChanged();
    }

    static QRect defaultRectForType(const QString &type, int ordinal)
    {
        const int x = 18 + (ordinal % 5) * 14;
        const int y = 24 + (ordinal % 8) * 18;
        if (type == QStringLiteral("Label")) return QRect(x, y, 120, 18);
        if (type == QStringLiteral("Checkbox") || type == QStringLiteral("Radio")) return QRect(x, y, 130, 20);
        if (type == QStringLiteral("Slider") || type == QStringLiteral("Scrollbar")) return QRect(x, y, 150, 18);
        if (type == QStringLiteral("ProgressBar")) return QRect(x, y, 150, 18);
        if (type == QStringLiteral("TextArea") || type == QStringLiteral("ListBox")) return QRect(x, y, 170, 80);
        if (type == QStringLiteral("GridSelect")) return QRect(x, y, 98, 74);
        if (type == QStringLiteral("Canvas") || type == QStringLiteral("BitmapView")) return QRect(x, y, 120, 80);
        if (type == QStringLiteral("TextBox")) return QRect(x, y, 150, 20);
        return QRect(x, y, 90, 22);
    }

    QString uniqueGadgetName(const QString &type) const
    {
        QString stem;
        if (type == QStringLiteral("Button")) stem = QStringLiteral("btn");
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
        g.callbackRoute = o.value(QStringLiteral("callbackRoute")).toInt(-1);
        g.minimum = o.value(QStringLiteral("minimum")).toInt(0);
        g.maximum = o.value(QStringLiteral("maximum")).toInt(100);
        g.value = o.value(QStringLiteral("value")).toInt(0);
        g.orientation = o.value(QStringLiteral("orientation")).toInt(1);
        g.checked = o.value(QStringLiteral("checked")).toInt(0);
        g.enabled = o.value(QStringLiteral("enabled")).toBool(true);
        g.group = o.value(QStringLiteral("group")).toInt(0);
        g.typeFlags = o.value(QStringLiteral("typeFlags")).toString();
        g.cellWidth = o.value(QStringLiteral("cellWidth")).toInt(24);
        g.cellHeight = o.value(QStringLiteral("cellHeight")).toInt(18);
        g.cellsX = o.value(QStringLiteral("cellsX")).toInt(4);
        g.cellsY = o.value(QStringLiteral("cellsY")).toInt(4);
        g.bitmapWidth = o.value(QStringLiteral("bitmapWidth")).toInt(64);
        g.bitmapHeight = o.value(QStringLiteral("bitmapHeight")).toInt(64);
        g.bitmapSource = o.value(QStringLiteral("bitmapSource")).toString();

        for (const QJsonValue &itemValue :
             o.value(QStringLiteral("listItems")).toArray()) {
            g.listItems.append(itemValue.toString());
        }

        syncGridSelectGeometry(&g);
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

        /*
         * Designer-generated callback names should follow the new gadget name.
         * Explicitly shared/custom callback names are deliberately preserved.
         */
        if (g.onActivate == oldAutoActivate) {
            g.onActivate =
                QStringLiteral("On_%1_Activate")
                    .arg(g.name);
        }

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

        if (newPos == oldPos) {
            return;
        }

        /* One Undo step for one held-arrow movement, not every auto-repeat. */
        if (!autoRepeat) {
            pushUndoSnapshot();
        }

        g.rect.moveTopLeft(newPos);
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
            flags.append(
                QStringLiteral(
                    "GAD_TOOL_INSET"));
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

        for (const QJsonValue &value :
             root.value(
                     QStringLiteral(
                         "gadgets"))
                 .toArray()) {
            const QJsonObject o =
                value.toObject();

            GuiDesignerGadget g;

            g.type =
                o.value(
                     QStringLiteral("type"))
                    .toString();

            g.name =
                o.value(
                     QStringLiteral("name"))
                    .toString();

            g.rect =
                QRect(
                    o.value(
                         QStringLiteral("x"))
                        .toInt(),
                    o.value(
                         QStringLiteral("y"))
                        .toInt(),
                    o.value(
                         QStringLiteral("w"))
                        .toInt(80),
                    o.value(
                         QStringLiteral("h"))
                        .toInt(20));

            g.text =
                o.value(
                     QStringLiteral("text"))
                    .toString();

            g.flags =
                o.value(
                     QStringLiteral("flags"))
                    .toString(
                        QStringLiteral(
                            "GAD_TOOL_DEFAULT"));

            g.bPen =
                o.value(
                     QStringLiteral("bPen"))
                    .toInt(-1);

            g.fPen =
                o.value(
                     QStringLiteral("fPen"))
                    .toInt(-1);

            g.hPen =
                o.value(
                     QStringLiteral("hPen"))
                    .toInt(-1);

            g.onActivate =
                o.value(
                     QStringLiteral(
                         "onActivate"))
                    .toString();

            g.onChange =
                o.value(
                     QStringLiteral(
                         "onChange"))
                    .toString();

            g.callbackRoute =
                o.value(
                     QStringLiteral(
                         "callbackRoute"))
                    .toInt(-1);

            g.minimum =
                o.value(
                     QStringLiteral(
                         "minimum"))
                    .toInt(0);

            g.maximum =
                o.value(
                     QStringLiteral(
                         "maximum"))
                    .toInt(100);

            g.value =
                o.value(
                     QStringLiteral(
                         "value"))
                    .toInt(0);

            g.orientation =
                o.value(
                     QStringLiteral(
                         "orientation"))
                    .toInt(1);

            g.checked =
                o.value(
                     QStringLiteral(
                         "checked"))
                    .toInt(0);

            g.enabled =
                o.value(
                     QStringLiteral(
                         "enabled"))
                    .toBool(true);

            g.group =
                o.value(
                     QStringLiteral(
                         "group"))
                    .toInt(0);

            g.typeFlags =
                o.value(
                     QStringLiteral(
                         "typeFlags"))
                    .toString();

            g.cellWidth =
                o.value(
                     QStringLiteral(
                         "cellWidth"))
                    .toInt(24);

            g.cellHeight =
                o.value(
                     QStringLiteral(
                         "cellHeight"))
                    .toInt(18);

            g.cellsX =
                o.value(
                     QStringLiteral(
                         "cellsX"))
                    .toInt(4);

            g.cellsY =
                o.value(
                     QStringLiteral(
                         "cellsY"))
                    .toInt(4);

            g.bitmapWidth =
                o.value(
                     QStringLiteral(
                         "bitmapWidth"))
                    .toInt(64);

            g.bitmapHeight =
                o.value(
                     QStringLiteral(
                         "bitmapHeight"))
                    .toInt(64);

            g.bitmapSource =
                o.value(
                     QStringLiteral(
                         "bitmapSource"))
                    .toString();

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

            m_gadgets.append(
                g);
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

    void jumpToGadgetSource(
        int index)
    {
        if (index < 0
            || index >= m_gadgets.size()) {
            return;
        }

        if (!generateCFile(false)) {
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
        g.text = (type == QStringLiteral("Button")) ? QStringLiteral("Button")
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
        if (type == QStringLiteral("Checkbox") || type == QStringLiteral("Radio")
            || type == QStringLiteral("Slider") || type == QStringLiteral("Scrollbar")
            || type == QStringLiteral("ListBox") || type == QStringLiteral("GridSelect")
            || type == QStringLiteral("TextBox") || type == QStringLiteral("TextArea")
            || type == QStringLiteral("BitmapView")) {
            g.onChange = QStringLiteral("On_%1_Change").arg(g.name);
        }

        if (type == QStringLiteral("TextBox")) g.typeFlags = QStringLiteral("TB_SINGLELINE");
        if (type == QStringLiteral("TextArea")) g.typeFlags = QStringLiteral("TA_DEFAULT");
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

        m_gadgets.append(g);
        m_canvas->setSelectedIndex(m_gadgets.size() - 1);
        setModified(true);
        m_canvas->update();
    }

    void clearPropertyRows()
    {
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

    QLineEdit *addLine(const QString &label, const QString &value,
                       const std::function<void(const QString &)> &changed)
    {
        auto *edit = new QLineEdit(value, m_propertyHost);
        m_propertyLayout->addRow(label, edit);
        connect(edit, &QLineEdit::editingFinished, this, [this, edit, changed]() {
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

        return g.bitmapSource
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
        GuiDesignerGadget *g)
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
        GuiDesignerGadget *g)
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
                "One ListBox item per line"));

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

    void rebuildProperties()
    {
        clearPropertyRows();
        m_propertyLayout->addRow(new QLabel(QStringLiteral("<b>%1</b>")
            .arg(m_canvas->selectedIndex() < 0 ? QObject::tr("Window") : QObject::tr("Gadget")), m_propertyHost));

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

            addSpin(QObject::tr("Back Pen"), m_window.backPen, 0, 255, [this](int v) { m_window.backPen = v; });
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
            if (gg.onChange == QStringLiteral("On_%1_Change").arg(old))
                gg.onChange = QStringLiteral("On_%1_Change").arg(gg.name);
        });
        auto *type = new QLabel(g.type, m_propertyHost);
        m_propertyLayout->addRow(QObject::tr("Type"), type);
        addSpin(QObject::tr("X"), g.rect.x(), 0, 2000, [this, selected](int v) { m_gadgets[selected].rect.moveLeft(v); });
        addSpin(QObject::tr("Y"), g.rect.y(), 0, 2000, [this, selected](int v) { m_gadgets[selected].rect.moveTop(v); });

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
            addLine(QObject::tr("Text"), g.text, [this, selected](const QString &v) { m_gadgets[selected].text = v; });
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

        addFlagList(
            QObject::tr("Gadget flags"),
            g.flags,
            gadgetFlagChoices(g.type),
            [this, selected](const QString &v) {
                if (selected >= 0
                    && selected < m_gadgets.size()) {
                    m_gadgets[selected].flags =
                        v;

                    syncGridSelectGeometry(
                        &m_gadgets[selected]);

                    syncDesignerDemoBitmapSize(
                        &m_gadgets[selected]);
                }
            });
        addSpin(QObject::tr("BPen (-1 default)"), g.bPen, -1, 255, [this, selected](int v) { m_gadgets[selected].bPen = v; });
        addSpin(QObject::tr("FPen (-1 default)"), g.fPen, -1, 255, [this, selected](int v) { m_gadgets[selected].fPen = v; });
        addSpin(QObject::tr("HPen (-1 default)"), g.hPen, -1, 255, [this, selected](int v) { m_gadgets[selected].hPen = v; });

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
                    QStringLiteral("CNV_RECTF")
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
                    syncGridSelectGeometry(
                        &m_gadgets[selected]);

                    QTimer::singleShot(
                        0,
                        this,
                        [this]() {
                            rebuildProperties();
                        });
                });
        }
        if (g.type == QStringLiteral("BitmapView")) {
            addSpin(QObject::tr("Bitmap width"), g.bitmapWidth, 1, 32767, [this, selected](int v) { m_gadgets[selected].bitmapWidth = v; });
            addSpin(QObject::tr("Bitmap height"), g.bitmapHeight, 1, 32767, [this, selected](int v) { m_gadgets[selected].bitmapHeight = v; });
            addLine(
                QObject::tr("Bitmap source"),
                g.bitmapSource,
                [this, selected](const QString &v) {
                    m_gadgets[selected].bitmapSource = v.trimmed();
                });
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
            g.bPen=o.value(QStringLiteral("bPen")).toInt(-1); g.fPen=o.value(QStringLiteral("fPen")).toInt(-1); g.hPen=o.value(QStringLiteral("hPen")).toInt(-1);
            g.onActivate=o.value(QStringLiteral("onActivate")).toString(); g.onChange=o.value(QStringLiteral("onChange")).toString();
            g.callbackRoute=o.value(QStringLiteral("callbackRoute")).toInt(-1);
            g.minimum=o.value(QStringLiteral("minimum")).toInt(0); g.maximum=o.value(QStringLiteral("maximum")).toInt(100); g.value=o.value(QStringLiteral("value")).toInt(0);
            g.orientation=o.value(QStringLiteral("orientation")).toInt(1); g.checked=o.value(QStringLiteral("checked")).toInt(0); g.enabled=o.value(QStringLiteral("enabled")).toBool(true); g.group=o.value(QStringLiteral("group")).toInt(0);
            g.typeFlags=o.value(QStringLiteral("typeFlags")).toString();
            g.cellWidth=o.value(QStringLiteral("cellWidth")).toInt(24); g.cellHeight=o.value(QStringLiteral("cellHeight")).toInt(18);
            g.cellsX=o.value(QStringLiteral("cellsX")).toInt(4); g.cellsY=o.value(QStringLiteral("cellsY")).toInt(4);
            g.bitmapWidth=o.value(QStringLiteral("bitmapWidth")).toInt(64); g.bitmapHeight=o.value(QStringLiteral("bitmapHeight")).toInt(64);
            g.bitmapSource =
                o.value(QStringLiteral("bitmapSource"))
                    .toString();

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
        o.insert(QStringLiteral("onActivate"),g.onActivate); o.insert(QStringLiteral("onChange"),g.onChange); o.insert(QStringLiteral("callbackRoute"),g.callbackRoute); o.insert(QStringLiteral("minimum"),g.minimum); o.insert(QStringLiteral("maximum"),g.maximum); o.insert(QStringLiteral("value"),g.value);
        o.insert(QStringLiteral("orientation"),g.orientation); o.insert(QStringLiteral("checked"),g.checked); o.insert(QStringLiteral("enabled"),g.enabled); o.insert(QStringLiteral("group"),g.group); o.insert(QStringLiteral("typeFlags"),g.typeFlags);
        o.insert(QStringLiteral("cellWidth"),g.cellWidth); o.insert(QStringLiteral("cellHeight"),g.cellHeight); o.insert(QStringLiteral("cellsX"),g.cellsX); o.insert(QStringLiteral("cellsY"),g.cellsY);
        o.insert(QStringLiteral("bitmapWidth"),g.bitmapWidth); o.insert(QStringLiteral("bitmapHeight"),g.bitmapHeight);
        o.insert(QStringLiteral("bitmapSource"), g.bitmapSource);

        QJsonArray listItems;
        for (const QString &item : g.listItems) {
            listItems.append(item);
        }
        o.insert(QStringLiteral("listItems"), listItems);

        return o;
    }

    bool saveDesign()
    {
        QJsonObject w; w.insert(QStringLiteral("name"),m_window.name); w.insert(QStringLiteral("title"),m_window.title); w.insert(QStringLiteral("flags"),m_window.flags); w.insert(QStringLiteral("backPen"),m_window.backPen); w.insert(QStringLiteral("callbackMode"),m_window.callbackMode);
        w.insert(QStringLiteral("x"),m_window.rect.x()); w.insert(QStringLiteral("y"),m_window.rect.y()); w.insert(QStringLiteral("w"),m_window.rect.width()); w.insert(QStringLiteral("h"),m_window.rect.height());
        QJsonArray gadgets; for (const GuiDesignerGadget &g : std::as_const(m_gadgets)) gadgets.append(gadgetToJson(g));
        QJsonArray menus; for (const GuiDesignerMenuTitle &menu : std::as_const(m_menus)) { QJsonObject mo; mo.insert(QStringLiteral("title"),menu.title); QJsonArray items; for (const GuiDesignerMenuItem &item : menu.items) { QJsonObject io; io.insert(QStringLiteral("name"),item.name); io.insert(QStringLiteral("text"),item.text); io.insert(QStringLiteral("callback"),item.callback); io.insert(QStringLiteral("flags"),item.flags); items.append(io); } mo.insert(QStringLiteral("items"),items); menus.append(mo); }
        QJsonObject root; root.insert(QStringLiteral("format"),QStringLiteral("SidboxGUI")); root.insert(QStringLiteral("version"),6); root.insert(QStringLiteral("screenWidth"),480); root.insert(QStringLiteral("screenHeight"),320); root.insert(QStringLiteral("designerGridSnap"),m_canvas ? m_canvas->gridSnap() : 0); root.insert(QStringLiteral("window"),w); root.insert(QStringLiteral("gadgets"),gadgets); root.insert(QStringLiteral("menus"),menus);
        QSaveFile file(m_filePath); if (!file.open(QIODevice::WriteOnly|QIODevice::Text)) { QMessageBox::warning(this,QObject::tr("GUI Designer"),QObject::tr("Could not save %1").arg(QDir::toNativeSeparators(m_filePath))); return false; }
        file.write(QJsonDocument(root).toJson(QJsonDocument::Indented)); if (!file.commit()) return false;
        setModified(false); return true;
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

            result.insert(key, oldSource.mid(contentStart, end - contentStart).trimmed());
            searchFrom = end + endMarker.size();
        }

        return result;
    }

    QString generatedCPath() const
    {
        QFileInfo info(m_filePath); return info.dir().filePath(info.completeBaseName() + QStringLiteral(".c"));
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

    bool generateCFile(bool showMessage)
    {
        const QString cPath =
            generatedCPath();

        QString oldSource;

        if (beforeGenerate
            && !beforeGenerate(cPath)) {
            return false;
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
        QStringList directGadgetCallbacks;
        QStringList menuCallbacks;

        for (const GuiDesignerGadget &g :
             std::as_const(m_gadgets)) {
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
        directGadgetCallbacks.removeDuplicates();
        menuCallbacks.removeDuplicates();

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

        QString out;
        QTextStream s(&out);

        s << "/* AUTO-GENERATED by Sidbox IDE GUI Designer.\n"
             "   Target: SIDBOX applet API (apis.h), not firmware-private CoderGirl headers.\n"
             "   Edit USER blocks only; designer regeneration replaces generated sections. */\n\n";

        s << "#include \"apis.h\"\n"
             "#include <stddef.h>\n"
             "#include <stdint.h>\n\n";

        /*
         * Application GUI handles are deliberately file-local. The real applet
         * examples also keep Window/Gadget/Menu state static.
         */
        s << "static CGWindow "
          << win
          << ";\n";

        for (const GuiDesignerGadget &g :
             m_gadgets) {
            s << "static CGGadget "
              << safeCIdentifier(
                     g.name,
                     QStringLiteral(
                         "gadget"))
              << ";\n";
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

            const QString source =
                safeCIdentifier(
                    g.bitmapSource,
                    n
                    + QStringLiteral(
                        "_pixels"));

            const QString macro =
                n.toUpper();

            s << "\n#define "
              << macro
              << "_BITMAP_W "
              << qMax(1, g.bitmapWidth)
              << "u\n";

            s << "#define "
              << macro
              << "_BITMAP_H "
              << qMax(1, g.bitmapHeight)
              << "u\n";

            s << "/* Designer demo bitmap for "
              << n
              << ": storage exactly matches the generated BitmapView dimensions. */\n";

            s << "static uint8_t MEMALIGN32 "
              << source
              << "["
              << macro
              << "_BITMAP_W * "
              << macro
              << "_BITMAP_H];\n";
        }

        s << "\nstatic CGWindowProcRes "
          << proc
          << "(CGWindow win, const CGMessage_t *m);\n";

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

            s << "static void "
              << n
              << "_InitDemoBitmap(void);\n";
        }

        s << "\n";

        for (const GuiDesignerGadget &g :
             demoBitmaps) {
            const QString n =
                safeCIdentifier(
                    g.name,
                    QStringLiteral(
                        "bitmap"));

            const QString source =
                safeCIdentifier(
                    g.bitmapSource,
                    n
                    + QStringLiteral(
                        "_pixels"));

            const QString macro =
                n.toUpper();

            s << "static void "
              << n
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

        s << "void "
          << win
          << "_Create(void)\n"
             "{\n";

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

        for (const GuiDesignerGadget &g :
             m_gadgets) {
            const QString n =
                safeCIdentifier(
                    g.name,
                    QStringLiteral(
                        "gadget"));

            if (isDesignerDemoBitmap(g)) {
                s << "\t"
                  << n
                  << "_InitDemoBitmap();\n";
            }

            s << "\t"
              << n
              << " = "
              << creationExpression(
                     g,
                     win)
              << ";\n";

            if (g.type == QStringLiteral("BitmapView")
                && !g.bitmapSource.trimmed().isEmpty()) {
                s << "\tSBOS_BitmapviewSetBitmap("
                  << n
                  << ", "
                  << g.bitmapSource.trimmed()
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

            s << "\tAPI->gui->gadgets->enabled("
              << n
              << ", "
              << (g.enabled
                      ? QStringLiteral("1u")
                      : QStringLiteral("0u"))
              << ");\n";

            if (g.type == QStringLiteral("Slider")
                || g.type == QStringLiteral("Scrollbar")) {
                s << "\t/* Initial value "
                  << g.value
                  << " is stored in the .sbui; current applet API has no exported value setter yet. */\n";
            } else if (g.type == QStringLiteral("ProgressBar")) {
                s << "\t/* Progress range "
                  << g.minimum
                  << ".."
                  << g.maximum
                  << " and value "
                  << g.value
                  << " are stored in the .sbui; current applet API has no exported progress setters yet. */\n";
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
                s << "\t/* Designer-preloaded ListBox items for "
                  << n
                  << ":\n";

                for (int itemIndex = 0;
                     itemIndex < g.listItems.size();
                     ++itemIndex) {
                    s << "\t   ["
                      << itemIndex
                      << "] \""
                      << escapedCString(
                             g.listItems.at(
                                 itemIndex))
                      << "\"\n";
                }

                s << "\t   The current public applet API exposes listbox_create(),"
                     " but not ItemList add/attach yet. */\n";
            }

            s << "\tAPI->gui->gadgets->repaint("
              << n
              << ");\n\n";
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
            if (gadgetUsesDirectCallbacks(g)) {
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
             "\t\tcase CGEVT_WIN_CLOSE_REQUEST:\n"
             "\t\t\t/* <SIDBOX-GUI:USER WINDOW_CLOSE> */\n";

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

        s << "\t\t\t/* </SIDBOX-GUI:USER WINDOW_CLOSE> */\n"
             "\t\t\tSBOS_CloseWindow(win);\n"
             "\t\t\treturn CGPROC_HANDLED;\n";

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

        s << "\n"
             "\t\tdefault:\n"
             "\t\t\tbreak;\n"
             "\t\t}\n"
             "\t\tbreak;\n";

        if (hasWindowRoutedGadget) {
            s << "\n"
                 "\tcase CGMSG_GADGET:\n"
                 "\t\tswitch (m->eventClass) {\n";

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
                 "\tcase CGMSG_MENU:\n"
                 "\t\tswitch (m->eventClass) {\n"
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
                 "\t(void)gadget; (void)a; (void)b; (void)c; (void)d;\n"
                 "\t/* <SIDBOX-GUI:USER "
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

        for (const QString &cb :
             menuCallbacks) {
            s << "static void "
              << cb
              << "(cg_menu_t menu, cg_menuitem_t item, void *userdata)\n"
                 "{\n"
                 "\t(void)menu; (void)item; (void)userdata;\n"
                 "\t/* <SIDBOX-GUI:USER "
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

        if (generatedFilesChanged) {
            generatedFilesChanged(
                m_filePath,
                cPath);
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
    bool m_modified = false;
    GuiDesignerWindow m_window;
    QList<GuiDesignerGadget> m_gadgets;
    QList<GuiDesignerMenuTitle> m_menus;
    QListWidget *m_toolbox = nullptr;
    QTreeWidget *m_menuTree = nullptr;
    GuiDesignerCanvas *m_canvas = nullptr;
    QWidget *m_propertyHost = nullptr;
    QFormLayout *m_propertyLayout = nullptr;
    QLabel *m_statusLabel = nullptr;
    QAction *m_undoAction = nullptr;
    QComboBox *m_snapCombo = nullptr;
    QList<QByteArray> m_undoStates;
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
