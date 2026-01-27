//**************************************************************************
// ShuffleSongs.java
// Author: 
// Date:
// Class: CSCI 131
// Purpose: Shuffle the songs in a playlist.
//**************************************************************************

public class ShuffleSongs {

    public static void main(String[] args) {

        // Load data from a file containing names of songs. 
        String[] songs = Playlist.readFromFile("songs.txt");

        // Shuffle them into random order.
        Playlist.shuffle(songs);
        Playlist.print(songs);

        }
        
    }

