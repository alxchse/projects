# Alexandra Chase and Elios Hoxholli
# ehoxho27@g.holycross.edu
# amchas26@g.holycross.edu, 
# CSCI 347 Artificial Intelligence
# Project 1: A* Dice Maze 
# February 13, 2026

import sys
import heapq
from collections import deque

class Dice:
    # define the Dice class to represent the actions of the dice
    
    def __init__(self, top=1, north=2, east=4):
        self.top = top
        self.bottom = 7 - top # opposite face of top
        self.north = north
        self.south = 7 - north # opposite face of north
        self.east = east
        self.west = 7 - east # opposite face of east

    # roll the dice in the specified direction.
    def roll_north(self):
        return Dice(self.south, self.top, self.east)   # top becomes south, south comes up top

    def roll_south(self):
        return Dice(self.north, self.bottom, self.east) # top becomes north, north comes up top

    def roll_east(self):
        return Dice(self.west, self.north, self.top)    # top becomes east, west comes up top

    def roll_west(self):
        return Dice(self.east, self.north, self.bottom) # top becomes west, east comes up top

    # get the current top and north face values. north face value indicates rotation. 
    def get_top(self):
        return self.top
    def get_north(self):
        return self.north
    
    # two dice are equal if they have the same top and north face values (east face is determined by these two)
    # this is important for checking if we have already explored a state with the same orientation
    def __eq__(self, other):
        return (self.top == other.top and
            self.north == other.north and
            self.east  == other.east)

    # we need to define __hash__ because we want to use Dice objects in sets and dictionary keys for explored states
    def __hash__(self):
        return hash((self.top, self.north, self.east))
    
class Maze:
    # rectangular maze loaded from a text file (one of available maze*.txt files) 
    # grid coordinates are (row, col) with (0,0) at the top-left.
    # characters: '.' open, '*' obstacle, 'S' start (open), 'G' goal (open).

    def __init__(self, filename: str):
        
        # read maze layout from selected text file
        with open(filename, 'r') as f:
            grid = [line.strip('\n') for line in f.readlines()]
        
        # convert .txt file to list of lists to identify critical coordinates
        self.grid = [list(row) for row in grid] 
        self.height = len(self.grid)
        self.width = len(self.grid[0])
        self.start = None
        self.goal = None
        self.obstacles = set()

        # identify chars as open space, start, goal, or obstacle
        for r in range(self.height):
            for c in range(len(self.grid[r])):
                ch = self.grid[r][c]
                if ch == 'S':
                    self.start = (r, c) # establish as start position
                elif ch == 'G':
                    self.goal = (r, c) # establish as goal position
                elif ch == '*':
                    self.obstacles.add((r, c)) # add to list of obstacles
                elif ch == '.':
                    continue # this line is necessary because otherwise '.' will raise error
                else:
                    raise ValueError(f"Invalid character '{ch}' in maze at ({r}, {c})")
        
        # check for other errors in the maze layout
        if self.start is None:
            raise ValueError("Maze has no start.")
        if self.goal is None:
            raise ValueError("Maze has no goal.")

        # print the given maze with start and goal positions
    def printMaze(self):
        print("Given Maze Layout:")
        for row in self.grid:
            print(''.join(row))
        print(f"\nStart Position: {self.start}, Goal Position: {self.goal}")

        # check if move is within bounds and not an obstacle
    def isMoveValid(self, row: int, col: int) -> bool:
        if row < 0 or row >= self.height: 
            return False
        if col < 0 or col >= self.width:
            return False
        if (row, col) in self.obstacles:
            return False
        return True

    def getChildren(self, state):
        # generate all valid child states from the current state.
        # returns list of children (next_state, action, cost).

        row, col, dice = state
        children = []

        # (action_name, new_row, new_col, rolled_dice)
        moves = [
            ('North', row - 1, col, dice.roll_north()),
            ('South', row + 1, col, dice.roll_south()),
            ('East',  row, col + 1, dice.roll_east()),
            ('West',  row, col - 1, dice.roll_west()),
        ]

        # only add valid moves where 6 is not on top  
        for action, new_row, new_col, new_dice in moves:
            if self.isMoveValid(new_row, new_col) and new_dice.get_top() != 6:
                children.append(((new_row, new_col, new_dice), action))

        return children

