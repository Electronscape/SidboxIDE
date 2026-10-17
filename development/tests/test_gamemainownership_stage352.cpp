// Optional host unit test: Qt6Core and zlib required; not part of SIDBOX SDK.
#include "gamemainownership.h"
#include <QTemporaryDir>
#include <QFile>
#include <cassert>
using namespace GamerGirlMainOwnership;
static QByteArray contents(const QString &path) {
    QFile f(path); assert(f.open(QIODevice::ReadOnly)); return f.readAll();
}
static void write(const QString &path, const QByteArray &v) {
    QFile f(path); assert(f.open(QIODevice::WriteOnly | QIODevice::Truncate));
    assert(f.write(v) == v.size());
}
int main() {
    QTemporaryDir temp;
    assert(temp.isValid());
    const QString root = temp.path();
    const QString path = mainPath(root);
    bool changed = false;
    QString error;
    // Brand new main.c becomes IDE-owned with a verified baseline.
    assert(installGenerated(root, "int main(void) { return 0; }\n", &changed, &error));
    assert(changed && isIdeOwnedUnchanged(root));
    assert(contents(path).contains("// OWNER: IDE\n"));
    assert(installGenerated(root, "int main(void) { return 1; }\n", &changed, &error));
    assert(changed && contents(path).contains("return 1;"));
    // CRC mismatch: external edit becomes OWNER:user; programmer's edits kept.
    QByteArray external = contents(path);
    external.replace("return 1;", "return 42;");
    write(path, external);
    assert(installGenerated(root, "int main(void) { return 2; }\n", &changed, &error));
    assert(!changed && contents(path).contains("return 42;"));
    assert(contents(path).startsWith("// GAMERGIRL GENERATED MAIN.C\n// OWNER: user\n"));
    assert(loadRecord(root).owner == QStringLiteral("user"));
    assert(installGenerated(root, "int main(void) { return 3; }\n", &changed, &error));
    assert(!changed && contents(path).contains("return 42;"));
    // Even a forged OWNER IDE line won't make a user-owned file overwriteable.
    QByteArray forged = contents(path); forged.replace("OWNER: user", "OWNER: IDE");
    write(path, forged);
    assert(installGenerated(root, "malicious overwrite", &changed, &error));
    assert(!changed && contents(path) == forged);
    // Unknown legacy files are never adopted even with a marker.
    QTemporaryDir other; assert(other.isValid());
    write(mainPath(other.path()), withOwnerHeader("legacy user edits\n"));
    assert(installGenerated(other.path(), "new game\n", &changed, &error));
    assert(!changed && contents(mainPath(other.path())).contains("legacy user edits"));
    // A deleted main.c may be deliberately regenerated even if previous owner=user.
    assert(QFile::remove(path));
    assert(installGenerated(root, "int main(void) { return 9; }\n", &changed, &error));
    assert(changed && isIdeOwnedUnchanged(root));
    return 0;
}
