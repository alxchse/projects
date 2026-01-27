// Alexandra Chase
// amchas26@g.holycross.edu
// Project 6
// 29 March 2023

#include "Maze.h"
#include <iostream>
#include <cassert>
#include <ctime>
#include <unistd.h>
using namespace std;

int randInRange(int lo, int hi);

bool Maze::printInColor = true;
bool Maze::animated = true;
int Maze::animationSlowness = 100;
bool Maze::allowCycles = false;
bool Maze::allowUnsolvable = false;

Maze::Maze(int w, int h, int seed) {
  assert(w > 1 && h > 1 && w <= MAX_WIDTH && h <= MAX_HEIGHT);
	width = w;
	height = h;
  moves = 0;
  generate(seed);
}  // end constructor

void Maze::generate(int seed) {
	clear();
  if (seed == 0) {
    seed = (int)time(NULL);
    cout << "To re-play this random maze, use seed " << seed << endl;
    srand(seed);
  } else {
    srand(seed);
  }
	fillRandomWalls(0, 0, width, height);
  if (allowUnsolvable) {
    // Add a handful of random walls, which could block the solution
    for (int i = 0; i < min(width, height)/4; i++) {
      if ((rand() % 2) == 0) {
        int x = randInRange(0, width - 1);
        int y = randInRange(1, height - 1);
        topWall[x][y] = true;
      } else {
        int x = randInRange(1, width - 1);
        int y = randInRange(0, height - 1);
        leftWall[x][y] = true;
      }
    }
  }
  if (allowCycles) {
    // Remove a handful of random walls, which could create cycles the solution
    for (int i = 0; i*i < 5*width*height; i++) {
      if ((rand() % 2) == 0) {
        int x = randInRange(0, width - 1);
        int y = randInRange(1, height - 1);
        topWall[x][y] = false;
      } else {
        int x = randInRange(1, width - 1);
        int y = randInRange(0, height - 1);
        leftWall[x][y] = false;
      }
    }
  }
}

void Maze::clear() {
  // Clear all internal walls.
	for (int i = 1; i < width; i++) {
		for (int j = 1; j < height; j++) {
			topWall[i][j] = false;
			leftWall[i][j] = false;
    }
  }
  // Clear all markers
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			marker[i][j] = 0;
		}
  }
  // Create walls around the outer borders.
  for (int i = 0; i < width; i++) {
    topWall[i][0] = true;
    topWall[i][height] = true;
  }
  for (int j = 0; j < height; j++) {
    leftWall[0][j] = true;
    leftWall[width][j] = true;
  }
  // Mark the exit in MAGENTA in the bottom right corner
	marker[width - 1][height - 1] = MAGENTA;
}  // end clear

void Maze::fillRandomWalls(int left, int top, int right, int bottom) {
	// cout << "Entering fillRandomWalls\n";
  if ((top == bottom - 1) || (left == right - 1)) {
    // Base case: nothing left to do
		return;
	} else {
    // Recursive case: pick random doorway, split remaining area in two pieces
    // cout << "Filling: left = " << left << ", top = " << top
    //            << ", right = " << right << ", bottom = " << bottom << endl;
    // Pick a random doorway
    int x, y;
    do {
      x = randInRange(left, right - 1);
      y = randInRange(top, bottom - 1);
    } while (x == left && y == top);
    // Divide either horizontally or vertically
    if (x == left || (y != top && min(x-left, right-x) < min(y-top, bottom-y)))
			divideHorizontally(left, top, right, bottom, x, y);
		else 
			divideVertically(left, top, right, bottom, x, y);
  }
}  // end fillRandomWalls

void Maze::divideHorizontally(int left, int top, int right, int bottom, int x, int y) {
	// cout << "Dividing horizontally, with doorway at x = " << x << ", y = " << y << endl;
  // Build a horizontal wall across the entire area
	for (int i = left; i < right; i++)
		topWall[i][y] = (i != x);
  // Fill in the two remaining areas, recursively
	fillRandomWalls(left, y, right, bottom);
	fillRandomWalls(left, top, right, y);
}  // end divideHorizontally

void Maze::divideVertically(int left, int top, int right, int bottom, int x, int y) {
	// cout << "Dividing vertically, with doorway at x = " << x << ", y = " << y << endl;
  // Build a vertical wall across the entire area
	for (int j = top; j < bottom; j++) 
		leftWall[x][j] = (j != y);
  // Fill in the two remaining areas, recursively
	fillRandomWalls(left, top, x, bottom);
	fillRandomWalls(x, top, right, bottom);
}  // end divideVertically

