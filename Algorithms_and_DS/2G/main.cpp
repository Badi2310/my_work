#include <iostream>
#include <random>
#include <vector>

int64_t Partition(std::vector<int64_t>& vec, int64_t left, int64_t right) {
  std::random_device rd;
  std::mt19937 generator(rd());
  int64_t pivot = vec.at(left + (generator() % (right - left)));
  int64_t left_index = left;
  int64_t right_index = right;

  while (left_index <= right_index) {
    while (left_index < right && vec.at(left_index) < pivot) {
      ++left_index;
    }
    while (right_index > left && vec.at(right_index) > pivot) {
      --right_index;
    }
    if (left_index >= right_index) {
      break;
    }
    std::swap(vec.at(left_index), vec.at(right_index));
    ++left_index;
    --right_index;
  }
  return right_index;
}

void QuickSort(std::vector<int64_t>& vec, int64_t left, int64_t right) {
  if (left == right) {
    return;
  }
  int64_t integer = Partition(vec, left, right);
  QuickSort(vec, left, integer);
  QuickSort(vec, integer + 1, right);
}

int main() {
  int32_t num;
  std::cin >> num;
  std::vector<int64_t> vec(num);
  for (int32_t i = 0; i < num; ++i) {
    std::cin >> vec[i];
  }
  QuickSort(vec, 0, num - 1);
  for (int64_t answer : vec) {
    std::cout << answer << ' ';
  }
}
