// Author: K. Walsh
// Date: 16 Nov, 2021
//
// Create and draw a simple pyramid temple using Box objects as the bricks.

public class Pyramid {

    public static void main(String args[]) {

        double brickWidth = 0.08;
        double brickHeight = 0.03;

        StdDraw.clear(StdDraw.WHITE);

        // Create and draw one brick near the middle.
        double x = 0.5, y = 0.5;
        Box brick = new Box(x, y, brickWidth, brickHeight);
        brick.draw();

        // Now create and draw more bricks in a pattern below the center one.
        // The first layer will have 2 bricks, the layer below that will have 3
        // bricks, etc.
        for (int layer = 2; layer < 10; layer++) {
            x -= brickWidth/2; // adjust coordinate left a little bit
            y -= brickHeight; // adjust coordinate lower a little bit
            // Now make the bricks in this layer
            for (int i = 0; i < layer; i++) {
                // Create and draw another brick in this layer
                brick = new Box(x+brickWidth*i, y, brickWidth, brickHeight);
                brick.draw();
            }
        }

        // Lastly, make two pillars near the bottom. These are just tall
        // rectangles.
        Box leftPillar = new Box(0.25, 0.125, 0.03, 0.25);
        Box rightPillar = new Box(0.75, 0.125, 0.03, 0.25);
        leftPillar.draw();
        rightPillar.draw();

        // Show everything on the screen
        StdDraw.show();

    } // end of main

} // end of Pyramid
