// gaussian_system.hpp

// Author: Jonah Miller (jonah.maxwell.miller@gmail.com)
// Time-stamp: <2013-08-06 17:04:21 (jonah)>

// This file prototypes a Gaussian system, which is a
// data structure for holding a system of linear equations and
// modifying them in-place to solve by Gaussian elimination.

// Note that some methods are defined inline for speed and ease of use.

// Include guard
#pragma once

#include <float.h>  // Lists machine epsilon
#include <iostream> // for printing a system.
#include <iomanip> // For controlling the output.
#include <fstream> // For building a system from an input file
#include "dynamic_array.hpp" // for dynamic arrays
using namespace std;

// A class that holds an n-dimensional matrix equation. Uses an nxn
// matrix and a n-dimensional vector. Enables row-swapping for
// Gaussian elimination.
class GaussianSystem {
  // Represents the system Ax = b,
  // where A is a matrix, x is a vector
  // of unkowns, and b is a vector of knowns.
public: // Constructors, destructors, and assignment operators.
  // Creates an empty gaussian system with an nxn coefficient matrix
  // and n unknowns.
  GaussianSystem(int n);
  // Creates an empty Gaussian system. To be initialized later.
  GaussianSystem();
  // Copy constructor. Creates a new Gaussian system that's a copy of
  // the input one.
  GaussianSystem(const GaussianSystem &rhs);
  // Stream constructor
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
  GaussianSystem(ifstream& input_file);
  // Assignment operator. Copies one Gaussian System into another.
  GaussianSystem& operator = (const GaussianSystem &rhs) {
    initialize_all_arrays(rhs.size());
    initialize_permutation_vector();
    for (int row = 0; row < system_size; row++) {
      for (int column = 0; column < system_size + 1; column++) {
	access(row,column) = rhs.get(row,column);
      }
    }
    return (*this);
  }
private: // Implementation details.
  int system_size; // The size of the system. A is system_size x
		   // system_size. b is system_size-dimensional
		   // vector.
  Dynamic2DArray<double> coefficient_matrix; // Matrix of coefficients. A
  Dynamic1DArray<double> knowns_vector; // Vector of knowns. b
  // Keeps track of row swaps so that rows don't actually have to be copied.
  Dynamic1DArray<int> permutation_vector;
  // Initializes the permutation vector to the identity.
  void initialize_permutation_vector();
  // Initializes the arrays for a system of size n.
  void initialize_all_arrays(int n);
public: // Interface.
  // Gives n, where the system has n equations and n unknowns.
  int size() const {
    return system_size;
  }
  // Returns true if the system isupper-triangular. False otherwise.
  // To determine if a row element is zero, uses DEFAULT_PRECISION by
  // default
  bool is_upper_triangular() const;
  // Tells the user the order of the permuted rows. Essential for
  // extracing the solution to the original system after Gaussian
  // elimination.
  Dynamic1DArray<int> get_permutations() const;
  // Swaps row1 and row2 in the system. Useful for pivoting.
  void swap(int row1, int row2);
  // Sets the (i,j)th element of the system. The final
  // column is the vector. The other columns are the coefficient
  // matrix.
  void set(int i, int j, double new_element);
  // Gets the (i,j)th element of the system.  The final column is the
  // vector. The other columns are the coefficient matrix.
  double get(int i, int j) const;
  // Returns the (i,j)th element of the system by reference. The final
  // column is the fector. The other columns are the coefficient
  // matrix.
  double& access(int i, int j);
  // This function is like set, but only looks at the coefficient matrix.
  void matrix_set(int i, int j, double new_element);
  // This function is like get, but only looks at the coefficient matrix.
  double matrix_get(int i, int j) const;
  // This function is like access, but only looks at the coefficients matrix.
  double& matrix_access(int i, int j);
  // This function is like set, but only looks at the unkowns vector.
  void vector_set(int i, double new_element);
  // This method is like get, but only looks at the unkowns vector.
  double vector_get(int i) const;
  // This method is like access, but only looks at the unkowns vector.
  double& vector_access(int i);
  // Builds a Gaussian system from file. Equivalent to calling the
  // file input constructor.
  void build(istream& input_file);
  // Prints out the system in a nice format. Precision sets the
  // precision of the output so it looks nice. Sets number of
  // significant digits.
  void print(ostream& output_stream = cout, int precision = 3) const;
  // Overload the stream input operator.
  friend ostream& operator << (ostream &out, const GaussianSystem &sys);
  // Overload the stream output operator.
  friend istream& operator >> (istream &in, GaussianSystem &sys);
};
