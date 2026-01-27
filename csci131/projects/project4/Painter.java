/*----------------------------------------------------------------
 *  Original author: K. Walsh (kwalsh@holycross.edu)
 *  Date: 6 Nov, 2021
 *  Modified by: Alexandra Chase
 *  Modified date:  11 Nov. 2022
 *  
 *  A graphical, mouse-based painting program. User can use
 *  left-click to draw, and right-click to bucket-fill. A toolbar
 *  with buttons allows the user to select pen colors, quit, save, etc.
 *
 *  Example:  java Painter
 *----------------------------------------------------------------*/


import GUI.*;
import java.awt.Color;

public class Painter extends AsyncEventAdapter {

    // ZOOM controls how zoomed-in the drawing canvas is. It's easiest
    // to see what is happening if we zoom by a factor of 8 or 16 or so.
    static final int ZOOM = 8;

    // WIDTH and HEIGHT control how large the drawing canvas is.
    static final int WIDTH = 60;
    static final int HEIGHT = 50;

    // WINDOW_WIDTH and WINDOW_HEIGHT are how large the entire window is,
    // including toolbar. We multiply by ZOOM because each dot drawn is actually
    // multiple pixels. To make room for the toolbar, we add 100 pixels to the
    // drawing canvas width.
    static final int WINDOW_WIDTH = WIDTH * ZOOM + 100;
    static final int WINDOW_HEIGHT = HEIGHT * ZOOM;

    // Windows, toolbar buttons, and the drawing widget.
    static Window window;
    static Button quit, small, medium, large, color, save, open, mystery;
    static Button[] rgbwcmyk;
    static CanvasWidget drawing;

    // The canvas variable refers to the large drawing canvas on the left side.
    static Canvas canvas;

    // The main function creates the Painter window, shows it on the
    // screen, waits for the user to close it, then prints a goodbye message.
    public static void main(String args[]) {
        String username = System.getenv("USER");
        StdOut.println("~~=== Welcome to Painter, " + username + "! ===~~");

        window = new Window("Painter!", WINDOW_WIDTH, WINDOW_HEIGHT);
        window.setBackgroundColor(Canvas.DARK_GRAY);

        // Add the toolbar buttons.
        quit = new Button(WINDOW_WIDTH-90, 10+0*40, 80, 30, "Quit");
        small = new Button(WINDOW_WIDTH-90, 10+1*40, 80, 30, "Small");
        medium = new Button(WINDOW_WIDTH-90, 10+2*40, 80, 30, "Medium");
        large = new Button(WINDOW_WIDTH-90, 10+3*40, 80, 30, "Large");
        color = new Button(WINDOW_WIDTH-90, 10+4*40, 80, 30, "Color");
        rgbwcmyk = new Button[8];
        rgbwcmyk[0] = new Button(WINDOW_WIDTH-90+0*20, 10+5*40, 18, 18, "R");
        rgbwcmyk[0].setBackgroundColor(Color.RED);
        rgbwcmyk[1] = new Button(WINDOW_WIDTH-90+1*20, 10+5*40, 18, 18, "G");
        rgbwcmyk[1].setBackgroundColor(Color.GREEN);
        rgbwcmyk[2] = new Button(WINDOW_WIDTH-90+2*20, 10+5*40, 18, 18, "B");
        rgbwcmyk[2].setBackgroundColor(Color.BLUE);
        rgbwcmyk[3] = new Button(WINDOW_WIDTH-90+3*20, 10+5*40, 18, 18, "W");
        rgbwcmyk[3].setBackgroundColor(Color.WHITE);
        rgbwcmyk[3].setForegroundColor(Color.BLACK);
        rgbwcmyk[4] = new Button(WINDOW_WIDTH-90+0*20, 10+5*40+20, 18, 18, "C");
        rgbwcmyk[4].setBackgroundColor(Color.CYAN);
        rgbwcmyk[4].setForegroundColor(Color.BLACK);
        rgbwcmyk[5] = new Button(WINDOW_WIDTH-90+1*20, 10+5*40+20, 18, 18, "M");
        rgbwcmyk[5].setBackgroundColor(Color.MAGENTA);
        rgbwcmyk[5].setForegroundColor(Color.BLACK);
        rgbwcmyk[6] = new Button(WINDOW_WIDTH-90+2*20, 10+5*40+20, 18, 18, "Y");
        rgbwcmyk[6].setBackgroundColor(Color.YELLOW);
        rgbwcmyk[6].setForegroundColor(Color.BLACK);
        rgbwcmyk[7] = new Button(WINDOW_WIDTH-90+3*20, 10+5*40+20, 18, 18, "K");
        rgbwcmyk[7].setBackgroundColor(Color.BLACK);
        save = new Button(WINDOW_WIDTH-90, 10+5*40+20+28, 80, 30, "Save");
        open = new Button(WINDOW_WIDTH-90, 10+6*40+20+28, 80, 30, "Open");
        mystery = new Button(WINDOW_WIDTH-90, 10+7*40+20+28, 80, 30, "Mystery");
        window.add(quit);
        window.add(color);
        window.add(small);
        window.add(medium);
        window.add(large);
        window.add(color);
        for (int i = 0; i < 8; i++)
            window.add(rgbwcmyk[i]);
        window.add(open);
        window.add(save);
        window.add(mystery);

        // Add the drawing area on the left side.
        drawing = new CanvasWidget(0, 0, WIDTH*ZOOM, HEIGHT*ZOOM, WIDTH, HEIGHT);
        window.add(drawing);
        canvas = drawing.canvas;
        updateColorButtonBackground();

        // Register a call-back to receive mouse events.
        window.addListener(new Painter());

        window.showAndAnimate(30);
        StdOut.println("All done, goodbye!");
        System.exit(0);
    }

