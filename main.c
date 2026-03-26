#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "function_declarations.h"

int main (int nargs, char **args)
{
    char filename[80] = "";
    double **A, **B;
    struct sparse_mat_coo S_coo, C_coo;
    struct sparse_mat_crs S_crs, C_crs;
    

    // read from command line the name of a data file in the matrix market exchange format
    strcat(filename, "data/");
    strcat(filename, args[1]);


    // read a sparse matrix from the matrix market data file, and store it in S_coo
    read_sparse_matrix_from_file (filename, &S_coo);


    // create the corresponding COO data structure C_coo
    C_coo.n = S_coo.n; C_coo.nnz = S_coo.nnz;
    C_coo.row_idx = S_coo.row_idx;
    C_coo.col_idx = S_coo.col_idx;
    C_coo.val = (double*)malloc(C_coo.nnz * sizeof(double));

    
    // allocate A and B as 2D n x n arrays and assign suitable numerical values
    int n = S_coo.n;
    A = malloc(n*sizeof(double *));
    A[0] = malloc(n*n*sizeof(double));
    
    B = malloc(n*sizeof(double*));
    B[0] = malloc(n*n*sizeof(double)); 

    for(int i = 0; i < n; i++)
    {
        A[i] = A[0] + i*n;
        B[i] = B[0] + i*n;
    }   

    srand(time(NULL));

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            A[i][j] = rand() %1000;
            B[j][i] = rand() %1000; 
        }
    }


    // // computation 1
    sampled_matrix_multiplication_coo (&C_coo, A, B, &S_coo);


    // // allocate CRS data structure S_crs
    S_crs.n = S_coo.n; S_crs.nnz = S_coo.nnz;
    S_crs.row_ptr = (int*)malloc((S_crs.n+1) * sizeof(int));
    S_crs.col_idx = (int*)malloc(S_crs.nnz * sizeof(int));
    S_crs.val = (double*)malloc(S_crs.nnz * sizeof(double));
    

    // // translate from S_coo to S_crs
    translate_coo_to_crs (&S_coo, &S_crs);


    // // allocate CRS data structure C_crs
    C_crs.n = S_crs.n; C_crs.nnz = S_crs.nnz;
    C_crs.row_ptr = S_crs.row_ptr;
    C_crs.col_idx = S_crs.col_idx;
    C_crs.val = (double*)malloc(C_crs.nnz * sizeof(double));


    // // computation 2
    sampled_matrix_multiplication_crs (&C_crs, A, B, &S_crs);


    // deallocate data structures
    free(S_coo.row_idx);
    free(S_coo.col_idx);
    free(S_coo.val);
    free(C_coo.val);
    free(A[0]);
    free(B[0]);
    free(A);
    free(B);
    free(S_crs.row_ptr);
    free(S_crs.col_idx);
    free(S_crs.val);
    free(C_crs.val);

    return 0;
}
