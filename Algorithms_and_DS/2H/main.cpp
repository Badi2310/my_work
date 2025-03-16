#include <iostream>
#include <vector>

namespace MagicNumbers {
const int32_t kConstF = 123;
const int32_t kConstS = 45;
const int32_t kBigNum = 10004321;
}  // namespace MagicNumbers

int32_t Partition(std::vector<int32_t>& vec, int32_t left, int32_t right) {
  int32_t pivot = vec.at(left + ((right - left) / 2));
  int32_t left_index = left;
  int32_t right_index = right;

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

int32_t KthStat(std::vector<int32_t>& vec, int32_t left, int32_t right,
                int32_t k_index) {
  int32_t index = Partition(vec, left, right);
  if (index > k_index) {
    return KthStat(vec, left, index, k_index);
  }
  if (index < k_index) {
    return KthStat(vec, index + 1, right, k_index);
  }
  return vec[index];
}

int main() {
  int32_t num;
  int32_t k_num;
  int32_t a_f;
  int32_t a_s;
  std::cin >> num >> k_num >> a_f >> a_s;

  std::vector<int32_t> vec(num);
  vec[0] = a_f;
  vec[1] = a_s;
  for (int32_t i_count = 2; i_count < num; ++i_count) {
    vec[i_count] = (vec[i_count - 1] * MagicNumbers::kConstF +
                    vec[i_count - 2] * MagicNumbers::kConstS) %
                   MagicNumbers::kBigNum;
  }

  std::cout << KthStat(vec, 0, num - 1, k_num - 1);

  return 0;
}
