// dynamic_array.hpp

// Author: Jonah Miller (jonah.maxwell.miller@gmail.com)
// Time-stamp: <2013-06-20 20:54:42 (jonah)>

// This file defines a library for using dynamic arrays of one and two
// dimensions. Useful for Gaussian Elimination.

// Include guard
#pragma once

#include<cstdlib>
#include<iostream> // streams needed for print functions
using namespace std;

// A class for 1-dimensional dynamic arrays.
template<typename TYPE>
class Dynamic1DArray {
public: // constructors, destructors, and assignment operators
  // Generates an empty dynamic 1D array of length l.
  Dynamic1DArray(int l) {
    array_length = l;
    if (array_length > 0) {
      my_array = new TYPE[l];
    }
  }
  // Allows the user to generate an empty dynamic 1D array.
  Dynamic1DArray() {
    array_length = 0;
  }
  // Copy constructor. Generates an exact copy of the input dynamic array.
  Dynamic1DArray(const Dynamic1DArray<TYPE> &rhs) {
    array_length = rhs.length();
    if (array_length > 0) {
      my_array = new TYPE[array_length];
      for (int i = 0; i < array_length; i++) {
	set(i,rhs.get(i));
      }
    }
  }
  // Destructor. Returns all dynamic memory used by the object to the heap.
  ~Dynamic1DArray() {
    if (array_length > 0) {
      delete [] my_array;
    }
  }
  // Assignment operator. Copies one Dynamic1DArray into another.
  Dynamic1DArray<TYPE>& operator = (const Dynamic1DArray<TYPE> &rhs) {
    if (array_length > 0) {
      delete [] my_array;
    }
    array_length = rhs.length();
    if (array_length > 0) {
      my_array = new TYPE[array_length];
      for (int i = 0; i < array_length; i++) {
	set(i,rhs.get(i));
      }
    }
    return *this;
  }
private:
  // The pointer to the dynamic array.
  TYPE * my_array;
  // The length of the array. If 0, the array is uninitialized.
  int array_length;
  // Test whether integer n is between 0 and the length of the
  // array. If not, throw an exception.
  void test_allocation(int n) const {
    if ( n >= array_length || n < 0 ) {
      cout << "You've accessed memory out of the array.\n"
	   << "The element you've accessed was: " << n << ".\n"
	   << "Check to make sure this was correct." << endl;
      exit(1);
    }
  }
    
public:
  // This function gives the length of the array.
  int length() const {
    return array_length;
  }
  // This function returns the nth element of the array. Not passed by
  // reference. Prevents reading from the wrong memory areas.
  TYPE get(int n) const {
    test_allocation(n);
    return my_array[n];
  }
  // This function sets the nth element of the array to t. Prevents
  // writing to the wrong memory areas.
  void set(int n, TYPE t) {
    test_allocation(n);
    my_array[n] = t;
  }
  // This function returns the nth element of the array by reference.
  TYPE& access(int n) {
    test_allocation(n);
    return my_array[n];
  }
  // Syntactic sugar for the access method.
  TYPE& operator [] (int n) {
    return access(n);
  }
  
  // Clears out the array and resets its length to l.
  void reset(int l) {
    if (array_length > 0) {
      delete [] my_array;
    }
    array_length = l;
    if (array_length > 0) {
      my_array = new TYPE[l];
    }
  }
  // Prints out the array as a 1D row vector.
  void print(ostream& s = cout) const {
    s << "[";
    for (int i=0; i < length()-1; i++) {
      s << get(i) << ", ";
    }
    s << get(length()-1) << "]";
  }

  // Overload the stream input operator. 
  friend ostream& operator <<(ostream &out, const Dynamic1DArray<TYPE> &a) {
    a.print(out);
    return out;
  }

};

