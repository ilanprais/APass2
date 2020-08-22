#pragma once
#include "BitAdjuster.hpp"
#include <string>

namespace bitmap {

class BitmapHeader : public BitAdjuster {
    // the file type, which is always 0x4D42
    uint16_t _fileType = 0x4D42; 
    // file size in bytes
    uint32_t _fileSize = 0;
    // reserved 
    uint16_t _reserved1 = 0;
    uint16_t _reserved2 = 0;
    // offset
    uint32_t _offset = 0;

    public:
        explicit BitmapHeader(std::string data);
        BitmapHeader() = default;

        BitmapHeader() = default;

        BitmapHeader(const BitmapHeader& other) = default;
        BitmapHeader& operator=(const BitmapHeader& other) = default;

        BitmapHeader(BitmapHeader&& other) noexcept = default;
        BitmapHeader& operator=(BitmapHeader&& other) noexcept = default;

        ~BitmapHeader() = default;

        void read() override;
        void write() override;

        void turn() override;
        void gray() override;

        uint32_t getOffset();

        void print();
};

}