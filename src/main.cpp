/*
  main.cpp - file to implement the MatrixApp Class for cppmatrix
  the meat of this application is locatd in console_matrix.cpp

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 1, or (at your option)
  any later version.                                                 
                                                                        
  This program is distributed in the hope that it will be useful,     
  but WITHOUT ANY WARRANTY; without even the implied warranty of      
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the       
  GNU General Public License for more details.                        
                                                                        
  You should have received a copy of the GNU General Public License   
  along with this program; if not, write to the Free Software         
  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.           

*/

#include <iostream>
#include <ncurses.h>
#include <cstdlib>
#include <ctime>

#include <unistd.h> // for getopt()

#include "console_matrix.hpp"

int main(int argc, char *argv[])
{
  MatrixApp m(argc, argv);
  m.run();

  return 0;
}
