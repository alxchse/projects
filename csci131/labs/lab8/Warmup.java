// A program to calculate statistics for daily quiz grades.
// Example:
//   java Warmup bars
// Output:
//   You earned 85.98 quiz average.
//   New best score!
//   [a bar graph of quiz results is also displayed]

public class Warmup {
    public static void main(String[] args) {

        double[] grades = In.readDoubles("semester-grades.txt");
        int n = grades.length;

        double average = StdStats.mean(grades);             // finding average grade
        StdOut.printf("You earned %.2f quiz average.", average); // print avg

        StdOut.println();

        double maxSem1 = StdStats.max(grades, 0, 30);       // highest grade from sem 1
        double maxSem2 = StdStats.max(grades, 31, n);       // highest grade from sem 2
            if (maxSem1 > maxSem2) {                        // if sem1 grade is higher
                StdOut.println("Keep trying!");             // say keep trying
            }
            else {                                          // if not
                StdOut.println("New best score!");          // say new best score
            }

        double[] fractions = new double[n];                 // new array fractions
        for (int i = 0; i < n; i++)
            fractions[i] = grades[i] / 100;

        String typeGraph = args[0];                         // what type of graph user wants

        if (typeGraph.equalsIgnoreCase("points"))           
            StdStats.plotPoints(fractions);                    // print point graph
        if (typeGraph.equalsIgnoreCase("bars"))
            StdStats.plotBars(fractions);                      // print bar graph
        if (typeGraph.equalsIgnoreCase("lines"))
            StdStats.plotLines(fractions);                     // print line graph
    
    } // end of main
}// end of class
