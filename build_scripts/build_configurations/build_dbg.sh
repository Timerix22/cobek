#!/bin/bash

source build_scripts/init.sh

print "${CYAN}=============[build_dbg]==============\n"
clear_dir "$OUTDIR"
clear_dir "$OBJDIR"
compile_c "$BUILD_DBG_C_ARGS" "$SRC_C"
compile_cpp "$BUILD_DBG_CPP_ARGS" "$SRC_CPP"
link "$BUILD_DBG_CPP_ARGS $BUILD_DBG_LINKER_ARGS" "$BUILD_FILE"
