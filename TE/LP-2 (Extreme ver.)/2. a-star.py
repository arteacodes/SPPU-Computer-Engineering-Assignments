"""
This code implements the A* algorithm for a grid-based game search problem where the goal is to find the shortest path from a start point to a goal point while avoiding obstacles.
"""

from queue import PriorityQueue

class Node:
    def __init__(self, position, parent=None):
        self.position = position
        self.parent = parent
        self.g = 0  # cost from start node to current node
        self.h = 0  # heuristic (estimated cost from current node to goal node)
        self.f = 0  # total cost (g + h)

    def __lt__(self, other):
        return self.f < other.f

def astar(grid, start, goal):
    open_set = PriorityQueue()
    start_node = Node(start)
    goal_node = Node(goal)
    open_set.put(start_node)
    closed_set = set()

    while not open_set.empty():
        current_node = open_set.get()
        if current_node.position == goal_node.position:
            path = []
            while current_node is not None:
                path.append(current_node.position)
                current_node = current_node.parent
            return path[::-1]  # reverse path to start from start node
        closed_set.add(current_node.position)

        # generate neighboring nodes
        for next_position in [(0, -1), (0, 1), (-1, 0), (1, 0)]:  # adjacent squares
            node_position = (current_node.position[0] + next_position[0], current_node.position[1] + next_position[1])
            
            # check if the node is within the bounds of the grid
            if node_position[0] > (len(grid) - 1) or node_position[0] < 0 or node_position[1] > (len(grid[len(grid)-1]) -1) or node_position[1] < 0:
                continue
            
            # check if the node is not an obstacle
            if grid[node_position[0]][node_position[1]] == 1:
                continue

            new_node = Node(node_position, current_node)
            new_node.g = current_node.g + 1
            new_node.h = abs(new_node.position[0] - goal_node.position[0]) + abs(new_node.position[1] - goal_node.position[1])
            new_node.f = new_node.g + new_node.h

            if node_position in closed_set:
                continue

            open_set.put(new_node)

    return None


def main():
    grid = [
        [0, 0, 0, 0, 0],
        [0, 1, 1, 0, 0],
        [0, 0, 0, 0, 0],
        [1, 1, 1, 1, 0],
        [0, 0, 0, 0, 0]
    ]
    start = (0, 0)
    goal = (4, 4)
    path = astar(grid, start, goal)
    if path:
        print("Path found:", path)
    else:
        print("No path found")


main()