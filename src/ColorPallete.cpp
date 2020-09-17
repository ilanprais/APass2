#include "ColorPallete.hpp"

namespace bitmap {

ColorPallete::ColorPallete(std::string data) : BitAdjuster(std::move(data)) {
    // iterating over the data string and adding each color to the colors vector
    for (uint32_t i = 0; i < getData().size(); i += 4) {
        std::array<int, 3> color = {bytesToInteger<uint8_t>(i), bytesToInteger<uint8_t>(i + 1), bytesToInteger<uint8_t>(i + 2)};
        m_colors.push_back(color);
    }
}

void ColorPallete::write() {
    std::string result = "";
    // iterating over the colors and adding each color to the string
    for (std::size_t i = 0; i < m_colors.size(); ++i) {
        result += integerToBytes<uint8_t>(m_colors.at(i)[0]) + integerToBytes<uint8_t>(m_colors.at(i)[1])
        + integerToBytes<uint8_t>(m_colors.at(i)[2]) + integerToBytes<uint8_t>(0x00);
    }
    // setting the new data string
    setData(result);
}

void ColorPallete::addColor(int b, int g, int r) {
    // creating a new color and adding it to the colors vector
    std::array<int, 3> color = {b, g, r};
    m_colors.push_back(color);
}

std::array<int, 3> ColorPallete::getColor(uint32_t index) const {
    return m_colors.at(index);
}

void ColorPallete::turn() {}

void ColorPallete::gray() {
    // changing each color to its gray version
    for (std::size_t i = 0 ; i < m_colors.size() ; ++i) {
        uint32_t newColor =  0.2126 * m_colors.at(i)[2] + 0.7152 * m_colors.at(i)[1] + 0.0722 * m_colors.at(i)[0];
        m_colors.at(i)[2] = newColor;
        m_colors.at(i)[1] = newColor;
        m_colors.at(i)[0] = newColor;
    } 
}

}