/*----------------------------------------------------------------
 *  Author: Alexandra Chase
 *  Email: amchas26@g.holycross.edu
 *  Written: November 09 2022
 *  
 *  Draw a tree, recursively. The number of branching levels is given by a
 *  command line argument.  The incremental angle increase of each branch is
 *  given by a second argument.
 *
 *  Example: java Tree 5 45
 *----------------------------------------------------------------*/
public class Tree {
    public static void main(String[] args) {
        if (args.length != 2) {
            System.out.println("Oops, you should provide exactly two arguments, like this:");
            System.out.println("  java Tree 4 40.0");
            System.exit(1);
        }
        int levels = Integer.parseInt(args[0]);  //Number of levels to draw
        double increment = Double.parseDouble(args[1]);
        StdOut.printf("Drawing a tree with %d levels and angle increment of %f\n", levels, increment);
        StdDraw.setXscale(0, 120);               //Scale the drawing window
        StdDraw.setYscale(0, 120);
        //Draw tree with angle of the trunk given by 90 degrees,
        //the angle of branches given by increment
        //and number of levels given by levels
        drawTree(60, 10, 50, 90.0, increment, levels); 
        StdDraw.show();
    }

    //*********************************************************************
    //drawTree(x, y, length, angle, increment, levels)
    //Purpose: Draw a tree at position (x, y) in the drawing
    //    window, with trunklength given by length, the angle of the
    //    tree trunk given by angle, the angle of the branches
    //    relative to the trunk given by increment, and the number of levels
    //    given by levels.
    //******************************************************************
    public static void drawTree(double x, double y, double length, 
            double angle, double increment, int levels) {

        //Compute endpoint of trunk
        double xEnd = x + Math.cos(Math.toRadians(angle))*length;
        double yEnd = y + Math.sin(Math.toRadians(angle))*length;

        if (levels == 0 ) {                      //Base case
            return;

        } else {                                 //General case
            StdOut.println("Drawing level " + levels + " tree");
            StdDraw.line(x, y, xEnd, yEnd);
            drawTree(xEnd, yEnd, length/2, angle+increment, increment, levels-1);
            drawTree(xEnd, yEnd, length/2, angle-increment, increment, levels-1);

        }
    } // end drawTree
} // end of class
