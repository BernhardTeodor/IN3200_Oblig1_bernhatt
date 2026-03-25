#include "function_declarations.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>


 // A = (
    // 1 2 3
    // 4 5 6
    // 7 8 9
    // )

    // B = (
    // 1 4 7
    // 2 5 8
    // 3 6 9
    // )

    // A x B = (
    // 14 32 50
    // 32 77 122
    // 50 122 194
    // )

    // S = (
    // 1 2 0
    // 0 3 0
    // 4 0 0
    // )

    // C = (
    // 14 64 0
    // 0 231 0
    // 200 0 0
    // )



void test_sampled_matrix_multiplication_coo()
{

    struct sparse_mat_coo Actual_C;
    Actual_C.n = 3;
    Actual_C.nnz = 4;

    double values[4] = {14, 64, 231, 200};
    int row[4] = {1,1,2,3};
    int col[4] = {1,2,2,1};

    Actual_C.val = values;
    Actual_C.row_idx = row;
    Actual_C.col_idx = col;

    // Creating A and B
    double **A, **B;
    int n = 3;
    A = malloc(n*sizeof(double *));
    A[0] = malloc(n*n*sizeof(double));
    
    B = malloc(n*sizeof(double*));
    B[0] = malloc(n*n*sizeof(double)); 

    // Fixing index
    for(int i = 0; i < n; i++)
    {
        A[i] = A[0] + i*n;
        B[i] = B[0] + i*n;
    }   

    // Filling with correct values
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            A[i][j] = 1+j + 3*i;
            B[j][i] = 1+j + 3*i; 
        }
    }

    
    // Creating S and C

    struct sparse_mat_coo S;
    S.n = 3;
    S.nnz = 4;
    S.row_idx = row;
    S.col_idx = col;
    
    double s_value[4] = {1, 2, 3, 4}; 
    S.val = s_value;
    
    struct sparse_mat_coo C;

    sampled_matrix_multiplication_coo(&C, A, B, &S);

    double tol  = 1e-7;

    for(int i = 0; i < S.nnz; i++)
    {
        assert(C.n == Actual_C.n);
        assert(C.nnz == Actual_C.nnz);
        assert(C.row_idx[i] == Actual_C.row_idx[i]);
        assert(C.col_idx[i] == Actual_C.col_idx[i]);
        assert(abs(C.val[i] -Actual_C.val[i] )< tol);
    }
    
    printf("Success");

    free(A[0]);
    free(A);
    free(B[0]);
    free(B);

}

int main()
{
    test_sampled_matrix_multiplication_coo();
    return 0;
}