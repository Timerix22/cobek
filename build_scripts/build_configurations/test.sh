#!/bin/bash

source build_scripts/init.sh

print "${CYAN}================[test]================\n"
cd $OUTDIR
./$BUILD_FILE
cd ..
