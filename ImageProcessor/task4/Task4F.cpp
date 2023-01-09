#include "../lib/CImg.h"
#include "Task4T.cpp"
#include <complex>

using namespace cimg_library;
using namespace std;

vector<vector<complex<double>>> imageToMatrix(CImg<unsigned char> image) {

    int N = image.height();
    vector<vector<complex<double>>> matrix(N, vector<complex<double>>(N));

    for(int x=0; x < N; x++)
    {
        for(int y=0; y < N; y++)
        {
            matrix[x][y] = image(x,y,0);
        }
    }
    return matrix;
}

CImg<unsigned char> matrixToImage(vector<vector<complex<double>>> matrix) {

    int N = matrix.size();
    CImg<unsigned char> image(N, N, 1, 3, 0);

    double maxValue = 0;
    for(int x=0; x < N; x++)
    {
        for(int y=0; y < N; y++)
        {
            double value = pow(pow(matrix[x][y].imag(), 2) + pow(matrix[x][y].real(), 2), 0.5);
            if(value > maxValue) maxValue = value;
        }
    }
    for(int x=0; x < N; x++)
    {
        for(int y=0; y < N; y++)
        {
            double value = pow(pow(matrix[x][y].imag(), 2) + pow(matrix[x][y].real(), 2), 0.5);
            value *= 255.0;
            value /= maxValue;
            image(x, y, 0) = value;
            image(x, y, 1) = value;
            image(x, y, 2) = value;
        }
    }
    return image;
}


void lowPassFilter(CImg<unsigned char> &image, int threshold) {

    int N = image.height();
    vector<vector<complex<double>>> lowPassed = imageToMatrix(image);

    matrixFFT(lowPassed, -1);

    for(int i=0; i<threshold; i++) {
        for(int j=0; j<threshold; j++) {
            lowPassed[i][j] = 0;
            lowPassed[N-i -1][j] = 0;
            lowPassed[i][N-j -1] = 0;
            lowPassed[N-i -1][N-j -1] = 0;
        }
    }

    matrixFFT(lowPassed, 1);

    image = matrixToImage(lowPassed);
}