#include "image.h"

Image::Image(size_t image_width, size_t image_height)
    : width_(image_width), height_(image_height), colors_(width_, std::vector<Color>(height_)) {
}

size_t Image::Height() const {
    return height_;
}

size_t Image::Width() const {
    return width_;
}

const std::vector<Color>& Image::operator[](size_t i) const {
    return colors_[i];
}
Color& Image::At(size_t x, size_t y) {
    return colors_[x][y];
};

void Image::Crop(size_t new_width, size_t new_height) {
    colors_.resize(new_width);
    for (size_t i = 0; i < new_height; ++i) {
        colors_[i].resize(new_height);
    }
    width_ = new_width;
    height_ = new_height;
}