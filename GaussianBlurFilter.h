#pragma once
#include "Filter.h"

class GaussianBlurFilter : public Filter {
public:
    GaussianBlurFilter(const std::vector<std::string>& params);
    void apply(Image& image) const override;

private:
    double sigma_;
};