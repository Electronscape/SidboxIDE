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
