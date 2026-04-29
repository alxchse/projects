Readme · MD
Copy

# Star Battle SAT Solver
 
A Python program that solves Star Battle puzzles using a SAT solver.
 
## Requirements
 
Python 3 and the `python-sat` package. Install it with:
 
```
pip install python-sat
```
 
## How to Run
 
```
python starbattle.py <puzzle_file>
```
 
For example:
 
```
python starbattle.py puzzle1.txt
```
 
## Input Format
 
The puzzle file must be a plain text file structured as follows:
 
- **Line 1**: A single integer (1, 2, or 3) representing the number of stars required in each row, column, and region.
- **Remaining lines**: The puzzle grid, where:
  - `+` marks grid corners/intersections
  - `-` marks horizontal walls between regions
  - `|` marks vertical walls between regions
  - ` ` (space) marks an empty playable cell
 
Example puzzle file (`puzzle1.txt`):
 
```
1
+-+-+-+-+-+
| | |   | |
+-+ + +-+ +
|   | |   |
+ + +-+-+ +
|   |   | |
+ + + + +-+
|   |     |
+-+-+ + + +
|         |
+-+-+-+-+-+
```
 
## Output
 
If a solution exists, the program prints the puzzle grid with stars placed as `*`:
 
```
+-+-+-+-+-+
|*| |   | |
+-+ + +-+ +
|   |*|   |
+ + +-+-+ +
|   |   |*|
+ + + + +-+
|  *|     |
+-+-+ + + +
|      *  |
+-+-+-+-+-+
```
 
If no solution exists, the program prints:
 
```
No solution exists.
```
 
## How It Works
 
1. **Parsing**: Reads the puzzle file and builds a 2D character grid.
2. **Region extraction**: Uses BFS (breadth-first search) to identify all distinct regions by following walls in the grid.
3. **SAT encoding**: Encodes the puzzle rules as a boolean formula in CNF (conjunctive normal form):
   - Exactly k stars per row
   - Exactly k stars per column
   - Exactly k stars per region
   - No two stars may be adjacent, including diagonally
4. **Solving**: Passes the formula to the Glucose3 SAT solver via PySAT to find a satisfying assignment.
5. **Output**: Prints the solved grid, or reports that no solution exists.
