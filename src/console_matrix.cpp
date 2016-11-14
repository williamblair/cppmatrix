/*
 * console_matrix.cpp - contains the meat of the
 * cppmatrix program - implements the class functions
 * of MatrixApp

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
#include <cstdlib>
#include <ctime>

#include <unistd.h> // for getopt()

#include "console_matrix.hpp"

MatrixApp::MatrixApp(int argc, char *argv[])
{
  w=0; h=0;

  FPS = 20; // Estimate of how many times per second the screen updates
  COL_HEIGHT = 15; // default max height for columns

  srand(time(0)); // seed time

  // init the ncurses screen
  initscr();

  // set the default color
  // colors defined as follows:
  // COLOR_BLACK	0
  // COLOR_RED	1
  // COLOR_GREEN	2
  // COLOR_YELLOW	3
  // COLOR_BLUE	4
  // COLOR_MAGENTA	5
  // COLOR_CYAN	6
  // COLOR_WHITE	7
  color = COLOR_GREEN;

  // get color option and speed option
  parseArgs(argc, argv);
/*
	printw("Out of parse args!\n");
	refresh();
	getchar();
*/
  // initialize color
  if( has_colors() ){
    start_color();
    use_default_colors();        // so we can use the current background
    init_pair(1, color, -1);
    init_pair(2, COLOR_WHITE, -1);
  }

  // set speed
  myTime.tv_sec = 0;
  myTime.tv_nsec = 1000000000L/FPS; // FPS using nanoseconds

  // get size of window
  // notice (y,x) not (x,y)
  getmaxyx(stdscr,h,w);

  // turn off cursor
  curs_set(0);

  // allocate size for the code columns
  c.reserve(w); // enough for 1 for each column

  // initialize each column
  for(int i=0; i<w; i++)
  {
    c[i].use = false;
    c[i].bold = false;
    c[i].col = i;
    c[i].h   = rand() % COL_HEIGHT;
    c[i].topRow    = 0;
    c[i].bottomRow = 0;
  }
/*t
  printw("Initialized column!\n");
  refresh();
  getchar();

  printw("got char entry!\n");
  refresh();
  getchar();
  // clear the screen
  clear();
*/
}

/* read arguments to set options */
void MatrixApp::parseArgs(int argc, char *argv[])
{
  char *colorStr = NULL;    // string to hold color option
  char *speedStr = NULL;    // string to hold speed option
	char *colStr   = NULL;    // string to hold column height option
  std::string cppColorStr;  // to use simple compare funcs
  int c;                    // holds status of getopt

  opterr = 0; // a ncurses variable - options error

  /* check for passed options */
  while((c = getopt(argc, argv, "c:s:m:h")) != -1)
  {
    switch(c)
    {
      case 'c':
        colorStr = optarg;
        break;
      case 's':
        speedStr = optarg;
				break;
			case 'm':
				colStr = optarg;
				break;	
			case 'h':
				printUsage(argc, argv);
				exit(0);
				break;
      case '?':
        if(optopt == 'c'){
          std::cerr << "Option -" << optopt << "requires a color as an arg\n";
        }
       	else if(optopt == 's'){
          std::cerr << "Option -" << optopt << "requires an int > 0 for FPS as an arg\n";
	      }
        break;
      default:
				printUsage(argc, argv);
				exit(0);
        break;
    }
  }

  /* if a color arg was passed in change the color we use */
  if( colorStr != NULL )
  {
    /* change color based on passed in value */
    cppColorStr = colorStr;

    /* wish i could use a switch statement... :/ */
    if(cppColorStr.compare("green") == 0)           color = COLOR_GREEN;
    else if(cppColorStr.compare("blue") == 0)       color = COLOR_BLUE;
    else if(cppColorStr.compare("red")  == 0)       color = COLOR_RED;
    else if(cppColorStr.compare("yellow") == 0)     color = COLOR_YELLOW;
    else if(cppColorStr.compare("magenta") == 0 ||
            cppColorStr.compare("purple") == 0)     color = COLOR_MAGENTA;
    else if(cppColorStr.compare("cyan") == 0)       color = COLOR_CYAN;
    else if(cppColorStr.compare("white") == 0)      color = COLOR_WHITE;
    else if(cppColorStr.compare("black") == 0)      color = COLOR_BLACK;
    else{
      /* show what the color got switched to */
      printw("Error: '%s' isn't a valid color!\n", colorStr);
      printw("Valid colors are:\n----------------------\n");
      printw("green\nblue\nred\nyellow\nmagenta/purple\ncyan\nwhite\nblack\n");
      printw("\nDefaulting to green...\n");
      refresh();
      getchar();
    }
  }

  /* set speed if given */
  if(speedStr != NULL)
  {
    int inFPS = (int)strtol(speedStr, NULL, 10);
    if( inFPS > 0 )
//      FPS = (int)strtol(speedStr, NULL, 10);
			FPS = inFPS;
    else {
      printw("Invalid FPS as an arg! try a number > 0...\n");
      refresh();
      getchar();
    }

  }

	/* set column height if given */
	if(colStr != NULL)
	{
		int inColHeight = (int)strtol(colStr, NULL, 10);
		if( inColHeight > 0 ){
			COL_HEIGHT = inColHeight;
		}
		else {
			printw("Invalid max column height as an arg! try a number > 0...\n");
			refresh();
			getchar();
		}
	}

  return;
}

