CC = g++
CPPFLAGS = -g -std=c++17 -I include
# -fpic
SRC_FILES = $(wildcard src/*/*.cpp) $(wildcard src/*/*/*.cpp) $(wildcard src/*/*/*/*.cpp)
# $(wildcard src/*.cpp)
LINKER_FLAGS = -lncurses

.PHONY:	linux

linux:
	$(CC) $(CPPFLAGS) src/main.cpp $(SRC_FILES) $(LINKER_FLAGS)