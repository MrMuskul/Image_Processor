#pragma once
#include "Filter.h"

class EdgeDetectionFilter : public Filter {
public:
    EdgeDetectionFilter(const std::vector<std::string>& params);
    void apply(Image& image) const override;

private:
    double threshold_;
};