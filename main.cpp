#include <iostream>

#include "ImageProcessor.h"

int main(int argc, char* argv[]) {
    try {
        ImageProcessor processor(argc, argv);
        processor.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}