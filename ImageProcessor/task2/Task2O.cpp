
using namespace cimg_library;

void robertOperator(CImg<unsigned char> &image)
{
    CImg<unsigned char> filteredImage = image;
    for (int x = 1; x < image.width()-1; x=x+1)
    {
        for (int y = 1; y < image.height()-1; y=y+1)
        {
            int r = abs(image(x, y, 0) - image(x+1, y+1, 0)) + abs(image(x, y+1, 0) - image(x+1, y, 0));
            int g = abs(image(x, y, 1) - image(x+1, y+1, 1)) + abs(image(x, y+1, 1) - image(x+1, y, 1));
            int b = abs(image(x, y, 2) - image(x+1, y+1, 2)) + abs(image(x, y+1, 2) - image(x+1, y, 2));

            int max = r;
            if(g > max)
            {
                max = g;
            }
            if(b > max)
            {
                max = b;
            }

            filteredImage(x, y, 0) = max;
            filteredImage(x, y, 1) = max;
            filteredImage(x, y, 2) = max;

        }
    }
    image = filteredImage;
}

void SobelOperator(CImg<unsigned char> &image)
{
    CImg<unsigned char> filteredImage = image;
    for (int x = 1; x < image.width()-1; x=x+1)
    {
        for (int y = 1; y < image.height()-1; y=y+1)
        {
            int a0 = image(x-1, y-1, 0);
            int a1 = image(x, y-1, 0);
            int a2 = image(x+1, y-1, 0);
            int a3 = image(x+1, y, 0);
            int a4 = image(x+1, y+1, 0);
            int a5 = image(x, y+1, 0);
            int a6 = image(x-1, y+1, 0);
            int a7 = image(x-1, y, 0);

            int bigX = a1 +2*a3 +a4 -a0 -2*a7 -a6;
            int bigY = a0 +2*a1 +a2 -a6 -2*a5 -a4;

            int g = (int)pow(pow(1.0*bigX,2) + pow(1.0*bigY,2), 0.5);

            filteredImage(x, y, 0) = g;
            filteredImage(x, y, 1) = g;
            filteredImage(x, y, 2) = g;
        }
    }
    image = filteredImage;
}

void kirshOperator(CImg<unsigned char> &image) {
    CImg<unsigned char> newImage = image;
    int s;
    int t;
    int max;
    for (unsigned short i = 0; i < 3; i++) {
        for (int x = 1; x < image.width() - 1; x++) {
            for (int y = 1; y < image.height() - 1; y++) {
                max = 1;
                int values[8] = {image(x - 1, y - 1, i), image(x, y - 1, i), image(x + 1, y - 1, i),
                                 image(x + 1, y, i), image(x + 1, y + 1, i), image(x, y + 1, i),
                                 image(x - 1, y + 1, i), image(x - 1, y, i)};
                for (unsigned short v = 0; v < 8; v++) {
                    s = values[v] + values[(v + 1) % 8] + values[(v + 2) % 8];
                    t = values[(v + 3) % 8] + values[(v + 4) % 8] + values[(v + 5) % 8] + values[(v + 6) % 8] +
                        values[(v + 7) % 8];
                    if (abs(5 * s - 3 * t) > max) {
                        max = abs(5 * s - 3 * t);
                    }
                }
                newImage(x, y, i) = max;
            }
        }
    }
    image = newImage;
}
