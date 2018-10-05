/***********************************************************************
* Program:
*    Assignment 01, Go Fish
*    Brother Helfrich, CS 235
* Author:
*    <your names here>
* Summary: 
*    This is all the functions necessary to play Go Fish!
*
*    Estimated:  0.0 hrs   
*    Actual:     0.0 hrs
*      Please describe briefly what was the most difficult part.
************************************************************************/

#include <iostream>
#include <fstream>
#include "set.h"
#include "card.h"
#include "goFish.h"
#include <string>
using namespace std;
using namespace custom;

/**********************************************************************
 * GO FISH
 * The function which starts it all
 ***********************************************************************/
void goFish()
{
   set <string> s;
   string temp;
   string choice;
   int count = 0;
   set <string> :: iterator itEmpty;
   set <string> :: iterator itFind;

   ifstream fin("/home/cs235/week05/hand.txt");

   if (fin.fail())
      return;

   while (fin >> temp)
   {
      s.insert(temp);
   }

   fin.close();

   cout << "We will play 5 rounds of Go Fish.  Guess the card in the hand\n";
   
   for (int i = 1; i <= 5; ++i)
   {
      cout << "round " << i << ": ";
      cin >> choice;
      itFind = s.find(choice);
      itEmpty = s.end();
      if (itEmpty != itFind)
      {
         cout << "\tYou got a match!\n";
         s.erase(itFind);
         count++;
      }
      else 
         cout << "\tGo Fish!\n";
   }   

   cout << "You have "
        << count 
        << " matches!\n";
   cout << "The remaining cards: ";

   set <string> :: iterator it;
   for (it = s.begin(); it != s.end(); ++it)
   {
      if (it != s.rbegin())
         cout << *it << ", ";
      else
         cout << *it << endl;;
   }
   return ;
}
