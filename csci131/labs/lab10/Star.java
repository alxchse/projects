/*----------------------------------------------------------------
 *  Author:   K. Walsh
 *  Email:    kwalsh@holycross.edu
 *  Written:  7/8/2015
 *  Updated:  9/11/2021 - added animation.
 *  
 *  A class used for drawing a "star" sprite. It is meant to be
 *  used by other classes, e.g. games, but it also has a main()
 *  function for testing purposes.
 *
 *  Example: java Star
 *----------------------------------------------------------------*/

import java.awt.Color;

/**
 * Each Star object represents a star-shaped sprite. It has a position, a color,
 * a size, etc., and it can draw itself using the StdDraw canvas. For example,
 * here is how to create a 5-pointed star with radius 0.1 and (x, y) coordinates
 * (0.5, 0.5), then draw it on the screen:
 *
 *    Star s = new Star(0.5, 0.5, 0.1, 5);
 *    s.draw();
 *    StdDraw.show();
 *
 * You can change the star's position, size, color, etc. using the accessor
 * functions. Changing these properties doesn't affect what has already been
 * drawn. Instead, you must call draw() again to draw the new image.
 *
 * Star objects have some support for animation. Each star has a velocity, and
 * the move() function will update the position according to the velocity. There
 * is also some code for detecting when the star has gone off the edge of the
 * canvas and either "wrapping around" to the other side or "bouncing" off the
 * edge. See main() below for an example of this kind of animation.
 */
public class Star { 

    // Position of this star on the canvas. Units are "meters".
    private double x, y;

    // Velocity of this star in the x and y directions. Positive vx values mean
    // rightward. Positive vy values mean upwards. Units are "meters" per
    // second.
    private double vx, vy;

    // Radius of this star when drawn on the canvas. Units are "meters".
    private double radius;

    // How much this star has been rotated (angle, in radians).
    private double rotation;

    // Number of points this star has.
    private int points;

    // Color used to draw this star on the canvas.
    private Color color;

    // Sharpness factor for the border of a star. Larger means more pointy. All
    // stars share the same sharpness factor, and it is constant.
    private static final double SHARPNESS = 0.2;

    /**
     * Constructor: Initializes a new n-pointed star at the given (x, y)
     * coordinates with the given radius. The color is BLACK initially.
     */
    public Star(double x, double y, double radius, int n) {
        this.x = x;
        this.y = y;
        this.vx = 0.0;
        this.vy = 0.0;
        this.radius = radius;
        this.points = n;
        this.color = StdDraw.BLACK;
    }

    /**
     * Constructor: Initialize a new n-pointed star. It will be placed at
     * coordinates (0.5, 0.5) with radius 0.1. The color is BLACK initially.
     */
    public Star(int n) {
        this.x = 0.5;
        this.y = 0.5;
        this.vx = 0.0;
        this.vy = 0.0;
        this.radius = 0.1;
        this.points = n;
        this.color = StdDraw.BLACK;
    }

    /**
     * Return a string representation of this star. Possibly useful for
     * debugging.
     */
    public String toString() {
        return "Star(" + x + ", " + y + ", " + radius + ", " + points + ")" +
            " with speed " + speed();
    }

    /**
     * Set the x coordinate of this star on the canvas. Units are "meters". This
     * does not affect any drawing that has already been done. The next time
     * draw() is called, the star will be drawn at the new position.
     */
    public void setXPosition(double x) {
        this.x = x;
    }

    /**
     * Set the y coordinate of this star on the canvas. Units are "meters". This
     * does not affect any drawing that has already been done. The next time
     * draw() is called, the star will be drawn at the new position.
     */
    public void setYPosition(double y) {
        this.y = y;
    }

    /**
     * Set the position of this star on the canvas. Units are "meters". This
     * does not affect any drawing that has already been done. The next time
     * draw() is called, the star will be drawn at the new position.
     */
    public void setPosition(double x, double y) {
        this.x = x;
        this.y = y;
    }

