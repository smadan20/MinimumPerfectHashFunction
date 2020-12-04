CXX = g++
CC = gcc
CXX_FLAGS = -g -Wall -std=c++11 -DNDEBUG -I ~/include -L ~/lib
main: main.cpp MPHF.h xxhash.h xxhash.o
	$(CXX) main.cpp MPHF.cpp xxhash.o -o main $(CXX_FLAGS) -lncurses -lsdsl -ldivsufsort -ldivsufsort64
xxhash.o: xxhash.c
	$(CC) -c xxhash.c -o xxhash.o
clean:
	rm -rf *.o main