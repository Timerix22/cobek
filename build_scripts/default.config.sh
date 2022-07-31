#!/bin/bash

OUTDIR=bin
OBJDIR=obj
CMP_C=gcc
CMP_CPP=g++
STD_C=c11
STD_CPP=c++17
WARN_C="-Wall -Wno-discarded-qualifiers" #-Wextra
WARN_CPP="-Wall -Wno-unused-variable -Wno-return-type" #-Wextra
SRC_C="$(    find src -name '*.c')"
SRC_CPP="$(  find src -name '*.cpp')"
TESTS_C="$(  find tests -name '*.c')"
TESTS_CPP="$(find tests -name '*.cpp')"
VALGRIND_ARGS="-s --log-file=valgrind.log --read-var-info=yes --track-origins=yes --fullpath-after=cobek/ --leak-check=full --show-leak-kinds=all"

# build
TEST_FILE=cb2c.com
BUILD_C_ARGS="-O2"
BUILD_CPP_ARGS="$BUILD_C_ARGS"
BUILD_LINKER_ARGS=""

# build_dbg
TEST_DBG_FILE=$TEST_FILE
BUILD_DBG_C_ARGS="-O0 -g"
BUILD_DBG_CPP_ARGS="$BUILD_DBG_C_ARGS"
BUILD_DBG_LINKER_ARGS=""
