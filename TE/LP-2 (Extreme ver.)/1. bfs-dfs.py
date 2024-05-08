from collections import defaultdict, deque

class Graph:

    def __init__(self):
        self.graph = defaultdict(list)


    def addEdge(self, u, v):
        self.graph[u].append(v)
        self.graph[v].append(u)


    def dfsRecursive(self, start):
        visited = set()

        def dfs(node, level):
            # add node to visited set and print
            visited.add(node)
            print(f'Visited node {node} at level {level}.')

            # check adjacency list and if any neighbour not visited, go to that node
            for neighbour in self.graph[node]:
                if neighbour not in visited:
                    dfs(neighbour, level+1)
        
        dfs(start, 0)


    def dfsIterative(self, start):
        visited = set()
        stack = [(start, 0)]

        # until stack is empty
        while stack:
            node, level = stack.pop()
            
            # if current node is unvisited then visit it
            if node not in visited:
                visited.add(node)
                print(f'Visited node {node} at level {level}.')

                # check adj list and if any neighbour is unvisited, add to stack
                # check in reverse so that most recently added neighbours are visited first
                for neighbour in reversed(self.graph[node]):
                    if neighbour not in visited:
                        stack.append((neighbour, level+1))


    def bfsIterative(self, start):
        visited = set()
        queue = deque([(start, 0)])  # use a deque with only popleft() function

        # until queue is empty
        while queue:
            # pop first node and add to visited set
            node, level = queue.popleft()
            visited.add(node)
            print(f'Visited node {node} at level {level}.')
            
            # check adj list and if any neighbour is unvisited, add to queue and mark visited
            for neighbour in self.graph[node]:
                if neighbour not in visited:
                    queue.append((neighbour, level+1))
                    visited.add(neighbour)

    
    # NOTE: BFS is usually not implemented recursively as it doesn't align with the algorithm's nature
    def bfsRecursive(self, start):
        visited = set()
        initial_queue = [(start)]

        def bfs(queue, level):
            # return if queue is empty
            if not queue:  
                return
            
            # this will store neighbours of current level's nodes to be processed next
            next_queue = []

            for node in queue:
                visited.add(node)
                print(f'Visited node {node} at level {level}.')

                # check neighbours of current node and if unvisited, append to next queue
                for neighbour in self.graph[node]:
                    if neighbour not in visited:
                        next_queue.append(neighbour)
            
            # after processing current level, call bfs() for next level
            bfs(next_queue, level+1)
        
        bfs(initial_queue, 0)

def main():

    g = Graph()

    edges = input("Enter edges (format 'node1 node2', type 'done' to finish): ")
    while edges != 'done':
        edge_nodes = edges.split()
        g.addEdge(edge_nodes[0], edge_nodes[1])
        edges = input("Enter edges: ")
    
    start = input("Enter starting node: ")

    print("\nDFS Recursive traversal:")
    g.dfsRecursive(start)

    print("\nDFS Iterative traversal:")
    g.dfsIterative(start)

    print("\nBFS Recursive traversal:")
    g.bfsRecursive(start)

    print("\nBFS Iterative traversal:")
    g.bfsIterative(start)


main()
