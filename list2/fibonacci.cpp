/***********************************************************************
 * Implementation:
 *    FIBONACCI
 * Summary:
 *    This will contain the implementation for fibonacci() as well as any
 *    other function or class implementations you may need
 *
 *    There is a lot of extra code here that we were working with becuase 
 *    we were not able to finish the project. 
 * Author
 *    Sam Haymond Emily Peck
 **********************************************************************/

#include <iostream>
#include "fibonacci.h"   // for fibonacci() prototype
#include "list.h"        // for LIST
#include "wholeNumber.h"
using namespace std;

void display(int number);
void displayNum(int number);

/************************************************
 * FIBONACCI
 * The interactive function allowing the user to
 * display Fibonacci numbers
 **********************************************/
void fibonacci()
{
   // show the first serveral Fibonacci numbers
   int number;
   cout << "How many Fibonacci numbers would you like to see? ";
   cin  >> number;

   // your code to display the first <number> Fibonacci numbers
   display(number);

   // prompt for a single large Fibonacci
   cout << "Which Fibonacci number would you like to display? ";
   cin  >> number;

   // your code to display the <number>th Fibonacci number
   displayNum(number);


}

void displayNum(int number)
{
   WholeNumber first(0);
   WholeNumber second(0);
   WholeNumber sum(0);

   for (int i = 1; i <= number; ++i)
   {
      if (i == 1 || i == 2)
      {
         first.setList(1); 
         second.setList(1);
      }

      else if (i == 3)
      {
         sum.setList(2);
         second = sum;
      }

      else 
      {       
         first += second;
         sum = first; 
         first = second; 
         second = sum; 
      }
   }
   cout << "\t";
   sum.display();
   cout << endl;
}

void display(int number)
{
   WholeNumber first(0);
   WholeNumber second(0);
   WholeNumber sum(0);

   for (int i = 1; i <= number; ++i)
   {
      if (i == 1 || i == 2)
      {
         cout << "\t" << 1 << endl;
         first.setList(1); 
         second.setList(1);
      }

      else if (i == 3)
      {
         sum.setList(2);
         cout << "\t";
         sum.display();
         cout << endl;
         second = sum;
      }

      else 
      {       
         first += second;
         sum = first; 
         cout << "\t";
         sum.display();
         cout << endl;
         first = second; 
         second = sum; 
      }
   }
}
