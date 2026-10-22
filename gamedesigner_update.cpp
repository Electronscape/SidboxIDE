// Stage 3.69: game project update, transactional ZIP backup and rollback.
#include "gamedesigner.h"
#include "ppbcodec.h"
#include "pngpaletteimport.h"
#include "gamepalette.h"
#include "gamepaletteeditor.h"
#include "gamecodegen.h"
#include "gameanimationeditor.h"
#include "gamemainownership.h"
#include "gamehelpertemplates.h"
#include "gameworldsnapshot.h"

#include <QCheckBox>
#include <QComboBox>
#include <QPaintEvent>
#include <QDir>
#include <QDirIterator>
#include <QEvent>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QContextMenuEvent>
#include <QMimeData>
#include <QUrl>
#include <QAbstractItemView>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QIcon>
#include <QDateTime>
#include <QFont>
#include <QFormLayout>
#include <QFrame>
#include <QGroupBox>
#include <QGraphicsItem>
#include <QApplication>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsPathItem>
#include <QPainterPath>
#include <QCoreApplication>
#include <QDialog>
#include <QDialogButtonBox>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QImage>
#include <QImageReader>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QLabel>
#include <QLineEdit>
#include <QInputDialog>
#include <QMessageBox>
#include <QMenu>
#include <QAction>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QPixmap>
#include <QPalette>
#include <QPushButton>
#include <QProgressDialog>
#include <QThread>
#include <QTimer>
#include <memory>
#include <algorithm>
#include <QSaveFile>
#include <zlib.h>
#include <limits>
#include <QScrollArea>
#include <QScrollBar>
#include <QSettings>
#include <QSizePolicy>
#include <QListView>
#include <QStringList>
#include <QSignalBlocker>
#include <QTextStream>
#include <QSpinBox>
#include <QSplitter>
#include <QToolButton>
#include <QTreeWidget>
#include <QTreeWidgetItemIterator>
#include <QTableWidget>
#include <QHeaderView>
#include <QSet>
#include <QRegularExpression>
#include <QVBoxLayout>
#include <QUuid>
#include <QtMath>


