#include <stdio.h>
#include <stdlib.h>
#include "function_declarations.h"



void sampled_matrix_multiplication_crs(struct sparse_mat_crs *C, double **A, double **B, struct sparse_mat_crs *S)
{
    double *values = malloc(S->nnz *sizeof(double));

    for(int i = 0; i < S->n; i++)
    {
        for(int j = S->row_ptr[i]; j < S->row_ptr[i + 1]; j++)
        {
            int col = S->col_idx[j];
            int val = S->val[j];
            double sum = 0.0;
            
            for(int k = 0; k < S->n; k++)
            {
                sum += A[i][k] * B[k][col];
            }
            values[j] = sum * val;
        }
    }



    C->n = S->n;
    C->nnz = S->nnz;
    C->col_idx = S->col_idx;
    C->row_ptr = S->row_ptr;
    C->val = values;
}