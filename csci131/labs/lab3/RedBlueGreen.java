/*----------------------------------------------------------------
 *  Author:   Alexandra Chase
 *  Email:    amchas26g.holycross.edu
 *  Written:  09/14/2022
 *  
 *  User picks a color and the program simulates rolling two dice.
 *
 *  Example: java RedBlueGreen blue
 *  Output: You picked blue and rolled a pair of 3s.
 *----------------------------------------------------------------*/

public class RedBlueGreen {
    public static void main(String[] args) { 
        // Error check: ensure one command-line argument was provided.
        if (args.length != 1) {
            System.out.println("Please provide one command line argument.");
            System.out.println("For example: java RedBlueGreen blue");
            System.exit(1);
        }

        String pick = args[0];                          // the user's guess
        if (!pick.equalsIgnoreCase("green")){           // if the input doesn't match one of
            if(!pick.equalsIgnoreCase("blue")){         // these colors, then an error message
                if(!pick.equalsIgnoreCase("red")){      // will print
            
            System.out.println("Your guess must be either red, blue, or green.");
            System.exit(1);
                 }
            }
        }

        // Pick two random integers each between 1 and 6, inclusive.
        int a = (int)(1 + Math.random() * 6); // first dice
        int b = (int)(1 + Math.random() * 6); // second dice
        
        // Sum of the two dice.
        int sum = a + b; 

        // Variable to hold the result of the game
        String result = "";

        // calculates result
        if (sum == 8)
            result = "green";
        else if (sum%2 == 0)
            result = "blue";
        else 
            result = "red";

        // establish the values of the prizes.
        int prize = 0;

        if(result.equals(pick) && pick.equalsIgnoreCase("red"))
            prize = 1;
        if(result.equals(pick) && pick.equalsIgnoreCase("blue"))
            prize = 1;
        if(result.equals(pick) && pick.equalsIgnoreCase("green"))
            prize = 4;

        // Print the results.
        if (a == b) {
            System.out.print("You picked " + pick);
            System.out.println(" and rolled a pair of " + a + "s.");
        } else {
            System.out.print("You picked " + pick);
            System.out.println(" and rolled a " + a + " and a " + b + ".");
        }

        System.out.println("The sum is " + sum);
        System.out.println("The result is " + result);

        if (result.equals(pick)) {
            System.out.println("You win!");

            // TODO: calculate prize
            
            System.out.println("Your prize is $" + prize + ".");
        } else {
            System.out.println("Sorry, you lost!");
        }
 
    } //end of main
} //end of RedBlueGreen
