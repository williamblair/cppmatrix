/*
  main.cpp - file to implement the MatrixApp Class for cppmatrix
  the meat of this application is locatd in console_matrix.cpp         
*/

#include "console_matrix.hpp"

int main(int argc, char *argv[])
{
  MatrixApp m(argc, argv);
  m.run();

  return 0;
}
