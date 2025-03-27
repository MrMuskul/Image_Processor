#include "NegativeFilter.h"

void NegativeFilter::apply(Image& image) const {
    for (size_t y = 0; y < image.getHeight(); ++y) {
        for (size_t x = 0; x < image.getWidth(); ++x) {
            Pixel& p = image.at(x, y);
            p.r = 1.0 - p.r;
            p.g = 1.0 - p.g;
            p.b = 1.0 - p.b;
        }
    }
}