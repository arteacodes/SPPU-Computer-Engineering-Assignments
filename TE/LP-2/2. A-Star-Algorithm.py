class AStarAlgorithm:
    def __init__(self, start_node, stop_node, graph_nodes, heuristic_dist):
        self.start_node = start_node
        self.stop_node = stop_node
        self.graph_nodes = graph_nodes
        self.heuristic_dist = heuristic_dist
        self.open_set = set([start_node])
        self.closed_set = set()
        self.g = {start_node: 0}
        self.parents = {start_node: start_node}

    def run_algorithm(self):
        while len(self.open_set) > 0:
            n = self._select_node_to_expand()

            if n == self.stop_node or self.graph_nodes.get(n) is None:
                pass
            else:
                for m, weight in self._get_neighbors(n):
                    if m not in self.open_set and m not in self.closed_set:
                        self._add_to_open_set(m, n, weight)
                    else:
                        self._update_node_cost(m, n, weight)

            if n is None:
                print('Path does not exist!')
                return None

            if n == self.stop_node:
                path = self._reconstruct_path()
                print('Path found: {}'.format(path))
                return path

            self._update_sets(n)

        print('Path does not exist!')
        return None

    def _select_node_to_expand(self):
        n = None
        for v in self.open_set:
            if n is None or self.g[v] + self.heuristic_dist[v] < self.g[n] + self.heuristic_dist[n]:
                n = v
        return n

    def _get_neighbors(self, v):
        return self.graph_nodes.get(v, [])

    def _add_to_open_set(self, m, n, weight):
        self.open_set.add(m)
        self.parents[m] = n
        self.g[m] = self.g[n] + weight

    def _update_node_cost(self, m, n, weight):
        if self.g[m] > self.g[n] + weight:
            self.g[m] = self.g[n] + weight
            self.parents[m] = n

            if m in self.closed_set:
                self.closed_set.remove(m)
                self.open_set.add(m)

    def _reconstruct_path(self):
        path = []
        n = self.stop_node
        while self.parents[n] != n:
            path.append(n)
            n = self.parents[n]
        path.append(self.start_node)
        path.reverse()
        return path

    def _update_sets(self, n):
        self.open_set.remove(n)
        self.closed_set.add(n)


def get_user_input():
    graph_nodes = {}
    heuristic_dist = {}

    num_nodes = int(input("Enter the number of nodes in the graph: "))
    for _ in range(num_nodes):
        node = input("Enter the node: ")
        neighbors = input("Enter neighbors and their weights (comma-separated): ").split(',')
        neighbors = [(n.strip(), int(w.strip())) for n, w in map(lambda x: x.split(':'), neighbors)]
        graph_nodes[node] = neighbors

    num_heuristics = int(input("Enter the number of heuristic values: "))
    for _ in range(num_heuristics):
        node = input("Enter the node: ")
        value = int(input("Enter the heuristic value: "))
        heuristic_dist[node] = value

    start_node = input("Enter the start node: ")
    stop_node = input("Enter the stop node: ")

    return start_node, stop_node, graph_nodes, heuristic_dist



start, stop, graph, heuristic = get_user_input()
astar = AStarAlgorithm(start, stop, graph, heuristic)
astar.run_algorithm()
