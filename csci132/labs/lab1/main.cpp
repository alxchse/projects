// File: main.cpp
// Description: Main to run and compile Student class
// Class: CSCI 132
// Date: 30 January 2023
// Modified by Alexandra Chase

#include "Student.h"
#include <iostream>
#include <string>

int main() {
  Student s;	// an object to hold info about a student
  Student greatStudent("Alex Chase",2026); // me

  // Ask user to set the graduation date
  int yr;
  std::cout << "Enter graduation year: ";
  std::cin >> yr;
  s.setGradDate(yr);
 
  // Ask user to enter courses
  while (true) {
    std::string course;
    std::cout << "Enter name of course to be added (or type \"done\" to stop): \n";
    std::cin >> course;
    if (course == "done") {
      break;
    }
    s.addCourse(course);
  }
    greatStudent.addCourse("Montserrat");
    greatStudent.addCourse("Greek");
    greatStudent.addCourse("CSCI 132");
    greatStudent.addCourse("CSCI 135");
  
  // Print out a summary
  s.printInfo();
  s.printCourses();
  greatStudent.printInfo();
  greatStudent.printCourses();

  return 0;
} // end main

  
 