template<typename TYPE>
class Dynamic2DArray {
public: // constructors, assignment operator, and destructors.
  // Generates an empty dynamic 2D array of width i and height j.
  Dynamic2DArray(int i, int j) {
    array_height = i;
    array_width = j;
    array_cell_number = array_height * array_width;
    if (array_cell_number > 0) {
      my_array = new TYPE [array_cell_number];
    }
  }
  // Default constructor. Allows the user to generate an uninitialized
  // dynamic 2D array.
  Dynamic2DArray() {
    array_height = 0;
    array_width = 0;
    array_cell_number = array_height * array_width;
  }
  // Copy constructor. Generates an exact copy of another array.
  Dynamic2DArray(const Dynamic2DArray<TYPE> &rhs) {
    array_width = rhs.width();
    array_height = rhs.height();
    array_cell_number = array_width * array_height;
    if (array_cell_number > 0) {
      my_array = new TYPE [array_cell_number];
      for (int row = 0; row < array_height; row++) {
	for (int column = 0; column < array_width; column++) {
	  set(row,column,rhs.get(row,column));
	}
      }
    }
  }
  // Returns all dynamic memory to the heap.
  ~Dynamic2DArray() {
    if (array_cell_number > 0) {
      delete[] my_array;
    }
  }
  // Assignment operator. Copies one object into another.
  Dynamic2DArray<TYPE>& operator = (const Dynamic2DArray<TYPE> &rhs) {
    if (array_cell_number > 0) {
      delete [] my_array;
    }
    array_width = rhs.width();
    array_height = rhs.height();
    array_cell_number = array_width * array_height;
    if (array_cell_number > 0) {
      my_array = new TYPE [array_cell_number];
      for (int row = 0; row < array_height; row++) {
	for (int column = 0; column < array_width; column++) {
	  set(row,column,rhs.get(row,column));
	}
      }
    }
    return *this;
  }
private:
  // The pointer to the dynamic array. One dimensional for speed.
  TYPE* my_array;
  // The array is array_width x array_height
  // First index is row. Second index is column.
  int array_height;
  int array_width;
  // The array has a number of cells equal to the width times the
  // height. If this value is zero, the array is empty.
  int array_cell_number;
  // Test whether coordinates are valid.
  void test_allocation(int i, int j) const {
    if ( i >= array_height || j >= array_width || i < 0 || j < 0 ) {
      cout << "You've accessed memory out of the array." << endl;
      cout << "The element you tried to access was ("
	   << i << ", " << j << ").\n"
	   << "Check to make sure this is right." << endl;
      exit(1);
    }
  }
  // Convert row,column coordinates into a cell index for the 1-dimensional array.
  int to_1d_index(int i, int j) const {
    test_allocation(i,j); // ensure the coordinates are valid.
    return i*array_width + j;
  }
public:
  // This function gives the width of the array.
  int width() const {
    return array_width;
  }
  // This function gives the height of the array.
  int height() const {
    return array_height;
  }
  // This function returns the number of elements the array can contain.
  int cell_number() const {
    return array_cell_number;
  }
  // This function returns the (i,j)th element of the array. Not
  // passed by reference. Prevents reading from the wrong memory
  // areas.
  TYPE get(int i, int j) const {
    test_allocation(i,j);
    return my_array[to_1d_index(i,j)];
  }
  // This function sets the (i,j)th element of the array to
  // t. Prevents writing to the wrong memory areas.
  void set(int i, int j, TYPE t) {
    test_allocation(i,j);
    my_array[to_1d_index(i,j)] = t;
  }
  
  // This function returns the pointer to the (i,j)th element of the
  // array. Prevents reading from the wrong memory areas. Is passed
  // by reference.

  // There is no array index operator. I chose not to include one
  // because it would have to index into the 1d array, which is
  // counterintuitive and confusing.
  TYPE& access(int i, int j) {
    test_allocation(i,j);
    return my_array[to_1d_index(i,j)];
  }

  // Clears out the array and resets its dimensions to (i,j).
  void reset(int i, int j) {
    if (array_cell_number > 0) {
      delete [] my_array;
    }
    array_height = i;
    array_width = j;
    array_cell_number = array_width * array_height;
    if (array_cell_number > 0) {
      my_array = new TYPE [array_cell_number];
    }
  }
  // Prints the array as a 2D matrix.
  // Quick and dirty. No formatting.
  void print(ostream& s = cout) const {
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
  friend ostream& operator <<(ostream &out, const Dynamic2DArray<TYPE> &a) {
    a.print(out);
    return out;
  }
};

