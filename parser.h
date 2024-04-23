#pragma once
#include <span>
#include <string>
#include "image.h"
#include "multifilter.h"

class ArgParser {
    struct Result {
        char *input_file;
        char *output_file;
        MultiFilter filters;
    };

public:
    explicit ArgParser(std::span<char *> args);

    Result Parse();

    class InvalidArguments : public std::exception {
    public:
        explicit InvalidArguments(const std::string &message);
        const char *what() const noexcept override;

    private:
        const std::string msg_;
    };

private:
    std::span<char *> args_;
};
