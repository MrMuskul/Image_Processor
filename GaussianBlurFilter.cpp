#include "GaussianBlurFilter.h"
#include <stdexcept>
#include <cmath>
#include <vector>

GaussianBlurFilter::GaussianBlurFilter(const std::vector<std::string>& params) {
    if (params.size() != 1) throw std::invalid_argument("Gaussian Blur requires 1 parameter");
    sigma_ = std::stod(params[0]);
    if (sigma_ <= 0) throw std::invalid_argument("Sigma must be positive");
}

void GaussianBlurFilter::apply(Image& image) const {
    int radius = static_cast<int>(std::ceil(3 * sigma_));
    int matrixSize = 2 * radius + 1;
    int offset = matrixSize / 2;

    std::vector<std::vector<double>> kernel(matrixSize, std::vector<double>(matrixSize));
    double sum = 0.0;
    double sigma2 = 2 * sigma_ * sigma_;
    double coeff = 1.0 / (2 * M_PI * sigma_ * sigma_);

    for (int dy = -offset; dy <= offset; ++dy) {
        for (int dx = -offset; dx <= offset; ++dx) {
            double value = coeff * std::exp(-(dx * dx + dy * dy) / sigma2);
            kernel[dy + offset][dx + offset] = value;
            sum += value;
        }
    }

    for (int y = 0; y < matrixSize; ++y) {
        for (int x = 0; x < matrixSize; ++x) {
            kernel[y][x] /= sum;
        }
    }

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
                    double weight = kernel[dy + offset][dx + offset];
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