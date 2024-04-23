#pragma once

#include "image.h"
#include "filter.h"

class Crop : public Filter {
public:
    Crop(size_t new_width, size_t new_height);
    void Apply(Image& image) override;

private:
    size_t new_width_;
    size_t new_height_;
};
