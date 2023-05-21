#ifndef IMAGE_H
#define IMAGE_H

#include "matrix.h"

struct sImage
{
    int NbLig;      // Number of lines in the image
    int NbCol;      // Number of columns in the image
    tMatrix matrix; // Gray level matrix of the image
};

// Structure to represent an image
typedef struct sImage *tImage;

// Function prototypes
tImage ImAllocate(int NbLignes, int NbColonnes);
void ImLiberer(tImage *pIm);
int ImNbLig(tImage Im);
int ImNbCol(tImage Im);
tMatrix ImNivGray(tImage Im);
tImage ImLire(char FileName[]);
void ImEcrire(tImage Im, char FileName[]);

#endif
