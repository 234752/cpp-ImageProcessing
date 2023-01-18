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
            for(unsigned short c = 0; c < 3; c++) {
                int q1 = image(x, y, c);
                int q2 = image(x, 2 * n - y - 1, c);
                int q3 = image(2 * n - x - 1, y, c);
                int q4 = image(2 * n - x - 1, 2 * n - y - 1, c);

                repositioned(n + x, n + y, c) = q1;
                repositioned(n + x, n - y - 1, c) = q2;
                repositioned(n - x - 1, n + y, c) = q3;
                repositioned(n - x - 1, n - y - 1, c) = q4;
            }
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

CImg<unsigned char> lowPassMask(CImg<unsigned char> &image, int r) {
    CImg<unsigned char> mask(image.width(), image.height(), 1, 3, 0);
    for(int i = 0; i<image.height(); i++) {
        for(int j = 0; j<image.width(); j++) {
            if(pow(i - image.height() / 2, 2) + pow(j - image.width() / 2, 2) <= pow(r, 2)) {
                mask(i, j, 0) = 255;
                mask(i, j, 1) = 255;
                mask(i, j, 2) = 255;
            }
        }
    }
    mask.save("mask.bmp");
    reposition(mask);

    vector<vector<complex<double>>> output = imageToMatrix(image);
    matrixFFT(output, -1);
    for(int i = 0; i<image.height(); i++) {
        for(int j = 0; j<image.width(); j++) {
            output[i][j] = output[i][j].operator*=( mask(i, j, 0)).operator/=(255);
        }
    }
    matrixFFT(output, 1);
    return matrixToImage(output);
}

CImg<unsigned char> highPassMask(CImg<unsigned char> &image, int r) {
    CImg<unsigned char> mask(image.width(), image.height(), 1, 3, 0);
    for(int i = 0; i<image.height(); i++) {
        for(int j = 0; j<image.width(); j++) {
            if(pow(i - (image.height() / 2), 2) + pow(j - (image.width() / 2), 2) > pow(r, 2)) {
                mask(i, j, 0) = 255;
                mask(i, j, 1) = 255;
                mask(i, j, 2) = 255;
            }
        }
    }
    mask(image.width() / 2, image.height() / 2, 0) = 255;
    mask(image.width() / 2, image.height() / 2, 1) = 255;
    mask(image.width() / 2, image.height() / 2, 2) = 255;
    mask.save("mask.bmp");
    reposition(mask);

    vector<vector<complex<double>>> output = imageToMatrix(image);
    matrixFFT(output, -1);
    for(int i = 0; i<image.height(); i++) {
        for(int j = 0; j<image.width(); j++) {
            output[i][j] = output[i][j].operator*=( mask(i, j, 0)).operator/=(255);
        }
    }
    matrixFFT(output, 1);
    return matrixToImage(output);
}

CImg<unsigned char> bandPassMask(CImg<unsigned char> &image, int r1, int r2) {
    CImg<unsigned char> mask(image.width(), image.height(), 1, 3, 0);
    for(int i = 0; i<image.height(); i++) {
        for(int j = 0; j<image.width(); j++) {
            if(pow(i - image.height() / 2, 2) + pow(j - image.width() / 2, 2) <= pow(r1, 2)
            && pow(i - image.height() / 2, 2) + pow(j - image.width() / 2, 2) > pow(r2, 2)) {
                mask(i, j, 0) = 255;
                mask(i, j, 1) = 255;
                mask(i, j, 2) = 255;
            }
        }
    }
    mask(image.width() / 2, image.height() / 2, 0) = 255;
    mask(image.width() / 2, image.height() / 2, 1) = 255;
    mask(image.width() / 2, image.height() / 2, 2) = 255;
    mask.save("mask.bmp");
    reposition(mask);

    vector<vector<complex<double>>> output = imageToMatrix(image);
    matrixFFT(output, -1);
    for(int i = 0; i<image.height(); i++) {
        for(int j = 0; j<image.width(); j++) {
            output[i][j] = output[i][j].operator*=( mask(i, j, 0)).operator/=(255);
        }
    }
    matrixFFT(output, 1);
    return matrixToImage(output);
}

