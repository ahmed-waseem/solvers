/*
 * matrix.c
 *
 *  Created on: Jul 31, 2014
 *      Author: waseem
 */

#include <stdio.h>
#include "matrix.h"

/*
 * Purpose : Initializes a matrix for Jacobi calculations with random values
 * 			 The diagonal will have higher elements as compared to the others.
 * Input : 	1. Matrix
 * 			2. Row size
 * 			3. Column size
 */
void init_jacobi_matrix(double **x, int size)
{

    int	i, j;

    for(i=0; i<size; i++)
        for(j=0; j<size; j++)
            if(i==j)
            {
                x[i][j] = (rand() % 10)+10000;
            }
            else
                x[i][j] = (rand() % 5)+1;

}

/*
 * Purpose : Initializes a matrix with random values
 * Input : 	1. Matrix
 * 			2. Row size
 * 			3. Column size
 * 			4. Min Range
 * 			5. Max Range
 * to initialize a 1-D vector keep row size as 1
 */
void init_matrix(double **x, int row, int column, int min, int max)
{
    int	i, j;

    for(i=0; i<row; i++)
        for(j=0; j<column; j++)
        	x[i][j] = (rand() % max) + min;
}

/*
 * Purpose : Multiplies two matrices and stores results in a specified resultant matrix
 * Input : 	1. Row A
 * 			2. Col A
 * 			3. Col B
 * 			4. First Matrix
 * 			5. Second Matrix
 * 			6. Result Matrix
 *
 */
void matrix_mul(int rowA, int colA, int colB,  double **x, double **y, double **z)
{
    int	i, j, k;
    double sum;

        for (i=0; i<rowA; i++)
        {
            for(j=0; j<colB; j++)
            {
                sum=0;
                for(k=0; k<colA; k++)
                    sum += x[i][k] * y[k][j];
                z[i][j] = sum;
            }
        }
}

/*
 * Purpose : Display a matrix in row-col order
 * Input : 	1. Matrix
 * 			2. No. of rows
 * 			3. no. of columns
 *
 */
void display_matrix(double **x, int row, int col)
{
    int i, j;
    for (i=0; i<row; i++)
    {
        for(j=0; j<col; j++)
            printf("%f\t",x[i][j]);
        printf("\n");
    }
    printf("\n");
}

