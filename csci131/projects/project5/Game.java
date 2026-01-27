/*----------------------------------------------------------------
 *  Author:   K. Walsh
 *  Email:    kwalsh@holycross.edu
 *  Written:  7/13/2015
 *  
 *  Minesweeper game. This class implements the game window and most
 *  of the game logic.
 *----------------------------------------------------------------*/

import GUI.*;

/**
 * A <i>Game</i> object manages all information about a minesweeper game as it
 * is being played and displayed on the screen. This includes information about
 * all of the cells (this is stored in a 2-D array of Cell objects), how many
 * flags have been planted, how many mines have been deployed, etc. Game extends
 * Window so it can be drawn on the screen. It also extends EventListener, so it
 * can respond to user interaction.
 */
public class Game extends Window implements EventListener {

    /**
     * Number of cells tall the game board will be.
     */
    public static final int NUM_ROWS = 20;

    /**
     * Number of cells wide the game board will be.
     */
    public static final int NUM_COLS = 30;

    // Example game screen layout:
    // +---------------------------------------------------------+
    // |      M A R G I N = 50                                   |
    // | M  + - - - - - - - - - - - - - - - - - - - - - - - + M  |
    // | A  |                                               | A  |
    // | R  |                                               | R  |
    // | G  |                Grid of Cells                  | G  |
    // | I  |                                               | I  |
    // | N  |                                               | N  |
    // | =  |       600 = NUM_COLS * Cell.SIZE wide         | =  |
    // | 50 |                      by                       | 50 |
    // |    |       400 = NUM_ROWS * Cell.SIZE tall         |    |
    // |    |                                               |    |
    // |    |                                               |    |
    // |    |                                               |    |
    // |    + - - - - - - - - - - - - - - - - - - - - - - - +    |
    // |            SPACE     S   SPACE   S    SPACE             |
    // |    + - - - - - - - + P + - - - + P + - - - - - - - +    |
    // |    |    Status     | A | Timer | A |     Help      |    |
    // |    |       Box     | C |       | C |      Box      |    |
    // |    + - - - - - - - + E + - - - + E + - - - - - - - +    |
    // |     M A R G I N = 50                                    |
    // +-- ------------------------------------------------------+

    /**
     * Width of the game window, in pixels.
     * Equal to 2*MARGIN + GRID_WIDTH
     * or 2*MARGIN + 2*SPACE + StatusBox.WIDTH, Timer.WIDTH, HelpBox.WIDTH,
     * whichever is larger.
     */
    public static final int WIDTH = 700;

    /**
     * Height of the game window, in pixels.
     * Equal to 2*MARGIN + SPACE
     *     + GRID_HEIGHT
     *     + max(StatusBox.Height, Timer.HEIGHT, HelpBox.HEIGHT)
     */
    public static final int HEIGHT = 600; 

    /**
     * Width of the grid part of the window, in pixels.
     * Equal to NUM_COLS * Cell.SIZE.
     */
    public static final int GRID_WIDTH = NUM_COLS * Cell.SIZE;

    /**
     * Height of the grid part of the window, in pixels.
     * Equal to NUM_ROWS * Cell.SIZE.
     */
    public static final int GRID_HEIGHT = NUM_ROWS * Cell.SIZE;

    /**
     * Margin around the edges of the canvas.
     */
    private static final int MARGIN = 50;

    /**
     * Space between elements on the canvas.
     */
    private static final int SPACE = 25;

    // A 2-D array of Cell objects to keep track of the board state.
    private Cell[][] cells = new Cell[NUM_ROWS][NUM_COLS];

    private int numMines = 0;    // number of mines deployed
    private int numRevealed = 0; // number of cells revealed so far

    // Whether or not the game has been won.
    private boolean gameWon = false;

    // Whether or not the game has been lost
    private boolean gameLost = false;

    // Name of the user playing the game.
    private String username;

    // The difficulty level of the game, used for tracking top scores.
    private String difficulty;

    // The status box that appears in the top left.
    private StatusBox status;

    // The timer that appears in the top middle.
    private Timer timer;

    // The help box that appears in the top right.
    private HelpBox help;

