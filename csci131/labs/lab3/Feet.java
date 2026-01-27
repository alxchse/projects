/*----------------------------------------------------------------
 *  Author:   Alexandra Chase
 *  Email:    amchas26@g.holycross.edu
 *  Written:  09/14/2022
 *  
 *  Picks a random number and prints an example creature with that many feet.
 *
 *  Example: java Feet
 *  Output: A starfish has 5 feet.
 *----------------------------------------------------------------*/

public class Feet {
    public static void main(String[] args) { 
        int n;           // number of feet
        String example;  // name of creature with that many feet

      if (args.length == 1) {                // if user inputs a number
        n = Integer.parseInt(args[0]);       // then n will be that number
      }                                    
      else {                                  // otherwise n will be 
        n = (int)(0 + Math.random() * 16);    // a random number
      }

        // Determine an appropriate creature.
        // NOTE: We use the empty-string ("") to indicate
        // that no creature is known with that many feet.
        if (n == 0)
          example = "A snake";
        else if (n == 1)
          example = "A mollusc";
        else if (n == 2)
          example = "A duck";
        else if (n == 4)
          example = "A horse";
        else if (n == 5)
          example = "A starfish";
        else if (n == 6)
          example = "An ant";
        else if (n == 8)
          example = "An octopus";
        else if (n == 10)
          example = "A lobster";
        else if (n == 14)
          example = "An isopod";
        else if (n == 16)
          example = "A caterpillar";
        else if (n >= 30 && n <= 298 && n%2 == 0)
          example = "A centipede";
        else
          example = ""; // no such creature exists


        // Print response, or an error message if no example was found.
        if (example.equals("A mollusc"))
          System.out.println(example + " has " + n + " foot."); // proper grammar for mollusc

        else if (!example.equals(""))
          System.out.println(example + " has " + n + " feet.");
        
        else
          System.out.println("Sorry, I can't think of a creature with " + n + " feet.");
        
    } //end of main
} //end of Feet
