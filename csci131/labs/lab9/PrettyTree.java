
import java.awt.Color;

public class PrettyTree {
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

        drawTree(60, 10, 50, 90.0, increment, levels); 
        StdDraw.show();
    } // end of main

    public static void drawTree(double x, double y, double length, 
            double angle, double increment, int levels) {

        //Compute endpoint of trunk
        double xEnd = x + Math.cos(Math.toRadians(angle))*length;
        double yEnd = y + Math.sin(Math.toRadians(angle))*length;
        double leafRadius = 2;
        double randAngle1 = angle + StdRandom.uniform(0, 20);
        double randAngle2 = angle - StdRandom.uniform(0, 20);

        if (levels == 0 ) {                      //Base case
            return;

        } else {                                 //General case
            StdOut.println("Drawing level " + levels + " tree");
            StdDraw.line(x, y, xEnd, yEnd);
            StdDraw.setPenColor(Color.GREEN);
            StdDraw.filledCircle(xEnd, yEnd, leafRadius);
            StdDraw.setPenColor(Color.BLACK);
                if (levels > 4) {
                    drawTree(xEnd, yEnd, length/2, randAngle1, increment, levels-1); 
                    drawTree(xEnd, yEnd, length/2, randAngle2, increment, levels-1); 
                }
            drawTree(xEnd, yEnd, length/2, angle+increment, increment, levels-1);
            drawTree(xEnd, yEnd, length/2, angle-increment, increment, levels-1);

            StdDraw.show();
            return;
        }
    } // end drawTree
} // end of class