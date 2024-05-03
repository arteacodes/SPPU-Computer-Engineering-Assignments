"""
This code implements Bellman-Ford algorithm for Single-Source Shortest Path Problem (SSSP) applied on a college map using a greedy approach.
"""

class Graph:
    
    def __init__(self, vertices):
        self.V = vertices
        self.graph = []

    
    def add_edge(self, u, v, w):
        self.graph.append((u, v, w))

    
    def bellman_ford(self, src):
        dist = {v: float('inf') for v in self.V}  # initial distances set to infinity
        dist[src] = 0  # distance from src to src set to 0

        # since longest possible path in any graph is V-1
        for _ in range(len(self.V) - 1):
            for u, v, w in self.graph:
                # if u is reachable and has a shorter path to it, update its distance from src
                if dist[u] != float('inf') and dist[u] + w < dist[v]:  
                    dist[v] = dist[u] + w

        print(f"\nPlace \tDistance from {src}")
        for place, distance in dist.items():
            print(place, "\t", distance)


def main():
    places = input("Enter the places in the college map separated by spaces: ").split()

    g = Graph(places)

    E = int(input("Enter the number of paths between places: "))
    print("Enter the paths (source, destination, distance):")

    for _ in range(E):
        u, v, w = input().split()
        g.add_edge(u, v, int(w))

    source_place = input("Enter the name of the source vertex: ")
    g.bellman_ford(source_place)


main()
