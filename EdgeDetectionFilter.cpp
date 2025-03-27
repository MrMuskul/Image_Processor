#include "EdgeDetectionFilter.h"
#include <stdexcept>

EdgeDetectionFilter::EdgeDetectionFilter(const std::vector<std::string>& params) {
    if (params.size() != 1) throw std::invalid_argument("Edge Detection requires 1 parameter");
    threshold_ = std::stod(params[0]);
}

void EdgeDetectionFilter::apply(Image& image) const {
    for (size_t y = 0; y < image.getHeight(); ++y) {
        for (size_t x = 0; x < image.getWidth(); ++x) {
            Pixel& p = image.at(x, y);
            double gray = 0.299 * p.r + 0.587 * p.g + 0.114 * p.b;
            p.r = p.g = p.b = gray;
        }
    }

    int matrix[3][3] = {
        { 0, -1,  0},
        {-1,  4, -1},
        { 0, -1,  0}
    };
    int matrixSize = 3;
    int offset = matrixSize / 2;

    std::vector<std::vector<Pixel>> newPixels(image.getHeight(), std::vector<Pixel>(image.getWidth()));

    for (size_t y = 0; y < image.getHeight(); ++y) {
        for (size_t x = 0; x < image.getWidth(); ++x) {
            double sum = 0.0;

            for (int dy = -offset; dy <= offset; ++dy) {
                for (int dx = -offset; dx <= offset; ++dx) {
                    int newX = static_cast<int>(x) + dx;
                    int newY = static_cast<int>(y) + dy;

                    if (newX < 0) newX = 0;
                    if (newX >= static_cast<int>(image.getWidth())) newX = image.getWidth() - 1;
                    if (newY < 0) newY = 0;
                    if (newY >= static_cast<int>(image.getHeight())) newY = image.getHeight() - 1;

                    const Pixel& p = image.at(newX, newY);
                    double weight = matrix[dy + offset][dx + offset];
                    sum += p.r * weight;
                }
            }

            Pixel& newPixel = newPixels[y][x];
            if (sum > threshold_) {
                newPixel.r = newPixel.g = newPixel.b = 1.0;
            } else {
                newPixel.r = newPixel.g = newPixel.b = 0.0;
            }
        }
    }

    for (size_t y = 0; y < image.getHeight(); ++y) {
        for (size_t x = 0; x < image.getWidth(); ++x) {
            image.at(x, y) = newPixels[y][x];
        }
    }
}