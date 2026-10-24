#pragma once
#include <QString>

// Generate the optional V1 title-screen runtime from .sidbox-title-screen.json.
// Writes IDE-owned gamehelpers/gametitle.c/.h; never edits the user's main.c.
namespace GameTitleRuntime {
bool enabled(const QString &projectRoot);
bool generate(const QString &projectRoot, const QString &fallbackWorld,
              const QString &sdkTemplateRoot, QString *error);
}
