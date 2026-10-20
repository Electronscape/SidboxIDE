#ifndef GAMEEDITORCONTROLSTYLE_H
#define GAMEEDITORCONTROLSTYLE_H

// Compatibility for game editor integrations: normal widgets now inherit
// ideGlobalControlStyle() from the QApplication-wide theme.
#include "ideglobaltheme.h"

inline QString gameEditorControlStyle(const IDETheme &theme)
{
    return ideGlobalControlStyle(theme);
}

#endif // GAMEEDITORCONTROLSTYLE_H
