CC = g++
CFLAGS = -c -I ../../openbabel-src/src/include -I ../../openbabel-src/build/include
LDFLAGS = -L ../../openbabel-src/build/lib/libopenbabel.so

P_SRC = ../src/

all: conv

conv: conv.o
	$(CC) $(LDFLAGS) conv.o -o conv

conv.o: $(P_SRC)conv.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) $(P_SRC)conv.cpp

clean:
	rm -rf conv.o conv
