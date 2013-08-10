// gaussian_elimination.cpp

// Author: Jonah Miller (jonah.maxwell.miller@gmail.com)
// Time-stamp: <2013-08-09 21:36:35 (jonah)>

// This file implements the Gaussian elimination library, which is a
// set of functions to solve non-degenerate linear systems by Gaussian
// elimination.

// This library is designed to be used with the gaussian_system data
// structure.

// ----------------------------------------------------------------------


// Includes
#include "gaussian_elimination.hpp"
#include <cmath>
#include <cassert>
#include <float.h>
#include <iomanip>
using namespace std;
// ----------------------------------------------------------------------



// Looks for the row k of gaussian system g_sys below row i such that
// the element in the kth row and jth column is the largest element in
// column j. Swaps the rows i and k. It is possible that there are no
// non-zero entries in column j below row i. If this is the case,
// returns false. Otherwise returns true.
// ----------------------------------------------------------------------
bool pivot(GaussianSystem& g_sys, int i, int j) {
  int largest_row = i; // The row with the largest element
  // the largest element
  double largest_value = abs(g_sys.matrix_get(largest_row,j)); 
  for (int k=i; k < g_sys.size(); k++) {
    if (abs(g_sys.matrix_get(k,j)) > largest_value) {
      largest_row = k;
      largest_value = abs(g_sys.matrix_get(largest_row,j));
    }
  }
  if (largest_row > 0) {
    g_sys.swap(i,largest_row);
    return true;
  } else {
    return false;
  }
}
// ----------------------------------------------------------------------


// Makes every element in column=index and a row below row=index in
// the gaussian system zero. Affects other elements of the matrix.
// ----------------------------------------------------------------------

// In gaussian elimination,
// a_{ij} = a_{ij} - (a_{ik}/a_{kk})*a_{kj}
// In this function:
//                   a_{ij} is old
//                   a_{ik} is row_numerator
//                   a_{kj} is column_numerator
//                   a_{kk} is divisor

void row_reduce(GaussianSystem& g_sys, int index) {

  // Local declarations
  double old;     // The old entry in the matrix system
  double divisor; // To generate the new entry in the matrix system,
		  // we willl need to divide by this number.
  double column_numerator; // To generate the new entry in the matrix
			   // system, we will need to multiply by this
			   // number.
  double row_numerator; // To generate the new entry in the matrix
			// system, we will need to multiply by this
			// number.
  double new_entry; // The new value

  for (int column = index; column <= g_sys.size(); column++) {
    column_numerator = g_sys.get(index,column);
    for (int row = index+1; row < g_sys.size(); row++) {
       old = g_sys.get(row,column);
       row_numerator = g_sys.get(row,index);
      // The new value
       new_entry = old - ((row_numerator * column_numerator)/divisor);
      // Set the new value
      g_sys.set(row,column,new_entry);
    }
  }
}
//----------------------------------------------------------------------


// Performs Gaussian elimination to reduce the gaussian system g_sys
// to a triangular matrix. Returns true if back substitution is
// possible on the gaussian-reduced matrix. Returns false otherwise.
// ----------------------------------------------------------------------
bool gaussian_elimination(GaussianSystem& g_sys) {
  // Whether or not the system can be solved by back
  // substitution. Assumed to be true initially.
  bool nondegenerate = true;
  // When a column is bad, that means it has no nonzero entries below
  // a given row. When this happens, we can skip row-reduction for the
  // rest of the column.
  bool good_column;

  // The main loop. Iterate through the columns, row-reducing below
  // the diagonal in each column.
  for (int column = 0; column < g_sys.size(); column++) {
    good_column = pivot(g_sys,column,column);
    nondegenerate = nondegenerate && good_column;
    if ( good_column ) {
      row_reduce(g_sys,column);
    }
  }
  return nondegenerate;
}
// ----------------------------------------------------------------------


// Performs back substitution to extract the values for all unknowns
// of the gaussian system. System is assumed to be
// upper-triangular. However, you can test for upper triangularity if
// you like. If you test for upper-triangularity, raises an error if
// the matrix is not upper-triangular, raises an error. Assumes the
// matrix is non-degenerate. If the matrix is degenerate, raises an
// error.
// ----------------------------------------------------------------------
Dynamic1DArray<double> back_substitution(const GaussianSystem& g_sys,
					 bool check_triangularity/*= false*/) {
  // Check for upper-triangularity
  if ( check_triangularity ) {
    assert( g_sys.is_upper_triangular()
	    && "The system is upper triangular." );
  }

  // Size of the Gaussian system
  int size = g_sys.size();

  // The permutation vector for the gaussian system. Used to ensure
  // that the x indexes for the solved unknowns are those originally
  // inserted.
  Dynamic1DArray<int> permutation;
  permutation = g_sys.get_permutations();

  // The list of values x values attained by back substitution
  Dynamic1DArray<double> output(size);

  // Iterates through the Gaussian system and finds the output by
  // back_substitution.
  for (int i = size-1; i >= 0; i--) {
    // Checks for non-degeneracy.
    assert ( abs(g_sys.matrix_get(i,i)) > DBL_EPSILON
	     && "The matrix is non-degenerate." );

    // After Gauss-Jordan elimination, the solution is just the knowns vector.
    output[i] = g_sys.vector_get(i);
    // But we didn't do Gauss-Jordan elimination. We did Gaussian
    // elimination. So to find the ith element of the solution, we
    // need to subtract the jth elements of the solution with
    // appropriate coefficients, where m > n.
    for (int j = size-1; j > i; j--) {
      output[i] -= g_sys.get(i,j) * output[j];
    }
    // Finally, we need to divide by the coefficient in front of the
    // ith unknown.
    output[i] = output[i]/g_sys.get(i,i);
  }
  // Outputs the solution
  return output;
}
// ----------------------------------------------------------------------


// Outputs a Dynamic1DArray vector in a nice format indicating the
// solution to a matrix equation. Sends it to the appropriate stream
// ----------------------------------------------------------------------
void print_solution(ostream& output_stream,
		    const Dynamic1DArray<double>& solutions_vector,
		    int precision) {
    // halfway through the rows. Where we put the equals sign.
  int halfway = (solutions_vector.length()-1)/2;

  // Sets the notation to scientific
  output_stream << scientific;

  // The rows of the unknowns vector
  for (int row = 0; row < solutions_vector.length(); row++) {
    output_stream << "[ x_" << row << " ]";
    // The equals sign
    if (row == halfway) {
      output_stream << " = ";
    }
    else {
      output_stream << "   ";
    }
    // The values
    output_stream << "[ " << solutions_vector.get(row) << " ]\n";
  }
  output_stream << endl;
}
// ----------------------------------------------------------------------


// Solves the matrix equation by Gaussian elimination and back
// substitution. Prints the solution and returns a solution vector.
// ----------------------------------------------------------------------
Dynamic1DArray<double> solve_system(GaussianSystem& g_sys) {
  bool back_substitution_possible;
  Dynamic1DArray<double> output(0);
  back_substitution_possible = gaussian_elimination(g_sys);
  if ( back_substitution_possible ) {
    output = back_substitution(g_sys);
  } else {
    cout << "Matrix degenerate and back substitution not possible.\n"
	 << "Here's the best I can do:\n"
	 << g_sys
	 << endl;
  }
  return output;
}
// ----------------------------------------------------------------------
