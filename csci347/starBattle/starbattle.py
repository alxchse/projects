# Alexandra Chase and Elios Hoxholli
# amchas26@g.holycross.edu, ehoxho27@g.holycross.edu
# CSCI 347
# 30 March 2026
# Project 2: Logic Project

# This program solves Star Battle puzzles by encoding the puzzle constraints into a CNF formula and using the PySAT library to find a solution.
# The program reads a puzzle from a text file, identifies the distinct regions using BFS, encodes the constraints for rows, columns, and regions.
# Then uses a SAT solver to find a valid placement of stars. Finally, it prints the solved grid with stars placed in the correct locations.

import sys
from collections import deque
from pysat.formula import CNF
from pysat.card import CardEnc, EncType
import pysat.solvers



# Reads a Star Battle puzzle from a text file.
# Args: filepath (str): The path to the puzzle text file.
# Returns:
# int k: The number of stars required per row, column, and region.
# int n: grid size n x n
# list of list grid A 2D grid representing the puzzle characters.
def parse_puzzle(filepath):

    with open(filepath, 'r') as file:
        lines = file.readlines()
            
    # the first line specifies the number of stars (1, 2, or 3)
    k = int(lines[0].strip())

    # the remaining lines make up the puzzle grid
    # we strip the newline character but preserve spaces, as " " represents empty playable spaces
    grid = [list(line.strip('\n')) for line in lines[1:]]
    
    # grid size: original 2D grid has has 2n+1 rows and 2n+1 cols. so N is calculated by removing "excess" chars
    n = (len(grid) - 1) // 2
        
    return k, n, grid

# Uses Breadth-First Search (BFS) to find all distinct regions in the Star Battle grid.
# The BFS process is to look at 
# Args: grid 
# Returns: region list of list of tuple: A list of regions, where each region is a list of (row, col) coordinates of the playable spaces.      
def find_regions(grid):

    visited = set()
    regions = []
    
    rows = len(grid)
    cols = len(grid) if rows > 0 else 0
    
    for r in range(1, rows, 2):
        for c in range(1, cols, 2):
            if (r, c) not in visited:
                current_region = []
                queue = deque([(r, c)])
                
                while queue:
                    curr_r, curr_c = queue.popleft()
                    
                    if (curr_r, curr_c) in visited:
                        continue
                        
                    visited.add((curr_r, curr_c))
                    current_region.append((curr_r, curr_c))
                    
                    # Check UP: wall at (curr_r - 1, curr_c)
                    if curr_r - 2 >= 0 and grid[curr_r - 1][curr_c] != "-":
                        queue.append((curr_r - 2, curr_c))
                        
                    # Check DOWN: wall at (curr_r + 1, curr_c)
                    if curr_r + 2 < rows and grid[curr_r + 1][curr_c] != "-":
                        queue.append((curr_r + 2, curr_c))
                        
                    # Check LEFT: wall at (curr_r, curr_c - 1)
                    if curr_c - 2 >= 0 and grid[curr_r][curr_c - 1] != "|":
                        queue.append((curr_r, curr_c - 2))
                        
                    # Check RIGHT: wall at (curr_r, curr_c + 1)
                    if curr_c + 2 < cols and grid[curr_r][curr_c + 1] != "|":
                        queue.append((curr_r, curr_c + 2))
                        
                if current_region:
                    regions.append(current_region)
                    
    return regions

# convert puzzle cell coordinate (r,c) to a single int that represents that cell ((rows * n) + (col))
# + 1 because PySAT solver is 1-indexed rather than 0. 
def convert2SAT(r, c, n):
    return r * n + c + 1

