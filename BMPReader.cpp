#include "BMPReader.h"
#include <fstream>
#include <stdexcept>
#include <cstdint>

#pragma pack(push, 1)
struct BMPFileHeader {
    uint16_t signature;
    uint32_t fileSize;
    uint32_t reserved;
    uint32_t dataOffset;
};

struct BMPInfoHeader {
    uint32_t headerSize;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bitCount;
    uint32_t compression;
    uint32_t imageSize;
    int32_t xPixelsPerM;
    int32_t yPixelsPerM;
    uint32_t colorsUsed;
    uint32_t colorsImportant;
};
#pragma pack(pop)

Image BMPReader::read(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Cannot open input file: " + filename);
    }

    BMPFileHeader fileHeader;
    file.read(reinterpret_cast<char*>(&fileHeader), sizeof(BMPFileHeader));
    if (!file) {
        throw std::runtime_error("Failed to read BMP file header from: " + filename);
    }

    if (fileHeader.signature != 0x4D42) {
        throw std::runtime_error("Invalid BMP signature in file: " + filename);
    }

    BMPInfoHeader infoHeader;
    file.read(reinterpret_cast<char*>(&infoHeader), sizeof(BMPInfoHeader));
    if (!file) {
        throw std::runtime_error("Failed to read BMP info header from: " + filename);
    }

    if (infoHeader.headerSize != 40) {
        throw std::runtime_error("Unsupported BMP header type in file: " + filename);
    }
    if (infoHeader.bitCount != 24) {
        throw std::runtime_error("Only 24-bit BMP files are supported: " + filename);
    }
    if (infoHeader.compression != 0) {
        throw std::runtime_error("Compressed BMP files are not supported: " + filename);
    }

    size_t width = static_cast<size_t>(infoHeader.width);
    size_t height = static_cast<size_t>(infoHeader.height < 0 ? -infoHeader.height : infoHeader.height);
    bool bottomUp = (infoHeader.height > 0);

    Image image(width, height);

    size_t padding = (4 - (width * 3) % 4) % 4;
    size_t rowSize = width * 3 + padding;

    file.seekg(fileHeader.dataOffset, std::ios::beg);
    if (!file) {
        throw std::runtime_error("Failed to seek to pixel data in: " + filename);
    }

    std::vector<char> rowBuffer(rowSize);

    for (size_t y = 0; y < height; ++y) {
        file.read(rowBuffer.data(), rowSize);
        if (!file) {
            throw std::runtime_error("Failed to read pixel data from: " + filename);
        }

        size_t targetY = bottomUp ? (height - 1 - y) : y;

        for (size_t x = 0; x < width; ++x) {
            uint8_t b = static_cast<uint8_t>(rowBuffer[x * 3]);
            uint8_t g = static_cast<uint8_t>(rowBuffer[x * 3 + 1]);
            uint8_t r = static_cast<uint8_t>(rowBuffer[x * 3 + 2]);

            Pixel& pixel = image.at(x, targetY);
            pixel.r = r / 255.0;
            pixel.g = g / 255.0;
            pixel.b = b / 255.0;
        }
    }

    return image;
}