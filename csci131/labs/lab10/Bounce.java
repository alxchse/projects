/*----------------------------------------------------------------
 *  Author:
 *  Email:
 *  Date:
 *
 *  Animation of two stars, one bouncing horizontally, and a ball
 *  at a random location bouncing diagonally.
 *
 *  Example: java Bounce
 *----------------------------------------------------------------*/

import java.awt.Color;
public class Bounce {

    public static void main(String args[]) {

        Star s = new Star(0.0, 0.5, 0.03, 9);
        s.setColor(StdDraw.PINK);


        Star ss =  new Star(0.8, 0.8, 0.08, 7);
        ss.setColor(StdDraw.BLUE);
        ss.setVelocity(0.05, 0);

        Ball b = new Ball(-0.6, -0.7, 0.1);
        b.setColor(new Color(153,153,255));
        b.setVelocity(1.0, 0.5);


        // Loop the animation forever.
        while (true) {

            s.rotateAngle(0.02);
        
            ss.move(20);
            ss.bounce();

            b.move(40);
            b.bounce();
            
            StdDraw.clear(StdDraw.WHITE);
            s.draw();
            ss.draw();
            b.draw();

            // Show the canvas on the screen.
            StdDraw.show(20); // 20ms duration for animation
        }

    }
}
