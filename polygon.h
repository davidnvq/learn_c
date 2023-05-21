#ifndef POLYGON_H
#define POLYGON_H

#include "svg.h"

struct sVertex // Vertex
{
    int x, y;
    struct sVertex *p_next; // pNext
};

struct sPolygon
{
    int Nb_vertices;                // number of vertices
    struct sVertex *p_first_vertex; // pointer to first vertex
};

typedef struct sPolygon *tPolygon;

int PolygoneNb_vertices(tPolygon Poly);

tPolygon PolygonCreate(void);

void display_polygon_vertex_i(int i, tPolygon Poly);

void polygon_add_vertex_at_i(int x, int y, int i, tPolygon Poly);

void display_polygon(tPolygon Poly);

void polygon_add_vertex_at_end(int x, int y, tPolygon Poly);

void polygon_add_vertex_at_begin(int x, int y, tPolygon Poly);

void PolygonLiberer(tPolygon Poly);

tPolygon PolygonRead(FILE *f);

void PolygonWrite(tPolygon Poly, FILE *f);

void delete_polygon_vertex_i(int i, tPolygon Poly);
void PolygonWriteSvg(tPolygon Poly, tStyle *pStyle, FILE *IdFichSVG);
#endif
