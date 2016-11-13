/*
 * console_matrix.hpp - header for console_matrix.cpp,
 * class for running the cppmatrix application

     This program is free software; you can redistribute it and/or modify *
 *   it under the terms of the GNU General Public License as published by *
 *   the Free Software Foundation; either version 1, or (at your option)  *
 *   any later version.                                                   *
 *                                                                        *
 *   This program is distributed in the hope that it will be useful,      *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of       *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        *
 *   GNU General Public License for more details.                         *
 *                                                                        *
 *   You should have received a copy of the GNU General Public License    *
 *   along with this program; if not, write to the Free Software          *
 *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.            *


 */

#include <iostream>
#include <ncurses.h>
#include <vector>
#include <cstdlib>
#include <ctime>

#include <unistd.h> // for getopt()

#ifndef BJ_MATRIX
#define BJ_MATRIX

#define MAX_COL_HEIGHT 15 // max number of symbols in one group

  typedef struct CodeColumn
  {
    bool use;       // bool for if the column is being used or not
    bool bold;      // bool for wether to bold the text or not
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
      struct timespec myTime;

      //int **screen; // matrix of each location on the screen
      std::vector<CodeColumn> c; // vector containing a bunch of code columns
      unsigned int color;        // the color of the code columns
  };

#endif
