//
// Created by Denis Ryapolov on 19.03.2023.
//

#include "edge.h"
Edge::Edge(double threshold) : threshold_(threshold) {
}
void Edge::Apply(Image &image) {
    GrayScale().Apply(image);
    MatrixConvolution::Apply(image);
    for (size_t x = 0; x < image.Width(); ++x) {
        for (size_t y = 0; y < image.Height(); ++y) {
            if (image.At(x, y).Red > threshold_) {
                image.At(x, y) = {1.0, 1.0, 1.0};
            } else {
                image.At(x, y) = {0.0, 0.0, 0.0};
            }
        }
    }
}