/*----------------------------------------------------------------
 *  Z.Lucas  
 *
 *  Similar to random.c of lab4, but without the songs
 *  and lights. The movement code is nearly identical.
 *
 *  As long as we keep hitting the edge of the drawing panel, the
 *  turn a random angle and continue driving.  Once the edge
 *  is hit, exit the loop and quit.
 *
 *  Example: java Random
 *----------------------------------------------------------------*/
public class Random extends HCTurtle {

    public static void main(String[] args) {
        // start the turtle
        WakeTurtle();

        // Now repeatedly wander around.
        // Start by driving straight somewhere
        boolean ok;
        ok = Straight(2 * METER);

        // Now loop so long as we keep bumping 
        while (!ok) {
            int random_angle = PickRandomBackwardsAngle();
            Turn(random_angle);

            // Now walk again
            ok = Straight(2 * METER);
        } // end while loop

    } //end main

} //end RandomWalk
