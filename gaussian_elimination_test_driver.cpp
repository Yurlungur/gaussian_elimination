// gaussian_elimination_test_driver.cpp

// Author: Jonah Miller (jonah.maxwell.miller@gmail.com)
// Time-stamp: <2013-08-15 19:50:45 (jonah)>

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

  cout << "\n\nNow testing a more sophisticated non-degenerate matrix.\n"
       << endl;

  int testing2_size = 3;
  GaussianSystem testing2(testing2_size);
  Dynamic1DArray<double> solution2;
  testing2.matrix_set(0,0,2);
  testing2.matrix_set(0,1,4);
  testing2.matrix_set(0,2,-2);
  testing2.matrix_set(1,0,4);
  testing2.matrix_set(1,1,9);
  testing2.matrix_set(1,2,-3);
  testing2.matrix_set(2,0,-2);
  testing2.matrix_set(2,1,-3);
  testing2.matrix_set(2,2,7);
  testing2.vector_set(0,2);
  testing2.vector_set(1,8);
  testing2.vector_set(2,10);


  cout << "Our new matrix is:\n"
       << testing2
       << endl;

  cout << "\nSolving...\n" << endl;

  solution2 = solve_system(testing2);

  cout << "\nGot it! The solution is:" << endl;
  print_solution(cout,solution2,DBL_EPSILON);

  cout << "And here's the original matrix...\n"
       << testing2 << endl;
  
  cout << "\n\nThis conlcudes the test." << endl;
}
// ----------------------------------------------------------------------
