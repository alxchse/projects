// Alexandra Chase
// CSCI 131-03
// Lab 7
// October 26 2022
// Factors.java will search a file for a specific word given 
// by the user. 

public class Factors {
    public static void main (String [] args) {
        int n = Integer.parseInt(args[0]);
        int f = factors(n);
        System.out.printf("There are %d numbers that evenly divide %d\n", f, n);
    } // end of main

    public static int factors(int n) {
    int numFactors = 0;
        for (int count = 2; count < n; count++) {
            if (n % count == 0) {
                StdOut.println(count);
                numFactors++;
            }
        } 
    return numFactors;
    } // end of factors

} // end of class
        

    