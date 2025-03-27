#include "CropFilter.h"
#include <stdexcept>

CropFilter::CropFilter(const std::vector<std::string>& params) {
    if (params.size() != 2) throw std::invalid_argument("Crop requires 2 parameters");
    width_ = std::stoul(params[0]);
    height_ = std::stoul(params[1]);
}

void CropFilter::apply(Image& image) const {
    size_t newWidth = std::min(width_, image.getWidth());
    size_t newHeight = std::min(height_, image.getHeight());
    std::vector<std::vector<Pixel>> newPixels(newHeight, std::vector<Pixel>(newWidth));

    for (size_t y = 0; y < newHeight; ++y) {
        for (size_t x = 0; x < newWidth; ++x) {
            newPixels[y][x] = image.at(x, y);
        }
    }

    image = Image(newWidth, newHeight);
    for (size_t y = 0; y < newHeight; ++y) {
        for (size_t x = 0; x < newWidth; ++x) {
            image.at(x, y) = newPixels[y][x];
        }
    }
}