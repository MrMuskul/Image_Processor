#pragma once
#include "Image.h"
#include <string>

class BMPReader {
public:
    static Image read(const std::string& filename);
};