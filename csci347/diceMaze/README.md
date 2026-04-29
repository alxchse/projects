# Rolling Die Maze Solver

**Authors:** Alexandra Chase and Elios Hoxholli  
**Course:** CSCI 347 Artificial Intelligence  
**Project:** A* Search for Rolling Die Mazes  
**Date:** February 13, 2026

## Project Description

This program solves rolling die maze puzzles using A* search with multiple heuristics. In a rolling die maze, a six-sided die must navigate from a start position to a goal position by rolling (toppling over edges). The die must reach the goal with face 1 on top while avoiding obstacles and ensuring that face 6 never appears on top during the journey.

## Requirements

- Python 3.6 or higher
- Standard library only (no external dependencies)


## Usage

Run the program from the command line with a maze file as an argument:
```bash
python blockmaze.py <maze_file.txt>
```

### Example
```bash
python blockmaze.py maze1.txt
```

## Maze File Format

Maze files should be plain text files with the following characters:
- `.` — Open space (passable)
- `*` — Obstacle (impassable)
- `S` — Start position (die begins here with face 1 on top, 2 facing north, 3 facing east)
- `G` — Goal position (die must reach here with face 1 on top)

### Example Maze File (`maze1.txt`)
```
S...G
.....
```

## Output

The program runs A* search twice (once for each heuristic) and outputs:

1. **Maze layout** with start and goal positions
2. **For each heuristic:**
   - Solution path (sequence of coordinates and die orientations)
   - Path length (number of moves)
   - Nodes generated (total nodes added to frontier)
   - Nodes expanded (total nodes removed from frontier and explored)

### Sample Output
```
Given Maze Layout:
.G*.S.
...*..
.*...*
......
...*..

Start Position: (0, 4), Goal Position: (0, 1)

Running A* search with Manhattan Distance heuristic...


Path:
(0, 4, top=1)
(1, 4, top=2)
(1, 5, top=3)
(0, 5, top=1)
(0, 4, top=2)
(1, 4, top=3)
(2, 4, top=5)
(3, 4, top=4)
(4, 4, top=2)
(4, 5, top=1)
(3, 5, top=4)
(3, 4, top=2)
(3, 3, top=3)
(3, 2, top=5)
(3, 1, top=4)
(4, 1, top=1)
(4, 0, top=2)
(3, 0, top=4)
(2, 0, top=5)
(1, 0, top=3)
(0, 0, top=2)
(0, 1, top=1)

Path Length: 21 moves
Nodes Generated: 128
Nodes Expanded: 101


Running A* search with Reorientation Heuristic (Manhattan Distance + Orientation Penalty)...


Path:
(0, 4, top=1)
(1, 4, top=2)
(1, 5, top=3)
(0, 5, top=1)
(0, 4, top=2)
(1, 4, top=3)
(2, 4, top=5)
(3, 4, top=4)
(4, 4, top=2)
(4, 5, top=1)
(3, 5, top=4)
(3, 4, top=2)
(3, 3, top=3)
(3, 2, top=5)
(3, 1, top=4)
(4, 1, top=1)
(4, 0, top=2)
(3, 0, top=4)
(2, 0, top=5)
(1, 0, top=3)
(0, 0, top=2)
(0, 1, top=1)

Path Length: 21 moves
Nodes Generated: 115
Nodes Expanded: 89
```

## Heuristics Implemented

### 1. Manhattan Distance
Calculates the straight-line grid distance from current position to goal:
```
h(n) = |current_row - goal_row| + |current_col - goal_col|
```

**Admissibility:** Always underestimates because the die cannot reach the goal in fewer moves than the Manhattan distance (ignores obstacles and orientation constraints).

### 2. Manhattan Distance + Orientation Penalty
Extends Manhattan distance with a penalty if the die does not currently have face 1 on top:
```
h(n) = Manhattan distance + (0 if top == 1, else 1)
```

**Admissibility:** The penalty of 1 never overestimates because if the die needs reorientation at the goal, at least one additional move is required.

## Algorithm Details

- **Search Strategy:** A* search with priority queue (min-heap)
- **State Representation:** `(row, col, dice_orientation)`
- **Die Orientation:** Tracked via `(top, north, east)` faces; opposite faces sum to 7
- **Successor Generation:** Four cardinal directions (North, South, East, West)
- **Constraints:** 
  - No stepping on obstacles
  - Face 6 never on top
  - Goal only satisfied with face 1 on top

## File Structure
```
blockmaze.py        # Main program file
maze1.txt           # Example maze file
maze2.txt           # Example maze file
maze3.txt           # Example maze file
maze4.txt           # Example maze file
maze5.txt           # Example maze file
README.md           # This file
project1.pdf        # Project writeup
discussion.txt      # Team discussion log
```

## Known Limitations

- Assumes rectangular mazes (all rows same width)
- No support for weighted edges (all moves cost 1)
- Die orientation is tracked but rotation around vertical axis is simplified

## Testing

Test the program with the provided maze files to verify correctness:
- `maze1.txt` — Simple 2×5 maze (should solve quickly)
- `maze2.txt` — Medium complexity with obstacles
- `maze3.txt` — Narrow corridors
- `maze4.txt` — Scattered obstacles
- `maze5.txt` — Large 12×12 maze

## Troubleshooting

**Error: "Maze has no start" or "Maze has no goal"**
- Ensure your maze file contains exactly one 'S' and one 'G'

**Error: "Invalid character in maze"**
- Only `.`, `*`, `S`, and `G` are valid characters

**Program runs but finds no solution**
- Verify the goal is reachable
- Check that there's a path avoiding obstacles where 6 never lands on top

## Authors' Notes

This implementation prioritizes clarity and correctness. The dual-heuristic comparison demonstrates how different admissible heuristics affect search efficiency while guaranteeing optimal solutions.
