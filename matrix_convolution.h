#pragma once
#include "image.h"
#include "filter.h"
#include <array>

using Matrix3x3 = std::array<std::array<double, 3>, 3>;

template <Matrix3x3 Matrix>
class MatrixConvolution : public Filter {
public:
    void Apply(Image& image) override {
        Image image_copy = image;
        for (size_t x = 0; x != image.Width(); ++x) {
            for (size_t y = 0; y != image.Height(); ++y) {
                Color& result = image.At(x, y) = {0, 0, 0};
                for (ssize_t i = -1; i != 2; ++i) {
                    for (ssize_t j = -1; j != 2; ++j) {
                        size_t x_ind = x + i;
                        if (x_ind == static_cast<ssize_t>(-1) || x_ind == image.Width()) {
                            x_ind = x;
                        }
                        size_t y_ind = y + j;
                        if (y_ind == static_cast<ssize_t>(-1) || y_ind == image.Height()) {
                            y_ind = y;
                        }
                        result.Red += Matrix[i + 1][j + 1] * image_copy[x_ind][y_ind].Red;
                        result.Green += Matrix[i + 1][j + 1] * image_copy[x_ind][y_ind].Green;
                        result.Blue += Matrix[i + 1][j + 1] * image_copy[x_ind][y_ind].Blue;
                    }
                }
                result.Red = std::clamp(result.Red, 0.0, 1.0);
                result.Green = std::clamp(result.Green, 0.0, 1.0);
                result.Blue = std::clamp(result.Blue, 0.0, 1.0);
            }
        }
    }
};
