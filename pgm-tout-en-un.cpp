#include <stdexcept>
/** @file
 * Lecture et ecriture d'images en niveau de gris au format PGM
 **/
#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
using namespace std;
/** Structure de donnee pour representer une image en teintes de gris **/
typedef vector<vector<double> > ImageGris;

/** Construire une image en teintes de gris depuis un fichier PGM
 * @param source le nom d'un fichier PGM
 * @return une image en teintes de gris
 **/
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

/** Ecrit une image en teintes de gris dans un fichier PGM
 * @param img une image en teintes de gris
 * @param cible le nom d'un fichier PGM
 **/
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
    		fichier << img[i][j] << " ";  
    	}
	}
	fichier.close();
}


/** Construit une image cliché d'une image en niveau de gris
 * @param img une image en niveau de gris
 * @return l'image cliché qui inverse les niveaux de gris
 **/
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

void lirePGMTest(){
    cout << "Vérifier que les images obtenues dans 'pgm/' sont semblables à celles fournies dans 'pgm/correction/'" << endl;
    ecrirePGM(lirePGM("images/brain.pgm"),  "pgm/brain.pgm");
    ecrirePGM(lirePGM("images/illusion.pgm"),  "pgm/illusion.pgm");
}

void inversePGMTest() {
    ImageGris imageOriginale;
    cout << "Vérifier que les images obtenues dans 'pgm/' sont semblables à celles fournies dans 'pgm/correction/'" << endl;
    imageOriginale = lirePGM("images/brain.pgm");
    ecrirePGM(inversePGM(imageOriginale),  "pgm/brain.pgm");
    imageOriginale = lirePGM("images/illusion.pgm");
    ecrirePGM(inversePGM(imageOriginale),  "pgm/illusion.pgm");
}

int main() {
    lirePGMTest();
    inversePGMTest();
    return 0;
}
