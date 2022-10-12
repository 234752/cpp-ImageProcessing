#include "CImg.h"
#include "Task1B.cpp"

int main() {
    cimg_library::CImg<unsigned char> image("..\\..\\img\\color_24bit\\lenac_small.bmp");

    negative(image);

    image.save_bmp("..\\..\\img\\color_24bit\\out.bmp");
    return 0;
}