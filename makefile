CC = g++
SOURCE := $(wildcard src/*.cpp)

default: build

build: $(SOURCE)
	$(CC) -O3 $? -o out/build/$@

debug: src/*.cpp
	$(CC) -D_DEBUG -Wall src/$@.cpp -o out/debug/$@

%: src/%.cpp
	[ -e "out/debug_$@" ] || mkdir "out/debug_$@"; \
	$(CC) -D_DEBUG_$@ -Wall src/$@.cpp -o out/debug_$@/$@ && ./out/debug_$@/$@