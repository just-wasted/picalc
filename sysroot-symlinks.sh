#!/usr/bin/env bash

# helper script to configure the sysroot from the raspi some with symlinks

argc=$#

if [[ argc -ne 1 ]]; then
    echo "Usage: sysroot-symlinks </path/to/sysroot>"
    exit 1
fi

sysroot=$(realpath "$1")
if [ ! -e "$sysroot" ]; then
    echo "Path not found."
    exit 1
fi

ln -s -v -T "$sysroot"/usr/lib "$sysroot"/lib

ln -s -v -T "$sysroot"/usr/lib/aarch64-linux-gnu "$sysroot"/lib64

ln -s -v -T "$sysroot"/usr/lib/aarch64-linux-gnu "$sysroot"/usr/lib64

ln -s -v -T "$sysroot"/usr/lib/aarch64-linux-gnu/ld-linux-aarch64.so.1 \
    "$sysroot"/usr/lib/ld-linux-aarch64.so.1
