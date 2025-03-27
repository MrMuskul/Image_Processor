#pragma once
#include "Filter.h"

class CropFilter : public Filter {
public:
    CropFilter(const std::vector<std::string>& params);
    void apply(Image& image) const override;

private:
    size_t width_, height_;
};