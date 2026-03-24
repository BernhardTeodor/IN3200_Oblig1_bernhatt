#include <stdio.h>
#include <stdlib.h>
#include "function_declarations.h"


void translate_coo_to_crs(struct sparse_mat_coo *mat_coo, struct sparse_mat_crs *mat_crs)
{


    int *row_ptr = malloc((mat_coo->n + 1) * sizeof(int));

    int *count = malloc(mat_coo->n *sizeof(int));
    row_ptr[0] = 0;
    
    int *next = malloc(mat_coo->n * sizeof(int));
    next[0] = 0;


    for(int i = 0; i < mat_coo->n; i++)
    {  
        count[i] = 0;
        for(int j = 0; j < mat_coo->nnz; j++)
        {
            if(i == mat_coo->row_idx[j])
            {
                count[i] += 1;
            }
        } 
    }


    for(int i = 1; i <= mat_coo->n; i++)
    {
        row_ptr[i] = row_ptr[i -1] + count[i -1];
        next[i] = next[i - 1] + count[i - 1];
    }

    double *val2 = malloc(mat_coo->nnz * sizeof(int));
    int *col2 = malloc(mat_coo->nnz * sizeof(int));

    for(int i = 0; i < mat_coo->nnz; i++)
    {
        int x_i =  mat_coo->row_idx[i];
        val2[next[x_i]] = mat_coo->val[i];
        col2[next[x_i]] = mat_coo->col_idx[i];
        next[x_i] ++;
    }


    mat_crs->n = mat_coo->n;
    mat_crs->nnz = mat_coo->nnz;
    mat_crs->col_idx = col2;
    mat_crs->val = val2;
    mat_crs->row_ptr = row_ptr;



}


