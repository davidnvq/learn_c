#include <stdio.h>
#include <stdlib.h>
#include "polygon.c"

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

tPolygon create_my_polygon(void)
{
    tPolygon poly = PolygonCreate();

    // Adding vertices
    polygon_add_vertex_at_end(0, 0, poly);
    polygon_add_vertex_at_end(0, 10, poly);
    polygon_add_vertex_at_end(0, 20, poly);
    polygon_add_vertex_at_end(10, 10, poly);
    polygon_add_vertex_at_end(10, 0, poly);
    display_polygon(poly);
    return poly;
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

void test_polygon_write_svg(void)
{
    FILE *file = SvgCreate("output.svg", 1000, 1000);
    tPolygon Poly = create_my_polygon();
    // tPolygon Poly = create_a_polygon_with_n_vertices(5);
    display_polygon(Poly);

    tStyle *Style = (tStyle *)malloc(sizeof(tStyle));

    Style->ColorTrait = "blue";
    Style->WidthTrait = 0.125;
    Style->OpaciteTrait = 1;
    Style->ColorFill = "none";
    Style->OpacityFill = 0;
    Style->ColorPoints = "red";
    Style->RadiusPoints = 0.125;

    PolygonWriteSvg(Poly, Style, file);
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