//
// Created by Denis Ryapolov on 11.03.2023.
//

#include "Negative.h"
void Negative::Apply(Image& image) {
    for (size_t x = 0; x != image.Width(); ++x) {
        for (size_t y = 0; y != image.Height(); ++y) {
            image.At(x, y).Red = 1 - image.At(x, y).Red;
            image.At(x, y).Green = 1 - image.At(x, y).Green;
            image.At(x, y).Blue = 1 - image.At(x, y).Blue;
        }
    }
}