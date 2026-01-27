/*----------------------------------------------------------------
 *  Z.Lucas  
 *
 *  Used to compare java code to c iRobot code, 
 *
 *  Example: java Simple
 *----------------------------------------------------------------*/

public class Simple extends HCTurtle {
    public static void main(String[] args) {

        WakeTurtle();
        Straight(FOOT);
        Turn(90);
        Straight(METER);
        Turn(60);
        Straight(200); 

    }
}
