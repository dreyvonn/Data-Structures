/***********************************************************************
 * Implementation:
 *    NOW SERVING
 * Summary:
 *    This will contain the implementation for nowServing() as well as any
 *    other function or class implementations you may need
 * Author
 *    Sam Haymond, Emily Peck
 **********************************************************************/

#include <iostream>     // for ISTREAM, OSTREAM, CIN, and COUT
#include <string>       // for STRING
#include <cassert>      // for ASSERT
#include "nowServing.h" // for nowServing() prototype
#include "deque.h"      // for DEQUE
#include "student.h"
using namespace std;

void display(Student s, deque <Student> d);

/************************************************
 * NOW SERVING
 * The interactive function allowing the user to
 * handle help requests in the Linux lab
 ***********************************************/
void nowServing()
{
   // instructions
   cout << "Every prompt is one minute.  The following input is accepted:\n";
   cout << "\t<class> <name> <#minutes>    : a normal help request\n";
   cout << "\t!! <class> <name> <#minutes> : an emergency help request\n";
   cout << "\tnone                         : no new request this minute\n";
   cout << "\tfinished                     : end simulation\n";

   deque <Student> d;
   Student s;
   Student s2;
   string name;
   string course;
   int time = 0;
   int serverTime = 0;
   bool finish = false;

   // your code here
   while(!finish)
   {
      cout << "<" << serverTime << "> ";
      cin >> course;

      if (course == "finished")
         finish = true;
      else if (course == "none")
      {
         if (s.getTime() != 0)
         {
            display(s, d);
         }

         if (s.getTime() == 0 && !d.empty())
         {
            s.setCourse(d.front().getCourse());
            s.setName(d.front().getName());
            s.setTime(d.front().getTime());
            s.setEmergency(d.front().isEmergency());

            d.pop_front();
            display(s, d);
         }

      }
      else if (course == "!!")
      {
         cin >> course;
         cin >> name;
         cin >> time;

         if (s.getTime() > 0)
         {
            s2.setCourse(course);
            s2.setName(name);
            s2.setTime(time);
            s2.setEmergency(true);
            d.push_front(s2);
         }
         else
         {
            s.setCourse(course);
            s.setName(name);
            s.setTime(time);
            s.setEmergency(true);
         }

         if (s.getTime() == 0 && !d.empty())
         {
            s.setCourse(d.front().getCourse());
            s.setName(d.front().getName());
            s.setTime(d.front().getTime());
            s.setEmergency(d.front().isEmergency());

            d.pop_front();
         }

         display(s, d);
      }
      else
      {
         cin >> name;
         cin >> time;
         if (s.getTime() > 0)
         {
            s2.setCourse(course);
            s2.setName(name);
            s2.setTime(time);
            s2.setEmergency(false);
            d.push_back(s2);
         }
         else
         {
            s.setCourse(course);
            s.setName(name);
            s.setTime(time);
            s.setEmergency(false);
         }

         if (s.getTime() == 0 && !d.empty())
         {
            s.setCourse(d.front().getCourse());
            s.setName(d.front().getName());
            s.setTime(d.front().getTime());
            s.setEmergency(false);

            d.pop_front();
         }

         display(s, d);
      }

      serverTime++;
      s.setTime(s.getTime() - 1);
   }

   // end
   cout << "End of simulation\n";
}

/************************************************
 * DISPLAY
 *displays the correct format for now serving
 ***********************************************/
void display(Student s, deque <Student> d)
{
   if (!s.isEmergency())
   {
      cout << "\tCurrently serving " 
           << s.getName()  
           << " for class "
           << s.getCourse()
           << ". Time left: "
           << s.getTime()
           << endl;
   }

   else 
   {
      cout << "\tEmergency for " 
        << s.getName()  
        << " for class "
        << s.getCourse()
        << ". Time left: "
        << s.getTime()
        << endl;
   }
}