#include <stdio.h>
#include <stdlib.h>
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

// create an empty polygon
/// return type : tPolygon (a pointer to a struct sPolygon)
// tPolygon PolygonCreate(void)
tPolygon PolygonCreate(void)
{
    // tPolygon is a typecast
    tPolygon pPolygon = (tPolygon)malloc(sizeof(struct sPolygon)); // (4+8=12 bytes)
    pPolygon->Nb_vertices = 0;
    pPolygon->p_first_vertex = NULL;
    return pPolygon;
}

// return the number of vertices of the polygon
int PolygoneNb_vertices(tPolygon Poly)
{
    return Poly->Nb_vertices;
}

// Print the coordinates of ith vertex of the polygon
void display_polygon_vertex_i(int i, tPolygon Poly)
{
    if (i < 0 || i >= Poly->Nb_vertices)
    {
        fprintf(stderr, "Invalid position to add vertex.\n");
        return;
    }

    struct sVertex *pCurrent = Poly->p_first_vertex;
    int cpt = 0;
    while (cpt < i)
    {
        pCurrent = pCurrent->p_next;
        cpt++;
    }
    printf("%d %d \n", pCurrent->x, pCurrent->y);
}

// add a vertex of coordinates (x,y) in ith position of the polygon
void polygon_add_vertex_at_i(int x, int y, int i, tPolygon Poly)
{
    struct sVertex *newVertex = (struct sVertex *)malloc(sizeof(struct sVertex));
    if (newVertex == NULL)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        return;
    }
    newVertex->x = x;
    newVertex->y = y;
    newVertex->p_next = NULL;

    if (i < 0 || i > Poly->Nb_vertices)
    {
        fprintf(stderr, "Invalid position to add vertex.\n");
        free(newVertex);
        return;
    }

    if (i == 0)
    {
        newVertex->p_next = Poly->p_first_vertex;
        Poly->p_first_vertex = newVertex;
    }
    else
    {
        struct sVertex *prevVertex = Poly->p_first_vertex;
        for (int j = 1; j < i; j++)
        {
            prevVertex = prevVertex->p_next;
        }
        newVertex->p_next = prevVertex->p_next;
        prevVertex->p_next = newVertex;
    }

    Poly->Nb_vertices++;
}

// Print the coordinates of the vertices of the polygon
void display_polygon(tPolygon Poly)
{
    struct sVertex *pCurrent = Poly->p_first_vertex;
    printf("%d\n", Poly->Nb_vertices);
    while (pCurrent != NULL)
    {
        printf("%d %d \n", pCurrent->x, pCurrent->y);
        pCurrent = pCurrent->p_next;
    }
    printf("\n");
}

// add a vertex of coordinates (x,y) at the end of the polygon
void polygon_add_vertex_at_end(int x, int y, tPolygon Poly)
{
    // allocate memory for a new vertex
    struct sVertex *p_new_vertex = (struct sVertex *)malloc(sizeof(struct sVertex));

    // set the coordinates of the new vertex
    p_new_vertex->x = x;
    p_new_vertex->y = y;

    // set the next vertex to NULL
    p_new_vertex->p_next = NULL;

    // if the polygon is empty
    if (Poly->p_first_vertex == NULL)
    {
        // set the first vertex to the new vertex
        Poly->p_first_vertex = p_new_vertex;
    }
    else
    {
        // if the polygon is not empty, find the last vertex
        struct sVertex *pCurrent = Poly->p_first_vertex;
        while (pCurrent->p_next != NULL)
        {
            pCurrent = pCurrent->p_next;
        }

        // set the next vertex of the last vertex to the new vertex
        pCurrent->p_next = p_new_vertex;
    }
    Poly->Nb_vertices++;
}

// ajouter un sommet de coordonnées (x,y) au début du polygone
// add a vertex of coordinates (x,y) at the beginning of the polygon
// void PolygoneAjouterSommetEnDebut(int x, int y, tPolygon Poly)
void polygon_add_vertex_at_begin(int x, int y, tPolygon Poly)
{
    // allocate memory for the new vertex:
    struct sVertex *p_new_vertex_at_begin = (struct sVertex *)malloc(sizeof(struct sVertex));

    // set the coordinates of the new vertex at the beginning:
    p_new_vertex_at_begin->x = x;
    p_new_vertex_at_begin->y = y;

    // The next vertex of the vertext at the beginning is the first vertex of the polygon:
    // If p_first_vertex is NULL, then p_new_vertex_at_begin->p_next is NULL (poly is empty)
    p_new_vertex_at_begin->p_next = Poly->p_first_vertex;

    // update the polygon
    Poly->Nb_vertices++;
    Poly->p_first_vertex = p_new_vertex_at_begin;
}

tPolygon create_a_polygon_with_n_vertices(int n_vertices)
{
    tPolygon poly = PolygonCreate();

    // Adding vertices
    for (int i = 0; i < n_vertices; i++)
    {
        polygon_add_vertex_at_end(i, i, poly);
    }
    display_polygon(poly);

    return poly;
}

