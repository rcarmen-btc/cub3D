mkdir -p ../bin/linux_debug
make  compile_flags="-O0 -g" \
	--directory=../bin/linux_debug \
	--makefile=../../project/Makefile