#include <cmath>
#include <complex>

using namespace cimg_library;
using namespace std;

const std::complex<double> I(0, 1);
const double PI = 3.141592653589793238463;

void matrixDFT(vector<vector<complex<double>>> &inputMatrix, int M, int N, int inverseCoefficient) { //coefficient: -1 for DFT, 1 for inverse DFT

    vector<vector<complex<double>>> outputMatrix(M, vector<complex<double>>(N));

    for (int u = 0; u < M; u++) {
        for (int v = 0; v < N; v++) {

            complex<double> sum(0, 0);

            for (int x = 0; x < M; x++) {
                for (int y = 0; y < N; y++) {

                    double angle = 2 * PI * (u * x) / M + 2 * PI * (v * y) / N;
                    double factor = sqrt(N * M);
                    sum += exp((double)inverseCoefficient * I * angle) * inputMatrix[x][y] / factor;
                }
            }

            //cout<<u<<" "<<v<<" "<<sum.real()<<" "<<sum.imag()<<endl;
            outputMatrix[u][v] = sum;
        }
        //cout<<u<<endl;
    }
    inputMatrix = outputMatrix;
}

void DFT(CImg<unsigned char> &image, int inverseCoefficient)
{
    CImg<unsigned char> transformed(image.width(), image.height(), 1, 3, 0);

    int M = image.width();
    int N = image.height();
    vector<vector<complex<double>>> dft(M, vector<complex<double>>(N));


    for(int x=0; x < M; x++)
    {
        for(int y=0; y < N; y++)
        {
            dft[x][y] = image(x, y, 0);
        }
    }
    matrixDFT(dft, M, N, inverseCoefficient);

    int maxValue = 0;
    for(int x=0; x < M; x++)
    {
        for(int y=0; y < N; y++)
        {
            int value = log(1+ pow(pow(dft[x][y].imag(), 2) + pow(dft[x][y].real(), 2), 0.5));
            if(value > maxValue) maxValue = value;
        }
    }
    for(int x=0; x < M; x++)
    {
        for(int y=0; y < N; y++)
        {
            int value = log(1+ pow(pow(dft[x][y].imag(), 2) + pow(dft[x][y].real(), 2), 0.5));
            value *= 255;
            value /= maxValue;
            transformed(x, y, 0) = value;
            transformed(x, y, 1) = value;
            transformed(x, y, 2) = value;
            //std::cout << x << " " << y << "  " << dft[x][y].real() << " " << dft[x][y].imag() << "  " << value << endl;
        }
    }
    transformed.save("DFT.bmp");
}

void linearFFT(vector<complex<double>> &x, int inverseCoefficient) {

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

    linearFFT(even, inverseCoefficient);
    linearFFT(odd, inverseCoefficient);

    double angle = 2.0 * PI / (double)n * (double)inverseCoefficient;
    complex<double> w(1);
    complex<double> wn(cos(angle), -sin(angle));
    for (int i = 0; i < n / 2; i++) {
        x[i] = even[i] + w * odd[i];
        x[i + n / 2] = even[i] - w * odd[i];
        w *= wn;
    }

}

void matrixFFT(vector<vector<complex<double>>> &inputMatrix, int inverseCoefficient) { //coefficient: -1 for FFT, 1 for inverse FFT
    int rows = inputMatrix.size();
    int cols = inputMatrix[0].size();

    for (vector<complex<double>> &row : inputMatrix) {
        linearFFT(row, inverseCoefficient);
    }

    vector<vector<complex<double>>> transposedMatrix(cols, vector<complex<double>>(rows));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            transposedMatrix[j][i] = inputMatrix[i][j];
        }
    }

    for (vector<complex<double>> &col : transposedMatrix) {
        linearFFT(col, inverseCoefficient);
    }

    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            inputMatrix[j][i] = transposedMatrix[i][j];
        }
    }
}

void FFT(CImg<unsigned char> &image, int inverseCoefficient) {
    CImg<unsigned char> transformed(image.width(), image.height(), 1, 3, 0);
    CImg<unsigned char> repositioned(image.width(), image.height(), 1, 3, 0);

    int N = image.height();
    vector<vector<complex<double>>> fft(N, vector<complex<double>>(N));

    for(int x=0; x < N; x++)
    {
        for(int y=0; y < N; y++)
        {
            fft[x][y] = image(x,y,0);
        }
    }

    matrixFFT(fft, inverseCoefficient);

    int maxValue = 0;
    for(int x=0; x < N; x++)
    {
        for(int y=0; y < N; y++)
        {
            int value = log(1+ pow(pow(fft[x][y].imag(), 2) + pow(fft[x][y].real(), 2), 0.5));
            if(value > maxValue) maxValue = value;
        }
    }
    for(int x=0; x < N; x++)
    {
        for(int y=0; y < N; y++)
        {
            int value = log(1+ pow(pow(fft[x][y].imag(), 2) + pow(fft[x][y].real(), 2), 0.5));
            value *= 255;
            value /= maxValue;
            transformed(x, y, 0) = value;
            transformed(x, y, 1) = value;
            transformed(x, y, 2) = value;
            //std::cout << x << " " << y << "  " << fft[x][y].real() << " " << fft[x][y].imag() << "  " << value << endl;
        }
    }

    for(int x=0; x < N /2; x++)
    {
        for(int y=0; y < N /2; y++)
        {
            int value = transformed(x, y,0);

            //Q1
            repositioned(N/2 + x, N/2 - y, 0) = value;
            repositioned(N/2 + x, N/2 - y, 1) = value;
            repositioned(N/2 + x, N/2 - y, 2) = value;

            //Q2
            repositioned(N/2 - x, N/2 - y, 0) = value;
            repositioned(N/2 - x, N/2 - y, 1) = value;
            repositioned(N/2 - x, N/2 - y, 2) = value;

            //Q3
            repositioned(N/2 - x, N/2 + y, 0) = value;
            repositioned(N/2 - x, N/2 + y, 1) = value;
            repositioned(N/2 - x, N/2 + y, 2) = value;

            //Q4
            repositioned(N/2 + x, N/2 + y, 0) = value;
            repositioned(N/2 + x, N/2 + y, 1) = value;
            repositioned(N/2 + x, N/2 + y, 2) = value;

        }
    }
    image = repositioned;
}