#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "common.h"
#include "matrix.h"

#define SIZE 1500

int main()
{
    int	i;
    double **a, **b, **c;
    double *a_block, *b_block, *c_block;

    a = (double **) malloc(SIZE*sizeof(double *)); /* matrix a to be multiplied */
    b = (double **) malloc(SIZE*sizeof(double *)); /* matrix b to be multiplied */
    c = (double **) malloc(SIZE*sizeof(double *)); /* result matrix c */

    a_block = (double *) malloc(SIZE*SIZE*sizeof(double)); /* Storage for matrices */
    b_block = (double *) malloc(SIZE*SIZE*sizeof(double));
    c_block = (double *) malloc(SIZE*SIZE*sizeof(double));


    for (i=0; i<SIZE; i++)   /* Initialize pointers to a */
        a[i] = a_block+i*SIZE;

    for (i=0; i<SIZE; i++)   /* Initialize pointers to b */
        b[i] = b_block+i*SIZE;

    for (i=0; i<SIZE; i++)   /* Initialize pointers to c */
        c[i] = c_block+i*SIZE;

    srand(time(NULL));
    init_jacobi_matrix(a, SIZE);
    init_matrix(b, SIZE, 1, 0, 100);
    matrix_mul(SIZE, SIZE, 1, a, b, c);
    printf("A Matrix is :\n");
    // display_matrix(a, SIZE, SIZE);

    printf("B Matrix is :\n");
    display_matrix(b, SIZE, 1);

    printf("C Matrix is :\n");
    // display_matrix(c, SIZE, 1);

    jacobi(a, c, SIZE);

    return 0;
}
