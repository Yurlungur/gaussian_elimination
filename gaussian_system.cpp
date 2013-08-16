// gaussian_system.cpp

// Author: Jonah Miller (jonah.maxwell.miller@gmail.com)
// Time-stamp: <2013-08-16 00:24:25 (jonah)>

// This file implements a Gaussian system, which is a data structure
// for holding a system of linear equations and modifying them in
// place to solve by Gaussian elimination.

#include<iostream>
#include<iomanip>
#include<fstream>
#include<cassert>
#include<cmath>
#include"dynamic_array.hpp"
#include"gaussian_system.hpp"
using namespace std;

// Constructors, destructors, and assignment operators
// ----------------------------------------------------------------------

// Creates an empty gaussian system with an nxn coefficient matrix
// and n unknowns.
GaussianSystem::GaussianSystem(int n) {
  // Build the arrays
  initialize_all_arrays(n);
  // Sets the matrix to un-permuted
  initialize_permutation_vector();
  // Initializes the system to the trivial zero matrix.
  for (int row = 0; row < n; row++) {
    for (int column = 0; column < n+1; column++) {
      access(row,column) = 0;
    }
  }
}

// Creates an empty Gaussian system. To be initialized later.
GaussianSystem::GaussianSystem() {
  system_size = 0; // 0 represents an unitialized system.
}

// Copy constructor. Creates a new Gaussian system that's a copy of
// the input oone.
GaussianSystem::GaussianSystem(const GaussianSystem &rhs) {
  initialize_all_arrays(rhs.size());
  initialize_permutation_vector();
  for (int row = 0; row < system_size; row++) {
    for (int column = 0; column < system_size + 1; column++) {
      access(row,column) = rhs.get(row,column);
    }
  }
}

// Stream constructor.
// Builds a Gaussian system from an input file. The first line
// containes the size of the system. The next line contains a space
// separated list of the values of first the matrix and then the
// vector of unkonws. Each row is a separate line. i.e.,
// 3
// 1 0 0 1
// 0 1 0 1
// 0 0 1 1
// represents a 3x3 system
// Ax = y
// where the solution is that x_1 = x_2 = x_3 = 1.
GaussianSystem::GaussianSystem(ifstream& input_file) {
  // Get the system size and then initialize the arrays.
  int n;
  input_file >> n;
  initialize_all_arrays(n);
  initialize_permutation_vector();
  // Start reading in the files.
  for (int row = 0; row < n; row++) {
    for (int column = 0; column < n+1; column++) {
      input_file >> access(row,column);
    }
  }
}

// ----------------------------------------------------------------------


// Private utility methods
// ----------------------------------------------------------------------

// Initializes the arrays for a system of size n.
void GaussianSystem::initialize_all_arrays(int n) {
  system_size = n;
  coefficient_matrix = Dynamic2DArray<double>(n,n);
  knowns_vector = Dynamic1DArray<double>(n);
  permutation_vector = Dynamic1DArray<int>(n);
  return;
}

// Initializes the permutation vector to the identity.
// WARNING: DO NOT CALL THIS METHOD BEFORE CALLING initialize_all_arrays
void GaussianSystem::initialize_permutation_vector() {
  for (int row = 0; row < system_size; row++) {
    permutation_vector[row] = row;
  }
  return;
}

// ----------------------------------------------------------------------

// Interface
// ----------------------------------------------------------------------

// Returns true if the system isupper-triangular. False otherwise.
bool GaussianSystem::is_upper_triangular() const {
  double precision = DBL_EPSILON; // Precision to zero.
  if ( size() <= 1 ) { // 1x1 matrix is upper-triangular
    return true;
  }
  for (int column = 0; column < size(); column++) {
    for (int row = column + 1; row < size(); row++) {
      double entry = get(row,column);
      if ( abs(entry) > precision ) {
	return false;
      }
    }
  }
  return true;
}

// Swaps row1 and row2 in the system. Useful for pivoting.
void GaussianSystem::swap(int row1, int row2) {
  int temp_row;
  temp_row = permutation_vector[row1];
  permutation_vector[row1] = permutation_vector[row2];
  permutation_vector[row2] = temp_row;
}

