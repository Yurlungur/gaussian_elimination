// dynamic_array.cpp

// Author: Jonah Miller (jonah.maxwell.miller@gmail.com)
// Time-stamp: <2013-06-16 23:26:22 (jonah)>

// This file defines a library for using dynamic arrays of one and two
// dimensions. Useful for Gaussian Elimination.

#include "dynamic_array.hpp"
#include <exception>
using namespace std;

// Dynamic1DArray
// ----------------------------------------------------------------------
// constructors.
// Generates an empty dynamic 1D array of length l.
template<typename TYPE>
Dynamic1DArray<TYPE>::Dynamic1DArray(int l) {
  my_array = new TYPE[l];
  array_length = l;
}
// Generates a dynamic 1D array of length l. Takes in a pointer to a
// non-dynamic 1D array of length l.
template<typename TYPE>
Dynamic1DArray<TYPE>::Dynamic1DArray(TYPE** tp, int l) {
  my_array = new TYPE[l];
  array_length = l;
  for (int i = 0; i < l; i++) {
    my_array[i] = (&tp)[i];
  }
}

// Other methods
// This function gives the length of the array.
template<typename TYPE>
int Dynamic1DArray<TYPE>::length() {
  return array_length;
}

// Test whether integer n is between 0 and the length of the
// array. If not, throw an exception.
template<typename TYPE>
void Dynamic1DArray<TYPE>::test_allocation(int n) {
  if (n >= array_length || n < 0) {
    cout << "You've accessed memory out of the array." << endl;
    exit(1);
  }
}

// This function returns the nth element of the array. Not passed by
// reference. Prevents reading from the wrong memory areas.
TYPE Dynamic1DArray::get(int n) {
  test_allocation(n);
  return my_array[n];
}

// This function sets the nth element of the array to t. Prevents
// writing to the wrong memory areas.
void Dynamic1DArray::set(int n, TYPE t) {
  test_allocation(n);
  my_array[n] = t;
}

// Clears out the array and resets its length to l.
void Dynamic1DArray::reset(int l) {
  delete [] my_array;
  array_length = l;
  my_array = new TYPE[l];
}

// ----------------------------------------------------------------------
