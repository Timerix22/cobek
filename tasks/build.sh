#!/bin/bash

source build_scripts/init.sh

print "${CYAN}===============[build]================\n"
clear_dir "$OUTDIR"
clear_dir "$OBJDIR"

cd kerep
make build_static_lib
cp bin/kerep.a ../obj/
printf "${GREEN}copied ${CYAN}kerep.a\n"
cd ..

compile_c "$BUILD_C_ARGS" "$SRC_C"
compile_cpp "$BUILD_CPP_ARGS" "$SRC_CPP"
link "$BUILD_CPP_ARGS $BUILD_LINKER_ARGS" "$BUILD_FILE"
