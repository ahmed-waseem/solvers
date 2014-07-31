/*
 * matrix.h
 *
 *  Created on: Jul 31, 2014
 *      Author: waseem
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include <time.h>
#include <stdlib.h>

void init_jacobi_matrix(double **x, int size);
void init_matrix(double **x, int row, int column, int min, int max);
void matrix_mul(int rowA, int colA, int colB,  double **x, double **y, double **z);
void display_matrix(double **x, int row, int col);

#endif /* MATRIX_H_ */
