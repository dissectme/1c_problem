#include <iostream>
#include <vector>

class Event {
 public:
 private:
};

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
        if (matrix_[i][j] == 1) {
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
    size_t begin1 = 0, begin2 = 0, end1 = 0, end2 = 0;
    for (size_t i = 0; i < max_xes.size(); i++) {
      if (max_xes[i + 1] != max_xes[i] + 1) {
        begin2 = max_xes[i + 1];
        end1 = max_xes[i];
      }
    }
    return {begin1, end1, begin2, begin2 + (end1 - begin1 + 1)};
  }

 private:
  using pixel = unsigned;
  std::vector<std::vector<pixel>> matrix_;
}
