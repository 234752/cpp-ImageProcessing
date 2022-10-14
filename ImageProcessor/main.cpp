#include "CImg.h"
#include "Task1B.cpp"
#include "Task1G.cpp"
#include "Task1E.cpp"
#include <iostream>
#include "Task1N.cpp"

int main() {

    cimg_library::CImg<unsigned char> image("..\\..\\img\\color_noise_24bit\\uniform_dist\\lenac_uniform3_small.bmp");
    adaptiveMedianFilter(image);
    image.save_bmp("..\\..\\img\\color_noise_24bit\\uniform_dist\\out.bmp");

    cimg_library::CImg<unsigned char> noise_image("..\\..\\img\\color_noise_24bit\\uniform_dist\\lenac_uniform3_small.bmp");
    cimg_library::CImg<unsigned char> improved_image("..\\..\\img\\color_noise_24bit\\uniform_dist\\out.bmp");
    cimg_library::CImg<unsigned char> original_image("..\\..\\img\\color_24bit\\lenac_small.bmp");

    std::cout << "\nError before noise removal: " << meanSquareError(original_image, noise_image);
    std::cout << "\nError after noise removal: " << meanSquareError(original_image, improved_image);
    return 0;
}