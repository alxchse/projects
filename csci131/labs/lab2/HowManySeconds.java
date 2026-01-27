// A program to calculate how many million seconds there are in a given number
// of years. For example, running:
//   java HowManySeconds 2
// will print:
//   In 2 years, there are about 63.1152 million seconds

public class HowManySeconds {
    public static void main (String[] args) {

        // YOUR TASK: Add more code here, and fix any mistakes you see.
int yrs = Integer.parseInt(args [0]);
double seconds = yrs * 365.25 * 24 * 60 * 60 / 1000000;

        System.out.print("In " + yrs + " years, there");
        System.out.println(" are about " + seconds + " million seconds.");
    }
}

