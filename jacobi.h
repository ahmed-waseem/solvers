/*
 * jacobi.h
 *
 *  Created on: Jul 31, 2014
 *      Author: waseem
 */

#ifndef JACOBI_H_
#define JACOBI_H_

#define TOL 0.0001

void jacobi(char *inFilename, char *outFilename);
void generate_jacobi_data(char *filename, int size);
void init_jacobi_matrix(double **x, int size);

#endif /* JACOBI_H_ */
