#include <filesystem>
#include <fstream>
#include <iostream>

#include "write.hpp"

namespace fs = std::filesystem;

int main(int argc, char *argv[]) {

    if(argc != 2) {
        std::cout << "error: invalid argument" << std::endl;
        return -1;
    }

    try {
        fs::path filepath = argv[1];
        int fileSize = fs::file_size(filepath);
        std::ifstream ifs(filepath, std::ios::binary);
        writeBitmap(ifs, fileSize);
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}