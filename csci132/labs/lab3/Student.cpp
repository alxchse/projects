// Student.cpp
// Alexandra Chase
// amchas26@g.holycross.edu
// 17 February 2023
//
// This is the implementation file for the Student class. It largely remained 
// uneditied, I did however add the functionality to remove a course from a list of
// options and delete it from a student's profile. 


#include "Student.h"
#include "Course.h"
#include <string>
#include <iostream>

Student::Student() {
  // Postcondition:
  //	Initializes the Student's name to "Jane Doe".
  //	Initializes the Student's graduation date to 0,
  //	Initializes the Student's course list to be empty.
  name = "Jane Doe";
  gradDate = 0;
  numCourses = 0;
} // end default constructor

Student::Student(std::string name, int year) {
  // Precondition:
  //   name is not empty
  //   year is positive
  // Postcondition:
  //	 Initializes the Student's name to the given name.
  //	 Initializes the Student's graduation date to the given year.
  //	 Initializes the Student's number list to be empty.

  this->name = name;
  this->gradDate = year; // or: setGradDate(year)
  this->numCourses = 0;
} // end two-argument constructor

void Student::addCourse(Course *aCourse) {
  // Precondition:
  // 	There are less than 6 courses in the course list already.
  // Postcondition:
  // 	The given course is added to the list.
  courses[numCourses] = aCourse;
  numCourses++;
} // end addCourse

void Student::removeCourse(Course *aCourse) {
  // preconditions: the student has at least one course to remove
  if (numCourses == 0)
    std::cout << "The student is not currently enrolled in any courses.";

  for (int i = 0; i < numCourses; i++){             // iterate through students courses
    if (courses[i] == aCourse) {                    // if the course matches the random course we are deleting
      for (int j = i; j < numCourses - 1; j++) {    // move the next course into that courses spot and repeat
      courses[j] = courses[j+1];
      }
      numCourses--;                                 // decrease the number of courses student is enrolled in
      courses[numCourses] = nullptr;                // make final pointer the null pointer
    }
  }
} // end removeCourse


bool Student::isEnrolled(Course *theCourse) const {
  for (int i = 0; i < numCourses; i++)
  {
    if (courses[i] == theCourse)
      return true;
  }
  return false;
} // end isEnrolled

void Student::printInfo(void) const {
  std::cout << "Name: " << name << std::endl;
  std::cout << "Graduation Date: " << gradDate << std::endl;
  std::cout << std::endl;
} // end printInfo

void Student::printCourses(void) const {
  for (int i = 0; i < numCourses; i++)
    std::cout << "Course " << (i+1) << ": " << courses[i]->getDescription() << std::endl;
  std::cout << std::endl;
} //end printCourses

LinkedSet<Course*> Student::getSchedule(void) const {
  LinkedSet<Course*> schedule;
  for (int i = 0; i < numCourses; i++)
    schedule.add(courses[i]);
  return schedule;
}

void Student::setGradDate(int year) {
  gradDate = year;
} // end SetGradDate

std::string Student::getName() const {
  return name;
} // end SetGradDate

