#include <stdio.h>
#include <string.h>
#include "svg.h"

/*
 * Création d'un fichier au format SVG
 * Si le fichier existe déjà, son contenu est écrasé
 * Entrées :
 *  - NomFichier : nom du fichier à créer
 *  - Largeur : largeur, en pixels de la zone de dessin
 *  - Hauteur : largeur, en pixels de la zone de dessin
 * Valeur de retour : identificateur du fichier ou NULL en cas de problème
 */
FILE *SvgCreer(char NomFichier[], int Largeur, int Hauteur)
{
  // Ouverture du fichier
  FILE *f;
  f=fopen(NomFichier,"wt");
  if (f==NULL)
  {
    perror(NomFichier);
    return NULL;
  }
  // Ouverture de la balise svg
  fprintf(f,"<svg viewBox=\"-0.5 -0.5 %.1f %.1f\" width=\"%d\" height=\"%d\"\n",
          Largeur-0.5,Hauteur-0.5,Largeur,Hauteur);
  fprintf(f,"     xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">\n");
  return f;
}


/*
 * Écriture d'une image dans un fichier au format SVG
 * Le coin en haut à gauche du pixel en haut à gauche de l'image sera positionné en (0,0).
 * L'image n'est pas "embarquée" dans le fichier, seul un lien  est écrit.
 * Entrées :
 *  - IdFichSVG : identificateur du fichier SVG dans lequel va se faire l'écriture
 *  - NomFichierImage : nom du fichier contenant l'image à écrire (format PNG ou JPG)
 *  - NbCol : nombre de colonnes de l'image (largeur)
 *  - NbLig : nombre de lignes de l'image (hauteur)
 */
void SvgEcrireImage(FILE *IdFichSVG, char NomFichierImage[], int NbCol, int NbLig)
{
  // Écriture de la balise image avec le lien vers le fichier contenant l'image
  fprintf(IdFichSVG,"<image x=\"-0.5\" y=\"-0.5\" width=\"%dpx\" height=\"%dpx\"\n",
          NbCol,NbLig);
  fprintf(IdFichSVG,"       xlink:href=\"%s\"\n",NomFichierImage);
  fprintf(IdFichSVG,"       image-rendering=\"pixelated\">\n");
  fprintf(IdFichSVG,"</image>\n");
}


/*
 * Écriture d'un polygone dans un fichier au format SVG
 * Entrées :
 *  - IdFichSVG : identificateur du fichier SVG dans lequel va se faire l'écriture
 *  - x : tableau des NbSommets indices de colonnes des sommets du polygone
 *  - y : tableau des NbSommets indices de lignes des sommets du polygone
 *  - NbSommets : nombre de sommets du polygone
 *  - pStyle : adresse de la structure décrivant le style du polygone
 *
 * Le dernier sommet sera automatiquement relié par un segment au premier sommet.
 * Repère utilisé pour dessiner dans un fichier SVG :
 * (0,0)--------> x
 *   |
 *   |
 *   |
 *   v
 *   y 
 */
void SvgEcrirePolygone(FILE *IdFichSVG, float x[], float y[], int NbSommets, tStyle *pStyle)
{
  // Écriture des segments avec la balise path
  fprintf(IdFichSVG,"  <path d=\"M%f %f",x[0],y[0]);
  for (int i=1; i<NbSommets; i++)
  {
    fprintf(IdFichSVG," L%f %f",x[i],y[i]);
  }
  fprintf(IdFichSVG," Z\"\n");
  // Écriture du style des segments et de l'éventuel remplissage du polygone
  fprintf(IdFichSVG,
         "style=\"stroke:%s;stroke-width:%f;stroke-opacity:%f;fill:%s;fill-opacity:%f;"
         "stroke-linecap:round;stroke-linejoin:round\"",
          pStyle->CouleurTrait,
          pStyle->LargeurTrait,
          pStyle->OpaciteTrait,
          pStyle->CouleurRemplissage,
          pStyle->OpaciteRemplissage);
  fprintf(IdFichSVG,"  />\n");
  
  // Écriture des disques représentant les sommets du polygone et de leur style
  for (int i=0; i<NbSommets; i++)
  {
      fprintf(IdFichSVG,"  <circle cx=\"%f\" cy=\"%f\" r=\"%f\" style=\"fill:%s\"/>\n",
              x[i],y[i],pStyle->RayonPoints,pStyle->CouleurPoints);
  }
}

/*
 * Fermeture d'un fichier au format SVG
 * L'appel à cette fonction est indispensable pour que le fichier soit complet.
 * Entrée :
 *  - IdFichSVG : identificateur du fichier SVG à fermer
 */
void SvgFermer(FILE *IdFichSVG)
{
  fprintf(IdFichSVG,"</svg>\n");
  fclose(IdFichSVG);
}
