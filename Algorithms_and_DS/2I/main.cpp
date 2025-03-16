#include <iostream>
#include <vector>

namespace MagicNumbers {
const size_t kSubBucketCount = 8;
const size_t kBucketSize = 256;
}  // namespace MagicNumbers
void ByteSort(std::vector<uint64_t>& vec, int32_t byte) {
  std::vector<uint32_t> cnt(MagicNumbers::kBucketSize);
  std::vector<uint64_t> ans(vec.size());
  for (size_t i = 0; i < vec.size(); ++i) {
    ++cnt[(vec[i] << (byte * MagicNumbers::kSubBucketCount)) >>
          ((MagicNumbers::kSubBucketCount - 1) *
           MagicNumbers::kSubBucketCount)];
  }

  for (size_t index = 1; index < MagicNumbers::kBucketSize; ++index) {
    cnt[index] += cnt[index - 1];
  }

  for (size_t i = vec.size(); i > 0; --i) {
    ans[cnt[(vec[i - 1] << (byte * MagicNumbers::kSubBucketCount)) >>
            ((MagicNumbers::kSubBucketCount - 1) *
             MagicNumbers::kSubBucketCount)]-- -
        1] = vec[i - 1];
  }
  vec = ans;
}

void LsdSort(std::vector<uint64_t>& vec) {
  for (size_t index = MagicNumbers::kSubBucketCount; index > 0; --index) {
    ByteSort(vec, index - 1);
  }
}

int main() {
  size_t num;
  std::cin >> num;
  std::vector<uint64_t> vec(num);
  for (size_t index = 0; index < num; ++index) {
    std::cin >> vec[index];
  }

  LsdSort(vec);

  for (size_t index = 0; index < num; ++index) {
    std::cout << vec[index] << "\n";
  }
  return 0;
}
