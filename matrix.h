#ifndef MATRIX_H
#define MATRIX_H

#include <gsl/gsl_blas.h>

void cmatrix_to_one_dim_matrix(double (*cmatrix)[], int x_limit, int y_limit,
    double **one_dim_matrix_out);

void one_dim_matrix_to_cmatrix(double *one_dim_matrix,
    int x_limit, int y_limit, double (**cmatrix_out)[]);

void power_matrix(double (**cmatrix)[], int n);

#endif
