#pragma once
#include "Filter.h"
#include <vector>
#include <string>

class ImageProcessor {
public:
    ImageProcessor(int argc, char* argv[]);
    void run();

private:
    std::string inputFile_, outputFile_;
    std::vector<Filter*> filters_;
    void printHelp() const;
};