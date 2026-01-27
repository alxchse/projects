// Alexandra Chase
// 30 November 2022
// CSCI 131 
// Lab 11
// This program will make a box on the screen using a specific color.

import java.awt.Color;

public class Box {

private double x, y;                           // initialize coordinates
private double width, height;                  // initialize w and h
private Color ColorBord, ColorFill;            // initialize colors

    public Box(double x, double y, double width, double height) {

    this.x = x;
    this.y = y;
    this.width = width;
    this.height = height;
    this.ColorBord = StdDraw.BLACK;
    this.ColorFill = StdDraw.RED;

    } // end of publicBox

    public void draw() {

        StdDraw.setPenColor(ColorFill);
        StdDraw.filledRectangle(x, y, width/2.0, height/2.0);
        StdDraw.setPenColor(ColorBord);
        StdDraw.rectangle(x, y, width/2.0, height/2.0);
    
    } // end of draw

    public double getLeft() {
        return x - width/2.0;
    }

    public double getRight() {
        return x + width/2.0;
    }

    public double getBottom() {
        return y - height/2.0;
    }

    public double getTop() {
        return y + height/2.0;
    }

    public boolean contains(double px, double py) {
        if ((this.getLeft() <= px && px <= this.getRight()) && (this.getBottom() <= py && py <= this.getTop())) {
            return true;
        }
        return false;
    } // end of contains

    public void setFillColor(Color c) {
        ColorFill = c;
    }

    public void setBorderColor(Color c) {
        ColorBord = c;
    }

    public boolean touching(Box other) {
        if (this.getRight() <= other.getLeft())     // check right side
            return false;
        if (this.getBottom() >= other.getTop())     // check bottom side
            return false;
        if (this.getTop() <= other.getBottom())      // check top side
            return false;
        if (this.getLeft() >= other.getRight())      // check left side
            return false;
    return true; 
    } // end of touching

    


} // end of Box