    /**
     * Set the velocity of this star (both speed and direction). Units are
     * "meters" per second. The velocity values affect how much the star will
     * move in the x and y directions when the move() function is called.
     * Positive vx values mean rightward. Positive vy values mean upwards.
     */
    public void setVelocity(double vx, double vy) {
        this.vx = vx;
        this.vy = vy;
    }

    /**
     * Set the speed of this star. Units are "meters" per second. The speed
     * values affect how fast the star is moving, but not the direction. To
     * change the direction, use setVelocity() instead. Note: if the star is
     * currently not moving at all, setting the speed to anything other than
     * zero will cause it to pick a random direction.
     */
    public void setSpeed(double s) {
        double oldSpeed = speed();
        if (oldSpeed < 0.0001) {
            // Avoid dividing by zero by picking a random direction.
            double angle = StdRandom.uniform(0, 2*Math.PI);
            vx = Math.cos(angle);
            vy = Math.sin(angle);
            oldSpeed = 1.0;
        }
        // Multiply current velocity to speed or slow the star.
        vx = vx * s / oldSpeed;
        vy = vy * s / oldSpeed;
    }

    /**
     * Change the velocity of this star so it is heading towards some new point
     * at the given speed. If the new point is close by, the actual speed will
     * be a little less than what was requested. If the new point is very close
     * by, exactly where this star already is, then the new velocity will be
     * close to zero.
     */
    public void aimTowards(double newx, double newy, double speed) {
        double dx = newx - x;
        double dy = newy - y;
        double distance = Math.sqrt(dx*dx + dy*dy);
        if (distance < radius) {
            // The point is close by, so divide by radius (a larger number)
            // instead of distance.
            vx = speed * dx / radius;
            vy = speed * dy / radius;
        } else {
            vx = speed * dx / distance;
            vy = speed * dy / distance;
        }
    }

    /**
     * Change the velocity of this star so it is heading away from the given
     * point at the given speed. If the new point is very close by, almost
     * exactly where the star already is, then the new velocity will be in a
     * random direction instead.
     */
    public void aimAwayFrom(double newx, double newy, double speed) {
        double dx = - (newx - x);
        double dy = - (newy - y);
        double distance = Math.sqrt(dx*dx + dy*dy);
        if (distance < 0.001) {
            // The point is too close by, so use a random destination to
            // avoid dividing by zero.
            double angle = StdRandom.uniform(0, 2*Math.PI);
            dx = Math.cos(angle);
            dy = Math.sin(angle);
            distance = 1.0;
        }
        vx = speed * dx / distance;
        vy = speed * dy / distance;
    }

    /**
     * Calculate the distance from this star to a specific point.
     */
    public double distanceTo(double otherx, double othery) {
        double dx = x - otherx;
        double dy = y - othery;
        return Math.sqrt(dx*dx + dy*dy);
    }

    /**
     * Calculate the distance from this star to another star.
     */
    public double distanceTo(Star other) {
        return distanceTo(other.getX(), other.getY());
    }

    /**
     * Calculate the distance from this star to a ball.
     */
    public double distanceTo(Ball ball) {
        return distanceTo(ball.getX(), ball.getY());
    }

    /**
     * Calculate the speed of this ball. Units are "meters" per second.
     */
    public double speed() {
        return Math.sqrt(vx*vx + vy*vy);
    }

    /**
     * Check whether this star is touching another.
     */
    public boolean touching(Star other) {
        // this star is touching other if the distance
        // is less than our combined sizes.
        return (distanceTo(other) < radius + other.getRadius());
    }

    /*
     * Check whether this star is touching a ball.
     */
    public boolean touching(Ball ball) {
        // this ball is touching other if the distance
        // is less than our combined sizes.
        return (distanceTo(ball) < radius + ball.getRadius());
    }

