/***********************************************************************
 * Header:
 *    WholeNumber
 * Summary:
 *    Has a list of ints broken up into nodes of 3. Has various operators
 *    overloaded for the user's convenience. 
 *
 * Author
 *    Sam Haymond, Emily Peck
 ************************************************************************/

#ifndef WHOLE_NUMBER
#define WHOLE_NUMBER

#include <iostream>
#include "list.h"
#include <iomanip>

using namespace custom;
using namespace std;

class WholeNumber
{
private:
   list <int> l;
public:
   WholeNumber() : l() {}
   WholeNumber(const WholeNumber & rhs);
   WholeNumber(int i);
   void display();
   void setList(int i);

   WholeNumber & operator =(const WholeNumber & rhs);
   WholeNumber & operator += (const WholeNumber & rhs);

};

/**************************************************
 * WholeNumber Copy Constructor
 * make a copy of a Wholenumber
 *************************************************/
WholeNumber :: WholeNumber(const WholeNumber & rhs)
{
   this->l = rhs.l;
}

/**************************************************
 * WholeNumber Non - Default Constructor
 * make a whole number with a set value
 *************************************************/
WholeNumber :: WholeNumber(int i)
{
   int temp = 0;
   while (i)
   {
      temp = i % 1000;
      l.push_front(temp);
      i -= temp;
      i *= 0.001;
   }
}

/**************************************************
 * WholeNumber: ASSIGNMENT
 * set one whole number equal to another
 *************************************************/
WholeNumber & WholeNumber :: operator = (const WholeNumber & rhs)
{
   this->l = rhs.l;

   return *this;
}

/**************************************************
 * WholeNumber: SETLIST
 * Allow the user to set the value of the wholnumber
 *************************************************/
void WholeNumber :: setList(int i)
{
   l.clear();
   int temp = 0;
   if (i == 0)
   {
      l.push_front(0);
   }
   while (i)
   {
      temp = i % 1000;
      l.push_front(temp);
      i -= temp;
      i *= 0.001;
   }
}

/**************************************************
 * WholeNumber: ADDONTO
 * Allow the user to add one wholenumber onto another
 ************************************************/
WholeNumber & WholeNumber :: operator += (const WholeNumber & rhs)
{
   list <int> :: reverse_iterator itRhs = rhs.l.rbegin();
   list <int> :: reverse_iterator it = l.rbegin();

   int i = 0;
   int carry = 0;

   while (it != l.rend() || itRhs != l.rend())
   {
      if (carry != 0 && it != l.rend())
      {
         *it += carry;
         carry = 0;
      }

      if (it != l.rend() && itRhs != l.rend())
         *it += *itRhs;

      else if (it == l.rend() && itRhs != rhs.l.rend())
      {
         l.push_front(*itRhs + carry);
         carry = 0;
      }

      else if (it != l.rend() && itRhs == rhs.l.rend())
      {
         *it += carry;
         carry = 0;
      }
      
      if (it != l.rend())
      {
         if (*it > 999)
         {
            carry = *it;
            i = carry % 1000;
            *it = i;
            carry -= i;
            carry *= 0.001;
         }
      }

      if (it != l.rend())
      {   
         it++;
      }
      if (itRhs != rhs.l.rend())
      {
         itRhs++;
      }
   }

   if (it == l.rend() && itRhs == rhs.l.rend() && carry != 0)
   {
      l.push_front(carry);
      carry = 0;
   }

   return *this;
}

/**************************************************
 * WholeNumber: DISPLAY
 * Display the wholenumber in a nice format
 *************************************************/
void WholeNumber::display()
{
   list <int> :: iterator it;

   for (it = l.begin(); it != l.end(); ++it)
   {
      if (it == l.begin() && it != l.rBegin())
         cout << *it << ",";
      else
      {
         if (it != l.rBegin())
            cout << setfill ('0') << setw(3) << *it << ",";
         else if (it == l.begin())
            cout << *it;
         else 
            cout << setfill ('0') << setw(3) << *it;
      }
      
   }
}

/*template <class T>
ostream & operator << (ostream & out, const WholeNumber & rhs)
{
   out.fill('0');
   list <int> :: iterator it;
   for (it = rhs.l.begin(); it != rhs.l.end(); ++it)
   {
      out << setw(3) << *it << ", \n";
   }
   return out;
}
*/
#endif
