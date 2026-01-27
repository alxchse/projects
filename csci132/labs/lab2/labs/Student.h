// File: student.h
// Description: Specification for the Student class
// Author: K. Walsh
// Class: CSCI 132
// Date: 12 July 2020

#ifndef STUDENT_H_
#define STUDENT_H_

#include "LinkedSet.h"
#include <string>

class Course; // forward declaration of type Course

// A Student object holds info about a single student and the courses
// they are enrolled in.
class Student
{

public:

  // Adds a new course to the Student's schedule.
  // Precondition:
  // 	There are less than 6 courses in the course list already.
  // Postcondition:
  // 	The given course is added to the list.
  void addCourse(Course *course);

  // TODO: invent a way to remove courses.

  // Checks if a course is in the Student's schedule.
  // Returns: true if the course is already in the student's schedule.
  bool isEnrolled(Course *course) const;
  
  // Prints the Student's list of courses to standard output, one course per
  // line, with one blank line at the end.
  void printCourses(void) const;
 
  // Prints the Student's name and graduation date to standard output, each on a
  // separate line, with one blank line at the end.
  void printInfo(void) const;
 
  // Changes the Student's graduation.
  // Postcondition:
  //   The Student's graduation year is set to the given year.
  void setGradDate(int year);

  // Gets the Student's name.
  std::string getName() const;

  // Gets the Student's course schedule.
  LinkedSet<Course*> getSchedule() const;
 
  // Default constructor.
  // Postcondition:
  //	Initializes the Student's name to "Jane Doe".
  //	Initializes the Student's graduation date to 0,
  //	Initializes the Student's course list to be empty.
  Student();
 
  // Constructor with name and year.
  // Precondition:
  //   name is not empty
  //   year is positive
  // Postcondition:
  //	 Initializes the Student's name to the given name.
  //	 Initializes the Student's graduation date to the given year.
  //	 Initializes the Student's number list to be empty.
  Student(std::string name, int year);
    
private:

  std::string name;     // Name of the student, or "Jane Doe" by default.
  int gradDate;         // Graduation date, or zero if no date has been set.
  Course *courses[6];   // List of courses the student is enrolled in.
  int numCourses;       // Number of courses student is enrolled in.
};

#endif
