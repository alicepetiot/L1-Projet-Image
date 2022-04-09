#include <stdexcept>
/** @file
 * Lecture et ecriture d'images binaires au format PBM
 **/
#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
using namespace std;
/** Structure de donnée pour représenter une image binaire **/
typedef vector<vector<int> > ImageNB;

/** Auteur : Paul ORIAT
 * Complexité : Si on considère - l'incrementation des compteur n² + n fois
								- la lecture du chiffre n² + 3 fois
								- l'affectation dans le tableau n² fois 
								Complexité = 3n² + n + 3 
 * Confiance sur une échelle de pas confiant, confiant, très confiant : 
 		- Très confiant : les images obtenues avec les tests sont bien celles attendues par rapport à la correction
 * Construire une image binaire depuis un fichier PBM
 * @param source le nom d'un fichier PBM
 * @return une image binaire (0/1)
 **/
ImageNB lirePBM(string source) {
    ifstream fichier;
    fichier.open(source);
    ifstream PBM(source);
    if (not PBM) {
    	throw runtime_error ("Fichier non trouvé: " + source);
    }
    string nombreMagique;
    fichier >> nombreMagique;
    int nbColonne;
    fichier >> nbColonne;
    int nbLigne;
    fichier >> nbLigne;
    int chiffre;
    ImageNB tableau;
    tableau = ImageNB(nbLigne);
	
    for (int i = 0; i < nbLigne; i++) { // Une ligne contient tant de colonne
    	tableau[i] = vector<int>(nbColonne);
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

/** Auteur : Alice PETIOT
 * Complexité : Si on considère - l'incrementation des compteur n² fois
								- l'écriture des chiffres n² + 3 fois
								Complexité = 2n² + 3 
 * Confiance sur une échelle de pas confiant, confiant, très confiant : 
 		- Très confiant : les images obtenues avec les tests sont bien celles attendues par rapport à la correction
 * Ecrit une image binaire dans un fichier PBM
 * @param img une image binaire (0/1)
 * @param cible le nom d'un fichier PBM
 **/
void ecrirePBM(ImageNB img, string cible) {
	ofstream fichier;
    fichier.open(cible);
    fichier << "P1" << endl;
    int nbLigne = img.size();
	int nbColonne = img[0].size();
    fichier << nbColonne << " " << nbLigne << endl;
    
	for (int i = 0; i < nbLigne; i++) {
    	for (int j = 0; j < nbColonne; j++) {
    		fichier << img[i][j] << " ";  
    	}
	}
	fichier.close();
}

/** Auteur : Alice PETIOT
 * Complexité : Si on considère - l'incrementation des compteur n² fois
								- le test d'égalité if n²
								Complexité = 2n²
 * Confiance sur une échelle de pas confiant, confiant, très confiant : 
 		- Très confiant : les images obtenues avec les tests sont bien celles attendues par rapport à la correction
/**Affiche une image binaire PBM à l'écran avec ' ' pour 0 et '@' pour 1
 * @param img une image binaire (0/1)
 **/
void affichePBM(ImageNB img) {
	int nbLigne = img.size();
	int nbColonne = img[0].size();
    for (int i = 0; i < nbLigne; i++) {
    	for (int j = 0; j < nbColonne; j++) {
    		if (img[i][j] == 0) {
    			cout << " ";
    		} else {
    			cout << "@";
    		}
    	}
    	cout << endl;
    }
}


/** Auteur :  Paul ORIAT
 * Complexité : Si on considère - l'incrementation des compteur n² fois
								- le test d'égalité if n² fois
								- l'affectation n² fois
								Complexité = 3n²
 * Confiance sur une échelle de pas confiant, confiant, très confiant : 
 		- Très confiant : les images obtenues avec les tests sont bien celles attendues par rapport à la correction
/** Echange le noir et le blanc dans une image PBM
 * @param img une image binaire (0/1)
 * @return l'image où le blanc et le noir ont été inversés
 **/
ImageNB inversePBM(ImageNB img) {
	int nbLigne = img.size();
	int nbColonne = img[0].size();
	for (int i = 0; i < nbLigne; i++) {
    	for (int j = 0; j < nbColonne; j++) {
    		if (img[i][j] == 0) {
    			img[i][j] = 1;
    		} else {
    			img[i][j] = 0;
    		}
    	}
    }
    return img;
}


void testLirePBM(){
    cout << "Vérifier que les images obtenues dans 'pbm/' sont semblables à celles fournies dans 'pbm/correction/'" << endl;
    ecrirePBM(lirePBM("images/smiley.pbm"),  "pbm/smiley.pbm");
    ecrirePBM(lirePBM("images/cercle.pbm"),  "pbm/cercle.pbm");
    ecrirePBM(lirePBM("images/code.pbm"), "pbm/code.pbm");
    ecrirePBM(lirePBM("images/damier.pbm"), "pbm/damier.pbm");
}

int main(){
	testLirePBM();
	ecrirePBM(inversePBM(lirePBM("images/smiley.pbm")),  "pbm/smiley.pbm");
	ecrirePBM(inversePBM(lirePBM("images/cercle.pbm")),  "pbm/cercle.pbm");
	ecrirePBM(inversePBM(lirePBM("images/code.pbm")), "pbm/code.pbm");
	ecrirePBM(inversePBM(lirePBM("images/damier.pbm")), "pbm/damier.pbm");
	affichePBM(lirePBM("pbm/smiley.pbm"));
	affichePBM(lirePBM("pbm/cercle.pbm"));
	affichePBM(lirePBM("pbm/code.pbm"));
	affichePBM(lirePBM("pbm/damier.pbm"));
    return 0;
}

