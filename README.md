Gaussian Elimination
----------------------------------------------------------------------
Author: Jonah Miller (jonah.maxwell.miller@gmail.com)
Time-stamp: <2013-08-15 22:39:48 (jonah)>

This is my implementation of the Gaussian Elimination algorithm.
There are a number of pieces:
 ---- dynamic_array.hpp is a class that encapsulates dynamic arrays.
 ---- gaussian_system.cpp/hpp is a library that
        implements a class to hold a matrix equation.
        Most importantly, it implements pivoting and row-swapping.
 ---- gaussian_elimination.cpp/hpp implements the algorithms for
        gaussian elimination and back substitution.
 ---- Test drivers exist for each of these components.

To just build the libraries so you can use them in your code,
use:
    make all

Currently the only compiler supported is the GNU compiler, G++. However, if you
open up the Makefile with a text editor and change the parameters to your system,
it'll probably work.

This also generates test drivers. Thanks for reading!
