# SPDX-License-Identifier: MPL-2.0

cmake_minimum_required(VERSION 3.13)

if(NOT DEFINED CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build, options are: Debug Release")
endif()

project(untitled
    VERSION 0.0.1
    DESCRIPTION "GBA programming"
    LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(devkitPro)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(untitled
    src/base.hpp
    src/bits.hpp
    src/input.cpp
    src/input.hpp
    src/main.cpp
    src/types.hpp)

target_include_directories(untitled PRIVATE src)
target_link_options(untitled PRIVATE -Wl,-Map,untitled.map)
make_gba_rom(untitled)
