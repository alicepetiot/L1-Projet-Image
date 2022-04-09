#include <stdexcept>
/** @file
 * Filtres de seuillage
 **/

#include <cmath>
#include <iostream>
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

/** filtre de Sobel horizontal
 * @param img une image en teintes de gris
 * @return une image en teintes de gris de l'intensite horizontale de img
 **/
ImageGris intensiteH(ImageGris img) {
    ImageGris imgH;
    imgH = img;
    for (int j = 0; j < img[0].size(); j++) {
        imgH[0][j] = 0;
        imgH[img.size()-1][j] = 0;
    }
    
    for (int i = 0; i < img.size(); i++) {
        imgH[i][0] = 0;
        imgH[i][img[0].size()-1] = 0;
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
    for (int j = 0; j < img[0].size(); j++) {
        imgV[0][j] = 0;
        imgV[img.size()-1][j] = 0;
    }
    for (int i = 0; i < img.size(); i++) {
        imgV[i][0] = 0;
        imgV[i][img[0].size()-1] = 0;
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
    		fichier << img[i][j] << " ";  
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


/** Renormalize une image en teinte de gris, les ramenant dans l'intervalle [0,255]
 * @param img un image en teintes de gris
 * @return une image en teintes de gris
 **/
ImageGris renormalise(ImageGris img) {
    ImageGris imgRenormalise;
    imgRenormalise = img;
    int vMax = 0;
    for (int i = 0; i < img.size(); i++) {
        for (int j = 0; i < img[0].size(); j++) {
            if (img[i][j] > vMax) {
                vMax = img[i][j];
            } 
        }
    }

    for (int i = 0; i < img.size(); i++) {
        for (int j = 0; i < img[0].size(); j++) {
            imgRenormalise[i][j] = (img[i][j]*255)/vMax;
        }
    }
    return imgRenormalise;
}




/** Filtre de seuillage
 * @param img
 * @param seuil un entier dans l'intervalle [0,255]
 * @return image en noir et blanc obtenue en remplacant la teinte de
 *  chaque pixel par
 *  - du blanc si teinte < seuil
 *  - du noir  si teinte > seuil
 **/
ImageGris seuillage(ImageGris img, int seuil) {
    ImageGris imgPBM;
    imgPBM = img;
    for (int i = 0; i < img.size(); i++) {
       for (int j = 0; j < img[0].size(); j++) {
            if (img[i][j] < seuil) {
                imgPBM[i][j]=255;
            } else if (img[i][j] > seuil) {
                imgPBM[i][j]=0;
            }
       }
    }
    return imgPBM;
}

/** Filtre de double seuillage
 * @param imgIntensite image d'intensite
 * @param imgContour image codant un ensemble de pixels selectionnes
 * @param seuil un entier de l'intervalle [0,255]
 * @return une copie d'imgIntensite modifiee de sorte que:
 *  -si teinte > seuil et voisin d'un pixel de imgContour, alors pixel noir
 *  -sinon pixel blanc
 **/
ImageGris doubleSeuillage(ImageGris imgIntensite, ImageGris imgContour, int seuil) {
    ImageGris imgIntensiteModif;
    imgIntensiteModif = imgIntensite;
    
    for (int i = 0; i < imgIntensite.size(); i++) {
    	for (int j = 0; j < imgIntensite[0].size(); j++) {
    			imgIntensiteModif[i][j] = 255;
    	}
    }
    
    for (int i = 1; i < imgIntensite.size()-1; i++) {
        for (int j = 1; j < imgIntensite[0].size()-1; j++) {
            if (imgIntensite[i][j] > seuil and ((imgContour[i-1][j-1] == 0) or
                                                (imgContour[i-1][j] == 0) or
                                                (imgContour[i-1][j+1] == 0) or
                                                (imgContour[i][j-1] == 0) or
                                                (imgContour[i][j+1] == 0) or 
                                                (imgContour[i+1][j-1] == 0) or
                                                (imgContour[i+1][j] == 0) or
                                                (imgContour[i+1][j+1] == 0))){
                imgIntensiteModif[i][j] = 0;
            }
        }
    }
    return imgIntensiteModif;
}
/** Filtre de double seuillage iteratif
 * @param imgIntensite image d'intensité
 * @param seuilFort un entier de l'intervalle [0,255]
 * @param seuilFaible un entier de l'intervalle [0,255]
 * @param nbAmeliorations un entier non negatif: le nombre d'itérations
 * @return le double seuillage de img
 **/
ImageGris doubleSeuillage(ImageGris imgIntensite, int seuilFort, int seuilFaible, int nbAmeliorations) {
    ImageGris imgDbSeuillage;
    imgDbSeuillage = seuillage(imgIntensite,seuilFort);
    for (int k = 0; k < nbAmeliorations; k++) {
        imgDbSeuillage = doubleSeuillage(imgIntensite, imgDbSeuillage , seuilFaible);
    }
    return imgDbSeuillage;
}


void seuillageTest() {
    ASSERT( ImageGrisEgal(seuillage( imgGrisTest, 80),
              ImageGris( {
                  {255, 0, 255, 0},
                  {255, 0, 0, 0},
                  {0, 0, 0, 0},
                  {0, 0, 0, 0}
              }),
              0.001) );
    ASSERT( ImageGrisEgal(seuillage( intensite(imgGrisTest), 80),
              ImageGris( {
                  {255, 255, 255, 255},
                  {255, 0, 0, 255},
                  {255, 255, 0, 255},
                  {255, 255, 255, 255}
              }),
              0.001) );
    ASSERT( ImageGrisEgal(doubleSeuillage(intensite(imgGrisTest), 400, 80, 4 ),
                          ImageGris( {
                              {255, 255, 255, 255},
                              {255, 0, 0, 255},
                              {255, 255, 0, 255},
                              {255, 255, 255, 255}
                          }),
                          0.001) );


    cout << "Vérifier que les images obtenues dans 'seuillage/' sont semblables à celles fournies dans 'seuillage/correction/'" << endl;
    ecrirePGM(seuillage(intensite(lirePGM("images/Billes.256.pgm")), 80), "seuillage/Billes.256.pgm");
    ecrirePGM(seuillage(intensite(lirePGM("images/Lena.512.pgm"  )), 80), "seuillage/Lena.512.pgm");
    cout << "\tProposer des seuils pour Embryos.512.ppm et House.256.ppm" << endl;
}

void doubleSeuillageTest(){
    cout << "Vérifier que les images obtenues dans 'seuillage_double/' sont semblables à celles fournies dans 'seuillage_double/correction/'" << endl;

    ecrirePGM(doubleSeuillage(lirePGM("images/Lena.512.pgm"),
                              seuillage(intensite(lirePGM("images/Lena.512.pgm" )),80),70),
              "seuillage_double/Lena-unpas.512.pgm");
    ecrirePGM(doubleSeuillage(intensite(lirePGM("images/Billes.256.pgm")), 500, 80, 100), "seuillage_double/Billes.256.pgm");
    ecrirePGM(doubleSeuillage(intensite(lirePGM("images/Lena.512.pgm"  )), 500, 80, 100), "seuillage_double/Lena.512.pgm");
    cout << "\tProposer des seuils pour Embryos.512.ppm et House.256.ppm" << endl;
}


int main(){
    seuillageTest();
    doubleSeuillageTest();
    return 0;
}
