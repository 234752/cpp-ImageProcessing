#include "CImg.h"

using namespace cimg_library;

void horizontalFlip(CImg<unsigned char> &image)
{
    CImg<unsigned char> flippedImage = image;

    for (int x = 0; x < image.width(); x++)
    {
        for (int y = 0; y < image.height(); y++)
        {
            flippedImage(image.width() - x, y, 0) = image(x, y, 0);
            flippedImage(image.width() - x, y, 1) = image(x, y, 1);
            flippedImage(image.width() - x, y, 2) = image(x, y, 2);
        }
    }
    image = flippedImage;
}