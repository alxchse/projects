/*----------------------------------------------------------------
 *  Author:   K. Walsh
 *  Email:    kwalsh@holycross.edu
 *  Written:  7/13/2015
 *  
 *  Each Cell object manages information about one "cell" and draws a
 *  single "cell" of the game grid. 
 *----------------------------------------------------------------*/

import GUI.*;
import java.awt.Color;

/**
 * A <i>Cell</i> object holds all information about the state of a single cell
 * of the minesweeper game board. This includes:
 *   - whether a mine is hidden in this cell or not
 *   - how many of its neighboring cells contain mines
 *   - whether it has been revealed yet or is still hidden
 * Each Cell object knows how to draw itself in a graphical window, and it will
 * draw itself in different styles, depending on all the above state information.
 */
public class Cell extends Widget {

    /**
     * Size of one cell when it is drawn on the screen, in pixels.
     */
    public static final int SIZE = 20;

    /* IMPORTANT NOTE:
     * Each Cell object inherits several member variables, including:
     *    double x;
     *    double y;
     *    double width;
     *    double height;
     * Code below can use these as regular member variables as usual, e.g. 
     *      this.x
     * or
     *      this.width
     */

    /**
     * Whether a mine is hidden in this cell or not.
     */
    protected boolean isMine;

    /**
     * Whether this cell is "revealed" or not.
     */
    protected boolean isRevealed;

    /**
     * Count of how many neighboring cells have mines.
     */
    protected int neighborMineCount;

    /**
     * Constructor: Initialize a cell to be drawn at the given x, y coordinates
     * on the screen. The cell will be blank. That is, it will not be a mine,
     * and it will have no neighboring mines so a neighbor mine count of zero.
     */
    public Cell(int x, int y) {
        super(x, y, SIZE, SIZE);
        this.isMine = false;
        this.isRevealed = false;
        this.neighborMineCount = 0;
    }

    /**
     * Hide a mine in this cell by changing the isMine variable to true.
     */
    public void plantMine() {
        isMine = true;
    }

    /**
     * Returns true if a mine is hidden in this cell, otherwise returns false.
     */
    public boolean isMine() {
        return isMine;
    }

    /**
     * Increment the neighbor mine count variable by one. 
     */
    public void incrementNeighborMineCount() {
        neighborMineCount++;
    }

    /**
     * Set the neighbor mine count variable to a given value.
     */
    public void setNeighborMineCount(int count) {
        neighborMineCount = count;
    }

    /**
     * Returns the value of the neighbor mine count variable.
     */
    public int getNeighborMineCount() {
        return neighborMineCount;
    }

    /**
     * Change this cell so that it is "revealed" by setting isRevealed to true.
     */
    public void reveal() {
        isRevealed = true;
    }

    /**
     * Returns true if this cell is "revealed", otherwise returns false.
     */
    public boolean isRevealed() {
        return isRevealed;
    }

    /**
     * Hide a mine in this cell by changing the isMine variable to true.
     */
    public void makeMine() {
        isMine = true;
    }

    /**
     * Change this cell so that it shows the mine that is hiding in it.
     */
    public void showMine() {
        if (isMine)
            isRevealed = true;
    }

    /**
     * Check whether there are neighboring mines.
     */
    public boolean coastIsClear() {
        return (neighborMineCount == 0);
    }

    /**
     * Paint this cell on the canvas. Don't call this directly, it is called by
     * the GUI system automatically. This function should draw something on the
     * canvas. Usually the drawing should stay within the bounds (x, y, width,
     * height) which are protected member variables of GUI.Widget, which this
     * class extends.
     * @param canvas the canvas on which to draw.
     */
    public void repaint(GUI.Canvas canvas) {
        canvas.setPenColor(Color.BLACK);
        canvas.rectangle(this.x, this.y, this.width, this.height);
        canvas.setPenColor(Color.PINK);
        canvas.filledRectangle(this.x, this.y, (this.width-0.5), (this.height-0.5));

        if (isRevealed == true) {
            canvas.setPenColor(Color.LIGHT_GRAY);
            canvas.filledRectangle(this.x, this.y, this.width, this.height);
            canvas.setPenColor(Color.BLACK);
            canvas.setFont(8);
                if (neighborMineCount == 1)
                canvas.text(this.x+10, this.y+10, "1");
                if (neighborMineCount == 2)
                canvas.text(this.x+10, this.y+10, "2");
                if (neighborMineCount == 3)
                canvas.text(this.x+10, this.y+10, "3");
                if (neighborMineCount == 4)
                canvas.text(this.x+10, this.y+10, "4");

        }

        if ((isMine == true) && (isRevealed == true)) {
            canvas.setPenColor(Color.YELLOW);
            canvas.filledRectangle(this.x, this.y, this.width, this.height);
            canvas.pictureCentered(this.x+10, this.y+10, "bomb.png", this.width, this.height);
        }



    } // END REPAINT
        
} // END OF CELL CLASS


