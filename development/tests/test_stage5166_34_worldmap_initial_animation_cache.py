#!/usr/bin/env python3
"""Stage 5.166.34: animated cache indices must use *initialized* chunk geometry.

Regression: on initial open resizeMap() rebuilt animatedSections while
chunkColumns was still 0. An edit rebuilt the index using correct dimensions,
so the rest of the World Map started animating only after a brush stroke.
"""
from pathlib import Path
import re

root = Path(__file__).resolve().parents[2]
source = (root / "gamerpguieditors.h").read_text()
start = source.index("const auto resizeMap=[&](int newTile){")
end = source.index("QObject::connect(w,qOverload<int>", start)
resize = source[start:end]

assert resize.count("rebuildAnimatedSections();") == 1, "one complete cache-index rebuild per resize"
geo = resize.index("chunkColumns=(pixelWidth+chunkPixels-1)/chunkPixels;")
last_item = resize.index("chunkItems.append(item);")
reindex = resize.index("rebuildAnimatedSections();")
redraw = resize.index("loadAtlas();")
assert geo < last_item < reindex < redraw, (
    "animated sections must be indexed AFTER setting chunkColumns and constructing chunks, "
    "but BEFORE the atlas redraw"
)

section_for = source[source.index("const auto sectionForCell=[&](int n){"):]
section_for = section_for[:section_for.index("};")]
assert "((n/columns)*tile)/chunkPixels)*chunkColumns" in section_for

# Animated tiles scattered over three separate 256px rows and four columns;
# every one must be registered with a distinct section for that row/column.
for tile, width, height in [(16, 1024, 768), (8, 1024, 768), (16, 2048, 1024)]:
    cols = width // tile
    chunk_columns = (width + 255) // 256
    chunk_rows = (height + 255) // 256
    indices = []
    for cy in range(chunk_rows):
        for cx in range(chunk_columns):
            x, y = cx * 256 // tile, cy * 256 // tile
            n = y * cols + x
            section = (((n // cols) * tile) // 256) * chunk_columns + (((n % cols) * tile) // 256)
            indices.append(section)
    assert indices == list(range(chunk_columns * chunk_rows)), (
        "the full animated map must update before painting", width, height, tile, indices
    )

assert "previousFrames.clear();" in resize[reindex:redraw], (
    "tile animations should recalculate frame state whenever chunk geometry changes"
)
print("PASS Stage 5.166.34: first-open and resized animated World Map chunk indexing")
