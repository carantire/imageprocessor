//
// Created by Denis Ryapolov on 19.03.2023.
//

#include "parser.h"
#include <iostream>
#include "crop.h"
#include "GrayScale.h"
#include "Sharpening.h"
#include "Negative.h"
#include "map"
#include "edge.h"
#include "Blur.h"
#include "Vignette.h"

ArgParser::ArgParser(std::span<char *> args) : args_(args) {
}
ArgParser::Result ArgParser::Parse() {
    if (args_.size() == 1) {
        std::cout << "CIMP: CLI image manipulation program" << std::endl;
        std::exit(0);
    }
    if (args_.size() == 2) {
        throw InvalidArguments("No image");
    }
    Result result = {args_[1], args_[2]};
    static const std::map<std::string, size_t> ARGSCOUNT = {{"-crop", 2}, {"-edge", 1},  {"-blur", 1}, {"-gs", 0},
                                                            {"-neg", 0},  {"-sharp", 0}, {"-vig", 3}};
    for (size_t i = 3; i < args_.size(); ++i) {
        const std::string filter_name = args_[i];
        if (!ARGSCOUNT.contains(filter_name)) {
            throw InvalidArguments("Unknown filter");
        }
        if (i + ARGSCOUNT.at(filter_name) >= args_.size()) {
            throw InvalidArguments("Not enough arguments for filter.");
        }
        if (filter_name == "-crop") {
            result.filters.Append(new Crop(std::stoi(args_[i + 1]), std::stoi(args_[i + 2])));
        } else if (filter_name == "-edge") {
            result.filters.Append(new Edge(std::stod(args_[i + 1])));
        } else if (filter_name == "-blur") {
            result.filters.Append(new Blur(std::stod(args_[i + 1])));
        } else if (filter_name == "-gs") {
            result.filters.Append(new GrayScale());
        } else if (filter_name == "-neg") {
            result.filters.Append(new Negative());
        } else if (filter_name == "-sharp") {
            result.filters.Append(new Sharpening());
        } else if (filter_name == "-vig") {
            result.filters.Append(
                new Vignette(std::stod(args_[i + 1]), std::stod(args_[i + 2]), std::stod(args_[i + 3])));
        }
        i += ARGSCOUNT.at(filter_name);
    }
    return result;
}
ArgParser::InvalidArguments::InvalidArguments(const std::string &message) : msg_(message) {
}

const char *ArgParser::InvalidArguments::what() const noexcept {
    return msg_.c_str();
}
