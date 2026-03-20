#include <stdio.h>
#include <stdlib.h>
#include "function_declarations.h"


void sampled_matrix_multiplication_coo(struct sparse_mat_coo *C, double **A, double **B, struct sparse_mat_coo *S)
{
    double **AxB;
    int n = S->n;

    AxB = malloc(n*sizeof(double*));
    AxB[0]= malloc(n*n*sizeof(double));

    for(int i = 1; i < n +1; i++)
    {
        AxB[i] = AxB[0] + i*n;
    }

    double *values = malloc(S->nnz *sizeof(double));

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            AxB[i][j] = 0;
            for(int k = 0; k < n; k++)
            {
                AxB[i][j] += A[i][k]*B[k][j];
            }
        }
    }

    for(int i = 0; i < S->nnz; i++)
    {
        int row =S->row_idx[i];
        int col =S->col_idx[i];
        double s = S->val[i];
        values[i] = AxB[row - 1][col - 1] * s;
    }

    C->n = S->n;
    C->nnz = S->nnz;
    C->col_idx = S->col_idx;
    C->row_idx = S->row_idx;
    C->val = values;

    free(AxB[0]);
    free(AxB);
}