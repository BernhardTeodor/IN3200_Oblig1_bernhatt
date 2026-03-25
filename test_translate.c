#include "function_declarations.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>


// A = (
// 0 2 5 0
// 0 0 0 4
// 6 3 0 0
// 0 0 1 7
// )     



void test_translate()
{

    double values[7] = {2, 5, 4, 6, 3, 1, 7};
    int row[7] = {0, 0, 1, 2, 2, 3, 3};
    int col[7] = {1, 2, 3, 0, 1, 2, 3};
    int n = 4;
    int nnz = 7;

    struct sparse_mat_coo x;

    x.val = values;
    x.row_idx = row;
    x.col_idx = col;
    x.n = n;
    x.nnz = nnz;

    
    struct sparse_mat_crs y;
    
    translate_coo_to_crs(&x, &y);

    int actual_rowptr[5] ={0, 2, 3, 5, 7};

    for(int i = 0;  i < 5; i++)
    {
        assert(y.row_ptr[i] == actual_rowptr[i]);
    }

    for(int i = 0; i < x.nnz; i ++)
    {
        assert(y.col_idx[i] == col[i]);
        assert(abs(y.val[i]-values[i]) < 1e-7);

    }

    printf("Success 111\n");
}


void test_read_and_convert()
{

    int row_ptr[8] = {0,3,5,7,9,11,13,15};

    struct sparse_mat_coo x;
    struct sparse_mat_crs y;
    read_sparse_matrix_from_file("data/b1_ss.mtx",&x);

    translate_coo_to_crs(&x,&y);

    for(int i = 0; i< x.n; i++)
    {
        assert(row_ptr[i] == y.row_ptr[i]);
    }

    printf("success 222 \n");
}




int main()
{   
    test_translate();
    test_read_and_convert();
    return 0;
}