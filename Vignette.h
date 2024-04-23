#pragma once

#include "image.h"
#include "filter.h"
class Vignette : public Filter {
public:
    Vignette(double radius, double soft, double gamma);
    void Apply(Image& image) override;

private:
    double radius_;
    double softness_;
    double gamma_;
};
