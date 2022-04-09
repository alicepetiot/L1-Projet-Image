#include <stdexcept>
/** @file
 * Filtres de seuillage
 **/

#include <cmath>
#include "image.h"
#include "sobel.h"

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
            if (vMax != 0) {
                imgRenormalise[i][j] = (img[i][j]*255)/vMax;
            } else {
                imgRenormalise[i][j] = 0;
            }
        }
    }
    return imgRenormalise;
}

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
ImageGris doubleSeuillage(ImageGris imgIntensite, ImageGris imgContour, int seuil) {
    ImageGris imgIntensiteModif;
    imgIntensiteModif = imgIntensite;
    int nbColonne = imgIntensite[0].size();
    int nbLigne = imgIntensite.size();

    for (int i = 0; i < nbLigne; i++) {
        for (int j = 0; j < nbColonne; j++) {
            imgIntensiteModif[i][j] = 255;
        }
    }
    
    for (int i = 1; i < imgIntensite.size()-1; i++) {
        for (int j = 1; j < imgIntensite[0].size()-1; j++) {
            if (imgIntensite[i][j] > seuil and ((imgContour[i-1][j-1] == 0) 
                                            or  (imgContour[i-1][j] == 0) 
                                            or  (imgContour[i-1][j+1] == 0) 
                                            or  (imgContour[i][j-1] == 0) 
                                            or  (imgContour[i][j+1] == 0) 
                                            or  (imgContour[i+1][j-1] == 0) 
                                            or  (imgContour[i+1][j] == 0) 
                                            or  (imgContour[i+1][j+1] == 0))){
                imgIntensiteModif[i][j] = 0;
            }
        }
    }
    return imgIntensiteModif;

}


ImageGris doubleSeuillage(ImageGris imgIntensite, int seuilFort, int seuilFaible, int nbAmeliorations) {
    ImageGris imgDbSeuillage;
    imgDbSeuillage = seuillage(imgIntensite,seuilFort);
    for (int k = 0; k < nbAmeliorations; k++) {
        imgDbSeuillage = doubleSeuillage(imgIntensite, imgDbSeuillage , seuilFaible);
    }
    return imgDbSeuillage;
}
