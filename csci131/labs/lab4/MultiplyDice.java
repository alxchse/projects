/*----------------------------------------------------------------
 * Alexandra Chase
 * September 27 2022
 * 
 *
 *  Example: java MultiplyDice
 *----------------------------------------------------------------*/

public class MultiplyDice {

    public static void main(String[] args) { 

        long score = 1;

            for (int count = 0; count < 20; count++) {
            int roll = StdRandom.uniform(1, 7);
            score = (roll * score);
            StdOut.println("You rolled " + roll + ", your score is now " + score + ".");
            }
        
        StdOut.println("After 20 rolls, your score is " + score + ".");

        
            while (score > 9) {
            score = score / 10;
            }

        long leadingDigit = score;

        System.out.println("The leading digit is " + leadingDigit + ".");

    } // end of main

} // end of class MultiplyDice
