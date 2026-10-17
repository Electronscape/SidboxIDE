#ifndef GAMEMAINOWNERSHIP_H
#define GAMEMAINOWNERSHIP_H

// GamerGirl Stage 3.52: never overwrite a programmer-owned main.c.
// This is IDE-side Qt code, NOT a SIDBOX runtime header.
#include <QByteArray>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSaveFile>
#include <QString>
#include <QtGlobal>
#include <zlib.h>

namespace GamerGirlMainOwnership {
inline QString mainPath(const QString &root) {
    return QDir(root).filePath(QStringLiteral("main.c"));
}
inline QString recordPath(const QString &root) {
    return QDir(root).filePath(QStringLiteral(".codergirl/main-ownership.json"));
}
inline bool matchesMainPath(const QString &path, const QString &projectRoot) {
    if (path.isEmpty() || projectRoot.isEmpty()) return false;
    return QFileInfo(path).absoluteFilePath() == QFileInfo(mainPath(projectRoot)).absoluteFilePath();
}
inline QByteArray marker(const char *owner) {
    return QByteArray("// OWNER: ") + owner;
}
inline QByteArray withOwnerHeader(const QByteArray &starter) {
    static const QByteArray header =
        "// GAMERGIRL GENERATED MAIN.C\n"
        "// OWNER: IDE\n"
        "// When OWNER is user, GamerGirl no longer regenerates main.c.\n"
        "// Refer to maingame.c.txt for updated modular support and examples.\n"
        "\n";
    return header + starter;
}
inline quint32 crc(const QByteArray &bytes) {
    uLong result = ::crc32(0L, Z_NULL, 0);
    const char *data = bytes.constData();
    qsizetype remaining = bytes.size();
    while (remaining > 0) {
        const uInt chunk = static_cast<uInt>(qMin<qsizetype>(remaining, 0x7fffffff));
        result = ::crc32(result, reinterpret_cast<const Bytef *>(data), chunk);
        data += chunk;
        remaining -= chunk;
    }
    return static_cast<quint32>(result);
}
inline QString hexCrc(const QByteArray &bytes) {
    return QStringLiteral("%1").arg(crc(bytes), 8, 16, QLatin1Char('0'));
}
struct Record {
    bool valid = false;
    QString owner;
    QString checksum;
    qint64 size = -1;
};
inline Record loadRecord(const QString &root) {
    Record r;
    QFile file(recordPath(root));
    if (!file.open(QIODevice::ReadOnly)) return r;
    QJsonParseError err;
    const QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &err);
    if (err.error != QJsonParseError::NoError || !doc.isObject()) return r;
    const QJsonObject obj = doc.object();
    if (obj.value(QStringLiteral("version")).toInt() != 1) return r;
    r.owner = obj.value(QStringLiteral("owner")).toString();
    r.checksum = obj.value(QStringLiteral("crc32")).toString();
    r.size = static_cast<qint64>(obj.value(QStringLiteral("bytes")).toDouble(-1));
    r.valid = (r.owner == QStringLiteral("IDE") || r.owner == QStringLiteral("user"))
        && r.checksum.size() == 8 && r.size >= 0;
    return r;
}
inline bool storeRecord(const QString &root, const QString &owner,
                        const QByteArray &contents, QString *error = nullptr) {
    const QString target = recordPath(root);
    if (!QDir().mkpath(QFileInfo(target).absolutePath())) {
        if (error) *error = QStringLiteral("Cannot create ownership metadata folder");
        return false;
    }
    QJsonObject json;
    json.insert(QStringLiteral("version"), 1);
    json.insert(QStringLiteral("owner"), owner);
    json.insert(QStringLiteral("crc32"), hexCrc(contents));
    json.insert(QStringLiteral("bytes"), static_cast<double>(contents.size()));
    const QByteArray bytes = QJsonDocument(json).toJson(QJsonDocument::Indented);
    QSaveFile out(target);
    if (!out.open(QIODevice::WriteOnly) || out.write(bytes) != bytes.size() || !out.commit()) {
        out.cancelWriting();
        if (error) *error = QStringLiteral("Cannot write %1").arg(target);
        return false;
    }
    return true;
}
inline bool readMain(const QString &root, QByteArray *contents) {
    QFile file(mainPath(root));
    if (!file.open(QIODevice::ReadOnly)) return false;
    *contents = file.readAll();
    return true;
}
inline bool isIdeOwnedUnchanged(const QString &root) {
    const Record r = loadRecord(root);
    if (!r.valid || r.owner != QStringLiteral("IDE")) return false;
    QByteArray contents;
    if (!readMain(root, &contents)) return false;
    return contents.startsWith("// GAMERGIRL GENERATED MAIN.C\n// OWNER: IDE\n")
        && r.size == contents.size() && r.checksum == hexCrc(contents);
}
// If contents differ from the recorded IDE output, never replace them. Mark
// OWNER user in-place (only that line), preserving the rest of the source.
inline bool transferToUser(const QString &root, QString *error = nullptr) {
    QByteArray contents;
    if (!readMain(root, &contents)) {
        if (error) *error = QStringLiteral("Cannot read main.c to transfer ownership");
        return false;
    }
    // Detect the owner line even if an external editor changed LF to CRLF.
    // The edit replaces only those twelve bytes, preserving every other byte.
    const int ownerAt = contents.indexOf(marker("IDE"));
    if (ownerAt >= 0 && ownerAt < 256 &&
        (ownerAt == 0 || contents.at(ownerAt - 1) == '\n')) {
        contents.replace(ownerAt, marker("IDE").size(), marker("user"));
        QSaveFile out(mainPath(root));
        if (!out.open(QIODevice::WriteOnly) || out.write(contents) != contents.size() || !out.commit()) {
            out.cancelWriting();
            if (error) *error = QStringLiteral("Could not change OWNER to user in main.c");
            return false;
        }
    }
    return storeRecord(root, QStringLiteral("user"), contents, error);
}
// Called *after* CoderGirl successfully saves a modified generated main.c.
// The editor changes the owner line in memory before the save.
inline bool recordUserSave(const QString &root, QString *error = nullptr) {
    QByteArray contents;
    return readMain(root, &contents) && storeRecord(root, QStringLiteral("user"), contents, error);
}
// Only installs an IDE-controlled file if main.c is absent OR matches a
// previously registered byte-for-byte IDE generation. Manual OWNER: IDE is
// insufficient. Does not overwrite an unregistered or user-owned main.c.
inline bool installGenerated(const QString &root, const QByteArray &starter,
                             bool *changed = nullptr, QString *error = nullptr) {
    if (changed) *changed = false;
    const QString path = mainPath(root);
    const bool exists = QFileInfo::exists(path);
    if (exists && !isIdeOwnedUnchanged(root)) {
        const Record r = loadRecord(root);
        if (r.valid && r.owner == QStringLiteral("IDE")) {
            // An external edit occurred. Preserve it and relinquish control.
            return transferToUser(root, error);
        }
        return true; // Never adopt legacy / manually marked main.c.
    }
    const QByteArray contents = withOwnerHeader(starter);
    if (exists) {
        QByteArray previous;
        if (readMain(root, &previous) && previous == contents) return true;
    }
    QSaveFile file(path);
    if (!file.open(QIODevice::WriteOnly) || file.write(contents) != contents.size() || !file.commit()) {
        file.cancelWriting();
        if (error) *error = QStringLiteral("Cannot generate %1").arg(path);
        return false;
    }
    if (changed) *changed = true;
    // A missing/corrupt metadata file makes ownership INVALID and prevents
    // any future overwrite, even if main.c was written successfully.
    return storeRecord(root, QStringLiteral("IDE"), contents, error);
}
}
#endif
