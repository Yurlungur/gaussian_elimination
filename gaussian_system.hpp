// gaussian_system.hpp

// Author: Jonah Miller (jonah.maxwell.miller@gmail.com)
// Time-stamp: <2013-06-21 00:26:24 (jonah)>

// This file prototypes a Gaussian system, which is a
// data structure for holding a system of linear equations and
// modifying them in-place to solve by Gaussian elimination.

// Include guard
#pragma once

#include<dynamic_array.hpp> // for dynamic arrays
#include<iostream> // for printing a system.
#include<fstream> // For building a system from an input file
using namespace std;

// A class that holds an n-dimensional matrix equation. Uses an nxn
// matrix and a n-dimensional vector. Enables row-swapping for
// Gaussian elimination.
class GuassianSystem {
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
  GuassianSystem(ifstream& input_file);
  // Destructor. Returns all dynamic memory used by the object to the heap.
  ~GaussianSystem();
  // Assignment operator. Copies one Gaussian System into another.
  GaussianSystem& operator = (const GaussianSystem &rhs);
private: // Implementation details.
  int system_size; // The size of the system. A is system_size x
		   // system_size. b is system_size-dimensional
		   // vector.
  Dynamic2DArray<double> coefficient_matrix; // Matrix of coefficients. A
  Dynamic1DArray<double> unkowns_vector; // Vector of knowns. b
  // Keeps track of row swaps so that rows don't actually have to be copied.
  Dynamic1DArray<int> permutation_vector;
  // Tests whether the (i,j)th element of the system exists. If not,
  // throws an error. The final row is the vector of knowns. The other
  // rows are the matrix of coefficients.
  void test_allocation(int i, int j) const;
  // Tests whether the (i,j)th element of the matrix exists. If not,
  // throws an error. Does not include the vector of knowns.
  void test_matrix_allocation(int i, int j) const;
  // Tests whether the ith element of the vector exists. If not,
  // throws an error. Ignores the coefficient matrix.
  void test_vector_allocation(int i) const;
public: // Interface.
  // Gives n, where the system has n equations and n unknowns.
  int size() const;
  // Swaps row1 and row2 in the system. Useful for pivoting.
  void swap(int row1, int row2);
  // This function sets the (i,j)th element of the system. The final
  // column is the vector. The other columns are the coefficient
  // matrix.
  void set(int i, int j, double new_element);
  // This function sets the (i,j)th element of the system to
  // new_element. The final column is the vector. The other columns
  // are the coefficient matrix.
  double get(int i, int j) const;
  // This function returns the (i,j)th element of the system by
  // reference. The final column is the fector. The other columns are
  // the coefficient matrix.
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
  void build(ifstream& input_file);
  // Prints out the system in a nice format.
  void print(ostream& output_stream = cout);
  // Overload the stream input operator.
  friend ostream& operator << (ostream &out, const GaussianSystem &sys);
}
