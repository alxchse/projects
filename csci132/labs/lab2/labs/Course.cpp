// File: Course.cpp
// Description: Implementation for the Course class
// Author: K. Walsh
// Class: CSCI 132
// Date: 25 July 2020

#include "Course.h"
#include "Student.h"
#include <iostream>
#include <cassert>

using namespace std;

bool Course::enroll(Student *s)
{
  if (roster.size() < maxEnrollment) {
    roster.add(s);
    s->addCourse(this);
    return true;
  } else {
    return false;
  }
}

void Course::printRoster() const
{
  int n = roster.size();
  cout << getDescription() << " (" << n << " enrolled)\n";
  for (int i = 0; i < n; i++)
    cout << (i+1) << ". " << roster.get(i)->getName() << "\n";
}

LinkedSet<Student*> Course::getRoster(void) const {
  return roster;
}

string Course::getDescription() const
{
  return dept + " " + to_string(num) + ": " + title;
}

string Course::getDepartment() const
{
  return dept;
}

int Course::getNumber() const
{
  return num;
}

string Course::getTitle() const
{
  return title;
}

Course::Course(string code, string title, int maxEnrollment)
{
  assert(maxEnrollment >= 0);

  this->dept = code.substr(0, 4);      // the "CLAS" part of "CLAS 101"
  this->num = stoi(code.substr(5, 8));  // the 101 part of "CLAS 101"
  this->title = title;
  this->maxEnrollment = maxEnrollment;
}

