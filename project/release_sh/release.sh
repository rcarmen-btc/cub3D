mkdir -p ../../bin/linux_release




make compile_flags="-O3" \
	--directory=../../bin/linux_release \
	--makefile=../../project/Makefile