# encodes into meaningful constraints that can be used by the PySAT solver
def encode(n, k, regions):
    cnf = CNF()
    top = n * n # necessary for CardEnc to know where to start (the max variable int) 

    # use sequential counter encoding to enforce exactly k true variables in the list of ids
    def constraints(ids):
        nonlocal top # allows us to update the top variable from the outer scope
        clauses = CardEnc.equals(ids, bound=k, top_id=top, encoding=EncType.seqcounter)
        cnf.extend(clauses) # add clauses to the main CNF formula
        # update top to be the max variable index used in the new clauses
        if clauses.clauses: 
            top = max(abs(l) for clause in clauses.clauses for l in clause)

    # exactly k stars per row (puzzle coords: rows 0..n-1)
    for r in range(n):
        constraints([convert2SAT(r, c, n) for c in range(n)])

    # exactly k stars per column
    for c in range(n):
        constraints([convert2SAT(r, c, n) for r in range(n)])

    # exactly k stars per region
    # regions are in original 2D grid coordinates, convert back to puzzle coords
    for region in regions:
        ids = [convert2SAT((r - 1) // 2, (c - 1) // 2, n) for r, c in region]
        constraints(ids)

    # no two adjacent stars including diagonals
    # iterate through puzzle coordinates (0..n-1) for rows and columns
    for r in range(n):  
        for c in range(n):
            # for each cell, check all 8 surrounding cells (including diagonals)
            for dr in [-1, 0, 1]: 
                for dc in [-1, 0, 1]:
                    # skip the cell itself (dr=0, dc=0) since we only want to check adjacent cells
                    if dr == 0 and dc == 0:
                        continue
                    # calculate the coordinates of the adjacent cell
                    r2, c2 = r + dr, c + dc
                    # check if the adjacent cell is within bounds of the grid
                    if 0 <= r2 < n and 0 <= c2 < n:
                        # to avoid adding duplicate constraints (e.g., for both (r,c) and (r2,c2)), we can enforce an ordering
                        if (r, c) < (r2, c2):
                            cnf.append([-convert2SAT(r, c, n), -convert2SAT(r2, c2, n)])

    return cnf


# uses the encoded CNF constraints and the PySAT solver to find a valid placement of stars that satisfies all the puzzle rules.
# Args: n (int): grid size, k (int): number of stars per row/col/region, regions (list of list of tuple): list of regions with their coordinates
# Returns: set of tuple: A set of (row, col) coordinates where stars are placed in the solution, or None if no solution exists.
def solve(n, k, regions):
    cnf = encode(n, k, regions) # encode puzzle constraints to CNF
    
    with pysat.solvers.Glucose3(bootstrap_with=cnf) as solver:
        # if it's solvable, get the model (list of variable assignments) and convert back to star coordinates
        if solver.solve():
            model = set(solver.get_model())
            stars = set()
            for r in range(n):
                for c in range(n):
                    # check if the variable corresponding to a star at (r, c) is true in the model before adding
                    if convert2SAT(r, c, n) in model:
                        stars.add((r, c))
            return stars
        else:
            return None
      
# Prints a copy of the grid with empty spaces replaced by their region number.
# This helps debug the BFS parsing matches the 'Maze 1' example in the instructions.
# DOES NOT PRINT THE SOLUTION, just the regions labeled with their index.
def print_labeled_grid(grid, regions):
    
    labeled_grid = [row[:] for row in grid] # create a copy of the grid to modify for labeling
    
    # label each space with its region index (1-based to match the example)
    # region_idx is 0-based, but we want to label regions starting from 1, so we add 1 when converting to string
    for region_idx, region in enumerate(regions): 
        region_num = str(region_idx + 1)
        for r, c in region: 
            labeled_grid[r][c] = region_num
            
    # Print the labeled grid
    print("\nLabeled Puzzle Regions:")
    for row in labeled_grid:
        print("".join(row))


# Print the solved grid with stars placed as '*', using puzzle coords.
# args: the original grid (with walls) AND set of star coordinates
# outputs: a copy of the grid with stars placed in the correct locations.
# This function prints the ACTUAL SOLUTION 
def print_solution(grid, stars):

    print("\nSolved Puzzle:")
    solution = [row[:] for row in grid] 
    for r, c in stars:
        # convert puzzle coords back to original char coordinatess
        solution[2 * r + 1][2 * c + 1] = '*'
    for row in solution:
        print("".join(row))



# main function
if __name__ == "__main__":
    k, n, puzzle_grid = parse_puzzle(sys.argv[1]) # read puzzle from file path provided as command line argument
    puzzle_regions = find_regions(puzzle_grid) # find distinct regions in the puzzle grid using BFS

    # debug: verify regions look right before solving
    print(f"Identified {len(puzzle_regions)} distinct regions.")
    print_labeled_grid(puzzle_grid, puzzle_regions)

    stars = solve(n, k, puzzle_regions) # solve the puzzle using the encoded constraints and the PySAT solver, returning the set of star coordinates

    if stars is None:
        print("No solution exists.")
    else:
        print_solution(puzzle_grid, stars)



