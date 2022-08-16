#!/bin/bash

source build_scripts/pre_build.sh

print "${CYAN}===============[build]================\n"
compile_c "$BUILD_C_ARGS" "$SRC_C"
compile_cpp "$BUILD_CPP_ARGS" "$SRC_CPP"
link "$BUILD_CPP_ARGS $BUILD_LINKER_ARGS" "$BUILD_FILE"
