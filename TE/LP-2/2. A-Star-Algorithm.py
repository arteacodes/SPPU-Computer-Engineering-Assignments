class AStarAlgorithm:

    def __init__(self, start_node, stop_node, graph_nodes, heuristic_dist):
        self.start_node = start_node
        self.stop_node = stop_node
        self.graph_nodes = graph_nodes
        self.heuristic_dist = heuristic_dist
        self.open_set = set([start_node])  # unvisited
        self.closed_set = set()  # visited
        self.g = {start_node: 0}  # cost to reach each node from start_node
        self.parents = {start_node: start_node}


    def run_algorithm(self):

        while len(self.open_set) > 0:
            n = self.select_node_to_expand()
            
            # if n is stop_node or has no neighbours
            if n == self.stop_node or self.graph_nodes.get(n) is None:
                pass
            else:
                for m, weight in self.get_neighbours(n):
                    if m not in self.open_set and m not in self.closed_set:
                        self.add_to_open_set(m, n, weight)
                    else:
                        self.update_cost(m, n, weight)

            if n is None:
                print('\nPath does not exist!')
                return None

            if n == self.stop_node:
                path = self.reconstruct_path()
                print('\nPath found: ', end="")
                for i in path:
                    print(i, "-> ", end="")
                return path

            self.update_sets(n)

        print('\nPath does not exist!')
        return None
    

    # returns node with lowest cost to expand
    def select_node_to_expand(self):
        n = None
        for v in self.open_set:
            if n is None or self.g[v] + self.heuristic_dist[v] < self.g[n] + self.heuristic_dist[n]:
                n = v
        return n


    # returns list of neighbours of a node
    def get_neighbours(self, v):
        return self.graph_nodes.get(v, [])


    # adds a node to open)set 
    def add_to_open_set(self, m, n, weight):
        self.open_set.add(m)
        self.parents[m] = n
        self.g[m] = self.g[n] + weight


    # updates cost of a node if lower cost path is found
    def update_cost(self, m, n, weight):
        if self.g[m] > self.g[n] + weight:
            self.g[m] = self.g[n] + weight
            self.parents[m] = n

            if m in self.closed_set:
                self.closed_set.remove(m)
                self.open_set.add(m)

    
    # updates open_set & closed_set after evaluating a node
    def update_sets(self, n):
        self.open_set.remove(n)
        self.closed_set.add(n)
    

    # returns recontructed path from stop_node to start_node
    def reconstruct_path(self):
        path = []
        n = self.stop_node
        while self.parents[n] != n:
            path.append(n)
            n = self.parents[n]
        path.append(self.start_node)
        path.reverse()
        return path



def get_user_input():
    graph_nodes = {}
    heuristic_dist = {}

    num_nodes = int(input("Enter the number of nodes in the graph: "))
    for _ in range(num_nodes):
        node = input("Enter the node: ")
        neighbors = input("Enter neighbors and their weights (comma-separated): ").split(',')
        neighbors = [(n.strip(), int(w.strip())) for n, w in map(lambda x: x.split(':'), neighbors)]
        graph_nodes[node] = neighbors

    num_heuristics = int(input("\nEnter the number of heuristic values: "))
    for _ in range(num_heuristics):
        node = input("Enter the node: ")
        value = int(input("Enter the heuristic value: "))
        heuristic_dist[node] = value

    start_node = input("\nEnter the start node: ")
    stop_node = input("Enter the stop node: ")

    return start_node, stop_node, graph_nodes, heuristic_dist



start, stop, graph, heuristic = get_user_input()
astar = AStarAlgorithm(start, stop, graph, heuristic)
astar.run_algorithm()


# SAMPLE INPUT
# Enter the number of nodes in the graph: 6
# Enter the node: A
# Enter neighbors and their weights (comma-separated): B:2, C:3
# ...
