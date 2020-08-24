#include "Bitmap.hpp"
#include <fstream>
#include <iterator>
#include <utility>
#include <stdexcept>

namespace bitmap {

    Bitmap::Bitmap(const std::string& inputPath, const std::string& outputPath) 
        : BitAdjuster(std::move(readFileContent(inputPath))),
        _header(getData().substr(0,14)), _dibHeader(getData().substr(14,40)), 
        _bitmapArray(getData().substr(_header.getOffset()), getData().substr(54 , _header.getOffset() - 54),
        _dibHeader.getBitsPerPixel(), _dibHeader.getHeight(), _dibHeader.getWidth()), _outputPath(outputPath) {}

    void Bitmap::write() {
        // activing write() for all of the parts of the bitmap
        _header.write();
        _dibHeader.write();
        _bitmapArray.write();
        
        // setting the new data string to be the data string of the bitmap
        setData(_header.getData() + _dibHeader.getData()
        + _bitmapArray.getColorPallete().getData() + _bitmapArray.getData());

        // writing the new data string into the file
        writeFileContent(_outputPath, getData()); 
    }

    void Bitmap::turn() {
        // activing turn() for all of the parts of the bitmap
        _header.turn();
        _dibHeader.turn();
        _bitmapArray.turn();

        // writing the changes into the data string
        write();
    }

    void Bitmap::gray() {
        // activing gray() for bitmap array, because it is the only part
        // which is affected by the color changing to gray
        _bitmapArray.gray();

        // writing the changes into the data string
        write();
    }

    std::string Bitmap::readFileContent(const std::string& filePath) { 
        // opening the file
        std::ifstream in(filePath, std::ios::binary);

        // checking if an error has occured
        if (!in) {
            throw std::runtime_error("An error has occured while opening the file");
        }

        // reading the content from the file
        auto content = std::string{std::istreambuf_iterator<char>{in}, std::istreambuf_iterator<char>{}};

        return content;
    }

    void Bitmap::writeFileContent(const std::string& filePath, const std::string& content) {
        // opening the file
        std::ofstream out(filePath, std::ios::binary | std::ios::trunc);

        // checking if an error has occured
        if (!out) {
            throw std::runtime_error("An error has occured while opening the file");
        }

        // writing the content to the file
        out.write(content.data(), static_cast<std::streamsize>(content.length()));

        // checking if an error has occured
        if (!out) {
            throw std::runtime_error("An error has occured while writing to the file");
        }
    }

}