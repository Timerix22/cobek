#!/bin/bash
source build_scripts/colors.sh

printf "${CYAN}=============[build_deps]=============\n"

cd kerep
if [ ! -f "bin/kerep.a" ]; then
    printf "${YELLOW}kerep/bin/kerep.a doesn't exist\n"
    make build_static_lib
fi
cp bin/kerep.a ../obj/
printf "${GREEN}copied ${CYAN}kerep.a\n"
cd ..