    /**
     * Constructor: Initializes a new game, but does not deploy any mines, plant
     * any flags, etc. The difficulty is either "easy", "medium", or "hard", and
     * will be used to load the proper top scores file. Name is used as the
     * user's name.
     */
    public Game(String name, String difficulty) {
        super("Minesweeper!", WIDTH, HEIGHT);

        this.username = name;
        this.difficulty = difficulty;

        // Create the background
        setBackgroundColor(Canvas.DARK_GRAY);

        // Create a border around the grid
        Box border = new Box(MARGIN-1.5, MARGIN-1.5, GRID_WIDTH+3, GRID_HEIGHT+3);
        border.setBackgroundColor(null);
        border.setBorderColor(Canvas.BLACK);
        add(border);

        // Create the info boxes
        help = new HelpBox(
                WIDTH - MARGIN - HelpBox.WIDTH,
                HEIGHT - MARGIN - HelpBox.HEIGHT);
        add(help);

        timer = new Timer(
            MARGIN + MARGIN/2 + StatusBox.WIDTH,
            HEIGHT - MARGIN - Timer.HEIGHT);
        add(timer);

        status = new StatusBox(
            this,
            MARGIN,
            HEIGHT - MARGIN - StatusBox.HEIGHT);
        add(status);
        
        // TODO: Create and add the other info boxes, besides help. Also,
        // initialize and add all of the cells to form the game grid. As an
        // example, I will add a label and a few mines, just to show how to add
        // these kinds of widgets to the window. You will want to eventually
        // replace these next few lines with real code.
        // Here is a giant red label, centered exactly in the middle of where
        // the game grid was meant to go...

        int row, col;                                                                       
        for (col = 0; col < NUM_COLS; col++) {                                                // for cols 0-29
            for (row = 0; row < NUM_ROWS; row++) {                                            // for rows 0-19
                cells[row][col] = new Cell(MARGIN+Cell.SIZE*col, MARGIN+Cell.SIZE*row);       // create cell in each 
                add(cells[row][col]);
            }
        }

    } // END GAME

    /**
     * Get the number of mines that are deployed.
     */
    public int getNumMinesDeployed() {
        return numMines;
    }

    /**
     * Get the number of hidden cells remaining to be revealed.
     */
    public int getNumCellsRemaining() {
        return NUM_ROWS * NUM_COLS - numRevealed;
    }

    /**
     * Deploy the given number of mines. This gets called once during game
     * setup. The game doesn't actually begin officially until the user clicks
     * a cell, so the timer should not start yet.
     */
    public void deployMines(int mines) {                                            
 
        for (numMines = 0; numMines < mines; numMines++){                      // loop until we reach desired number of mines

            int x = StdRandom.uniform(0, NUM_ROWS);                                 // get random x
            int y = StdRandom.uniform(0, NUM_COLS);                                 // get random y

            while (cells[x][y].isMine() == true) {                                      // if already a mine then break
                x = StdRandom.uniform(0, NUM_ROWS);                                 // get random x
                y = StdRandom.uniform(0, NUM_COLS);
            }

            cells[x][y].makeMine();                                                 // make cell a mine

                if (!(x == 0))
                    cells[x-1][y].incrementNeighborMineCount();
                if (!(x == 0) && !(y == 29))
                    cells[x-1][y+1].incrementNeighborMineCount(); 
                if (!(x == 0) && !(y == 0))
                    cells[x-1][y-1].incrementNeighborMineCount();
                if (!(y == 0))
                    cells[x][y-1].incrementNeighborMineCount();     
                if (!(y == 0) && !(x == 19))
                    cells[x+1][y-1].incrementNeighborMineCount();
                if (!(x == 19))
                    cells[x+1][y].incrementNeighborMineCount();
                if (!(y == 29))
                    cells[x][y+1].incrementNeighborMineCount();
                if (!(x == 19) && !(y == 29))
                    cells[x+1][y+1].incrementNeighborMineCount();

            
        }
    } // END DEPLOYMINES

    public void showAllMines() {

        for (int row = 0; row < NUM_ROWS; row++){
            for (int col = 0; col < NUM_COLS; col++) {                                 // loop through all cells
                if (cells[row][col].isMine == true) {                                  // if cell is a mine
                    cells[row][col].reveal();                                          // reveal it
                }
            }
        }
    } // END SHOWMINES

