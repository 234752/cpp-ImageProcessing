using namespace cimg_library;

short mask[3][3] =
        {{0, 1, 0},
         {1, 1, 1},
         {0, 1, 0}};

// value 2 represents inactive points
short mask1[3][3] = {{1, 2, 2},
                     {1, 0, 2},
                     {1, 2, 2}};
short mask2[3][3] = {{1, 1, 1},
                     {2, 0, 2},
                     {2, 2, 2}};
short mask3[3][3] = {{2, 2, 1},
                     {2, 0, 1},
                     {2, 2, 1}};
short mask4[3][3] = {{2, 2, 2},
                     {2, 0, 2},
                     {1, 1, 1}};
//short mask1[3][3] = {{2, 2, 2},
//                     {1, 0, 2},
//                     {1, 1, 2}};
//short mask2[3][3] = {{1, 1, 2},
//                     {1, 0, 2},
//                     {2, 2, 2}};
//short mask3[3][3] = {{2, 1, 1},
//                     {2, 0, 1},
//                     {2, 2, 2}};
//short mask4[3][3] = {{2, 2, 2},
//                     {2, 0, 1},
//                     {2, 1, 1}};


int findMaxValueInMask(CImg<unsigned char> &image, int x, int y)
{
    int max =0;
    for(int maskX = -1; maskX<2; maskX++)
    {
        for(int maskY = -1; maskY<2; maskY++)
        {
            if(mask[maskX+1][maskY+1] == 1 && image(x + maskX , y + maskY , 0) > max)
            {
                max = image(x + maskX , y + maskY , 0);
            }
        }
    }
    return max;
}

int findMinValueInMask(CImg<unsigned char> &image, int x, int y)
{
    int min = 255;
    for(int maskX = -1; maskX<2; maskX++)
    {
        for(int maskY = -1; maskY<2; maskY++)
        {
            if(mask[maskX+1][maskY+1] == 1 && image(x + maskX , y + maskY , 0) < min)
            {
                min = image(x + maskX , y + maskY , 0);
            }
        }
    }
    return min;
}

bool checkHitOrMiss(CImg<unsigned char> &image, int x, int y)
{
    for(int maskX = -1; maskX < 2; maskX++)
    {
        for(int maskY = -1; maskY < 2; maskY++)
        {
            if(mask[maskX+1][maskY+1] != 2)
            {
                if (mask[maskX+1][maskY+1] == 1 && image(x + maskX, y + maskY, 0) == 0) {
                    return false;
                }
                if (mask[maskX+1][maskY+1] == 0 && image(x + maskX, y + maskY, 0) != 0) {
                    return false;
                }
            }
        }
    }
    //if for every spot of the mask, there was a foreground of the image, return hit
    return true;
}

void dilation(CImg<unsigned char> &image)
{
    CImg<unsigned char> newImage = image;

    for (int x = 1; x < image.width()-1; x++)
    {
        for (int y = 1; y < image.height()-1; y++)
        {
            int newValue = findMaxValueInMask(image, x, y);
            newImage(x, y, 0) = newValue;
            newImage(x, y, 1) = newValue;
            newImage(x, y, 2) = newValue;
        }
    }
    image = newImage;
}

void erosion(CImg<unsigned char> &image)
{
    CImg<unsigned char> newImage = image;

    for (int x = 1; x < image.width()-1; x++)
    {
        for (int y = 1; y < image.height()-1; y++)
        {
            int newValue = findMinValueInMask(image, x, y);
            newImage(x, y, 0) = newValue;
            newImage(x, y, 1) = newValue;
            newImage(x, y, 2) = newValue;
        }
    }
    image = newImage;
}

void opening(CImg<unsigned char> &image)
{
    erosion(image);
    dilation(image);
}

void closing(CImg<unsigned char> &image)
{
    dilation(image);
    erosion(image);
}

void HMT(CImg<unsigned char> &image)
{
    CImg<unsigned char> newImage(image.width(), image.height(), 1, 3, 0);

    for (int x = 1; x < image.width()-1; x++)
    {
        for (int y = 1; y < image.height()-1; y++)
        {
            if(checkHitOrMiss(image, x, y))
            {
                newImage(x, y, 0) = 255;
                newImage(x, y, 1) = 255;
                newImage(x, y, 2) = 255;
            }
        }
    }
    image = newImage;
}

