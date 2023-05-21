#include <stdio.h>
#include <stdlib.h>
#include "image.h"

int main()
{
    int NbLignes = 3;
    int NbColonnes = 4;

    // Allocate memory for the image
    tImage image = ImAllouer(NbLignes, NbColonnes);
    if (image == NULL)
    {
        printf("Failed to allocate memory for the image\n");
        // Handle the error
    }

    // Free the memory occupied by the image
    ImLiberer(&image);

    // Read the image from the file
    tImage image1 = ImLire("data/im0.pgm");

    // Get the gray levels matrix of the image
    tMatrice matrix = ImNivGray(image1);

    NbLignes = ImNbLig(image1);
    NbColonnes = ImNbCol(image1);

    // Display matrix
    MatAfficher(matrix, NbLignes, NbColonnes);

    ImEcrire(image1, "data/im0_copy.pgm");
    return 0;
}