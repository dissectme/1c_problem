#include <iostream>
#include <vector>

#include "lodepng.h"

class DecodeWrapper {
 public:
  DecodeWrapper(const std::string& filename) {
    unsigned error = lodepng::decode(image, width_, height_, filename);

    // if there's an error, display it
    if (error) {
      std::cout << "decoder error " << error << ": "
                << lodepng_error_text(error) << std::endl;
    }
  }

  std::vector<std::vector<char>> ConvertToMatrix() const {}

 private:
  bool IsBlackPixel(size_t x, size_t y) const {
    auto black_component = image.at(y * width_ * 4 + x * 4);
    if (black_component == 0xAA) {
      return true;
    }
    //    for (unsigned j = 150; j < 200; ++j)
    //      for (unsigned i = 0; i < width; ++i) {
    //        image.at(j * width * 4 + 4 * i) = 0xAA;
    //        image.at(j * width * 4 + 4 * i + 1) = 0x00;
    //        image.at(j * width * 4 + 4 * i + 2) = 0x00;
    //        image.at(j * width * 4 + 4 * i + 3) = 0xFF;
    //      }
  }

  std::vector<unsigned char> raw_image_;
  size_t height_ = 0;
  size_t width_ = 0;
};
