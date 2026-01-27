// File: Student.cpp
// Description: Implementation for the Student class.
// Class: CSCI 132
// Date: 30 January 2023
// Modified by Alexandra Chase

#include "Student.h"
#include <string>
#include <iostream>

Student::Student() {
  // Postcondition:
  //	 Initializes this Student's name to "Jane Doe".
  //	 Initializes this Student's graduation date to 0.
  //	 Initializes this Student's course list to be empty.
  name = "Jane Doe";
  gradDate = 0;
  numCourses = 0;
} // end default constructor

Student::Student(std::string n, int y) {
  // Precondition:
  //   n is not empty
  //   y is positive
  //   note: you do not need to check these for this lab
  // Postcondition:
  name = n;
  gradDate = y;

} // end two-argument constructor

void Student::addCourse(std::string courseName) {
  // Precondition:
  // 	 There are less than 6 courses in the course list already.
        if (numCourses > 5) {
          std::cout << "Too many courses!\n";
          return;
        }
  // Postcondition:
  // 	 The given course is added to the list.
  courses[numCourses] = courseName; 
  numCourses++;
} // end addCourses

void Student::printInfo(void) const {

  std::cout << "Name: " << name << "\n";
  std::cout << "Graduation Date: " << gradDate << "\n";
  std::cout << "Number of Courses: " << numCourses << "\n";

} // end printInfo

void Student::printCourses(void) const {
  
  std::cout << "Here is a list of your courses: " << "\n";
  for (int i = 0; i < numCourses; i++) {
    std::cout << courses[i] << "\n";
  }

} //end printCourses

void Student::setGradDate(int year) {
  gradDate = year;
} // end setGradDate

