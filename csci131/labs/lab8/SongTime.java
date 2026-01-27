// Author: K. Walsh
// Date: 14 Oct 2021
//
// This is a library of functions for working with song durations.
// It is meant to be used as part of other programs.

public class SongTime {

    /* Given a duration in "min:sec" format, this function converts to the
     * equilvalent number of seconds. For example, given "3:24", it will return
     * 3*60+24 = 204 seconds.
     */
    public static int toSeconds(String mmss) {
        int n = mmss.length();
        // Everything but the last 3 characters is the minutes part.
        int mm = Integer.parseInt(mmss.substring(0, n-3));
        // Last two characters are the seconds part.
        int ss = Integer.parseInt(mmss.substring(n-2));
        return mm*60 + ss;
    }

    /* Given a duration in seconds, this function converts to the equivalent
     * "min:sec" format. For example, given 204 seconds, it will return "3:24".
     */
    public static String toMMSS(int seconds) {
        int mm = seconds / 60;
        int ss = seconds % 60;
        return String.format("%d:%02d", mm, ss);
    }

}
