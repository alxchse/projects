// A program to generate random (simple) math facts. It
// chooses two integers at random and prints some arithmetic
// facts using those numbers.
// For example, running:
//   java MathFacts
// will print output like:
//   11 + 6 = 17
//   11 - 6 = 5
//   11 * 6 = 66
//   11 / 6 = 1.8333333333333333
//   average of 11 and 6 = 8.5
//   geometric mean of 11 and 6 = 8.12403840463596

public class MathFacts {
    public static void main(String[] args) {

        long x = Math.round(0.5 + Math.random() * 20);
        long y = Math.round(0.5 + Math.random() * 20);

// YOUR TASK: Add more code here to calculate product, quotient, average, etc.
        int sum = (int)x + (int)y;
        int difference = (int)x - (int)y;
        int product = (int)x * (int)y;
        double quotient = (double)x / (double)y;
        double average = ((double)x + (double)y) / 2.0;
        double geometricMean = Math.sqrt((double)x * (double)y);

// YOUR TASK: Add more printing here to show other results.
        System.out.println(x + " + " + y + " = " + sum);
        System.out.println(x + " - " + y + " = " + difference);
        System.out.println(x + " * " + y + " = " + product);
        System.out.println(x + " / " + y + " = " + quotient);
        System.out.println("average of " + x + " and " + y + " = " + average);
        System.out.println("geometric mean of " + x + " and " + y + " = " + geometricMean);
    }
}
