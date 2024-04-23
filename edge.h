#pragma once
#include "image.h"
#include "matrix_convolution.h"
#include "GrayScale.h"

static constexpr std::array<std::array<double, 3>, 3> EdgeMatrix = {
    std::array{0.0, -1.0, 0.0}, {-1.0, 4.0, -1.0}, {0.0, -1.0, 0.0}};

class Edge : public MatrixConvolution<EdgeMatrix> {
public:
    explicit Edge(double threshold);
    void Apply(Image& image) override;

private:
    double threshold_;
};
