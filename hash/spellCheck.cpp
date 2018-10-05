/***********************************************************************
 * Module:
 *    Assignment 12, Spell Check
 *    Brother Helfrich, CS 235
 * Author:
 *    Sam Haymond, Emily Peck, Emily Barrera
 * Summary:
 *    This program will implement the spellCheck() function
 ************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include "spellCheck.h"
#include "hash.h"
#include <cassert>

using namespace std;

/****************************************
 * SHASH
 * Derived from the Hash class, data type
 * string
 ****************************************/
class SHash : public Hash <string>
{
public:
   SHash(int numBuckets)    throw (const char *) : Hash <string> (numBuckets) {}
   SHash(const SHash & rhs) throw (const char *) : Hash <string> (rhs)        {}

   // hash function for strings
   int hash(const string & value) const
   {
      int sum = 0;
      for (int i = 0; i < value.length(); i++)
      {
         sum += int(value[i]);
      }  

      int index = sum % capacity();
      assert(0 <= index && index < capacity());

      return index;
   }
};

/*****************************************
 * SPELL CHECK
 * Prompt the user for a file to spell-check
 ****************************************/
void spellCheck()
{
   //read in the dictionary to the hash
   string temp;
   SHash h(500);

   ifstream fin("/home/cs235/week12/dictionary.txt");
   if (fin.fail())
      return;

   while (fin >> temp)
   {
      h.insert(temp);
   }

   fin.close();

   //prompt user for filename
   string filename;
   cout << "What file do you want to check? ";
   cin >> filename;

   ifstream fin2(filename.c_str());

   if (fin2.fail())
   {
      return;
   }

   string temp2;
   string misspelled[256];
   int count = 0;

   while (fin2 >> temp2)
   {
      string temp3 = temp2;

      //check for lowercase exceptions
      temp3[0] = tolower(temp2[0]);

      if (!h.find(temp3))
      {
         misspelled[count] = temp2;
         count++;
      }
   }

   fin2.close();

   if (misspelled[0] != "")
   {
      cout << "Misspelled: ";
      for (int i = 0; i < count; ++i)
      {
         if (i == count -1)
         {
            cout << misspelled[i] << endl;
         }
         else 
            cout << misspelled[i] << ", ";
      }
   }
   else 
      cout << "File contains no spelling errors\n";
}
