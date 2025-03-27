#include "ImageProcessor.h"
#include "BMPReader.h"
#include "BMPWriter.h"
#include <iostream>

ImageProcessor::ImageProcessor(int argc, char* argv[]) {
    if (argc < 3) {
        printHelp();
        throw std::runtime_error("Invalid number of arguments");
    }
    inputFile_ = argv[1];
    outputFile_ = argv[2];

    for (int i = 3; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg[0] == '-') {
            std::string filterName = arg.substr(1);
            std::vector<std::string> params;
            while (i + 1 < argc && argv[i + 1][0] != '-') {
                params.push_back(argv[++i]);
            }
            filters_.push_back(Filter::create(filterName, params));
        }
    }
}

void ImageProcessor::run() {
    Image image = BMPReader::read(inputFile_);
    for (const auto* filter : filters_) {
        filter->apply(image);
    }
    BMPWriter::write(outputFile_, image);
}

void ImageProcessor::printHelp() const {
    std::cout << "Usage: ./image_processor input.bmp output.bmp [-filter1 [param1] ...] ..." << std::endl;
}
