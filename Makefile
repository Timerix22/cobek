######################################
######       Build tasks       #######
######################################

all: build_exec_dbg

# creates executable using profiling info generated by profile
build_exec: profile
	@cbuild/call_task.sh build_exec  2>&1 | tee -a make_raw.log

# creates executable with debug info and no optimizations
build_exec_dbg:
	@cbuild/call_task.sh build_exec_dbg 2>&1 | tee make_raw.log

######################################
######       Launch tasks      #######
######################################

# executes $EXEC_FILE
exec: build_exec
	@cbuild/call_task.sh exec 2>&1 | tee -a make_raw.log

# executes $EXEC_FILE
exec_dbg: build_exec_dbg
	@cbuild/call_task.sh exec 2>&1 | tee -a make_raw.log

# executes $EXEC_FILE with valgrind memory checker
valgrind: build_exec_dbg
	@cbuild/call_task.sh valgrind 2>&1 | tee -a make_raw.log

# generates profiling info
profile:
	@cbuild/call_task.sh profile 2>&1 | tee make_raw.log

# compiles program with -pg and runs it with gprof
# uses gprof2dot python script to generate function call tree  
gprof:
	@cbuild/call_task.sh gprof 2>&1 | tee make_raw.log
	
# compiles executable with sanitizers and executes it to find errors and warnings
sanitize:
	@cbuild/call_task.sh sanitize 2>&1 | tee make_raw.log

######################################
######       Other tasks       #######
######################################

# deletes generated files
clean:
	@cbuild/call_task.sh clean 2>&1 | tee make_raw.log

# removes all unreadable characters copied from stdio
fix_log:
	sed 's/[^[:blank:][:print:]]//g' make_raw.log \
		| sed 's/\[0;[0-9][0-9]m//g' \
		| sed 's/\[0;[0-9]m//g' \
		| sed 's/\[[0-9][0-9]m//g' \
		| sed 's/\[[0-9]m//g' \
		| sed 's/  H  //g' \
		| sed 's/\[3gH  //g' \
		> make_fixed.log

# recompile kerep.a in the next build task
rebuild_kerep: 
	@cbuild/call_task.sh rebuild_kerep
