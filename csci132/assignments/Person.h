#ifndef _PERSON_H
#define _PERSON_H

#include <string>

class Person
{
  // Note: everything in this class is public (and constant)
public:
   const std::string name;       // Full name, e.g. "Lakshmi Narayan Nehru"
   const std::string occupation; // Notable occupation(s), e.g. "Prime Minister" or "Scribe"
   const int birthYear;     // Approx. birth year, or zero if unknown
   const int deathYear;     // Approx. death year, or zero if unknown or not applicable
   const std::string lineage;    // Lineage, e.g. "son of Mausa Ram Kaul"

public:
   Person(std::string myName, std::string myOccupation, int myBirthYear, int myDeathYear, std::string myLineage);

   // Note: Compiler will provide a suitable copy-constructor, assignment-operator,
   // and destructor, because there are no pointers held in a Person object.

   std::string toString() const;

   void print() const;

   static Person *parseLine(std::string line);

};  // end Person

#endif
