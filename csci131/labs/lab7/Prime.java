// Alexandra Chase
// CSCi 131-03
// Lab 7
// October 26 2022
// Prime.java will return true/false based on the number
// given by the user.

public class Prime {
    public static void main (String [] args) {
        int n = Integer.parseInt(args[0]);
        if (isPrime(n)) StdOut.println(n + " is prime.");
        else StdOut.println(n + " is not prime.");
    } // end of main

    public static boolean isPrime(int n) {
        boolean value = true;
        for (int count = 2; count < n; count++) {
            if (n%count == 0)
            value = false; 
            }
         
    return value;
    } // end of factors

} // end of class