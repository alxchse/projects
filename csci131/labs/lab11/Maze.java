// Author: K. Walsh
// Date: 16 Nov, 2021
// Modified by:
// Modified date:
//
// Create and draw a maze-like obstacle course using N random colored boxes,
// where N is a command-line parameter. This also draws an animated ball
// bouncing around the maze.

import java.awt.Color;

public class Maze {

    // This static function checks whether a given Box, b, touches any of the
    // boxes in the given partially-filled array. The parameter n is the count
    // of Box objects in the array.
    public static boolean touchingAny(Box b, Box[] list, int n) {
        for (int i = 0; i < n; i++) {
             if (b.touching(list[i]))
                 return true;
        }
        return false;
    }

    // This static function creates an array and fills it with N Box objects, at
    // random locations and with random sizes. Each new box is compared with the
    // previous ones to ensure none of the boxes touch each other. Only boxes
    // that are not touching each other are added to the array. The boxes are
    // given random border and fill colors.
    public static Box[] generateRandomWalls(int N) {
        // Create the array
        Box[] walls = new Box[N];
        int numWalls = 0;
        // Repeatedly make a box, then add it to the array if it's not touching
        // any other previous box.
        while (numWalls < N) {
            // Make a new random box
            Box b = new Box(
                    StdRandom.uniform(0.0, 1.0), // x
                    StdRandom.uniform(0.0, 0.75), // y
                    StdRandom.uniform(0.05, 0.15), // width
                    StdRandom.uniform(0.03, 0.10)); // height
            // Only if it's not touching any of the previous ones, add it to the
            // list and give it a nice color.
            if (!touchingAny(b, walls, numWalls)) {
                // Pick a nice color for the border and fill.
                float hue = (float)StdRandom.uniform();
                Color light = Color.getHSBColor(hue, 0.7f, 0.6f);
                Color dark = Color.getHSBColor(hue, 0.5f, 0.3f);
                b.setFillColor(light);
                b.setBorderColor(dark);
                // Add it to the array, and increment the count.
                walls[numWalls] = b;
                numWalls++;
            }
        }
        // Return the array, which should now be completely filled with Box objects.
        return walls;
    }

    public static void main(String args[]) {
    
        // Use a slightly wider pen than usual, so we can see the box borders.
        StdDraw.setPenRadius(0.005);

        int N = Integer.parseInt(args[0]);
        StdRandom.setSeed(N); // this ensures we get the same random sequence each time

        StdOut.printf("Generating %d random boxes...\n", N);
        Box[] walls = generateRandomWalls(N);

        StdOut.printf("Generating 1 ball...\n");
        // Make one ball, at the top center, moving slightly right and upwards
        Ball ball = new Ball(0.5, 0.9, 0.02);
        ball.setVelocity(0.1, 0.05);
  
        StdOut.printf("Drawing the scene...\n");

        while (true) {
            // Make the ball feel gravity, move, and bounce off edges of the screen.
            ball.gravity(20);
            ball.move(20);
            ball.bounce();

            for (int i = 0; i < walls.length; i++) 
                ball.bounce(walls[i]);

            // Draw the scene.
            StdDraw.clear(StdDraw.WHITE);
            for (int i = 0; i < walls.length; i++) {
                walls[i].draw();
            }
            ball.draw();
            StdDraw.show(20);
        } // end of animation loop.

    } // end of main

} // end of Maze
