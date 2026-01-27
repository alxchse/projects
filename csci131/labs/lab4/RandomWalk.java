/*----------------------------------------------------------------
 *  Z.Lucas  
 *
 *  "Infinitely" drive, when hits the edge of the
 *  drawing panel, turns a random angle and then
 *  continues driving.
 *
 *  Example: java RandomWalk
 *----------------------------------------------------------------*/
public class RandomWalk extends HCTurtle {

    public static void main(String[] args) {
        // start the body if needed
        WakeTurtle();

        //loop "forever"
        while (true) {
            Straight(0); // walk until a wall
            Turn(PickRandomBackwardsAngle());  // turn a random direction
        } //for each shape side
    } //end main

} //end RandomWalk
