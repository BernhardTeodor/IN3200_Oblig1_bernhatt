#include <stdio.h>
#include <stdlib.h>
#include "function_declarations.h"


void sampled_matrix_multiplication_coo(struct sparse_mat_coo *C, double **A, double **B, struct sparse_mat_coo *S)
{
    for(int i = 0; i < S->nnz; i++)
    {
        int row = S->row_idx[i];
        int col = S->col_idx[i]; 
        double s = S->val[i];       
        double sum = 0.0;

        for(int j = 0; j < S->n; j++)
        { 
            sum += A[row][j] * B[j][col];          
        }
        C->val[i] = sum * s;
    }
}