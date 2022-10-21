#include "CImg.h"
#include <vector>

using namespace cimg_library;

struct Pixel
{
    int Red = 0;
    int Green = 0;
    int Blue = 0;
    Pixel(int r, int g, int b)
    {
        Red = r;
        Green = g;
        Blue = b;
    }
    friend bool operator<(const Pixel& p1, const Pixel& p2)
    {
        return p1.Red + p1.Green + p1.Blue < p2.Red + p2.Green + p2.Blue;
    }
};

int stageB(int zxy, int zmed, int zmin, int zmax)
{
    int B1 = zxy - zmin;
    int B2 = zxy - zmax;

    if(B1 > 0 && B2 < 0) return zxy;
    else return zmed;
}

int stageA(int zxy, int zmed, int zmin, int zmax, int Sxy, int Smax)
{
    int A1 = zmed - zmin;
    int A2 = zmed - zmax;

    if(A1 > 0 && A2 < 0) return stageB(zxy, zmed, zmin, zmax);
    else
    {
        if(Sxy < Smax) return 2137;
        else return zxy;
    }
}

int filterSinglePixelMedian(CImg<unsigned char> image, int x, int y, int channel)
{
    int Smax = image.width() - x;
    if(image.height() - y < Smax) Smax = image.height() - y;
    if(x < Smax) Smax = x;
    if(y < Smax) Smax = y;
    int Sxy = 1;

    int result = 2137;
    while(result == 2137)
    {
        std::vector<int> values;
        for (int xi = x - Sxy; xi <= x + Sxy; xi++)
        {
            for (int yi = y - Sxy; yi <= y + Sxy; yi++)
            {
                values.push_back(image(xi, yi, channel));
            }
        }

        std::sort(values.begin(), values.end());
        int zmin = values.front();
        int zmax = values.back();
        int zxy = image(x, y, channel);
        int zmed;
        if(values.size()%2 == 0)
        {
            zmed = 0.5 * (values[values.size() / 2 - 1] + values[values.size() / 2]);
        }
        else
        {
            zmed = values[values.size() / 2];
        }

        result = stageA(zxy, zmed, zmin, zmax, Sxy, Smax);
        Sxy++;
    }
    return result;
}

Pixel filterSinglePixelMin(CImg<unsigned char> image, int x, int y)
{
    int Sxy = 1;

    std::vector<Pixel> pixels;
    for (int xi = x - Sxy; xi <= x + Sxy; xi++)
    {
        for (int yi = y - Sxy; yi <= y + Sxy; yi++)
        {
            pixels.push_back(Pixel(image(xi, yi, 0), image(xi, yi, 1), image(xi, yi, 2)));
        }
    }

    std::sort(pixels.begin(), pixels.end());
    Pixel result = pixels[0];
    return result;
}

Pixel filterSinglePixelMax(CImg<unsigned char> image, int x, int y)
{
    int Sxy = 1;

    std::vector<Pixel> pixels;
    for (int xi = x - Sxy; xi <= x + Sxy; xi++)
    {
        for (int yi = y - Sxy; yi <= y + Sxy; yi++)
        {
            pixels.push_back(Pixel(image(xi, yi, 0), image(xi, yi, 1), image(xi, yi, 2)));
        }
    }

    std::sort(pixels.begin(), pixels.end());
    Pixel result = pixels[8];
    return result;
}

void minFilter(CImg<unsigned char> &image)
{
    CImg<unsigned char> filteredImage = image;
    for (int x = 1; x < image.width()-1; x=x+1)
    {
        for (int y = 1; y < image.height()-1; y=y+1)
        {
            Pixel result = filterSinglePixelMin(image, x, y);
            filteredImage(x, y, 0) = result.Red;
            filteredImage(x, y, 1) = result.Green;
            filteredImage(x, y, 2) = result.Blue;
        }
    }
    image = filteredImage;
}

void maxFilter(CImg<unsigned char> &image)
{
    CImg<unsigned char> filteredImage = image;
    for (int x = 1; x < image.width()-1; x=x+1)
    {
        for (int y = 1; y < image.height()-1; y=y+1)
        {
            Pixel result = filterSinglePixelMax(image, x, y);
            filteredImage(x, y, 0) = result.Red;
            filteredImage(x, y, 1) = result.Green;
            filteredImage(x, y, 2) = result.Blue;
        }
    }
    image = filteredImage;
}

void adaptiveMedianFilter(CImg<unsigned char> &image)
{
    CImg<unsigned char> filteredImage = image;
    for (int x = 1; x < image.width()-1; x=x+1)
    {
        for (int y = 1; y < image.height()-1; y=y+1)
        {
            filteredImage(x, y, 0) = filterSinglePixelMedian(image, x, y, 0);
            filteredImage(x, y, 1) = filterSinglePixelMedian(image, x, y, 1);
            filteredImage(x, y, 2) = filterSinglePixelMedian(image, x, y, 2);
        }
    }
    image = filteredImage;
}
