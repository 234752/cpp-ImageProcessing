#include "CImg.h"
#include <vector>
#include <algorithm>

using namespace cimg_library;

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
            Smax--;
            int Sxy = 0;


            int result = 0;
            while(true)
            {
                int zmin = 255;
                int zmax = 0;
                int zmed;
                int zxy = image(x, y, 0);

                std::vector<int> values;

                for(int xi = x-Sxy; xi < xi+Sxy; xi++)
                {
                    for(int yi = y-Sxy; yi < y+Sxy; yi++)
                    {
                        values.push_back(image(xi, yi, 0));
                    }
                }
                std::sort(values.begin(), values.end());
                zmin = values.front();
                zmax = values.back();
                zmed = values[values.size()/2];

                //A
                int A1 = zmed-zmin;
                int A2 = zmed-zmax;
                if(A1>0 && A2<0) //B
                {
                    int B1 = zxy-zmin;
                    int B2 = zxy-zmax;
                    if(B1>0 && B2<0)
                    {
                        result = zxy;
                        break;
                    }
                    else
                    {
                        result = zmed;
                        break;
                    }
                }
                else
                {
                    Sxy++;
                    if(Sxy <= Smax)
                    {

                    }
                    else
                    {
                        result = zxy;
                        break;
                    }
                }

            }
            image(x, y, 0) = result;
            image(x, y, 1) = result;
            image(x, y, 2) = result;

        }
    }
    image = filteredImage;
}