// Returns the (i,j)th element of the coefficients matrix by
// reference.
double& GaussianSystem::matrix_access(int i, int j) {
  assert(i < system_size && j < system_size && i >= 0 && j >= 0
	 && "Coordinates within allocated memory.");
  return coefficient_matrix.access(permutation_vector[i],j);
}

// Returns the ith element of the vector of knowns.
double& GaussianSystem::vector_access(int i) {
  assert(i < system_size && i >= 0
	 && "Coordinates within allocated memory.");
  return knowns_vector[permutation_vector[i]];
}

// Returns the (i,j)th element of the system by reference. The final
// column is the fector. The other columns are the coefficient
// matrix.
double& GaussianSystem::access(int i, int j) {
  if (j < system_size) {
    return matrix_access(i,j);
  }
  else {
    return vector_access(i);
  }
}

// This function is like get, but only looks at the coefficient matrix.
double GaussianSystem::matrix_get(int i, int j) const {
  assert(i < system_size && j < system_size && i >= 0 && j >= 0
	 && "Coordinates within allocated memory.");
  return coefficient_matrix.get(permutation_vector.get(i),j);
}

// This method is like get, but only looks at the unkowns vector.
double GaussianSystem::vector_get(int i) const {
  assert(i < system_size && i >= 0
	 && "Coordinates within allocated memory.");
  return knowns_vector.get(permutation_vector.get(i));
}

// Gets the (i,j)th element of the system.  The final column is the
// vector. The other columns are the coefficient matrix.
double GaussianSystem::get(int i, int j) const {
  if (j < system_size) {
    return matrix_get(i,j);
  }
  else {
    return vector_get(i);
  }
}

// This function is like set, but only looks at the coefficient matrix.
void GaussianSystem::matrix_set(int i, int j, double new_element) {
  matrix_access(i,j) = new_element;
}

// This function is like set, but only looks at the unkowns vector.
void GaussianSystem::vector_set(int i, double new_element) {
  vector_access(i) = new_element;
}

// Sets the (i,j)th element of the system. The final
// column is the vector. The other columns are the coefficient
// matrix.
void GaussianSystem::set(int i, int j, double new_element) {
  access(i,j) = new_element;
}

// Builds a Gaussian system from file. Equivalent to calling the
// file input constructor.
void GaussianSystem::build(istream& input_file) {
  // Get the system size and then initialize the arrays.
  int n;
  input_file >> n;
  initialize_all_arrays(n);
  initialize_permutation_vector();
  // Start reading in the files.
  for (int row = 0; row < n; row++) {
    for (int column = 0; column < n+1; column++) {
      input_file >> access(row,column);
    }
  }
}

// Prints out the system in a nice format.
void GaussianSystem::print(ostream& output_stream, int precision) const {
  // halfway through the rows. Where we put the equals sign.
  int halfway = (size()-1)/2;

  // Sets the notation to scientific
  output_stream << scientific;

  // Makes a nice matrix equation
  for (int row = 0; row < size(); row++) {
    // The rows of the matrix
    output_stream << left << "[ ";
    for (int column = 0; column < size()-1; column++) {
      output_stream << setprecision(precision)
		    << matrix_get(row,column)
		    << ", ";
    }
    output_stream << setprecision(precision)
		  << matrix_get(row,size()-1) << " ";
    // The rows of the unknowns vector
    output_stream << "] [ x_" << row << " ]";
    // The equals sign
    if (row == halfway) {
      output_stream << " = ";
    }
    else {
      output_stream << "   ";
    }
    // The rows of the knowns vector.
    output_stream << "[ " << vector_get(row) << " ]\n";
  }
  output_stream << endl;
}

// ----------------------------------------------------------------------

// Friend functions
// ----------------------------------------------------------------------
// Overload the stream input operator.
ostream& operator << (ostream &out, const GaussianSystem &sys) {
  sys.print(out);
  return out;
}

// Overload the stream output operator.
istream& operator >> (istream &in, GaussianSystem &sys) {
  sys.build(in);
  return in;
}
// ----------------------------------------------------------------------
