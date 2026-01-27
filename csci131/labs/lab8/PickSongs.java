//**************************************************************************
// PickSongs.java
// Author: Alexandra Chase
// Date: 11/08/2022
// Class: CSCI 131
// Purpose: Interactively generate a randomized playlist from a list of songs.
//**************************************************************************

public class PickSongs {

    public static void main(String[] args) {

        // Load data from a file containing names of songs. 
        String[] songs = Playlist.readFromFile("songs.txt");

        // Print all the songs, in whatever order they happen to be, in a nicely
        // formatted list.
        StdOut.println("Here are the available songs:");
        Playlist.print(songs);

        // Make a playlist containing n songs.
        StdOut.print("How many songs do you want in your playlist? ");
        int n = StdIn.readInt();
        String[] playlist = Playlist.generatePlaylist(songs, n);

        // Print the resulting playlist in a nicely formatted list.
        StdOut.println("Here is your playlist:");
        Playlist.print(playlist);

 
    }
}
