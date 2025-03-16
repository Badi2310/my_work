#include <algorithm>
#include <iostream>
#include <vector>

int FFunc(int index) { return (index & (index + 1)); }

int GFunc(int index) { return index | (index + 1); }

struct FenwickTree {
  explicit FenwickTree(int num) {
    vec.resize(num);
    for (int i = 0; i < num; ++i) {
      vec[i].resize(num);
      for (int j = 0; j < num; ++j) {
        vec[i][j].resize(num);
      }
    }
  }

  void Update(int x_cord, int y_cord, int z_cord, int k_val) {
    for (size_t i = x_cord; i < vec.size(); i = GFunc(i)) {
      for (size_t j = y_cord; j < vec.size(); j = GFunc(j)) {
        for (size_t t_i = z_cord; t_i < vec.size(); t_i = GFunc(t_i)) {
          vec[i][j][t_i] += k_val;
        }
      }
    }
  }

  int PrefSum(int x_cord, int y_cord, int z_cord) {
    int answer = 0;
    if (x_cord == -1 || y_cord == -1 || z_cord == -1) {
      return answer;
    }
    for (int i = x_cord; i >= 0; i = FFunc(i) - 1) {
      for (int j = y_cord; j >= 0; j = FFunc(j) - 1) {
        for (int t_i = z_cord; t_i >= 0; t_i = FFunc(t_i) - 1) {
          answer += vec[i][j][t_i];
        }
      }
    }
    return answer;
  }

  std::vector<std::vector<std::vector<int>>> vec;
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  int num;
  std::cin >> num;

  FenwickTree fen_t(num);
  int x_1;
  int x_2;
  int y_1;
  int y_2;
  int z_1;
  int z_2;
  int k_val;
  int indicator;
  int answer = 0;
  std::cin >> indicator;
  while (indicator != 3) {
    if (indicator == 1) {
      std::cin >> x_1 >> y_1 >> z_1 >> k_val;
      fen_t.Update(x_1, y_1, z_1, k_val);
    } else {
      std::cin >> x_1 >> y_1 >> z_1 >> x_2 >> y_2 >> z_2;

      answer += fen_t.PrefSum(x_2, y_2, z_2);
      answer -= fen_t.PrefSum(x_1 - 1, y_2, z_2);
      answer -= fen_t.PrefSum(x_2, y_1 - 1, z_2);
      answer -= fen_t.PrefSum(x_2, y_2, z_1 - 1);
      answer += fen_t.PrefSum(x_1 - 1, y_1 - 1, z_2);
      answer += fen_t.PrefSum(x_1 - 1, y_2, z_1 - 1);
      answer += fen_t.PrefSum(x_2, y_1 - 1, z_1 - 1);
      answer -= fen_t.PrefSum(x_1 - 1, y_1 - 1, z_1 - 1);
      std::cout << answer << "\n";
      answer = 0;
    }
    std::cin >> indicator;
  }
}
