#include <stdio.h>
#include <stdlib.h>

struct sSommet
{
    int x,y;
    struct sSommet *pSuivant;
};
struct sPolygone
{
    int NbSommets; // nombre de sommets
    struct sSommet *pPremierSommet; // pointeur vers le premier sommet
};
typedef struct sPolygone *tPolygone;

// creer un polygone vide
/// return type : tPolygone (a pointer to a struct sPolygone)
tPolygone PolygoneCreer(void)
{
    // tPolygone is a typecast 
    tPolygone pPolygone = (tPolygone)malloc(sizeof(struct sPolygone)); // (4+8=12 bytes)
    pPolygone->NbSommets = 0;
    pPolygone->pPremierSommet = NULL;
    return pPolygone;
}

// retourner le nombre de sommets du polygone
int PolygoneNbSommets(tPolygone Poly)
{
    return Poly->NbSommets;
}

// ajouter un sommet de coordonnées (x,y) a la fin du polygone
void PolygoneAjouterSommetEnFin(int x, int y, tPolygone Poly)
{
    // allocate memory for a new vertex
    struct sSommet *pNouveauSommet = (struct sSommet*)malloc(sizeof(struct sSommet));
    
    // set the coordinates of the new vertex
    pNouveauSommet->x = x;
    pNouveauSommet->y = y;

    // set the next vertex to NULL
    pNouveauSommet->pSuivant = NULL;

    // if the polygon is empty
    if (Poly->pPremierSommet == NULL)
    {
        // set the first vertex to the new vertex
        Poly->pPremierSommet = pNouveauSommet;
    }
    else
    {
        // if the polygon is not empty, find the last vertex 
        struct sSommet *pCurrent = Poly->pPremierSommet;
        while (pCurrent->pSuivant != NULL)
        {
            pCurrent = pCurrent->pSuivant;
        }

        // set the next vertex of the last vertex to the new vertex
        pCurrent->pSuivant = pNouveauSommet;
    }
    Poly->NbSommets++;
}

// ajouter un sommet de coordonnées (x,y) au début du polygone
void PolygoneAjouterSommetEnDebut(int x, int y, tPolygone Poly)
{
 // allocate memory for the new vertex:
    struct sSommet *pNouveauSommetDebut = (struct sSommet*)malloc(sizeof(struct sSommet));

    // set the coordinates of the new vertex at the beginning:
    pNouveauSommetDebut->x = x;
    pNouveauSommetDebut->y = y;

    // The next vertex of the vertext at the beginning is the first vertex of the polygon:
    // If pPremierSommet is NULL, then pNouveauSommetDebut->pSuivant is NULL (poly is empty)
    pNouveauSommetDebut->pSuivant = Poly->pPremierSommet;

    //update the polygon
    Poly->NbSommets++;
    Poly->pPremierSommet = pNouveauSommetDebut;
}

// ajouter un sommet de coordonnées (x,y) en ieme position du polygone
void PolygoneAjouterSommetEnIeme(int x, int y, int i, tPolygone Poly)
{
    // allocate memory for the new vertex:
    struct sSommet *pNouveauSommetIeme = (struct sSommet*)malloc(sizeof(struct sSommet));

    // find the vertex at the i position:
    int cpt = 0;
    struct sSommet *pCurrent = Poly->pPremierSommet;
    if (i == 0)
    {
        PolygoneAjouterSommetEnDebut(x, y, Poly);
    }
    else if (i == Poly->NbSommets)
    {
        PolygoneAjouterSommetEnFin(x, y, Poly);
    }
    else
    {
        while (cpt < i-1)
        {
            pCurrent = pCurrent->pSuivant;
            cpt++;
        }

        // set the coordinates of the new vertex at the i position:
        pNouveauSommetIeme->x = x;
        pNouveauSommetIeme->y = y;

        // The next vertex of the vertext at the i position is the next vertex of the vertex at the i-1 position:
        pNouveauSommetIeme->pSuivant = pCurrent->pSuivant;

        // The next vertex of the vertex at the i-1 position is the new vertex:
        pCurrent->pSuivant = pNouveauSommetIeme;

        //update the polygon
        Poly->NbSommets++;
    }
}

// Print the coordinates of the vertices of the polygon
void PolygoneAfficher(tPolygone Poly)
{
    struct sSommet *pCurrent = Poly->pPremierSommet;
    printf("Nombre de sommets :%d\n", Poly->NbSommets);
    while (pCurrent != NULL)
    {
        printf("%d %d \n", pCurrent->x, pCurrent->y);
        pCurrent = pCurrent->pSuivant;
    }
    printf("\n");
}

// Print the coordinates of ith vertex of the polygon
void PolygoneSommetIeme(int i, tPolygone Poly)
{
    struct sSommet *pCurrent = Poly->pPremierSommet;
    int cpt = 0;
    while (cpt < i)
    {
        pCurrent = pCurrent->pSuivant;
        cpt++;
    }
    printf("%d %d \n", pCurrent->x, pCurrent->y);
}

// Delete the ith vertex of the polygon
void PolygonSommetSupprimerIeme(int i, tPolygone Poly)
{
    struct sSommet *pCurrent = Poly->pPremierSommet;
    int cpt = 0;
    if (i == 0)
    {
        Poly->pPremierSommet = pCurrent->pSuivant;
        free(pCurrent);
    }
    else
    {
        while (cpt < i-1)
        {
            pCurrent = pCurrent->pSuivant;
            cpt++;
        }
        struct sSommet *pCurrentSuivant = pCurrent->pSuivant;
        pCurrent->pSuivant = pCurrentSuivant->pSuivant;
        free(pCurrentSuivant);
    }
    Poly->NbSommets--;
}

// Liberation de la memoire occupee par le polygone
void PolygonLiberer(tPolygone Poly)
{
    struct sSommet *pCurrent = Poly->pPremierSommet;
    while (pCurrent != NULL)
    {
        struct sSommet *pCurrentSuivant = pCurrent->pSuivant;
        free(pCurrent);
        pCurrent = pCurrentSuivant;
    }
    free(Poly);
}

FILE* file;
file = fopen("C:\\Users\\chaud\\OneDrive\\2. Study\\Paul Sab Licence Info\\2e semestre\\2. ProgC\\C_Project\\polygon.txt", "r");

// Lecture d'un polygone dans un fichier
tPolygone PolygoneLiref(FILE *f)
{
    // allocate memory for the polygon
    tPolygone Poly = (tPolygone)malloc(sizeof(struct sPolygone));

    // read the number of vertices
    fscanf(f, "%d", &Poly->NbSommets);

    // read the coordinates of the vertices
    int x, y;
    for (int i = 0; i < Poly->NbSommets; i++)
    {
        fscanf(f, "%d %d", &x, &y);
        PolygoneAjouterSommetEnFin(x, y, Poly);
    }
    return Poly;
}