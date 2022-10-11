#include "CImg.h"

using namespace cimg_library;

void brightnessModification(CImg<unsigned char> &image, int brightness)
{
    if(brightness >= 0)
    {
        for (int x = 0; x < image.width(); x++) {
            for (int y = 0; y < image.height(); y++) {
                float valR = image(x, y, 0) + brightness;
                float valG = image(x, y, 1) + brightness;
                float valB = image(x, y, 2) + brightness;

                if(valR <= 255) image(x, y,0) = valR;
                else image(x, y,0) = 255;

                if(valG <= 255) image(x, y,1) = valG;
                else image(x, y,1) = 255;

                if(valB <= 255) image(x, y,2) = valB;
                else image(x, y,2) = 255;
            }
        }
    }
    else
    {
        for (int x = 0; x < image.width(); x++) {
            for (int y = 0; y < image.height(); y++) {
                float valR = image(x, y, 0) + brightness;
                float valG = image(x, y, 1) + brightness;
                float valB = image(x, y, 2) + brightness;

                if(valR >= 0) image(x, y,0) = valR;
                else image(x, y,0) = 0;

                if(valG >= 0) image(x, y,1) = valG;
                else image(x, y,1) = 0;

                if(valB >= 0) image(x, y,2) = valB;
                else image(x, y,2) = 0;
            }
        }
    }

}