void uHMT(CImg<unsigned char> &image)
{
    CImg<unsigned char> newImage = image;

    for (int x = 1; x < image.width()-1; x++)
    {
        for (int y = 1; y < image.height()-1; y++)
        {
            if(checkHitOrMiss(image, x, y))
            {
                newImage(x, y, 0) = 255;
                newImage(x, y, 1) = 255;
                newImage(x, y, 2) = 255;
            }
        }
    }
    image = newImage;
}

void changeMask(short newMask[3][3]) {
    for (short i = 0; i < 3; i++) {
        for (short j = 0; j < 3; j++) {
            mask[i][j] = newMask[i][j];
        }
    }
}

void imageUnion(CImg<unsigned char> &image1, CImg<unsigned char> &image2) {
    for (int x = 0; x < image1.width(); x++)
    {
        for (int y = 0; y < image1.height(); y++)
        {
            if(image2(x, y, 0) == 255)
            {
                image1(x, y, 0) = 255;
                image1(x, y, 1) = 255;
                image1(x, y, 2) = 255;
            }
        }
    }
}

// convex hull - otoczka wypukła <3
void M4(CImg<unsigned char> &image) {
    CImg<unsigned char> image1 = image, image2 = image, image3 = image, image4 = image;
    changeMask(mask1);
    while (true) {
        uHMT(image1);
        if (image == image1) break;
        image = image1;
    }
    image = image2;
    changeMask(mask2);
    while (true) {
        uHMT(image2);
        if (image == image2) break;
        image = image2;
    }
    image = image3;
    changeMask(mask3);
    while (true) {
        uHMT(image3);
        if (image == image3) break;
        image = image3;
    }
    image = image4;
    changeMask(mask4);
    while (true) {
        uHMT(image4);
        if (image == image4) break;
        image = image4;
    }
    imageUnion(image, image1);
    imageUnion(image, image2);
    imageUnion(image, image3);
}

/* optimised convex hull algorithm */

bool checkRow(CImg<unsigned char> &image, int y) {
    for (unsigned int x = 0; x < image.width(); x++) {
        if (image(x, y, 1) != 0) {
            return true;
        }
    }
    return false;
}

bool checkColumn(CImg<unsigned char> &image, int x) {
    for (unsigned int y = 0; y < image.height(); y++) {
        if (image(x, y, 0) != 0){
            return true;
        }
    }
    return false;
}

bool checkHM(CImg<unsigned char> &image, int x, int y, bool horizontalCheck)
{
    for(int maskX = -1; maskX < 2; maskX++)
    {
        for(int maskY = -1; maskY < 2; maskY++)
        {
            if(mask[maskX+1][maskY+1] != 2)
            {
                if (mask[maskX+1][maskY+1] == 1 && image(x + maskX, y + maskY, 0) == 0) {
                    return false;
                }
                if (mask[maskX+1][maskY+1] == 0 && image(x + maskX, y + maskY, 0) != 0) {
                    return false;
                }
            }
        }
    }
    //check if change would make the object convex
    if(horizontalCheck) {
        return checkRow(image, y);
    } else {
        return checkColumn(image, x);
    }
}

void oHMT(CImg<unsigned char> &image, bool horizontalCheck)
{
    CImg<unsigned char> newImage = image;

    for (int x = 1; x < image.width()-1; x++)
    {
        for (int y = 1; y < image.height()-1; y++)
        {
            if(checkHM(image, x, y, horizontalCheck))
            {
                newImage(x, y, 0) = 255;
                newImage(x, y, 1) = 255;
                newImage(x, y, 2) = 255;
            }
        }
    }
    image = newImage;
}

void oM4(CImg<unsigned char> &image) {
    CImg<unsigned char> image1 = image, image2 = image, image3 = image, image4 = image;
    changeMask(mask1);
    while (true) {
        oHMT(image1, true);
        if (image == image1) break;
        image = image1;
    }
    image = image2;
    changeMask(mask2);
    while (true) {
        oHMT(image2, false);
        if (image == image2) break;
        image = image2;
    }
    image = image3;
    changeMask(mask3);
    while (true) {
        oHMT(image3, true);
        if (image == image3) break;
        image = image3;
    }
    image = image4;
    changeMask(mask4);
    while (true) {
        oHMT(image4, false);
        if (image == image4) break;
        image = image4;
    }
    imageUnion(image, image1);
    imageUnion(image, image2);
    imageUnion(image, image3);
}