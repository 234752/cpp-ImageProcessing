#include "CImg.h"

using namespace cimg_library;

float meanSquareError(CImg<unsigned char> &image1, CImg<unsigned char> &image2) {
    float e = 0;
    for (unsigned int x = 0; x < image1.width(); x++) {
        for (unsigned int y = 0; y < image1.height(); y++) {
            e += pow((image1(x,y) - image2(x,y)), 2);
        }
    }
    return e/(image1.height()*image2.width());
}
