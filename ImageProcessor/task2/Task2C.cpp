
using namespace cimg_library;

unsigned int histogramValues[256];

void fillHistogramValues(CImg<unsigned char> &image, int channel)
{
    for (unsigned int &value : histogramValues) {
        value = 0;
    }
    for (unsigned int x = 0; x < image.width(); x++) {
        for (unsigned int y = 0; y < image.height(); y++) {
            histogramValues[image(x, y, channel)]++;
        }
    }
}

double mean(CImg<unsigned char> &image, int channel)
{
    fillHistogramValues(image, channel);
    double mean = 0;
    for(int i = 0; i < 256; i++)
    {
        mean += histogramValues[i]*i;
    }
    mean /= (image.width() * image.height());
    return mean;
}

double variance(CImg<unsigned char> &image, int channel)
{
    double b = mean(image, channel);
    double variance = 0;
    for(int i = 0; i < 256; i++)
    {
        variance += pow(i - b, 2)*histogramValues[i];
    }
    variance /= (image.width() * image.height());
    return variance;
}