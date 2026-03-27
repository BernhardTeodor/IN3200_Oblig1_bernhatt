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


// Reads and fills a sparse matrix in COO format.
//
// Parameters
// ----------
// filename: Filename or path to file
// matrix: Empty sparse_mat_coo.
//
// Output
// ---------------
// matrix filled with values from file
void read_sparse_matrix_from_file(char *filename, struct sparse_mat_coo *matrix);

// Executes the sampled dense matrix multiplication C = (A x B) ⊙ S when S and C are COO.
// 
// Parameters
// ----------
// C: Sparse matrix in COO-format. Same n,nnz,row and col as S and predefined memory for values.
// A,B: Matrices of doubles
// S: Sparse matrix in the COO-format.
//
// Output
// ---------------
// Matrix C filled with values from (A x B) ⊙ S on COO-format
void sampled_matrix_multiplication_coo(struct sparse_mat_coo *C, double **A, double **B, struct sparse_mat_coo *S);


// Translates a matrix on COO-format to CRS-format
//
// Parameters
// ----------
// mat_coo: A matrix on COO-format
// mat_crs: A matrix with same n and nnz as mat_coo and predefined memory for row,col and val.
//
// Output
// ------
// The matrix on COO-format in CRS-format
void translate_coo_to_crs(struct sparse_mat_coo *mat_coo, struct sparse_mat_crs *mat_crs);

// Executes the sampled dense matrix multiplication C = (A x B) ⊙ S when S and C are COO.
//
// Parameters
// ----------
// C: Sparse matrix in CRS-format. Same n,nnz,row and col as S and predefined memory for values.
// A,B: Matrices of doubles
// S: Sparse matrix in the CRS-format.
//
// Output
// ---------------
// Matrix C filled with values from (A x B) ⊙ S on CRS-format
void sampled_matrix_multiplication_crs(struct sparse_mat_crs *C, double **A, double **B, struct sparse_mat_crs *S);

#endif
