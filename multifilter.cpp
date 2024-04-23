//
// Created by Denis Ryapolov on 19.03.2023.
//

#include "multifilter.h"
void MultiFilter::Append(Filter* new_filter) {
    filters_.emplace_back(new_filter);
}
void MultiFilter::Apply(Image& image) {
    for (const auto& filter : filters_) {
        filter->Apply(image);
    }
}
