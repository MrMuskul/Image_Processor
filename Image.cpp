#include "Image.h"
#include <stdexcept>

Image::Image(size_t width, size_t height) : width_(width), height_(height) {
    pixels_.resize(height, std::vector<Pixel>(width));
}

Pixel& Image::at(size_t x, size_t y) {
    if (x >= width_ || y >= height_) throw std::out_of_range("Pixel out of bounds");
    return pixels_[y][x];
}

const Pixel& Image::at(size_t x, size_t y) const {
    if (x >= width_ || y >= height_) throw std::out_of_range("Pixel out of bounds");
    return pixels_[y][x];
}

size_t Image::getWidth() const { return width_; }
size_t Image::getHeight() const { return height_; }