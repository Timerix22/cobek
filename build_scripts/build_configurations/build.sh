#!/bin/bash

source build_scripts/init.sh

print "${CYAN}===============[build]================\n"
clear_dir "$OUTDIR"
clear_dir "$OBJDIR"
compile_c "$BUILD_C_ARGS" "$SRC_C"
compile_cpp "$BUILD_CPP_ARGS" "$SRC_CPP"
ar x deps/* --output=obj
link "$BUILD_CPP_ARGS $BUILD_LINKER_ARGS" "$BUILD_FILE"
