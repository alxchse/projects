// Alexandra Chase
// September 27 2022
// This program generates a random pin with the number of digits set by the user. 

public class Pin {
    public static void main (String[] args) {

int N; // number of desired digits in pin

StdOut.println("How many digits do you want in your pin?");

N = StdIn.readInt ();

StdOut.print ("Your random pin is: ");

    for (int count = 0; count < N; count++) {
        StdOut.print (StdRandom.uniform (0, 10));
        StdOut.print (" ");
    }
    }
}
