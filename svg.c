#include <stdio.h>
#include <string.h>
#include "svg.h"

/*
 * Creation of a file in SVG format
 * If the file already exists, its content is overwritten
 * Entrances:
 * - FileName: name of the file to create
 * - Width: width, in pixels of the drawing area
 * - Height: width, in pixels of the drawing area
 * Return value: file identifier or NULL in case of problem
 */
FILE *SvgCreate(char NomFichier[], int Largeur, int Hauteur)
{
  // Opening the file
  FILE *f;
  f = fopen(NomFichier, "wt");
  if (f == NULL)
  {
    perror(NomFichier);
    return NULL;
  }
  // Opening svg tag
  fprintf(f, "<svg viewBox=\"-0.5 -0.5 %.1f %.1f\" width=\"%d\" height=\"%d\"\n",
          Largeur - 0.5, Hauteur - 0.5, Largeur, Hauteur);
  fprintf(f, "     xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">\n");
  return f;
}

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
void SvgWriteImage(FILE *IdFichSVG, char NomFichierImage[], int NbCol, int NbLig)
{
  // Write the image tag with the link to the file containing the image
  fprintf(IdFichSVG, "<image x=\"-0.5\" y=\"-0.5\" width=\"%dpx\" height=\"%dpx\" opacity=\"0.5\"\n",
          NbCol, NbLig);
  fprintf(IdFichSVG, "       xlink:href=\"%s\"\n", NomFichierImage);
  fprintf(IdFichSVG, "       image-rendering=\"pixelated\">\n");
  fprintf(IdFichSVG, "</image>\n");
}

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

// void SvgEcrirePolygone(FILE *IdFichSVG, float x[], float y[], int NbSommets, tStyle *pStyle)
void SvgWritePolygon(FILE *IdFichSVG, float x[], float y[], int NbSommets, tStyle *pStyle)
{
  // Écriture des segments avec la balise path
  // Write segments with the path tag
  fprintf(IdFichSVG, "  <path d=\"M%f %f", x[0], y[0]);
  for (int i = 1; i < NbSommets; i++)
  {
    fprintf(IdFichSVG, " L%f %f", x[i], y[i]);
  }
  fprintf(IdFichSVG, " Z\"\n");
  // Écriture du style des segments et de l'éventuel remplissage du polygone
  // Write the style of the segments and the possible filling of the polygon
  fprintf(IdFichSVG,
          "style=\"stroke:%s;stroke-width:%f;stroke-opacity:%f;fill:%s;fill-opacity:%f;"
          "stroke-linecap:round;stroke-linejoin:round\"",
          pStyle->ColorTrait,
          pStyle->WidthTrait,
          pStyle->OpaciteTrait,
          pStyle->ColorFill,
          pStyle->OpacityFill);
  fprintf(IdFichSVG, "  />\n");

  // Écriture des disques représentant les sommets du polygone et de leur style
  for (int i = 0; i < NbSommets; i++)
  {
    fprintf(IdFichSVG, "  <circle cx=\"%f\" cy=\"%f\" r=\"%f\" style=\"fill:%s\"/>\n",
            x[i], y[i], pStyle->RadiusPoints, pStyle->ColorPoints);
  }
}

/*
 * Closing a file in SVG format
 * The call to this function is essential for the file to be complete.
 * Entrance :
 * - IdFichSVG: identifier of the SVG file to close
 */
void SvgClose(FILE *IdFichSVG)
{
  fprintf(IdFichSVG, "</svg>\n");
  fclose(IdFichSVG);
}
