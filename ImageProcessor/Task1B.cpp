#include "CImg.h"

using namespace cimg_library;

void brightnessModification(CImg<unsigned char> &image, int brightness)
{
    if(brightness >= 0)
    {
        for (int x = 0; x < image.width(); x++)
        {
            for (int y = 0; y < image.height(); y++)
            {
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
        for (int x = 0; x < image.width(); x++)
        {
            for (int y = 0; y < image.height(); y++)
            {
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

void contrast(CImg<unsigned char> &image, int contrast)
{
    for (int x = 0; x < image.width(); x++) {
        for (int y = 0; y < image.height(); y++) {
            float factor = (259 * (contrast + 255)) / (255 * (259 - contrast));
            float valR = factor * (image(x, y, 0) - 128) + 128;
            float valG = factor * (image(x, y, 1) - 128) + 128;
            float valB = factor * (image(x, y, 2) - 128) + 128;
            if(valR <= 0) image(x, y,0) = 0;
            else if (valR >= 255) image(x, y,0) = 255;
            else image(x, y,0) = valR;

            if(valG <= 0) image(x, y,1) = 0;
            else if (valG >= 255) image(x, y,1) = 255;
            else image(x, y,1) = valG;

            if(valB <= 0) image(x, y,2) = 0;
            else if (valB >= 255) image(x, y,2) = 255;
            else image(x, y,2) = valB;
        }
    }
}

void negative(CImg<unsigned char> &image)
{
    for (int x = 0; x < image.width(); x++)
    {
        for (int y = 0; y < image.height(); y++)
        {
            image(x, y, 0) = 255 - image(x, y, 0);
            image(x, y, 1) = 255 - image(x, y, 1);
            image(x, y, 2) = 255 - image(x, y, 2);
        }
    }
}