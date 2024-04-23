#include "image.h"
#include "crop.h"
Crop::Crop(size_t new_width, size_t new_height) : new_width_(new_width), new_height_(new_height){};
void Crop::Apply(Image& image) {
    image.Crop(new_width_, new_height_);
}