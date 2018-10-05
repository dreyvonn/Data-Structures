/***********************************************************************
 * Implementation:
 *    STUDENT
 * Summary:
 *    This is the header for our student class, it contains all 
 *    methods and variables that are needed for this object.
 * Author
 *    Sam Haymond, Emily Peck
 **********************************************************************/
#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include "deque.h"

using namespace std;
using namespace custom;

class Student
{
private:
   string name;
   string course;
   int time;
   bool emergency;
public:
   Student() : name(""), course(""), time(0), emergency(false) {}
   ~Student() {}

   string getName() { return name; }
   string getCourse() { return course; }
   int getTime() { return time; }
   bool isEmergency() { return emergency; }

   void setName(string name) { this->name = name; }
   void setCourse(string course) { this->course = course; }
   void setTime(int time) { this->time = time; }
   void setEmergency(bool emergency) { this->emergency = emergency; }
};

#endif