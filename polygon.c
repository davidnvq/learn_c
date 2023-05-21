#include <stdio.h>
#include <stdlib.h>
#include "polygon.h"

// return the number of vertices of the polygon
int PolygoneNbSommets(tPolygone Poly)
{
    return Poly->NbSommets;
}

// create an empty polygon
/// return type : tPolygon (a pointer to a struct sPolygon)
// tPolygon PolygonCreate(void)
tPolygone PolygoneCreer(void)
{
    // tPolygon is a typecast
    tPolygone pPolygon = (tPolygone)malloc(sizeof(struct sPolygone)); // (4+8=12 bytes)
    pPolygon->NbSommets = 0;
    pPolygon->PremierSommet = NULL;
    return pPolygon;
}

// Print the coordinates of ith vertex of the polygon
void PolygoneSommetIeme(int i, tPolygone Poly)
{
    if (i < 0 || i >= Poly->NbSommets)
    {
        fprintf(stderr, "Invalid position to add vertex.\n");
        return;
    }

    struct sSommet *pCurrent = Poly->PremierSommet;
    int cpt = 0;
    while (cpt < i)
    {
        pCurrent = pCurrent->pSuivant;
        cpt++;
    }
    printf("%d %d \n", pCurrent->x, pCurrent->y);
}

// add a vertex of coordinates (x,y) in ith position of the polygon
void PolygoneAjouterSommetEnIeme(int x, int y, int i, tPolygone Poly)
{
    struct sSommet *newVertex = (struct sSommet *)malloc(sizeof(struct sSommet));
    if (newVertex == NULL)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        return;
    }
    newVertex->x = x;
    newVertex->y = y;
    newVertex->pSuivant = NULL;

    if (i < 0 || i > Poly->NbSommets)
    {
        fprintf(stderr, "Invalid position to add vertex.\n");
        free(newVertex);
        return;
    }

    if (i == 0)
    {
        newVertex->pSuivant = Poly->PremierSommet;
        Poly->PremierSommet = newVertex;
    }
    else
    {
        struct sSommet *prevVertex = Poly->PremierSommet;
        for (int j = 1; j < i; j++)
        {
            prevVertex = prevVertex->pSuivant;
        }
        newVertex->pSuivant = prevVertex->pSuivant;
        prevVertex->pSuivant = newVertex;
    }

    Poly->NbSommets++;
}

// Print the coordinates of the vertices of the polygon
void PolygoneAfficher(tPolygone Poly)
{
    struct sSommet *pCurrent = Poly->PremierSommet;
    printf("%d\n", Poly->NbSommets);
    while (pCurrent != NULL)
    {
        printf("%d %d \n", pCurrent->x, pCurrent->y);
        pCurrent = pCurrent->pSuivant;
    }
    printf("\n");
}

// add a vertex of coordinates (x,y) at the end of the polygon
void PolygoneAjouterSommetEnFin(int x, int y, tPolygone Poly)
{
    // allocate memory for a new vertex
    struct sSommet *p_new_vertex = (struct sSommet *)malloc(sizeof(struct sSommet));

    // set the coordinates of the new vertex
    p_new_vertex->x = x;
    p_new_vertex->y = y;

    // set the next vertex to NULL
    p_new_vertex->pSuivant = NULL;

    // if the polygon is empty
    if (Poly->PremierSommet == NULL)
    {
        // set the first vertex to the new vertex
        Poly->PremierSommet = p_new_vertex;
    }
    else
    {
        // if the polygon is not empty, find the last vertex
        struct sSommet *pCurrent = Poly->PremierSommet;
        while (pCurrent->pSuivant != NULL)
        {
            pCurrent = pCurrent->pSuivant;
        }

        // set the next vertex of the last vertex to the new vertex
        pCurrent->pSuivant = p_new_vertex;
    }
    Poly->NbSommets++;
}

// ajouter un sommet de coordonnées (x,y) au début du polygone
// add a vertex of coordinates (x,y) at the beginning of the polygon
// void PolygoneAjouterSommetEnDebut(int x, int y, tPolygon Poly)
void PolygoneAjouterSommetEnDebut(int x, int y, tPolygone Poly)
{
    // allocate memory for the new vertex:
    struct sSommet *p_new_vertex_at_begin = (struct sSommet *)malloc(sizeof(struct sSommet));

    // set the coordinates of the new vertex at the beginning:
    p_new_vertex_at_begin->x = x;
    p_new_vertex_at_begin->y = y;

    // The next vertex of the vertext at the beginning is the first vertex of the polygon:
    // If p_first_vertex is NULL, then p_new_vertex_at_begin->p_next is NULL (poly is empty)
    p_new_vertex_at_begin->pSuivant = Poly->PremierSommet;

    // update the polygon
    Poly->NbSommets++;
    Poly->PremierSommet = p_new_vertex_at_begin;
}

// Freeing the memory occupied by the polygon
void PolygonLiberer(tPolygone Poly)
{
    struct sSommet *current = Poly->PremierSommet;
    while (current != NULL)
    {
        struct sSommet *temp = current;
        current = current->pSuivant;
        free(temp);
    }

    free(Poly);
}

tPolygone PolygoneLiref(FILE *f)
{
    tPolygone poly = PolygoneCreer();
    int numVertices;
    fscanf(f, "%d", &numVertices);

    for (int i = 0; i < numVertices; i++)
    {
        int x, y;
        fscanf(f, "%d %d", &x, &y);
        PolygoneAjouterSommetEnFin(x, y, poly);
    }

    return poly;
}

void PolygoneEcriref(tPolygone Poly, FILE *f)
{
    fprintf(f, "%d\n", Poly->NbSommets);
    struct sSommet *current = Poly->PremierSommet;
    while (current != NULL)
    {
        fprintf(f, "%d %d\n", current->x, current->y);
        current = current->pSuivant;
    }
}

// Delete the ith vertex of the polygon
void PolygoneSommetSupprimerIeme(int i, tPolygone Poly)
{
    struct sSommet *pCurrent = Poly->PremierSommet;
    int cpt = 0;
    if (i == 0)
    {
        Poly->PremierSommet = pCurrent->pSuivant;
        free(pCurrent);
    }
    else
    {
        while (cpt < i - 1)
        {
            pCurrent = pCurrent->pSuivant;
            cpt++;
        }
        struct sSommet *p_current_next = pCurrent->pSuivant;
        pCurrent->pSuivant = p_current_next->pSuivant;
        free(p_current_next);
    }
    Poly->NbSommets--;
}

void PolygoneEcrireSvg(tPolygone Poly, tStyle *pStyle, FILE *IdFichSVG)
{
    float *x = (float *)malloc(sizeof(float) * Poly->NbSommets);
    float *y = (float *)malloc(sizeof(float) * Poly->NbSommets);

    struct sSommet *current = Poly->PremierSommet;
    int i = 0;
    while (current != NULL)
    {
        y[i] = current->x;
        // printf("Write to svg x[%d] y[%d] = %f %f\n", i, i, x[i], y[i]);
        x[i] = current->y;
        current = current->pSuivant;
        i++;
    }

    SvgWritePolygon(IdFichSVG, x, y, Poly->NbSommets, pStyle);

    free(x);
    free(y);
}
