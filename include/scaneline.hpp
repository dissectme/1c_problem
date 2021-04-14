#include <iostream>
#include <vector>

#include "image.hpp"

class Field {
 public:
  std::vector<size_t> ScanArea(int x_begin, int y_begin, int dx, int dy) {
    std::vector<size_t> x_sums(dx);
    for (int i = x_begin; i < x_begin + dx; i++) {
      //  _||_||_
      //  _||_||_
      //   || ||
      size_t x_sum = 0;
      for (int j = y_begin; j < y_begin + dy; j++) {
        if (image.IsBlackPixel(i, j)) {
          x_sum++;
        }
      }

      x_sums[i] = x_sum;
    }

    return x_sums;
  }

  std::vector<size_t> GetMaxConcentrationXes(const std::vector<size_t>& sums) {
    size_t max = 0;
    std::vector<size_t> xes;
    for (size_t i = 0; i < sums.size(); i++) {
      if (sums[i] > max) {
        max = sums[i];
        xes.clear();
        xes.push_back(i);
      } else if (sums[i] == max) {
        xes.push_back(i);
      }
    }
    return xes;
  }

  std::vector<size_t> CondenseXes(const std::vector<size_t>& max_xes) {
    size_t begin1 = 0, begin2 = 0, end1 = 0;
    for (size_t i = 0; i < max_xes.size(); i++) {
      if (max_xes[i + 1] != max_xes[i] + 1) {
        begin2 = max_xes[i + 1];
        end1 = max_xes[i];
      }
    }
    return {begin1, end1, begin2, begin2 + (end1 - begin1 + 1)};
  }

  std::vector<size_t> FindBorderY(size_t x) {
    size_t min_y = image.height - 1;

    while (!image.IsBlackPixel(x, min_y))
      ;

    size_t max_y = 0;
    while (!image.IsBlackPixel(x, max_y))
      ;

    return {min_y, max_y};
  }

  Field(const Image& img) : image{img} {
    auto x_sums = ScanArea(0, 0, image.width, image.height);
    auto x_max = GetMaxConcentrationXes(x_sums);
    auto x_condensed = CondenseXes(x_max);

    bar_width = x_condensed[1] - x_condensed[0] + 1;
    cell_width = (x_condensed[2] - x_condensed[1] - 1);

    size_t center_x = (x_condensed[1] + x_condensed[2]) / 2;
    auto y = FindBorderY(x_condensed[1]);
    size_t center_y = (y[0] + y[1]) / 2;

    center = {center_x, center_y};
  }

 private:
  size_t cell_width = 0, bar_width = 0;
  std::pair<size_t, size_t> center;
  const Image& image;
};
