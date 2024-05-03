"""
This code implements Prim's Minimal Spanning Tree algorithm for a water supply network using a greedy approach.
"""

class Graph:

    def __init__(self, vertices):
        self.V = vertices
        self.graph = [[] for _ in range(vertices)]


    def add_edge(self, u, v, w):
        self.graph[u].append((v, w))
        self.graph[v].append((u, w))  


    def prim_mst(self):
        # initialize sets to track visited and unvisited vertices
        cost = 0
        mst_set = set()
        unvisited_set = set(range(self.V))

        # starting from the first vertex
        mst_set.add(0)
        unvisited_set.remove(0)

        while unvisited_set:
            min_edge = None
            min_weight = float('inf')

            # find the minimum weight edge connecting the MST to the unvisited vertices
            for u in mst_set:
                for v, weight in self.graph[u]:
                    if v in unvisited_set and weight < min_weight:
                        min_edge = (u, v)
                        min_weight = weight

            if min_edge:
                u, v = min_edge
                print(f"Pipe from {u} to {v} with capacity {min_weight} is added to the network.")
                cost += min_weight
                mst_set.add(v)
                unvisited_set.remove(v)
            else:
                break

        print(f"\nTotal cost of MST = {cost}")


def main():
    num_vertices = int(input("Enter the number of junctions (vertices) in the water supply network: "))
    g = Graph(num_vertices)

    num_edges = int(input("Enter the number of pipes (edges) in the network: "))
    print("Enter the connections and capacities for each pipe (source, destination, capacity):")
    for _ in range(num_edges):
        u, v, w = input().split()
        g.add_edge(int(u), int(v), int(w))

    print("\nMST for water supply network:")
    g.prim_mst()


main()