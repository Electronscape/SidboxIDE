#include "mainwindow.h"

#include <QApplication>
#include <QMainWindow>
#include <QIcon>
#include <QDebug>
#include <QCoreApplication>
#include <QGuiApplication>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QPixmap>
#include <QTimer>
#include <QWindow>
#include <QWidget>

#include <QProcess>
#include <QProcessEnvironment>

namespace {
QIcon loadSidboxIcon()
{
    const QString appDir = QCoreApplication::applicationDirPath();
    const QStringList candidates = {
        QStringLiteral(":/icons/icon.png"),
        QDir(appDir).filePath(QStringLiteral("icons/icon.png")),
        QDir(appDir).filePath(QStringLiteral("../icons/icon.png")),
        QDir(appDir).filePath(QStringLiteral("../../icons/icon.png")),
        QDir::current().filePath(QStringLiteral("icons/icon.png")),
        QDir::current().filePath(QStringLiteral("SidboxIDE/icons/icon.png")),
        QStringLiteral(":/icons/icon.ico"),
        QDir(appDir).filePath(QStringLiteral("icons/icon.ico")),
        QDir(appDir).filePath(QStringLiteral("../icons/icon.ico")),
        QDir::current().filePath(QStringLiteral("icons/icon.ico")),
        QDir::current().filePath(QStringLiteral("SidboxIDE/icons/icon.ico"))
    };

    for (const QString &candidate : candidates) {
        QPixmap pixmap(candidate);
        if (!pixmap.isNull()) {
            QIcon icon;
            icon.addPixmap(pixmap);
            qDebug() << "Loaded Sidbox IDE icon:" << candidate << pixmap.size();
            return icon;
        }
    }

    qWarning() << "Could not decode Sidbox IDE icon from any candidate" << candidates;
    return {};
}

void applySidboxIcon(QWidget *window, const QIcon &icon)
{
    if (!window || icon.isNull()) {
        return;
    }

    QApplication::setWindowIcon(icon);
    window->setWindowIcon(icon);
    if (QWindow *nativeWindow = window->windowHandle()) {
        nativeWindow->setIcon(icon);
    }
}
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setApplicationName(QStringLiteral("Sidbox IDE"));
    QGuiApplication::setDesktopFileName(QStringLiteral("SidboxIDE"));

    const QIcon appIcon = loadSidboxIcon();
    if (!appIcon.isNull()) {
        QApplication::setWindowIcon(appIcon);
    } else {
        qWarning() << "Could not load Sidbox IDE icon from resources";
    }

/*
#ifdef Q_OS_LINUX
    QString platform = QGuiApplication::platformName();
    printf("Current platform: %s\n", platform.toUtf8().constData());

    // If not already running under X11/XWayland
    if (!platform.contains("xcb", Qt::CaseInsensitive)) {
        printf("Relaunching with XWayland...\n");

        QStringList args = QCoreApplication::arguments();
        args.removeFirst();  // remove program name

        // Build environment without Wayland variables
        QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
        env.remove("WAYLAND_DISPLAY");
        env.remove("WAYLAND_SOCKET");
        env.remove("XDG_SESSION_TYPE");
        env.insert("XDG_SESSION_TYPE", "x11");
        env.insert("QT_QPA_PLATFORM", "xcb");

        // Launch the process
        QProcess *p = new QProcess;
        p->setProcessEnvironment(env);
        p->setProgram(QCoreApplication::applicationFilePath());
        p->setArguments(args);
        p->setWorkingDirectory(QCoreApplication::applicationDirPath());

        if (p->startDetached()) {
            printf("Relaunched successfully!\n");
            return 0;
        } else {
            printf("!Relaunch failed!\n");
            delete p;
        }
    } else {
        printf("already bubbling !!!\n");
    }
#endif
*/
    MainWindow w;

    setvbuf(stdout, NULL, _IONBF, 0);

    applySidboxIcon(&w, appIcon);

    printf("Start Sidbox\r\n"); //fflush(stdout);

    w.show();
    QTimer::singleShot(0, &w, [&w, appIcon]() {
        applySidboxIcon(&w, appIcon);
    });
    QTimer::singleShot(250, &w, [&w, appIcon]() {
        applySidboxIcon(&w, appIcon);
    });
    return a.exec();
}
