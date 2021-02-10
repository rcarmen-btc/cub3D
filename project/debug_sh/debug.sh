mkdir -p ../../bin/linux_debug
#make fclean \
#	--directory=../../bin/linux_debug \
#	--makefile=../../project/Makefile

make COMPILE_FLAGS="-O0 -g" \
	--directory=../../bin/linux_debug \
	--makefile=../../project/Makefile
