#!/bin/bash

source build_scripts/init.sh

print "${CYAN}===========[test_valgrind]============\n"
cd $OUTDIR
valgrind $VALGRIND_ARGS ./$BUILD_DBG_FILE
cat valgrind.log
cd ..
