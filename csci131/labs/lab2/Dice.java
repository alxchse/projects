// This program simulates rolling a dice by
// printing a randomnumber, but the user gets to specify the
// number of sides as a command-line argument.
//
// Alexandra Chase
// Lab 2

public class Dice {
    public static void main(String[] args) {

        int n;
        n = Integer.parseInt(args [0]);
        long x = Math.round(0.5 + Math.random() * n);
        
        System.out.println("Using a " + n + " sided dice, you rolled a " + x + ".");
    }

}