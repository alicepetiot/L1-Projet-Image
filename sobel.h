#ifndef SOBEL_H
#define SOBEL_H
#include <stdexcept>
/** @file
 * Filtres de Sobel
 **/

#include "image.h"
/** Auteur : Alice PETIOT **/
/** Complexité : Si on considère 	- l'incrementation des compteur 2(n-1)²+n² fois
									- l'affectation 2n² fois
									Complexité = 3n² + 2(n-1)²
 * Confiance sur une échelle de pas confiant, confiant, très confiant : 
 		- Très confiant : les images obtenues avec les tests sont pareils que dans la correction
**/
/** filtre de Sobel horizontal
 * @param img une image en teintes de gris
 * @return une image en teintes de gris de l'intensite horizontale de img
 **/
ImageGris intensiteH(ImageGris img);

/** Auteur : Alice PETIOT **/
/** Complexité : Si on considère 	- l'incrementation des compteur 2(n-1)²+n² fois
									- l'affectation 2n² fois
									Complexité = 3n² + 2(n-1)²
 * Confiance sur une échelle de pas confiant, confiant, très confiant : 
 		- Très confiant : les images obtenues avec les tests sont pareils que dans la correction
**/
/** filtre de Sobel vertical
 * @param img une image en teintes de gris
 * @return une image en teintes de gris de l'intensite verticale de img
 **/
ImageGris intensiteV(ImageGris img);
/** Auteur : Alice PETIOT **/
/** Complexité : Si on considère 	- l'incrementation des compteur n² fois
									- l'affectation n² fois
									Complexité = 2n²
 * Confiance sur une échelle de pas confiant, confiant, très confiant : 
 		- Très confiant : les images obtenues avec les tests sont pareils que dans la correction
**/
/** filtre de Sobel
 * @param img une image en teintes de gris
 * @return une image en teintes de gris de l'intensite de img
 **/
ImageGris intensite(ImageGris img);
#endif
