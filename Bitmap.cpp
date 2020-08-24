#include "Bitmap.hpp"
#include <fstream>
#include <iterator>
#include <utility>

namespace bitmap {

    Bitmap::Bitmap(std::string path) 
        : BitAdjuster(std::move(readFromFile(path))), _path(std::move(path)),
        _header(getData().substr(0,14)), _dibHeader(getData().substr(14,40)), 
        _bitmapArray(getData().substr(_header.getOffset()), getData().substr(54 , _header.getOffset() - 54),
        _dibHeader.getBitsPerPixel(), _dibHeader.getHeight(), _dibHeader.getWidth()) {}

    void Bitmap::write(){
        
        // activing write() for all of the parts of the bitmap
        _header.write();
        _dibHeader.write();
        _bitmapArray.write();
        
        // setting the new data string to be the data string of the bitmap
        setData(_header.getData() + _dibHeader.getData()
        + _bitmapArray.getColorPallete().getData() + _bitmapArray.getData());

        // writing the new data string into the file
        writeFileContent(_path, getData()); 
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

    std::string readFileContent(const std::string& filePath) { 
        std::ifstream in(filePath, std::ios::binary);

        if (!in) {
        // Error here...
        }

        auto content = std::string{std::istreambuf_iterator<char>{in},
                             std::istreambuf_iterator<char>{}};

        if (!in.eof()) {
          // Unlikly to happen error here...
        }

        return content;
    }

    void writeFileContent(const std::string& filePath, const std::string& content) {
        std::ofstream out(filePath, std::ios::binary | std::ios::trunc);

        if (!out) {
          // Error here...
        }
  
        out.write(content.data(), static_cast<std::streamsize>(content.length()));
        if (!out) {
          // Unlikly to happen error here...
        }
    }
    
}