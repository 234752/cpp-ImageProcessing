#include <iostream>
#include "lib/CImg.h"
#include "lib/popl.hpp"
#include "task1/Task1B.cpp"
#include "task1/Task1G.cpp"
#include "task1/Task1E.cpp"
#include "task1/Task1N.cpp"

using namespace std;
using namespace popl;

int main(int argc, char *argv[]) {

    OptionParser op("Allowed options");
    auto help_option     = op.add<Switch>("h", "help", "produce help message");
    auto string_option   = op.add<Value<string>>("s", "string", "test for string values");

    auto brightness_option = op.add<Value<int>>("b", "brightness", "brightness modification", 0);
    auto contrast_option = op.add<Value<int>>("c", "contrast", "contrast modification", 0);
    auto negative_option = op.add<Switch>("n", "negative", "turn image into negative");

    op.parse(argc, argv);

    // print auto-generated help message
    if (help_option->count() == 1) cout << op << "\n";
    else if (help_option->count() == 2) cout << op.help(Attribute::advanced) << "\n";
    else if (help_option->count() > 2) cout << op.help(Attribute::expert) << "\n";

    // show all non option arguments (those without "-o" or "--option")
    for (const auto& non_option_arg: op.non_option_args())
        cout << "non_option_args: " << non_option_arg << "\n";

    // show unknown options (undefined ones, like "-u" or "--undefined")
    for (const auto& unknown_option: op.unknown_options())
        cout << "unknown_options: " << unknown_option << "\n";

    // print all the configured values
    cout << "string_option   - is_set: " << string_option->is_set() << ", count: " << string_option->count() << "\n";
    if (string_option->is_set())
    {
        for (size_t n=0; n<string_option->count(); ++n)
            cout << "string_option #" << n << " - value: " << string_option->value(n) << "\n";
    }

    cout << "brightness   - is_set: " << brightness_option->is_set() << ", count: " << brightness_option->count() << ", value: " << brightness_option->value() << "\n";
    cout << "contrast   - is_set: " << contrast_option->is_set() << ", count: " << contrast_option->count() << ", value: " << contrast_option->value() << "\n";
    cout << "negative   - is_set: " << negative_option->is_set() << ", count: " << negative_option->count() << "\n";

    return 0;
}