#include <iostream>
#include <vector>

#include "image.hpp"

using point = std::pair<size_t, size_t>;
point operator+(const point& a, const point& b) {
  return point{a.first + b.first, a.second + b.second};
}

class Field {
 public:
  std::vector<size_t> ScanArea(int x_begin, int y_begin, int dx, int dy) {
    std::vector<size_t> x_sums(dx);
    for (int i = x_begin; i < x_begin + dx - 10; i++) {
      //  _||_||_
      //  _||_||_
      //   || ||
      size_t x_sum = 0;
      for (int j = y_begin; j < y_begin + dy - 10; j++) {
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
    size_t begin1 = max_xes[0], begin2 = 0, end1 = 0;
    for (size_t i = 0; i < max_xes.size() - 1; i++) {
      if (max_xes[i + 1] != max_xes[i] + 1) {
        begin2 = max_xes[i + 1];
        end1 = max_xes[i];
      }
    }
    return {begin1, end1, begin2, max_xes.back()};
  }

  std::vector<size_t> FindBorderY(size_t x) {
    size_t min_y = image.height - 1;

    while (!image.IsBlackPixel(x, min_y--))
      ;

    size_t max_y = 0;
    while (!image.IsBlackPixel(x, max_y++))
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

  auto DetectFigure(point a) {
    size_t x_begin = a.first, y_begin = a.second;
    if (image.IsBlackPixel(x_begin + cell_width / 2,
                           y_begin + cell_width / 2)) {
      return 1;  // cross
    }

    auto x_sum = ScanArea(x_begin, y_begin, cell_width, cell_width);
    if (x_sum[x_sum.size() / 2] != 0) {
      return -1;  // circle
    } else {
      return 0;
    }
  }

  void FindFigures() {
    for (int i = -1; i <= 1; i++) {
      for (int j = -1; j <= 1; j++) {
        size_t delta = cell_width + bar_width;
        point current_center = center + point{i * delta, j * delta};

        figures[i + 1][j + 1] = DetectFigure(
            current_center + point{-cell_width / 2, -cell_width / 2});
        std::cout << figures[i + 1][j + 1] << " " << std::endl;
      }
      std::cout << std::endl;
    }
  }

 private:
  size_t cell_width = 0, bar_width = 0;
  using point = std::pair<size_t, size_t>;
  std::pair<size_t, size_t> center;
  int figures[3][3];
  const Image& image;
};