// Freeing the memory occupied by the polygon
void PolygonLiberer(tPolygon Poly)
{
    struct sVertex *current = Poly->p_first_vertex;
    while (current != NULL)
    {
        struct sVertex *temp = current;
        current = current->p_next;
        free(temp);
    }

    free(Poly);
}

tPolygon PolygonRead(FILE *f)
{
    tPolygon poly = PolygonCreate();
    int numVertices;
    fscanf(f, "%d", &numVertices);

    for (int i = 0; i < numVertices; i++)
    {
        int x, y;
        fscanf(f, "%d %d", &x, &y);
        polygon_add_vertex_at_end(x, y, poly);
    }

    return poly;
}

void PolygonWrite(tPolygon Poly, FILE *f)
{
    fprintf(f, "%d\n", Poly->Nb_vertices);
    struct sVertex *current = Poly->p_first_vertex;
    while (current != NULL)
    {
        fprintf(f, "%d %d\n", current->x, current->y);
        current = current->p_next;
    }
}

void PolygonWriteSvg(tPolygon Poly, tStyle *pStyle, FILE *IdFichSVG)
{
}

void test_polygon_write(void)
{
    FILE *file = fopen("output.txt", "w");
    tPolygon poly = create_a_polygon_with_n_vertices(10);
    PolygonWrite(poly, file);
    PolygonLiberer(poly);
    fclose(file);
}

void test_polygon_read(void)
{
    FILE *file = fopen("input.txt", "r");
    tPolygon poly = PolygonRead(file);

    display_polygon(poly);
    PolygonLiberer(poly);
    fclose(file);
}

void test_add_vertex_at_begin(void)
{
    tPolygon poly = PolygonCreate();

    // Adding vertices
    polygon_add_vertex_at_begin(0, 0, poly);
    polygon_add_vertex_at_begin(1, 1, poly);
    polygon_add_vertex_at_begin(2, 2, poly);
    polygon_add_vertex_at_begin(3, 3, poly);
    display_polygon(poly);

    free(poly);
}

void test_add_vertex_at_i(void)
{
    tPolygon poly = PolygonCreate();

    // Adding vertices
    polygon_add_vertex_at_i(1, 1, 0, poly);
    polygon_add_vertex_at_i(2, 2, 1, poly);
    polygon_add_vertex_at_i(3, 3, 2, poly);

    // Printing the number of vertices and their coordinates
    display_polygon(poly);

    PolygonLiberer(poly);
}

void test_display_polygon_vertex_i(void)
{
    printf("Create a polygon with 5\n");
    tPolygon poly = create_a_polygon_with_n_vertices(5);

    display_polygon_vertex_i(0, poly);
    display_polygon_vertex_i(2, poly);
    display_polygon_vertex_i(3, poly);
    display_polygon_vertex_i(4, poly);
    display_polygon_vertex_i(5, poly);
    display_polygon_vertex_i(6, poly);
    PolygonLiberer(poly);
}

void test_add_vertex_at_end(void)
{
    tPolygon poly = PolygonCreate();

    // Adding vertices
    polygon_add_vertex_at_end(2, 3, poly);
    polygon_add_vertex_at_end(4, 5, poly);
    polygon_add_vertex_at_end(6, 7, poly);
    polygon_add_vertex_at_end(6, 7, poly);
    display_polygon(poly);

    PolygonLiberer(poly);
}

// Delete the ith vertex of the polygon
void delete_polygon_vertex_i(int i, tPolygon Poly)
{
    struct sVertex *pCurrent = Poly->p_first_vertex;
    int cpt = 0;
    if (i == 0)
    {
        Poly->p_first_vertex = pCurrent->p_next;
        free(pCurrent);
    }
    else
    {
        while (cpt < i - 1)
        {
            pCurrent = pCurrent->p_next;
            cpt++;
        }
        struct sVertex *p_current_next = pCurrent->p_next;
        pCurrent->p_next = p_current_next->p_next;
        free(p_current_next);
    }
    Poly->Nb_vertices--;
}

void test_delete_polygon_vertex_i(void)
{
    tPolygon poly1 = create_a_polygon_with_n_vertices(3);

    printf("Delete at 0\n");
    delete_polygon_vertex_i(0, poly1);
    display_polygon(poly1);
    PolygonLiberer(poly1);

    printf("Delete at end\n");
    tPolygon poly2 = create_a_polygon_with_n_vertices(3);
    delete_polygon_vertex_i(2, poly2);
    display_polygon(poly2);
    PolygonLiberer(poly2);

    printf("Delete at begin\n");
    tPolygon poly3 = create_a_polygon_with_n_vertices(3);
    delete_polygon_vertex_i(0, poly3);
    display_polygon(poly3);
    PolygonLiberer(poly3);
}

int main()
{

    printf("Test Add At the Beginning\n");
    test_add_vertex_at_begin();

    printf("Test Add At the End\n");
    test_add_vertex_at_end();

    printf("Test Add At the position i\n");
    test_add_vertex_at_i();

    printf("Test display at i\n");
    test_display_polygon_vertex_i();

    printf("Test delete at i\n");
    test_delete_polygon_vertex_i();

    printf("Test read polygon\n");
    test_polygon_read();

    printf("Test write polygon\n");
    test_polygon_write();

    return 0;
}
