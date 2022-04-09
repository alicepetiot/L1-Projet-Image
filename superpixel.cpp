#include <stdexcept>
/** @file
 * Filtre Super Pixel
 **/
#include <cmath>
#include "superpixel.h"

double distancePoints(Point p, Point c) {
    vector<int>vecteurPC;
    vecteurPC = vector<int>(p.size());
    int distancePC = 0;
    for (int i = 0; i <+ p.size(); i++) {
        vecteurPC[i] = p[i]-c[i];
        distancePC += vecteurPC[i]*vecteurPC[i]; 
    }
    return sqrt(distancePC);
}


double distanceAEnsemble(Point p, EnsemblePoints C) {

int distancePlusCourte = distancePoints(p,C[0]);

for(int i=1; i<C.size(); i++) {
    if(distancePlusCourte>distancePoints(p,C[i])) {
            distancePlusCourte=distancePoints(p,C[i]);
        }
    }       
    return distancePlusCourte;
}
int plusProcheVoisin(Point p, EnsemblePoints C) {
Point c = C[0]
int k = 0;
	for (int i = 0; i < C.size(); i++) {
		if (distancePoint(p,C[i]) < distancePoint(p,c)) {
			c = C[i];
            k = i;
		}
		return i;  
	} 
}


EnsemblePoints sousEnsemble(EnsemblePoints P,EnsemblePoints C,int k) {
    EnsemblePoints Pvoisink;
    for (int i = 0; i < P.size(); i++) {
    	Point p = P[i];          
        if (k == plusProcheVoisin(p,C)) {
        	Pvoisink.push_back(p);
        }
    }
    return Pvoisink;
}

Point barycentre(EnsemblePoints Q) {
    vector<double>barycentre(Q.size());
    for (int i = 0; i < Q.size(); i++) {
        for (int j = 0; j < Q[0].size(); j++) {
            barycentre[i] = Q[i][j] + barycentre[i];
        }
    }

    for (int i = 0; i < Q[0].size(); i++) {
        barycentre[i] = barycentre[i]/Q.size();
    }
    return barycentre; 
}

EnsemblePoints KMoyenne(EnsemblePoints P,EnsemblePoints C, int nbAmeliorations) {
    EnsemblePoints Classe;
    for (int i = 0; i < nbAmeliorations; i++) {
        Point p = P[i];
        Point c = C[i];
        Classe.push_back(barycentre(sousEnsemble(P,C, distancePoints(p,c))));
    }
    return Classe;
}

EnsemblePoints FAST_KMoyenne(EnsemblePoints P,EnsemblePoints C, int nbAmeliorations) {
    vector<int> label;
    label.resize(P.size());
    for(int n=0; n<nbAmeliorations; n++) {
        vector<int> clusterSize;
        clusterSize.resize(C.size(),0);
        for (int p=((int)P.size())-1; p>=0; p--) {
            double di = 0;
            int nn=0;
            for(int d=((int)P[0].size())-1; d>=0; d--)
                di+=(P[p][d]-C[0][d])*(P[p][d]-C[0][d]);
            for(int c=((int)C.size())-1; c>=1; c--) {
                double dt=0;
                for(int d=((int)P[0].size())-1; d>=0; d--)
                    dt+=(P[p][d]-C[c][d])*(P[p][d]-C[c][d]);
                if(dt<di) {
                    di=dt;
                    nn=c;
                }
            }
            label[p]=nn;
            clusterSize[nn]++;
        }
        for (int p=((int)P.size())-1; p>=0; p--)
            for(int d=((int)P[0].size())-1; d>=0; d--)
                C[label[p]][d]+=P[p][d];
        for(int c=((int)C.size())-1; c>=0; c--)
            if(clusterSize[c]!=0)
                for(int d=((int)P[0].size())-1; d>=0; d--)
                    C[c][d] = C[c][d]/(clusterSize[c]+1);
    }
    return C;
}

EnsemblePoints pivotSuperPixel(Image img, double lambda, int mu) {
    // Remplacer la ligne suivante par le code adéquat
    throw runtime_error("Fonction pivotSuperPixel non implanté ligne 74");
}

EnsemblePoints superPixels(Image img,double lambda, int mu, int nbAmeliorations) {
    // Remplacer la ligne suivante par le code adéquat
    throw runtime_error("Fonction superPixels non implanté ligne 79");
}

Image superPixel(Image img, double lambda, int mu, int nbAmeliorations) {
    // Remplacer la ligne suivante par le code adéquat
    throw runtime_error("Fonction superPixel non implanté ligne 84");
}