    /**
     * Check whether this star is completely covering another.
     */
    public boolean covering(Star other) {
        // this star is covering other if we are bigger than
        // the distance plus their size.
        return (radius > distanceTo(other) + other.getRadius());
    }

    /**
     * Check whether this star is completely covering a ball.
     */
    public boolean covering(Ball ball) {
        // this ball is covering ball if we are bigger than
        // the distance plus their size.
        return (radius > distanceTo(ball) + ball.getRadius());
    }


    /**
     * Set the radius of this star. Units are "meters". This does not affect any
     * drawing that has already been done. The next time draw() is called, the
     * star will be drawn with the new radius.
     */
    public void setRadius(double r) {
        radius = r;
    }

    /**
     * Set the color of this star. This does not affect any drawing that has
     * already been done. The next time draw() is called, the star will be drawn
     * with the new color.
     */
    public void setColor(Color c) {
        color = c;
    }

    public void setHue(double hue) {
        color = Color.getHSBColor((float)hue, 0.7f, 0.6f);
    }

    /**
     * Return the x coordinate of this star.
     */
    public double getX() {
        return x;
    }

    /**
     * Return the y coordinate of this star.
     */
    public double getY() {
        return y;
    }

    /**
     * Return the radius of this star.
     */
    public double getRadius() {
        return radius;
    }

    /**
     * Return the rotation amount of this star (as an angle, in radians).
     */
    public double getRotationAngle() {
        return rotation;
    }

    /**
     * Return the rotation amount of this star (as an angle, in degrees).
     */
    public double getRotationDegrees() {
        return Math.toDegrees(rotation);
    }

    /**
     * Set the rotation amount of this star (as an angle, in radians).
     */
    public void setRotationAngle(double angle) {
        rotation = angle;
    }

    /**
     * Set the rotation amount of this star (as an angle, in degrees).
     */
    public void getRotationDegrees(double degrees) {
        rotation = Math.toRadians(degrees);
    }

    /**
     * Rotate this star counter-clockwise by some angle (in radians). You can
     * use negative angles to rotate clockwise.
     */
    public void rotateAngle(double angle) {
        rotation += angle;
    }

    /**
     * Rotate this star counter-clockwise by some angle (in degrees). You can
     * use negative angles to rotate clockwise.
     */
    public void rotateDegrees(double degrees) {
        rotation += Math.toRadians(degrees);
    }

    /**
     * Calculate the approximate size (or "surface area") of this star. Units
     * are square "meters".
     */
    public double size() {
        return Math.PI * radius * radius;
    }

    /**
     * Make the size (or "surface area") of this ball larger or smaller by the
     * given amount. Units are square "meters".
     */
    public void grow(double amount) {
        setSize(size() + amount);
    }

    /**
     * Set the size of this ball. Units are square "meters".
     */
    public void setSize(double newSize) {
        radius = Math.sqrt(newSize / Math.PI);
    }

    /**
     * Draw this star on the StdDraw canvas. After calling this function,
     * clients should call one of the StdDraw.show() functions so that the
     * updated canvas appears on the screen.
     */
    public void draw() {
        StdDraw.setPenColor(color);
        // Calculate the corners defining the boundary of the star.
        // For an n-sided star, there are 2n corners (the outer corners and the
        // inner corners).
        double[] px = new double[2*points]; // x coordinates of each corner
        double[] py = new double[2*points]; // y coordinates of each corner
        for (int i = 0; i < 2 * points; i++) {
            double angle = rotation + i * 2 * Math.PI / (2 * points);
            double r = radius * (1.0 + (i % 2 == 0 ? SHARPNESS : -SHARPNESS));
            px[i] = x + r * Math.sin(angle);
            py[i] = y + r * Math.cos(angle);
        }
        StdDraw.filledPolygon(px, py);
    }

