#!/bin/bash

cd kerep
if [ ! -f "bin/kerep.a" ]; then
    exec make "$KEREP_BUILD_TASK"
fi
cp bin/kerep.a ../obj/
printf "${GREEN}copied ${CYAN}kerep.a\n"
cd ..
