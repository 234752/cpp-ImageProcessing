#include "../lib/CImg.h"

using namespace cimg_library;



bool checkPixelsAround(CImg<unsigned char> image, CImg<unsigned char> region, int x, int y, int allowedDiff)
{
    if(region(x+1, y, 0) != 0 && abs(image(x+1, y, 0) - image(x,y, 0)) < allowedDiff) return true;
    if(region(x-1, y, 0) != 0 && abs(image(x-1, y, 0) - image(x,y, 0)) < allowedDiff) return true;
    if(region(x, y+1, 0) != 0 && abs(image(x, y+1, 0) - image(x,y, 0)) < allowedDiff) return true;
    if(region(x, y-1, 0) != 0 && abs(image(x, y-1, 0) - image(x,y, 0)) < allowedDiff) return true;
    return false;
}

void regionMerge(CImg<unsigned char> &image)
{

    CImg<unsigned char> region(image.width(), image.height(), 1, 3, 0);
    int seedX = 470;
    int seedY = 180;
    int allowedDiff = 10;
    region(seedX, seedY, 0) = 255;



    for (int x = 1; x < image.width()-1; x++)
    {
        for (int y = 1; y < image.height()-1; y++)
        {
            if(region(x,y,0) == 0 && checkPixelsAround(image, region, x, y, allowedDiff))
            {
                region(x,y,0) = 255;
            }
        }
    }

    for (int x = image.width()-1; x > 1; x--)
    {
        for (int y = 1; y < image.height()-1; y++)
        {
            if(region(x,y,0) == 0 && checkPixelsAround(image, region, x, y, allowedDiff))
            {
                region(x,y,0) = 255;
            }
        }
    }

    for (int x = 1; x < image.width()-1; x++)
    {
        for (int y = image.height()-1; y > 1; y--)
        {
            if(region(x,y,0) == 0 && checkPixelsAround(image, region, x, y, allowedDiff))
            {
                region(x,y,0) = 255;
            }
        }
    }

    for (int x = image.width()-1; x > 1; x--)
    {
        for (int y = image.height()-1; y > 1; y--)
        {
            if(region(x,y,0) == 0 && checkPixelsAround(image, region, x, y, allowedDiff))
            {
                region(x,y,0) = 255;
            }
        }
    }
    image = region;
}