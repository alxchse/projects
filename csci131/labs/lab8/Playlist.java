// Author:
// Date:
//
// This is a library of functions for working with "Playlists", lists of songs.
// It is meant to be used as part of other programs.

public class Playlist {

    public static int countLinesInFile(String filename) {
        int count = 0;

        In inFile = new In(filename);
        while (inFile.hasNextLine()) {
            String line = inFile.readLine();
            count++;
       }
       inFile.close();
       return count;
    }   // end of countLinesInFile


    public static String[] readFromFile(String filename) {
        StdOut.printf("Loading song titles from %s ... ", filename);
        int numSongs = countLinesInFile(filename);                     // how many songs

        String[] songs = new String[numSongs];                       // new array of songs
        In inFile = new In(filename);                                // open file
            for (int i = 0; i < numSongs; i++) {
                songs[i] = inFile.readLine();                        // each line goes into array
        }
        inFile.close();                                                // close file
        StdOut.printf(" found %d songs\n", numSongs);
        return songs;                                                // return songs
    }   // end of readFromFile


    public static String getSongTitle(String song) {
        int pos = song.indexOf(" -- ");
        return song.substring(0, pos);
    }   // end of getSongTitle


    public static String getSongArtist(String song) {
        int posA = song.indexOf(" -- ");
        int posB = song.lastIndexOf(" -- ");
        return song.substring(posA + 4, posB);
    }   // end of getSongArtist


    public static String getSongDuration(String song) {
        int pos = song.lastIndexOf(" -- ");
        return song.substring(pos + 4);
    } // end of getSongDuration


    public static void shuffle(String[] songs) {
        for (int i = 0; i < songs.length; i++) {
            int j = (StdRandom.uniform(0, songs.length));
            String temp = songs[i];
            songs[i] = songs[j];
            songs[j] = temp;
        }

    }   // end of shuffle
    

    public static void print(String[] songs) {

        // Print out the shuffled list.
        // Number each line of output for the user's convenience, and align the
        // columns, e.g.:
        // ###  Title                  Artist                           mm:ss
        //   1. Happy                  Pharrell Williams                 3:24
        //   2. Southern Cross         Crosby, Stills, Nash and Young    2:30
        // .... ...                    ...                              ..:..
        StdOut.printf("###  %-30s %-30s mm:ss\n", "Title", "Artist");
        for (int i = 0; i < songs.length; i++) {
            StdOut.printf("%3d. %-30s %-30s %5s\n",
                    i+1,
                    Playlist.getSongTitle(songs[i]),
                    Playlist.getSongArtist(songs[i]),
                    Playlist.getSongDuration(songs[i]));
        }

        int[] durations = new int[songs.length]; // length of each song, in seconds
        for (int i = 0; i < songs.length; i++) {
            String d = Playlist.getSongDuration(songs[i]);
            durations[i] = SongTime.toSeconds(d);
        }

        StdOut.println("   Shortest song:    " + SongTime.toMMSS(StdStats.min(durations)));
        StdOut.println("    Longest song:   " + SongTime.toMMSS(StdStats.max(durations)));;
        StdOut.println("    Average song:    " + SongTime.toMMSS((int)StdStats.mean(durations)));
        StdOut.println("  Total duration:   " + SongTime.toMMSS((int)(durations.length*StdStats.mean(durations))));

    } // end of print

    public static String pickSongAtRandom(String[] songs) {
        return songs[StdRandom.uniform(0, songs.length)];
    } // end of pickSongAtRandom


    public static String[] generatePlaylist(String[] songs, int n) {
        String[] playlist = new String[n];
        for (int i = 0; i < n; i++){
            playlist[i] = Playlist.pickSongAtRandom(songs);
        }
    return playlist;
    } // end of generatePlaylist


    public static void main(String[] args) {
        StdOut.println("Sorry, this class is a library meant to be used as part of other programs.");
    
    } // ene of main

} // end of playlist
