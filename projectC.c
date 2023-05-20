#include <stdio.h>
#include <stdlib.h>

struct sVertex // Vertex
{
    int x,y;
    struct sVertex *p_next; // pNext
};
struct sPolygone
{
    int Nb_vertices; // nombre de sommets  // number of vertices
    struct sVertex *p_first_vertex; // pointeur vers le premier sommet //pointer to first vertex
};
typedef struct sPolygone *tPolygone;

// creer un polygone vide
// create an empty polygon
/// return type : tPolygone (a pointer to a struct sPolygone)
// tPolygone PolygonCreate(void)
tPolygone PolygonCreate(void)
{
    // tPolygone is a typecast 
    tPolygone pPolygone = (tPolygone)malloc(sizeof(struct sPolygone)); // (4+8=12 bytes)
    pPolygone->Nb_vertices = 0;
    pPolygone->p_first_vertex = NULL;
    return pPolygone;
}

// retourner le nombre de sommets du polygone
// return the number of vertices of the polygon
int PolygoneNb_vertices(tPolygone Poly)
{
    return Poly->Nb_vertices;
}

// ajouter un sommet de coordonnées (x,y) a la fin du polygone
// add a vertex of coordinates (x,y) at the end of the polygon
// void polygon_add_vertex_at_end(int x, int y, tPolygone Poly)
void polygon_add_vertex_at_end(int x, int y, tPolygone Poly)
{
    // allocate memory for a new vertex
    struct sVertex *p_new_vertex = (struct sVertex*)malloc(sizeof(struct sVertex));
    
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
// void PolygoneAjouterSommetEnDebut(int x, int y, tPolygone Poly)
void polygon_add_vertex_at_begin(int x, int y, tPolygone Poly)
{
 // allocate memory for the new vertex:
    struct sVertex *p_new_vertex_at_begin = (struct sVertex*)malloc(sizeof(struct sVertex));

    // set the coordinates of the new vertex at the beginning:
    p_new_vertex_at_begin->x = x;
    p_new_vertex_at_begin->y = y;

    // The next vertex of the vertext at the beginning is the first vertex of the polygon:
    // If p_first_vertex is NULL, then p_new_vertex_at_begin->p_next is NULL (poly is empty)
    p_new_vertex_at_begin->p_next = Poly->p_first_vertex;

    //update the polygon
    Poly->Nb_vertices++;
    Poly->p_first_vertex = p_new_vertex_at_begin;
}

// ajouter un sommet de coordonnées (x,y) en ieme position du polygone
// add a vertex of coordinates (x,y) in ith position of the polygon
void polygon_add_vertex_at_i(int x, int y, int i, tPolygone Poly)
{
    // allocate memory for the new vertex:
    struct sVertex *p_new_vertex_i = (struct sVertex*)malloc(sizeof(struct sVertex));

    // find the vertex at the i position:
    int cpt = 0;
    struct sVertex *pCurrent = Poly->p_first_vertex;
    if (i == 0)
    {
        polygon_add_vertex_at_begin(x, y, Poly);
    }
    else if (i == Poly->Nb_vertices)
    {
        polygon_add_vertex_at_end(x, y, Poly);
    }
    else
    {
        while (cpt < i-1)
        {
            pCurrent = pCurrent->p_next;
            cpt++;
        }

        // set the coordinates of the new vertex at the i position:
        p_new_vertex_i->x = x;
        p_new_vertex_i->y = y;

        // The next vertex of the vertext at the i position is the next vertex of the vertex at the i-1 position:
        p_new_vertex_i->p_next = pCurrent->p_next;

        // The next vertex of the vertex at the i-1 position is the new vertex:
        pCurrent->p_next = p_new_vertex_i;

        //update the polygon
        Poly->Nb_vertices++;
    }
}

// Print the coordinates of the vertices of the polygon
void display_polygon(tPolygone Poly)
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

// Print the coordinates of ith vertex of the polygon
void display_polygon_vertex_i(int i, tPolygone Poly)
{
    struct sVertex *pCurrent = Poly->p_first_vertex;
    int cpt = 0;
    while (cpt < i)
    {
        pCurrent = pCurrent->p_next;
        cpt++;
    }
    printf("%d %d \n", pCurrent->x, pCurrent->y);
}

// Delete the ith vertex of the polygon
void delete_polygon_vertex_i(int i, tPolygone Poly)
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
        while (cpt < i-1)
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

// Liberation de la memoire occupee par le polygone
// Freeing the memory occupied by the polygon
void PolygonLiberer(tPolygone Poly)
{
    struct sVertex *pCurrent = Poly->p_first_vertex;
    while (pCurrent != NULL)
    {
        struct sVertex *p_current_next = pCurrent->p_next;
        free(pCurrent);
        pCurrent = p_current_next;
    }
    free(Poly);
}

FILE* file;
// file = fopen("C:\\Users\\chaud\\OneDrive\\2. Study\\Paul Sab Licence Info\\2e semestre\\2. ProgC\\C_Project\\polygon.txt", "r");

// Lecture d'un polygone dans un fichier
// Reading a polygon from a file
// tPolygone PolygoneLiref(FILE *f)
tPolygone PolygonRead(FILE *f)
{
    // allocate memory for the polygon
    tPolygone Poly = (tPolygone)malloc(sizeof(struct sPolygone));

    // read the number of vertices
    fscanf(f, "%d", &Poly->Nb_vertices);

    // read the coordinates of the vertices
    int x, y;
    for (int i = 0; i < Poly->Nb_vertices; i++)
    {
        fscanf(f, "%d %d", &x, &y);
        polygon_add_vertex_at_end(x, y, Poly);
    }
    return Poly;
}

int main()
{
    tPolygone Poly = (tPolygone)malloc(sizeof(struct sPolygone));
    Poly = PolygonCreate();
    polygon_add_vertex_at_end(1, 2, Poly);
    polygon_add_vertex_at_end(3, 4, Poly);
    polygon_add_vertex_at_end(5, 6, Poly);
    Poly->Nb_vertices = 3;
    display_polygon(Poly);

}
