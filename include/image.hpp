#include <cassert>
#include <iostream>
#include <optional>
#include <vector>

#include "lodepng.h"

class Image {
 public:
  const unsigned height;
  const unsigned width;

  static std::optional<Image> FromFile(const std::string& filename,
                                       unsigned& error) {
    std::vector<unsigned char> image;
    unsigned width = 0, height = 0;
    error = lodepng::decode(image, width, height, filename.c_str());

    // if there's an error, display it
    if (error) {
      return std::nullopt;
    } else {
      return Image(std::move(image), width, height);
    }
  }

  bool IsBlackPixel(const unsigned x, const unsigned y) const {
    assert(x < width);
    assert(y < height);

    bool is_black = true;
    for (unsigned i = 0; i < 4; ++i)
      is_black &= image.at(y * width * 4 + x * 4 + i) > 0xDD;

    return is_black;
  }

  void SetBlackPixel(const unsigned x, const unsigned y) {
    assert(x < width);
    assert(y < height);

    for (unsigned i = 0; i < 3; ++i) {
      image.at(y * width * 4 + x * 4 + i) = 0x00;
    }
    image.at(y * width * 4 + x * 4 + 3) = 0xFF;
  }

  unsigned ToFile(const std::string& filename) const {
    return lodepng::encode(filename.c_str(), image, width, height);
  }

 private:
  Image(std::vector<unsigned char>&& image, unsigned width, unsigned height)
      : height(height), width(width), image(image) {}

  std::vector<unsigned char> image;
};
