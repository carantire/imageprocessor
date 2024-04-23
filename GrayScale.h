#pragma once

#include "image.h"
#include "filter.h"
class GrayScale : public Filter {
public:
    void Apply(Image& image) override;
};
