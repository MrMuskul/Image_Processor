#include "BMPWriter.h"
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

void BMPWriter::write(const std::string& filename, const Image& image) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Cannot open output file: " + filename);
    }

    size_t width = image.getWidth();
    size_t height = image.getHeight();

    size_t padding = (4 - (width * 3) % 4) % 4;
    size_t rowSize = width * 3 + padding;
    size_t dataSize = rowSize * height;

    BMPFileHeader fileHeader{};
    fileHeader.signature = 0x4D42;
    fileHeader.dataOffset = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader);
    fileHeader.fileSize = fileHeader.dataOffset + dataSize;
    fileHeader.reserved = 0;

    BMPInfoHeader infoHeader{};
    infoHeader.headerSize = sizeof(BMPInfoHeader);
    infoHeader.width = static_cast<int32_t>(width);
    infoHeader.height = static_cast<int32_t>(height);
    infoHeader.planes = 1;
    infoHeader.bitCount = 24;
    infoHeader.compression = 0;
    infoHeader.imageSize = static_cast<uint32_t>(dataSize);
    infoHeader.xPixelsPerM = 0;
    infoHeader.yPixelsPerM = 0;
    infoHeader.colorsUsed = 0;
    infoHeader.colorsImportant = 0;

    file.write(reinterpret_cast<const char*>(&fileHeader), sizeof(BMPFileHeader));
    file.write(reinterpret_cast<const char*>(&infoHeader), sizeof(BMPInfoHeader));

    if (!file) {
        throw std::runtime_error("Failed to write BMP headers to: " + filename);
    }

    std::vector<char> rowBuffer(rowSize, 0);

    for (size_t y = 0; y < height; ++y) {
        size_t targetY = height - 1 - y;
        for (size_t x = 0; x < width; ++x) {
            const Pixel& pixel = image.at(x, targetY);
            rowBuffer[x * 3] = static_cast<char>(pixel.b * 255.0);
            rowBuffer[x * 3 + 1] = static_cast<char>(pixel.g * 255.0);
            rowBuffer[x * 3 + 2] = static_cast<char>(pixel.r * 255.0);
        }
        file.write(rowBuffer.data(), rowSize);
        if (!file) {
            throw std::runtime_error("Failed to write pixel data to: " + filename);
        }
    }
}