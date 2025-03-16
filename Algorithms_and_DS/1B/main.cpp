#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

namespace MagicNumbers {
const int kLogBase = 10;
}

void Solution(std::vector<double>& mandra, std::vector<double>& log_sums) {
  log_sums[0] = 0;
  double logs = log_sums[0];
  for (size_t i = 0; i < mandra.size(); ++i) {
    logs += std::log10(mandra[i]);
    log_sums[i + 1] = logs;
  }
}

int main() {
  int num;
  std::cin >> num;
  std::vector<double> mandra(num);
  for (int i = 0; i < num; ++i) {
    std::cin >> mandra[i];
  }
  std::vector<double> log_sums(num + 1);
  Solution(mandra, log_sums);

  int questions;
  std::cin >> questions;
  int left;
  int right;
  double degree;
  for (int i = 0; i < questions; ++i) {
    std::cin >> left >> right;
    degree =
        (log_sums[right + 1] - log_sums[left]) * (1.0 / (right - left + 1));
    std::cout << std::fixed << std::setprecision(MagicNumbers::kLogBase)
              << pow(MagicNumbers::kLogBase, degree) << "\n";
  }
}
