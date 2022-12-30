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

vector<vector<complex<double>>> matrixDFT(vector<vector<complex<double>>> inputMatrix, int M, int N, int inverseCoefficient) { //coefficient: -1 for DFT, 1 for inverse DFT

    vector<vector<complex<double>>> outputMatrix(M, vector<complex<double>>(N));

    for (int u = 0; u < M; u++) {
        for (int v = 0; v < N; v++) {

            complex<double> sum(0, 0);

            for (int x = 0; x < M; x++) {
                for (int y = 0; y < N; y++) {

                    double angle = 2 * M_PI * (u * x) / M + 2 * M_PI * (v * y) / N;
                    double factor = sqrt(N * M);
                    sum += exp((double)inverseCoefficient * I * angle) * inputMatrix[x][y] / factor;
                }
            }

            cout<<u<<" "<<v<<" "<<sum.real()<<" "<<sum.imag()<<endl;
            outputMatrix[u][v] = sum;
        }
    }
    return outputMatrix;
}

void DFT(CImg<unsigned char> &image)
{
    CImg<unsigned char> transformed(image.width(), image.height(), 1, 3, 0);

    int M = image.width();
    int N = image.height();
    vector<vector<complex<double>>> matrix(M, vector<complex<double>>(N));


    for(int x=0; x < M; x++)
    {
        for(int y=0; y < N; y++)
        {
            matrix[x][y] = image(x, y, 0);
        }
    }
    vector<vector<complex<double>>> dft = matrixDFT(matrix, M, N, -1);
    dft = matrixDFT(dft, M, N, 1);

    for(int i=0; i<M; i++)
    {
        for(int j=0; j<N; j++)
        {
            int value = pow(pow(dft[i][j].imag(),2) + pow(dft[i][j].real(),2), 0.5);
            transformed(i,j,0) = value;
            transformed(i,j,1) = value;
            transformed(i,j,2) = value;
            std::cout<<i<<" "<<j<<" "<<value<<endl;
        }
    }
    transformed.save("both_domains.bmp");
}

void FFT(CImg<unsigned char> &image) {}
void IFFT(CImg<unsigned char> &image) {}