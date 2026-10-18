#ifndef GAMERGIRL_TILEMAP_INTERNAL_H
#define GAMERGIRL_TILEMAP_INTERNAL_H
#include "gametilemap.h"

// Used by both JSON import and collision-stamp export.
inline bool validSlopePoints(const SidboxCollisionStamp &stamp)
{
    if (stamp.points.size() < 2 || stamp.points.size() > 128 ||
        stamp.points.first().x() != 0 ||
        stamp.points.last().x() != stamp.width * stamp.tileSize) return false;
    int previous = -1;
    for (const QPoint &p : stamp.points) {
        if (p.x() <= previous || p.x() > stamp.width * stamp.tileSize ||
            p.y() < 0 || p.y() > stamp.height * stamp.tileSize) return false;
        previous = p.x();
    }
    return true;
}

#endif
