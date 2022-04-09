#ifndef PPM_H
#define PPM_H
#include <stdexcept>
/** @file
 * Lecture et ecriture de fichiers au format PPM
 **/

#include <string>
#include "image.h"

/** Auteur : Paul ORIAT **/
/** Complexité : Si on considère 	- l'incrementation des compteur n²  + n fois
                                    - la lecture du fichier 3n² + 4 fois 
									- l'affectation 3n² fois
									Complexité = 7n²+n+4
 * Confiance sur une échelle de pas confiant, confiant, très confiant : 
 		-très confiant : les images obtenues avec le test sont les même que la correction
**/
/** Lit une image au format PPM, retourne un tableau de Couleur
 * @param source vers une image .ppm
 * @return une image
 **/
Image lirePPM(string source);

/** Auteur : Alice PETIOT **/
/** Complexité : Si on considère 	- l'incrementation des compteur n² fois
                                    - l'écriture du fichier n² + 4 fois
									Complexité = 2n²+n+4
 * Confiance sur une échelle de pas confiant, confiant, très confiant : 
 		-très confiant : les images obtenues avec le test sont les même que la correction
**/
/**  Écrit une image dans un fichier PPM
 * @param img une image
 * @param cible le nom d'un fichier PPM
 **/
void  ecrirePPM(Image img, string cible);
#endif
