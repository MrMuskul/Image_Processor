#pragma once
#include "Filter.h"

class NegativeFilter : public Filter {
public:
    void apply(Image& image) const override;
};