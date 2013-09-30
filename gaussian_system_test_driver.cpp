// gaussian_system_test_driver.cpp

// Author: Jonah Miller (jonah.maxwell.miller@gmail.com)
// Time-stamp: <2013-09-30 10:38:08 (jonah)>

// This file is the test driver for the Gaussian System class,
// which is a data structure for holding a systme of linear
// equations and modifying them in place to solve by
// Gaussian elimination.

#include <iostream>
#include <fstream>
#include <cassert>
#include "dynamic_array.hpp"
#include "gaussian_system.hpp"
using namespace std;

// Main function
// ----------------------------------------------------------------------
int main() {
  cout << "Testing the 'GaussianSystem' class.\n"
       << "BEGIN." << endl;

  cout << "\n\n" << endl;

  cout << "Testing basic methods,\n"
       << "size(), (int n) constructor, print, operator <<,\n"
       << "access, set, get\n"
       << "----------------------------------------------------\n" << endl;
  
  cout << "Initializing a 5x5 empty Gaussian system." << endl;
  GaussianSystem testing1(5);
  cout << "Making an extremely simple, solved, system." << endl;
  for (int i = 0; i < testing1.size(); i++) {
    for (int j = 0; j < testing1.size(); j++) {
      testing1.set(i,j, (i==j) ? 1 : 0);
    }
    testing1.vector_set(i,i);
  }
  cout << "The system is thus:\n" << testing1 << endl;

  cout << "\n\n"
       << "Testing swap.\n"
       << "----------------------------------------------------\n" << endl;

  cout << "Swapping 0th and 1st rows." << endl;
  testing1.swap(0,1);
  cout << "The system is thus:\n";
  testing1.print(cout,0);
  cout << endl;

  cout << "Swapping the 1st and 2nd rows." << endl;
  testing1.swap(1,2);
  cout << "The system is thus:\n";
  testing1.print(cout,0);
  cout << endl;

  cout << "\n\n"
       << "Testing the text file input method.\n"
       << "----------------------------------------------------\n" << endl;

  cout << "Inputting a very simple file." << endl;
  ifstream infile;
  infile.open("test_system.txt");
  infile >> testing1;
  cout << "The system is thus:\n";
  testing1.print(cout,0);
  cout << endl;

  cout << "Test successful." << endl;
}
