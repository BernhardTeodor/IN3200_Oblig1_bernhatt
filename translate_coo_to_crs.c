#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function_declarations.h"


void translate_coo_to_crs(struct sparse_mat_coo *mat_coo, struct sparse_mat_crs *mat_crs)
{

    int n = mat_coo->n;
    int nnz = mat_coo->nnz;

    mat_crs->row_ptr[0] = 0;

    int *count = calloc(n,sizeof(int));
    int *next = malloc(n * sizeof(int));

    for(int i = 0; i < nnz; i++)
    {  
        count[mat_coo->row_idx[i]]++;     
    }

    for(int i = 1; i <= n; i++)
    {
        mat_crs->row_ptr[i] = mat_crs->row_ptr[i -1] + count[i -1];
    }   

    memcpy(next, mat_crs->row_ptr, n*sizeof(int));

    for(int i = 0; i < nnz; i++)
    {
        int x_i =  mat_coo->row_idx[i];
        mat_crs->val[next[x_i]] = mat_coo->val[i];
        mat_crs->col_idx[next[x_i]] = mat_coo->col_idx[i];
        next[x_i] ++;
    }

    free(next);
    free(count);

}


