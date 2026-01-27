// Alexandra Chase
// September 27 2022
// This program generates a random pin with the number of digits set by the user. 
// Same as Pin.java, though no two numbers next to each other will be the same. 

public class PinVariation {
    public static void main (String[] args) {

int N; // number of desired digits in pin
int y; // variable for last digit
int per = 11; 

StdOut.println("How many digits do you want in your pin?");
N = StdIn.readInt ();

StdOut.print ("Your random pin is: ");

    for (int count = 0; count < N; count++) {
    y = StdRandom.uniform (0, 10);
        while (per == y)
        y = StdRandom.uniform (0,10);
        
    StdOut.print (y + " ");
    per = y;
    }
StdOut.println();
}
}
