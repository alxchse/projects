// A program to demonstrate random numbers and rounding.
// For example, running:
//   java Rounding
// will print something like:

public class Rounding {
    public static void main(String[] args) {

        double a = Math.random();
        long b = Math.round(a);

        System.out.println("Random number: " + a);
        System.out.println("Rounded, that is: " + b);
    }
}
