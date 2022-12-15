#include "../lib/CImg.h"

using namespace cimg_library;

struct XY
{
    int x;
    int y;
    XY(int _x, int _y)
    {
        x = _x;
        y = _y;
    }
};

void regionMerge(CImg<unsigned char> &image, int seedX, int seedY, int allowedDiff)
{
    CImg<unsigned char> region(image.width(), image.height(), 1, 3, 0);
    region(seedX, seedY, 0) = 255;

    std::vector<XY> border = std::vector<XY>();

    border.push_back(XY(seedX, seedY));

    while(true)
    {
        bool anythingChanged = false;
        std::vector<XY> newBorder = std::vector<XY>();

        for (int i = 0; i < border.size(); i++)
        {
            int X = border[i].x;
            int Y = border[i].y;
            if(X>0 && X<image.width()-1 && Y>0 && Y<image.height()-1)
            {
                if (region(X + 1, Y, 0) == 0 && abs(image(X + 1, Y, 0) - image(X, Y, 0)) < allowedDiff)
                {
                    newBorder.push_back(XY(X + 1, Y));
                    region(X + 1, Y, 0) = 255;
                    anythingChanged = true;
                }

                if (region(X - 1, Y, 0) == 0 && abs(image(X - 1, Y, 0) - image(X, Y, 0)) < allowedDiff)
                {
                    newBorder.push_back(XY(X - 1, Y));
                    region(X - 1, Y, 0) = 255;
                    anythingChanged = true;
                }

                if (region(X, Y + 1, 0) == 0 && abs(image(X, Y + 1, 0) - image(X, Y, 0)) < allowedDiff)
                {
                    newBorder.push_back(XY(X, Y + 1));
                    region(X, Y + 1, 0) = 255;
                    anythingChanged = true;
                }

                if (region(X, Y - 1, 0) == 0 && abs(image(X, Y - 1, 0) - image(X, Y, 0)) < allowedDiff)
                {
                    newBorder.push_back(XY(X, Y - 1));
                    region(X, Y - 1, 0) = 255;
                    anythingChanged = true;
                }
            }
        }
        border = newBorder;
        if(!anythingChanged) break;
    }
    image = region;
}