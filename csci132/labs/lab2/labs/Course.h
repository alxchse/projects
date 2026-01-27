// File: Course.h
// Description: Specification for the Course class
// Author: K. Walsh
// Class: CSCI 132
// Date: 25 July 2020

#ifndef COURSE_H_
#define COURSE_H_

#include "LinkedSet.h"
#include <string>

class Student; // forward declaration of type Student

// A Course object holds info about a single course, including
// a roster of all students enrolled in the course.
class Course
{
public:

  // Enroll a Student in this Course, so long as there is room enough in the
  // course. This method also ensures this Course is listed on the Student's
  // course schedule.
  // returns: true if the student was able to enroll,
  //          false if the course was full.
  bool enroll(Student *s);
  
  // Prints a roster of all students in this Course.
  void printRoster() const;
 
  // Gets a description of this course, in the format "DEPT NUM: TITLE"
  std::string getDescription() const;

  // Gets the department name of this Course.
  std::string getDepartment() const;

  // Gets the course number for this Course.
  int getNumber() const;

  // Gets the course title for this Course.
  std::string getTitle() const;

  // Gets the roster of students enrolled in this Course.
  // Note: a copy of the roster is returned, so any changes
  // made to the returned set do not affect this Course.
  LinkedSet<Student*> getRoster() const;

  // Constructor with two parameters
  // Precondition:
  //   code has the format "DEPT NUM", where DEPT is a four-character
  //     department name, and NUM is a three-digit course number.
  //   maxEnrollment is not negative
  // Postcondition:
  //	 Initializes the Course's department to the given DEPT
  //	 Initializes the Course's course number to the given NUM
  //	 Initializes the Course's title to the given title
  //	 Initializes the Course's max enrollment to the given number
  Course(std::string code, std::string title, int maxEnrollment);
    
private:

  std::string dept;  // e.g. "LATN"
  int num;           // e.g. 101
  std::string title; // e.g. "Introduction to Latin"
  int maxEnrollment; // maximum number of students allowed to enroll
  
  LinkedSet<Student *> roster; // the set of all enrolled students
};

#endif
