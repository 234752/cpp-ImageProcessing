#include "../lib/CImg.h"

using namespace cimg_library;

void histogram(CImg<unsigned char> &image, int channel)
{
    CImg<unsigned char> histogramImage(512, 512, 1, 3, 0);
    unsigned int values[256];
    for (unsigned int &value : values) {
        value = 0;
    }
    for (unsigned int x = 0; x < image.width(); x++) {
        for (unsigned int y = 0; y < image.height(); y++) {
            values[image(x, y, channel)]++;
        }
    }
    for (unsigned int &value : values) {
        value = (10000 * value) / (image.width() * image.height());
    }
    for (unsigned short x = 0; x < 256; x++)
    {
        //std::cout << "x = " << x << ", v(x) = " << values[x] << "\n";
        for (unsigned int y = 0; y < values[x]; y++)
        {
            histogramImage(2 * x, 511 - y, 0) = 255;
            histogramImage(2 * x + 1, 511 - y, 0) = 255;
            histogramImage(2 * x, 511 - y, 1) = 255;
            histogramImage(2 * x + 1, 511 - y, 1) = 255;
            histogramImage(2 * x, 511 - y, 2) = 255;
            histogramImage(2 * x + 1, 511 - y, 2) = 255;
        }
    }
    histogramImage.save("histogram.bmp");
}

void hyperbolicPDF()
{
    throw std::exception();
}