#pragma once
#include "Filter.h"

class SharpeningFilter : public Filter {
public:
    void apply(Image& image) const override;
};