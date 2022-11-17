
using namespace cimg_library;

unsigned int* histogramValues(CImg<unsigned char> &image, int channel)
{
    CImg<unsigned char> histogramImage(512, 256, 1, 3, 0);
    static unsigned int values[256];
    for (unsigned int &value : values) {
        value = 0;
    }
    for (unsigned int x = 0; x < image.width(); x++) {
        for (unsigned int y = 0; y < image.height(); y++) {
            values[image(x, y, channel)]++;
        }
    }
    return values;
}

float mean(CImg<unsigned char> &image, int channel)
{
    unsigned int* values = histogramValues(image, channel);
    double mean = 0;
    for(int i = 0; i < 256; i++)
    {
        mean = mean + values[i]*i;
    }
    mean = mean / (image.width() * image.height());
    return mean;
}