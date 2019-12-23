COMP=g++
CFLAGS=-std=c++17
COUT=-o cm

all:
	${COMP} ${CFLAGS} *.cpp ${COUT}
