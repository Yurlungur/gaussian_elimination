// gaussian_elimination.hpp

// Author: Jonah Miller (jonah.maxwell.miller@gmail.com)
// Time-stamp: <2013-08-06 18:14:33 (jonah)>

// This file prototypes the Gaussian elimination library, which is a
// set of functions to solve non-degenerate linear systems by Gaussian
// elimination.

// This library is designed to be used with the gaussian_system data
// structure.
// ----------------------------------------------------------------------


// Include guard
#pragma once
// ----------------------------------------------------------------------


// Includes
#include "dynamic_array.hpp"
#include "gaussian_system.hpp"
#include <iostream>
using namespace std;
// ----------------------------------------------------------------------


// Looks for the row k of gaussian system g_sys below row i such that
// the element in the kth row and jth column is the largest element in
// column j. Swaps the rows i and k. It is possible that there are no
// non-zero entries in column j below row i. If this is the case,
// returns false. Otherwise returns true.
bool pivot(GaussianSystem& g_sys, int i, int j);


// Makes every element in column=index and a row below row=index in
// the gaussian system zero. Affects other elements of the matrix.
void row_reduce(GaussianSystem& g_sys, int index);


// Performs Gaussian elimination to reduce the gaussian system g_sys
// to a triangular matrix. Returns true if back substitution is
// possible on the gaussian-reduced matrix. Returns false otherwise.
bool gaussian_elimination(GaussianSystem& g_sys);

// Performs back substitution to extract the values for all unknowns
// of the gaussian system. System is assumed to be
// upper-triangular. However, you can test for upper triangularity if
// you like. If you test for upper-triangularity, raises an error if
// the matrix is not upper-triangular, raises an error. Assumes the
// matrix is non-degenerate. If the matrix is degenerate, raises an
// error.
Dynamic1DArray<double> back_substitution(const GaussianSystem& g_sys,
					 bool check_triangularity = false);

// Outputs a Dynamic1DArray vector in a nice format indicating the
// solution to a matrix equation. Sends it to the appropriate stream
void print_solution(ostream& output_stream,
		    const Dynamic1DArray<double>& solutions_vector,
		    int precision);

