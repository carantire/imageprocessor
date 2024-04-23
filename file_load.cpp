//
// Created by Denis Ryapolov on 18.03.2023.
//
#include "image.h"
#include <fstream>
#include <numeric>
#pragma pack(push, 1)
struct BmpHeader {
    char id[2];
    uint32_t file_size;
    uint32_t unused;
    uint32_t offset;
};
struct DibHeader {
    uint32_t header_size;
    int32_t width;
    int32_t height;
    uint16_t plane_count;
    uint16_t bits_per_pixel;
    uint32_t compression;
    uint32_t bitmap_data_size;
    uint32_t horizontal_resolution;
    uint32_t vertical_resolution;
    uint32_t colors_in_palette;
    uint32_t important_colors;
};

struct RGB {
    uint8_t blue;
    uint8_t green;
    uint8_t red;
};
#pragma pack(pop)

Image Read(const char *file) {
    std::ifstream fstream(file, std::ios::binary);
    BmpHeader bmpheader;
    fstream.read(reinterpret_cast<char *>(&bmpheader), sizeof(bmpheader));
    DibHeader dibheader;
    fstream.read(reinterpret_cast<char *>(&dibheader), sizeof(dibheader));
    Image image(dibheader.width, dibheader.height);
    for (size_t y = 0; y < dibheader.height; ++y) {
        for (size_t x = 0; x < dibheader.width; ++x) {
            RGB rgb;
            fstream.read(reinterpret_cast<char *>(&rgb), sizeof(rgb));
            static constexpr auto ToDouble = [](uint8_t x) {
                return static_cast<double>(x) / std::numeric_limits<uint8_t>::max();
            };
            image.At(x, dibheader.height - y - 1) = {ToDouble(rgb.red), ToDouble(rgb.green), ToDouble(rgb.blue)};
        }
        fstream.ignore((4 - (3 * dibheader.width) % 4) % 4);
    }
    return image;
};

void Write(const char *file, const Image &image) {
    static constexpr uint16_t BitPerPixel = 24;
    std::ofstream ofstream(file, std::ios::binary);
    const uint32_t row_size = ((3 * image.Width() + 3) / 4) * 4;
    const uint32_t pixmap_size = row_size * image.Height();
    BmpHeader bmpheader = {{'B', 'M'},
                           static_cast<uint32_t>(sizeof(BmpHeader) + sizeof(DibHeader) + pixmap_size),
                           0,
                           sizeof(BmpHeader) + sizeof(DibHeader)};
    ofstream.write(reinterpret_cast<char *>(&bmpheader), sizeof(bmpheader));
    DibHeader dib_header = {sizeof(DibHeader),
                            static_cast<int32_t>(image.Width()),
                            static_cast<int32_t>(image.Height()),
                            1,
                            BitPerPixel,
                            0,
                            pixmap_size,
                            0,
                            0,
                            0,
                            0};
    ofstream.write(reinterpret_cast<char *>(&dib_header), sizeof(dib_header));
    for (size_t y = 0; y < image.Height(); ++y) {
        for (size_t x = 0; x < image.Width(); ++x) {
            RGB rgb = {
                .blue =
                    static_cast<uint8_t>(image[x][image.Height() - y - 1].Blue * std::numeric_limits<uint8_t>::max()),
                .green =
                    static_cast<uint8_t>(image[x][image.Height() - y - 1].Green * std::numeric_limits<uint8_t>::max()),
                .red = static_cast<uint8_t>(image[x][image.Height() - y - 1].Red * std::numeric_limits<uint8_t>::max())

            };
            ofstream.write(reinterpret_cast<char *>(&rgb), sizeof(rgb));
        }
        ofstream.write("\0\0", static_cast<std::streamsize>(row_size - 3 * image.Width()));
        ofstream.flush();
    }
    ofstream.close();
}