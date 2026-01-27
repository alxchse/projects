// A program to calculate the period of a pendulum of a given length. That is,
// how long it takes, in seconds, for a weight on a rope (or a child on a
// swingset) to swing back and forth. The user specifies the length of the rope
// as a command-line argument. For example:
//   java Pendulum 2.5
// will calculate and print:
//   A pendulum with a 2.5 meter rope has a period of about 3.1734878129702615 seconds.
//
// Side note for the curious: Intuitively, one might think the weight of the
// "bob" at the end of the rope would make a difference in the period. Don't
// heavy pendulums swing slower?! But physicists tell us that for simple
// pendulums, and ignoring friction and air resistance, the weight is
// irrelevant. Only the length of the rope matters.

public class Pendulum {
    public static void main(String[] args) {

        double g = 9.81; // Acceleration due to gravity is 9.81 meters / second on earth.

        // TODO: Add code here to create and assign a variable L, for the user
        // input.
        double L;
        L = Double.parseDouble(args [0]);

        // TODO: Add code here to calculate
        double ans = (2 * Math.PI) * Math.sqrt(L / g);

        // TODO: Add suitable print statements here. Try to match
        // the example output in the comments above.
        System.out.println("A pendulum with a " + L + " meter rope has a period of about " 
        + ans + " seconds.");

    }
}
