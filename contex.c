#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include "polygon.h"

int ContourLabelsFromImage(tImage image, unsigned char Labels[])
{
    if (image == NULL || image->matrix == NULL)
    {
        return 0;
    }

    int NbLig = image->NbLig;
    int NbCol = image->NbCol;
    tMatrix matrix = image->matrix;

    int maxLabels = 256;
    int numLabels = 0;

    unsigned char *labelCounts = (unsigned char *)calloc(maxLabels, sizeof(unsigned char));
    if (labelCounts == NULL)
    {
        printf("Failed to allocate memory for label counts\n");
        return 0;
    }

    // Count the label occurrences
    for (int i = 0; i < NbLig; i++)
    {
        for (int j = 0; j < NbCol; j++)
        {
            unsigned char label = matrix[i][j];
            if (label != 0 && labelCounts[label] == 0)
            {
                Labels[numLabels] = label;
                numLabels++;
            }
            labelCounts[label]++;
        }
    }

    // Free memory for unused labels
    for (int i = 0; i < numLabels; i++)
    {
        unsigned char label = Labels[i];
        if (labelCounts[label] == 0)
        {
            Labels[i] = 0;
        }
    }
    free(labelCounts);
    return numLabels;
}

int ContourLabels(char FileNameLabels[], unsigned char Labels[])
{
    tImage image = ImLire(FileNameLabels);
    int num_labels = ContourLabelsFromImage(image, Labels);
    return num_labels;
}

tPolygon ContourSuivi(tImage Im, unsigned char label)
{
    int startX = -1, startY = -1;
    int x, y;
    int prev_x, prev_y;

    for (int i = 0; i < Im->NbLig; i++)
    {
        for (int j = 0; j < Im->NbCol; j++)
        {
            printf("%d ", Im->matrix[i][j]);
        }
        printf("\n");
    }

    // Find the starting pixel of the region
    for (int i = 0; i < Im->NbLig; i++)
    {
        for (int j = 0; j < Im->NbCol; j++)
        {
            if (Im->matrix[i][j] == label)
            {
                printf("Found label %d at (%d, %d)\n", label, i, j);
                startX = i;
                startY = j;
                break;
            }
        }
        if (startX != -1 && startY != -1)
        {
            break;
        }
    }

    if (startX == -1 || startY == -1)
    {
        // Region not found, return NULL
        return NULL;
    }
    printf("Start pixel: (%d, %d)\n", startX, startY);

    int max_pixels = Im->NbLig * Im->NbCol;
    unsigned char *visited = (unsigned char *)calloc(max_pixels, sizeof(unsigned char));

    tPolygon contourPolygon = (tPolygon)malloc(sizeof(struct sPolygon));
    contourPolygon->Nb_vertices = 0;
    contourPolygon->p_first_vertex = NULL;

    x = startX;
    y = startY;

    prev_x = startX;
    prev_y = startY;

    polygon_add_vertex_at_end(x, y, contourPolygon);
    display_polygon(contourPolygon);

    x = x - 1;

    // printf("Current pixel 0: (%d, %d) px py (%d %d) \n", x, y, prev_x, prev_y);

    do
    {
        int idx = x * Im->NbCol + y; // Index of the current pixel for visited array

        if (Im->matrix[x][y] == label)
        {
            if (visited[idx] == 1)
            {
                // printf("Already visited\n");
                continue;
            }
            else
            {
                printf("updated Current pixel: (%d, %d) px py (%d %d) \n", x, y, prev_x, prev_y);
                polygon_add_vertex_at_end(x, y, contourPolygon);
                visited[idx] = 1;
            }
            if (x == prev_x)
            {
                prev_x = x;
                x = x + (prev_y - y);
                prev_y = y;
                printf("Left x\n");
            }
            else
            {
                prev_y = y;
                y = y - (prev_x - x);
                prev_x = x;
                printf("Left y\n");
            }
        }
        else if (Im->matrix[x][y] != label)
        {
            if (x == prev_x)
            {
                prev_x = x;
                x = x - (prev_y - y);
                prev_y = y;
                printf("Right x\n");
            }
            else
            {
                prev_y = y;
                y = y + (prev_x - x);
                prev_x = x;
                printf("Right y\n");
            }
        }
        else
        {
            x = startX;
            y = startY;
        }

    } while (x != startX || y != startY);

    printf("Final polygon:\n");
    display_polygon(contourPolygon);
    return contourPolygon;
}

