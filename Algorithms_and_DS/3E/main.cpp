#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

void Checker(int32_t& same_counter, bool was_equal, bool will_equal) {
  if (was_equal) {
    --same_counter;
  } else if (will_equal) {
    ++same_counter;
  }
}

int32_t SameCountFinder(size_t num, std::unordered_map<char, size_t>& small_map,
                        std::unordered_map<char, size_t>& big_map,
                        std::queue<char>& big_str) {
  int32_t same_counter = 0;
  for (size_t index = 0; index < num; ++index) {
    char letter;
    std::cin >> letter;
    bool was_equal = (small_map[letter] == big_map[letter]);
    ++big_map[letter];
    bool will_equal = (small_map[letter] == big_map[letter]);
    Checker(same_counter, was_equal, will_equal);
    big_str.push(letter);
  }
  return same_counter;
}

bool Helper(std::unordered_map<char, size_t>& small_map,
            std::unordered_map<char, size_t>& big_map,
            std::queue<char>& big_str, int32_t same_counter,
            int32_t diff_counter) {
  bool was_equal;
  bool will_equal;
  char letter;
  while (std::cin >> letter) {
    was_equal = (small_map[letter] == big_map[letter]);
    ++big_map[letter];
    will_equal = (small_map[letter] == big_map[letter]);
    Checker(same_counter, was_equal, will_equal);
    big_str.push(letter);

    was_equal = (small_map[big_str.front()] == big_map[big_str.front()]);
    --big_map[big_str.front()];
    will_equal = (small_map[big_str.front()] == big_map[big_str.front()]);
    Checker(same_counter, was_equal, will_equal);
    big_str.pop();
    if (same_counter == diff_counter) {
      return true;
    }
  }
  return false;
}

bool FindAnswer(std::string& small_str) {
  std::queue<char> big_str;
  std::unordered_map<char, size_t> small_map;
  std::unordered_map<char, size_t> big_map;
  int32_t diff_counter = 0;

  for (char letter : small_str) {
    if (small_map[letter] == 0) {
      ++diff_counter;
    }
    ++small_map[letter];
  }

  int32_t same_counter = 0;

  same_counter = SameCountFinder(small_str.size(), small_map, big_map, big_str);

  if (same_counter == diff_counter) {
    return true;
  }

  return Helper(small_map, big_map, big_str, same_counter, diff_counter);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::string small_str;
  std::cin >> small_str;

  if (FindAnswer(small_str)) {
    std::cout << "Yes";
  } else {
    std::cout << "No";
  }
}
