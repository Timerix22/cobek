#!/bin/bash

source build_scripts/init.sh

clear_dir "$OUTDIR"
clear_dir "$OBJDIR"
bash build_scripts/build_deps.sh