    // This function updates the color button so it has a background that
    // matches the current pen color.
    public static void updateColorButtonBackground() {
        Color c = canvas.getPenColor();
        color.setBackgroundColor(c);
        if (c.getRed() + c.getGreen() + c.getBlue() > 350)
            color.setForegroundColor(Color.BLACK);
        else
            color.setForegroundColor(Color.WHITE);
    }

    // Made my own printSmiley function for the mystery button
    public static void printSmiley(int x, int y) {
        Color color1 = canvas.getPenColor();
        canvas.setPenColor(Color.BLACK);
        if ((x < 0) || (x >= WIDTH) || (y < 0) || (y >= HEIGHT)) 
            return;
        if (canvas.colorAt(x, y).equals(Color.BLACK))
            return;

        canvas.point(x+2, y);
        printSmiley(x+2, y-1);
        printSmiley(x+2, y-2);
        printSmiley(x+4, y);
        printSmiley(x+4, y-1);
        printSmiley(x+4, y-2);
        printSmiley(x, y-3);
        printSmiley(x+1, y-4);
        printSmiley(x+2, y-5);
        printSmiley(x+3, y-5);
        printSmiley(x+4, y-5);
        printSmiley(x+5, y-4);
        printSmiley(x+6, y-3);

    }

    // This function is called whenever the user does a mouse single-click.
    public void mouseWasClicked(double x, double y, String button) {
        if (button.equals("left") && quit.containsPoint(x, y)) {
            window.hide();
        } else if (button.equals("left") && small.containsPoint(x, y)) {
            canvas.setPenRadius(1);
        } else if (button.equals("left") && medium.containsPoint(x, y)) {
            canvas.setPenRadius(3);
        } else if (button.equals("left") && large.containsPoint(x, y)) {
            canvas.setPenRadius(6);
        } else if (button.equals("left") && save.containsPoint(x, y)) {
            canvas.saveFile();
        } else if (button.equals("left") && open.containsPoint(x, y)) {
            canvas.openFile();
        } else if (button.equals("left") && mystery.containsPoint(x, y)) {
            printSmiley(0, 0);
        } else if (button.equals("left") && color.containsPoint(x, y)) {
            drawing.showColorPicker();
            updateColorButtonBackground();
        } else if (button.equals("left") && rgbwcmyk[0].containsPoint(x, y)) {
            canvas.setPenColor(Color.RED);
            updateColorButtonBackground();
        } else if (button.equals("left") && rgbwcmyk[1].containsPoint(x, y)) {
            canvas.setPenColor(Color.GREEN);
            updateColorButtonBackground();
        } else if (button.equals("left") && rgbwcmyk[2].containsPoint(x, y)) {
            canvas.setPenColor(Color.BLUE);
            updateColorButtonBackground();
        } else if (button.equals("left") && rgbwcmyk[3].containsPoint(x, y)) {
            canvas.setPenColor(Color.WHITE);
            updateColorButtonBackground();
        } else if (button.equals("left") && rgbwcmyk[4].containsPoint(x, y)) {
            canvas.setPenColor(Color.CYAN);
            updateColorButtonBackground();
        } else if (button.equals("left") && rgbwcmyk[5].containsPoint(x, y)) {
            canvas.setPenColor(Color.MAGENTA);
            updateColorButtonBackground();
        } else if (button.equals("left") && rgbwcmyk[6].containsPoint(x, y)) {
            canvas.setPenColor(Color.YELLOW);
            updateColorButtonBackground();
        } else if (button.equals("left") && rgbwcmyk[7].containsPoint(x, y)) {
            canvas.setPenColor(Color.BLACK);
            updateColorButtonBackground();
        } else if (button.equals("left") && drawing.containsPoint(x, y)) {
            // Each drawing dot is multiple pixels, so we divide the x and y
            // values by ZOOM to figure out which drawing coordinate was
            // clicked.
            int xx = (int)(x/ZOOM);
            int yy = (int)(y/ZOOM);
            respondToLeftClick(xx, yy);
        } else if (button.equals("right") && drawing.containsPoint(x, y)) {
            // Each drawing dot is multiple pixels, so we divide the x and y
            // values by ZOOM to figure out which drawing coordinate was
            // clicked. We also set the pen radius to 1 for this operation,
            // temporarily.
            int xx = (int)(x/ZOOM);
            int yy = (int)(y/ZOOM);
            double r = canvas.getPenRadius();
            canvas.setPenRadius(1);
            respondToRightClick(xx, yy);
            canvas.setPenRadius(r);
        }
    }