CImg<unsigned char> bandCutMask(CImg<unsigned char> &image, int r1, int r2) {
    CImg<unsigned char> mask(image.width(), image.height(), 1, 3, 0);
    for(int i = 0; i<image.height(); i++) {
        for(int j = 0; j<image.width(); j++) {
            if(pow(i - image.height() / 2, 2) + pow(j - image.width() / 2, 2) > pow(r1, 2)
               || pow(i - image.height() / 2, 2) + pow(j - image.width() / 2, 2) <= pow(r2, 2)) {
                mask(i, j, 0) = 255;
                mask(i, j, 1) = 255;
                mask(i, j, 2) = 255;
            }
        }
    }
    mask.save("mask.bmp");
    reposition(mask);

    vector<vector<complex<double>>> output = imageToMatrix(image);
    matrixFFT(output, -1);
    for(int i = 0; i<image.height(); i++) {
        for(int j = 0; j<image.width(); j++) {
            output[i][j] = output[i][j].operator*=( mask(i, j, 0)).operator/=(255);
        }
    }
    matrixFFT(output, 1);
    return matrixToImage(output);
}

CImg<unsigned char> edgeMaskA(CImg<unsigned char> &image, int r, double s, double t) {
    CImg<unsigned char> mask(image.width(), image.height(), 1, 3, 0);
    for(int i = 0; i<image.width() / 2; i++) {
        for(int j = 0; j<image.height(); j++) {
            if(pow(i - (image.height() / 2.0), 2) + pow(j - (image.width() / 2.0), 2) > pow(r, 2)
            && ((i < (s + t) * (image.width() / 2.0 - j) + image.height() / 2.0
            && i > (s - t) * (image.width() / 2.0 - j) + image.height() / 2.0)
            || (i > (s + t) * (image.width() / 2.0 - j) + image.height() / 2.0
            && i < (s - t) * (image.width() / 2.0 - j) + image.height() / 2.0))) {
                mask(j, i, 0) = 255;
                mask(j, i, 1) = 255;
                mask(j, i, 2) = 255;
            }
        }
    }
    for(int i = image.width() / 2; i<image.width(); i++) {
        for(int j = 0; j<image.height(); j++) {
            if(pow(i - (image.height() / 2.0), 2) + pow(j - (image.width() / 2.0), 2) > pow(r, 2)
               && ((i < (s + t) * (image.width() / 2.0 - j) + image.height() / 2.0
               && i > (s - t) * (image.width() / 2.0 - j) + image.height() / 2.0)
               || (i > (s + t) * (image.width() / 2.0 - j) + image.height() / 2.0
               && i < (s - t) * (image.width() / 2.0 - j) + image.height() / 2.0))) {
                    mask(j, i, 0) = 255;
                    mask(j, i, 1) = 255;
                    mask(j, i, 2) = 255;
            }
        }
    }
    mask(image.width() / 2, image.height() / 2, 0) = 255;
    mask(image.width() / 2, image.height() / 2, 1) = 255;
    mask(image.width() / 2, image.height() / 2, 2) = 255;
    return mask;
}

CImg<unsigned char> edgeMaskB(CImg<unsigned char> &image, int r, double s, double t) {
    CImg<unsigned char> mask(image.width(), image.height(), 1, 3, 0);
    for(int i = 0; i<image.width() / 2; i++) {
        for(int j = 0; j<image.height(); j++) {
            if(pow(i - (image.height() / 2.0), 2) + pow(j - (image.width() / 2.0), 2) > pow(r, 2)
               && ((i < (s + t) * (image.width() / 2.0 - j) + image.height() / 2.0
                    && i > (s - t) * (image.width() / 2.0 - j) + image.height() / 2.0)
                   || (i > (s + t) * (image.width() / 2.0 - j) + image.height() / 2.0
                       && i < (s - t) * (image.width() / 2.0 - j) + image.height() / 2.0))) {
                mask(i, j, 0) = 255;
                mask(i, j, 1) = 255;
                mask(i, j, 2) = 255;
            }
        }
    }
    for(int i = image.width() / 2; i<image.width(); i++) {
        for(int j = 0; j<image.height(); j++) {
            if(pow(i - (image.height() / 2.0), 2) + pow(j - (image.width() / 2.0), 2) > pow(r, 2)
               && ((i < (s + t) * (image.width() / 2.0 - j) + image.height() / 2.0
               && i > (s - t) * (image.width() / 2.0 - j) + image.height() / 2.0)
               || (i > (s + t) * (image.width() / 2.0 - j) + image.height() / 2.0
               && i < (s - t) * (image.width() / 2.0 - j) + image.height() / 2.0))) {
                    mask(i, j, 0) = 255;
                    mask(i, j, 1) = 255;
                    mask(i, j, 2) = 255;
            }
        }
    }
    mask(image.width() / 2, image.height() / 2, 0) = 255;
    mask(image.width() / 2, image.height() / 2, 1) = 255;
    mask(image.width() / 2, image.height() / 2, 2) = 255;
    return mask;
}