void MatrixApp::resetCol(const int colNum)
{
  c[colNum].use = false;
  c[colNum].bold = false;
  c[colNum].col = colNum;

  c[colNum].h   = rand() % COL_HEIGHT;

  c[colNum].topRow    = 0;
  c[colNum].bottomRow = 0;

  // fill the column with spaces to clear it
  for(int i=0; i<=h; i++)
    mvaddch(i,colNum,' ');

  // randomly set bold
  if(rand() %10 >= 8)
    c[colNum].bold = true;

  return;
}

void MatrixApp::printCol(const int colNum)
{
  int letter; // the random letter to print

  // print spaces before top row
  for(int i=0; i<c[colNum].topRow; i++)
    mvaddch(i, c[colNum].col, ' '); // space

  // TODO - test putting refresh in more places
  refresh();

  if(c[colNum].bold) attron(A_BOLD);
  else               attroff(A_BOLD);

  //print the random chars between top and bottom row
  // TODO - print cooler ascii chars and stuff
  for(int i=c[colNum].topRow; i<=c[colNum].bottomRow-1; i++) {

    // generate a random char and make sure it's in the right scope
    letter = rand()%126;
    if( letter < 33 )
      letter = letter + 33; // 94 = difference between highest and lowest val

    mvaddch(i, c[colNum].col, (char)letter); // random char
  }

  // add the white leading character
  if(has_colors() != FALSE)
    attron(COLOR_PAIR(2));

  // generate a random char and make sure it's in the right scope
  letter = rand()%126;
  if( letter < 33 )
    letter = letter + 33; // 94 = difference between highest and lowest val
  mvaddch(c[colNum].bottomRow,c[colNum].col,(char)letter);

  // turn off white and put back to green
  if(has_colors() != FALSE) {
    attroff(COLOR_PAIR(2));
    attron(COLOR_PAIR(1));
  }

  refresh();

  // print the bottom 'cursor'
  //mvaddch(c[colNum].bottomRow+1, c[colNum].col, (char)178); // hopefully a terminal looking block
  //mvaddch(c[colNum].bottomRow+1, c[colNum].col, '_');

  // move down - and test if need to expand height
  if( c[colNum].bottomRow >= c[colNum].h ) // if the bottom row is down far enought to fit all chars
    (c[colNum].topRow)++;

  // if the bottom row hasn't reached the bottom of the screen
  if( c[colNum].bottomRow < h)
    (c[colNum].bottomRow)++;

  // test if both top and bottom have reached the bottom of the screen
  if( c[colNum].topRow >= h && c[colNum].bottomRow >= h)
    resetCol(colNum); // reset the column

  // debugging
  //getchar(); // making wait
  refresh();

  return;
}

void MatrixApp::run(void)
{
  int curCol = 0; // current column we're scanning
  clear();

  if(has_colors() != FALSE){
    attron(COLOR_PAIR(1)); // turn on color
  }

  while(1)
  {
    // scan each column
    for(curCol=0; curCol < w; curCol++)
    {
      // if the column bool is set true
      if(c[curCol].use)
      {
        //printw("Print stuff here!\n");
        printCol(curCol);
        refresh();
      }
      // if the column bool is set false
      else
      {
        if( (rand() % 1000) > 980) // chance of using column
        {
          // INIT COLUMN
          c[curCol].use = true;
        }
        else
        {
          c[curCol].use = false;

          // PRINT ALL SPACES
          for(int i=0; i<h; i++)
            mvaddch(i,curCol,' ');

        } // end else for rand() %2 for use column
      } // end column bool false if
    } // end for each column

    // test 1 refresh
    refresh();

    nanosleep(&myTime, NULL); // NULL is optional error timespec struct

  } // end while 1

  endwin();
  return;
}

void MatrixApp::printUsage(int argc, char *argv[])
{
	endwin();
	std::cout << "Usage: " << argv[0] << " [-s speed] [-c color]" << std::endl;
	std::cout << "-s [speed]: how fast the matrix updates (in Frames Per Second); defaults to 20\n";
	std::cout << "-c [color]: color to display the matrix in; defaults to green\n";
	std::cout << "-m [height]: maximum height of a column of randomized characters (default 15)\n";
	return;
}

