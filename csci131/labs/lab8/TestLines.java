// A test program for Playlist.countLinesInFile().
// Example:
//   java TestLines
// Output will be similar to:
//   File semester-grades.txt has 62 lines
//   File songs.txt has 17 lines
//   File TestLines.java has 22 lines
//   File SongTime.java has 31 lines
//   File Playlist.java has 119 lines

public class TestLines {
    public static void main(String[] args) {
        if (args.length == 0)
            args = new String[] { "semester-grades.txt", "songs.txt",
                "TestLines.java", "SongTime.java", "Playlist.java" };

        for (int i = 0; i < args.length; i++) {
            int n = Playlist.countLinesInFile(args[i]);
            StdOut.printf("File %s has %d lines\n", args[i], n);
        }
    }
}
