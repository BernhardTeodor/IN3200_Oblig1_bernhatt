#include <stdio.h>
#include <stdlib.h>
#include "function_declarations.h"



void sampled_matrix_multiplication_crs(struct sparse_mat_crs *C, double **A, double **B, struct sparse_mat_crs *S)
{

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
            C->val[j] = sum * val;
        }
    }

}