class Node:
    # node in the A* search tree
    # stores state (orientation and coordinates), parent, action taken, and search costs

    def __init__(self, state, parent=None, action=None, gCost=0, hCost=0):
        self.state = state    # (row, col, dice)
        self.parent = parent   # parent Node
        self.action = action   # action taken to reach this node
        self.gCost = gCost   # cost from start to this node
        self.hCost = hCost   # heuristic cost from this node to goal
        self.fCost = gCost + hCost # A* cost function

    # heapq needs to compare Nodes' F costs when they are added to the priority queue (frontier)
    def __lt__(self, other):
        return self.fCost < other.fCost


def heuristicManhattan(state, maze: Maze) -> int:
    # calculates Manhattan distance from current position to goal
    # it is admissible because we cannot reach goal in fewer moves than this Manhattan distance
    # function is | current row - goal row | + | current col - goal col |

    row, col, dice = state
    goal_row, goal_col = maze.goal
    return abs(row - goal_row) + abs(col - goal_col)


def heuristicReorientation(state, maze: Maze) -> int:
    # calculates Manhattan distance with an orientation penalty
    # if die does not have 1 on top at the goal, AT LEAST 1 extra move is needed to reorient properly
    # adding 1 for a penalty keeps this admissible because, most often, the true cost to reorient will be more than 1
    
    row, col, dice = state
    goal_row, goal_col = maze.goal
    manhattan = abs(row - goal_row) + abs(col - goal_col)

    # WORK IN PROGRESS
    if dice.get_top() == 1:
        orientation_penalty = 0
    else:
        orientation_penalty = 1

    return manhattan + orientation_penalty

def find_path(initial_state, maze: Maze, heuristic) -> (list, int, function):
     # A* search from initial_state to goal
     # takes initial_state: (row, col, dice) and maze
     # returns (path, nodes_generated, nodes_expanded)
     # where path is list of (row, col, dice) states from start node to goal node

    initial_node = Node(
        state = initial_state,
        parent = None,
        action = None,
        gCost = 0,
        hCost = heuristic(initial_state, maze),
    )

    frontier = []
    heapq.heappush(frontier, initial_node)

    explored = set() 
    nodes_generated = 1
    nodes_expanded = 0

    # A* search loop: pop lowest f_cost node, check goal, add children to frontier if not yet explored
    while frontier:
        current = heapq.heappop(frontier)

        # skip if already explored this state
        if current.state in explored:
            continue

        nodes_expanded += 1

        # goal test: at goal position with 1 on top
        row, col, dice = current.state
        if (row, col) == maze.goal and dice.get_top() == 1:
            path = reconstruct_path(current)
            return path, nodes_generated, nodes_expanded

        # now we can establish this state as explored
        explored.add(current.state)

        # generate its children and add to frontier if not already explored
        for next_state, action in maze.getChildren(current.state):
            if next_state not in explored:
                child = Node(
                    state = next_state,
                    parent = current,
                    action = action,
                    gCost = current.gCost + 1,
                    hCost = heuristic(next_state, maze),
                )
                heapq.heappush(frontier, child)
                nodes_generated += 1

    return [], nodes_generated, nodes_expanded  # no solution found


def reconstruct_path(node: Node):
    # print out the path used to find goal node
    # follow parent pointers from goal back to start, then reverse it
    
    path = []
    while node is not None:
        path.append(node.state)
        node = node.parent
    path.reverse()
    return path

def print_results(path, nodes_generated, nodes_expanded):
    # print search results in proper format

    if not path:
        print("No solution exists.")
    else:
        print("\nPath:")
        for state in path:
           print(f"({state[0]}, {state[1]}, top={state[2].get_top()})")
        print(f"\nPath Length: {len(path) - 1} moves") # subtract 1 since path includes the initial state

    print(f"Nodes Generated: {nodes_generated}")
    print(f"Nodes Expanded: {nodes_expanded}\n")

def main():

    # make sure user provides correct input
    if len(sys.argv) != 2:
        print("Usage: python blockmaze.py <maze_file.txt>")
        return

    maze_file = sys.argv[1]
    maze = Maze(maze_file)
    maze.printMaze()

    # initial state: start position, die with 1 on top, 2 north, 3 east
    initial_state = (maze.start[0], maze.start[1], Dice())

    # run A* search with both heuristics and print results
    print("\nRunning A* search with Manhattan Distance heuristic...\n")
    path, nodes_generated, nodes_expanded = find_path(initial_state, maze, heuristicManhattan)
    print_results(path, nodes_generated, nodes_expanded)

    print("\nRunning A* search with Reorientation Heuristic (Manhattan Distance + Orientation Penalty)...\n")
    path, nodes_generated, nodes_expanded = find_path(initial_state, maze, heuristicReorientation)
    print_results(path, nodes_generated, nodes_expanded)

if __name__ == '__main__':
    main()


   

    
    
    

    

