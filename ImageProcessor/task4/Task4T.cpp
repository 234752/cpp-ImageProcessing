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

            //cout<<u<<" "<<v<<" "<<sum.real()<<" "<<sum.imag()<<endl;
            outputMatrix[u][v] = sum;
        }
        cout<<u<<endl;
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
    //dft = matrixDFT(dft, M, N, 1);

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

void linearFFT(vector<complex<double>> &x, int inverse) {

    int n = x.size();

    if (n == 1) {
        return;
    }

    vector<complex<double>> even(n / 2);
    vector<complex<double>> odd(n / 2);
    for (int i = 0; i < n / 2; i++) {
        even[i] = x[2 * i];
        odd[i] = x[2 * i + 1];
    }

    linearFFT(even, inverse);
    linearFFT(odd, inverse);

    double angle = 2 * M_PI / n * (inverse ? -1 : 1);
    complex<double> w(1);
    complex<double> wn(cos(angle), sin(angle));
    for (int i = 0; i < n / 2; i++) {
        x[i] = even[i] + w * odd[i];
        x[i + n / 2] = even[i] - w * odd[i];
        w *= wn;
    }
}

void matrixFFT(vector<vector<complex<double>>> &inputMatrix, int inverse) {
    int rows = inputMatrix.size();
    int cols = inputMatrix[0].size();

    for (vector<complex<double>> &row : inputMatrix) {
        linearFFT(row, inverse);
    }

    vector<vector<complex<double>>> transposedMatrix(cols, vector<complex<double>>(rows));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            transposedMatrix[j][i] = inputMatrix[i][j];
        }
    }

    for (vector<complex<double>> &col : transposedMatrix) {
        linearFFT(col, inverse);
    }

    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            inputMatrix[j][i] = transposedMatrix[i][j];
        }
    }
}

void FFT(CImg<unsigned char> &image) {
    CImg<unsigned char> transformed(image.width(), image.height(), 1, 3, 0);

    int N = image.height();
    vector<vector<complex<double>>> matrix(N, vector<complex<double>>(N));


    for(int x=0; x < N; x++)
    {
        for(int y=0; y < N; y++)
        {
            matrix[x][y] = image(x,y,0);
        }
    }

    matrixFFT(matrix, 0);


    int maxValue = 0;
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            int value = log(1+ pow(pow(matrix[i][j].imag(),2) + pow(matrix[i][j].real(),2), 0.5));
            if(value > maxValue) maxValue = value;
        }
    }
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            int value = log(1+ pow(pow(matrix[i][j].imag(),2) + pow(matrix[i][j].real(),2), 0.5));
            value *= 255;
            value /= maxValue;
            transformed(i,j,0) = value;
            transformed(i,j,1) = value;
            transformed(i,j,2) = value;
            std::cout<<i<<" "<<j<<"  "<<matrix[i][j].real()<<" "<<matrix[i][j].imag()<<"  "<<value<<endl;
        }
    }
    transformed.save("FFT.bmp");
}
void IFFT(CImg<unsigned char> &image) {}