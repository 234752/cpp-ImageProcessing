
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