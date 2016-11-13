# Makefile for cppmatrix

CC = g++

BIN = cppmatrix

SOURCES = src/main.cpp src/console_matrix.cpp

OBJS = build/main.o build/console_matrix.o

LIBS = -lncurses

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(OBJS) -o $(BIN) $(LIBS)

build/%.o: src/%.cpp
	$(CC) -c -o $@ $<

clean:
	rm -rf build/* $(BIN)