    /**
     * Update the position of this star, as if it had moved for the given
     * duration of time (in milliseconds) in the direction specified by its
     * velocity. It is intended that clients will call move(X) once every X
     * milliseconds. For example, you might call move(10) once every 100
     * milliseconds (or 10 times per second), which will give the illusion of
     * motion animation at 10 frames per second.
     */
    public void move(int durationInMilliseconds) {
        // We divide by 1000 because the (vx, vy) velocities are in meters per
        // second, not meters per millisecond.
        x += vx * durationInMilliseconds / 1000.0;
        y += vy * durationInMilliseconds / 1000.0;
    }

    /**
     * If this star has completely moved off the StdDraw canvas, change its
     * position so it "wrap" around to the other side of the canvas. The
     * velocity is left as is. Calling this function between calls to move()
     * will give the illusion that the left and right sides of the screen "wrap
     * around", and similarly the top and bottom of the screen "wrap around".
     *
     * Note: This function assumes the drawing window scale has not been changed
     * from the default.
     */
    public void wrap() {
        while (x > 1.0 + radius) x -= (1.0 + 2.0*radius);
        while (y > 1.0 + radius) y -= (1.0 + 2.0*radius);
        while (x < 0.0 - radius) x += (1.0 + 2.0*radius);
        while (y < 0.0 - radius) y += (1.0 + 2.0*radius);
    }

    /**
     * If this star is moving towards and touching an edge of the StdDraw
     * canvas, negate its velocity so it appears to "bounce" off the edge. The
     * position and speed are left alone, only the direction of travel is
     * changed. Calling this function between calls to move() will give the
     * illusion that the edges of the screen are solid walls.
     *
     * Note: This function assumes the drawing window scale has not been changed
     * from the default.
     */
    public void bounce() {
        if ((vx > 0 && x + radius > 1.0) || (vx < 0 && x - radius < 0.0)) {
            vx *= -1;
        }
        if ((vy > 0 && y + radius > 1.0) || (vy < 0 && y - radius < 0.0)) {
            vy *= -1;
        }
    }

    /**
     * If this star is touching the other star, this star will change it's
     * direction so that it is moving directly away from the other star.
     */
    public void bounce(Star other) {
        if (distanceTo(other) < this.radius + other.radius) {
            aimAwayFrom(other.getX(), other.getY(), this.speed());
        }
    }

    /**
     * If this star is touching the ball, this star will change it's
     * direction so that it is moving directly away from the ball.
     */
    public void bounce(Ball other) {
        if (distanceTo(other) < this.radius + other.getRadius()) {
            aimAwayFrom(other.getX(), other.getY(), this.speed());
        }
    }

    /**
     * A main() function for testing purposes.
     * <pre>
     * {@code
     *   // Draw a large yellow 7-pointed star in the middle of the canvas.
     *   Star a = new Star(0.5, 0.5, 0.3, 7);
     *   a.setColor(StdDraw.YELLOW);
     *   a.draw();
     *
     *   // Draw 10 small blue 11-pointed stars at random positions.
     *   for (int i = 0; i < 10; i++) {
     *       Star b = new Star(StdRandom.uniform(),
     *               StdRandom.uniform(), 0.03, 11);
     *       b.setColor(StdDraw.BLUE);
     *       b.draw();
     *   }
     *
     *   // Show the canvas on the screen.
     *   StdDraw.show();
     * }
     * </pre>
     */
    public static void main(String args[]) {
        // Draw a large yellow 7-pointed star in the middle of the canvas.
        Star a = new Star(0.5, 0.5, 0.3, 7);
        a.setColor(StdDraw.YELLOW);
        a.draw();

        // Draw 10 small blue 11-pointed stars at random positions.
        for (int i = 0; i < 10; i++) {
            Star b = new Star(StdRandom.uniform(),
                    StdRandom.uniform(), 0.03, 11);
            b.setColor(StdDraw.BLUE);
            b.draw();
        }

        // Show the canvas on the screen.
        StdDraw.show();
    }
}
