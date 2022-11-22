using namespace cimg_library;

CImg<unsigned char> lowPassFilter(CImg<unsigned char> &image) {
    CImg<unsigned char> newImage = image;
    for (unsigned short c = 0; c < 3; c++) {
        for (unsigned x = 1; x < image.width() - 1; x++) {
            for (unsigned y = 1; y < image.height() - 1; y++) {
                unsigned sum = 0;
                for (short i = -1; i < 2; i++) {
                    for (short j = -1; j < 2; j++) {
                        sum += image(x + i, y + j, c);
                    }
                }
                newImage(x, y, c) = sum / 9;
            }
        }
    }
    return newImage;
}

CImg<unsigned char> lowPassFilter1(CImg<unsigned char> &image) {
    CImg<unsigned char> newImage = image;
    for (unsigned short c = 0; c < 3; c++) {
        for (unsigned x = 1; x < image.width() - 1; x++) {
            for (unsigned y = 1; y < image.height() - 1; y++) {
                unsigned sum = 0;
                for (short i = -1; i < 2; i++) {
                    for (short j = -1; j < 2; j++) {
                        sum += image(x + i, y + j, c);
                    }
                }
                newImage(x, y, c) = sum / 9;
            }
        }
    }
    return newImage;
}

CImg<unsigned char> lowPassFilter2(CImg<unsigned char> &image) {
    CImg<unsigned char> newImage = image;
    for (unsigned short c = 0; c < 3; c++) {
        for (unsigned x = 1; x < image.width() - 1; x++) {
            for (unsigned y = 1; y < image.height() - 1; y++) {
                unsigned sum = 0;
                for (short i = -1; i < 2; i++) {
                    for (short j = -1; j < 2; j++) {
                        sum += image(x + i, y + j, c);
                    }
                }
                sum += image(x, y, c);
                newImage(x, y, c) = sum / 10;
            }
        }
    }
    return newImage;
}

CImg<unsigned char> lowPassFilter3(CImg<unsigned char> &image) {
    CImg<unsigned char> newImage = image;
    for (unsigned short c = 0; c < 3; c++) {
        for (unsigned x = 1; x < image.width() - 1; x++) {
            for (unsigned y = 1; y < image.height() - 1; y++) {
                unsigned sum = 0;
                for (short i = -1; i < 2; i++) {
                    for (short j = -1; j < 2; j++) {
                        sum += image(x + i, y + j, c);
                    }
                    sum += image(x + i, y, c);
                    sum += image(x, y + i, c);
                }
                sum += image(x, y, c);
                newImage(x, y, c) = sum / 16;
            }
        }
    }
    return newImage;
}

CImg<unsigned char> optimisedLowPassFilter(CImg<unsigned char> &image) {
    CImg<unsigned char> newImage = lowPassFilter1(image);
    return newImage;
}