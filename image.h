#ifndef IMAGE_H
#define IMAGE_H

#include "matrix.h"

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
