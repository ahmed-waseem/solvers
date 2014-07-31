#include "common.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"

/* Number of threads used */
#define NR_THREADS 1

void jacobi(double **a, double **c, int size)
{
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
				approx2[p] = (c[p][0] - (sum - temp))/a[p][p];
				// printf("Values for %d are %f, %f, %f, %f, %f and %f\n", p, sum, temp, approx1[p], approx2[p], a[p][p], c[p][0]);
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

	printf("\nFinal resultant matrix (after %d iterations using Jacobi): ", count);
	for(p=0; p<size; p++)
	{
		printf("%f, ",approx2[p]);
	}
	printf("\n");
}








