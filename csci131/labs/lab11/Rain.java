// Author: K. Walsh
// Date: 16 Nov, 2021
//
// Create and draw a very simple house (just a single Box), print out some
// information about it, and then animate a scene with falling raindrops. When
// the raindrops hit the house, they disappear and are replaced by new
// raindrops.

import java.awt.Color;

public class Rain {

    // Create a small blue ball randomly somewhere near the top half of the
    // screen, and set the speed so it is heading downwards to the right.
    public static Ball makeRaindrop(double height) {
        Ball raindrop =  new Ball(StdRandom.uniform(0.0, 1.0), StdRandom.uniform(height, 1.0), 0.01);
        raindrop.setVelocity(StdRandom.uniform(0.03, 0.05), -0.1); // downwards slaning to the right
        raindrop.setColor(Color.BLUE);
        return raindrop;
    }

    public static void main(String args[]) {

        // Create a large box near the bottom center of the screen.
        Box house = new Box(0.5, 0.15, 0.5, 0.3);

        StdOut.printf("   Left edge of house is at coordinates x=%.2f\n", house.getLeft());
        StdOut.printf("  Right edge of house is at coordinates x=%.2f\n", house.getRight());
        StdOut.printf(" Bottom edge of house is at coordinates y=%.2f\n", house.getBottom());
        StdOut.printf("    Top edge of house is at coordinates y=%.2f\n", house.getTop());

        // Make lots of small raindrops.
        Ball rain[] = new Ball[200];
        for (int i = 0; i < rain.length; i++) {
            rain[i] = makeRaindrop(house.getTop());
        }

        // Animate the scene.
        while (true) {
            StdDraw.clear(Color.LIGHT_GRAY);
            house.draw();

            for (int i = 0; i < rain.length; i++) {
                rain[i].move(20);
                rain[i].wrap(); // wrap around the edge of the screen
                
                // If the raindrop touches the house, make a new raindrop to replace it.
                if (house.contains(rain[i].getX(), rain[i].getY()))
                    rain[i] = makeRaindrop(house.getTop());
                rain[i].draw();
            }

            // Show the scene for a fraction of a second.
            StdDraw.show(20);
        } // end of animation loop

    } // end of main

} // end of Rain
