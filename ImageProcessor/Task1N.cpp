#include "CImg.h"
#include <vector>

using namespace cimg_library;

int stageB(int zxy, int zmed, int zmin, int zmax)
{
    int B1 = zxy - zmin;
    int B2 = zxy - zmax;

    if(B1 > 0 && B2 < 0) return zxy;
    else return zmed;
}

int stageA(int zxy, int zmed, int zmin, int zmax, int Sxy, int Smax)
{
    int A1 = zmed - zmin;
    int A2 = zmed - zmax;

    if(A1 > 0 && A2 < 0) return stageB(zxy, zmed, zmin, zmax);
    else
    {
        if(Sxy < Smax) return 2137;
        else return zxy;
    }
}

int filterSinglePixel(CImg<unsigned char> image, int x, int y, int channel)
{
    int Smax = image.width() - x;
    if(image.height() - y < Smax) Smax = image.height() - y;
    if(x < Smax) Smax = x;
    if(y < Smax) Smax = y;
    int Sxy = 1;

    int result = 2137;
    while(result == 2137)
    {
        std::vector<int> values;
        for (int xi = x - Sxy; xi <= x + Sxy; xi++)
        {
            for (int yi = y - Sxy; yi <= y + Sxy; yi++)
            {
                //if(xi != x || yi != y)
                    values.push_back(image(xi, yi, channel));
            }
        }

        std::sort(values.begin(), values.end());
        int zmin = values.front();
        int zmax = values.back();
        int zxy = image(x, y, 0);
        int zmed;
        if(values.size()%2 == 0)
        {
            zmed = 0.5 * (values[values.size() / 2 - 1] + values[values.size() / 2]);
        }
        else
        {
            zmed = values[values.size() / 2];
        }

        result = stageA(zxy, zmed, zmin, zmax, Sxy, Smax);
        Sxy++;
    }
    return result;
}

int filterSinglePixelMin(CImg<unsigned char> image, int x, int y, int channel)
{
    int Sxy = 1;

    std::vector<int> values;
    for (int xi = x - Sxy; xi <= x + Sxy; xi++)
    {
        for (int yi = y - Sxy; yi <= y + Sxy; yi++)
        {
            //if(xi != x || yi != y)
            values.push_back(image(xi, yi));
        }
    }

    std::sort(values.begin(), values.end());
    int result = values[0];
    return result;
}

int filterSinglePixelMax(CImg<unsigned char> image, int x, int y, int channel)
{
    int Sxy = 1;

    std::vector<int> values;
    for (int xi = x - Sxy; xi <= x + Sxy; xi++)
    {
        for (int yi = y - Sxy; yi <= y + Sxy; yi++)
        {
            //if(xi != x || yi != y)
            values.push_back(image(xi, yi));
        }
    }

    std::sort(values.begin(), values.end());
    int result = values[8];
    return result;
}

void adaptiveMedianFilter(CImg<unsigned char> &image)
{
    CImg<unsigned char> filteredImage = image;
    for (int x = 1; x < image.width()-1; x++)
    {
        for (int y = 1; y < image.height()-1; y++)
        {
            filteredImage(x, y, 0) = filterSinglePixel(image, x, y, 0);
            filteredImage(x, y, 1) = filterSinglePixel(image, x, y, 1);
            filteredImage(x, y, 2) = filterSinglePixel(image, x, y, 2);
        }
    }
    image = filteredImage;
}




