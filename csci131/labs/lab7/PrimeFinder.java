// Alexandra Chase
// CSCI 131-03
// October 26 2022
// Lab 7

public class PrimeFinder {
    public static void main (String [] args) {
        int n = Integer.parseInt(args[0]);

    } // end of main

    public static int findPrime(int n) {

        while (!Prime.isPrime(n)) {
        if (Prime.isPrime(n)) {
            int prime = (Prime.isPrime(n));
        else n++;
        }
    return prime;
    } // end of findPrime
} // end of class