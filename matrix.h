#ifndef MATRIX_H
#define MATRIX_H

// Structure to represent a matrix
typedef struct
{
    int rows;
    int cols;
    unsigned char **data;
} Matrix;
typedef unsigned char **tMatrix;

// Function to allocate memory for a matrix
tMatrix MatAllouer(int NbLig, int NbCol);

// Function to read a matrix from input and return it
tMatrix MatLire(int *pNbLig, int *pNbCol);

// Function to display a matrix
void MatDisplay(tMatrix Mat, int NbLig, int NbCol);

// Function to create a copy of a matrix
tMatrix MatCopy(tMatrix Mat, int NbLig, int NbCol);

// Function to deallocate memory used by a matrix
void MatLiberer(tMatrix *pMat, int NbLig);

#endif
