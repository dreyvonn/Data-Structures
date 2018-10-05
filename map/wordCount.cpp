/***********************************************************************
 * Module:
 *    Week 10, WORD COUNT
 *    Brother Helfrich, CS 235
 * Author:
 *    Sam Haymond, Emily Barrera, Emily Peck 
 * Summary:
 *    This program will implement the wordCount() function
 ************************************************************************/

#include "map.h"       // for MAP
#include "wordCount.h" // for wordCount() prototype
#include <string>
#include <fstream>
#include <iostream>
using namespace std;
using namespace custom;

/*****************************************************
 * WORD COUNT
 * Prompt the user for a file to read, then prompt the
 * user for words to get the count from
 *****************************************************/
void wordCount()
{
   string filename; 
   string temp;
   int i = 0;
   map  <string, int> m;
   map  <string, int> :: iterator it2;
   Pair <string, int> p;

   cout << "What is the filename to be counted? ";
   cin >> filename;

   ifstream fin(filename.c_str());

   if (fin.fail())
      return;

   while (fin >> temp)
   {
      it2 = m.find(temp);
      if (it2 != m.end())
      {
         (*it2).second += 1;  
      }
      else 
      {
         Pair <string, int> p = *new Pair<string,int>();
         p.first = temp;
         p.second = 1;
         m.insert(p);
      }
   }
   
   fin.close();
   
   string word;
   bool done = false;
   int count = 0;
   map <string, int> :: iterator it;
   cout << "What word whose frequency is to be found. Type ! when done\n";
   while (!done)
   {
      cout << "> ";
      cin >> word;

      if (word == "!")
         done = true;

      else
      {
         it = m.find(word);

         if (it != m.end())
            cout << "\t" << word << " : " << (*it).second << endl;
         else
            cout <<"\t" << word << " : " << '0' << endl;
      }
   }

   
}
