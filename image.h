#pragma once

#include "color.h"

#include <cstdlib>
#include <vector>

class Image {
public:
    Image() = default;
    Image(size_t im_width, size_t im_height);

    size_t Height() const;
    size_t Width() const;

    Color& At(size_t x, size_t y);
    void Crop(size_t new_width, size_t new_height);
    const std::vector<Color>& operator[](size_t i) const;

private:
    size_t width_ = 0;
    size_t height_ = 0;
    std::vector<std::vector<Color>> colors_;
};