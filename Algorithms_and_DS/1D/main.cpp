#include <algorithm>
#include <iostream>
#include <vector>

bool CheckIfSuits(int num, int count, int length,
                  const std::vector<int>& coords) {
  int border = coords[0] + length;
  --count;
  for (int i = 1; i < num; ++i) {
    if (coords[i] >= border) {
      --count;
      border = coords[i] + length;
    }
    if (count == 0) {
      return true;
    }
  }
  return false;
}

int FindLength(int num, int count, const std::vector<int>& coords, int left,
               int right) {
  if (right - left <= 1) {
    if (CheckIfSuits(num, count, right, coords)) {
      return right;
    }
    return left;
  }
  if (CheckIfSuits(num, count, left + (right - left) / 2, coords)) {
    return FindLength(num, count, coords, left + (right - left) / 2, right);
  }
  return FindLength(num, count, coords, left, left + (right - left) / 2);
}

int main() {
  int num;
  int count;
  std::cin >> num >> count;
  std::vector<int> coords(num);
  for (int i = 0; i < num; ++i) {
    std::cin >> coords[i];
  }

  std::cout << FindLength(num, count, coords, 0, (coords[num - 1] - coords[0]));
}
