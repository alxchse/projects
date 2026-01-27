//**************************************************************************
// ArrayStats.java
//     Author: Alexandra Chase
//     Date: 09/28/2022
//     Class: CSCI 131
//     Purpose: Compute statistics for a list of grades.
//**************************************************************************

public class ArrayStats {

    static final int MAX_NUM_GRADES = 100;

    public static void main(String[ ] args) {
        if (args.length != 1) {
            StdOut.println("Ooops, this program was expecting one command-line argument!");
            StdOut.println("Try running it like this:");
            StdOut.println("  java ArrayStats 10");
            System.exit(1);
        }

        int[ ] grades = new int[MAX_NUM_GRADES];   //Array with space for up to 100 grades.

        int numGrades = Integer.parseInt(args[0]); //The number of grades to be entered by user
        
        // check user input for reasonableness
        if (numGrades < 1 || numGrades > 100) {
            StdOut.println("Please enter a valid number of grades.");
            System.exit(0);
        }

        for (int i = 0; i < numGrades; i++) {      //Generate some grades for practice
            grades[i] = (int)(100*Math.random( ));
        }

        for (int i = 0; i < numGrades; i++) {     //Print out the grades
            System.out.print(grades[i] + " ");
        }
        System.out.println( );

        System.out.println("First grade is " + grades[0]);     //Print out the first grade
        
        System.out.println( );                   //Start new line

        int last = numGrades - 1;
        System.out.println("Last grade is " + grades[last]);       //Print out the last grade
        
        System.out.println( );                   //Start new line

        //Find the average of items in the array
        int sum = 0;
        for (int i = 0; i < numGrades; i++) {
            sum += grades[i];
        }
        double average = (double)sum/(double)numGrades;
        System.out.println("The average grade is: " + average);

        //Find the maximum value in the array
        int max = grades[0];  //maximum element seen so far
        for (int i = 1; i < numGrades; i++) {
            if (grades[i] > max) {
                max = grades[i];
            } //current max is the largest seen so far
        }
        System.out.println("The maximum grade is: " + max);
        
        // compute and print the minimum grade
        int min = grades[0]; // minimum element seen so far
        for (int ii = 1; ii < numGrades; ii++) {
            if (grades [ii] < min) {
                min = grades[ii];
            } // current min is the smallest seen so far
        }
        StdOut.println("The minimum grade is: " + min);
    } // end of main
} // end of ArrayStats class
