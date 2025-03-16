#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>

enum class Colors {
  KWhite = 0,
  KGray,
  KBlack,
};

template <class Vertex>
struct Edge {
  Edge(const Vertex& from, const Vertex& to) : vertices_(from, to) {}

  const Vertex& GetStart() const { return vertices_.first; }
  const Vertex& GetTarget() const { return vertices_.second; }

 private:
  std::pair<Vertex, Vertex> vertices_;
};

template <typename Vertex = int>
class Graph {
 public:
  using VertexT = Vertex;
  using EdgeT = Edge<VertexT>;

  Graph(const std::vector<EdgeT>& edges) {
    for (const auto& edge : edges) {
      adjacent_[edge.GetStart()].push_back(edge);
    }
  }

  const std::vector<EdgeT>& GetOutgoingEdges(const Vertex& vertex) {
    return adjacent_[vertex];
  }

 private:
  std::unordered_map<VertexT, std::vector<EdgeT>> adjacent_;
};

template <class Graph, class Visitor>
void DFS(Graph& graph, const typename Graph::VertexT& vertex,
         Visitor& visitor) {
  visitor.DiscoverVertex(vertex);
  for (const auto& outgoing_edge : graph.GetOutgoingEdges(vertex)) {
    const auto& neighbour = outgoing_edge.GetTarget();
    if (visitor.GetColor(neighbour) == Colors::KWhite) {
      DFS(graph, neighbour, visitor);
    }
  }
  visitor.FinishVertex(vertex);
}

template <class Graph>
class AbstractDFSVisitor {
 public:
  virtual void DiscoverVertex(const typename Graph::VertexT& vertex) = 0;
  virtual void FinishVertex(const typename Graph::VertexT& vertex) = 0;
  virtual Colors GetColor(const typename Graph::VertexT& vertex) = 0;
  virtual ~AbstractDFSVisitor() = default;

 protected:
  std::unordered_map<typename Graph::VertexT, Colors> colors_;
};

template <class Graph>
class TimerDFSVisitor : public AbstractDFSVisitor<Graph> {
 public:
  void DiscoverVertex(const typename Graph::VertexT& vertex) final {
    BaseClass::colors_[vertex] = Colors::KGray;
    ++time_;
    t_in_[vertex] = time_;
  }

  void FinishVertex(const typename Graph::VertexT& vertex) final {
    BaseClass::colors_[vertex] = Colors::KBlack;
    ++time_;
    t_out_[vertex] = time_;
  }

  Colors GetColor(const typename Graph::VertexT& vertex) final {
    if (BaseClass::colors_.contains(vertex)) {
      return BaseClass ::colors_[vertex];
    }
    return Colors::KWhite;
  }

  virtual ~TimerDFSVisitor() = default;

  const std::unordered_map<typename Graph::VertexT, int>& GetTimeOut() const {
    return t_out_;
  }

 private:
  using BaseClass = AbstractDFSVisitor<Graph>;
  int time_ = 0;

  std::unordered_map<typename Graph::VertexT, int> t_in_;
  std::unordered_map<typename Graph::VertexT, int> t_out_;
};

template <class Graph>
class CompDFSVisitor : public AbstractDFSVisitor<Graph> {
 public:
  void DiscoverVertex(const typename Graph::VertexT& vertex) final {
    BaseClass::colors_[vertex] = Colors::KGray;
    comp_[vertex] = comp_index_;
  }

  void FinishVertex(const typename Graph::VertexT& vertex) final {
    BaseClass::colors_[vertex] = Colors::KBlack;
  }

  Colors GetColor(const typename Graph::VertexT& vertex) final {
    if (BaseClass::colors_.contains(vertex)) {
      return BaseClass ::colors_[vertex];
    }
    return Colors::KWhite;
  }

  int GetComp(const typename Graph::VertexT& vertex) { return comp_[vertex]; }

  virtual ~CompDFSVisitor() = default;

  void ChangeIndex() { ++comp_index_; }

  void IncreaseCompCount() { ++comp_count_; }

  void PrintCompCount() { std::cout << comp_count_ << "\n"; }

 private:
  using BaseClass = AbstractDFSVisitor<Graph>;

  int comp_index_ = 1;
  int comp_count_ = 0;
  std::unordered_map<typename Graph::VertexT, int> comp_;
};

int main() {
  int n_num;
  int m_num;
  std::cin >> n_num >> m_num;

  std::vector<Edge<int>> edges;
  std::vector<Edge<int>> reverse_edges;
  for (int i = 0; i < m_num; ++i) {
    int start;
    int target;
    std::cin >> start >> target;
    edges.emplace_back(Edge<int>(start - 1, target - 1));
    reverse_edges.emplace_back(Edge<int>(target - 1, start - 1));
  }
  Graph<> graph(edges);
  Graph<> graph_t(reverse_edges);

  TimerDFSVisitor<Graph<>> timer_visitor;
  CompDFSVisitor<Graph<>> comp_visitor;

  for (int i = 0; i < n_num; ++i) {
    if (timer_visitor.GetColor(i) == Colors::KWhite) {
      DFS(graph, i, timer_visitor);
    }
  }

  std::vector<std::pair<int, int>> t_out;

  for (const auto& vert_time : timer_visitor.GetTimeOut()) {
    t_out.push_back(vert_time);
  }

  std::sort(
      t_out.begin(), t_out.end(),
      [](const std::pair<int, int>& left, const std::pair<int, int>& right) {
        return left.second > right.second;
      });

  for (auto& vert_time : t_out) {
    if (comp_visitor.GetColor(vert_time.first) == Colors::KWhite) {
      DFS(graph_t, vert_time.first, comp_visitor);
      comp_visitor.ChangeIndex();
      comp_visitor.IncreaseCompCount();
    }
  }
  comp_visitor.PrintCompCount();
  for (int i = 0; i < n_num; ++i) {
    std::cout << comp_visitor.GetComp(i) << " ";
  }
}