    public void autoRevealCells(int row, int col) {

        if ((row < 0) || (row > NUM_ROWS-1) || (col < 0) || (col > NUM_COLS-1)){            // guards against going off grid
            return;
        } else if (cells[row][col].isRevealed()) {
            return;
        }
        cells[row][col].reveal();
        numRevealed++;
           
         if (cells[row][col].getNeighborMineCount() == 0) {
            autoRevealCells(row+1, col-1);                                            
            autoRevealCells(row+1, col);
            autoRevealCells(row+1, col+1);
            autoRevealCells(row, col-1);
            autoRevealCells(row, col+1);
            autoRevealCells(row-1, col-1);
            autoRevealCells(row-1, col);
            autoRevealCells(row-1, col+1);
        }

    } // END AUTOREVEALCELLS
        
    /**
     * Respond to a mouse click. This function will be called each time the user
     * clicks on the game window. The x, y parameters indicate the screen
     * coordinates where the user has clicked, and the button parameter
     * indicates which mouse button was clicked (either "left", "middle", or
     * "right"). The function should update the game state according to what the
     * user has clicked.
     * @param x the x coordinate where the user clicked, in pixels.
     * @param y the y coordinate where the user clicked, in pixels.
     * @param button either "left", "middle", or "right".
     */
    public void mouseClicked(double x, double y, String button) {
        // User clicked the mouse, see what they want to do.

        // If game is over, then ignore the mouse click.
        if (gameWon || gameLost) {
            return;
        }
        // If the user middle-clicked, ignore it.
        if (!button.equals("left") && !button.equals("right"))
            return;

        // If the user clicked outside of the game grid, ignore it.
        if (x < MARGIN || y < MARGIN
                || x >= MARGIN + GRID_WIDTH || y >= MARGIN + GRID_HEIGHT) {
            return;
                }

        // Calculate which cell the user clicked.
        int row = (int)((y - MARGIN) / Cell.SIZE);
        int col = (int)((x - MARGIN) / Cell.SIZE);

        StdOut.printf("You clicked row %d column %d with button %s\n", row, col, button);
        timer.startCounting();
        
        if (!cells[row][col].isRevealed() && !cells[row][col].isMine()){
            autoRevealCells(row,col);
            if (numMines == getNumCellsRemaining()){
                gameWon = true;
                timer.stopCounting();
                Label gameWon = new Label(
                    MARGIN + NUM_COLS * Cell.SIZE /2,
                    MARGIN + NUM_ROWS * Cell.SIZE /2,
                    "Congratulations! You won!");
                gameWon.setFont("SansSerif Bold", 24);
                gameWon.setForegroundColor(Canvas.PINK);
                gameWon.setBackgroundColor(Canvas.BLACK);
                gameWon.setBorderColor(Canvas.WHITE);
                add(gameWon);
        }
        } else if (!cells[row][col].isRevealed() && cells[row][col].isMine()) {
            showAllMines();
            cells[row][col].reveal();
            gameLost = true;
            timer.stopCounting();
        Label gameLost = new Label(
            MARGIN + NUM_COLS * Cell.SIZE /2,
            MARGIN + NUM_ROWS * Cell.SIZE /2,
            "Wow! That was sad...");
        gameLost.setFont("SansSerif Bold", 24);
        gameLost.setForegroundColor(Canvas.PINK);
        gameLost.setBackgroundColor(Canvas.BLACK);
        gameLost.setBorderColor(Canvas.WHITE);
        add(gameLost);
        } else if (cells[row][col].isRevealed()) {
            StdOut.println("This cell has already been revealed!");
        }

    } // END OF MOUSECLICKED
       

    /**
     * Respond to key presses. This function will be called each time the user
     * presses a key. The parameter indicates the character the user pressed.
     * The function should update the game state according to what character the
     * user has pressed. 
     * @param c the character that was typed.
     */
    public void keyTyped(char c)
    {
        // User pressed a key, see what they want to do.
        switch (c) {
            case 'q': 
            case 'Q': 
                hide(); // user wants to quit
                break;
            default:
                break; // anything else is ignored
        }
    }

    /**
     * Paint the background for this window on the canvas. Don't call this
     * directly, it is called by the GUI system automatically. This function
     * should draw something on the canvas, if you like. Or the background can
     * be blank.
     * @param canvas the canvas on which to draw.
     */
    public void repaintWindowBackground(GUI.Canvas canvas) {

    }
} // END
