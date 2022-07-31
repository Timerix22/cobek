######      Building tasks     #######
build: 
	@build_scripts/build_configurations/build.sh

build_dbg: 
	@build_scripts/build_configurations/build_dbg.sh

######      Testing tasks      #######
test: build
	@build_scripts/build_configurations/test.sh

test_valgrind: build_dbg
	@build_scripts/build_configurations/test_valgrind.sh

all: build
