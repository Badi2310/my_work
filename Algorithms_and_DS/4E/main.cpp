#include <algorithm>
#include <iostream>
#include <vector>

size_t FindMaxTwo(std::vector<size_t>& two_deg, std::vector<size_t>& logs,
                  size_t num) {
  two_deg.resize(num);
  logs.resize(num);
  size_t keeper = 1;
  size_t ans = 0;

  for (size_t i = 1; i < num; ++i) {
    if (keeper * 2 <= i) {
      keeper *= 2;
      ++ans;
    }
    two_deg[i] = keeper;
    logs[i] = ans;
  }
  return ans;
}

struct SparseTable {
  SparseTable(std::vector<int>& new_arr) {
    arr = new_arr;
    size_t size = FindMaxTwo(two_deg, logs, arr.size() + 1);
    vec.resize(size + 1);

    for (size_t i = 0; i < size + 1; ++i) {
      vec[i].resize(arr.size());
    }

    for (size_t j = 0; j < arr.size(); ++j) {
      vec[0][j] = std::make_pair(j, j);
    }
    size_t power = 1;
    for (size_t i = 1; i < size + 1; ++i) {
      BuildLayer(vec[i - 1], vec[i], power);
      power *= 2;
    }
  }

  int GetQuery(size_t left, size_t right) {
    size_t dist = right - left + 1;
    size_t deg = two_deg[dist];
    size_t log = logs[dist];

    if (dist == deg) {
      return arr[vec[log][left].second];
    }

    std::pair<size_t, size_t> chokopai =
        Func(vec[log][left], vec[log][right + 1 - deg]);
    return arr[chokopai.second];
  }

  std::pair<size_t, size_t> Func(std::pair<size_t, size_t> fir,
                                 std::pair<size_t, size_t> sec) {
    std::vector<std::pair<int, size_t>> array(4);
    array[0] = std::make_pair(arr[fir.first], fir.first);
    array[1] = std::make_pair(arr[fir.second], fir.second);
    array[2] = std::make_pair(arr[sec.first], sec.first);
    array[3] = std::make_pair(arr[sec.second], sec.second);
    std::sort(array.begin(), array.end());
    if (array[0].second == array[1].second) {
      if (array[0].second == array[2].second) {
        return std::make_pair(array[0].second, array[3].second);
      }
      return std::make_pair(array[0].second, array[2].second);
    }
    return std::make_pair(array[0].second, array[1].second);
  }

  void BuildLayer(std::vector<std::pair<size_t, size_t>>& source,
                  std::vector<std::pair<size_t, size_t>>& dest,
                  size_t distance) {
    for (size_t i = 0; i < dest.size(); ++i) {
      dest[i] =
          Func(source[i], source[std::min(i + distance, source.size() - 1)]);
    }
  }
  std::vector<int> arr;
  std::vector<std::vector<std::pair<size_t, size_t>>> vec;
  std::vector<size_t> two_deg;
  std::vector<size_t> logs;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
  int num;
  int m_num;
  std::cin >> num >> m_num;
  std::vector<int> vec(num);
  for (int i = 0; i < num; ++i) {
    std::cin >> vec[i];
  }
  SparseTable my_sp(vec);

  size_t left;
  size_t right;
  for (int i = 0; i < m_num; ++i) {
    std::cin >> left >> right;
    std::cout << my_sp.GetQuery(left - 1, right - 1) << "\n";
  }
}
