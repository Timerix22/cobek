#!/bin/bash
source build_scripts/colors.sh

printf "${CYAN}=============[build_deps]=============\n"
mkdir -p deps
cd ../kerep/

if [ ! -f "bin/kerep.a" ]; then
    printf "${YELLOW}../kerep/bin/kerep.a doesn't exist\n"
    while true; do
        printf "${WHITE}build it from source? (y/n) "
        read answ
        case $answ in
            [Yy] ) break;;
            [Nn] ) exit;;
            * ) printf "${RED}incorrect answer\n";;
        esac
    done
    make build_static_lib
fi
cp bin/kerep.a ../cobek/deps/
printf "${GREEN} copied ${CYAN}kerep.a\n"
cd ../cobek
