prefix = .
bindir = $(prefix)
srcdir = $(prefix)
OS = $(shell uname -s)
CC = g++

CFLAGS = -g

all:	fridgemadness
fm_src.o:	fm_src.h fm_src.cpp
	$(CC) $(CFLAGS) -c fm_src.cpp
fridgemadness: fm_src.o fridgemadness.cpp
	$(CC) $(CFLAGS) -o  fridgemadness fridgemadness.cpp fm_src.o
clean: 
	rm -f *.o fridgemadness
