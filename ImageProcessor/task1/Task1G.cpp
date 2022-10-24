#include "../lib/CImg.h"

using namespace cimg_library;

void horizontalFlip(CImg<unsigned char> &image)
{
    CImg<unsigned char> flippedImage = image;

    for (int x = 0; x < image.width(); x++)
    {
        for (int y = 0; y < image.height(); y++)
        {
            flippedImage(x, y, 0) = image(image.width() - x, y, 0);
            flippedImage(x, y, 1) = image(image.width() - x, y, 1);
            flippedImage(x, y, 2) = image(image.width() - x, y, 2);
        }
    }
    image = flippedImage;
}

void verticalFlip(CImg<unsigned char> &image)
{
    CImg<unsigned char> flippedImage = image;

    for (int x = 0; x < image.width(); x++)
    {
        for (int y = 0; y < image.height(); y++)
        {
            flippedImage(x, y, 0) = image(x, image.height() - y, 0);
            flippedImage(x, y, 1) = image(x, image.height() - y, 1);
            flippedImage(x, y, 2) = image(x, image.height() - y, 2);
        }
    }
    image = flippedImage;
}

void diagonalFlip(CImg<unsigned char> &image)
{
    CImg<unsigned char> flippedImage = image;

    for (int x = 0; x < image.width(); x++)
    {
        for (int y = 0; y < image.height(); y++)
        {
            flippedImage(x, y, 0) = image(image.width() - x, image.height() - y, 0);
            flippedImage(x, y, 1) = image(image.width() - x, image.height() - y, 1);
            flippedImage(x, y, 2) = image(image.width() - x, image.height() - y, 2);
        }
    }
    image = flippedImage;
}

void scale(CImg<unsigned char> &image, double scale)
{
    CImg<unsigned char> scaledImage(image.width()*scale, image.height()*scale, 1, 3, 0);

    for (int x = 0; x < scaledImage.width(); x++)
    {
        for (int y = 0; y < scaledImage.height(); y++)
        {
            scaledImage(x, y, 0) = image(x/scale, y/scale, 0);
            scaledImage(x, y, 1) = image(x/scale, y/scale, 1);
            scaledImage(x, y, 2) = image(x/scale, y/scale, 2);
        }
    }
    image = scaledImage;
}