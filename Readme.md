# cppmatrix
cppmatrix - written by BJ Blair; inspired by Chris Allegretta's
cmatrix. Visit Chris's website at http://www.asty.org/cmatrix/

RUNNING:
-------------------
usage:

   cppmatrix [-s speed] [-c color] [-m height]

where 'speed' is an approximate FPS cppmatrix tries to run at (defaults to 20),
and 'color' is a string of the color to display the text in (defaults to green)
supported colors are:

    green, blue, red, yello, magenta/purple, cyan, white, and black

-m 'height' refers to the max height of character columns (default is 15)

example usage:

    cppmatrix -s 40 -c blue -m 20


COMPILING:
-------------------
You will need g++ and make to compile (technically make is optional - it's not
that hard to compile by hand!)
For other systems, you will need to install the ncurses development libraries,
installed with:

    sudo apt-get install libncurses5-dev libncursesw5-dev

for debian/ubuntu systems; modify for your package manager.
Make sure you

    sudo ldconfig

to update your libraries!
Then type:

    make clean
    make

which should give you a usable in this directory. You can then place the
program somwhere like /usr/local/bin so you can run cppmatrix wherever!

COPYRIGHT
----------
Released under GNU General Public License - see 'COPYING'; I have no 
affiliation with 'the Matrix'
