#pragma once
#include "filter.h"
#include <vector>
#include <memory>
class MultiFilter : public Filter {
public:
    void Apply(Image& image) override;
    void Append(Filter* new_filter);

private:
    std::vector<std::unique_ptr<Filter>> filters_;
};
