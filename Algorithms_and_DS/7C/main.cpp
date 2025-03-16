#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>

template <class Elem = int32_t>
class DSU {
 public:
  void MakeSet(Elem elem) { parents_[elem] = elem; }

  Elem GetRoot(Elem vert) {
    if (vert == parents_[vert]) {
      return vert;
    }
    return (parents_[vert] = GetRoot(parents_[vert]));
  }

  void Unite(Elem vert1, Elem vert2) {
    vert1 = GetRoot(vert1);
    vert2 = GetRoot(vert2);

    if (vert1 != vert2) {
      parents_[vert1] = vert2;
    }
  }

  bool AreSame(Elem elem1, Elem elem2) {
    return (GetRoot(elem1) == GetRoot(elem2));
  }

 private:
  std::unordered_map<Elem, Elem> parents_;
};

int main() {
  using EdgeT = std::pair<int, std::pair<int, int>>;
  using VertexT = int32_t;
  int32_t n_num;
  int32_t m_num;
  std::cin >> n_num >> m_num;
  std::vector<EdgeT> edges;

  DSU dsu;
  for (int32_t i = 0; i < n_num; ++i) {
    dsu.MakeSet(i);
  }

  for (int32_t i = 0; i < m_num; ++i) {
    VertexT begin;
    VertexT end;
    int32_t weight;
    std::cin >> begin >> end >> weight;
    edges.emplace_back(
        std::make_pair(weight, std::make_pair(begin - 1, end - 1)));
  }

  int32_t cost = 0;

  sort(edges.begin(), edges.end());

  for (EdgeT edge : edges) {
    int32_t weight = edge.first;
    VertexT vert1 = edge.second.first;
    VertexT vert2 = edge.second.second;

    if (!dsu.AreSame(vert1, vert2)) {
      cost += weight;
      dsu.Unite(vert1, vert2);
    }
  }
  std::cout << cost;
}