// Alexandra Chase
// amchas26@g.holycross.edu
// 24 March 2023
// CSCI 132
// Lab 6

#include "ArraySet.h"
#include "ArrayList.h"
#include <iostream>
#include <string>

using namespace std;

// This program is designed for a map containing nine cities,
// named "A" through "I", as shown in Figure 5-6 of the textbook.
static const int NUM_CITIES = 9;

// Given a city name, returns the number of that city. For example,
// getCityNumber("A") returns 0, 
// getCityNumber("C") returns 2, and
// getCityNumber("I") returns 8.
int getCityNumber(string city) {
  assert(city.length() == 1 && 'A' <= city.at(0) && city.at(0) < 'A'+NUM_CITIES);
  return (int)city.at(0) - 'A';
}

// Given a city number, returns the name of that city. For example,
// getCityName(0) returns "A", 
// getCityName(2) returns "C", and
// getCityName(8) returns "I".
string getCityName(int cityNumber) {
  assert(0 <= cityNumber && cityNumber < NUM_CITIES);
  string cityname = "";
  cityname += (char)('A' + cityNumber);
  return cityname;
}

// This initializes the flightMap[] array so it contains information about the
// flights available, as shown in Figure 5-6 of the textbook.
//
// Each element in the array represents a single city's info. That is,
// flightMap[i] is an ArrayList<string>, and that ArrayList cotnains all the
// cities that can be reached by direct flight from city number i.
//
// For example, flightMap[getCityNumber("C")].contains("E") is true,
// because there is a direct flight from city "C" to city "E".
void initializeFlightMap(ArrayList<string> flightMap[]) {
  flightMap[getCityNumber("A")].append("B"); // direct flight A to B
  flightMap[getCityNumber("A")].append("C"); // direct flight A to C
  flightMap[getCityNumber("B")].append("H"); // direct flight B to H
  flightMap[getCityNumber("B")].append("D"); // direct flight B to D
  flightMap[getCityNumber("C")].append("B"); // direct flight C to B
  flightMap[getCityNumber("C")].append("D"); // direct flight C to D
  flightMap[getCityNumber("C")].append("E"); // direct flight C to E
  flightMap[getCityNumber("D")].append("H"); // direct flight D to H
  flightMap[getCityNumber("D")].append("E"); // direct flight D to E
  flightMap[getCityNumber("D")].append("F"); // direct flight D to F
  flightMap[getCityNumber("H")].append("G"); // direct flight H to G
  flightMap[getCityNumber("G")].append("C"); // direct flight G to C
  flightMap[getCityNumber("E")].append("I"); // direct flight E to I
  flightMap[getCityNumber("I")].append("C"); // direct flight I to C
  flightMap[getCityNumber("F")].append("G"); // direct flight F to G
  flightMap[getCityNumber("F")].append("I"); // direct flight F to I
}


// This finds a path from one city (current) to another (dest). The path could
// be a single direct flight (if one is available), or a multi-hop itinerary
// involving stops in several other cities.
bool findPath(string current, string dest,
              const ArrayList<string> flightMap[],
              ArraySet<string>& visited,
              ArrayList<string>& solution) {
  
  bool goodPath = false;

  // (1) Has this city already been visited before? If so, there is no need to
  // check it again or do any more work -- any solution reachable through this
  // city would have already been found. Otherwise, continue processing.
  if (visited.contains(current)) {
    cout << current << " has already been visited! \n";
    return goodPath;
  } else {
    // (2 Update the set of visited cities. That way, if this same city is
    // encountered again later, the algorithm can avoid that redundant processing.
    visited.add(current);
    solution.append(current);
  }

  // (3) Check for other base cases: Is the traveler currently in the desired
  // destination city? If so, a path has been found, and there is no need for
  // further processing.
  if (current == dest){
    cout << "You are already at location " << dest << ". No further processing necessary. \n";
    return true;
  }
 
  // (4) Use the flight map to consider all the possible flights departing from
  // the current city directly to some neighboring city. For each one, see if
  // there is a way to reach the destination via that neighboring city. Only if
  // none of the above options work should we give up and declare that there is
  // no possible path from the current city to the destination.

  for (int i = 1; i <= flightMap[getCityNumber(current)].getLength(); i++){
      string nextCity = flightMap[getCityNumber(current)].getEntry(i);
      goodPath = findPath(nextCity, dest, flightMap, visited, solution);
      if (goodPath == true) {
        return goodPath;
      }
  }

  // (5) Somewhere in the above list of steps, update the solution to include a
  // list of all the cities on the itinerary. You have many options (all of
  // these work, though each one requires different code):
  //  - Add the current city to the itinerary when the traveler first arrives at
  //    that city (i.e. near the top of the function). If the destination can't
  //    be reached, and false is going to be returned, remove the unhelpful city
  //    from the itinerary.
  //  - Each time a neighboring city is considered, add that neighboring city to
  //    the itinerary just before the traveler flies there (i.e. in the middle
  //    of your code, just before a recursive function calls). If the traveler
  //    is returns with a failure, remove the unhelpful city from the itinerary
  //    before trying the next neighboring city (i.e. after a failed recursive
  //    call.
  //  - Don't add cities to the itinerary while searching at all. Instead, only
  //    add a city to the itinerary when a solution has been found and you know
  //    for sure that the city should be included in the final itinerary (i.e.
  //    in the base case, or just after a successful recursive call).
  
  // For debugging, print some or all of the parameters, either at the start of
  // your code, or maybe after updating some of the variables. You may want to
  // print the set of visited cities too.
  cout << "Traveler is at " << current << " trying to reach " << dest
    << " with itinerary so far: " << solution.toStringWithSeparator(" -> ") << endl;

  solution.remove(solution.getLength());
  return false;
}

int main(int argc, char **argv) {

  ArrayList<string> flightMap[NUM_CITIES];
  initializeFlightMap(flightMap);

  string start; // starting city
  string dest; // destination city
  
  if (argc == 3) {
    start = argv[1][0];
    dest = argv[2][0];
  } else {
    cout << "Enter a starting city: ";
    cin >> start;
    cout << "Enter a destination city: ";
    cin >> dest;
  }

  cout << "Searching for a path from "
    << start << " (city #" << getCityNumber(start) << ") to "
    << dest << " (city #" << getCityNumber(dest) << ")...\n";

  ArraySet<string> visited; // set of cities traveler has visited to so far
  ArrayList<string> solution; // an ordered list of cities connecting start to dest

  if (findPath(start, dest, flightMap, visited, solution)) {
    cout << "Path found: " << solution.toStringWithSeparator(" -> ") << endl;
  } else {
    cout << "Sorry, you can't get from " << start << " to " << dest << ".\n";
  }

  return 0;
}
