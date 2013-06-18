// dynamic_array_test_driver.cpp

// Author: Jonah Miller (jonah.maxwell.miller@gmail.com)
// Time-stamp: <2013-06-18 00:07:37 (jonah)>

// This file is a test driver for the dynamic_array.cpp

#include <iostream>
#include "dynamic_array.hpp"
using namespace std;


// ----------------------------------------------------------------------
int main() {
  int testlength = 10;
  cout << "Beginning test of Dynamic1DArray." << endl;
  // Dynamic1DArray Test
  Dynamic1DArray<int> testing1(testlength);
  cout << "Test the length method." << endl;
  cout << testing1.length() << endl;
  cout << "Test set methods." << endl;
  for (int i = 0; i < testlength; i++) {
    testing1.set(i,2*i);
  }
  cout << "Test the get methods." << endl;
  cout << "# index value" << endl;
  for (int i = 0; i < testlength; i++) {
    cout << "#   " << i << "     " << testing1.get(i) << endl;
  }
  cout << "Test the reset method." << endl;
  testing1.reset(20);
  cout << "Ensure the first element is junk.\n"
       << "The first element is: " << testing1.get(0) << endl;
  cout << "Check the array length:\n"
       << "The array length is: " << testing1.length() << endl;
  cout << "Check that the 19th element is accessible\n"
       << "Set the 19th element to 4. Then get it out." << endl;
  testing1.set(19,4);
  cout << "The 19th element is: " << testing1.get(19) << endl;
  cout << "Checking the print function.\n"
       << "The array is currently: "
       << testing1
       << endl;

  // Dynamic2DArray Test
  cout << "\nBeginning test of Dynamic2DArray." << endl;
  int testwidth = 5;
  int testheight = 10;
  Dynamic2DArray<int> testing2(testheight,testwidth);
  cout << "Tests the dimensions functions." << endl;
  cout << "The width of the array is: " << testing2.width() << endl;
  cout << "The height of the array is: " << testing2.height() << endl;

  cout << "Testing the set and get functions." << endl;
  for (int row = 0; row < testheight; row++) {
    for (int column = 0; column < testwidth; column++) {
      testing2.set(row,column,row+column);
    }
  }

  for (int row = 0; row < testheight; row++) {
    for (int column = 0; column < testwidth; column++) {
      cout << testing2.get(row,column) << ", ";
    }
    cout << "\n";
  }
  cout << endl;

  cout << "Testing the print method." << endl;
  cout << "The current array is: "
       << testing2
       << endl;

  cout << "Testing the reset method." << endl;
  testing2.reset(2,2);
  Dynamic2DArray<int> testing3(5,5);
  testing3.reset(2,2);
  
  return 0;
}
// ----------------------------------------------------------------------
