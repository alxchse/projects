/*----------------------------------------------------------------
 *  TODO: FILL THIS IN
 *
 *  Checks whether the MultiplyDice game follows Benford's law.
 *
 *  Usage: java Benford count
 *  Example: java Benford 1000
 *----------------------------------------------------------------*/

public class Benford {

    public static void main(String[] args) { 

        // TODO: Use first command-line argument for n, the repetition count.
        // TODO: Use second command-line argument for k, the target value.

        // TODO: Declare and initialize a variable to count the number of times
        // that k appeared as the leading digit.

        // TODO: Play the game n times. After each game, check if a k appeared
        // as the leading digit and, if so, then count it.

        // Print a summary.
        System.out.println("Out of " + n + " games, a " + k + " appears as the leading digit");
        System.out.println("of the score " + count + " times, or "+(count*100.0/n)+"% of the time.");

    } // end of main

} // end of Benford
