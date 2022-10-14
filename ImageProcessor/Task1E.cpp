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

float peakMeanSquareError(CImg<unsigned char> &image1, CImg<unsigned char> &image2) {
    float e = 0;
    float m = 0;
    for (unsigned int x = 0; x < image1.width(); x++) {
        for (unsigned int y = 0; y < image1.height(); y++) {
            if(image1(x,y) > m) m = image1(x,y);
        }
    }
    for (unsigned int x = 0; x < image1.width(); x++) {
        for (unsigned int y = 0; y < image1.height(); y++) {
            e += pow((image1(x,y) - image2(x,y)), 2);
        }
    }
    return e/(image1.height()*image2.width()); //idk where to divide by m
}

float signalToNoiseRatio(CImg<unsigned char> &image1, CImg<unsigned char> &image2) {
    float signal = 0;
    float noise = 0;
    for (unsigned int x = 0; x < image1.width(); x++) {
        for (unsigned int y = 0; y < image1.height(); y++) {
            signal += pow((image1(x,y)), 2);
            noise += pow((image1(x,y) - image2(x,y)), 2);
        }
    }
    return 10*log10(signal/noise);
}

float peakSignalToNoiseRatio(CImg<unsigned char> &image1, CImg<unsigned char> &image2) {
    float signal = 0;
    float noise = 0;
    for (unsigned int x = 0; x < image1.width(); x++) {
        for (unsigned int y = 0; y < image1.height(); y++) {
            if(image1(x,y) > signal) signal = image1(x,y);
            noise += pow((image1(x,y) - image2(x,y)), 2);
        }
    }
    return 10*log10((image1.width()*image1.height()*pow(signal,2))/noise);
}

float maxDifference(CImg<unsigned char> &image1, CImg<unsigned char> &image2) {
    float m = 0;
    for (unsigned int x = 0; x < image1.width(); x++) {
        for (unsigned int y = 0; y < image1.height(); y++) {
            if (std::abs(image1(x, y) - image2(x, y)) > m) m = std::abs(image1(x, y) - image2(x, y));
        }
    }
    return m;
}
