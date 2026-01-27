/*********************************************************************************
 * Name: Alexandra Chase
 * Date: 29 March 2023
 * Course: CSCI 132
 * Assignment: Project 6
 * Instructor: Fitzsimmons
 * Program: SolveMaze.cpp
 * Purpose: Create a random maze and solves it recursively.
 ********************************************************************************/

#include <iostream>
#include "Maze.h"
using namespace std;

// Try to find a path throught maze from (x, y) to the MAGENTA exit.
// add preconditions, postconditions, and a more complete comment here.
bool solveMaze(Maze &m, int x, int y) {

  // if marker is at the end (magenta) then return true
  if(m.getMarker(x, y) == 2) {
    return true;
  } else if (m.getMarker(x, y) == 1) { // if we have already been to that spot (yellow) then skip
    return false;
  } else {
    if(m.hasWallRight(x, y) == false) { // if theres no wall to the right
      m.markPosition(x, y, 1);          // mark the spot
      if (solveMaze(m, x + 1, y))       // call next spot to the right, if you can go there...
      return true;
    }
    if(m.hasWallLeft(x, y) == false) { // if theres no wall to the left
      m.markPosition(x, y, 1);         // mark spot
      if (solveMaze(m, x - 1, y))      // call next spot to the left, if you can go there...
      return true;
    }
    if(m.hasWallAbove(x, y) == false) { // if theres no wall above
      m.markPosition(x, y, 1);          // mark spot
      if (solveMaze(m, x, y - 1))       // call next spot above, if you can go there...
      return true;
    }
    if(m.hasWallBelow(x, y) == false) { // if theres no wall below
      m.markPosition(x, y, 1);          // mark spot
      if (solveMaze(m, x, y + 1))       // call next spot below, if you can go there...
      return true;
    }
  }
  return false; // Or maybe just give up

}  // end solveMaze

int main(int argc, char **argv)  {

  // Modify the default behavior for Maze class, if desired.
  Maze::printInColor = false;
  Maze::animated = false;
  Maze::animationSlowness = 30; // lower is quicker
  Maze::allowCycles = true;
  Maze::allowUnsolvable = true;

  int width, height, seed;

  if (argc == 4) {
    // Use command-line parameters, if provided
    width = atoi(argv[1]);
    height = atoi(argv[2]);
    seed = atoi(argv[3]);
  } else {
    cout << "Enter width and height for maze: ";
    cin >> width >> height;
    cout << "Enter a seed for the random generator (or 0 for varying): ";
    cin >> seed;
  }

  Maze m(width, height, seed);

  cout << "Maze to be solved:\n";
  m.print();

  bool success = solveMaze(m, 0, 0);

  if (success)
    cout << "Maze is solved:\n";
  else
    cout << "Maze could not be solved:\n";
  m.print();

  return 0;
}  // end main
