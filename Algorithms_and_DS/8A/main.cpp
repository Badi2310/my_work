#include <algorithm>
#include <functional>
#include <iostream>
#include <optional>
#include <queue>
#include <stack>
#include <unordered_set>
#include <utility>
#include <vector>

// template from seminar

template <class Vertex>
struct Edge {
  Vertex from;
  Vertex to;
  int id;
};

template <class Vertex, class Graph, class Visitor>
void DepthFirstSearch(Vertex origin_vertex, const Graph& graph,
                      Visitor& visitor) {
  std::stack<Vertex> dfs_stack;
  std::unordered_set<Vertex> used;

  used.insert(origin_vertex);
  dfs_stack.push(origin_vertex);

  while (!dfs_stack.empty()) {
    Vertex neighbour = dfs_stack.top();
    dfs_stack.pop();
    for (const auto& edge : graph.EdgesFromVertex(neighbour)) {
      Vertex to = edge.to;
      if (!used.contains(to)) {
        visitor.TreeEdge(edge);
        used.insert(to);
        dfs_stack.push(to);
      }
    }
  }
}

template <class Vertex, class Edge = std::pair<Vertex, Vertex>>
class Graph {
 public:
  using VertexT = Vertex;
  using EdgeT = Edge;

  Graph() = default;
  explicit Graph(int number_vertices)
      : number_vertices_(number_vertices),
        adjacency_list_(number_vertices, std::vector<Edge>()) {}

  void AddEdge(int from, int to) {
    adjacency_list_[from].push_back({from, to, number_edges_});
    ++number_edges_;
  }

  void AddVertex() {
    adjacency_list_.emplace_back();
    ++number_vertices_;
  }

  int VerticesCount() const { return number_vertices_; }

  int EdgesCount() const { return number_edges_; }

  const std::vector<Edge>& EdgesFromVertex(int vertex) const {
    return adjacency_list_[vertex];
  }

  int EdgesNumberFromVertex(int vertex) const {
    return static_cast<int>(adjacency_list_[vertex].size());
  }

 private:
  int number_edges_ = 0;
  int number_vertices_ = 0;
  std::vector<std::vector<Edge>> adjacency_list_;
};

template <class Vertex, class Edge = std::pair<Vertex, Vertex>>
class FilteredGraph {
 public:
  using GraphT = Graph<Vertex, Edge>;
  using EdgeT = typename GraphT::EdgeT;
  using VertexT = typename GraphT::VertexT;

  FilteredGraph(const Graph<Vertex, Edge>& graph,
                std::function<bool(typename GraphT::EdgeT)> predicate)
      : graph_(graph), predicate_(std::move(predicate)) {}

  std::vector<EdgeT> EdgesFromVertex(int vertex) const {
    auto outgoing_edges = graph_.EdgesFromVertex(vertex);
    std::vector<EdgeT> filtered_edges;
    for (const auto& edge : outgoing_edges) {
      if (predicate_(edge)) {
        filtered_edges.push_back(edge);
      }
    }
    return filtered_edges;
  }

  int VerticesCount() const { return graph_.VerticesCount(); }

 private:
  const GraphT& graph_;
  std::function<bool(typename GraphT::EdgeT)> predicate_;
};

template <class Graph>
class NetworkBuilder;

template <class Graph>
class FlowNetwork {
 public:
  using GraphT = Graph;
  void UpdateFlowByEdge(const typename Graph::EdgeT& edge, int extra_flow) {
    edges_properties_[edge.id].flow += extra_flow;
    int rev_edge_id = edges_properties_[edge.id].reverse_edge_id;
    edges_properties_[rev_edge_id].flow -= extra_flow;
  }

  int ResidualCapacity(int edge_id) const {
    return edges_properties_[edge_id].capacity -
           edges_properties_[edge_id].flow;
  }

  int NumberEdges() const { return graph_.EdgesCount(); }

  int NumberVertices() const { return graph_.VerticesCount(); }

  int Source() const { return source_; }

  int Sink() const { return sink_; }

  FilteredGraph<typename Graph::VertexT, typename Graph::EdgeT>
  ResidualNetworkView() {
    return FilteredGraph(graph_, [this](typename GraphT::EdgeT edge) {
      return ResidualCapacity(edge.id) > 0;
    });
  }

  friend class NetworkBuilder<Graph>;

 private:
  struct EdgeProperties {
    EdgeProperties(int flow, int capacity, int reverse_edge_id)
        : flow(flow), capacity(capacity), reverse_edge_id(reverse_edge_id) {}
    int flow;
    int capacity;
    int reverse_edge_id;
  };

  FlowNetwork() = default;
  explicit FlowNetwork(Graph graph) : graph_(std::move(graph)) {}

  int source_ = 0;
  int sink_ = 0;
  std::vector<EdgeProperties> edges_properties_;
  Graph graph_;
};

template <class Graph>
class NetworkBuilder {
 public:
  using GraphT = Graph;
  using VertexT = typename GraphT::VertexT;

  explicit NetworkBuilder(int vertices_number) {
    network_.graph_ = Graph(vertices_number);
  }

