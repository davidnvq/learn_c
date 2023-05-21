#ifndef MATRIX_H
#define MATRIX_H

// Structure to represent a matrix
typedef unsigned char **tMatrice;

// Function to allocate memory for a matrix
extern tMatrice MatAllouer(int NbLig, int NbCol);

// Function to read a matrix from input and return it
extern tMatrice MatLire(int *pNbLig, int *pNbCol);

// Function to display a matrix
extern void MatAfficher(tMatrice Mat, int NbLig, int NbCol);

// Function to create a copy of a matrix
tMatrice MatCopier(tMatrice Mat, int NbLig, int NbCol);

// Function to deallocate memory used by a matrix
extern void MatLiberer(tMatrice *pMat, int NbLig);

#endif
