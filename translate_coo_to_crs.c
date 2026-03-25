#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function_declarations.h"


void translate_coo_to_crs(struct sparse_mat_coo *mat_coo, struct sparse_mat_crs *mat_crs)
{

    int n = mat_coo->n;
    int nnz = mat_coo->nnz;

    int *row_ptr = malloc((n + 1) * sizeof(int));
    row_ptr[0] = 0;

    int *count = calloc(n,sizeof(int));
    int *next = malloc(n * sizeof(int));

    for(int i = 0; i < nnz; i++)
    {  
        count[mat_coo->row_idx[i]]++;     
    }

    for(int i = 1; i <= n; i++)
    {
        row_ptr[i] = row_ptr[i -1] + count[i -1];
    }   

    memcpy(next, row_ptr, n*sizeof(int));

    double *val2 = malloc(nnz * sizeof(double));
    int *col2 = malloc(nnz * sizeof(int));

    for(int i = 0; i < nnz; i++)
    {
        int x_i =  mat_coo->row_idx[i];
        val2[next[x_i]] = mat_coo->val[i];
        col2[next[x_i]] = mat_coo->col_idx[i];
        next[x_i] ++;
    }

    mat_crs->n = n;
    mat_crs->nnz = nnz;
    mat_crs->col_idx = col2;
    mat_crs->val = val2;
    mat_crs->row_ptr = row_ptr;

    free(col2);
    free(val2);

}


