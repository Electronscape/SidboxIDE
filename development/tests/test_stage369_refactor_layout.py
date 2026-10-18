"""Qt-free checks for the Stage 3.69 source split and ownership boundaries.

Run alongside the original runtime regressions. Building the Qt6 application
still requires the developer's Qt Creator environment.
"""
from pathlib import Path
import re

root = Path(__file__).resolve().parents[2]
cmake = (root / "CMakeLists.txt").read_text()
cpp_names = ("gamedesigner.cpp", "gamedesigner_export.cpp", "gamedesigner_project.cpp",
             "gamedesigner_update.cpp", "gametilemap.cpp", "gametilemapmodel.cpp")
sources = {name: (root / name).read_text() for name in cpp_names}
for name in cpp_names:
    assert re.search(r"^\s*" + re.escape(name) + r"\s*$", cmake, re.MULTILINE), name

# Each class function must have exactly one out-of-class definition.
for method in ("installMissingWorldHelpers", "exportWorldItems", "exportExampleMain",
               "syncManagedMain", "updateGameProject", "generateGameCode",
               "generateGameCodeCore", "loadDesign", "saveDesign"):
    matches = sum(len(re.findall(r"\bSidboxGameDesigner::" + method + r"\s*\(", body))
                  for body in sources.values())
    assert matches == 1, (method, matches)
for cls, method in (("SidboxTileStamp", "resizeStamp"),
                    ("SidboxCollisionStamp", "resizeStamp"),
                    ("SidboxTilemap", "resizeMap"),
                    ("SidboxTilemap", "toJson"),
                    ("SidboxTilemap", "fromJson")):
    matches = sum(len(re.findall(r"\b" + cls + r"::" + method + r"\s*\(", body))
                  for body in sources.values())
    assert matches == 1, (cls, method, matches)

assert "gameBackupWriteZip" in sources["gamedesigner_update.cpp"]
assert "gameBackupWriteZip" not in sources["gamedesigner.cpp"]
assert "gametilemapinternal.h" in sources["gametilemap.cpp"]
assert "gametilemapinternal.h" in sources["gametilemapmodel.cpp"]
assert "validSlopePoints" in (root / "gametilemapinternal.h").read_text()
assert "gamedesigner_limits.h" in sources["gamedesigner.cpp"]
assert "gamedesigner_limits.h" in sources["gamedesigner_project.cpp"]
print("PASS: Stage 3.69 class methods split uniquely; CMake and shared interfaces wired.")
