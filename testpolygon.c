#include <stdio.h>
#include <stdlib.h>
#include "polygon.c"

tPolygone create_a_polygon_with_n_vertices(int n_vertices)
{
    tPolygone poly = PolygoneCreer();

    // Adding vertices
    for (int i = 0; i < n_vertices; i++)
    {
        PolygoneAjouterSommetEnFin(i, i, poly);
    }
    PolygoneAfficher(poly);

    return poly;
}

tPolygone create_my_polygon(void)
{
    tPolygone poly = PolygoneCreer();

    // Adding vertices
    PolygoneAjouterSommetEnFin(0, 0, poly);
    PolygoneAjouterSommetEnFin(0, 10, poly);
    PolygoneAjouterSommetEnFin(0, 20, poly);
    PolygoneAjouterSommetEnFin(10, 10, poly);
    PolygoneAjouterSommetEnFin(10, 0, poly);
    PolygoneAfficher(poly);
    return poly;
}
void test_polygon_write(void)
{
    FILE *file = fopen("output.txt", "w");
    tPolygone poly = create_a_polygon_with_n_vertices(10);
    PolygoneEcriref(poly, file);
    PolygonLiberer(poly);
    fclose(file);
}

void test_polygon_read(void)
{
    FILE *file = fopen("input.txt", "r");
    tPolygone poly = PolygoneLiref(file);

    PolygoneAfficher(poly);
    PolygonLiberer(poly);
    fclose(file);
}

void test_add_vertex_at_begin(void)
{
    tPolygone poly = PolygoneCreer();

    // Adding vertices
    PolygoneAjouterSommetEnDebut(0, 0, poly);
    PolygoneAjouterSommetEnDebut(1, 1, poly);
    PolygoneAjouterSommetEnDebut(2, 2, poly);
    PolygoneAjouterSommetEnDebut(3, 3, poly);
    PolygoneAfficher(poly);

    free(poly);
}

void test_add_vertex_at_i(void)
{
    tPolygone poly = PolygoneCreer();

    // Adding vertices
    PolygoneAjouterSommetEnIeme(1, 1, 0, poly);
    PolygoneAjouterSommetEnIeme(2, 2, 1, poly);
    PolygoneAjouterSommetEnIeme(3, 3, 2, poly);

    // Printing the number of vertices and their coordinates
    PolygoneAfficher(poly);

    PolygonLiberer(poly);
}

void test_display_polygon_vertex_i(void)
{
    printf("Create a polygon with 5\n");
    tPolygone poly = create_a_polygon_with_n_vertices(5);

    PolygoneSommetIeme(0, poly);
    PolygoneSommetIeme(2, poly);
    PolygoneSommetIeme(3, poly);
    PolygoneSommetIeme(4, poly);
    PolygoneSommetIeme(5, poly);
    PolygoneSommetIeme(6, poly);
    PolygonLiberer(poly);
}

void test_add_vertex_at_end(void)
{
    tPolygone poly = PolygoneCreer();

    // Adding vertices
    PolygoneAjouterSommetEnFin(2, 3, poly);
    PolygoneAjouterSommetEnFin(4, 5, poly);
    PolygoneAjouterSommetEnFin(6, 7, poly);
    PolygoneAjouterSommetEnFin(6, 7, poly);
    PolygoneAfficher(poly);

    PolygonLiberer(poly);
}

void test_delete_polygon_vertex_i(void)
{
    tPolygone poly1 = create_a_polygon_with_n_vertices(3);

    printf("Delete at 0\n");
    PolygoneSommetSupprimerIeme(0, poly1);
    PolygoneAfficher(poly1);
    PolygonLiberer(poly1);

    printf("Delete at end\n");
    tPolygone poly2 = create_a_polygon_with_n_vertices(3);
    PolygoneSommetSupprimerIeme(2, poly2);
    PolygoneAfficher(poly2);
    PolygonLiberer(poly2);

    printf("Delete at begin\n");
    tPolygone poly3 = create_a_polygon_with_n_vertices(3);
    PolygoneSommetSupprimerIeme(0, poly3);
    PolygoneAfficher(poly3);
    PolygonLiberer(poly3);
}

void test_polygon_write_svg(void)
{
    FILE *file = SvgCreate("output.svg", 1000, 1000);
    tPolygone Poly = create_my_polygon();
    // tPolygon Poly = create_a_polygon_with_n_vertices(5);
    PolygoneAfficher(Poly);

    tStyle *Style = (tStyle *)malloc(sizeof(tStyle));

    Style->ColorTrait = "blue";
    Style->WidthTrait = 0.125;
    Style->OpaciteTrait = 1;
    Style->ColorFill = "none";
    Style->OpacityFill = 0;
    Style->ColorPoints = "red";
    Style->RadiusPoints = 0.125;

    PolygoneEcrireSvg(Poly, Style, file);
    SvgClose(file);
    PolygonLiberer(Poly);
    free(Style);
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

    tStyle QStyle = {"blue", 0.125, 1, "none", 0, "red", 0.125};
    printf("SVG polygon %s\n", QStyle.ColorTrait);
    printf("SVG polygon %f\n", QStyle.WidthTrait);

    printf("Test write polygon SVG\n");
    test_polygon_write_svg();

    return 0;
}