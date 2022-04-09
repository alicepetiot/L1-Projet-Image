#include <stdexcept>
/** @file
 * Filtres de conversion couleur <-> teintes de gris
 **/

#include "image.h"
/** Auteur : Alice PETIOT **/
/** Complexité : Si on considère 	- l'incrementation des compteur n² + n fois
									- l'affectation n² fois
									Complexité = 2n²+n
 * Confiance sur une échelle de pas confiant, confiant, très confiant : 
 		-très confiant : les images obtenues avec le test sont les même que la correction
**/
/** Transforme une image couleur en une image en teintes de gris
 * @param img une image
 * @return une image en teintes de gris
 **/
ImageGris CouleurAuGris(Image img);

/** Auteur : Alice PETIOT **/
/** Complexité : Si on considère 	- l'incrementation des compteur n² + n fois
									- l'affectation 3n² fois
									Complexité = 5n²+n
 * Confiance sur une échelle de pas confiant, confiant, très confiant : 
 		-très confiant : les images obtenues avec le test sont les même que la correction
**/
/** Transforme une image en teintes de gris en une image en couleurs (mais grise)
 * @param img une image en teintes de gris
 * @return une image
 **/
Image GrisACouleur(ImageGris img);
