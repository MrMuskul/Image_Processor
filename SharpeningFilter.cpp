#include "SharpeningFilter.h"

void SharpeningFilter::apply(Image& image) const {
    int matrix[3][3] = {
        {0, -1, 0},
        {-1,  5, -1},
        {0, -1, 0    }
    };
    int matrixSize = 3;
    int offset = matrixSize / 2;

    std::vector<std::vector<Pixel>> newPixels(image.getHeight(), std::vector<Pixel>(image.getWidth()));

    for (size_t y = 0; y < image.getHeight(); ++y) {
        for (size_t x = 0; x < image.getWidth(); ++x) {
            double rSum = 0.0, gSum = 0.0, bSum = 0.0;

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
                    rSum += p.r * weight;
                    gSum += p.g * weight;
                    bSum += p.b * weight;
                }
            }

            Pixel& newPixel = newPixels[y][x];
            newPixel.r = std::min(1.0, std::max(0.0, rSum));
            newPixel.g = std::min(1.0, std::max(0.0, gSum));
            newPixel.b = std::min(1.0, std::max(0.0, bSum));
        }
    }

    for (size_t y = 0; y < image.getHeight(); ++y) {
        for (size_t x = 0; x < image.getWidth(); ++x) {
            image.at(x, y) = newPixels[y][x];
        }
    }
}