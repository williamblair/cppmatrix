# Makefile for cppmatrix
# Windows version - includes the location of the ncurses 
# library for windows

# tested build in both cmd and msys, however only
# ran in cmd

CC = mingw32-g++

BIN = cppmatrix.exe

SOURCES = ../src/main.cpp ../src/console_matrix.cpp

OBJS = build/main.o build/console_matrix.o

BUILDDIR = build

# change this to the location of the ncurses for
# windows library
NCURSDIR = C:\MinGW_pc\external_libs\ncurses_windows
INCDIRS  = -I$(NCURSDIR)\include
LIBDIRS  = -L$(NCURSDIR)\lib
LIBS     = -lncursesw

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(OBJS) -o $(BIN) $(INCDIRS) $(LIBDIRS) $(LIBS)

build/%.o: ../src/%.cpp $(BUILDDIR)
	$(CC) -c -o $@ $< $(INCDIRS)

$(BUILDDIR):
	mkdir $(BUILDDIR)

clean:
	del $(BIN) build\*
	rmdir build
