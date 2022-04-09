#include <stdexcept>
/** @file
 * Filtres de Sobel
 **/
#include <cmath>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <fstream>
using namespace std;

/** Structure de donnee pour representer une image en teintes de gris **/
typedef vector<vector<double> > ImageGris;



/** Infrastructure minimale de test **/
#define ASSERT(test) if (!(test)) cout << "Test failed in file " << __FILE__ << " line " << __LINE__ << ": " #test << endl


/** Une image 4x4 en teintes de gris pour faire des tests **/
ImageGris imgGrisTest = {
    {0, 255, 54.213, 236.589},
    {18.411, 182.376, 200.787, 120},
    {139.583, 172.841, 94.0878, 88.4974},
    {158.278, 172.841, 89.0236, 80.0384}
};



/** Construire une image en teintes de gris depuis un fichier PGM
 * @param source le nom d'un fichier PGM
 * @return une image en teintes de gris
 **/
ImageGris lirePGM(string source) {
    ifstream fichier;
	fichier.open(source);
	ifstream PGM(source);
	if (not PGM) {
		throw runtime_error ("Fichier non trouvé: " + source);
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
    		fichier << ((int)img[i][j]) << " ";  
    	}
	}
	fichier.close();
}








/** Teste si deux images en teintes de gris sont égales modulo imprécision numérique
 * En cas de différence un message est affiché
 * @param a une image en teintes de gris
 * @param b une image en teintes de gris
 * @param precision un flottant positif: la précision souhaitée; typiquement 0.001
 * @return vrai si les images sont égales et faux sinon
 **/
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


/** filtre de Sobel horizontal
 * @param img une image en teintes de gris
 * @return une image en teintes de gris de l'intensite horizontale de img
 **/
ImageGris intensiteH(ImageGris img) {
    ImageGris imgH;
    imgH = img;
    for (int i = 0; i < img.size(); i++) {
        for (int j = 0; j < img[0].size(); j++) {
            imgH[i][j] = 0;
        }
    }

    for (int i = 1; i < img.size()-1; i++) {
        for (int j = 1; j < img[0].size()-1;j++) {
            imgH[i][j] = img[i-1][j-1] + 2*img[i][j-1] + img[i+1][j-1] - img[i-1][j+1] - 2*img[i][j+1] - img[i+1][j+1];
        }
    }
    return imgH;
}


/** filtre de Sobel vertical
 * @param img une image en teintes de gris
 * @return une image en teintes de gris de l'intensite verticale de img
 **/
ImageGris intensiteV(ImageGris img) {
    ImageGris imgV;
    imgV = img;
    for (int i = 0; i < img.size(); i++) {
        for (int j = 0; j < img[0].size(); j++) {
            imgV[i][j] = 0;
        }
    }

    for (int i = 1; i < img.size()-1; i++) {
        for (int j = 1; j < img[0].size()-1;j++) {
            imgV[i][j] = img[i-1][j-1] + 2*img[i-1][j] + img[i-1][j+1] - img[i+1][j-1] - 2*img[i+1][j] - img[i+1][j+1] ;
        }
    }
    return imgV;
}


/** filtre de Sobel
 * @param img une image en teintes de gris
 * @return une image en teintes de gris de l'intensite de img
 **/
ImageGris intensite(ImageGris img) {
    ImageGris imgVH, imgH, imgV;
    imgVH = img;
    imgH = intensiteH(img);
    imgV = intensiteV(img);
    for (int i = 0; i < img.size(); i++) {
        for (int j = 0; j < img[0].size();j++) {
            imgVH[i][j] = sqrt((imgH[i][j]*imgH[i][j]) + (imgV[i][j]*imgV[i][j]));
        }
    }
    return imgVH;
}


void testSobel() {
    ASSERT( ImageGrisEgal(intensiteH(imgGrisTest),
              ImageGris( {
                  {0, 0, 0, 0},
                  {0, -373.47, 227.507, 0},
                  {0, -22.1312, 323.866, 0},
                  {0, 0, 0, 0}
              }),
              0.001) );
    ASSERT( ImageGrisEgal(intensiteV(imgGrisTest),
               ImageGris( {
                   {0, 0, 0, 0},
                   {0, -15.1398, 150.501, 0},
                   {0, -9.0336, 273.023, 0},
                   {0, 0, 0, 0}
               }),
               0.001) );
    ASSERT( ImageGrisEgal(intensite(imgGrisTest),
               ImageGris( {
                   {0, 0, 0, 0},
                   {0, 373.777, 272.782, 0},
                   {0, 23.9039, 423.593, 0},
                   {0, 0, 0, 0}
               }),
               0.001) );

    cout << "Vérifier que les images obtenues dans 'sobel/' sont semblables à celles fournies dans 'sobel/correction/'" << endl;
    ecrirePGM(intensite(lirePGM("images/Baboon.512.pgm" )), "sobel/Baboon.512.pgm");
    ecrirePGM(intensite(lirePGM("images/Billes.256.pgm" )), "sobel/Billes.256.pgm");
    ecrirePGM(intensite(lirePGM("images/Embryos.512.pgm")), "sobel/Embryos.512.pgm");
    ecrirePGM(intensite(lirePGM("images/House.256.pgm"  )), "sobel/House.256.pgm");
    ecrirePGM(intensite(lirePGM("images/Lena.512.pgm"   )), "sobel/Lena.512.pgm");
}



int main(){
    testSobel();
    return 0 ;
}
