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
#include "task3/Task3R.cpp"
#include "task3/Task3M.cpp"
#include "task4/Task4F.cpp"


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
    auto hhyper_option = op.add<Switch>("", "hhyper", "apply hyperbolic pdf");

    //C options
    auto cmean_option = op.add<Value<int>>("", "cmean", "calculate mean");
    auto cvariance_option = op.add<Value<int>>("", "cvariance", "calculate variance");
    auto cstdev_option = op.add<Value<int>>("", "cstdev", "calculate standard deviation");
    auto cvarcoi_option = op.add<Value<int>>("", "cvarcoi", "calculate deviation coefficient");
    auto casyco_option = op.add<Value<int>>("", "casyco", "calculate asymmetry coefficient");
    auto cfsyco_option = op.add<Value<int>>("", "cfsyco", "calculate flattening coefficient");
    auto cvarcoii_option = op.add<Value<int>>("", "cvarcoii", "calculate variation coefficient II");
    auto centropy_option = op.add<Value<int>>("", "centropy", "calculate information source entropy");

    //S options
    auto slowpass_option = op.add<Value<int>>("", "slowpass", "filter image using low pass filter");
    auto solowpass_option = op.add<Switch>("", "solowpass", "filter image using optimised low pass filter");

    //O option
    auto orobertsii_option = op.add<Switch>("", "orobertsii", "filter using Robert's operator II");
    auto okirsf_option = op.add<Switch>("", "okirsf", "filter using Kirsh Operator");

    //M options
    auto dilation_option = op.add<Switch>("", "dilation", "apply dilation");
    auto erosion_option = op.add<Switch>("", "erosion", "apply erosion");
    auto opening_option = op.add<Switch>("", "opening", "apply opening");
    auto closing_option = op.add<Switch>("", "closing", "apply closing");
    auto hmt_option = op.add<Switch>("", "hmt", "apply HMT transform");
    auto ch_option = op.add<Switch>("", "ch", "apply convex hull");

    //R option
    auto merging_option = op.add<Value<int>>("", "merging", "merge regions", 10);

    //T options
    auto dft_option = op.add<Switch>("", "dft", "discrete Fourier transform (slow)");
    auto fft_option = op.add<Switch>("", "fft", "fast Fourier transform (spatial domain)");

    //F options
    auto lowpass_option = op.add<Value<int>>("", "lowpass", "low-pass filter, (high-cut filter)");
    auto highpass_option = op.add<Value<int>>("", "highpass", "high-pass filter, (low-cut filter)");

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
        contrast(inputImage, contrast_option->value());
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
            //there could be a better way to get min and max
            int min, max;
            std::cout << "Minimal colour value: ";
            std::cin >> min;
            std::cout << "Maximal colour value: ";
            std::cin >> max;
            hyperPDF(inputImage, min, max);
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

    //S options execution
    if(slowpass_option->is_set()) {
        vector<int> mask;
        int maskValue;
        bool nonZero = false;
        for(int i = 0; i < pow(2 * slowpass_option -> value() + 1, 2); i++) {
            cout << "Mask (" << i / (2 * slowpass_option -> value() + 1) + 1 << ", "
                 << i % (2 * slowpass_option -> value() + 1) + 1 << ") : ";
            cin >> maskValue;
            if(maskValue > 0) {
                nonZero = true;
                mask.push_back(maskValue);
            } else if(maskValue == 0) {
                mask.push_back(maskValue);
            } else {
                cout << "Value cannot be lower than 0\n";
                i--;
            }
        }
        if(nonZero) {
            inputImage = lowPassFilter(inputImage, slowpass_option->value(), mask);
        } else {
            cout << "All mask values cannot be equal to 0\n";
        }
        save = true;
    }
    if(solowpass_option->is_set()) {
        inputImage = optimisedLowPassFilter(inputImage);
        save = true;
    }

    //O option execution
    if(orobertsii_option->is_set()) {
        robertOperator(inputImage);
        save = true;
    }

    if(okirsf_option->is_set()) {
        kirshOperator(inputImage);
        save = true;
    }

    //M options execution
    if(dilation_option->is_set()) {
        dilation(inputImage);
        save = true;
    }
    if(erosion_option->is_set()) {
        erosion(inputImage);
        save = true;
    }
    if(opening_option->is_set()) {
        opening(inputImage);
        save = true;
    }
    if(closing_option->is_set()) {
        closing(inputImage);
        save = true;
    }
    if(hmt_option->is_set()) {
        HMT(inputImage);
        save = true;
    }
    if(ch_option->is_set()) {
        oM4(inputImage);
        save = true;
    }

    //R option execution
    if(merging_option->is_set()) {
        int x, y;
        std::cout<<"\nX coordinate of starting pixel: ";
        std::cin>>x;
        std::cout<<"\nY coordinate of starting pixel: ";
        std::cin>>y;
        regionMerge(inputImage, x, y, merging_option->value());
        save = true;
    }

    //T options execution
    if(dft_option->is_set()) {
        DFT(inputImage, -1);
        save = true;
    }
    if(fft_option->is_set()) {
        FFT(inputImage, -1);
        save = true;
    }

    //F options execution
    if(lowpass_option->is_set()) {
//        lowPassFilter(inputImage, lowpass_option->value());
        CImg<unsigned char> mask = CImg("f1a.bmp");
        applyMask(inputImage, mask);
        save = true;
    }
    if(highpass_option->is_set()) {
//        highPassFilter(inputImage, highpass_option->value());
        CImg<unsigned char> mask = CImg("f2a.bmp");
        applyMask(inputImage, mask);
        save = true;
    }

    if(save) {
        inputImage.save("out.bmp");
    }

    return 0;
} // :)