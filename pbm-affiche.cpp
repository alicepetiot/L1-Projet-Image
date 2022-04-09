#include <stdexcept>
/** @file
 * Affichage d'une image PBM
 **/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;
 

/**Affiche une image binaire PBM à l'écran avec ' ' pour 0 et '@' pour 1
 * @param source le nom d'un fichier PBM
 **/
 
void affichePBM(string source)  {
	ifstream fichier;
	fichier.open(source);
	int chiffre; 
	int nbLigne;
	int nbColonne;
	string debut;
	fichier>>debut; 
	fichier>>nbLigne;
	fichier>>nbColonne;
	for (int i = 0; i < nbLigne; i++)  { 
		for (int j = 0; j < nbColonne; j++) { 
			fichier >> chiffre; 
			if (chiffre == 0) { 
				cout << " ";
			} else {
				cout << "@";
			}
		}
		cout << endl;
	}
	fichier.close();
}
	
			

/**Echange le noir et le blanc dans une image PBM
 * @param source le nom du fichier PBM à lire
 * @param cible le nom du nouveau fichier PMB créé
 **/
void inversePBM(string source, string cible) {
    ifstream fichier;
    fichier.open(source);
    ofstream fichier2;
    fichier2.open(cible);
    string debut;
    fichier >> debut;
    int nbLigne;
    fichier >> nbLigne;
    int nbColonne;
    fichier >> nbColonne;
    int chiffre;
    fichier2 << debut << endl;
    fichier2 << nbLigne << " " << nbColonne << endl;
    for (int i = 0; i < nbColonne; i++) {
    	for (int j = 0; j < nbLigne; j++) {
    		fichier >> chiffre;
    		if (chiffre == 0) {
    			fichier2 << "1 ";
    		} else {
    			fichier2 << "0 ";
    		}
    	}
    }
    fichier.close();
    fichier2.close();
}


int main(){
    cout << "Affichage du smiley " << endl;
    affichePBM("./images/smiley.pbm");
    cout << "Fabrication du smiley inversé (vérifiez que le nouveau fichier a été créé dans le dosier pbm/smiley-inverse.pbm" << endl;
    inversePBM("images/smiley.pbm","pbm/smiley-inverse.pbm");
    cout << "Affichage du smiley inversé" << endl;
    affichePBM("./pbm/smiley-inverse.pbm");
    return 0;
}