CImg<unsigned char> edgeMask2(CImg<unsigned char> &image, int r, double angle, double width) {
    CImg<unsigned char> mask(image.width(), image.height(), 1, 3, 0);
    int originX = image.width()/2;
    int originY = image.width()/2;
    for(int i = 0; i<image.width(); i++) {
        for(int j = 0; j<image.height(); j++) {
            if(pow(i - (image.height() / 2), 2) + pow(j - (image.width() / 2), 2) > pow(r, 2)) {
                if (i == originX) continue;
                if ((tan(angle) > (double) (j - originY) / (double) (i - originX) &&
                     tan(angle - width) < (double) (j - originY) / (double) (i - originX))
                    || (tan(angle) < (double) (j - originY) / (double) (i - originX) &&
                        tan(angle - width) > (double) (j - originY) / (double) (i - originX))) {
                    mask(i, j, 0) = 255;
                    mask(i, j, 1) = 255;
                    mask(i, j, 2) = 255;
                }
            }
        }
    }

    mask(image.width() / 2, image.height() / 2, 0) = 255;
    mask(image.width() / 2, image.height() / 2, 1) = 255;
    mask(image.width() / 2, image.height() / 2, 2) = 255;
    mask.save("mask.bmp");
    reposition(mask);

    vector<vector<complex<double>>> output = imageToMatrix(image);
    matrixFFT(output, -1);
    for(int i = 0; i<image.height(); i++) {
        for(int j = 0; j<image.width(); j++) {
            output[i][j] = output[i][j].operator*=( mask(i, j, 0)).operator/=(255);
        }
    }
    matrixFFT(output, 1);
    return matrixToImage(output);
}

CImg<unsigned char> edgeMask7(CImg<unsigned char> &image, int r, double angle, double width) {
    CImg<unsigned char> mask(image.width(), image.height(), 1, 3, 0);
    int originX = image.width()/2;
    int originY = image.width()/2;
    for(int i = 0; i<image.width(); i++) {
        for(int j = 0; j<image.height(); j++) {
            if(pow(i - (image.height() / 2), 2) + pow(j - (image.width() / 2), 2) > pow(r, 2)) {
                if (i == originX) continue;
                if ((tan(angle) > (double) (j - originY) / (double) (i - originX) &&
                     tan(angle - width) < (double) (j - originY) / (double) (i - originX))
                    || (tan(angle) < (double) (j - originY) / (double) (i - originX) &&
                        tan(angle - width) > (double) (j - originY) / (double) (i - originX))) {
                    mask(j, i, 0) = 255;
                    mask(j, i, 1) = 255;
                    mask(j, i, 2) = 255;
                }
            }
        }
    }

    mask(image.width() / 2, image.height() / 2, 0) = 255;
    mask(image.width() / 2, image.height() / 2, 1) = 255;
    mask(image.width() / 2, image.height() / 2, 2) = 255;
    mask.save("mask.bmp");
    reposition(mask);

    vector<vector<complex<double>>> output = imageToMatrix(image);
    matrixFFT(output, -1);
    for(int i = 0; i<image.height(); i++) {
        for(int j = 0; j<image.width(); j++) {
            output[i][j] = output[i][j].operator*=( mask(i, j, 0)).operator/=(255);
        }
    }
    matrixFFT(output, 1);
    return matrixToImage(output);
}

void modifyPhase(CImg<unsigned char> &image, int l, int k) {
    vector<vector<complex<double>>> output = imageToMatrix(image);
    matrixFFT(output, -1);
    for(int i = 0; i<image.width(); i++) {
        for(int j = 0; j<image.height(); j++) {
            output[i][j] = output[i][j] * exp(I * (((-i * k * 2.0 * PI) / image.width()) +
                           ((-j * l * 2.0 * PI) / image.height()) + ((k + l) * PI)));
        }
    }
    matrixFFT(output, 1);
    image = matrixToImage(output);
}