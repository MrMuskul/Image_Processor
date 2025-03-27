#pragma once
#include "Image.h"
#include <string>

class BMPWriter {
public:
    static void write(const std::string& filename, const Image& image);
};
