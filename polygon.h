#ifndef POLYGON_H
#define POLYGON_H

#include "svg.h"

struct sSommet // Vertex
{
    int x, y;
    struct sSommet *pSuivant; // pNext
};

struct sPolygone
{
    int NbSommets;                 // number of vertices
    struct sSommet *PremierSommet; // pointer to first vertex
};

typedef struct sPolygone *tPolygone;

int PolygoneNbSommets(tPolygone Poly);

tPolygone PolygoneCreer(void);

void PolygoneSommetIeme(int i, tPolygone Poly);

void PolygoneAjouterSommetEnIeme(int x, int y, int i, tPolygone Poly);

void PolygoneAfficher(tPolygone Poly);

void PolygoneAjouterSommetEnFin(int x, int y, tPolygone Poly);

void PolygoneAjouterSommetEnDebut(int x, int y, tPolygone Poly);

void PolygonLiberer(tPolygone Poly);

tPolygone PolygoneLiref(FILE *f);

void PolygoneEcriref(tPolygone Poly, FILE *f);

void PolygoneSommetSupprimerIeme(int i, tPolygone Poly);

void PolygoneEcrireSvg(tPolygone Poly, tStyle *pStyle, FILE *IdFichSVG);

#endif
