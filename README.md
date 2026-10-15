<div align="center">

# CoderGirl IDE / SIDBOX IDE

**A custom C/C++ development environment for SIDBOX applets, with support for both legacy V1 applets and CGARM V2 relocatable applets.**

![Platform](https://img.shields.io/badge/platform-Linux-blue)
![Qt](https://img.shields.io/badge/Qt-6-green)
![Status](https://img.shields.io/badge/status-active-success)
![CGARM](https://img.shields.io/badge/CGARM-beta-purple)
![Target](https://img.shields.io/badge/target-STM32H743-orange)

</div>

---

## Overview

**CoderGirl IDE** (also referred to as **SIDBOX IDE**) is a custom development environment for building software for the **SIDBOX** platform.

It supports:

- **V1 legacy fixed-address applets**
- **CGARM (Beta) V2 relocatable applets**
- GUI-based applet development
- project management
- resource generation
- syntax highlighting and code folding
- integrated build output
- a standalone command-line compiler for CGARM projects

The project is designed to make SIDBOX software development easier, while still exposing the power of the platform when needed.

---

## Features

### IDE Features

- Code editor with syntax highlighting
- Code folding
- Project management
- GUI project support
- Build output window
- Assembly output generation
- Project settings editor
- Integrated compile workflow for:
  - **V1 legacy applets**
  - **CGARM V2 applets**
- Incremental compilation for CGARM V2 builds
- Clean CGARM build cache action from the Compile dropdown

### CGARM Features

- Relocatable ARM ELF applets (**V2**)
- Precompiled standard library archive: **`libcgarm.a`**
- Standalone command-line builder: **`cgarm-build`**
- Automatic RAM sizing assistance in the IDE
- Link-only relink support for faster app size adjustment
- TFCard filesystem support
- Standard C runtime functionality tailored for SIDBOX applets

---

## Build Modes

### V1 (Legacy Fixed-Address)

The original SIDBOX applet format.

- Fixed-address applets
- Built directly by the IDE’s legacy compiler path
- Best for existing projects and traditional applets

### CGARM (Beta) / V2 ELF

The newer relocatable SIDBOX applet format.

- Relocatable ARM ELF (`ET_DYN`)
- Built using **`cgarm-build`**
- Linked against **`libcgarm.a`**
- Supports improved flexibility and modernised build flow

> V1 and CGARM V2 use separate build paths inside the IDE.

---

## Screenshots

> Replace these image paths with your actual images in the repository.

### IDE Project Settings

![Project Settings](docs/images/project-settings.png)

### App Manager / Multiple Running V2 Applets

![App Manager](docs/images/app-manager.png)

### Editor / Build Output

![Editor Build Output](docs/images/editor-build-output.png)

---

## Repository Layout

```text
SidboxIDE/
├── CMakeLists.txt
├── mainwindow.cpp
├── mainwindow.h
├── codeeditor.cpp
├── codeeditor.h
├── projectsettingsdialog.cpp
├── idelibs/
│   ├── api/
│   ├── libraries/
│   └── tools/
│       ├── bin/
│       │   ├── arm-none-eabi-gcc
│       │   ├── cgarm-build
│       │   └── sidbox-v2-packer
│       └── cgarm/
│           ├── include/
│           └── lib/
│               └── libcgarm.a
└── development/
    └── tools/
        └── cgarm-build/
            └── cgarm-build.cpp
```

---

## Requirements

Typical development environment:

- Linux
- Qt 6
- CMake
- bundled `arm-none-eabi` toolchain
- LLVM `ld.lld`
- SIDBOX SDK files included in `idelibs/`

> The repository structure assumes the bundled SIDBOX toolchain layout used by this project.

---

## Building the IDE

From the repository root:

```bash
mkdir build
cd build
cmake ..
make -j$(nproc)
```

Or open the project in **Qt Creator** and build normally.

---

## Using the IDE

### V1 Applets

1. Open or create a project
2. Set applet format to **V1 (legacy fixed-address)**
3. Press **F5** to build

### CGARM V2 Applets

1. Open or create a project
2. Set applet format to **CGARM (Beta) - relocatable GUI (V2 ELF)**
3. Configure:
   - applet size
   - CGARM heap allowance
   - CGARM private callback stack
4. Press **F5** to build

The IDE will:

- save project resources
- compile sources
- call `cgarm-build`
- link the applet
- pack the final `.app`
- generate assembly output

If the applet is too large for the selected memory allowance, the IDE can suggest a larger size and relink without recompiling.

---

## `cgarm-build` Command-Line Usage

`cgarm-build` is the standalone CGARM V2 compiler backend.

### Build a single source file

```bash
cgarm-build hello.c -o hello.app
```

### Build a project file

```bash
cgarm-build myproject.proj -o myproject.app
```

### Dry run

```bash
cgarm-build myproject.proj -o myproject.app --dry-run
```

### Force a full rebuild

```bash
cgarm-build myproject.proj -o myproject.app --rebuild
```

### Clean CGARM build cache

```bash
cgarm-build myproject.proj --clean
```

---

## Incremental Compilation

CGARM builds support incremental compilation.

This means:

- unchanged files are skipped
- only modified `.c` files are recompiled
- header dependency changes trigger rebuilds where needed
- RAM-size relinks can reuse existing objects without recompiling

This makes repeated builds significantly faster during development.

---

## Cleaning Builds

For CGARM projects, you can clean generated build cache in two ways:

### From the IDE

Use the **Compile** dropdown and choose:

**Clean CGARM Build Cache...**

### From the command line

```bash
cgarm-build myproject.proj --clean
```

This removes generated CGARM cache/intermediate files while preserving:

- project source files
- GUI Designer files
- project settings
- previously built `.app` files

---

## Editor Quality-of-Life Features

- Code folding
- Shift-click fold expansion for nested blocks
- Alt + Up / Alt + Down scrolling
- Build-aware source saving
- Syntax highlighting with large-file safeguards

---

## Current Status

### Working

- V1 applet build path
- CGARM V2 build path
- GUI projects
- standalone `cgarm-build`
- `libcgarm.a`
- incremental compilation
- automatic RAM resize workflow
- assembly output generation

### In Progress / Future Improvements

- additional IDE polish
- continued CGARM library expansion
- further tooling cleanup
- ongoing testing and hardening

---

## Why This Exists

SIDBOX is about making software for a custom platform approachable without hiding the interesting parts.

The goal is to provide:

- a friendly IDE
- a working command-line toolchain
- support for experimentation
- enough automation that developers can focus on writing applets rather than wrestling the build system

---

## Contributing

This project is still evolving.

Bug reports, testing feedback and tooling improvements are welcome.

If you are developing CGARM V2 applets, please report:

- build issues
- IDE integration issues
- library compatibility problems
- runtime issues on SIDBOX hardware

---

## License

Add your preferred license here.

Example:

```text
MIT License
```

or

```text
All rights reserved
```

---

## Acknowledgements

- SIDBOX platform development
- CGARM runtime and tooling work
- Qt
- GNU Arm Embedded toolchain
- LLVM LLD

---

<div align="center">

**CoderGirl IDE / SIDBOX IDE**  
Custom tools for building software on SIDBOX.

</div>

## New (experimental): Advanced Tilemap Editor

See `TILEMAP-START-HERE.md` for the visual two-layer map editor and the new foreground 960x320 mirrored horizontal ring. The background remains static at 480x320. Hardware validation remains pending.
