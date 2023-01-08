#include "../lib/CImg.h"
#include "Task4T.cpp"
#include <complex>

using namespace cimg_library;
using namespace std;

void lowPassFilter(CImg<unsigned char> &image, int threshold) {
    CImg<unsigned char> transformed(image.width(), image.height(), 1, 3, 0);

    int N = image.height();
    vector<vector<complex<double>>> lowPassed(N, vector<complex<double>>(N));

    for(int x=0; x < N; x++)
    {
        for(int y=0; y < N; y++)
        {
            lowPassed[x][y] = image(x,y,0);
        }
    }

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

    for(int x=0; x < N; x++)
    {
        for(int y=0; y < N; y++)
        {
            int value = pow(pow(lowPassed[x][y].imag(), 2) + pow(lowPassed[x][y].real(), 2), 0.5);
            transformed(x, y, 0) = value;
            transformed(x, y, 1) = value;
            transformed(x, y, 2) = value;
        }
    }
    image = transformed;
}