namespace {
// ZIP backup writer using the zlib already linked by CoderGirl. Entries are
// streamed, not buffered in RAM, and are compatible with Ark/7-Zip/unzip.
// Standard ZIP32 intentionally rejects archives exceeding ZIP32 limits.
struct GameBackupZipEntry {
    QByteArray name;
    quint32 crc = 0;
    quint32 compressed = 0;
    quint32 original = 0;
    quint32 offset = 0;
};

bool gameBackupZip16(QIODevice *out, quint16 value)
{
    const char b[2] = {char(value & 255), char((value >> 8) & 255)};
    return out->write(b, 2) == 2;
}
bool gameBackupZip32(QIODevice *out, quint32 value)
{
    const char b[4] = {char(value & 255), char((value >> 8) & 255),
                       char((value >> 16) & 255), char((value >> 24) & 255)};
    return out->write(b, 4) == 4;
}

bool gameBackupWriteZip(const QString &backupFolder, const QString &zipPath,
                        QString *error)
{
    QDir root(backupFolder);
    QStringList files;
    QDirIterator iterator(backupFolder, QDir::Files | QDir::NoSymLinks,
                          QDirIterator::Subdirectories);
    while (iterator.hasNext()) {
        const QString relative = QDir::fromNativeSeparators(root.relativeFilePath(iterator.next()));
        if (relative == QStringLiteral("..") || relative.startsWith(QStringLiteral("../"))
            || QDir::isAbsolutePath(relative)) {
            if (error) *error = QObject::tr("Invalid file path inside backup: %1").arg(relative);
            return false;
        }
        files << relative;
    }
    files.sort();
    if (files.size() > 65535) {
        if (error) *error = QObject::tr("Too many files for ZIP backup.");
        return false;
    }
    QSaveFile output(zipPath);
    if (!output.open(QIODevice::WriteOnly)) {
        if (error) *error = QObject::tr("Cannot open ZIP archive: %1").arg(zipPath);
        return false;
    }
    QVector<GameBackupZipEntry> entries;
    char compressedBlock[65536];
    auto fail = [&](const QString &why) {
        if (error) *error = why;
        output.cancelWriting();
        return false;
    };
    for (const QString &relative : files) {
        QFile input(root.filePath(relative));
        if (!input.open(QIODevice::ReadOnly))
            return fail(QObject::tr("Cannot read backup file: %1").arg(relative));
        const QByteArray name = relative.toUtf8();
        if (name.size() > 65535 || input.size() > std::numeric_limits<quint32>::max()
            || output.pos() > std::numeric_limits<quint32>::max())
            return fail(QObject::tr("ZIP32 limits exceeded by %1").arg(relative));
        GameBackupZipEntry entry;
        entry.name = name;
        entry.offset = quint32(output.pos());
        // Local file header: UTF-8 filenames and a data descriptor after data.
        if (!gameBackupZip32(&output, 0x04034b50) || !gameBackupZip16(&output, 20)
            || !gameBackupZip16(&output, 0x0808) || !gameBackupZip16(&output, 8)
            || !gameBackupZip16(&output, 0) || !gameBackupZip16(&output, 0)
            || !gameBackupZip32(&output, 0) || !gameBackupZip32(&output, 0)
            || !gameBackupZip32(&output, 0) || !gameBackupZip16(&output, quint16(name.size()))
            || !gameBackupZip16(&output, 0) || output.write(name) != name.size())
            return fail(QObject::tr("Cannot write ZIP header for %1").arg(relative));
        z_stream stream{};
        if (deflateInit2(&stream, Z_DEFAULT_COMPRESSION, Z_DEFLATED,
                         -MAX_WBITS, 8, Z_DEFAULT_STRATEGY) != Z_OK)
            return fail(QObject::tr("ZIP compressor initialization failed."));
        quint32 crc = quint32(crc32(0L, Z_NULL, 0));
        quint64 count = 0;
        quint64 packed = 0;
        bool ok = true;
        while (!input.atEnd() && ok) {
            const QByteArray data = input.read(65536);
            if (data.isEmpty()) { ok = false; break; }
            crc = quint32(crc32(crc, reinterpret_cast<const Bytef *>(data.constData()), uInt(data.size())));
            count += quint64(data.size());
            stream.next_in = reinterpret_cast<Bytef *>(const_cast<char *>(data.constData()));
            stream.avail_in = uInt(data.size());
            do {
                stream.next_out = reinterpret_cast<Bytef *>(compressedBlock);
                stream.avail_out = sizeof(compressedBlock);
                if (deflate(&stream, Z_NO_FLUSH) != Z_OK) { ok = false; break; }
                const qint64 produced = qint64(sizeof(compressedBlock) - stream.avail_out);
                if (output.write(compressedBlock, produced) != produced) { ok = false; break; }
                packed += quint64(produced);
            } while (stream.avail_in > 0 || stream.avail_out == 0);
        }
        if (input.error() != QFile::NoError) ok = false;
        if (ok) {
            int result = Z_OK;
            do {
                stream.next_out = reinterpret_cast<Bytef *>(compressedBlock);
                stream.avail_out = sizeof(compressedBlock);
                result = deflate(&stream, Z_FINISH);
                if (result != Z_OK && result != Z_STREAM_END) { ok = false; break; }
                const qint64 produced = qint64(sizeof(compressedBlock) - stream.avail_out);
                if (output.write(compressedBlock, produced) != produced) { ok = false; break; }
                packed += quint64(produced);
            } while (result != Z_STREAM_END);
        }
        deflateEnd(&stream);
        if (!ok || count > std::numeric_limits<quint32>::max()
            || packed > std::numeric_limits<quint32>::max()
            || output.pos() > std::numeric_limits<quint32>::max())
            return fail(QObject::tr("Could not compress backup file: %1").arg(relative));
        entry.crc = crc;
        entry.compressed = quint32(packed);
        entry.original = quint32(count);
        if (!gameBackupZip32(&output, 0x08074b50) || !gameBackupZip32(&output, entry.crc)
            || !gameBackupZip32(&output, entry.compressed)
            || !gameBackupZip32(&output, entry.original))
            return fail(QObject::tr("Could not finish ZIP entry: %1").arg(relative));
        entries.append(entry);
    }
    if (output.pos() > std::numeric_limits<quint32>::max())
        return fail(QObject::tr("ZIP archive exceeds 4 GiB ZIP32 limit."));
    const quint32 centralOffset = quint32(output.pos());
    for (const GameBackupZipEntry &entry : entries) {
        if (!gameBackupZip32(&output, 0x02014b50) || !gameBackupZip16(&output, 20)
            || !gameBackupZip16(&output, 20) || !gameBackupZip16(&output, 0x0808)
            || !gameBackupZip16(&output, 8) || !gameBackupZip16(&output, 0)
            || !gameBackupZip16(&output, 0) || !gameBackupZip32(&output, entry.crc)
            || !gameBackupZip32(&output, entry.compressed)
            || !gameBackupZip32(&output, entry.original)
            || !gameBackupZip16(&output, quint16(entry.name.size()))
            || !gameBackupZip16(&output, 0) || !gameBackupZip16(&output, 0)
            || !gameBackupZip16(&output, 0) || !gameBackupZip16(&output, 0)
            || !gameBackupZip32(&output, 0) || !gameBackupZip32(&output, entry.offset)
            || output.write(entry.name) != entry.name.size())
            return fail(QObject::tr("Could not write ZIP directory."));
    }
    if (output.pos() - centralOffset > std::numeric_limits<quint32>::max())
        return fail(QObject::tr("ZIP directory exceeds ZIP32 limit."));
    const quint32 centralLength = quint32(output.pos() - centralOffset);
    if (!gameBackupZip32(&output, 0x06054b50) || !gameBackupZip16(&output, 0)
        || !gameBackupZip16(&output, 0)
        || !gameBackupZip16(&output, quint16(entries.size()))
        || !gameBackupZip16(&output, quint16(entries.size()))
        || !gameBackupZip32(&output, centralLength)
        || !gameBackupZip32(&output, centralOffset)
        || !gameBackupZip16(&output, 0))
        return fail(QObject::tr("Cannot finish ZIP archive."));
    if (!output.commit()) {
        if (error) *error = QObject::tr("Cannot save ZIP archive: %1").arg(zipPath);
        return false;
    }
    return true;
}

void gameBackupTrimArchives(const QDir &location)
{
    // Sort by timestamped filename; the .history/ backups are independent.
    // Leave legacy Stage 3.4 folder backups untouched for manual recovery.
    const QStringList archives = location.entryList({QStringLiteral("*.zip")},
        QDir::Files, QDir::Name);
    for (int i = 0; i < archives.size() - 20; ++i)
        QFile::remove(location.filePath(archives.at(i)));
}
}

