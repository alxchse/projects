// **************************************************************
// Alexandra Chase
// CSCI 131-03
// September 08 2022
// Project 1
//
// This project will estimate the distance between two latitude
// and longitutde coordinates on the earth, home and destination,
// using the haversine formula. 
// These coordinates will be entered by the user through the 
// command line. It will also give the user an option to see a 
// map with markers and lines connecting the locations.
//****************************************************************

public class Flight {
    public static void main(String [ ] args) {


    final double earthRadius = 3963.1676; // Earth's radius is a constant

// Codes for home coordinates from user input
    double homeLatitude = Double.parseDouble(args[0]);
    double homeLongitude = Double.parseDouble(args[2]);
    char homeNorthSouth = args[1].charAt(0);
    char homeEastWest = args[3].charAt(0);
    double homeLatitudeDec = homeLatitude;
    double homeLongitudeDec = homeLongitude;

// home guards
        if (homeLatitude < 0 && homeLatitude > 90 && homeLongitude < 0 && homeLongitude > 180) {
            StdOut.println("Sorry, the home coordinates you entered are not valid.");
            StdOut.println("Because of the invalid coordinates, the program will terminate.");
            System.exit(1);
        }

        if (homeNorthSouth != 'N' && homeNorthSouth != 'n' && homeNorthSouth != 'S' && homeNorthSouth != 's') {
            StdOut.println("Sorry, the home coordinates you entered are not valid.");
            StdOut.println("Because of the invalid  b coordinates, the program will terminate.");
            System.exit(1);
        }

        if (homeEastWest != 'E' && homeEastWest != 'e' && homeEastWest != 'W' && homeEastWest != 'w') {
            StdOut.println("Sorry, the home coordinates you entered are not valid.");
            StdOut.println("Because of the invalid  c coordinates, the program will terminate.");
            System.exit(1);
        }

// east and south conversions to negative coordinates
        if (homeNorthSouth == 'S' || homeNorthSouth == 's')
            homeLatitudeDec = (homeLatitude * -1);

        if (homeEastWest == 'W' || homeEastWest == 'w')
            homeLongitudeDec = (homeLongitude * -1);


    double homeLatRad = (homeLatitudeDec * (Math.PI / 180.0)); // home latitude in radians
    double homeLongRad = (homeLongitudeDec * (Math.PI / 180.0)); // home longitude in radians

// Codes for destiantion coordinates from user input
    double desLatitude = Double.parseDouble(args[4]);
    double desLongitude = Double.parseDouble(args[6]);
    char desNorthSouth = args[5].charAt(0);
    char desEastWest = args[7].charAt(0);
    double desLatitudeDec = desLatitude; 
    double desLongitudeDec = desLongitude;

// destination guards
        if (desLatitude < 0 || desLatitude > 90 || desLongitude < 0 || desLongitude > 180) {
            StdOut.println("Sorry, the destination coordinates you entered are not valid.");
            StdOut.println("Because of the invalid coordinates, the program will terminate.");
            System.exit(1);
        }

        if (desNorthSouth != 'N' && desNorthSouth != 'n' && desNorthSouth != 'S' && desNorthSouth != 's') {
            StdOut.println("Sorry, the destination coordinates you entered are not valid.");
            StdOut.println("Because of the invalid coordinates, the program will terminate.");
            System.exit(1);
        }

        if (desEastWest != 'E' && desEastWest != 'e' && desEastWest != 'W' && desEastWest != 'w') {
            StdOut.println("Sorry, the destination coordinates you entered are not valid.");
            StdOut.println("Because of the invalid coordinates, the program will terminate.");
            System.exit(1);
        }

// east and south conversions
        if (desNorthSouth == 'S' || desNorthSouth ==  's')
            desLatitudeDec = (desLatitude * -1);

        if (desEastWest == 'W' || desEastWest == 'w')
            desLongitudeDec = (desLongitude * -1);

    double desLatRad = (desLatitudeDec * (Math.PI / 180.0)); // destination latitude in radians
    double desLongRad = (desLongitudeDec * (Math.PI / 180.0)); // destination longitude in radians

// Distance calculations in radians
    double distanceLat = (homeLatRad - desLatRad);
    double distanceLong = (homeLongRad - desLongRad);

// print out radians

// Haversine Formula calculation
    double chunk1 = (Math.sin(distanceLat / 2.0)) * (Math.sin(distanceLat / 2.0));
    double chunk2 = (Math.sin(distanceLong / 2.0)) * (Math.sin(distanceLong / 2.0));
    double chunk3 = (Math.cos(homeLatRad) * Math.cos(desLatRad));
    double a = chunk1 + (chunk2 * chunk3);
    double c = 2 * earthRadius * Math.atan2(Math.sqrt(a), Math.sqrt(1-a));

// print results
    StdOut.println("Home latitude is " + homeLatitude + " " + homeNorthSouth + ".");
    StdOut.println("Home longitude is " + homeLongitude + " " + homeEastWest + ".");
    StdOut.println("Destination latitude is " + desLatitude + " " + desNorthSouth + ".");
    StdOut.println("Destination longitude is " + desLongitude + " " + desEastWest + ".");
    StdOut.println("The distance from home to destination is " + c + " miles.");

// map output
    StdOut.println("Would you like to see a map of your trip?");
    String response = StdIn.readString();

        if (!(response.equalsIgnoreCase("Yes"))) {
            StdOut.println("Ok, goodbye.");
            System.exit(1);
        }
    StdOut.println("You said yes!");
    StdOut.println("Right-click this link or copy it into your browser:");

// convert coordinates to string

    String urlHLat = Double.toString(homeLatitudeDec);
    String urlHLong = Double.toString(homeLongitudeDec);
    String urlDLat = Double.toString(desLatitudeDec);
    String urlDLong = Double.toString(desLongitudeDec);

// run url 
    String url = ("https://www.mapquestapi.com/staticmap/v4/getmap?" + "key=t8xhSEnIxadDAwSL0fSuJer5JAWqGPZ5&size=400,400&type=map&bestfit="
    + "&pois=A," + urlHLat + "," + urlHLong + "%7CB," + urlDLat + "," + urlDLong + "&polyline=color:0xff0000%7Cwidth:3%7C"
    + urlHLat + "," + urlHLong + "," + urlDLat + "," + urlDLong);

    System.out.println(url);
    StdDraw.picture(0.5, 0.5, url);

    StdOut.println("Thank you, bye!");


    } // end of class
} // end of main