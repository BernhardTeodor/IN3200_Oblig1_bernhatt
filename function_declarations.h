#ifndef FUNCTION_DECLARATIONS
#define FUNCTION_DECLARATIONS

struct sparse_mat_coo {
    int n, nnz;
    double *val;
    int *row_idx, *col_idx;
};

struct sparse_mat_crs {
    int n, nnz;
    double *val;
    int *row_ptr, *col_idx;
};

void read_sparse_matrix_from_file(char *filename, struct sparse_mat_coo *matrix);

#endif
