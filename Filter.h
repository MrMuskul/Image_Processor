#pragma once
#include "Image.h"
#include <vector>
#include <string>

class Filter {
public:
    virtual void apply(Image& image) const = 0;
    virtual ~Filter() = default;
    static Filter* create(const std::string& name, const std::vector<std::string>& params);
};