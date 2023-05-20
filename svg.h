#ifndef SVG_H
#define SVG_H
#include <stdio.h>

/*
 * Module permettant de dessiner des polygones dans un fichier au format SVG
 */

// Style d'un polygone
typedef struct sStyle
{
  char *CouleurTrait; // Couleur des segments
  float LargeurTrait; // Largeur des segments en pixels
  float OpaciteTrait; // Opacité des segments (compris entre 0 et 1)
  char *CouleurRemplissage; // Couleur de remplissage du polygone ("none" pour aucun)
  float OpaciteRemplissage; // Opacité du remplissage du polygone (compris entre 0 et 1)
  char *CouleurPoints; // Couleur des sommets
  float RayonPoints; // Rayon, en pixels, des points représentant les sommets
} tStyle;
// Par exemple, pour obtenir des segments bleus d'une largeur de 0.125 pixel,
// des sommets rouges de 0.125 pixel de rayon et aucun remplissage à l'intérieur du 
// polygone, on peut utiliser le style suivant :
// tStyle Style={"blue",0.125,1,"none",0,"red",0.125};
// Les couleurs peuvent être spécifiées comme en HTML : "blue", "#0000FF", rgb(0,0,255).


/*
 * Création d'un fichier au format SVG
 * Si le fichier existe déjà, son contenu est écrasé
 * Entrées :
 *  - NomFichier : nom du fichier à créer
 *  - Largeur : largeur, en pixels de la zone de dessin
 *  - Hauteur : largeur, en pixels de la zone de dessin
 * Valeur de retour : identificateur du fichier ou NULL en cas de problème
 */
extern FILE *SvgCreer(char NomFichier[], int Largeur, int Hauteur);

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
extern void SvgEcrireImage(FILE *IdFichSVG, char NomFichierImage[], int NbCol, int NbLig);

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
extern void SvgEcrirePolygone(FILE *IdFichSVG, float x[], float y[], int NbSommets, tStyle *pStyle);

/*
 * Fermeture d'un fichier au format SVG
 * L'appel à cette fonction est indispensable pour que le fichier soit complet.
 * Entrée :
 *  - IdFichSVG : identificateur du fichier SVG à fermer
 */
extern void SvgFermer(FILE *IdFichSVG);


#endif /* SVG_H */
