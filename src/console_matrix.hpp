/*
 * console_matrix.hpp - header for console_matrix.cpp,
 * class for running the cppmatrix application\
 *
 * */

#ifdef _WIN32
  #include <ncursesw/ncurses.h>
#else
  #include <ncurses.h>
#endif

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <unistd.h> // for getopt()

#ifndef BJ_MATRIX
#define BJ_MATRIX

  typedef struct CodeColumn
  {
    bool use;       // bool for if the column is being used or not
    bool bold;      // bool for whether to bold the text or not
    int col;        // the column this group is in
    int h;          // height of the codeColumn
    int topRow;     // the location of the top of the code
    int bottomRow;  // the location of the bottom of the code
  } CodeColumn;

  class MatrixApp
  {
    public:
      MatrixApp(int argc, char *argv[]);
      void run(void);
			void printUsage(int argc, char *argv[]);
    protected:
      void resetCol(const int colNum); // reset column
      void printCol(const int colNum);
      void parseArgs(int argc, char *argv[]);
    private:
      int w; // the width of the screen
      int h; // the height of the screen

      int FPS; // speed of the program
      int COL_HEIGHT; // how many characters a block of text is tall
      struct timespec myTime;

      std::vector<CodeColumn> c; // vector containing a bunch of code columns
      unsigned int color;        // the color of the code columns
  };

#endif
