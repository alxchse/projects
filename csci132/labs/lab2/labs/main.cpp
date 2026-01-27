// Lab 3 code for playing with pointers and memory management
// Author: K. Walsh
// Date: July 25, 2020

#include "Student.h"
#include "Course.h"
#include "ArrayBag.h"
#include "LinkedSet.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void enrollRandomCourses(ArrayBag<Course *> &courses, Student *stu, int count) {
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
  // TODO: change to LinkedSet
  ArrayBag<Course*> courses;
  courses.add(new Course("CSCI 131", "Techniques of Programming", 32));
  courses.add(new Course("MUSC 242", "Coding Music", 19));
  courses.add(new Course("CLAS 151", "History of Ancient Rome", 16));

  // TODO: Add the three courses described in the writeup after diagramming
  // memory.

  // Enroll students in some random courses
  // TODO: Update the number of courses for each student
  // after diagramming memory
  enrollRandomCourses(courses, a, 2);
  enrollRandomCourses(courses, b, 2);
  enrollRandomCourses(courses, c, 3);

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
  int n = (int)courses.getCurrentSize();
  Course** v = new Course*[n];
  courses.fillArray(v);
  for (int i = 0; i < n; i++)
    v[i]->printRoster();

  cout << "READY!\n";

  // TODO: Pick a random course from Judith's schedule, and print the name 
  // of a random student from that course.

  // TODO: Pick a random course to be cancelled. Delete that course. Be sure to
  // also remove it from the courses list, and to remove it from any student's
  // schedules too. Once your code is finished, there should be no dangling
  // references to the now-deleted course.

  // TODO: Print the revised student schedules
  // cout << "==== Revised schedules for all students ====\n";

  // TODO: Pick one random course from each student, and add it to a Bag. Print
  // the vote counts for each course.
  // cout << "==== Tallies for each course ====\n";

}
