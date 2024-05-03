"""
This code implements Prim's algorithm for Minimum Spanning Tree (MST) and Bellman-Ford algorithm for Single-Source Shortest Path Problem (SSSP).
"""


class Graph:
    def __init__(self, vertices):
        self.V = vertices
        self.graph = []

    # function to add an edge to the graph
    def add_edge(self, u, v, w):
        self.graph.append((u, v, w))

    # function to find the vertex with minimum key value
    def min_key(self, key, mst_set):
        min_value = float('inf')
        min_index = -1
        for v in range(self.V):
            if key[v] < min_value and mst_set[v] is False:
                min_value = key[v]
                min_index = v
        return min_index

    # function to construct MST using Prim's algorithm
    def prim_mst(self):
        parent = [-1] * self.V
        key = [float('inf')] * self.V
        mst_set = [False] * self.V

        key[0] = 0  # start from the first vertex

        for _ in range(self.V):
            u = self.min_key(key, mst_set)
            mst_set[u] = True

            # update key values adjacent to the picked vertex
            for u, v, w in self.graph:
                if u == v:
                    continue
                if u == u and mst_set[v] is False and w < key[v]:
                    key[v] = w
                    parent[v] = u

        # print the constructed MST
        print("Minimum Spanning Tree using Prim's algorithm:")
        print("Edge \tWeight")
        for i in range(1, self.V):
            print(parent[i], "-", i, "\t", key[i])

    # function to find the shortest paths from a source vertex using Bellman-Ford algorithm
    def bellman_ford(self, src):
        dist = [float('inf')] * self.V
        dist[src] = 0

        for _ in range(self.V - 1):
            for u, v, w in self.graph:
                if dist[u] != float('inf') and dist[u] + w < dist[v]:
                    dist[v] = dist[u] + w

        # print the shortest distances from source to all vertices
        print("\nSingle-Source Shortest Path Problem using Bellman-Ford algorithm:")
        print("Vertex \tDistance from Source")
        for v in range(self.V):
            print(v, "\t", dist[v])


def main():
    V = int(input("Enter the number of vertices: "))
    g = Graph(V)

    E = int(input("Enter the number of edges: "))
    print("Enter the edges (source destination weight):")
    for _ in range(E):
        u, v, w = map(int, input().split())
        g.add_edge(u, v, w)

    source_vertex = int(input("Enter the source vertex: "))

    g.prim_mst()
    g.bellman_ford(source_vertex)


if __name__ == "__main__":
    main()
