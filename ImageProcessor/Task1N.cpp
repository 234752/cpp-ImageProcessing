#include "CImg.h"
#include <vector>
#include <algorithm>

using namespace cimg_library;

void adaptiveMedianFilter(CImg<unsigned char> &image)
{
    for (int x = 1; x < image.width()-1; x++)
    {
        for (int y = 1; y < image.height()-1; y++)
        {
            int Smax = image.width() - x;
            if(image.height() - y < Smax) Smax = image.height() - y;
            if(x < Smax) Smax = x;
            if(y < Smax) Smax = y;
            int Sxy = 1;

            int result = 0;
            while(true)
            {
                int zmin = 255;
                int zmax = 0;
                int zmed;
                int zxy = image(x, y, 0);

                std::vector<int> values;

                for(int xi = x-Sxy; xi < x+Sxy; xi++)
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

                //A starts here
                int A1 = zmed-zmin; //A1 - values
                int A2 = zmed-zmax;
                if(A1>0 && A2<0) //A2 true - go to B
                {
                    //B starts here
                    int B1 = zxy-zmin; //B1 - values
                    int B2 = zxy-zmax;
                    if(B1>0 && B2<0)
                    {
                        result = zxy; //B2 - output
                        break;
                    }
                    else
                    {
                        result = zmed; //B3 - output
                        break;
                    }
                }
                else //A2 false - go to A3
                {
                    Sxy++; //A3 increase window size
                    if(Sxy <= Smax) //A4 true - do nothing and repeat loop
                    {

                    }
                    else
                    {
                        result = zxy; //A5 - output
                        break;
                    }
                }

            }

            int Smax1 = image.width() - x;
            if(image.height() - y < Smax1) Smax1 = image.height() - y;
            if(x < Smax1) Smax1 = x;
            if(y < Smax1) Smax1 = y;
            int Sxy1 = 1;

            int result1 = 0;
            while(true)
            {
                int zmin = 255;
                int zmax = 0;
                int zmed;
                int zxy = image(x, y, 0);

                std::vector<int> values;

                for(int xi = x-Sxy1; xi < x+Sxy1; xi++)
                {
                    for(int yi = y-Sxy1; yi < y+Sxy1; yi++)
                    {
                        values.push_back(image(xi, yi, 1));
                    }
                }
                std::sort(values.begin(), values.end());
                zmin = values.front();
                zmax = values.back();
                zmed = values[values.size()/2];

                //A starts here
                int A1 = zmed-zmin; //A1 - values
                int A2 = zmed-zmax;
                if(A1>0 && A2<0) //A2 true - go to B
                {
                    //B starts here
                    int B1 = zxy-zmin; //B1 - values
                    int B2 = zxy-zmax;
                    if(B1>0 && B2<0)
                    {
                        result1 = zxy; //B2 - output
                        break;
                    }
                    else
                    {
                        result1 = zmed; //B3 - output
                        break;
                    }
                }
                else //A2 false - go to A3
                {
                    Sxy1++; //A3 increase window size
                    if(Sxy1 <= Smax1) //A4 true - do nothing and repeat loop
                    {

                    }
                    else
                    {
                        result1 = zxy; //A5 - output
                        break;
                    }
                }
            }


            int Smax2 = image.width() - x;
            if(image.height() - y < Smax2) Smax2 = image.height() - y;
            if(x < Smax2) Smax2 = x;
            if(y < Smax2) Smax2 = y;
            int Sxy2 = 1;

            int result2 = 0;
            while(true)
            {
                int zmin = 255;
                int zmax = 0;
                int zmed;
                int zxy = image(x, y, 0);

                std::vector<int> values;

                for(int xi = x-Sxy2; xi < x+Sxy2; xi++)
                {
                    for(int yi = y-Sxy2; yi < y+Sxy2; yi++)
                    {
                        values.push_back(image(xi, yi, 2));
                    }
                }
                std::sort(values.begin(), values.end());
                zmin = values.front();
                zmax = values.back();
                zmed = values[values.size()/2];

                //A starts here
                int A1 = zmed-zmin; //A1 - values
                int A2 = zmed-zmax;
                if(A1>0 && A2<0) //A2 true - go to B
                {
                    //B starts here
                    int B1 = zxy-zmin; //B1 - values
                    int B2 = zxy-zmax;
                    if(B1>0 && B2<0)
                    {
                        result2 = zxy; //B2 - output
                        break;
                    }
                    else
                    {
                        result2 = zmed; //B3 - output
                        break;
                    }
                }
                else //A2 false - go to A3
                {
                    Sxy2++; //A3 increase window size
                    if(Sxy2 <= Smax2) //A4 true - do nothing and repeat loop
                    {

                    }
                    else
                    {
                        result2 = zxy; //A5 - output
                        break;
                    }
                }
            }
            image(x, y, 0) = result;
            image(x, y, 1) = result1;
            image(x, y, 2) = result2;

        }
    }
}

