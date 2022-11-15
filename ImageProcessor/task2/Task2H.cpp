#include "../lib/CImg.h"

using namespace cimg_library;

void histogram(CImg<unsigned char> &image, int channel)
{
    CImg<unsigned char> histogramImage(512, 512, 1, 3, 0);
    unsigned short values[256];
    for (unsigned int x = 0; x < image.width(); x++)
    {
        for (unsigned int y = 0; y < image.height(); y++)
        {
            values[image(x, y, channel)]++;
        }
    }
    for (unsigned short x = 0; x < 256; x++)
    {
        for (unsigned short y = 0; y < values[x] * 2; y++)
        {
            histogramImage(2 * x, y, 0) = 255;
            histogramImage(2 * x + 1, y, 0) = 255;
        }
    }
    histogramImage.save("histogram.bmp");
    std::cout << "hehe";
}

void hyperbolicPDF()
{
    throw std::exception();
}