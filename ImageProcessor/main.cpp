#include "CImg.h"
#include "Task1B.cpp"
#include "Task1G.cpp"
#include "Task1N.cpp"

int main() {
    //cimg_library::CImg<unsigned char> image("..\\..\\img\\color_24bit\\lenac_small.bmp");
    //cimg_library::CImg<unsigned char> image("..\\..\\img\\gray_scale_8bit\\lena_small.bmp");
    cimg_library::CImg<unsigned char> image("..\\..\\img\\color_noise_24bit\\uniform_dist\\lenac_uniform3_small.bmp");

    adaptiveMedianFilter(image);

    //image.save_bmp("..\\..\\img\\color_24bit\\out.bmp");
    image.save_bmp("..\\..\\img\\color_noise_24bit\\uniform_dist\\out.bmp");
    return 0;
}