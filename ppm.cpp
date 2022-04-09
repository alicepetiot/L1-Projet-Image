#include <stdexcept>
/** @file
 * Lecture et écriture d'images au format PPM
 **/


#include <iostream>
#include <fstream>
#include "image.h"
#include "ppm.h"

/** Construire une image en couleur depuis un fichier PPM
 * @param source le nom d'un fichier PPM
 * @return une image en couleur
 **/
Image lirePPM(string source) {
    ifstream fichier;
    fichier.open(source);
    string nbMagique;
    fichier >> nbMagique;
    int nbColonne;
    fichier >> nbColonne;
    int nbLigne;
    fichier >> nbLigne;
    int nbMax;
    fichier >> nbMax;
    int rouge;
    int vert;
    int bleu;
    Image imgCouleur;
    imgCouleur = Image(nbLigne);

    for (int i = 0; i < nbLigne; i++) {
        imgCouleur[i] = vector<Couleur>(nbColonne);
    }

    for (int i = 0; i < nbLigne; i++) {
        for (int j = 0; j < nbColonne; j++) {
            fichier >> rouge; 
            fichier >> bleu;
            fichier >> vert;
            imgCouleur[i][j].r = rouge; 
            imgCouleur[i][j].b = bleu;
            imgCouleur[i][j].g = vert;
        }
    }
    fichier.close();
    return imgCouleur;
}


/** Ecrit une image en couleur dans un fichier PPM
 * @param img une image en couleur
 * @param cible le nom d'un fichier PPM
 **/
void ecrirePPM(Image img, string cible) {
    ofstream fichier;
    fichier.open(cible);
    string nbMagique = "P3";
    int nbLigne = img.size();
	int nbColonne = img[0].size();
	int nbMax = 255;
	fichier << nbMagique << endl;
    fichier << nbColonne << " " << nbLigne << endl;
    fichier << nbMax << endl;
    
	for (int i = 0; i < nbLigne; i++) {
    	for (int j = 0; j < nbColonne; j++) {
    		fichier << img[i][j].r << " " << img[i][j].b << " " << img[i][j].g << " ";
    	}
	}
	fichier.close();
}