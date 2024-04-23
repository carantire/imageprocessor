#include <iostream>
#include "parser.h"
#include "file_load.h"

int main(int argc, char** argv) try {
    ArgParser parser({argv, static_cast<size_t>(argc)});
    auto [input_file, output_file, filters] = parser.Parse();
    Image image = Read(input_file);
    filters.Apply(image);
    Write(output_file, image);
    return 0;
} catch (const ArgParser::InvalidArguments& e) {
    std::cout << "Error: " << e.what() << std::endl;
}
