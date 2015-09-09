#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <gsl/gsl_blas.h>

#include "matrix.h"

void cmatrix_to_one_dim_matrix(double (*cmatrix)[20],
    int x_limit, int y_limit,
    double **one_dim_matrix_out)
  /* ! free one_dim_matrix */
{
  double *one_dim_matrix = malloc(x_limit * y_limit * sizeof(double));
  int x, y, i;

  for (y = 0, i = 0; y < y_limit; y++) {
    for (x = 0; x < x_limit; x++, i++) {
      one_dim_matrix[i] = cmatrix[y][x];
    }
  }


  /* assign return variabels */
  *one_dim_matrix_out = one_dim_matrix;
}

void one_dim_matrix_to_cmatrix(double *one_dim_matrix,
    int x_limit, int y_limit, double (**cmatrix_out)[])
{
  int x, y, i;
  double (*cmatrix)[20];
  cmatrix = malloc(sizeof(double[20][20]));
  

  for (y = 0, i = 0; y < y_limit; y++) {
    for (x = 0; x < x_limit; x++, i++) {
      cmatrix[y][x] = one_dim_matrix[i];
    }
  }

  /* assign return variabels */
  *cmatrix_out = cmatrix;
}

void power_matrix(double (**cmatrix)[20], int n)
{
  double *multiplier;
  double *result;
  double *one_dim_matrix;
  gsl_matrix_view power_gsl_matrix[2];
  gsl_matrix_view multiplier_gsl_matrix;
  int i;

  cmatrix_to_one_dim_matrix(*cmatrix, 20, 20, &one_dim_matrix);

  multiplier = malloc(20 * 20 * sizeof(double));
  result = malloc(20 * 20 * sizeof(double));

  memcpy((void*)multiplier, (void*)one_dim_matrix, 20 * 20 * sizeof(double));

  multiplier_gsl_matrix =  gsl_matrix_view_array(multiplier, 20, 20);

  /* power matrix */
  for (i = 1; i < n; i++) {
    power_gsl_matrix[0] =  gsl_matrix_view_array(one_dim_matrix, 20, 20);
    power_gsl_matrix[1] =  gsl_matrix_view_array(result, 20, 20);

    gsl_blas_dgemm (CblasNoTrans, CblasNoTrans,
        1.0, &power_gsl_matrix[0].matrix, &multiplier_gsl_matrix.matrix,
        0.0, &power_gsl_matrix[1].matrix);

    memcpy((void*)one_dim_matrix, (void*)result, 20 * 20 * sizeof(double));
  }
  /*
  for (i = 0 ; i < 20 * 20; i++) {
    if (!(i % 20))
      printf("\n");
    printf("%.4f ", result[i]);
  }
  printf("\n");
  */

  /* assign returned variables */
  one_dim_matrix_to_cmatrix(result, 20, 20, cmatrix);

  /* free alocated memory */
  free(one_dim_matrix);
  free(multiplier);
  free(result);
}

