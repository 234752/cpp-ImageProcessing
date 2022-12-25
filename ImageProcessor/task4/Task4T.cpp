#include "../lib/CImg.h"
#include <complex>

using namespace cimg_library;
using namespace std;


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
    CImg<unsigned char> transformed(image.width(), image.height(), 1, 3, 0);
    int N = image.width();

        vector<vector<complex<double>>> dft(N, vector<complex<double>>(N));

        for (int u = 0; u < N; u++) {
            for (int v = 0; v < N; v++) {

                complex<double> sum(0, 0);

                for (int i = 0; i < N; i++) {
                    for (int j = 0; j < N; j++) {

                        double cosine = cos(2 * M_PI * (u * i + v * j) / N);
                        double sine = sin(2 * M_PI * (u * i + v * j) / N);
                        complex<double> term(cosine, -sine);
                        sum += term * (double)image(i,j,0);
                    }
                }

                cout<<u<<" "<<v<<endl;
                dft[u][v] = sum;
            }
        }

    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            transformed(i,j,0) = dft[i][j].real();
            transformed(i,j,1) = dft[i][j].real();
            transformed(i,j,2) = dft[i][j].real();
        }
    }
    transformed.save("real_domain.bmp");

    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            transformed(i,j,0) = dft[i][j].imag();
            transformed(i,j,1) = dft[i][j].imag();
            transformed(i,j,2) = dft[i][j].imag();
        }
    }
    transformed.save("imag_domain.bmp");

}

void DFT2(CImg<unsigned char> &image)
{

    CImg<unsigned char> transformed(image.width(), image.height(), 1, 3, 0);
    std::vector<std::complex<double>> results = std::vector<std::complex<double>>();

    int M = image.width();
    int N = image.height();

    for (int u = 0; u < M; u++)
    {
        for (int v = 0; v < N; v++)
        {

            for (int x = 0; x < M; x++)
            {
                for (int y = 0; y < N; y++)
                {
                    results.push_back(((std::complex<double>)image(x, y, 0) * exp(-I * 2.0 * M_PI * (double)u * (double)x / (double)M) * exp(-I * 2.0 * M_PI * (double)v * (double)y / (double)N))/pow(N*M,0.5));
                }
            }

        }
    }
    for(int i=0; i<results.size(); i++)
    {
        transformed(results[i].real(), results[i].imag(), 0) += 1;
        transformed(results[i].real(), results[i].imag(), 1) += 1;
        transformed(results[i].real(), results[i].imag(), 2) += 1;
    }
    image = transformed;
}

void FFT(CImg<unsigned char> &image) {}
void IFFT(CImg<unsigned char> &image) {}