#ifndef MAZE_H_
#define MAZE_H_

// The following color constants are useful as markers in the maze. Although any
// integer can work as a marker, using these integers will result in a nice
// colorful output when calling Maze::print().
const int BLANK = 0;
const int YELLOW = 1;
const int MAGENTA = 2;
const int RED = 3;
const int GREEN = 4;
const int BLUE = 5;
const int CYAN = 6;
const int WHITE = 7;


// A Maze object represents a 2d (rectangular) maze with horizontal and vertical
// walls. Colored markers can be set at different positions, like leaving a
// trail of breadcrumbs.
class Maze {
  public:

    // Printing is colorful by default. If this doesn't work in the terminal
    // being used, set Maze::printInColor = false.
    static bool printInColor;

    // Animation is enabled by default. This will print the entire maze
    // every time a marker is added or removed. To disable the animation, set
    // Maze::animated = false;
    static bool animated;

    // Animation goes pretty slow by default (slowness = 100). To get quicker
    // animation, set Maze::animationSlowness to a smaller value.
    static int animationSlowness;

    // By default, generated mazes will be solvable and will have have no
    // cycles, meaning that any path through the maze can't possibly lead back
    // to itself, and for any two points in the maze, there will always be
    // exactly one path leading from one to the other.

    // To allow cycles in the maze, set Maze::allowCycles = true.
    static bool allowCycles;

    // To allow unsolvable mazes, set set Maze::allowUnsolvable = true.
    static bool allowUnsolvable;

    // Note: Maze has no default constructor.
    
    // Construct a maze with the given width and height, initialized with a
    // random set of walls. Initially, the bottom right corner will be marked in
    // MAGENTA, to represent the "exit" point for the maze.
    //
    // Note: the coordinate system for the maze uses
    // "screen coordinates", where x moves from left to right, and y moves from
    // top to bottom. So she maze corners will be:
    //   location (x=0, y=0) for the top left corner,
    //   location (x=w-1, y=0) for the top right corner,
    //   location (x=0, y=h-1) for the bottom left corner,
    //   location (x=w-1, y=h-1) for the bottom right corner.
    // This coordinate system is "upside-down" compared to a graphical coordinat
    // system used in mathematics. It might help to think of x as the column
    // number, and y as the row number, rather than as x, y axis.
    //
    // The seed value is used to seed the random number generator. Using the
    // same seed will generate the same random maze each time. Using 0 for the
    // seed will generate a random maze based on the time of day instead.
    Maze(int w, int h, int seed);

    // Get the width of the maze. The x coordinates range from 0 to width-1.
    int getWidth();

    // Get the height of the maze. The y coordinates range from 0 to height-1.
    int getHeight();

    // Print this maze to standard output.
    void print( );

    // Mark the given (x, y) location in the maze. Any integer value between 1
    // and 99 is acceptable to use as the color, but using the color constants
    // defined above will result in a pretty color output when calling
    // print(). Marker 0 is the default value, and shows as a blank.
    void markPosition(int x, int y, int color);

    // Get the marker for the given (x, y) location in the maze. If a marker was
    // previously set using markPosition(), that value will be returned here. If
    // no marker was previously set of this location, then BLANK will be
    // returned.
    int getMarker(int x, int y);

    // Get information about possible walls adjacent to the given (x, y)
    // location in the maze. Each location may have walls to the left, right,
    // above, or below.
    bool hasWallLeft(int x, int y);
    bool hasWallRight(int x, int y);
    bool hasWallAbove(int x, int y);
    bool hasWallBelow(int x, int y);

  private:

    static const int MAX_WIDTH = 100;   // Maximum dimensions.
    static const int MAX_HEIGHT = 100;

    int moves; // Count of how many times markPosition was called.
    int width, height; // Actual dimensions.

    bool topWall[MAX_WIDTH][MAX_HEIGHT+1]; // Wall and marker data.
    bool leftWall[MAX_WIDTH+1][MAX_HEIGHT];
    int marker[MAX_WIDTH][MAX_HEIGHT];

    // Remove all horizontal and vertical walls, and clear all markers, except
    // for a single MAGENTA marker in the bottom right corner, and a series of
    // walls around the outside borders of the maze.
    void clear( );

    // Generate a random maze.
    void generate(int seed);

    // Mutually recursive methods to fill a given area with walls.
    void fillRandomWalls(int left, int top, int right, int bottom);
    void divideHorizontally(int left, int top, int right, int bottom, int x, int y);
    void divideVertically(int left, int top, int right, int bottom, int x, int y);
};

#endif
