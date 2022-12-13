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

bool checkPixelsAround(CImg<unsigned char> image, CImg<unsigned char> region, int x, int y, int allowedDiff)
{
    if(region(x+1, y, 0) != 0 && abs(image(x+1, y, 0) - image(x,y, 0)) < allowedDiff) return true;
    if(region(x-1, y, 0) != 0 && abs(image(x-1, y, 0) - image(x,y, 0)) < allowedDiff) return true;
    if(region(x, y+1, 0) != 0 && abs(image(x, y+1, 0) - image(x,y, 0)) < allowedDiff) return true;
    if(region(x, y-1, 0) != 0 && abs(image(x, y-1, 0) - image(x,y, 0)) < allowedDiff) return true;
    return false;
}

bool checkSinglePixel(CImg<unsigned char> &image, int x, int y)
{

}

void regionMerge(CImg<unsigned char> &image)
{

    CImg<unsigned char> region(image.width(), image.height(), 1, 3, 0);
    int seedX = 470;
    int seedY = 180;
    int allowedDiff = 200;
    region(seedX, seedY, 0) = 1;

    std::vector<XY> border = std::vector<XY>();


    border.push_back(XY(seedX, seedY));

    while(true) {

        bool anythingChanged = false;
        std::vector<XY> newBorder = std::vector<XY>();


        for (int i = 0; i < border.size(); i++) {


            if(border[i].x>0 && border[i].x<image.width() && border[i].y>0 && border[i].y<image.height()) {


                if (region(border[i].x + 1, border[i].y, 0) == 0 &&
                    abs(image(border[i].x + 1, border[i].y, 0) - image(border[i].x, border[i].y, 0)) < allowedDiff) {
                    newBorder.push_back(XY(border[i].x + 1, border[i].y));
                    region(border[i].x + 1, border[i].y, 0) = 255;
                    anythingChanged = true;
                }

                if (region(border[i].x - 1, border[i].y, 0) == 0 &&
                    abs(image(border[i].x - 1, border[i].y, 0) - image(border[i].x, border[i].y, 0)) < allowedDiff) {
                    newBorder.push_back(XY(border[i].x - 1, border[i].y));
                    region(border[i].x - 1, border[i].y, 0) = 255;
                    anythingChanged = true;
                }

                if (region(border[i].x, border[i].y + 1, 0) == 0 &&
                    abs(image(border[i].x, border[i].y + 1, 0) - image(border[i].x, border[i].y, 0)) < allowedDiff) {
                    newBorder.push_back(XY(border[i].x, border[i].y + 1));
                    region(border[i].x, border[i].y + 1, 0) = 255;
                    anythingChanged = true;
                }

                if (region(border[i].x, border[i].y - 1, 0) == 0 &&
                    abs(image(border[i].x, border[i].y - 1, 0) - image(border[i].x, border[i].y, 0)) < allowedDiff) {
                    newBorder.push_back(XY(border[i].x, border[i].y - 1));
                    region(border[i].x, border[i].y - 1, 0) = 255;
                    anythingChanged = true;
                }
            }
        }

        border = newBorder;
        if(!anythingChanged) break;


    }



//    for (int x = 1; x < image.width()-1; x++)
//    {
//        for (int y = 1; y < image.height()-1; y++)
//        {
//            if(region(x,y,0) == 0 && checkPixelsAround(image, region, x, y, allowedDiff))
//            {
//                region(x,y,0) = 255;
//            }
//        }
//    }
//
//    for (int x = image.width()-1; x > 1; x--)
//    {
//        for (int y = 1; y < image.height()-1; y++)
//        {
//            if(region(x,y,0) == 0 && checkPixelsAround(image, region, x, y, allowedDiff))
//            {
//                region(x,y,0) = 255;
//            }
//        }
//    }
//
//    for (int x = 1; x < image.width()-1; x++)
//    {
//        for (int y = image.height()-1; y > 1; y--)
//        {
//            if(region(x,y,0) == 0 && checkPixelsAround(image, region, x, y, allowedDiff))
//            {
//                region(x,y,0) = 255;
//            }
//        }
//    }
//
//    for (int x = image.width()-1; x > 1; x--)
//    {
//        for (int y = image.height()-1; y > 1; y--)
//        {
//            if(region(x,y,0) == 0 && checkPixelsAround(image, region, x, y, allowedDiff))
//            {
//                region(x,y,0) = 255;
//            }
//        }
//    }
    image = region;
}