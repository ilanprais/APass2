#include "bmp_tester.hpp"
#include "Bitmap.hpp"

using namespace bitmap;

namespace testing {
namespace bmp {

void rotate_image(const std::string& imagePath, const std::string& outputPath) {
    Bitmap bitmap(imagePath, outputPath);
    bitmap.turn();
}

void convert_to_grayscale(const std::string& imagePath, const std::string& outputPath) {
    Bitmap bitmap(imagePath, outputPath);
    bitmap.gray();
}
}
}