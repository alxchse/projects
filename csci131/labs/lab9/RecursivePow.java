// A demonstration of a singly-recursive function.

public class RecursivePow {

    public static void main(String[] args) {
        int x = Integer.parseInt(args[0]);;
        int y = Integer.parseInt(args[1]);;

        StdOut.printf("within main: pow(%d, %d) is about to be called...\n", x, y);
        int z = pow(x, y);
        StdOut.printf("within main: pow(%d, %d) returned %d as the final answer.\n", x, y, z);
    }

    // A recursive function to calculate a-to-the-power-b.
    public static int pow(int a, int b) {
        if (b == 0) {
            return 1;
        } else {
            int r = pow(a, b-1);
            return a * r;
        }
    }

}
