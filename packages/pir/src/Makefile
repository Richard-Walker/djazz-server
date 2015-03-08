CPPSRC = pirlib2/buttonparser.cpp \
	pirlib2/iparser.cpp \
	pirlib2/irreceiveparser.cpp \
	pirlib2/irsend.cpp \
	pirlib2/manager.cpp \
	pirlib2/pir.cpp \
	pirlib2/pirlib2.cpp \
	pirlib2/sendirparser.cpp \
	pirlib2/boolsig.cpp \
	pirlib2/ipir.cpp \
	pirlib2/irlearnparser.cpp \
	main.cpp
	
CSRC = pirlib2/hidlinux.c pirlib2/pt.c

CCFLAGS = -std=c++0x -Wall -I./pirlib2
LDFLAGS = -lpthread -lusb-1.0 -lrt -ludev
CFLAGS = -Wall 
OBJ = $(CPPSRC:.cpp=.o) $(CSRC:.c=.o)


OUT = ../bin/pir

LIBS = -Llibusb-1.0.so.0

CCC = g++
CC = gcc

default: $(OUT)
.c.o:
	$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@

.cpp.o:
	$(CCC) $(INCLUDES) $(CCFLAGS) -c $< -o $@

$(OUT): $(OBJ)
	$(CCC) $(OBJ) $(LDFLAGS) -o $(OUT) 
	strip $(OUT)


clean:
	rm -f $(OBJ) $(OUT) Makefile.bak 
