#include <algorithm>
#include <iostream>
#include <vector>

void Sort(std::vector<std::vector<int32_t>>& vec) {
  if (vec.size() <= 1) {
    return;
  }
  std::vector<std::vector<int32_t>> new_vec((vec.size() + 1) / 2);
  for (size_t index = 0; index < vec.size(); index += 2) {
    if (index + 1 < vec.size()) {
      std::merge(vec[index].begin(), vec[index].end(), vec[index + 1].begin(),
                 vec[index + 1].end(), std::back_inserter(new_vec[index / 2]));
    } else {
      new_vec[index / 2] = std::move(vec[index]);
    }
  }
  Sort(new_vec);
  vec = std::move(new_vec);
}

int main() {
  size_t k_num;
  std::cin >> k_num;
  std::vector<std::vector<int32_t>> vec(k_num);

  size_t in_size;
  for (size_t index = 0; index < k_num; ++index) {
    std::cin >> in_size;
    vec[index].resize(in_size);
    for (size_t in_index = 0; in_index < in_size; ++in_index) {
      std::cin >> vec[index][in_index];
    }
  }

  Sort(vec);
  for (size_t index = 0; index < vec[0].size(); ++index) {
    std::cout << vec[0][index] << ' ';
  }
}
