#include "CImg.h"
#include <vector>
#include <algorithm>

using namespace cimg_library;

int stageB(int zxy, int zmed, int zmin, int zmax)
{
    int B1 = zxy - zmin;
    int B2 = zxy - zmax;

    if(B1 > 0 && B2 < 0) return zxy;
    else
    {
        return zmed;
    }
}

int stageA(int zxy, int zmed, int zmin, int zmax, int Sxy, int Smax)
{
    int A1 = zmed - zmin;
    int A2 = zmed - zmax;

    if(A1 > 0 && A2 < 0) return stageB(zxy, zmed, zmin, zmax);
    else
    {
        Sxy++;
        if(Sxy <= Smax) return 1000;
        else
        {
            return zxy;
        }
    }
}


void adaptiveMedianFilter(CImg<unsigned char> &image)
{
    CImg<unsigned char> filteredImage = image;
    for (int x = 1; x < image.width()-1; x++)
    {
        for (int y = 1; y < image.height()-1; y++)
        {
            int Smax = image.width() - x;
            if(image.height() - y < Smax) Smax = image.height() - y;
            if(x < Smax) Smax = x;
            if(y < Smax) Smax = y;
            int Sxy = 1;

            int result = 1000;
            while(true)
            {
                int zmin = 255;
                int zmax = 0;
                int zmed;
                int zxy = image(x, y, 0);

                std::vector<int> values;

                for (int xi = x - Sxy; xi <= x + Sxy; xi++)
                {
                    for (int yi = y - Sxy; yi <= y + Sxy; yi++)
                    {
                        if(xi != x || yi != y) values.push_back(image(xi, yi, 0));
                    }
                }
                std::sort(values.begin(), values.end());
                zmin = values.front();
                zmax = values.back();
                if(values.size()%2 == 0)
                {
                    zmed = 0.5 * (values[values.size() / 2 - 1] + values[values.size() / 2]);
                }
                else
                {
                    zmed = values[values.size() / 2];
                }
                result = stageA(zxy, zmed, zmin, zmax, Sxy, Smax);
                if(result == 1000) Sxy++;
                else break;
            }
            filteredImage(x, y, 0) = result;
            filteredImage(x, y, 1) = result;
            filteredImage(x, y, 2) = result;
        }
    }
    image = filteredImage;
}


