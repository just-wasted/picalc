#!/usr/bin/env bash

set -e

BUILD_DIR=build
TOOLCHAIN_FILE=toolchain.cmake

if [ "$1" == "clean" ]; then
    echo "Cleaning build folder..."
    rm -rf "$BUILD_DIR"
    exit 0
fi

mkdir -p "$BUILD_DIR"

cmake -B "$BUILD_DIR"\
	-S . \
	-DCMAKE_TOOLCHAIN_FILE="$TOOLCHAIN_FILE" \
	-DCMAKE_BUILD_TYPE=Debug \
	-DCMAKE_EXPORT_COMPILE_COMMANDS=1

cmake --build "$BUILD_DIR" -- VERBOSE=1

ln -sf "$BUILD_DIR/compile_commands.json" compile_commands.json
