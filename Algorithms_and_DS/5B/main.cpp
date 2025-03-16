#include <iostream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
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

template <typename Vertex = int32_t>
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

template <class Vertex, class Graph, class Visitor>
void CompDFS(Graph& graph, Visitor& visitor, int32_t n) {
  std::stack<Vertex> dfs_stack;
  std::unordered_set<Vertex> used;

  for (int32_t i = 0; i < n; ++i) {
    if (!used.contains(i)) {
      used.insert(i);
      dfs_stack.push(i);
      visitor.JoinToComp(i);

      while (!dfs_stack.empty()) {
        Vertex neighbour = dfs_stack.top();
        dfs_stack.pop();
        for (auto& edge : graph.GetOutgoingEdges(neighbour)) {
          Vertex to = edge.GetTarget();
          if (!used.contains(to)) {
            used.insert(to);
            dfs_stack.push(to);
            visitor.JoinToComp(to);
          }
        }
      }
      visitor.IncreaseCompCount();
      visitor.ChangeIndex();
    }
  }
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

  void PrintTimeIn() const {
    for (const auto& [u, time] : t_in_) {
      std::cout << "Vertex: " << u << " , t_in: " << time << '\n';
    }
  }

  void PrintTimeOut() const {
    for (const auto& [u, time] : t_out_) {
      std::cout << "Vertex: " << u << " , t_out: " << time << '\n';
    }
  }

 private:
  using BaseClass = AbstractDFSVisitor<Graph>;
  int32_t time_ = 0;

  std::unordered_map<typename Graph::VertexT, int32_t> t_in_;
  std::unordered_map<typename Graph::VertexT, int32_t> t_out_;
};

template <class Graph>
class CompDFSVisitor : public AbstractDFSVisitor<Graph> {
 public:
  void DiscoverVertex(const typename Graph::VertexT& vertex) final {
    BaseClass::colors_[vertex] = Colors::KGray;
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

  virtual ~CompDFSVisitor() = default;

  void ChangeIndex() { ++comp_index_; }

  void IncreaseCompCount() { ++comp_count_; }

  void JoinToComp(typename Graph::VertexT vert) {
    comp_[comp_index_].push_back(vert);
  }

  void PrintComp() {
    for (auto& [comp, vector] : comp_) {
      std::cout << vector.size() << "\n";
      for (auto& vert : vector) {
        std::cout << vert + 1 << " ";
      }
      std::cout << "\n";
    }
  }

  void PrintCompCount() { std::cout << comp_count_ << "\n"; }

 private:
  using BaseClass = AbstractDFSVisitor<Graph>;

  int32_t comp_index_ = 1;
  size_t comp_count_ = 0;
  std::unordered_map<int32_t, std::vector<typename Graph::VertexT>> comp_;
};

int main() {
  using VertexT = int32_t;
  int32_t n_num;
  int32_t m_num;
  std::cin >> n_num >> m_num;

  std::vector<Edge<VertexT>> edges;
  for (int32_t i = 0; i < m_num; ++i) {
    VertexT start;
    VertexT target;
    std::cin >> start >> target;
    edges.emplace_back(Edge<VertexT>(start - 1, target - 1));
    edges.emplace_back(Edge<VertexT>(target - 1, start - 1));
  }
  Graph<> graph(edges);

  CompDFSVisitor<Graph<>> visitor;

  CompDFS<VertexT>(graph, visitor, n_num);

  visitor.PrintCompCount();
  visitor.PrintComp();
}