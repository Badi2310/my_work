#include <iostream>
#include <vector>

size_t FindAnswer(std::vector<int64_t>& vec) {
  size_t left_ind = 0;
  size_t right_ind = vec.size() - 1;
  int64_t answer = 0;
  while (left_ind < right_ind) {
    if (vec[left_ind] < vec[right_ind]) {
      size_t old_left_ind = left_ind;
      ++left_ind;
      while (left_ind < right_ind && vec[old_left_ind] >= vec[left_ind]) {
        ++left_ind;
      }
      for (size_t i = old_left_ind + 1; i < left_ind; ++i) {
        answer += vec[old_left_ind] - vec[i];
      }
    } else {
      size_t old_right_ind = right_ind;
      --right_ind;
      while (left_ind < right_ind && vec[old_right_ind] >= vec[right_ind]) {
        --right_ind;
      }
      for (size_t i = old_right_ind - 1; i > right_ind; --i) {
        answer += vec[old_right_ind] - vec[i];
      }
    }
  }
  return answer;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  size_t num;
  std::cin >> num;

  std::vector<int64_t> vec(num);

  for (size_t i = 0; i < num; ++i) {
    std::cin >> vec[i];
  }

  std::cout << FindAnswer(vec);
}
