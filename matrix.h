#ifndef MATRIX_H
#define MATRIX_H

// Structure to represent a matrix
typedef struct
{
    int rows;
    int cols;
    unsigned char **data;
} Matrix;

// Function to allocate memory for a matrix
Matrix *MatAllocate(int rows, int cols);

// Function to read a matrix from input and return it
Matrix *MatRead(int *pRows, int *pCols);

// Function to display a matrix
void MatDisplay(Matrix *mat);

// Function to create a copy of a matrix
Matrix *MatCopy(Matrix *mat);

// Function to deallocate memory used by a matrix
void MatFree(Matrix **mat);

#endif
