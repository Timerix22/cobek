#!/bin/bash

source build_scripts/pre_build.sh

print "${CYAN}=============[build_dbg]==============\n"
compile_c "$BUILD_DBG_C_ARGS" "$SRC_C"
compile_cpp "$BUILD_DBG_CPP_ARGS" "$SRC_CPP"
link "$BUILD_DBG_CPP_ARGS $BUILD_DBG_LINKER_ARGS" "$BUILD_FILE"
