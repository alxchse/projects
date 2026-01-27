//**************************************************************************
// Trends.java
// Author:
// Date:
// Class: CSCI 131
// Purpose: Compute a few basic statistics for a list of integers, using a
// completely-full array to hold the values. Data is taken from a file of
// climate data.
//**************************************************************************

public class Trends {

    public static void main(String[] args) {

        // Load data from a file containing historical climate data for
        // Worcester, MA. The data consists of a single number, the montly
        // average temperature, for each month starting in January 1900.
        StdOut.println("Loading data from worcester-temperature.txt ...");
        In infile = new In("worcester-temperature.txt");
        double[] data = infile.readAllDoubles();

        StdOut.print("Do you want to see all the data? [y or n] ");
        if (StdIn.readString().equalsIgnoreCase("y")) {
            // Print all temperature data, with spaces, and a newline between every 12 numbers.
            StdOut.println("There are " + data.length + " values in the array.");
            for (int i = 0; i < data.length; i++) {
                if (i % 12 == 0)
                    StdOut.println();
                StdOut.print(data[i] + " ");
            }
            StdOut.println( );
        }

        StdOut.println("The earliest year of data is from 1900.");
        int numYears = data.length/12;  //Calculate the number of years;
        int endYear = 1900 + numYears - 1; // Calculate the ending year.
        StdOut.println("The most recent year of data is from " + endYear + ".");
        StdOut.println("There are " + numYears + " years worth of data in all.");

        // Print out average of all the data.
        double sumAll = 0; // variable for the sum of all temps
            for (int count1 = 0; count1 < data.length; count1++) {
                sumAll += data[count1];
        }
        double avgAll = sumAll/(double)data.length;
        System.out.println("Average temperature overall: " + avgAll);
        StdOut.println( );                // blank line

        // Print out the average for just the first 120 months (1900 to 1909)
        double sumFirstDec = 0; // variable for first decade temp sum
            for (int count2 = 0; count2 < 120; count2++) { // only for first 120 values
                sumFirstDec += data[count2];
        }
        double avgFirstDec = sumFirstDec/120.0;
        System.out.println("Average temperature for 1900-1909: " + avgFirstDec);
        StdOut.println( );                // Leave one blank line

        // Print out the average for just the last 120 months (2010 to 2020)
        double sumLastDec = 0; // variable for first decade temp sum
            for (int count3 = data.length - 1; count3 > (data.length - 121); count3--) { // only for last 120 values
                sumLastDec += data[count3];
        }
        double avgLastDec = sumLastDec/120.0;
        StdOut.println("Average temperature for last decade: " + avgLastDec);
        StdOut.println( );                // Leave one blank line

        // Declare and allocate an array of doubles to hold yearly averages.
        double[] yearlyAvg = new double[numYears];

        // Each value in the yearlyAvg array will represent the average over an
        // entire year worth of data. There will be one value for 1900, one
        // value for 1901, one value for 1902, etc., up to and including
        // endYear. For each year, calculate the average for the 12 months of
        // that year, and store this result in the appropriate place in the
        // yearlyAvg array.
		int year = 0;
		for (int i = 0; i < data.length; i +=12) {
			double sum = 0;
			for (int j = 0; j < 12; j++) {
				sum = sum + data[i + j];
			}
			yearlyAvg[year] = sum/12.0;
			year++;
		}
				
        // Print all of the yearly averages.
        for (int yr = 1900; yr <= endYear; yr++) {
            StdOut.print("Average yearly temperature for " + yr + ": ");
            StdOut.println(yearlyAvg[yr-1900]);
        }

        // Examine each year from 1900 to endYear, inclusive. If that year was
        // particularly hot (more than 2 degrees above the overall average) or
        // particularly cold (more than 2 deegrees below the overall average),
        // then print a message saying so.

        for (int i = 0; i < yearlyAvg.length; i++) {
            if (yearlyAvg[i] < (avgAll - 2)) {
                StdOut.println((1900 + i) + " was a cold year.");
            }
    
            else if (yearlyAvg[i] > avgAll +2) {
                StdOut.println((1900 + i) + " was a hot year.");
            }
        }

    }
}
