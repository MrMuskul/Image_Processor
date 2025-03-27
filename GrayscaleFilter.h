#pragma once
#include "Filter.h"

class GrayscaleFilter : public Filter {
public:
    void apply(Image& image) const override;
};