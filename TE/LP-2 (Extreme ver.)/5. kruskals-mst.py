class Graph:

    def __init__(self, vertices):
        self.V = vertices
        self.graph = []


    def add_edge(self, u, v, w):
        self.graph.append([u, v, w])

    # find method of Union-Find algorithm for cycle detection
    def find(self, parent, i):
        if parent[i] == i:
            return i
        return self.find(parent, parent[i])


    # union method of Union-Find algorithm for cycle detection
    def union(self, parent, rank, x, y):
        x_root = self.find(parent, x)
        y_root = self.find(parent, y)

        if rank[x_root] < rank[y_root]:
            parent[x_root] = y_root
        elif rank[x_root] > rank[y_root]:
            parent[y_root] = x_root
        else:
            parent[y_root] = x_root
            rank[x_root] += 1


    def kruskal_mst(self):
        result = []
        i, e = 0, 0
        self.graph = sorted(self.graph, key=lambda item: item[2])  # sort edges by weight
        parent = [i for i in range(self.V)]  # initialize each vertex as its own parent
        rank = [0] * self.V  # initialize rank of each vertex as 0

        while e < self.V - 1:
            # get current edge
            u, v, w = self.graph[i]
            i += 1
            # find root of nodes u and v
            x = self.find(parent, u)
            y = self.find(parent, v)

            # check if adding this edge creates a cycle
            if x != y:
                e += 1
                result.append([u, v, w])
                self.union(parent, rank, x, y)  # merge the subsets

        return result


def main():
    # example: "0 1 4,0 7 8,1 7 11,1 2 8,7 8 7,7 6 1,8 6 6,2 3 7,2 5 4,2 8 2,6 5 2,3 5 14,3 4 9,5 4 10"
    input_str = input("Enter the network connections with their cost separated by commas (e.g., '0 1 4, 0 2 8, 1 2 3'): ")
    edges = input_str.split(',')
    vertices = set()
    for edge in edges:
        u, v, w = map(int, edge.split())
        vertices.add(u)
        vertices.add(v)

    num_vertices = len(vertices)
    g = Graph(num_vertices)

    for edge in edges:
        u, v, w = map(int, edge.split())
        g.add_edge(u, v, w)

    mst = g.kruskal_mst()
    total_cost = sum(edge[2] for edge in mst)
    
    print("MST for Least Cost Network:")
    for u, v, weight in mst:
        print(f"{u} - {v} : {weight}")
    print(f"Total cost of network = {total_cost}")


main()