#include <iostream>
#include "lib/CImg.h"
#include "lib/popl.hpp"
#include "task1/Task1B.cpp"
#include "task1/Task1G.cpp"
#include "task1/Task1E.cpp"
#include "task1/Task1N.cpp"

int main(int argc, char *argv[]) {

    cimg_library::CImg<unsigned char> image("..\\..\\img\\color_noise_24bit\\uniform_dist\\lena_noise.bmp");
    adaptiveMedianFilter(image);
    image.save_bmp("..\\..\\img\\color_noise_24bit\\uniform_dist\\out.bmp");

    cimg_library::CImg<unsigned char> noise_image("..\\..\\img\\color_noise_24bit\\uniform_dist\\lena_noise.bmp");
    cimg_library::CImg<unsigned char> improved_image("..\\..\\img\\color_noise_24bit\\uniform_dist\\out.bmp");
    cimg_library::CImg<unsigned char> original_image("..\\..\\img\\color_noise_24bit\\uniform_dist\\lena_original.bmp");

    std::cout << "\nError before noise removal: " << peakSignalToNoiseRatio(original_image, noise_image);
    std::cout << "\nError after noise removal: " << peakSignalToNoiseRatio(original_image, improved_image);
    return 0;
}