/*----------------------------------------------------------------
 *  Author: Alexandra Chase
 *  Email: amchas26@g.holycross.edu
 *  Written: 11/16/22
 * 
 *  A game similar to https://agar.io/, in which the user controls a round blob
 *  with the mouse and tries to eat smaller round blobs and avoid spikey shapes.
 *
 *  Example: java Agar
 *----------------------------------------------------------------*/
import java.awt.Color;
public class Agar {

    // Create a small ball with random position and velocity.
    public static Ball launchRandomBall() {
    Ball b = new Ball(StdRandom.uniform(), StdRandom.uniform(), 0.04);
    b.setHue(Math.random());
    b.aimTowards(StdRandom.uniform(), StdRandom.uniform(), 0.3);
    return b;
    }

    // Make the player blob eat the food blob by growing larger.
    public static void eat(Ball player, Ball food) {
        player.grow(food.size());
        System.out.printf("Yum! Now I am %.5f big!\n", player.size());
    }

    // Poison the player blob by shrinking it.
    public static void poison(Ball player) {
        player.grow(-player.size()/4.0);
        StdOut.printf("Ack! I shrank to %.5f small!\n", player.size());
    }

    public static void main(String args[]) {

        // Create a medium-sized ball for the player.
        Ball player = new Ball(0.8, 0.2, 0.05);
        player.setColor(StdDraw.RED);

        Ball food1 = launchRandomBall();
        Ball food2 = launchRandomBall();

        // Create a star to act as poison.

        // Loop the animation forever.
        while (true) {

            // Update player so it is aiming towards the mouse.
            player.aimTowards(StdDraw.mouseX(), StdDraw.mouseY(), 1.0/6.0);

            // Make the player bounce off the edge of the screen.
            player.bounce();

            // Make the food blobs bounce off the edge of the screen.
            food1.bounce();
            food2.bounce();

            // Move the player.
            player.move(20);

            // Move the food blobs.
            food1.move(20);
            food2.move(20);

            // Eat the food
            if (player.covering(food1)) {
                eat(player,food1);
                food1 = launchRandomBall();
            }

            if (player.covering(food2)) {
                eat(player,food2);
                food2 = launchRandomBall();
            }

            // (extra): Check if the player has touched the poison. If so,
            // call the poison() function above.

            // Draw the scene on the StdDraw canvas.
            StdDraw.clear(StdDraw.WHITE);

            // Draw the two food balls.
            food1.draw();
            food2.draw();

            // (extra): Draw the poison.

            // Draw the player.
            player.draw();

            // Show the canvas on the screen.
            StdDraw.show(20);
        }
    }       
}           // end of class
