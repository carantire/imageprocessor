#pragma once
#include "image.h"
#include "filter.h"

class Blur : public Filter {
public:
    explicit Blur(double sigma);
    void Apply(Image& image) override;

private:
    std::vector<double> coefs_;
    double sigma_;
};
