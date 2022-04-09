#include <stdexcept>
/** @file
 * Filtres de Sobel
 **/
#include <cmath>
#include "sobel.h"

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
