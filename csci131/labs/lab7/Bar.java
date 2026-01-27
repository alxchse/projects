// Alexandra Chase
// CSCI 131
// 30 October 2022
// Lab 7

public class Bar {
    public static void repeatedlyPrintX(int n){
        String X = "X";

        for (int count = 0; count < n; count++) 
            StdOut.print(X);
        StdOut.println();
    } // end repeatedlyPrintX

    public static void main (String[] args) {
        int n;
        repeatedlyPrintX(10);
        repeatedlyPrintX(5);
        repeatedlyPrintX(7);
    } // end of main

} // end of class