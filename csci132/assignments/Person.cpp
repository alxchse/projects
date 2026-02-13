
#include "Person.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

Person::Person(string myName, string myOccupation, int myBirthYear, int myDeathYear, string myLineage)
     : name(myName), occupation(myOccupation), birthYear(myBirthYear), deathYear(myDeathYear),
     lineage(myLineage)
{
} // end default constructor

string Person::toString() const
{
  ostringstream out;
  out << "Name: " << name << ", "
    << "Lived: " << birthYear << "-" << deathYear <<", "
    << "Lineage: " << lineage << ", "
    << "Occupation: " << occupation;
  return out.str();
}  // end toString

void Person::print() const
{
  cout << toString() << "\n";
}  // end print

Person* Person::parseLine(string line) {
  // If the line is blank, just ignore it and return nullptr.
  if (line.length() == 0)
    return nullptr;

  // Convert the line to an input stream.
  stringstream input(line);

  // Extract the parts. The expected format of the line is like this:
  // Lakshmi Narayan Nehru, 1800 - 1860, son of Mausa Ram Kaul, Scribe
  string name, born, dash, died, lineage, occupation;
  getline(input, name, ',');
  input >> born >> dash >> died;
  input.ignore(1, ' ');
  getline(input, lineage, ',');
  input.ignore(1, ' ');
  getline(input, occupation);
  if (!input) {
    cout << "Oops, there was a problem parsing this line:\n"
      << "  " << line << "\n";
    return nullptr;
  }

  // Allocate a new Person instance to hold the data.
  return new Person(name, occupation, atoi(born.c_str()), atoi(died.c_str()), lineage);
}

