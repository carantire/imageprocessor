//
// Created by Denis Ryapolov on 26.03.2023.
//

#include "Vignette.h"
#include <numbers>
#include <cmath>

Vignette::Vignette(double radius, double softness, double gamma) : radius_(radius), softness_(softness), gamma_(gamma) {
}
void Vignette::Apply(Image& image) {
    for (size_t x = 0; x < image.Width(); ++x) {
        for (size_t y = 0; y < image.Height(); ++y) {
            const auto center_x_dist =
                1 - 2 * static_cast<double>(std::min(x, image.Width() - x - 1)) / static_cast<double>(image.Width());
            const auto center_y_dist =
                1 - 2 * static_cast<double>(std::min(y, image.Height() - y - 1)) / static_cast<double>(image.Height());
            const auto center_dist = std::hypot(center_x_dist, center_y_dist);
            if (center_dist >= radius_) {
                image.At(x, y) = {0, 0, 0};
            } else if (center_dist >= radius_ * softness_) {
                const double coef = std::pow((radius_ - center_dist) / (radius_ - radius_ * softness_), gamma_);
                image.At(x, y) = {image.At(x, y).Red * coef, image.At(x, y).Green * coef, image.At(x, y).Blue * coef};
            }
        }
    }
}
