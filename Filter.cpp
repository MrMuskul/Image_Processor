#include "Filter.h"
#include "GrayscaleFilter.h"
#include "CropFilter.h"
#include "NegativeFilter.h"
#include "SharpeningFilter.h"
#include "EdgeDetectionFilter.h"
#include "GaussianBlurFilter.h"

Filter* Filter::create(const std::string& name, const std::vector<std::string>& params) {
    if (name == "gs") return new GrayscaleFilter();
    if (name == "crop") return new CropFilter(params);
    if (name == "neg") return new NegativeFilter();
    if (name == "sharp") return new SharpeningFilter();
    if (name == "edge") return new EdgeDetectionFilter(params);
    if (name == "blur") return new GaussianBlurFilter(params);
    throw std::invalid_argument("Unknown filter: " + name);
}