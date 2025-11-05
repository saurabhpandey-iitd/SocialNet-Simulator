#!/bin/bash
# ===========================
# Compile and Run Social Network Simulator (Linux/macOS)
# ===========================

CPP_COMPILER=g++
SRC=main.cpp
HEADER=social_network.hpp 
OUT=social_network 

echo "Compiling $SRC ..."
$CPP_COMPILER -std=c++17 "$SRC" -o "$OUT"

if [ $? -ne 0 ]; then
    echo "Compilation failed!"
    exit 1
fi

echo
echo "Running Social Network Simulator..."
echo "==========================="
./"$OUT"
