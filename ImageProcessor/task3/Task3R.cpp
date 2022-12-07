#include "../lib/CImg.h"

using namespace cimg_library;

bool checkPixelsAround(CImg<unsigned char> image, int x, int y)
{
    for (int xi = -1; xi < 2 && xi < image.width(); xi++)
    {
        for (int yi = -1; yi < 2 && yi < image.width(); yi++)
        {
            if(xi != 0 || yi != 0)
            {
                if(image(x+xi, y+yi, 0) > image(x, y, 0) - 1 && image(x+xi, y+yi, 0) < image(x, y, 0) + 1)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

bool checkRegionAround(CImg<unsigned char> regions, int x, int y)
{
    for (int xi = -1; xi < 2; xi++)
    {
        for (int yi = -1; yi < 2; yi++)
        {
            if((xi != 0 || yi != 0) && regions(x+xi, y+yi, 1) != 0)
            {
                if(regions(x+xi, y+yi, 1) == 255)
                {
                    return true;
                }
            }
        }
    }
    return false;
}


void regionMerge(CImg<unsigned char> &image)
{

    CImg<unsigned char> regions(image.width(), image.height(), 1, 3, 0);
    int seedX = 100;
    int seedY = 100;
    regions(seedX, seedY, 1) = 255;



    for (int x = 1; x < image.width()-1; x++)
    {
        for (int y = 1; y < image.height()-1; y++)
        {
            if(regions(x,y,1) == 0 && checkRegionAround(regions, x, y) && checkPixelsAround(image, x, y))
            {
                regions(x,y,1) = 255;
            }
        }
    }

    for (int x = image.width()-1; x > 1; x--)
    {
        for (int y = 1; y < image.height()-1; y++)
        {
            if(regions(x,y,1) == 0 && checkRegionAround(regions, x, y) && checkPixelsAround(image, x, y))
            {
                regions(x,y,1) = 255;
            }
        }
    }

    for (int x = 1; x < image.width()-1; x++)
    {
        for (int y = image.height()-1; y > 1; y--)
        {
            if(regions(x,y,1) == 0 && checkRegionAround(regions, x, y) && checkPixelsAround(image, x, y))
            {
                regions(x,y,1) = 255;
            }
        }
    }

    for (int x = image.width()-1; x > 1; x--)
    {
        for (int y = image.height()-1; y > 1; y--)
        {
            if(regions(x,y,1) == 0 && checkRegionAround(regions, x, y) && checkPixelsAround(image, x, y))
            {
                regions(x,y,1) = 255;
            }
        }
    }
    image = regions;
}