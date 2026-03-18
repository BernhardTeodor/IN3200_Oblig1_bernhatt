#include <stdio.h>
#include <stdlib.h>
#include "function_declarations.h"


void read_sparse_matrix_from_file(char *filename, struct sparse_mat_coo *matrix)
{

    FILE *fp = fopen(filename, "r");
    char buffer[1024] = {0};
    if (fp == NULL)
    {
        printf("Error in opening file/n");
        exit(1);
    }

    while(fgets(buffer,sizeof(buffer), fp)[0] == '%')
    {
    }

    int row, col, nnz;
    sscanf(buffer, "%d %d %d", &row, &col, &nnz);

    matrix->n = row;
    matrix->nnz = nnz;

    int *row_array = malloc(matrix->nnz* sizeof(int));
    int *col_array = malloc(matrix->nnz* sizeof(int));

    double *values = malloc(matrix->nnz* sizeof(double));

    for (int i = 0; i < matrix->nnz; i++)
    {
        fscanf(fp, "%d %d %lf", &row_array[i], &col_array[i], &values[i]);
    }

    matrix->row_idx = row_array;
    matrix->col_idx = col_array;
    matrix->val = values;
    fclose(fp);

}