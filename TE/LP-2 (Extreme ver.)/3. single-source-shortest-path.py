"""
This code implements Dijkstra's algorithm for Single-Source Shortest Path Problem (SSSP) applied on a college map using a greedy approach.
"""

class Graph:
    def __init__(self, vertices):
        self.V = vertices
        self.graph = {v: {} for v in vertices}

    def add_edge(self, u, v, w):
        # directed graph
        self.graph[u][v] = w

    def dijkstra(self, src):
        
        visited = set()
        distances = {v: float('inf') for v in self.V}  # initialize distances to all vertices as infinity
        distances[src] = 0  # distance from source to source is 0

        # iterate until all vertices are visited
        while len(visited) < len(self.V):
            # find the unvisited vertex with the minimum distance
            min_distance = float('inf')
            min_node = None
            for node in self.V:
                if node not in visited and distances[node] < min_distance:
                    min_distance = distances[node]
                    min_node = node

            # mark the minimum distance node as visited
            visited.add(min_node)

            # update distances for neighboring vertices
            for neighbor, weight in self.graph[min_node].items():
                # calculate distance to neighbor through current node
                distance = distances[min_node] + weight
                # update distance if shorter path found
                if distance < distances[neighbor]:
                    distances[neighbor] = distance

        print("\nPlace \tDistance from", src)
        for place, distance in distances.items():
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
    g.dijkstra(source_place)


main()