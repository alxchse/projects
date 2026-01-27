/*----------------------------------------------------------------
 *  Author:   K. Walsh
 *  Email:    kwalsh@holycross.edu
 *  Written:  7/6/2015
 *  Updated:  8/15/2022 - changed ordering of calculations
 *  
 *  Calculates the impact velocity of a hailstone, along with the free-fall
 *  velocity and terminal velocity.
 *
 *  Example: java Hail 0.02 2000 
 *  Output:
 *    Gravitational acceleration: 9.81 m/s^2
 *         Density of atmosphere: 1.225 kg/m^3
 *                Density of ice: 934.0 kg/m^3
 *           Coefficient of drag: 0.5
 *         Diameter of hailstone: 0.02 m
 *           Height of hailstone: 2000.0 m
 *           Radius of hailstone: 0.01 m
 *    Cross-section of hailstone: 3.141592653589793E-4 m^2
 *           Volume of hailstone: 4.1887902047863905E-6 m^3
 *             Mass of hailstone: 0.003912330051270489 kg
 *             Terminal velocity: 19.972814176336016 m/s
 *            Free-fall velocity: 198.09088823063013 m/s
 *               Impact velocity: 19.972814176336016 m/s
 *   
 *
 *----------------------------------------------------------------*/

public class Hail {

    // Acceleration due to gravity, in m/s^2 (meters per second squared).
    public static final double GRAVITY = 9.81;

    // Density of fluid atmosphere, in kg/m^3 (kilograms per cubic meter).
    public static final double AIR_DENSITY = 1.225;

    // Density of ice, in kg/m^3 (kilograms per cubic meter).
    public static final double ICE_DENSITY = 934.0;

    // Coefficient of drag for a typical hailstone (unitless).
    public static final double DRAG = 0.5;

    public static void main(String args[]) {

        double diameter; // diameter of the falling object (m)
        double height; // height of the falling object (m)

        double radius; // radius of the falling object (m)
        double area;   // projected area of the falling object (m^2)
        double volume; // volume of the falling object (m^3)
        double mass;   // mass of the falling object (kg)

        double freefallVelocity; // result of free-fall velocity calculation
        double terminalVelocity; // result of terminal velocity calculation
        double impactVelocity;   // final velocity at time of impact

        // Get input parameters from command-line arguments.
        diameter = Double.parseDouble(args[0]);
        height = Double.parseDouble(args[1]);

        // Calculate properties of the hailstone and the free-fall velocity.
        radius = diameter / 2.0;
        area = Math.PI * Math.pow(radius, 2);
        freefallVelocity = Math.sqrt(2.0 * GRAVITY * height);

        // Calculate volume and mass of hailstone.
        volume = ((4.0/3.0) * Math.PI) * Math.pow(radius, 3);
        mass = volume * ICE_DENSITY; 
        // Calculate terminal velocity and impact velocity.
        terminalVelocity = Math.sqrt((2.0 * mass * GRAVITY) / (area*AIR_DENSITY*DRAG));
        impactVelocity = Math.min(freefallVelocity, terminalVelocity);

        // Print the inputs, intermediate calculations, and the results.
        System.out.println("Gravitational acceleration: " + GRAVITY + " m/s^2");
        System.out.println("     Density of atmosphere: " + AIR_DENSITY + " kg/m^3");
        System.out.println("            Density of ice: " + ICE_DENSITY + " kg/m^3");
        System.out.println("       Coefficient of drag: " + DRAG);
        System.out.println("     Diameter of hailstone: " + diameter + " m");
        System.out.println("       Height of hailstone: " + height + " m");
        System.out.println("       Radius of hailstone: " + radius + " m");
        System.out.println("Cross-section of hailstone: " + area + " m^2");
        System.out.println("       Volume of hailstone: " + volume + " m^3");
        System.out.println("         Mass of hailstone: " + mass + " kg");
        System.out.println("         Terminal velocity: " + terminalVelocity + " m/s");
        System.out.println("        Free-fall velocity: " + freefallVelocity + " m/s");
        System.out.println("           Impact velocity: " + impactVelocity + " m/s");
    }
}
