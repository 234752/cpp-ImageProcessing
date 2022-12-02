#include "../lib/CImg.h"

using namespace cimg_library;

void dilation(CImg<unsigned char> &image) {

    short mask[3][3] =
            {{0, 1, 0},
             {1, 1, 1},
             {0, 1, 0}};
    CImg<unsigned char> newImage = image;

    for (int x = 1; x < image.width()-1; x++)
    {
        for (int y = 1; y < image.height()-1; y++)
        {
            if(image(x, y, 0) == 0)
            {
                int topLeftCornerX = x-1;
                int topLeftCornerY = y-1;
                for(int xi = 0; xi<3; xi++)
                {
                    for(int yi = 0; yi<3; yi++)
                    {
                        newImage(topLeftCornerX + xi, topLeftCornerY + yi, 0) =  newImage(topLeftCornerX + xi, topLeftCornerY + yi, 0) || mask[xi][yi];
                        newImage(topLeftCornerX + xi, topLeftCornerY + yi, 1) =  newImage(topLeftCornerX + xi, topLeftCornerY + yi, 1) || mask[xi][yi];
                        newImage(topLeftCornerX + xi, topLeftCornerY + yi, 2) =  newImage(topLeftCornerX + xi, topLeftCornerY + yi, 2) || mask[xi][yi];
                    }
                }
            }
        }
    }

    image = newImage;
}