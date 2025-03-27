#pragma once
#include <vector>

struct Pixel {
    double r, g, b;
};

class Image {
public:
    Image(size_t width, size_t height);
    Pixel& at(size_t x, size_t y);
    const Pixel& at(size_t x, size_t y) const;
    size_t getWidth() const;
    size_t getHeight() const;

private:
    std::vector<std::vector<Pixel>> pixels_;
    size_t width_, height_;
};
