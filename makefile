CC = g++
SOURCE := $(wildcard src/*.cpp)

default: build

build: $(SOURCE)
	$(CC) -O3 $? -o $@

debug: src/*.cpp
	$(CC) -D_DEBUG -Wall src/$@.cpp -o $@

%: src/%.cpp
	$(CC) -D_DEBUG -Wall src/$@.cpp -o $@