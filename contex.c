#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include "polygon.h"

// Return the number of labels and store the labels in the array `labels` from the given image
int ContourLabelsFromImage(tImage image, unsigned char Labels[])
{
    if (image == NULL || image->matrix == NULL)
    {
        return 0;
    }

    int NbLig = image->NbLig;
    int NbCol = image->NbCol;
    tMatrix matrix = image->matrix;

    // Maximum number of labels is 256, since the pixel values are in range 0-255
    int maxLabels = 256;
    int numLabels = 0;

    // Create an array to store the label counts, default = 0
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
            // Only add the label if it is not 0 (background) and it is not already added (labelCounts[label] == 0)
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

// Return the number of labels and store the labels in the array `labels` from the given pgm file
// int ContourEtiquettes(char NomFichEtiquettes[], unsigned char Etiquettes[])
int ContourLabels(char pgmFileName[], unsigned char labels[])
{
    tImage image = ImLire(pgmFileName);
    int num_labels = ContourLabelsFromImage(image, labels);
    return num_labels;
}

// Return the next contour polygon for the given label
// tPolygone ContourSuivi(tImage Im, unsigned char Etiquette)
tPolygone ContourSuivi(tImage image, unsigned char label)
{
    int startX = -1, startY = -1;
    int x, y;
    int prev_x, prev_y;

    // Find the starting pixel of the region
    for (int i = 0; i < image->NbLig; i++)
    {
        for (int j = 0; j < image->NbCol; j++)
        {
            if (image->matrix[i][j] == label)
            {
                // printf("Found label %d at (%d, %d)\n", label, i, j);
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

    int max_pixels = image->NbLig * image->NbCol;
    unsigned char *visited = (unsigned char *)calloc(max_pixels, sizeof(unsigned char));

    tPolygone contourPolygon = (tPolygone)malloc(sizeof(struct sPolygone));
    contourPolygon->NbSommets = 0;
    contourPolygon->PremierSommet = NULL;

    x = startX;
    y = startY;

    prev_x = startX;
    prev_y = startY;

    // printf("Add this vertex to contour polygon: (%d, %d) \n", x, y);
    PolygoneAjouterSommetEnFin(x, y, contourPolygon);

    // For the first vertex, we need to go left
    x = x - 1;

    do
    {
        int idx = x * image->NbCol + y; // Index of the current pixel for visited array

        // If we encounter a pixel/vertex which is the label, we need to go left
        if (image->matrix[x][y] == label)
        {
            if (visited[idx] == 0)
            {
                // printf("Add this vertex to contour polygon: (%d, %d) \n", x, y);
                PolygoneAjouterSommetEnFin(x, y, contourPolygon);
                visited[idx] = 1; // Mark as visited, so we don't add it again to the contour
            }
            if (x == prev_x)
            {
                prev_x = x;
                x = x + (prev_y - y);
                prev_y = y;
                // printf("Left x\n");
            }
            else
            {
                prev_y = y;
                y = y - (prev_x - x);
                prev_x = x;
                // printf("Left y\n");
            }
        }
        // If we encounter a pixel/vertex which is not the label, we need to go right
        else if (image->matrix[x][y] != label)
        {
            if (x == prev_x)
            {
                prev_x = x;
                x = x - (prev_y - y);
                prev_y = y;
                // printf("Right x\n");
            }
            else
            {
                prev_y = y;
                y = y + (prev_x - x);
                prev_x = x;
                // printf("Right y\n");
            }
        }
        else
        {
            x = startX;
            y = startY;
        }

    } while (x != startX || y != startY);

    return contourPolygon;
}

// Extract the contour polygons for the given labels and write them to the given file
// void ContourExtraire(char NomFichEtiquettes[], unsigned char Etiquette[], int NbRegions, char NomFichContours[])
void ExtractContour(char *FileName, unsigned char Labels[], int NbRegions, char *ContourFileName)
{
    // Read the PGM file (open the pgm file to see the format!)
    tImage image = ImLire(FileName);
    FILE *file = fopen(ContourFileName, "a");
    fprintf(file, "%d\n", NbRegions);

    for (int i = 0; i < NbRegions; i++)
    {
        unsigned char label = Labels[i];
        // Find the next contour polygon which has the label = Labels[i]
        tPolygone contourPolygon = ContourSuivi(image, label);
        if (contourPolygon != NULL)
        {
            // printf("Writing contour %d to file\n", i);

            // Write the contour polygon to the file, ONE at a time
            PolygoneEcriref(contourPolygon, file);
            PolygonLiberer(contourPolygon); // free the memory for the polygon
        }
    }
    fclose(file);
}

// Write the given contour polygons to the given SVG file
// void ContourEcrireSurImageSvg(char NomFichContours[], char NomFichImage[], int NbCol, int NbLig, tStyle *pStyle, char NomFichSVG[])
void ContourWriteOverImageSvg(char *ContourFileName, char *ImageFileName, int NbCol, int NbLig, tStyle *pStyle, char *SvgFileName)
{
    FILE *contFile = fopen(ContourFileName, "r");
    FILE *svgFile = SvgCreate(SvgFileName, NbLig, NbCol);

    // Write the png image to the svg file first,
    // so that the png image is at the back, and the contours are drawn on front!!!
    SvgWriteImage(svgFile, ImageFileName, NbCol, NbLig);

    // Read the contours from the file and write them to the svg file
    int numRegions;
    fscanf(contFile, "%d", &numRegions);
    // printf("Num regions: %d\n", numRegions);

    for (int i = 0; i < numRegions; i++)
    {
        tPolygone poly = PolygoneCreer();
        int numVertices;

        fscanf(contFile, "%d", &numVertices);
        // printf("Num vertices: %d\n", numVertices);

        for (int i = 0; i < numVertices; i++)
        {
            int x, y;
            fscanf(contFile, "%d %d", &x, &y);
            PolygoneAjouterSommetEnFin(x, y, poly);
        }
        // write ONE polygon to the svg file at a time
        PolygoneEcrireSvg(poly, pStyle, svgFile);
        PolygonLiberer(poly); // free the memory allocated for the polygon after finish!
    }
    // Close the files
    fclose(contFile);
    SvgClose(svgFile);
    free(pStyle);
}

int main(int argc, char *argv[])
{
    if (argc != 5)
    {
        printf("Usage: %s <im2_pgm> <im2_png> <output_contour_file> <output_svg_file>\n", argv[0]);
        return 1;
    }
    // Read command line arguments and store them in variables
    // command line: ./contex  argv[1] argv[2] argv[3] argv[4]
    // note that: argv[0] is the program name = ./contex
    char *pgmFile = argv[1];
    char *imgFile = argv[2];
    char *contourFile = argv[3];
    char *SVGFile = argv[4];

    // printf("pgmFile: %s\n", pgmFile);
    // printf("imgFile: %s\n", imgFile);
    // printf("contourFile: %s\n", contourFile);
    // printf("SVGFile: %s\n", SVGFile);

    // Find the number of labels in the image and store them in Labels
    unsigned char Labels[256];
    int numLabels = ContourLabels(pgmFile, Labels);
    printf("Number of labels: %d\n", numLabels);

    // print Labels array
    printf("Label(s): ");
    for (int i = 0; i < numLabels; i++)
    {
        printf("%d ", Labels[i]);
    }
    printf("\n\n\n");

    tImage image = ImLire(pgmFile);

    // default Style config from svg.h
    tStyle *Style = (tStyle *)malloc(sizeof(tStyle));
    Style->ColorTrait = "blue";
    Style->WidthTrait = 0.125;
    Style->OpaciteTrait = 1;
    Style->ColorFill = "none";
    Style->OpacityFill = 0;
    Style->ColorPoints = "red";
    Style->RadiusPoints = 0.125;

    // extract contour polygons and write them to ONE file (contourFile)
    ExtractContour(pgmFile, Labels, numLabels, contourFile);

    // Read polygons from contourFile and write them to SVGFile with the image File
    ContourWriteOverImageSvg(contourFile, imgFile, image->NbCol, image->NbLig, Style, SVGFile);
    return 0;
}
