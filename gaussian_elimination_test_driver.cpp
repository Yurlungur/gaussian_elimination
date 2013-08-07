// gaussian_elimination_test_driver.cpp

// Author: Jonah Miller (jonah.maxwell.miller@gmail.com)
// Time-stamp: <2013-08-06 18:29:14 (jonah)>

// This file tests the gaussian elimination library. Just runs a
// couple of simple tests.

// ----------------------------------------------------------------------


// Includes
#include <iostream>
#include <fstream>
#include "gaussian_system.hpp"
#include "gaussian_elimination.hpp"
#include <float.h>
using namespace std;
// ----------------------------------------------------------------------


// Main function
// ----------------------------------------------------------------------
int main() {
  cout << "Testing the gaussian_elimination library.\n"
       << "BEGIN." << endl;

  cout << "\n\n" << endl;

  cout << "We will first test by solving this extremely simple 2x2 system:"
       << endl;

  GaussianSystem testing1;
  ifstream infile;
  infile.open("test_system.txt");
  infile >> testing1;
  testing1.print(cout,0);
  cout << endl;

  cout << "\nSolving...\n" << endl;
  gaussian_elimination(testing1);
  Dynamic1DArray<double> solution1;
  cout << "\nGaussian elimination finished.\n"
       << "Here's what the system looks like:\n"
       << testing1
       << endl;

  cout << "Starting back-substitution." << endl;
  solution1 = back_substitution(testing1);
  cout << "Got it! The solution is:" << endl;
  print_solution(cout,solution1,DBL_EPSILON);

  cout << "\n\nThis conlcudes the test." << endl;
}
// ----------------------------------------------------------------------
