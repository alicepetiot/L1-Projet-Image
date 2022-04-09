#include <stdexcept>
/** @file
 * Lecture et ecriture d'images en niveau de gris au format PGM
 **/

#include <iostream>
#include <fstream>
#include "image.h"
#include "pgm.h"


/** Auteur : Alice PETIOT **/
ImageGris lirePGM(string source) {
    ifstream fichier;
	fichier.open(source);
	ifstream PGM(source);
	if (not PGM) {
		throw runtime_error ("Fichier non trouve: " + source);
	}
	string nbMagique;
	fichier >> nbMagique;
	int nbColonne;
	fichier >> nbColonne;
	int nbLigne;
	fichier >> nbLigne;
	int maxEntier;
	fichier >> maxEntier;
	int chiffre;
	ImageGris tableau;
	tableau = ImageGris(nbLigne);

    for (int i = 0; i < nbLigne; i++) { 
    	tableau[i] = vector<double>(nbColonne);
    }
    
    for (int i = 0; i < nbLigne; i++) {
    	for (int j = 0; j < nbColonne; j++) {
    		fichier >> chiffre;
    		tableau[i][j] = chiffre;  
    	}
    }
    fichier.close();
    return tableau;
}

/**Auteur : Paul ORIAT **/
void ecrirePGM(ImageGris img, string cible) {
    ofstream fichier;
    fichier.open(cible);
    string nbMagique = "P2";
    int nbLigne = img.size();
	int nbColonne = img[0].size();
	int maxEntier = 255;
	fichier << nbMagique << endl;
    fichier << nbColonne << " " << nbLigne << endl;
    fichier << maxEntier << endl;
    
	for (int i = 0; i < nbLigne; i++) {
    	for (int j = 0; j < nbColonne; j++) {
    		fichier << ((int)img[i][j]) << " ";  
    	}
	}
	fichier.close();
}

bool ImageGrisEgal(ImageGris a, ImageGris b, float precision) {
    if (a.size() != b.size())  {
        cout << "Nombre de lignes différent" << endl;
        return false;
    }
    for (int i=0; i<a[0].size(); i++)
        if (a[0].size() != b[i].size()) {
            cout << "Nombre de colonnes différent" << endl;
            return false;
        }
    for (int i=0; i<a.size(); i++)
        for (int j=0; j<a[0].size(); j++)
            if (abs(a[i][j] - b[i][j]) > precision) {
                cout << "Valeur differentes en position " << i << "," << j
             << ": " << a[i][j] << " au lieu de " << b[i][j] << endl;
                return false;
            }
    return true;
}

/** Auteur : Paul ORIAT **/
ImageGris inversePGM(ImageGris img) {
    int nbLigne = img.size();
	int nbColonne = img[0].size();
	int maxEntier = 255;
	for (int i = 0; i < nbLigne; i++) {
    	for (int j = 0; j < nbColonne; j++) {
    		img[i][j] = maxEntier - img[i][j];
    	}
    }
    return img;
}
