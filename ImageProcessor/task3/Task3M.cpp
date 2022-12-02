#include "../lib/CImg.h"

using namespace cimg_library;

short mask[3][3] =
        {{0, 1, 0},
         {1, 1, 1},
         {0, 1, 0}};

int findMaxValueInMask(CImg<unsigned char> &image, int x, int y)
{
    int max =0;
    for(int maskX = -1; maskX<2; maskX++)
    {
        for(int maskY = -1; maskY<2; maskY++)
        {
            if(mask[maskX+1][maskY+1] == 1 && image(x + maskX , y + maskY , 0) > max)
            {
                max = image(x + maskX , y + maskY , 0);
            }
        }
    }
    return max;
}

int findMinValueInMask(CImg<unsigned char> &image, int x, int y)
{
    int min = 255;
    for(int maskX = -1; maskX<2; maskX++)
    {
        for(int maskY = -1; maskY<2; maskY++)
        {
            if(mask[maskX+1][maskY+1] == 1 && image(x + maskX , y + maskY , 0) < min)
            {
                min = image(x + maskX , y + maskY , 0);
            }
        }
    }
    return min;
}

void dilation(CImg<unsigned char> &image)
{
    CImg<unsigned char> newImage = image;

    for (int x = 1; x < image.width()-1; x++)
    {
        for (int y = 1; y < image.height()-1; y++)
        {
            int newValue = findMaxValueInMask(image, x, y);
            newImage(x, y, 0) = newValue;
            newImage(x, y, 1) = newValue;
            newImage(x, y, 2) = newValue;
        }
    }
    image = newImage;
}

void erosion(CImg<unsigned char> &image)
{
    CImg<unsigned char> newImage = image;

    for (int x = 1; x < image.width()-1; x++)
    {
        for (int y = 1; y < image.height()-1; y++)
        {
            int newValue = findMinValueInMask(image, x, y);
            newImage(x, y, 0) = newValue;
            newImage(x, y, 1) = newValue;
            newImage(x, y, 2) = newValue;
        }
    }
    image = newImage;
}

void opening(CImg<unsigned char> &image)
{
    erosion(image);
    dilation(image);
}

void closing(CImg<unsigned char> &image)
{
    dilation(image);
    erosion(image);
}