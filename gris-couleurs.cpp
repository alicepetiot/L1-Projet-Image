#include <stdexcept>
/** @file
 * Filtres de conversion couleur <-> teintes de gris
 **/
#include "gris-couleurs.h"
#include "pgm.h"
#include "ppm.h"

ImageGris CouleurAuGris( Image img ) {
    ImageGris imgGris;
    imgGris = ImageGris(img.size());
    for (int i = 0; i < img.size(); i++) {
        imgGris[i] = vector<double>(img[0].size());
    }

    for (int i = 0; i < img.size(); i++) {
        for (int j = 0; j < img[0].size(); j++) {
            imgGris[i][j] = 0.2126*(img[i][j].r) + 0.7152*(img[i][j].g) + 0.0722*(img[i][j].b);
        }
    }
    return imgGris;
}

Image GrisACouleur( ImageGris img ) {
    Image imgCouleur;
    imgCouleur = Image(img.size());
    for (int i = 0; i < img.size(); i++) {
        imgCouleur[i] = vector<Couleur>(img[0].size());
    }

    for (int i = 0; i < img.size(); i++) {
        for (int j = 0; j < img[0].size(); j++) {
            imgCouleur[i][j].r = img[i][j];
            imgCouleur[i][j].b = img[i][j];
            imgCouleur[i][j].g = img[i][j];
        }
    }
    return imgCouleur;
}
