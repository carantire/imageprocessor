#pragma once
#include "image.h"
#include "filter.h"
class Negative : public Filter {
public:
    void Apply(Image& image) override;
};
