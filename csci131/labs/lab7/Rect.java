// Alexandra Chase
// CSCI 131
// 30 October 2022
// Lab 7

public class Rect{
    public static void main(String[] args) {
        int n;
        int width;
        int height;
        printRectangle(10, 4);
        printRectangle(6, 8);
    } // end of main

    public static void printRectangle (int width, int height) {

        for (int count = 0; count < height; count++) {
            Bar.repeatedlyPrintX(width);
        }
    } // end of printRectangle
    
} // end of class
