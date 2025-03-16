#include <algorithm>
#include <iostream>
#include <vector>

class Heap {
 public:
  Heap() = default;

  void Insert(const std::pair<int64_t, int64_t>& elem) {
    data.push_back(elem);
    ans.push_back(data.size() - 1);
    SiftUp(data.size() - 1);
  }

  int64_t GetMin() {
    ans.push_back(0);
    return data.at(0).first;
  }

  void ExtractMin() {
    std::swap(data.at(0), data.at(data.size() - 1));
    std::swap(ans.at(data.at(0).second),
              ans.at(data.at(data.size() - 1).second));
    data.pop_back();
    if (!data.empty()) {
      SiftDown(0);
    }
    ans.push_back(0);
  }

  void DecreaseMin(size_t index, int64_t value) {
    ans.push_back(0);
    data.at(ans.at(index)).first -= value;
    SiftUp(ans.at(index));
  }

  size_t Size() const { return data.size(); }

  void SiftUp(size_t index) {
    if (index == 0 || data.at((index - 1) / 2).first < data.at(index).first) {
      return;
    }
    std::swap(data.at((index - 1) / 2), data.at(index));
    std::swap(ans.at(data.at((index - 1) / 2).second),
              ans.at(data.at(index).second));
    SiftUp((index - 1) / 2);
  }

  void SiftDown(size_t index) {
    const size_t kLeftChildIndex = (index * 2) + 1;
    const size_t kRightChildIndex = (index * 2) + 2;
    size_t min_child_index = kLeftChildIndex;

    const bool kLeftExistence = kLeftChildIndex <= data.size() - 1;
    const bool kRightExistence = kRightChildIndex <= data.size() - 1;

    if (kLeftExistence && kRightExistence) {
      if (data.at(kLeftChildIndex).first > data.at(kRightChildIndex).first) {
        min_child_index = kRightChildIndex;
      }
    } else if (!kLeftExistence) {
      return;
    }

    if (data.at(index).first <= data.at(min_child_index).first) {
      return;
    }

    std::swap(data.at(index), data.at(min_child_index));
    std::swap(ans.at(data.at(index).second),
              ans.at(data.at(min_child_index).second));

    SiftDown(min_child_index);
  }

  std::vector<std::pair<int64_t, int64_t>> data;
  std::vector<int64_t> ans{0};
};

int main() {
  size_t quest;
  std::string str;
  int64_t value = 0;
  size_t index = 0;
  Heap my_heap;

  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  std::cin >> quest;

  for (size_t i = 1; i < quest + 1; ++i) {
    std::cin >> str;
    if (str == "insert") {
      std::cin >> value;
      my_heap.Insert({value, i});

    } else if (str == "getMin") {
      std::cout.tie(0);
      std::cout << my_heap.GetMin() << "\n";

    } else if (str == "extractMin") {
      my_heap.ExtractMin();

    } else if (str == "decreaseKey") {
      std::cin >> index;
      std::cin >> value;
      my_heap.DecreaseMin(index, value);
    }
  }
}
