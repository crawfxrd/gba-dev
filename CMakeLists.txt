# SPDX-License-Identifier: MPL-2.0

#
# Copyright (c) 2019 Tim Crawford <crawfxrd@gmail.com>
#

cmake_minimum_required(VERSION 3.13)

if(NOT DEFINED CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build, options are: Debug Release")
endif()

project(untitled
    VERSION 0.0.1
    DESCRIPTION "GBA programming"
    LANGUAGES CXX ASM)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(devkitPro)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Target to compile all 16-bit THUMB code
add_library(thumb OBJECT
    src/input.cpp
    src/main.cpp
    # Headers
    src/base.hpp
    src/bits.hpp
    src/input.hpp
    src/types.hpp)
target_compile_options(thumb PRIVATE -mthumb)

# Target to compile all 32-bit ARM code
add_library(arm OBJECT
    src/isr.cpp
    # Headers
    src/types.hpp)
target_compile_options(arm PRIVATE -marm)

add_executable(untitled $<TARGET_OBJECTS:thumb> $<TARGET_OBJECTS:arm>)
target_include_directories(untitled PRIVATE src)
target_link_options(untitled PRIVATE -Wl,-Map,untitled.map)
make_gba_rom(untitled)
