#!/bin/sh
# SPDX-License-Identifier: CC0-1.0

if [ -z "$DEVKITPRO" ] || [ -z "$DEVKITARM" ]; then
    echo "Environment variables not set: DEVKITPRO DEVKITARM" >&2
    exit 1
fi

rm -rf build/
cmake -B build . -DCMAKE_TOOLCHAIN_FILE=toolchain-gcc.cmake "$@"
