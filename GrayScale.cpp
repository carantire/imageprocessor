//
// Created by Denis Ryapolov on 11.03.2023.
//

#include "GrayScale.h"
void GrayScale::Apply(Image &image) {
    static constexpr double RedCoef = 0.299;
    static constexpr double GreenCoef = 0.587;
    static constexpr double BlueCoef = 0.114;
    for (size_t x = 0; x != image.Width(); ++x) {
        for (size_t y = 0; y != image.Height(); ++y) {
            double new_color =
                RedCoef * (image.At(x, y).Red) + GreenCoef * (image.At(x, y).Green) + BlueCoef * (image.At(x, y).Blue);
            image.At(x, y) = {new_color, new_color, new_color};
        }
    }
}