void colorPrint(int color, int val) {
  if (!Maze::printInColor)
    color = BLANK;
  // Use ancient ANSI escape sequences to print in color
  switch (color) {
    case YELLOW:  printf("\033[43;30m%-2d\033[m", val); break;
    case MAGENTA: printf("\033[45m%-2d\033[m", val); break;
    case RED:     printf("\033[41m%-2d\033[m", val); break;
    case GREEN:   printf("\033[42m%-2d\033[m", val); break;
    case BLUE:    printf("\033[44m%-2d\033[m", val); break;
    case CYAN:    printf("\033[46m%-2d\033[m", val); break;
    case WHITE:   printf("\033[47;30m%-2d\033[m", val); break;
    default: printf("%-2d", val); break;
  }
}

void Maze::print( ) {
  cout << "Maze (" << width << " x " << height << ") with "
    << moves << " moves so far.\n";
	for (int j = 0; j <= height; j++) { // for each row of the maze
    // Print walls above this row
		for (int i = 0; i < width; i++) {
      if ((j != height && leftWall[i][j]) || (j > 0 && leftWall[i][j-1])) {
        if (i > 0 && topWall[i-1][j])
          cout << (topWall[i][j] ? "+--" : "+  ");
        else
          cout << (topWall[i][j] ? "+--" : "|  ");
      } else {
        cout << (topWall[i][j] ? "---" : "   ");
      }
    }
    cout << (topWall[width-1][j] ? "+\n" : "|\n");
    // The last row has no markers or vertical walls
    if (j == height)
      break;
    // Print the markers and vertical walls in this row
		for (int i = 0; i <= width; i++) { // for each column of the maze
			if (leftWall[i][j]) 
				cout << "|";
			else 
				cout << " ";
      // The last column has no markers
      if (i == width)
        break;
      int val = marker[i][j];
      if (val == BLANK)
        cout << "  ";
      else
        colorPrint(val, val);
		}
		cout << endl;
  }  // for each row of the maze
}  // end print

void Maze::markPosition(int x, int y, int val)
{
	if ((x < 0) || (x >= width) || (y < 0) || (y >= height)) {
		cout << "Error!  Position (" << x << ", " << y << ") out of range!  Can't set marker.\n";
  } else if (val < 0 || val > 99) {
		cout << "Error!  Marker value " << val << " is not valid. Can't set marker.\n";
  } else {
		marker[x][y] = val;
    moves++;
    if (animated) {
      print();
      if (animationSlowness > 0)
        usleep(animationSlowness*1000);
    }
  }
}  // end markPosition

int Maze::getMarker(int x, int y)
{
	if ((x < 0) || (x >= width) || (y < 0) || (y >= height)) {
		cout << "Error!  Position (" << x << ", " << y << ") out of range!  Can't get marker.\n";
    return -1;
  } else {
		return marker[x][y];
  }
}  // end getMarker

bool Maze::hasWallLeft(int x, int y) {
	if ((x < 0) || (x >= width) || (y < 0) || (y >= height)) {
		cout << "Error!  Position (" << x << ", " << y << ") out of range!  Can't check for left wall.\n";
    return true;
  } else {
		return leftWall[x][y];
  }
}  // end hasWallLeft

bool Maze::hasWallRight(int x, int y) {
	if ((x < 0) || (x >= width) || (y < 0) || (y >= height)) {
		cout << "Error!  Position (" << x << ", " << y << ") out of range!  Can't check for right wall.\n";
    return true;
  } else {
		return leftWall[x+1][y];
  }
}  // end hasWallRight

bool Maze::hasWallAbove(int x, int y) {
	if ((x < 0) || (x >= width) || (y < 0) || (y >= height)) {
		cout << "Error!  Position (" << x << ", " << y << ") out of range!  Can't check for above wall.\n";
    return true;
  } else {
		return topWall[x][y];
  }
}  // end hasWallAbove

bool Maze::hasWallBelow(int x, int y) {
	if ((x < 0) || (x >= width) || (y < 0) || (y >= height)) {
		cout << "Error!  Position (" << x << ", " << y << ") out of range!  Can't check for below wall.\n";
    return true;
  } else {
		return topWall[x][y+1];
  }
}  // end hasWallBelow
	
int Maze::getWidth( ) {
	return width;
}  // end getWidth

int Maze::getHeight( ) {
	return height;
}  // end getHeight

// randInRange returns a random integer in the range lo to hi, inclusive.
int randInRange(int lo, int hi)
{
    return lo + (int)((double)rand()/((double)RAND_MAX+1.0) * (double)(hi-lo+1));
}
