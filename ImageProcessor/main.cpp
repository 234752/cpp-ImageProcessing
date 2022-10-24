#include <iostream>
#include "lib/popl.hpp"
#include "lib/CImg.h"
#include "task1/Task1B.cpp"
#include "task1/Task1G.cpp"
#include "task1/Task1E.cpp"
#include "task1/Task1N.cpp"


using namespace popl;
using namespace std;

int main(int argc, char *argv[])
{
    OptionParser op("Allowed options");
    auto help_option     = op.add<Switch>("", "help", "produce help message");

    //B options
    auto brightness_option = op.add<Value<int>>("", "brightness", "brightness modification", 0);
    auto contrast_option = op.add<Value<int>>("", "contrast", "contrast modification", 0);
    auto negative_option = op.add<Switch>("", "negative", "turn image into negative");

    //G options
    auto hflip_option = op.add<Switch>("", "hflip", "flip horizontally");
    auto vflip_option = op.add<Switch>("", "vflip", "flip vertically");
    auto dflip_option = op.add<Switch>("", "dflip", "flip diagonally (rotate by 180 degrees)");
    auto shrink_option = op.add<Value<float>>("", "shrink", "shrink image by a selected factor", 1.0);
    auto enlarge_option = op.add<Value<float>>("", "enlarge", "enlarge image by a selected factor", 1.0);

    //N options
    auto adaptive_option = op.add<Switch>("", "adaptive", "filter image using adaptive median filter");
    auto min_option = op.add<Switch>("", "min", "filter image using min filter");
    auto max_option = op.add<Switch>("", "max", "filter image using max filter");

    //E options
    auto mse_option = op.add<Switch>("", "mse", "calculate mean square error");
    auto pmse_option = op.add<Switch>("", "pmse", "calculate peak mean square error");
    auto snr_option = op.add<Switch>("", "snr", "calculate signal to noise ratio");
    auto psnr_option = op.add<Switch>("", "psnr", "calculate peak signal to noise ratio");
    auto md_option = op.add<Switch>("", "md", "calculate maximum difference between images");

    op.parse(argc, argv);

    // print auto-generated help message
    if (help_option->is_set()) std::cout << op << "\n";

    // show all non option arguments (those without "-o" or "--option")
    for (const auto& non_option_arg: op.non_option_args()) std::cout << "non_option_args: " << non_option_arg << "\n";

    // show unknown options (undefined ones, like "-u" or "--undefined")
    for (const auto& unknown_option: op.unknown_options()) std::cout << "unknown_options: " << unknown_option << "\n";

    CImg<unsigned char> inputImage;
    CImg<unsigned char> originalImage;
    const char *const input_image_path = argv[1];
    const char *const original_image_path = argv[2];
    try
    {
        inputImage = CImg(input_image_path);
    }
    catch (CImgIOException ex)
    {
        cout<<"input file does not exist, remember that first argument is name/path of input file";
    }
    if(mse_option->is_set() || pmse_option->is_set() || snr_option->is_set() || psnr_option->is_set() || md_option->is_set())
    {
        try
        {
            originalImage = CImg(original_image_path);
        }
        catch (CImgIOException ex)
        {
            cout<<"original image file does not exist, remember that in case of error calculations second argument is name/path of original image";
        }
    }

    //B options execution
    if(brightness_option->is_set()) brightnessModification(inputImage, brightness_option->value());
    if(contrast_option->is_set()) contrast(inputImage, contrast_option->value());
    if(negative_option->is_set()) negative(inputImage);

    //G options execution
    if(hflip_option->is_set()) horizontalFlip(inputImage);
    if(vflip_option->is_set()) verticalFlip(inputImage);
    if(dflip_option->is_set()) diagonalFlip(inputImage);
    if(shrink_option->is_set()) scale(inputImage, 1.0/shrink_option->value());
    if(enlarge_option->is_set()) scale(inputImage, enlarge_option->value());

    //N options execution
    if(adaptive_option->is_set()) adaptiveMedianFilter(inputImage);
    if(min_option->is_set()) minFilter(inputImage);
    if(max_option->is_set()) maxFilter(inputImage);

    //E options execution
    if(mse_option->is_set()) cout<<"Mean square error: "<<meanSquareError(inputImage, originalImage)<<endl;
    if(pmse_option->is_set()) cout<<"peak mean square error: "<<peakMeanSquareError(inputImage, originalImage)<<endl;
    if(snr_option->is_set()) cout<<"Signal to noise ratio: "<<signalToNoiseRatio(inputImage, originalImage)<<endl;
    if(psnr_option->is_set()) cout<<"Peak signal to noise ratio: "<<peakSignalToNoiseRatio(inputImage, originalImage)<<endl;
    if(md_option->is_set()) cout<<"Max difference: "<<maxDifference(inputImage, originalImage)<<endl;

    inputImage.save("..\\..\\img\\test\\out.bmp");

    return 0;
}