    // This function is called when the user starts pressing a mouse button.
    public void mouseWasPressed(double x, double y, String button) {
        if (drawing.containsPoint(x, y))
            mouseWasClicked(x, y, button);
    }

    // This function is called repeatedly while the user drags the mouse while
    // holding a button.
    public void mouseWasDragged(double x, double y) {
        if (drawing.containsPoint(x, y))
            mouseWasClicked(x, y, "left");
    }

    // This function is called whenever the user left-clicks within the drawing canvas.
    public static void respondToLeftClick(int x, int y) {
        // The user left-clicked the mouse at coordinates (x, y),
        // so paint that pixel using the current pen color.
        // But only do this if the pixel is not already painted that color.
        if (!canvas.colorAt(x, y).equals(canvas.getPenColor())) {
            canvas.point(x, y);
        }
    }

    // This function is called whenever the user right-clicks within the drawing canvas.
    public static void respondToRightClick(int x, int y) {
        // The user right-clicked the mouse at coordinates (x, y),
        // so fill that entire area using the current pen color.
        // But only do this if the pixel is not already painted that color.
        // Use a separate helper-function to do the actuall recursive fill.
        if (!canvas.colorAt(x, y).equals(canvas.getPenColor())) {
            Color color1 = canvas.colorAt(x, y);
            Color color2 = canvas.getPenColor();
            bucketFill(color1, color2, x, y);
        }
    }

    public static void bucketFill(Color color1, Color color2, int x, int y) {
        // error checking and base cases
        if ((x < 0) || (x >= WIDTH) || (y < 0) || (y >= HEIGHT))    // if out of bounds         
            return;                                                 // return
        if (!canvas.colorAt(x, y).equals(color1))                   // if color matches
            return;                                                 // return
        
        // recursive case
        if (canvas.colorAt(x, y).equals(color1)) {                  // if the color doesnt match
            canvas.setPenColor(color2);                             // new pen color
            canvas.point(x, y);                                     // draw
            canvas.pause(50);                                       // pause for 50 miliseconds

            bucketFill(color1, color2, x+1, y);                     // draw right pixel
            bucketFill(color1, color2, x, y+1);                     // up 
            bucketFill(color1, color2, x-1, y);                     // left
            bucketFill(color1, color2, x, y-1);                     // down
        }   
    } // end of bucketFill

} // end of class
