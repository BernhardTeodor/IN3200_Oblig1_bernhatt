#include <stdio.h>
#include <stdlib.h>
#include "function_declarations.h"


void read_sparse_matrix_from_file(char *filename, struct sparse_mat_coo *matrix)
{

    FILE *fp = fopen(filename, "r");
    
    if (fp == NULL)
    {
        printf("Error in opening file/n");
        exit(1);
    }


    fclose(fp);

}