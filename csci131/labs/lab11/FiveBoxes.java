// Author: K. Walsh
// Date: 16 Nov, 2021
//
// Create and draw five Box objects on the screen in a nice pattern.

public class FiveBoxes {

    public static void main(String args[]) {

        // Clear the screen, and make the pen size a little thicker than usual.
        StdDraw.clear(StdDraw.WHITE);
        StdDraw.setPenRadius(0.01);

        // A large rectangle in the middle.
        Box middle = new Box(0.5, 0.5, 0.6, 0.6);
        middle.draw();
        
        // Four smaller rectangles around the edges.
        Box a = new Box(0.15, 0.5, 0.02, 0.6);
        a.draw();

        Box b = new Box(0.85, 0.5, 0.02, 0.6);
        b.draw();

        Box c = new Box(0.5, 0.15, 0.6, 0.02);
        c.draw();

        Box d = new Box(0.5, 0.85, 0.6, 0.02);
        d.draw();

        // Show everything on the screen.
        StdDraw.show();

    } // end of main

} // end of FiveBoxes
