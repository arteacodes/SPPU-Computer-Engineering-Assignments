"""
This code implements Depth First Search (DFS) and Breadth First Search (BFS) algorithms for traversing an undirected graph - using recursive and iterative methods.
"""

from collections import defaultdict, deque
# using defaultdict will assign blank list [] to keys (nodes) that don't have any value yet

class Graph:

    def __init__(self):
        self.graph = defaultdict(list)

    # appends node 'v' in list of neighbours of node 'u' and vice-versa
    def add_edge(self, u, v):
        self.graph[u].append(v)
        self.graph[v].append(u)


    def dfs_recursive(self, start):
        visited = set()
        traversal = []

        def dfs_util(node, level):
            visited.add(node)
            print(f"Visited node {node} at level {level}")

            for neighbor in self.graph[node]:
                if neighbor not in visited:
                    dfs_util(neighbor, level + 1)

        dfs_util(start, 0)


    def dfs_iterative(self, start):
        visited = set()
        stack = [(start, 0)]

        while stack:
            node, level = stack.pop()
            if node not in visited:
                visited.add(node)
                print(f"Visited node {node} at level {level}")

                for neighbor in self.graph[node]:
                    if neighbor not in visited:
                        stack.append((neighbor, level + 1))


    def bfs_recursive(self, start):
        visited = set()

        def bfs_util(queue, level):
            if not queue:
                return
            next_queue = []
            for node in queue:
                visited.add(node)
                print(f"Visited node {node} at level {level}")
                for neighbor in self.graph[node]:
                    if neighbor not in visited:
                        next_queue.append(neighbor)
            bfs_util(next_queue, level + 1)

        bfs_util([start], 0)


    def bfs_iterative(self, start):
        visited = set()
        queue = deque([(start, 0)])

        while queue:
            node, level = queue.popleft()
            visited.add(node)
            print(f"Visited node {node} at level {level}")

            for neighbor in self.graph[node]:
                if neighbor not in visited:
                    queue.append((neighbor, level + 1))
                    visited.add(neighbor)


def main():
    graph = Graph()

    # node can be string/number
    edges = input("Enter edges (format: 'node1 node2', type 'done' to finish): ")
    while edges != 'done':
        edge_nodes = edges.split()
        graph.add_edge(edge_nodes[0], edge_nodes[1])
        edges = input("Enter edges: ")

    start_node = input("Enter starting node: ")

    print("\nDFS Recursive traversal:")
    graph.dfs_recursive(start_node)

    print("\nDFS Iterative traversal:")
    graph.dfs_iterative(start_node)

    print("\nBFS Recursive traversal:")
    graph.bfs_recursive(start_node)

    print("\nBFS Iterative traversal:")
    graph.bfs_iterative(start_node)


main()