#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "matrix.h"
#include "image.h"

// The corresponding private implementation type is:

tImage ImAllouer(int NbLignes, int NbColonnes)
{
    tImage image = (tImage)malloc(sizeof(struct sImage));
    if (image == NULL)
    {
        return NULL;
    }

    image->NbLig = NbLignes;
    image->NbCol = NbColonnes;

    image->matrix = (tMatrice)malloc(NbLignes * sizeof(unsigned char *));
    if (image->matrix == NULL)
    {
        free(image);
        return NULL;
    }

    for (int i = 0; i < NbLignes; i++)
    {
        image->matrix[i] = (unsigned char *)malloc(NbColonnes * sizeof(unsigned char));
        if (image->matrix[i] == NULL)
        {
            for (int j = 0; j < i; j++)
            {
                free(image->matrix[j]);
            }
            free(image->matrix);
            free(image);
            return NULL;
        }
    }

    return image;
}

void ImLiberer(tImage *pIm)
{
    if (pIm == NULL || *pIm == NULL)
    {
        return;
    }

    tImage image = *pIm;

    // Free the matrix rows
    if (image->matrix != NULL)
    {
        for (int i = 0; i < image->NbLig; i++)
        {
            free(image->matrix[i]);
        }
        free(image->matrix);
    }

    // Free the image structure
    free(image);

    // Assign NULL to the freed image pointer
    *pIm = NULL;
}

int ImNbLig(tImage Im)
{
    return Im->NbLig;
}

int ImNbCol(tImage Im)
{
    return Im->NbCol;
}

// This function returns the grayscale matrix of the image Im.
tMatrice ImNivGray(tImage Im)
{
    return Im->matrix;
}

tImage ImLire(char FileName[])
{
    FILE *file = fopen(FileName, "r");
    if (file == NULL)
    {
        printf("Failed to open file: %s\n", FileName);
        return NULL;
    }

    // Read the signature (P2)
    char signature[3];
    fscanf(file, "%s", signature);
    if (strcmp(signature, "P2") != 0)
    {
        printf("Invalid image format\n");
        fclose(file);
        return NULL;
    }

    // Read the number of columns and rows
    int NbCol, NbLig;
    fscanf(file, "%d %d", &NbCol, &NbLig);

    // Read the maximum grey level
    int maxGreyLevel;
    fscanf(file, "%d", &maxGreyLevel);

    // Allocate memory for the image
    tImage image = ImAllouer(NbLig, NbCol);
    if (image == NULL)
    {
        printf("Failed to allocate memory for the image\n");
        fclose(file);
        return NULL;
    }

    // Read the gray levels of the image
    for (int i = 0; i < image->NbLig; i++)
    {
        for (int j = 0; j < image->NbCol; j++)
        {
            int grayLevel;
            fscanf(file, "%d", &grayLevel);
            image->matrix[i][j] = (unsigned char)grayLevel;
        }
    }

    fclose(file);
    return image;
}

void ImEcrire(tImage Im, char FileName[])
{
    FILE *file = fopen(FileName, "w");
    if (file == NULL)
    {
        printf("Failed to open file: %s\n", FileName);
        return;
    }

    // Write the PGM-ASCII header
    fprintf(file, "P2\n");
    fprintf(file, "%d %d\n", Im->NbCol, Im->NbLig);
    fprintf(file, "255\n");

    // Write the gray levels of the image
    for (int i = 0; i < Im->NbLig; i++)
    {
        for (int j = 0; j < Im->NbCol; j++)
        {
            fprintf(file, "%d ", Im->matrix[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}
