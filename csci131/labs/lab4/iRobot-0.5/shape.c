/*******************************************************************************
 * shape.c
 *
 * A simple iRobot program to demo in lab4.
 * Plays a few songs while crashing into things.
 * Re-written by kwalsh@cs.holycross.edu, based on original simple.c.
 *******************************************************************************/
#include "iRobot.h"


int main(void)
{
    // start the body if needed
    WakeRobot();

    // wait for button, then play the song from deliverance
    WaitForBlackButton();
    
        int count = 0; // start tally at 0

        while (count < 3) { // keep looping up to three times
    
             Straight(1 * FOOT); // walk forward a foot
             Turn(120); // turn 120 degrees
             count ++; // update count
            
        } 
    
}





