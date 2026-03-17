int main (int nargs, char **args)
{
    char filename[80];
    double **A, **B;
    struct sparse_mat_coo S_coo, C_coo;
    struct sparse_mat_crs S_crs, C_crs;

    // read from command line the name of a data file in the matrix market exchange format
    // ....


    // read a sparse matrix from the matrix market data file, and store it in S_coo
    read_sparse_matrix_from_file (filename, &S_coo);

    // create the corresponding COO data structure C_coo
    C_coo.n = S_coo.n; C_coo.nnz = S_coo.nnz;
    C_coo.row_idx = S_coo.row_idx;
    C_coo.col_idx = S_coo.col_idx;
    C_coo.val = (double*)malloc(C_coo.nnz * sizeof(double));
    
    // allocate A and B as 2D n x n arrays and assign suitable numerical values
    // ....
    
    // computation 1
    sampled_matrix_multiplication_coo (&C_coo, A, B, &S_coo);
    
    // allocate CRS data structure S_crs
    S_crs.n = S_coo.n; S_crs.nnz = S_coo.nnz;
    S_crs.row_ptr = (int*)malloc((S_crs.n+1) * sizeof(int));
    S_crs.col_idx = (int*)malloc(S_crs.nnz * sizeof(int));
    S_crs.val = (double*)malloc(S_crs.nnz * sizeof(double));
    
    // translate from S_coo to S_crs
    translate_coo_to_crs (&S_coo, &S_crs);
    
    // allocate CRS data structure C_crs
    C_crs.n = S_crs.n; C_crs.nnz = S_crs.nnz;
    C_crs.row_ptr = S_crs.row_ptr;
    C_crs.col_idx = S_crs.col_idx;
    C_crs.val = (double*)malloc(C_crs.nnz * sizeof(double));
    
    // computation 2
    sampled_matrix_multiplication_crs (&C_crs, A, B, &S_crs);
    
    // deallocate data structures
    // .....
    
    return 0;
}
