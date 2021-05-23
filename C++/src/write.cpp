#include <cmath>
#include <fstream>
#include <vector>

#include "write.hpp"

void writeBitmap(std::ifstream &img, u32 size) {

    int width = std::sqrt(size/3);
    int height = width;
    char header_buffer[DEFAULT_HEADER_SIZE];

    BITMAP_FILE_HEADER *file = (BITMAP_FILE_HEADER*)header_buffer;
    BITMAP_INFO_HEADER *info = (BITMAP_INFO_HEADER*)(header_buffer + FILE_HEADER_SIZE);

    int stride = (width * 3 + 3) / 4 * 4;

    file->bfType = FILE_TYPE;
    file->bfSize = DEFAULT_HEADER_SIZE + stride * height;
    file->bfReserved1 = 0;
    file->bfReserved2 = 0;
    file->bfOffBits = DEFAULT_HEADER_SIZE;

    info->biSize = INFO_HEADER_SIZE;
    info->biWidth = width;
    info->biHeight = height;
    info->biPlanes = 1;
    info->biBitCount = 24;
    info->biCompression = 0;
    info->biSizeImage = stride * height;
    info->biXPixPerMeter = 0;
    info->biYPixPerMeter = 0;
    info->biClrUsed = 0;
    info->biClrImportant = 0;

    std::ofstream ofs("result.bmp", std::ios::binary);
    ofs.write(reinterpret_cast<const char*>(header_buffer), DEFAULT_HEADER_SIZE);

    std::vector<char> buffer(stride);

    for (int y = 0; y < height; ++y) {

        for (int x = 0; x < 3 * width; ++x)
            img.read(&buffer[x], sizeof(char));

        ofs.write(buffer.data(), stride);
    }
}