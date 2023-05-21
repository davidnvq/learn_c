#ifndef SVG_H
#define SVG_H
#include <stdio.h>

/*
 * Module to draw polygons in a file in SVG format
 */

// Style of a polygon
typedef struct sStyle
{
  char *ColorTrait;   // Couleur of segments
  float WidthTrait;   // Largeur of segments en pixels
  float OpaciteTrait; // Opacity of segments (compris entre 0 et 1)
  char *ColorFill;    // Polygon fill color ("none" for none)
  float OpacityFill;  // Polygon fill opacity (between 0 and 1)
  char *ColorPoints;  // vertex color
  float RadiusPoints; // Radius, in pixels, of the points representing the vertices
} tStyle;
// For example, to get blue segments with a width of 0.125 pixels,
// red vertices of 0.125 pixel radius and no fill inside the
// polygon, we can use the following style:
// tStyle Style={"blue",0.125,1,"none",0,"red",0.125};
// Colors can be specified as in HTML: "blue", "#0000FF", rgb(0,0,255).

/*
 * Creation of a file in SVG format
 * If the file already exists, its content is overwritten
 * Entrances:
 * - FileName: name of the file to create
 * - Width: width, in pixels of the drawing area
 * - Height: width, in pixels of the drawing area
 * Return value: file identifier or NULL in case of problem
 */

extern FILE *SvgCreate(char FileName[], int width, int height);

/*
 * Writing an image to an SVG format file
 * The top left corner of the top left pixel of the image will be positioned at (0,0).
 * The image is not "embedded" in the file, only a link is written.
 * Entrances:
 * - IdFichSVG: identifier of the SVG file in which the writing will be done
 * - ImageFileName: name of the file containing the image to write (PNG or JPG format)
 * - NbCol: number of columns in the image (width)
 * - NbLig: number of lines in the image (height)
 */
extern void SvgWriteImage(FILE *IdFichSVG, char NameImage[], int NbCol, int NbRow);

/*
 * Writing a polygon to a file in SVG format
 * Entrances:
 * - IdFichSVG: identifier of the SVG file in which the writing will be done
 * - x: table of NbVertices indexes of columns of the vertices of the polygon
 * - y: table of NbVertices indices of lines of the vertices of the polygon
 * - NbVertices: number of vertices of the polygon
 * - pStyle: address of the structure describing the style of the polygon
 *
 * The last vertex will be automatically connected by a segment to the first vertex.
 * Mark used to draw in an SVG file:
 * (0,0)--------> x
 *   |
 *   |
 *   |
 *   v
 *   y
 */
extern void SvgWritePolygon(FILE *IdFichSVG, float x[], float y[], int NbSommets, tStyle *pStyle);

/*
* Closing a file in SVG format
  * The call to this function is essential for the file to be complete.
  * Entrance :
  * - IdFichSVG: identifier of the SVG file to close

 */
extern void SvgClose(FILE *IdFichSVG);

#endif /* SVG_H */
