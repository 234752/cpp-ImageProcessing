#include "Task4T.cpp"
#include <complex>

using namespace cimg_library;
using namespace std;

void reposition(CImg<unsigned char> &image) {
    CImg<unsigned char> repositioned = image;
    unsigned int n = image.height() / 2;
    for (unsigned int x = 0; x < n; x++)
    {
        for (unsigned int y = 0; y < n; y++)
        {
            int q1 = image(x, y, 0);
            int q2 = image(x, 2 * n - y, 0);
            int q3 = image(2 * n - x, y, 0);
            int q4 = image(2 * n - x, 2 * n - y, 0);
            //Q1
            repositioned(n + x, n - y - 1, 0) = q4;
            repositioned(n + x, n - y - 1, 1) = q4;
            repositioned(n + x, n - y - 1, 2) = q4;

            //Q2
            repositioned(n - x - 1, n - y - 1, 0) = q3;
            repositioned(n - x - 1, n - y - 1, 1) = q3;
            repositioned(n - x - 1, n - y - 1, 2) = q3;

            //Q3
            repositioned(n - x - 1, n + y, 0) = q2;
            repositioned(n - x - 1, n + y, 1) = q2;
            repositioned(n - x - 1, n + y, 2) = q2;

            //Q4
            repositioned(n + x, n + y, 0) = q1;
            repositioned(n + x, n + y, 1) = q1;
            repositioned(n + x, n + y, 2) = q1;
        }
    }
    image = repositioned;
}

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

void showAppliedMask(CImg<unsigned char> &image, CImg<unsigned char> &mask) {
    if(image.height() != mask.height() || image.width() != mask.width()) {
        cout << "Size of the mask is different than size of the image";
        return;
    }
    double value;
    for(unsigned i = 0; i < image.height(); i++) {
        for(unsigned j = 0; j < image.width(); j++) {
            value = image(i, j, 0);
            image(i, j, 0) = (value * mask(i, j, 0)) / 255;
            image(i, j, 1) = (value * mask(i, j, 0)) / 255;
            image(i, j, 2) = (value * mask(i, j, 0)) / 255;
        }
    }
}

void applyMask(CImg<unsigned char> &image, CImg<unsigned char> &mask) {
    if(image.height() != mask.height() || image.width() != mask.width()) {
        cout << "Size of the mask is different than size of the image";
        return;
    }
    vector<vector<complex<double>>> output = imageToMatrix(image);
    matrixFFT(output, -1);
    for(int i = 0; i<image.height(); i++) {
        for(int j = 0; j<image.width(); j++) {
            output[i][j] = output[i][j].operator*=( mask(i, j, 0)).operator/=(255);
        }
    }
    matrixFFT(output, 1);
    image = matrixToImage(output);
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

void highPassFilter(CImg<unsigned char> &image, int threshold) {

    int N = image.height();
    vector<vector<complex<double>>> highPassed = imageToMatrix(image);

    matrixFFT(highPassed, -1);

    for(int i=N/2-threshold; i<N/2+threshold; i++) {
        for(int j=N/2-threshold; j<N/2+threshold; j++) {
            highPassed[i][j] = 0;
        }
    }

    matrixFFT(highPassed, 1);

    image = matrixToImage(highPassed);
}