#include <iostream>
#include "lib/popl.hpp"
#include "lib/CImg.h"
#include "task1/Task1B.cpp"
#include "task1/Task1G.cpp"
#include "task1/Task1E.cpp"
#include "task1/Task1N.cpp"
#include "task2/Task2H.cpp"
#include "task2/Task2C.cpp"
#include "task2/Task2S.cpp"
#include "task2/Task2O.cpp"


using namespace popl;
using namespace std;

int main(int argc, char *argv[])
{
    OptionParser op("Allowed options");
    auto help_option= op.add<Switch>("h", "help", "produce help message");

    //B options
    auto brightness_option = op.add<Value<int>>("", "brightness", "brightness modification", 0);
    auto contrast_option = op.add<Value<int>>("", "contrast", "contrast modification", 0);
    auto negative_option = op.add<Switch>("", "negative", "turn image into negative");

    //G options
    auto hflip_option = op.add<Switch>("", "hflip", "flip horizontally");
    auto vflip_option = op.add<Switch>("", "vflip", "flip vertically");
    auto dflip_option = op.add<Switch>("", "dflip", "flip diagonally (rotate by 180 degrees)");
    auto shrink_option = op.add<Value<float>>("", "shrink", "shrink image by a selected factor", 1.0);
    auto enlarge_option = op.add<Value<int>>("", "enlarge", "enlarge image by a selected factor", 1.0);

    //N options
    auto adaptive_option = op.add<Switch>("", "adaptive", "filter image using adaptive median filter");
    auto min_option = op.add<Value<int>>("", "min", "filter image using min filter", 1);
    auto max_option = op.add<Value<int>>("", "max", "filter image using max filter", 1);

    //E options
    auto mse_option = op.add<Switch>("", "mse", "calculate mean square error");
    auto pmse_option = op.add<Switch>("", "pmse", "calculate peak mean square error");
    auto snr_option = op.add<Switch>("", "snr", "calculate signal to noise ratio");
    auto psnr_option = op.add<Switch>("", "psnr", "calculate peak signal to noise ratio");
    auto md_option = op.add<Switch>("", "md", "calculate maximum difference between images");

    //H options
    auto histogram_option = op.add<Value<int>>("", "histogram", "produce histogram");
    auto hhyper_option = op.add<Value<int>>("", "hhyper", "apply hyperbolic pdf");

    //C options
    auto cmean_option = op.add<Value<int>>("", "cmean", "calculate mean");
    auto cvariance_option = op.add<Value<int>>("", "cvariance", "calculate variance");
    auto cstdev_option = op.add<Value<int>>("", "cstdev", "calculate standard deviation");
    auto cvarcoi_option = op.add<Value<int>>("", "cvarcoi", "calculate deviation coefficient");
    auto casyco_option = op.add<Value<int>>("", "casyco", "calculate asymmetry coefficient");
    auto cfsyco_option = op.add<Value<int>>("", "cfsyco", "calculate flattening coefficient");
    auto cvarcoii_option = op.add<Value<int>>("", "cvarcoii", "calculate variation coefficient II");
    auto centropy_option = op.add<Value<int>>("", "centropy", "calculate information source entropy");

    op.parse(argc, argv);

    // print auto-generated help message
    if (help_option->is_set()) {
        std::cout << op << "\n";
        return 0;
    }

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

    bool save = false;

    //B options execution
    if(brightness_option->is_set()) {
        brightnessModification(inputImage, brightness_option->value());
        save = true;
    }
    if(contrast_option->is_set()) {
        contrast2(inputImage, contrast_option->value());
        save = true;
    }
    if(negative_option->is_set()) {
        negative(inputImage);
        save = true;
    }

    //G options execution
    if(hflip_option->is_set()) {
        horizontalFlip(inputImage);
        save = true;
    }
    if(vflip_option->is_set()) {
        verticalFlip(inputImage);
        save = true;
    }
    if(dflip_option->is_set()) {
        diagonalFlip(inputImage);
        save = true;
    }
    if(shrink_option->is_set()) {
        scale(inputImage, 1.0/shrink_option->value());
        save = true;
    }
    if(enlarge_option->is_set()) {
        scale(inputImage, enlarge_option->value());
        save = true;
    }

    //N options execution
    if(adaptive_option->is_set()) {
        adaptiveMedianFilter(inputImage);
        save = true;
    }
    if(min_option->is_set()) {
        minFilter(inputImage, min_option->value());
        save = true;
    }
    if(max_option->is_set()) {
        maxFilter(inputImage, max_option->value());
        save = true;
    }

    //E options execution
    if(mse_option->is_set()) cout<<"Mean square error: "<<meanSquareError(inputImage, originalImage)<<endl;
    if(pmse_option->is_set()) cout<<"Peak mean square error: "<<peakMeanSquareError(inputImage, originalImage)<<endl;
    if(snr_option->is_set()) cout<<"Signal to noise ratio: "<<signalToNoiseRatio(inputImage, originalImage)<<endl;
    if(psnr_option->is_set()) cout<<"Peak signal to noise ratio: "<<peakSignalToNoiseRatio(inputImage, originalImage)<<endl;
    if(md_option->is_set()) cout<<"Max difference: "<<maxDifference(inputImage, originalImage)<<endl;

    //H options execution
    if (histogram_option -> is_set()) {
        if (histogram_option -> value() >= 0 && histogram_option -> value() <= 2) {
            histogram(inputImage, histogram_option -> value());
        } else {
            std::cout << "Chanel value has to be between 0 and 2\n";
        }
    }
    if (hhyper_option -> is_set()) {
        if (hhyper_option -> value() >= 0 && hhyper_option -> value() <= 2) {
            //there could be a better way to get min and max
            int min, max;
            std::cout << "Minimal colour value: ";
            std::cin >> min;
            std::cout << "Maximal colour value: ";
            std::cin >> max;
            hyperbolicPDF(inputImage, hhyper_option -> value(), min, max);
        } else {
            std::cout << "Chanel value has to be between 0 and 2\n";
        }
    }

    //C options execution
    if(cmean_option->is_set()) cout<<"Mean: "<<mean(inputImage, cmean_option->value())<<endl;
    if(cvariance_option->is_set()) cout<<"Variance: "<<variance(inputImage, cvariance_option->value())<<endl;
    if(cstdev_option->is_set()) cout<<"Standard deviation: "<<deviation(inputImage, cstdev_option->value())<<endl;
    if(cvarcoi_option->is_set()) cout<<"Variation coefficient: "<<variationCoefficient(inputImage, cvarcoi_option->value())<<endl;
    if(casyco_option->is_set()) cout<<"Asymmetry coefficient: "<<asymmetryCoefficient(inputImage, casyco_option->value())<<endl;
    if(cfsyco_option->is_set()) cout<<"Flattening coefficient: "<<flatteningCoefficient(inputImage, cfsyco_option->value())<<endl;
    if(cvarcoii_option->is_set()) cout<<"Variation coefficient II: "<<variationCoefficientII(inputImage, cvarcoii_option->value())<<endl;
    if(centropy_option->is_set()) cout<<"Information source entropy: "<<entropy(inputImage, centropy_option->value())<<endl;


    if(save) {
        inputImage.save("out.bmp");
    }

    return 0;
}