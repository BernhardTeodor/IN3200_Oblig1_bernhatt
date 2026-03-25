#include "function_declarations.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>


void test_read_matrix()
{

    struct sparse_mat_coo x;

    read_sparse_matrix_from_file("data/b1_ss.mtx", &x);

    int actual_n = 7;
    int actual_nnz = 15;
    int actual_row[15] = {5, 6, 7, 1, 2, 1, 3, 1, 4, 2, 5, 3, 6, 4, 7};
    int actual_col[15] = {1, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7};
    double actual_val[15] = {-0.03599942, -0.0176371, -0.007721779, 1, -1, 1, -1, 1, -1, 0.45, 1, 0.1, 1, 0.45, 1};

    assert(x.n == actual_n);
    assert(x.nnz == actual_nnz);

    double tol = 1e-7;

    for (int i = 0; i < actual_nnz; i++)
    {
        assert(actual_col[i] - 1 == x.col_idx[i]);
        assert(actual_row[i] - 1 == x.row_idx[i]);
        assert(abs(actual_val[i] - x.val[i]) < tol);
    }
    printf("Success\n");

    free(x.row_idx);
    free(x.col_idx);
    free(x.val);

}

int main()
{
    test_read_matrix();
    return 0;
}

// RUN: gcc -o test test.c read_sparse_matrix_from_file.c

