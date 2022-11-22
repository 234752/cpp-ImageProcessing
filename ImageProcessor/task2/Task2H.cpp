#include <numeric>

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
            histogramImage(2 * x, 255 - y, channel) = 255;
            histogramImage(2 * x + 1, 255 - y, channel) = 255;
        }
    }
    histogramImage.save("histogram.bmp");
}

//histogram performed on an image
// I think this is correct --hhyper
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