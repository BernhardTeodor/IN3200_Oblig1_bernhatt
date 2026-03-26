#include "function_declarations.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <stdbool.h>

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

// C.row_ptr = (0, 2, 3, 4)

void test_sampled_matrix_multiplication_crs()
{

    double **A, **B;
    int n = 3;
    A = malloc(n*sizeof(double *));
    A[0] = malloc(n*n*sizeof(double));

    B = malloc(n*sizeof(double*));
    B[0] = malloc(n*n*sizeof(double)); 

    for(int i = 0; i < n; i++)
    {
        A[i] = A[0] + i*n;
        B[i] = B[0] + i*n;
    }   

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            A[i][j] = 1+j + 3*i;
            B[j][i] = 1+j + 3*i; 
        }
    }

    int row[4] = {0,0,1,2};
    int col[4] = {0,1,1,0};

    struct sparse_mat_coo S;
    S.n = 3;
    S.nnz = 4;
    S.row_idx = row;
    S.col_idx = col;

    double s_value[4] = {1, 2, 3, 4}; 
    S.val = s_value;

    struct sparse_mat_crs S_crs;
    S_crs.n = S.n; S_crs.nnz = S.nnz;
    S_crs.row_ptr = (int*)malloc((S_crs.n+1) * sizeof(int));
    S_crs.col_idx = (int*)malloc(S_crs.nnz * sizeof(int));
    S_crs.val = (double*)malloc(S_crs.nnz * sizeof(double));

    translate_coo_to_crs(&S, &S_crs);

    struct sparse_mat_crs C;
    C.n = S.n; C.nnz = S.nnz;
    C.row_ptr = (int*)malloc((S.n + 1) * sizeof(int));
    C.col_idx = (int*)malloc(S.nnz * sizeof(int));
    C.val = (double*)malloc(S.nnz * sizeof(double));

    sampled_matrix_multiplication_crs(&C, A, B, &S_crs);

    int actual_rowptr[4] ={0, 2, 3, 4};

    for(int i = 0; i < 4; i++)
    {
        assert(actual_rowptr[i] == C.row_ptr[i]);
    }

    int actual_nnz = 4;
    assert(C.nnz == actual_nnz);
    int actual_n = 3;
    assert(C.n == actual_n);


    for(int i = 0; i<C.nnz; i++)
    {
        printf("i = %d, C.val[i] = %f\n",i, C.val[i]);
    }


    bool row1_14 = (C.val[0] == 14 || C.val[1] == 14);
    bool row1_64 = (C.val[0] == 64 || C.val[1] == 64);

    bool row2 = (C.val[2] - 231 < 1e-7);
    bool row3 = (C.val[3] - 200 < 1e-7);

    assert(row1_14);
    assert(row1_64);
    assert(C.val[2] == 231);
    assert(C.val[3] ==200);

    printf("Success\n");

    free(A[0]);
    free(A);
    free(B[0]);
    free(B);
}

int main()
{
    test_sampled_matrix_multiplication_crs();
    return 0;
}