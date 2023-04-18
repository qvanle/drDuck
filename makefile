all: clearscreen run
	
.PHONY: all run
run: DEBUG 
	build/ShowMePls

BUILD:
	cmake -B build/
	make -C build

DEBUG:
	cmake -DCMAKE_BUILD_TYPE=DEBUG -B build/ 
	make -C build

.PHONY: clearscreen
clearscreen:
	clear

