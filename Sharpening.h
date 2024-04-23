#pragma once
#include "image.h"
#include "matrix_convolution.h"

static constexpr std::array<std::array<double, 3>, 3> SharpMatrix = {
    std::array{0.0, -1.0, 0.0}, {-1.0, 5.0, -1.0}, {0.0, -1.0, 0.0}};

using Sharpening = MatrixConvolution<SharpMatrix>;