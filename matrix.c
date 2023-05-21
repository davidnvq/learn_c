#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

#define NBLIGMAX 100
#define NBCOLMAX 100
unsigned char tab[NBLIGMAX][NBCOLMAX];

tMatrix MatAllouer(int NbLig, int NbCol)
{
    // Allocate memory for the matrix data
    unsigned char *data = (unsigned char *)malloc(NbLig * NbCol * sizeof(unsigned char));
    if (data == NULL)
    {
        // Memory allocation failed
        return NULL;
    }

    // Allocate memory for the row pointers
    unsigned char **rows = (unsigned char **)malloc(NbLig * sizeof(unsigned char *));
    if (rows == NULL)
    {
        // Memory allocation failed
        free(data);
        return NULL;
    }

    // Fill the row pointers with the start addresses of the rows
    for (int i = 0; i < NbLig; i++)
    {
        rows[i] = &data[i * NbCol];
    }

    // Return the matrix
    return rows;
}

tMatrix MatLire(int *pNbLig, int *pNbCol)
{
    // Ask the user for the number of rows and columns
    printf("Enter the number of rows: ");
    scanf("%d", pNbLig);
    printf("Enter the number of columns: ");
    scanf("%d", pNbCol);

    // Allocate the matrix
    tMatrix matrix = MatAllouer(*pNbLig, *pNbCol);
    if (matrix == NULL)
    {
        printf("Memory allocation failed\n");
        return NULL;
    }

    // Read the elements from the user
    for (int i = 0; i < *pNbLig; i++)
    {
        printf("Enter the elements for row %d (space-separated): ", i + 1);
        for (int j = 0; j < *pNbCol; j++)
        {
            scanf("%hhu", &matrix[i][j]);
        }
    }

    return matrix;
}

void MatDisplay(tMatrix Mat, int NbLig, int NbCol)
{
    for (int i = 0; i < NbLig; i++)
    {
        for (int j = 0; j < NbCol; j++)
        {
            printf("%d ", Mat[i][j]);
        }
        printf("\n");
    }
}

tMatrix MatCopy(tMatrix Mat, int NbLig, int NbCol)
{
    // Allocate memory for the copy
    tMatrix copy = MatAllouer(NbLig, NbCol);
    if (copy == NULL)
    {
        return NULL;
    }

    // Copy the elements
    for (int i = 0; i < NbLig; i++)
    {
        for (int j = 0; j < NbCol; j++)
        {
            copy[i][j] = Mat[i][j];
        }
    }

    return copy;
}

void MatLiberer(tMatrix *pMat, int NbLig)
{
    if (pMat == NULL || *pMat == NULL)
    {
        return; // Nothing to free
    }

    // Free the elements of each row
    for (int i = 0; i < NbLig; i++)
    {
        free((*pMat)[i]);
    }

    // Free the array of pointers
    free(*pMat);

    // Assign NULL to the freed matrix
    *pMat = NULL;
}
