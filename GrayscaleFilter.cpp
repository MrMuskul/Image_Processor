#include "GrayscaleFilter.h"

void GrayscaleFilter::apply(Image& image) const {
    for (size_t y = 0; y < image.getHeight(); ++y) {
        for (size_t x = 0; x < image.getWidth(); ++x) {
            Pixel& p = image.at(x, y);
            double gray = 0.299 * p.r + 0.587 * p.g + 0.114 * p.b;
            p.r = p.g = p.b = gray;
        }
    }
}