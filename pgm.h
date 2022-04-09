#ifndef PGM_H
#define PGM_H

#include <stdexcept>
/** @file
 * Lecture et ecriture de fichiers au format PGM
 **/


#include <string>
#include "image.h"
/** Auteur : Alice PETIOT **/
/** Complexité : Si on considère 	- l'incrementation des compteur n² + n fois
								 	- la lecture des chiffres n² + 3 fois 
									- l'affectation n² fois
								Complexité = 3n² + n + 3
 * Confiance sur une échelle de pas confiant, confiant, très confiant : 
 		- Très confiant : les images obtenues avec les tests sont pareils que dans la correction
**/
/** Construire une image en teintes de gris depuis un fichier PGM
 * @param source le nom d'un fichier PGM
 * @return une image en teintes de gris
 **/
ImageGris lirePGM(string source);

/** Auteur : Paul ORIAT **/
/** Complexité : Si on considère 	- l'incrementation des compteur n² fois
								 	- l'écriture des chiffres n² + 3 fois 
									Complexité = 2n² +  + 3
 * Confiance sur une échelle de pas confiant, confiant, très confiant : 
 		- Très confiant : les images obtenues avec les tests sont pareils que dans la correction
**/
/** Ecrit une image en teintes de gris dans un fichier PGM
 * @param img une image en teintes de gris
 * @param cible le nom d'un fichier PGM
 **/
void  ecrirePGM(ImageGris img, string cible);

/** Teste si deux images en teintes de gris sont égales modulo imprécision numérique
 * En cas de différence un message est affiché
 * @param a une image en teintes de gris
 * @param b une image en teintes de gris
 * @param precision un flottant positif: la précision souhaitée; typiquement 0.001
 * @return vrai si les images sont égales et faux sinon
 **/
bool ImageGrisEgal(ImageGris a, ImageGris b, float precision);

/** Auteur : Paul ORIAT **/
/** Complexité : Si on considère 	- l'incrementation des compteur n² fois
									- l'affectation n² fois
									Complexité = 2n²
 * Confiance sur une échelle de pas confiant, confiant, très confiant : 
 		- Très confiant : les images obtenues avec les tests sont pareils que dans la correction
**/
/** Construit une image cliché d'une image en niveau de gris
 * @param img une image en niveau de gris
 * @return l'image cliché qui inverse les niveaux de gris
 **/
ImageGris inversePGM(ImageGris img);

#endif
