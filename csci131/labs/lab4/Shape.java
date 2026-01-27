//****************************************************************
// Shape.java
// Alexandra Chase
// September 21 2022
//
// Makes triangle

public class Shape extends HCTurtle {
    public static void main (String[] args) {


        WakeTurtle(); // wake up
    
        int count = 0; // start tally at 0

        while (count < 3) { // keep looping up to three times
    
             Straight(1 * FOOT); // walk forward a foot
             Turn(120); // turn 120 degrees
             count ++; // update count
            
        } 
    }
}
