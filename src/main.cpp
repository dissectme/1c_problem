#include <fstream>
#include <iostream>
#include <string>

#include "image.hpp"
#include "scaneline.hpp"

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cout << "Criss-cross" << std::endl;
    std::cout << "Usage: " << argv[0] << " .PNG " << std::endl;

    return 0;
  }

  std::string filename(argv[1]);

  unsigned error = 0;
  auto img = Image::FromFile(filename, error).value();
  Field f(img);

  f.FindFigures();

  return 0;
}
