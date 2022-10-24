#include <iostream>
#include "lib/popl.hpp"
#include "lib/CImg.h"
#include "task1/Task1B.cpp"
#include "task1/Task1G.cpp"
#include "task1/Task1E.cpp"
#include "task1/Task1N.cpp"


using namespace popl;

int main(int argc, char *argv[]) {

    OptionParser op("Allowed options");
    auto help_option     = op.add<Switch>("", "help", "produce help message");

    //input image
    auto input_option = op.add<Value<std::string>>("", "input-image", "provide name or path to input image [obligatory in case of all operations]", "");

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
    auto original_option = op.add<Value<std::string>>("", "original-image", "provide name or path to original image [obligatory in case of all error calculations]", "");
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

    if(input_option->is_set())
    {
        if(original_option->is_set())
        {
            std::cout<<input_option->value()<<"  "<<original_option->value();
        }
    }

    return 0;
}