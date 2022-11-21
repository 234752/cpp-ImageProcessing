#include <numeric>
#include "../lib/CImg.h"

using namespace cimg_library;

void histogram(CImg<unsigned char> &image, int channel)
{
    CImg<unsigned char> histogramImage(512, 256, 1, 3, 0);
    unsigned int values[256];
    for (unsigned int &value : values) {
        value = 0;
    }
    for (unsigned int x = 0; x < image.width(); x++) {
        for (unsigned int y = 0; y < image.height(); y++) {
            values[image(x, y, channel)]++;
        }
    }
    unsigned int maxValue = 0;
    for (unsigned int &value : values) {
        if (value > maxValue) {
            maxValue = value;
        }
    }
    for (unsigned int &value : values) {
        value = (255 * value) / (maxValue);
    }
    for (unsigned short x = 0; x < 256; x++)
    {
        for (unsigned int y = 0; y < values[x]; y++)
        {
            histogramImage(2 * x, 255 - y, 0) = 255;
            histogramImage(2 * x + 1, 255 - y, 0) = 255;
            histogramImage(2 * x, 255 - y, 1) = 255;
            histogramImage(2 * x + 1, 255 - y, 1) = 255;
            histogramImage(2 * x, 255 - y, 2) = 255;
            histogramImage(2 * x + 1, 255 - y, 2) = 255;
        }
    }
    histogramImage.save("histogram.bmp");
}

//performed on a histogram
void hyperbolicPDF(CImg<unsigned char> &image, int channel, int min, int max)
{
    CImg<unsigned char> histogramImage(512, 256, 1, 3, 0);
    unsigned int values[256];
    for (unsigned int &value : values) {
        value = 0;
    }
    for (unsigned int x = 0; x < image.width(); x++) {
        for (unsigned int y = 0; y < image.height(); y++) {
            values[image(x, y, channel)]++;
        }
    }
    unsigned int newValues[256];
    if(min > 0) {
        for (unsigned int i = 0; i < 256; i++) {
            unsigned int sum = std::accumulate(values, values + i, 0);
            newValues[i] = min * (pow((float)max / (float)min, ((float) sum / (float) (image.height() * image.width()))));
        }
    } else {
        for (unsigned int i = 0; i < 256; i++) {
            unsigned int sum = std::accumulate(values, values + i, 0);
            newValues[i] = 0.001 * (pow((float)max / 0.001, ((float) sum / (float) (image.height() * image.width()))));
        }
    }
    for (unsigned short x = 0; x < 256; x++)
    {
        for (unsigned int y = 0; y < newValues[x]; y++)
        {
            histogramImage(2 * x, 255 - y, 0) = 255;
            histogramImage(2 * x + 1, 255 - y, 0) = 255;
            histogramImage(2 * x, 255 - y, 1) = 255;
            histogramImage(2 * x + 1, 255 - y, 1) = 255;
            histogramImage(2 * x, 255 - y, 2) = 255;
            histogramImage(2 * x + 1, 255 - y, 2) = 255;
        }
    }
    histogramImage.save("histogram.bmp");
}

void hhyperPDF(CImg<unsigned char> &image, int channel, int min, int max)
{
    CImg<unsigned char> newImage = image;
    unsigned int values[256];
    for (unsigned int &value : values) {
        value = 0;
    }
    for (unsigned int x = 0; x < image.width(); x++) {
        for (unsigned int y = 0; y < image.height(); y++) {
            values[image(x, y, channel)]++;
        }
    }
    unsigned int newValues[256];
    if(min > 0) {
        for (unsigned int i = 0; i < 256; i++) {
            unsigned int sum = std::accumulate(values, values + i, 0);
            newValues[i] = min * (pow((float)max / (float)min, ((float) sum / (float) (image.height() * image.width()))));
        }
    } else {
        for (unsigned int i = 0; i < 256; i++) {
            unsigned int sum = std::accumulate(values, values + i, 0);
            newValues[i] = 0.001 * (pow((float)max / 0.001, ((float) sum / (float) (image.height() * image.width()))));
        }
    }
    for (unsigned short x = 0; x < newImage.width(); x++)
    {
        for (unsigned int y = 0; y < newImage.height(); y++)
        {
            newImage(x, y, 0) = newValues[image(x, y, channel)];
            newImage(x, y, 1) = newValues[image(x, y, channel)];
            newImage(x, y, 2) = newValues[image(x, y, channel)];
        }
    }
    newImage.save("out.bmp");
}

//histogram performed on an image
void hyperPDF(CImg<unsigned char> &image, int channel, int min, int max)
{
    CImg<unsigned char> newImage = image;
    unsigned int values[256];
    float minF;
    if (min == 0) {
        minF = 0.001;
    } else {
        minF = (float)min;
    }
    unsigned int size = image.width()*image.height();

    for (unsigned int &value : values) {
        value = 0;
    }
    for (unsigned int x = 0; x < image.width(); x++) {
        for (unsigned int y = 0; y < image.height(); y++) {
            values[image(x, y, channel)]++;
        }
    }

    for (unsigned short x = 0; x < newImage.width(); x++)
    {
        for (unsigned int y = 0; y < newImage.height(); y++)
        {
            unsigned int sum = std::accumulate(values, values + image(x, y, channel), 0);
            newImage(x, y, 0) = minF * (pow((float)max / minF, ((float) sum / (float) size)));
            newImage(x, y, 1) = minF * (pow((float)max / minF, ((float) sum / (float) size)));
            newImage(x, y, 2) = minF * (pow((float)max / minF, ((float) sum / (float) size)));
        }
    }
    newImage.save("out.bmp");
}