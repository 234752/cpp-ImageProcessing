#include "../lib/CImg.h"
#include <complex>

using namespace cimg_library;


const std::complex<double> I(0, 1);

std::vector<std::complex<double>> linearDFT(std::vector<std::complex<double>> sequence) //SLOW
{

    std::vector<std::complex<double>> outputSequence = std::vector<std::complex<double>>();
    int N = sequence.size();

    for (int k = 0; k < N; k++)
    {
        outputSequence.push_back(std::complex<double>(0, 0));
        for (int n = 0; n < N; n++)
        {
            outputSequence[k] += sequence[n] * exp(-I * 2.0 * M_PI * (double)k * (double)n / (double)N);
        }
    }
}

void DFT(CImg<unsigned char> &image)
{
    CImg<unsigned char> transformed = image;

    int M = image.width();
    int N = image.height();
    for (int u = 0; u < M; u++)
    {
        for (int v = 0; v < N; v++)
        {
            int result = 0;
            for (int x = 0; x < M; x++)
            {
                for (int y = 0; y < N; y++)
                {
                    result += ((std::complex<double>)image(x, y, 0) * exp(-I * 2.0 * M_PI * (double)u * (double)x / (double)M) * exp(-I * 2.0 * M_PI * (double)v * (double)y / (double)N)).real();
                }
            }
            transformed(u, v, 0) = result;
            transformed(u, v, 1) = result;
            transformed(u, v, 2) = result;
        }
    }
    image = transformed;
}
void FFT(CImg<unsigned char> &image) {}
void IFFT(CImg<unsigned char> &image) {}