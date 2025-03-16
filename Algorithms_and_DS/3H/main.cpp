#include <iostream>
#include <vector>

void Helper(size_t& answer, char sign_first, char sign_second, size_t& first,
            size_t& second) {
  if (sign_first == sign_second) {
    ++first;
  } else {
    ++second;
  }
  if (first < second) {
    first = 0;
    second = 0;
    return;
  }
  if (first == second) {
    answer = std::max(answer, 2 * first);
  }
}

size_t FindAnswer(std::string& vec) {
  size_t open_count = 0;
  size_t close_count = 0;
  size_t answer = 0;
  for (size_t index = 0; index < vec.size(); ++index) {
    Helper(answer, vec[index], '(', open_count, close_count);
  }
  open_count = 0;
  close_count = 0;
  for (size_t index = vec.size(); index > 0; --index) {
    Helper(answer, vec[index - 1], ')', close_count, open_count);
  }
  return answer;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::string str;
  std::cin >> str;

  std::cout << FindAnswer(str);
}
