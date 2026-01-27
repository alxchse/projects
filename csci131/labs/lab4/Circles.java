/*----------------------------------------------------------------
 *  Z.Lucas  
 *
 *  Drives in ever-widening circles.  If the edge of the 
 *  drawing panel is hit, then backup and spin once.
 *
 *  Example: java Circles
 *----------------------------------------------------------------*/
public class Circles extends HCTurtle {

    public static void main(String[] args) {
        WakeTurtle();

        boolean ok = Turn(360);

        // if no problems, make a larger circle, 100 radius
        if (ok)
            ok = Drive(WALK, 100, 0, 360);

        // if no problems, make a larger circle, 300 radius
        if (ok)
            ok = Drive(WALK, 300, 0, 360);

        // if no problems, make a larger circle, 500 radius
        if (ok)
            ok = Drive(WALK, 500, 0, 360);

        if (!ok) {
            Straight(-400);
            Turn(360);
        } // bumped edge, so backup and turn
    } // end of main
} //Circle class
