#include "CImg.h"
#include "Task1B.cpp"
#include "Task1G.cpp"
#include "Task1E.cpp"
#include <iostream>

int main() {
    cimg_library::CImg<unsigned char> image("..\\..\\img\\color_24bit\\lenac_small.bmp");
    cimg_library::CImg<unsigned char> image_low_noise("..\\..\\img\\color_noise_24bit\\impulse\\lenac_impulse1_small.bmp");
    cimg_library::CImg<unsigned char> image_high_noise("..\\..\\img\\color_noise_24bit\\impulse\\lenac_impulse3_small.bmp");
    //cimg_library::CImg<unsigned char> image("..\\..\\img\\gray_scale_8bit\\lena_small.bmp");

    //contrast(image, 180);

    std::cout << "\nLow noise: " << peakSignalToNoiseRatio(image, image_low_noise);
    std::cout << "\nHigh noise: " << peakSignalToNoiseRatio(image, image_high_noise);
    //image.save_bmp("..\\..\\img\\color_24bit\\out.bmp");
    return 0;
}