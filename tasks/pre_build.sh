#!/bin/bash

cd kerep
make $KEREP_BUILD_TASK
cp bin/kerep.a ../obj/
printf "${GREEN}copied ${CYAN}kerep.a\n"
cd ..