// A test program for Playlist.readFromFile().
// Example:
//   java TestReading
// Output will be similar to:
//   File songs.txt has 17 songs in it.
//   The first line is:
//      God Save the King -- Alan Turing -- 2:00
//   The last line is:
//      Ordinary Joe -- Terry Callier -- 4:10

public class TestReading {
    public static void main(String[] args) {
        if (args.length == 0)
            args = new String[] { "songs.txt" };

        for (int i = 0; i < args.length; i++) {
            String[] songs = Playlist.readFromFile(args[i]);
            StdOut.printf("File %s has %d songs in\n", args[i], songs.length);
            StdOut.println("The first line is:\n  " + songs[0]);
            StdOut.println("The last line is:\n  " + songs[songs.length - 1]);
        }
    }
}
