//
// Created by Denis Ryapolov on 20.03.2023.
//

#include "Blur.h"
#include <numbers>
#include <cmath>

Blur::Blur(double sigma) : sigma_(sigma) {
    const size_t diameter = static_cast<size_t>(6 * sigma_ + 1) | 1;
    coefs_.resize(diameter);
    const double help_coef = 1 / std::sqrt(std::numbers::pi * 2 * sigma_ * sigma_);
    for (ssize_t x = 0; x < coefs_.size(); ++x) {
        coefs_[x] = help_coef * std::exp(-std::pow(x - static_cast<ssize_t>(diameter / 2), 2) / (2 * sigma_ * sigma_));
    }
}
void Blur::Apply(Image& image) {
    Image image_copy(image.Width(), image.Height());
    for (ssize_t x = 0; x < image.Width(); ++x) {
        for (ssize_t y = 0; y < image.Height(); ++y) {
            for (ssize_t i = -static_cast<ssize_t>(coefs_.size() / 2); i != coefs_.size() / 2 + 1; ++i) {
                ssize_t y_ind = y + i;
                double coef = coefs_[i + coefs_.size() / 2];
                if (y_ind < 0) {
                    y_ind = 0;
                } else if (y_ind >= image.Height()) {
                    y_ind = static_cast<ssize_t>(image.Height()) - 1;
                }
                image_copy.At(x, y).Red += coef * image.At(x, y_ind).Red;
                image_copy.At(x, y).Green += coef * image.At(x, y_ind).Green;
                image_copy.At(x, y).Blue += coef * image.At(x, y_ind).Blue;
            }
        }
    }
    image = Image(image.Width(), image.Height());
    for (ssize_t y = 0; y < image.Height(); ++y) {
        for (ssize_t x = 0; x < image.Width(); ++x) {
            for (ssize_t i = -static_cast<ssize_t>(coefs_.size() / 2); i != coefs_.size() / 2 + 1; ++i) {
                ssize_t x_ind = x + i;
                double coef = coefs_[i + coefs_.size() / 2];
                if (x_ind < 0) {
                    x_ind = 0;
                } else if (x_ind >= image.Height()) {
                    x_ind = static_cast<ssize_t>(image.Width()) - 1;
                }
                image.At(x, y).Red += coef * image_copy.At(x_ind, y).Red;
                image.At(x, y).Green += coef * image_copy.At(x_ind, y).Green;
                image.At(x, y).Blue += coef * image_copy.At(x_ind, y).Blue;
            }
        }
    }
}
