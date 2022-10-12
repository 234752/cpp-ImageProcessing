#include "CImg.h"
#include "Task1B.cpp"
#include "Task1G.cpp"

int main() {
    cimg_library::CImg<unsigned char> image("..\\..\\img\\color_24bit\\lenac_small.bmp");
    //cimg_library::CImg<unsigned char> image("..\\..\\img\\gray_scale_8bit\\lena_small.bmp");

    scale(image, 0.5);

    image.save_bmp("..\\..\\img\\color_24bit\\out.bmp");
    return 0;
}