bool SidboxGameDesigner::updateGameProject(bool fromCompile)
{
    // Only the explicit Game Designer button shows the update confirmation and
    // success notice. F5 already handled consent and may have remembered it
    // for this IDE session. Both paths use the SAME backup and update logic;
    // errors remain visible even when called by F5.
    if (m_filePath.isEmpty() || !m_valid) return false;
    QString nameError;
    if (!GameWorldSnapshot::validateUniqueName(m_filePath, &nameError)) {
        QMessageBox::warning(this, tr("World Naming Conflict"), nameError);
        return false;
    }
    const QDir project(QFileInfo(m_filePath).absolutePath());
    const QDir templates(QDir(helperTemplatesRoot()).filePath(QStringLiteral("game")));
    if (!templates.exists()) {
        QMessageBox::warning(this, tr("Update Game Project"),
            tr("Could not find the bundled game helper templates."));
        return false;
    }

    // Refresh installed helpers and add dependencies needed by this design.
    // No unrelated helper is added, and .txt guides are never replaced.
    QSet<QString> needed;
    if (m_tilemapEnabled) needed.insert(QStringLiteral("tilemap"));
    if (hasAdventure()) needed.insert(QStringLiteral("adventureruntime"));
    bool hasSpline = false;
    for (const SplinePath &path : m_splinePaths)
        if (path.points.size() >= 2) hasSpline = true;
    if (hasSpline) needed.insert(QStringLiteral("spline"));
    for (const Resource &r : m_resources) {
        if (r.kind != QStringLiteral("sprite") || r.objectType == QStringLiteral("decoration")) continue;
        needed.insert(r.objectType == QStringLiteral("collectable")
                          ? QStringLiteral("collectables") : QStringLiteral("worldobjects"));
        needed.insert(QStringLiteral("animation"));
        needed.insert(QStringLiteral("spline"));
    }
    const QDir installed(project.filePath(QStringLiteral("gamehelpers")));
    const QStringList known = templates.entryList({QStringLiteral("*.c"), QStringLiteral("*.rulec")}, QDir::Files, QDir::Name);
    for (const QString &name : known) {
        const QString base = QFileInfo(name).completeBaseName();
        // The story rules generate gameadventure.c/.h; they are not
        // SDK helpers and must never become gamegameadventure.c/.h.
        if (base == QStringLiteral("gameadventure") || base == QStringLiteral("gameadventureempty")
            || base == QStringLiteral("gameworlditems")
            || base == QStringLiteral("embeddedresource") || base == QStringLiteral("worldmap")
            || base == QStringLiteral("gameworlds")) continue;
        if (QFileInfo::exists(installed.filePath(QStringLiteral("game") + base + QStringLiteral(".c")))
            || QFileInfo::exists(installed.filePath(QStringLiteral("game") + base + QStringLiteral(".h"))))
            needed.insert(base);
    }
    // The Adventure story is a generated project file, not an installable
    // "game<helper>" runtime. It has its own .rulec/.ruleh pair. Check both
    // before starting Update Game Project's ZIP backup / file replacement.
    if (hasAdventure()) {
        for (const QString &ext : {QStringLiteral(".rulec"), QStringLiteral(".ruleh")}) {
            const QString path = templates.filePath(QStringLiteral("gameadventure") + ext);
            if (!QFileInfo::exists(path)) {
                QMessageBox::warning(this, tr("Update Game Project"),
                    tr("Missing Adventure story rule: %1\n"
                       "The game project has not been modified.").arg(path));
                return false;
            }
        }
    }
    // Make sure the required templates are all present before touching disk.
    QStringList helperNames;
    for (const QString &base : needed) helperNames << base;
    helperNames.sort();
    for (const QString &base : helperNames) {
        for (const QString &ext : {QStringLiteral(".c"), QStringLiteral(".h")}) {
            const QString source = GameHelperTemplates::sourcePath(templates, base, ext);
            if (!QFileInfo::exists(source)) {
                QMessageBox::warning(this, tr("Update Game Project"),
                    tr("Missing SDK helper template: %1").arg(source));
                return false;
            }
        }
    }

    // Resolve every helper C/H template BEFORE backing up or modifying the
    // project. Unknown and unfinished @IDE markers are fatal, never copied.
    // Keep these rendered bytes for the actual install so the source cannot
    // change between validation and commit.
    QMap<QString, QByteArray> renderedHelpers;
    for (const QString &base : helperNames) {
        for (const QString &ext : {QStringLiteral(".c"), QStringLiteral(".h")}) {
            QFile input(GameHelperTemplates::sourcePath(templates, base, ext));
            if (!input.open(QIODevice::ReadOnly)) {
                QMessageBox::warning(this, tr("Update Game Project"),
                    tr("Cannot read game helper template: %1").arg(input.fileName()));
                return false;
            }
            QByteArray output;
            QString renderError;
            if (!GameHelperTemplates::render(input.readAll(), base, ext, m_adventure,
                                             &output, &renderError)) {
                QMessageBox::warning(this, tr("Update Game Project"), renderError);
                return false;
            }
            if (ext == QStringLiteral(".c"))
                output.replace(QStringLiteral("\"%1.h\"").arg(base).toUtf8(),
                               QStringLiteral("\"game%1.h\"").arg(base).toUtf8());
            renderedHelpers.insert(base + ext, output);
        }
    }

    // This is also the explicit write-set for the backup. New files won't
    // exist in the snapshot; user-owned main.c is backed up, never replaced.
    QSet<QString> outputs;
    outputs.insert(QFileInfo(m_filePath).absoluteFilePath());
    // Global definitions now belong to the project and the shared runtime
    // module is regenerated during a world export. Both must roll back too.
    const QDir currentProject(QFileInfo(m_filePath).absolutePath());
    const QStringList projectFiles = currentProject.entryList(
        {QStringLiteral("*.proj")}, QDir::Files, QDir::Name);
    if (projectFiles.size() == 1) outputs.insert(projectFiles.first());
    outputs.insert(QStringLiteral("gamehelpers/gameglobalstamps.c"));
    const QDir gameProject(QFileInfo(m_filePath).absolutePath());
    if (QFileInfo::exists(gameProject.filePath(QStringLiteral("players/player.sbpi")))) {
        outputs.insert(QStringLiteral("gamehelpers/gameplayer.c"));
        outputs.insert(QStringLiteral("gamehelpers/gameplayer.h"));
    }
    outputs.insert(QStringLiteral("gameassets/gameassets.c"));
    outputs.insert(QStringLiteral("gameassets/gameassets.h"));
    // These generated world modules are temporarily written at the project
    // root, published to worlds/<name>/gamehelpers/, then cleaned up. Include
    // old root copies in the rollback ZIP before the publisher removes them.
    outputs.insert(QStringLiteral("gamehelpers/gameworlditems.c"));
    outputs.insert(QStringLiteral("gamehelpers/gameworlditems.h"));
    outputs.insert(QStringLiteral("gamehelpers/gameworlditems.txt"));
    // Even no-story worlds regenerate empty Adventure stubs; back them up too.
    outputs.insert(QStringLiteral("gamehelpers/gameadventure.c"));
    outputs.insert(QStringLiteral("gamehelpers/gameadventure.h"));
    outputs.insert(QStringLiteral("gamehelpers/gameworlds.c"));
    outputs.insert(QStringLiteral("gamehelpers/gameworlds.h"));
    outputs.insert(QStringLiteral("maingame.c.txt"));
    // Main generation may create a missing file or transfer a dirty external
    // file. Back up/track BOTH source and metadata for full rollback. User
    // files are still excluded from actual regeneration by the CRC gate.
    outputs.insert(QStringLiteral("main.c"));
    outputs.insert(QStringLiteral(".codergirl/main-ownership.json"));
    outputs.insert(QStringLiteral(".codergirl/active-world.json"));

    if (hasSpline
        || QFileInfo::exists(installed.filePath(QStringLiteral("splinepaths.h")))) {
        // saveDesign also refreshes previously exported paths even if the
        // last spline was just deleted, so their originals need backing up.
        outputs.insert(QStringLiteral("gamehelpers/splinepaths.c"));
        outputs.insert(QStringLiteral("gamehelpers/splinepaths.h"));
    }
    // Back up any obsolete root-level exports from earlier IDE stages before
    // the publisher removes them. Nothing new is written to project/gamelevels/.
    for (const QString &design : project.entryList(
             {QStringLiteral("*.sbgm")}, QDir::Files, QDir::Name)) {
        const QString base = sidboxTilemapWorldBaseName(project.filePath(design));
        for (const QString &ext : {QStringLiteral(".c"), QStringLiteral(".h"), QStringLiteral(".map")}) {
            const QString legacy = QStringLiteral("gamelevels/") + base + ext;
            if (QFileInfo::exists(project.filePath(legacy))) outputs.insert(legacy);
        }
    }
    for (const QString &base : helperNames) {
        const QString targetBase = QStringLiteral("gamehelpers/game") + base;
        outputs.insert(targetBase + QStringLiteral(".c"));
        outputs.insert(targetBase + QStringLiteral(".h"));
        // Only missing beginner guides get installed; existing ones stay intact.
        if (!QFileInfo::exists(project.filePath(targetBase + QStringLiteral(".txt")))
            && QFileInfo::exists(templates.filePath(base + QStringLiteral(".txt"))))
            outputs.insert(targetBase + QStringLiteral(".txt"));
    }
    QStringList paths;
    for (const QString &path : outputs) paths << path;
    paths.sort();
    QStringList replacing, adding;
    for (const QString &p : paths) {
        if (QFileInfo::exists(QDir::isAbsolutePath(p) ? p : project.filePath(p))) replacing << p;
        else adding << p;
    }

    bool embedPixels = false; // Compile uses the normal external-PPB mode.
    if (!fromCompile) {
        QMessageBox confirm(this);
        confirm.setIcon(QMessageBox::Warning);
        confirm.setStyleSheet(QStringLiteral("QMessageBox, QPushButton, QCheckBox, QTextEdit { border-radius: 0px; }"));
        confirm.setWindowTitle(tr("Update Game Project — Confirm"));
        confirm.setText(tr("Back up and update the current game project?"));
        confirm.setInformativeText(tr(
            "CoderGirl will refresh existing game helper C/H files from the SDK, "
            "export the current spline paths and tilemap (if present), then regenerate "
            "each published world's resources and a world-manager maingame.c.txt.\n\n"
            "Any edits in replaced helpers or generated files will be overwritten. "
            "A ZIP backup is made FIRST.\n\n"
            "Only a verified, unchanged IDE-owned main.c may be regenerated. "
            "Hand-edited, unknown and user-owned main.c files remain protected. "
            "maingame.c.txt is always updated.\n\n"
            "Only the newest 20 Update Project ZIP backups are retained "
            "(older ZIPs are deleted after a successful update). "
            "Earlier folder-style backups are preserved.\n\n"
            "Replace %1 existing files; create up to %2 missing files.")
            .arg(replacing.size()).arg(adding.size()));
        confirm.setDetailedText(tr("FILES TO REPLACE:\n%1\n\nFILES TO CREATE:\n%2")
            .arg(replacing.isEmpty() ? tr("(none)") : replacing.join(QStringLiteral("\n")),
                 adding.isEmpty() ? tr("(none)") : adding.join(QStringLiteral("\n"))));
        auto *embed = new QCheckBox(tr("Embed sprite and selected tile-atlas PPBs in generated C (normally load from SD card)"), &confirm);
        embed->setChecked(false);
        confirm.setCheckBox(embed);
        auto *proceed = confirm.addButton(tr("Back Up and Update"), QMessageBox::AcceptRole);
        confirm.addButton(QMessageBox::Cancel);
        confirm.setDefaultButton(qobject_cast<QPushButton *>(confirm.button(QMessageBox::Cancel)));
        confirm.exec();
        if (confirm.clickedButton() != proceed) return false;

        embedPixels = embed->isChecked();
    }

    const QString stamp = QDateTime::currentDateTime().toString(QStringLiteral("yyyyMMdd-HHmmss-zzz"));
    const QDir backupRoot(project.filePath(QStringLiteral(".codergirl-backups/updates")));
    const QString backupFolder = backupRoot.filePath(QStringLiteral(".staging-") + stamp);
    const QString archivePath = backupRoot.filePath(stamp + QStringLiteral(".zip"));
    QDir backup(backupFolder);
    if (!QDir().mkpath(backupFolder)) {
        QMessageBox::warning(this, tr("Update Game Project"), tr("Cannot create backup folder:\n%1").arg(backupFolder));
        return false;
    }
    for (const QString &relative : replacing) {
        const QString src = QDir::isAbsolutePath(relative) ? relative : project.filePath(relative);
        // .sbgm is inside the project in normal use. Restrict backup targets
        // to project files, never copy a path outside the project tree.
        const QString safeName = project.relativeFilePath(src);
        if (safeName == QStringLiteral("..") || safeName.startsWith(QStringLiteral("../"))
            || QDir::isAbsolutePath(safeName)) {
            QMessageBox::warning(this, tr("Update Game Project"),
                tr("Unsafe backup path: %1").arg(src));
            return false;
        }
        const QString dest = backup.filePath(safeName);
        if (!QDir().mkpath(QFileInfo(dest).absolutePath()) || !QFile::copy(src, dest)) {
            QMessageBox::warning(this, tr("Update Game Project"),
                tr("Backup failed; project update was NOT started.\n%1").arg(src));
            return false;
        }
    }

    // Archive is complete before any generated or helper file is modified.
    // Keep the staging copies until the update finishes for safe rollback.
    QString zipError;
    if (!gameBackupWriteZip(backupFolder, archivePath, &zipError)) {
        QMessageBox::warning(this, tr("Update Game Project"),
            tr("Could not create the ZIP backup; project update was NOT started.\n%1")
                .arg(zipError));
        return false;
    }

    // Only the template-backed helper C/H files are deliberately replaced.
    // Their paired .txt guides are installed when missing, never overwritten.
    QString error;
    for (const QString &base : helperNames) {
        const QString installedBase = QStringLiteral("game") + base;
        for (const QString &ext : {QStringLiteral(".h"), QStringLiteral(".c"), QStringLiteral(".txt")}) {
            const QString output = installed.filePath(installedBase + ext);
            if (ext == QStringLiteral(".txt") && QFileInfo::exists(output)) continue;
            QByteArray bytes;
            if (ext == QStringLiteral(".txt")) {
                QFile source(templates.filePath(base + ext));
                if (!source.exists()) continue;
                if (!source.open(QIODevice::ReadOnly)) {
                    error = tr("Cannot read guide: %1").arg(source.fileName()); break;
                }
                bytes = source.readAll();
            } else {
                bytes = renderedHelpers.value(base + ext);
            }
            if (!QDir().mkpath(QFileInfo(output).absolutePath())) {
                error = tr("Cannot create folder for: %1").arg(output); break;
            }
            QSaveFile file(output);
            if (!file.open(QIODevice::WriteOnly)
                || file.write(bytes) != bytes.size() || !file.commit()) {
                file.cancelWriting();
                error = tr("Cannot install helper: %1").arg(output); break;
            }
        }
        if (!error.isEmpty()) break;
    }
    // saveDesign auto-updates previously exported paths/level; explicitly
    // export again to cover first-time exports as well.
    if (error.isEmpty() && !saveDesign()) error = tr("Saving the design failed.");
    if (error.isEmpty() && hasSpline && !exportSplinePaths(false))
        error = tr("Spline export failed.");
    if (error.isEmpty() && m_tilemapEnabled && !exportTilemap(false, true))
        error = tr("Tilemap export failed.");
    if (error.isEmpty() && !generateGameCodeCore(embedPixels, true))
        error = tr("V1 game code generation failed.");
    if (!error.isEmpty()) {
        // Restore known outputs, using atomic replacement. The originals
        // remain in the backup folder even if rollback itself fails.
        QStringList restoreFailures;
        for (const QString &relative : replacing) {
            const QString destination = QDir::isAbsolutePath(relative)
                ? relative : project.filePath(relative);
            const QString from = backup.filePath(project.relativeFilePath(destination));
            QFile original(from);
            if (!original.open(QIODevice::ReadOnly)) {
                restoreFailures << destination;
                continue;
            }
            QSaveFile restored(destination);
            const QByteArray bytes = original.readAll();
            if (!restored.open(QIODevice::WriteOnly)
                || restored.write(bytes) != bytes.size() || !restored.commit()) {
                restored.cancelWriting();
                restoreFailures << destination;
            }
        }
        for (const QString &relative : adding) {
            const QString created = QDir::isAbsolutePath(relative)
                ? relative : project.filePath(relative);
            if (QFileInfo::exists(created) && !QFile::remove(created))
                restoreFailures << created;
        }
        setDirty(true); // The in-memory design may differ from restored .sbgm.
        const QString recovery = restoreFailures.isEmpty()
            ? tr("Files were restored to their pre-update state.")
            : tr("Automatic recovery could not restore these files:\n%1\n"
                 "Recover them manually from the ZIP backup (or staging folder).")
                  .arg(restoreFailures.join(QStringLiteral("\n")));
        QMessageBox::critical(this, tr("Update Game Project — Incomplete"),
            tr("The update stopped: %1\n\n%2\n\nZIP backup:\n%3")
               .arg(error, recovery, archivePath));
        if (restoreFailures.isEmpty()) QDir(backupFolder).removeRecursively();
        if (assetFilesChanged) assetFilesChanged();
        return false;
    }
    // Only now is it safe to delete the temporary rollback copies, and trim
    // old ZIP archives after a fully successful project update.
    QDir(backupFolder).removeRecursively();
    gameBackupTrimArchives(backupRoot);
    if (assetFilesChanged) assetFilesChanged();
    if (!fromCompile) {
        QMessageBox::information(this, tr("Game Project Updated"),
            tr("Game helper files refreshed, splines/tilemap exported, and V1 game code regenerated.\n\n"
               "This world has a separate buildable source tree under worlds/<name>/. Other published worlds are compiled too.\n\n"
               "main.c is updated only while still IDE-owned. User-owned source and existing beginner guides are untouched.\n\n"
               "ZIP backup: %1\nOnly the newest 20 update ZIP backups are kept.")
                   .arg(archivePath));
    }
    return true;
}
