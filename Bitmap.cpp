#include "Bitmap.hpp"
#include "BitAdjuster.hpp"
#include <fstream>
#include <iterator>
#include <utility>

namespace bitmap {

    Bitmap::Bitmap(std::string path) : BitAdjuster(std::move(readFromFile(path))) {
        read();
    }

    Bitmap::Bitmap(const Bitmap& other) : BitAdjuster(other) {
        this->_header = new BitmapHeader(other._header);
        this->_dibHeader = new BitmapDIBHeader(other._dibHeader);
        this->_bitmapArray = new BitmapArray(other._bitmapArray);
        this->_colorPallete = new ColorPallete(other._colorPallete);
    }

    Bitmap& Bitmap::operator=(const Bitmap& other) {
        if (this == &other) {
		    return *this;
	    }

        reset();

        *this = Bitmap(other); 
	    return *this;
    }

    Bitmap::Bitmap(Bitmap&& other) noexcept : BitAdjuster(std::move(other)) {
        other.setData(nullptr);
        _header = std::exchange(other._header, nullptr);
        _dibHeader = std::exchange(other._dibHeader, nullptr);
        _bitmapArray = std::exchange(other._bitmapArray, nullptr);
        _colorPallete = std::exchange(other._colorPallete, nullptr);
    }

    Bitmap& Bitmap::operator=(Bitmap&& other) noexcept {
        if (this == &other) {
		    return *this;
	    }

	    reset();
        
        this->setData(std::move(other.getData()));
        other.setData(nullptr);
        _header = std::exchange(other._header, nullptr);
        _dibHeader = std::exchange(other._dibHeader, nullptr);
        _bitmapArray = std::exchange(other._bitmapArray, nullptr);
        _colorPallete = std::exchange(other._colorPallete, nullptr);
        return *this;
    }

    Bitmap::~Bitmap() {
        try {
		    reset();
	    }
	    catch (...) {

	    }
    }

    /**
     * @brief This method reads the .bmp file and cuts it to sections
     * according to the 4 parts, and builds the 4 parts.
     * 
     */
    void Bitmap::read(){
        this->_header = new BitmapHeader(content.substr(0,14));
        this->_dibHeader = new BitmapDIBHeader(content.substr(14,40));
        this->_bitmapArray = new BitmapArray(content.substr(this->_header.getOffset()));
        this->_colorPallete = new ColorPallete(content.substr(54 , this->_header.getOffset() - 54)); 
        //return nullptr in color pallete if the substr size is 0 or less.
    }

    /**
     * @brief This method writes the given 4 parts into
     * one whole .bmp file.
     * 
     */
    void Bitmap::write(){

        //NEED TO IMPLEMENT
    }

    /**
     * @brief This method turns the bitmap 90 degrees.
     * 
     */
    void Bitmap::turn(){
        _header->turn();
        _dibHeader->turn();
        _bitmapArray->turn();
        if( _colorPallete != nullptr){
            _colorPallete -> turn();
        }
        write();
    }

    /**
     * @brief This method changes the .bmp image to 
     * gray shade colors.
     * 
     */
    void Bitmap::gray(){
        _header->gray();
        _dibHeader->gray();
        _bitmapArray->gray();
        if( _colorPallete != nullptr){
            _colorPallete -> gray();
        }
        write();
    }

    void Bitmap::reset() noexcept {
        delete &getData();
        delete _header;
        delete _dibHeader;
        delete _bitmapArray;
        delete _colorPallete;
    }

    std::string readFileContent(const std::string& filePath) { 
        // Opens input-only file (ifstream) in binary mode.
        std::ifstream in(filePath, std::ios::binary);

        // The file is in a bad state. The error can be retrieved
        //	using the global `errno` in linux (#include <cerrno>).
        if (!in) {
        // Error here...
        }

        // Read the file to a vector. This is not the most effecient
        //	method to read a file.
        auto content = std::string{std::istreambuf_iterator<char>{in},
                             std::istreambuf_iterator<char>{}};

        // After reading the file, it should meet EOF (end of file). If
        //  it did not, it means that an error occurred.
        if (!in.eof()) {
          // Unlikly to happen error here...
        }

        return content;
    }

    void writeFileContent(const std::string& filePath, const std::string& content) {
        // Opens output-only file (ofstream) in binary mode, and truncates all
        //    existing content from the file.
        std::ofstream out(filePath, std::ios::binary | std::ios::trunc);

        // The file is in a bad state.
        if (!out) {
          // Error here...
        }
  
        out.write(content.data(), static_cast<std::streamsize>(content.length()));
        if (!out) {
          // Unlikly to happen error here...
        }
    }
    
}