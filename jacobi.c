#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "jacobi.h"
#include "matrix.h"

/* Number of threads used */
#define NR_THREADS 1

void jacobi(char *inFilename, char *outFilename)
{
	int size;

    double **a, *c;
    double *a_block;

    int i, j;

    FILE *fin, *fout;
    fin = fopen(inFilename, "r");
    if(fin == NULL )
    {
       perror("Error while opening input file.\n");
       exit(EXIT_FAILURE);
    }
    fout = fopen(outFilename, "w");
    if(fout == NULL )
    {
       perror("Error while opening output file.\n");
       exit(EXIT_FAILURE);
    }

	fscanf(fin, "%d", &size);

    a = (double **) malloc(size*sizeof(double *)); /* matrix a to be multiplied */
    c = (double *) malloc(size*sizeof(double *)); /* result matrix c */

    a_block = (double *) malloc(size*size*sizeof(double)); /* Storage for matrices */
    for (i=0; i<size; i++)   /* Initialize pointers to a */
        a[i] = a_block+i*size;


    printf("Data read is :\n");
	for(i=0; i<size; i++) {
		for(j=0; j<size; j++) {
			fscanf(fin, "%lf", &a[i][j]);
			printf("%f, ", a[i][j]);
		}
		fscanf(fin, "%lf", &c[i]);
		printf("%f\n", c[i]);
	}

	double *approx1, *approx2;
	int tid;
	int count = 0;

	double sum, temp;
	int p,q;

	approx1 = (double *) malloc(size*sizeof(double *));
	approx2 = (double *) malloc(size*sizeof(double *));

	// initialize all elements to zero
	// #pragma omp for
	for(p=0; p<size; p++)
	{
		approx1[p] = 0;
		approx2[p] = 0;
	}

	int repeat = 1;
	double diff;

	printf("Starting Jacobi's iteration with SIZE : %d...\n", size);

//#pragma omp parallel shared(approx1,approx2) private(tid,p,q, temp, sum) num_threads(NR_THREADS)
	{
		tid = omp_get_thread_num();
		if (tid == 0)
		{
			/* Only thread 0 prints */
			//nthreads = omp_get_num_threads();
			// printf("Starting Approximation with %d threads\n",nthreads);
			printf("\n");
		}

		while(repeat)
		{
			count++;

//#pragma omp parallel for
			for(p=0; p<size; p++)
			{
				sum = 0;
				for(q=0; q<size; q++)
				{
					sum += a[p][q] * approx1[q];
				}
				temp = a[p][p] * approx1[p];
				approx2[p] = (c[p] - (sum - temp))/a[p][p];
				// printf("Values for %d are %f, %f, %f, %f, %f and %f\n", p, sum, temp, approx1[p], approx2[p], a[p][p], c[p]);
			}
			diff = 0;
			repeat = 0;
			// printf("\nresultant matrix in iteration %d : ", count);
			for(p=0; p<size; p++)
			{
				diff += fabs(approx1[p] - approx2[p]);
				if (diff > TOL) repeat = 1;
				approx1[p] = approx2[p];
				// printf("%f, ",approx2[p]);
			}
			// printf("(%f)\n", diff);

			//getchar();
		}
	}

	printf("\nFinal resultant matrix (after %d iterations using Jacobi) in %s\n", count, outFilename);
	for(p=0; p<size; p++)
	{
		fprintf(fout, "%f\n",approx2[p]);
	}

    fclose(fin);
    fclose(fout);
}

void generate_jacobi_data(char *filename, int size)
{
    int	i, j;
    double **a, **b, **c;
    double *a_block, *b_block, *c_block;

    a = (double **) malloc(size*sizeof(double *)); /* matrix a to be multiplied */
    b = (double **) malloc(size*sizeof(double *)); /* matrix b to be multiplied */
    c = (double **) malloc(size*sizeof(double *)); /* result matrix c */

    a_block = (double *) malloc(size*size*sizeof(double)); /* Storage for matrices */
    b_block = (double *) malloc(size*size*sizeof(double));
    c_block = (double *) malloc(size*size*sizeof(double));

    FILE *fout;
    fout = fopen(filename, "w");
    if(fout == NULL )
    {
       perror("Error while opening output file.\n");
       exit(EXIT_FAILURE);
    }

    for (i=0; i<size; i++)   /* Initialize pointers to a */
        a[i] = a_block+i*size;

    for (i=0; i<size; i++)   /* Initialize pointers to b */
        b[i] = b_block+i*size;

    for (i=0; i<size; i++)   /* Initialize pointers to c */
        c[i] = c_block+i*size;

    srand(time(NULL));
    init_jacobi_matrix(a, size);
    init_matrix(b, size, 1, 0, 100);
    matrix_mul(size, size, 1, a, b, c);

    for(i=0; i<size; i++) {
        for(j=0; j<size; j++) {
        	fprintf(fout, "%lf ", a[i][j]);
        }
        fprintf(fout, "%lf ", c[i]);
    }

}

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