void ExtractContour(char *FileName, unsigned char Labels[], int NbRegions, char *ContourFileName)
{
    tImage image = ImLire(FileName);
    FILE *file = fopen(ContourFileName, "a");
    fprintf(file, "%d\n", NbRegions);

    for (int i = 0; i < NbRegions; i++)
    {
        unsigned char label = Labels[i];
        tPolygon contourPolygon = ContourSuivi(image, label);
        if (contourPolygon != NULL)
        {
            printf("Writing contour %d to file\n", i);
            PolygonWrite(contourPolygon, file);
            PolygonLiberer(contourPolygon);
        }
    }
    fclose(file);
}

void ContourWriteOverImageSvg(char *ContourFileName, char *ImageFileName, int NbCol, int NbLig, tStyle *pStyle, char *SVGFileName)
{
    printf("Hello \n");
    FILE *file = fopen(ContourFileName, "r");
    FILE *svgFile = SvgCreate(SVGFileName, NbLig, NbCol);

    int numRegions;
    fscanf(file, "%d", &numRegions);
    printf("Num regions: %d\n", numRegions);

    for (int i = 0; i < numRegions; i++)
    {
        tPolygon poly = PolygonCreate();
        int numVertices;

        fscanf(file, "%d", &numVertices);
        printf("Num vertices: %d\n", numVertices);

        for (int i = 0; i < numVertices; i++)
        {
            int x, y;
            fscanf(file, "%d %d", &x, &y);
            // printf("Read x: %d y: %d\n", x, y);
            polygon_add_vertex_at_end(x, y, poly);
        }
        printf("Write to MY GOD \n");
        PolygonWriteSvg(poly, pStyle, svgFile);
        PolygonLiberer(poly);
    }

    SvgClose(file);
    free(pStyle);

    SvgWriteImage(svgFile, ImageFileName, NbCol, NbLig);
}

int main(int argc, char *argv[])
{
    if (argc != 5)
    {
        printf("Usage: %s <im2_pgm> <im2_png> <output_contour_file> <output_svg_file>\n", argv[0]);
        return 1;
    }

    char *pgmFile = argv[1];
    char *imgFile = argv[2];
    char *contourFile = argv[3];
    char *SVGFile = argv[4];

    printf("pgmFile: %s\n", pgmFile);
    printf("imgFile: %s\n", imgFile);
    printf("contourFile: %s\n", contourFile);
    printf("SVGFile: %s\n", SVGFile);

    // Rest of your code goes here
    unsigned char Labels[256];
    int numLabels = ContourLabels(pgmFile, Labels);
    printf("Number of labels: %d\n", numLabels);

    // print Labels array
    for (int i = 0; i < numLabels; i++)
    {
        printf("Label %d ", Labels[i]);
    }
    printf("\n");

    tImage image = ImLire(pgmFile);

    tStyle *Style = (tStyle *)malloc(sizeof(tStyle));
    Style->ColorTrait = "blue";
    Style->WidthTrait = 0.125;
    Style->OpaciteTrait = 1;
    Style->ColorFill = "none";
    Style->OpacityFill = 0;
    Style->ColorPoints = "red";
    Style->RadiusPoints = 0.125;
    ExtractContour(pgmFile, Labels, numLabels, contourFile);

    ContourWriteOverImageSvg(contourFile, imgFile, image->NbCol, image->NbLig, Style, SVGFile);
    return 0;
}
