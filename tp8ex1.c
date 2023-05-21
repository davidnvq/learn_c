#include <stdio.h>
#include <stdlib.h>
#include "matrix.c"

int main()
{
    int NbLig = 3;
    int NbCol = 4;

    tMatrix matrix = MatAllouer(NbLig, NbCol);
    if (matrix == NULL)
    {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Access and modify matrix elements
    matrix[0][0] = 1;
    matrix[1][2] = 2;

    // Free the memory allocated for the matrix
    free(matrix[0]); // Free the data
    free(matrix);    // Free the row pointers

    tMatrix matrix1 = MatLire(&NbLig, &NbCol);

    MatDisplay(matrix1, NbLig, NbCol);

    // Create a copy of the matrix
    tMatrix copy = MatCopy(matrix1, NbLig, NbCol);

    MatDisplay(copy, NbLig, NbCol);

    // TODO: Can't work properly.
    // MatLiberer(&matrix1, NbLig);
    // MatLiberer(&copy, NbLig);

    return 0;
}