  void AddEdge(VertexT from, VertexT to, int capacity) {
    network_.edges_properties_.emplace_back(
        0, capacity, static_cast<int>(network_.edges_properties_.size() + 1));
    network_.graph_.AddEdge(from, to);
    network_.edges_properties_.emplace_back(
        0, 0, static_cast<int>(network_.edges_properties_.size()) - 1);
    network_.graph_.AddEdge(to, from);
  }

  void AssignSource(int source) { network_.source_ = source; }

  void AssignSink(int sink) { network_.sink_ = sink; }

  FlowNetwork<Graph> GetFlowNetwork() const { return std::move(network_); }

 private:
  FlowNetwork<Graph> network_;
};

template <class Vertex, class Edge>
class DfsVisitor {
 public:
  using GraphT = Graph<Vertex, Edge>;

  virtual void TreeEdge(Edge /*edge*/) {}
  virtual ~DfsVisitor() = default;
};

class AncestorsCalculator : public DfsVisitor<int, Edge<int>> {
 public:
  using BaseVisitor = DfsVisitor<int, Edge<int>>;
  using GraphT = typename BaseVisitor::GraphT;
  using OptionalEdgeVector = std::vector<std::optional<typename GraphT::EdgeT>>;

  explicit AncestorsCalculator(
      OptionalEdgeVector* edges_to_ancestor_in_bfs_tree)
      : edges_to_ancestor_in_bfs_tree_(edges_to_ancestor_in_bfs_tree) {}

  void TreeEdge(GraphT::EdgeT edge) override {
    (*edges_to_ancestor_in_bfs_tree_)[edge.to] = edge;
  }

 private:
  OptionalEdgeVector* edges_to_ancestor_in_bfs_tree_;
};

template <class FlowNetwork>
class EdmondsKarpAlgorithm {
 public:
  using GraphT = typename FlowNetwork::GraphT;
  using EdgeT = typename GraphT::EdgeT;

  explicit EdmondsKarpAlgorithm(FlowNetwork network)
      : network_(std::move(network)) {}

  int FindMaxFlow() {
    int max_flow = 0;
    for (auto ancestors = AncestorsInShortestPathsTree();
         ancestors[network_.Sink()];
         ancestors = AncestorsInShortestPathsTree()) {
      auto edges_id_on_path = PathEdges(ancestors);
      int extra_flow = ExtraFlow(edges_id_on_path);
      for (const auto& edge : edges_id_on_path) {
        network_.UpdateFlowByEdge(edge, extra_flow);
      }
      max_flow += extra_flow;
    }
    return max_flow;
  }

 private:
  using OptionalEdgeVector = std::vector<std::optional<EdgeT>>;
  std::vector<std::optional<EdgeT>> AncestorsInShortestPathsTree() {
    std::vector<std::optional<EdgeT>> ancestors(network_.NumberVertices());
    AncestorsCalculator ancestors_calculator(&ancestors);
    auto residual_network = network_.ResidualNetworkView();

    DepthFirstSearch(network_.Source(), residual_network, ancestors_calculator);
    return ancestors;
  }

  std::vector<EdgeT> PathEdges(const OptionalEdgeVector& ancestors) {
    std::vector<EdgeT> edges_id;
    int cur_vertex = network_.Sink();
    while (cur_vertex != network_.Source()) {
      edges_id.push_back(ancestors[cur_vertex].value());
      cur_vertex = ancestors[cur_vertex]->from;
    }
    std::reverse(edges_id.begin(), edges_id.end());
    return edges_id;
  }

  int ExtraFlow(const std::vector<EdgeT>& edges_id_on_path) {
    auto get_residual_capacity = [&](const EdgeT& edge) {
      return network_.ResidualCapacity(edge.id);
    };
    auto min_residual_capacity =
        get_residual_capacity(edges_id_on_path.front());
    for (const auto& edge : edges_id_on_path) {
      min_residual_capacity =
          std::min(min_residual_capacity, get_residual_capacity(edge));
    }
    return min_residual_capacity;
  }

  FlowNetwork network_;
};

std::vector<Edge<int>> ReadGraph(int number_edges,
                                 std::istream& is = std::cin) {
  std::vector<Edge<int>> edges;
  edges.resize(number_edges);
  for (auto& [from, to, cap] : edges) {
    is >> from >> to >> cap;
    --from, --to;
  }
  return edges;
}

void OptimizeIO() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
}

FlowNetwork<Graph<int, Edge<int>>> BuildNetwork(
    const std::vector<Edge<int>>& edges, int number_vertices) {
  NetworkBuilder<Graph<int, Edge<int>>> builder(number_vertices);
  builder.AssignSource(0);
  builder.AssignSink(number_vertices - 1);
  for (const auto& [from, to, cap] : edges) {
    builder.AddEdge(from, to, cap);
  }
  return builder.GetFlowNetwork();
}

int main() {
  OptimizeIO();
  int servers_num;
  int channels_num;
  std::cin >> servers_num >> channels_num;
  auto edges = ReadGraph(channels_num);
  auto network = BuildNetwork(edges, servers_num);
  EdmondsKarpAlgorithm flow_searcher(network);
  std::cout << flow_searcher.FindMaxFlow();
  return 0;
}