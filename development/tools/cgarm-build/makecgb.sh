#!/bin/bash

cd /mnt/LinuxDatas/work/SidboxIDE/SidboxIDE

g++ -std=c++17 -O2 -Wall -Wextra \
development/tools/cgarm-build/cgarm-build.cpp \
-o idelibs/tools/bin/cgarm-build
