#ifndef SUPERPIXEL_H
#define SUPERPIXEL_H
#include <stdexcept>
/** @file
 * Filtre Super Pixel
 **/

#include "image.h"

/** Structure de donnee representant un point dans l'espace 
    spacio colorimetrique **/
typedef vector<double> Point;

/** Structure de donnee representant un ensemble de points dans l'espace 
    spacio colorimetrique **/
typedef vector<Point> EnsemblePoints;

/** Auteur : Paul ORIAT **/
/** Complexité : Si on considère 	- l'incrementation du compteur n fois
									- les affectations 2n fois
									Complexité = 3n 
 * Confiance sur une échelle de pas confiant, confiant, très confiant : 
 		-très confiant : les tests sont bons
**/
/** Renvoie la distance Euclidienne entre deux points
 * @param p un point
 * @param c un point
 * @return la distance entre p et c
 **/
double distancePoints(Point p, Point c);
/** Auteur : Paul ORIAT **/
/** Complexité : Si on considère 	- l'incrementation du compteur n fois
                                    - le test d'égalité if n fois
									- l'affectation n fois
									Complexité = 3n 
 * Confiance sur une échelle de pas confiant, confiant, très confiant : 
 		- pas confiant : pas de test même si pas d'erreur pendant la compilation
**/
/** Renvoie la distance Euclidienne d'un point a un ensemble de points
 * @param p un point
 * @param C un ensemble de points
 * @return la distance
 **/
double distanceAEnsemble(Point p, EnsemblePoints C);

/** Auteur : Paul ORIAT **/
/** Complexité : Si on considère 	- l'incrementation du compteur n fois
                                    - le test d'égalité if n fois
									- l'affectation n fois
									Complexité = 3n 
 * Confiance sur une échelle de pas confiant, confiant, très confiant : 
 		-très confiant : les tests sont bons
**/
/** Renvoie le plus proche voisin d'un point p dans un ensemble C
 * @param p un point
 * @param C un ensemble de points
 * @return l'index du plus proche voisin
 **/
int plusProcheVoisin(Point p, EnsemblePoints C);

/** Auteur : Alice PETIOT **/
/** Complexité : Si on considère 	- l'incrementation du compteur n fois
                                    - le test d'égalité if n fois
									- l'affectation n fois
									Complexité = 3n 
 * Confiance sur une échelle de pas confiant, confiant, très confiant : 
 		-pas confiant : pas de test même si pas d'erreur pendant la compilation 
**/

/** Renvoie les points p de P tels que C[k] est le plus proche voisin de p dans C
 * @param P un ensemble de points
 * @param C un ensemble de points
 * @param k un entier
 * @return un sous ensemble des points de P
 **/
EnsemblePoints sousEnsemble(EnsemblePoints P, EnsemblePoints C,int k);

/** Auteur : Paul Oriat **/
/** Complexité : Si on considère 	- l'incrementation du compteur n fois
                                    - le test d'égalité if n fois
									- l'affectation n fois
									Complexité = 3n 
 * Confiance sur une échelle de pas confiant, confiant, très confiant : 
 		-confiant voir pas confiant : pas de test mais pas d'erreur pendant la compilation 
**/
/** Renvoie le barycentre d'unn ensemble de points
 * @param Q un ensemble de points
 * @return c le barycentre de Q
 **/
Point barycentre(EnsemblePoints Q);

/** Renvoie la K-moyenne de deux ensembles de points
 * @param P un ensemble de points
 * @param C un ensemble de points
 * @param nbAmeliorations:entier le nombre de fois ou l'amelioration va etre effectuee
 * @return C un ensemble de points les positions finales de points pilotes
 **/
EnsemblePoints KMoyenne(EnsemblePoints P, EnsemblePoints C, int nbAmeliorations);

/** Implantation optimisee de K-moyenne
 * @param P un ensemble de points
 * @param C un ensemble de points
 * @param nbAmeliorations:entier le nombre de fois ou l'amelioration va etre effectuee
 * @return C un ensemble de points les positions finales de points pilotes
 **/
EnsemblePoints FAST_KMoyenne(EnsemblePoints P, EnsemblePoints C, int nbAmeliorations);

/** Renvoie un ensemble de points (espace spatio colorimetrique) 
 *  regulierement espaces dans une image
 * @param img une image
 * @param lambda un double
 * @param mu un entier
 * @return un ensemble de points dans l'espace spatio colorimetrique
 **/
EnsemblePoints pivotSuperPixel (Image img, double lambda, int mu);

/** Renvoie les superpixels d'une image dans l'espace spatio colorimetrique
 * @param img une image en teintes de gris
 * @param lambda un double
 * @param mu un entier
 * @param nbAmeliorations un entier
 * @return un ensemble de points, les superpixels
 **/
EnsemblePoints superPixels(Image img, double lambda, int mu, int nbAmeliorations);

/** Filtre SuperPixel
 * @param img une image
 * @param lambda un double
 * @param mu un entier
 * @param nbAmeliorations
 * @return l'image associee aux superpixels d'une image
 **/
Image superPixel(Image img, double lambda, int mu, int nbAmeliorations);
#endif
