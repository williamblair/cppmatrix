# Makefile for cppmatrix

CC = g++

BIN = cppmatrix

SOURCES = src/main.cpp src/console_matrix.cpp

OBJS = build/main.o build/console_matrix.o

BUILDDIR = build

LIBS = -lncurses

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(OBJS) -o $(BIN) $(LIBS)

build/%.o: src/%.cpp $(BUILDDIR)
	$(CC) -c -o $@ $<

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

clean:
	rm -rf build/* $(BIN)
