/***********************************************************************
 * Module:
 *    Week 02, Stack
 *    Brother Helfrich, CS 235
 * Author:
 *    Sam Haymond, Emily Peck
 * Summary:
 *    This program will implement the testInfixToPostfix()
 *    and testInfixToAssembly() functions
 ************************************************************************/

#include <iostream>    // for ISTREAM and COUT
#include <string>      // for STRING
#include <cassert>     // for ASSERT
#include "stack.h"     // for STACK
#include "token.h"
#include <ctype.h>

using namespace std;
using namespace custom;

/*****************************************************
 * CONVERT INFIX TO POSTFIX
 * Convert infix equation "5 + 2" into postifx "5 2 +"
 *****************************************************/
string convertInfixToPostfix(const string & infix)
{
   string postfix;
   stack <char> s;
   int type = 0;
   Token t;
   Token t2;

   for (int i = 0; i < infix.size(); ++i)
   {
      t.setToken(infix[i]);

      switch (t.getType())
      {
         case 1:
         case 2:
         case 3:
            if (!s.empty())
            {
               t2.setToken(s.top());
            }
            while (!s.empty() && t.getType() <= t2.getType())
            {
               postfix += s.top();
               postfix += " ";
               s.pop();
            }
            s.push(infix[i]);
         break;
         case 0:
            s.push(infix[i]);
         break;
         case 5:
            while (s.top() != '(')
            {
               postfix += s.top();
               s.pop();
            }
            postfix += " ";
            s.pop();
         break;
         case 6:
            postfix += infix[i];

            if (!isalnum(infix[i + 1]) && infix[i + 1] != '.')
            {
               postfix += " ";
            }
         break;
         case 7:
         break;
         case 8:
            postfix += infix[i];
         break;
         default:
            cerr << "ERROR" << endl;
      }
   }
   while (!s.empty())
   {
      postfix += s.top();
      s.pop();
      if (!s.empty())
      {
         postfix += " ";
         cerr << "top " << s.top() << endl;
      }
   }

   return postfix;
}

/*****************************************************
 * TEST INFIX TO POSTFIX
 * Prompt the user for infix text and display the
 * equivalent postfix expression
 *****************************************************/
void testInfixToPostfix()
{
   string input;
   cout << "Enter an infix equation.  Type \"quit\" when done.\n";
   
   do
   {
      // handle errors
      if (cin.fail())
      {
         cin.clear();
         cin.ignore(256, '\n');
      }
      
      // prompt for infix
      cout << "infix > ";
      getline(cin, input);

      // generate postfix
      if (input != "quit")
      {
         string postfix = convertInfixToPostfix(input);
         cout << "\tpostfix:  " << postfix << endl << endl;
      }
   }
   while (input != "quit");
}

/**********************************************
 * CONVERT POSTFIX TO ASSEMBLY
 * Convert postfix "5 2 +" to assembly:
 *     LOAD 5
 *     ADD 2
 *     STORE VALUE1
 **********************************************/
string convertPostfixToAssembly(const string & postfix)
{
   string assembly;

   return assembly;
}

/*****************************************************
 * TEST INFIX TO ASSEMBLY
 * Prompt the user for infix text and display the
 * resulting assembly instructions
 *****************************************************/
void testInfixToAssembly()
{
   string input;
   cout << "Enter an infix equation.  Type \"quit\" when done.\n";

   do
   {
      // handle errors
      if (cin.fail())
      {
         cin.clear();
         cin.ignore(256, '\n');
      }
      
      // prompt for infix
      cout << "infix > ";
      getline(cin, input);
      
      // generate postfix
      if (input != "quit")
      {
         string postfix = convertInfixToPostfix(input);
         cout << convertPostfixToAssembly(postfix);
      }
   }
   while (input != "quit");
      
}
