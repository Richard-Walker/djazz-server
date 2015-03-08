


CPPSRC = buttonparser.cpp \
	iparser.cpp \
	irreceiveparser.cpp \
	irsend.cpp \
	manager.cpp \
	pir.cpp \
	pirlib2.cpp \
	sendirparser.cpp \
	boolsig.cpp \
	ipir.cpp \
	irlearnparser.cpp
	
CSRC = hidlinux.c pt.c
CCFLAGS = -std=c++0x -Wall
#CCFLAGS = -std=c++11 -Wall
CFLAGS = -Wall -g
OBJ = $(CPPSRC:.cpp=.o) $(CSRC:.c=.o)

OUT = libpir.a

LIBS = -Llibusb-1.0.so.0

CCC = g++
CC = gcc

default: $(OUT)

.c.o:
	$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@

.cpp.o:
	$(CCC) $(INCLUDES) $(CCFLAGS) -c $< -o $@

$(OUT): $(OBJ)
	ar rcs $(OUT) $(OBJ)

clean:
	rm -f $(OBJ) $(OUT) Makefile.bak 
