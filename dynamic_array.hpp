// dynamic_array.hpp

// Author: Jonah Miller (jonah.maxwell.miller@gmail.com)
// Time-stamp: <2013-06-18 00:07:20 (jonah)>

// This file defines a library for using dynamic arrays of one and two
// dimensions. Useful for Gaussian Elimination.

// Include Guard
// ----------------------------------------------------------------------
#ifndef DYNAMIC_ARRAY_HEADER
#define DYNAMIC_ARRAY_HEADER
// ----------------------------------------------------------------------

#include<cstdlib>
#include<iostream> // streams needed for print functions
using namespace std;

// A class for 1-dimensional dynamic arrays.
template<typename TYPE>
class Dynamic1DArray {
public: // constructors. And Destructors.
  // Generates an empty dynamic 1D array of length l.
  Dynamic1DArray(int l) {
    my_array = new TYPE[l];
    array_length = l;
  }
  /*
  // Destructor. Returns all dynamic memory used by the object to the heap.
  ~Dynamic1DArray() {
    delete [] my_array;
  }
  */
private:
  // The pointer to the dynamic array.
  TYPE * my_array;
  // The length of the array.
  int array_length;
  // Test whether integer n is between 0 and the length of the
  // array. If not, throw an exception.
  void test_allocation(int n) {
    if (n >= array_length || n < 0) {
      cout << "You've accessed memory out of the array.\n"
	   << "The element you've accessed was: " << n << ".\n"
	   << "Check to make sure this was correct." << endl;
      exit(1);
    }
  }
    
public:

  // This function gives the length of the array.
  int length() {
    return array_length;
  }
  // This function returns the nth element of the array. Not passed by
  // reference. Prevents reading from the wrong memory areas.
  TYPE get(int n) {
    test_allocation(n);
    return my_array[n];
  }
  // This function sets the nth element of the array to t. Prevents
  // writing to the wrong memory areas.
  void set(int n, TYPE t) {
    test_allocation(n);
    my_array[n] = t;
  }
  // Clears out the array and resets its length to l.
  void reset(int l) {
    delete [] my_array;
    array_length = l;
    my_array = new TYPE[l];
  }
  // Prints out the array as a 1D row vector.
  void print(ostream& s = cout) {
    s << "[";
    for (int i=0; i < array_length-1; i++) {
      s << get(i) << ", ";
    }
    s << get(array_length-1) << "]";
  }

  // Overload the stream input operator. 
  friend ostream& operator <<(ostream &out, Dynamic1DArray<TYPE> a) {
    a.print(out);
    return out;
  }

};

template<typename TYPE>
class Dynamic2DArray {
public: // constructors and destructors.
  // Generates an empty dynamic 2D array of width i and height j.
  Dynamic2DArray(int i, int j) {
    array_height = i;
    array_width = j;
    my_array = new TYPE* [array_height];
    for (int row=0; row < array_height; row++) {
      my_array[row] = new TYPE[array_width];
    }
  }
  // Returns all dynamic memory to the heap.
  ~Dynamic2DArray() {
    for (int y = 0; y < array_width; y++) {
      delete [] my_array[y];
    }
    delete [] my_array;
  }

private:
  // The pointer to the dynamic array.
  TYPE** my_array;
  // The array is WIDTHxHEIGHT
  // First index is row. Second index is column.
  int array_height;
  int array_width;
  // Test whether coordinates are valid.
  void test_allocation(int i, int j) {
    if ( i >= array_height || j >= array_width || i < 0 || j < 0 ) {
      cout << "You've accessed memory out of the array." << endl;
      cout << "The element you tried to access was ("
	   << i << ", " << j << ").\n"
	   << "Check to make sure this is right." << endl;
      exit(1);
    }
  }
public:
  // This function gives the width of the array.
  int width() {
    return array_width;
  }
  // This function gives the height of the array.
  int height() {
    return array_height;
  }
  // This function returns the (i,j)th element of the array. Not
  // passed by reference. Prevents reading from the wrong memory
  // areas.
  TYPE get(int i, int j) {
    test_allocation(i,j);
    return my_array[i][j];
  }
  // This function sets the (i,j)th element of the array to
  // t. Prevents writing to the wrong memory areas.
  void set(int i, int j, TYPE t) {
    test_allocation(i,j);
    my_array[i][j] = t;
  }
  // Clears out the array and resets its dimensions to (i,j).
  void reset(int i, int j) {
    for (int row = 0; row < array_height; row++) {
      delete [] my_array[row];
    }
    delete [] my_array;
    array_height = i;
    array_width = j;
    my_array = new TYPE* [array_height];
    for (int row=0; row < array_height; row++) {
      my_array[row] = new TYPE[array_width];
    }
  }
  // Prints the array as a 2D matrix.
  // Quick and dirty. No formatting.
  void print(ostream& s = cout) {
    for (int row = 0; row < array_height; row++) {
      s << "\n[";
      for (int column = 0; column < array_width-1; column++) {
	s << get(row,column) << ", ";
      }
      s << get(row,array_width-1) << "]";
    }
    s << "\n";
  }
  // Overload the stream input operator. 
  friend ostream& operator <<(ostream &out, Dynamic2DArray<TYPE> a) {
    a.print(out);
    return out;
  }
};


// End include guard
// ----------------------------------------------------------------------
#endif
// ----------------------------------------------------------------------

