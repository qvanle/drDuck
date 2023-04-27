all: clearscreen run
	
.PHONY: all run
run: BUILD 
	build/ShowMePls

BUILD:
	cmake -B build/
	make -C build

DEBUG:
	cmake -DCMAKE_C_FLAGS="-g" -DCMAKE_CXX_FLAGS="-g" -B build/ 
	make -C build

.PHONY: clearscreen
clearscreen:
	clear

