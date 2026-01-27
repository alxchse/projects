// Lab 3 code for playing with pointers and memory management
// Author: K. Walsh
// Date: July 25, 2020
// Modified by Alexandra Chase
// 13 February 2023

#include "Student.h"
#include "Course.h"
#include "ArrayBag.h"
#include "LinkedSet.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void enrollRandomCourses(LinkedSet<Course *> &courses, Student *stu, int count) {
  for (int i = 0; i < count; i++)
  {
    Course *c = courses.pickRandom();
    while (stu->isEnrolled(c))
    {
      c = courses.pickRandom();
    }
    cout << "Enrolling " << stu->getName() << " in " << c->getDescription() << "\n";
    c->enroll(stu);
  }
}

int main(void)
{
  // Create some students records
  Student *a = new Student("Salif Kieta", 2024);
  Student *b = new Student("Bojana Novakovic", 2022);
  Student *c = new Student("Judith Gutierrez", 2023);

  // Create a list of available courses
  LinkedSet<Course*> courses;
  courses.add(new Course("CSCI 131", "Techniques of Programming", 32));
  courses.add(new Course("MUSC 242", "Coding Music", 19));
  courses.add(new Course("CLAS 151", "History of Ancient Rome", 16));
  courses.add(new Course("THEA 229", "Virtual Realities", 16));
  courses.add(new Course("CSCI 328", "Coding Music", 16));
  courses.add(new Course("VAST 105", "Digital Arts Studio 1", 16));

  // Enroll students in some random courses
  enrollRandomCourses(courses, a, 5);
  enrollRandomCourses(courses, b, 5);
  enrollRandomCourses(courses, c, 5);

  // Print the student schedules
  cout << "==== Schedules for all students ====\n";
  a->printInfo();
  a->printCourses();
  b->printInfo();
  b->printCourses();
  c->printInfo();
  c->printCourses();

  // Print the course rosters
  // Note: ArrayBag doesn't have an easy way to enumerate the items, so
  // we allocate a new simple array here and fill it with the courses.
  cout << "==== Rosters for all courses ====\n";
  cout << "READY!\n";
  int n = (int)courses.size();
  for (int i = 0; i < n; i++) {
    courses.get(i)->printRoster();
  }
  cout << "\n";

  // Pick a random course from Judith's schedule, and print the name 
  // of a random student from that course.

  Course*coursePtr = c->getSchedule().pickRandom();
  Student*randStudent = coursePtr->getRoster().pickRandom();
  std::string friendName = randStudent->getName();
  cout << "Judith made a new friend! Their name is " << friendName << ". \n";
  cout << "\n";


  // Pick a random course to be cancelled. Delete that course. Be sure to
  // also remove it from the courses list, and to remove it from any student's
  // schedules too. Once your code is finished, there should be no dangling
  // references to the now-deleted course.

  Course*randCourse = courses.pickRandom();
  std::string deletedCourseTitle = randCourse->getTitle();

    cout << "Oh no! The course " << deletedCourseTitle << " needs to be removed. \n";
    a->removeCourse(randCourse);
    b->removeCourse(randCourse);
    c->removeCourse(randCourse);

  // Print the revised student schedules
  cout << "==== Revised schedules for all students ====\n";
    a->printInfo();
    a->printCourses();
    b->printInfo();
    b->printCourses();
    c->printInfo();
    c->printCourses();

  // Pick one random course from each student, and add it to a Bag. Print
  // the vote counts for each course.

ArrayBag<Course*> votes;
Course* randA = a->getSchedule().pickRandom();
Course* randB = b->getSchedule().pickRandom();
Course* randC = c->getSchedule().pickRandom();

votes.add(randA);
votes.add(randB);
votes.add(randC);

cout << "==== Tallies for each course ====\n";

cout << randA->getDepartment() << " " << randA->getNumber() << ": " << randA->getTitle() << " won " << votes.getFrequencyOf(randA) << " votes! \n";
cout << randB->getDepartment() << " " << randB->getNumber() << ": " << randB->getTitle() << " won " << votes.getFrequencyOf(randB) << " votes! \n";
cout << randC->getDepartment() << " " << randC->getNumber() << ": " << randC->getTitle() << " won " << votes.getFrequencyOf(randC) << " votes! \n";

}