#!/bin/bash

cd kerep
make $KEREP_BUILD_TARGET
cp bin/kerep.a ../obj/
printf "${GREEN}copied ${CYAN}kerep.a\n"
cd ..