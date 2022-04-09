#ifndef SEUILLAGE_H
#define SEUILLAGE_H
#include <stdexcept>
/** @file
 * Filtres de seuillage
 **/

/** Auteur : Alice PETIOT **/
/** Complexité : Si on considère 	- l'incrementation des compteur 2n² fois
                                    - le test d'égalité if n² fois 
									- l'affectation n² fois
									Complexité = 4n²
 * Confiance sur une échelle de pas confiant, confiant, très confiant : 
 		-confiant voir pas confiant: pas d'erreur mais pas de test pour vérifier
**/
/** Renormalize une image en teinte de gris, les ramenant dans l'intervalle [0,255]
 * @param img un image en teintes de gris
 * @return une image en teintes de gris
 **/
ImageGris renormalise(ImageGris img);


/** Auteur : Alice PETIOT **/
/** Complexité : Si on considère 	- l'incrementation des compteur 2n² fois
                                    - le test d'égalité if 2n² fois 
									- l'affectation n² fois
									Complexité = 5n²
 * Confiance sur une échelle de pas confiant, confiant, très confiant : 
 		-très confiant: les images obtenues avec les tests sont les même quand dans la correction
**/
/** Filtre de seuillage
 * @param img
 * @param seuil un entier dans l'intervalle [0,255]
 * @return image en noir et blanc obtenue en remplacant la teinte de 
 *  chaque pixel par
 *  - du blanc si teinte < seuil
 *  - du noir  si teinte > seuil
 **/
ImageGris seuillage(ImageGris img, int seuil);


/** Auteur : Alice PETIOT **/
/** Complexité : Si on considère 	- l'incrementation des compteur 2(n-1)² + n² fois
                                    - le test d'égalité if 9n fois 
									- l'affectation n² fois
									Complexité = 2n² + 2(n-1)² + 9n
 * Confiance sur une échelle de pas confiant, confiant, très confiant : 
 		-confiant : pas d'erreur dans les tests mais aucune vérification visuelle
**/
/** Filtre de double seuillage
 * @param imgIntensite image d'intensite
 * @param imgContour image codant un ensemble de pixels selectionnes
 * @param seuil un entier de l'intervalle [0,255]
 * @return une copie d'imgIntensite modifiee de sorte que:
 *  -si teinte > seuil et voisin d'un pixel de imgContour, alors pixel noir
 *  -sinon pixel blanc
 **/
ImageGris doubleSeuillage(ImageGris imgIntensite, ImageGris imgContour, int seuil);

/** Auteur : Alice PETIOT **/
/** Complexité : Si on considère 	- l'incrementation du compteur n fois
									- l'affectation n² fois
									Complexité = n² + n
 * Confiance sur une échelle de pas confiant, confiant, très confiant : 
 		- pas confiant : pas d'erreur dans les tests mais les images obtenues ne sont pas les même que dans la correction
**/
/** Filtre de double seuillage iteratif
 * @param imgIntensite image d'intensité
 * @param seuilFort un entier de l'intervalle [0,255]
 * @param seuilFaible un entier de l'intervalle [0,255]
 * @param nbAmeliorations un entier non negatif: le nombre d'itérations
 * @return le double seuillage de img
 **/
ImageGris doubleSeuillage(ImageGris imgIntensite, int seuilFort, 
				int seuilFaible, int nbAmeliorations);
#endif


