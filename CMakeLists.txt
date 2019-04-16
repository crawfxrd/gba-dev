# SPDX-License-Identifier: MPL-2.0

cmake_minimum_required(VERSION 3.12)

project(untitled
    VERSION 0.0.1
    DESCRIPTION "GBA programming"
    LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(devkitPro)

add_executable(untitled src/main.cpp)
make_gba_rom(untitled)
