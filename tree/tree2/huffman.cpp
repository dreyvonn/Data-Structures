/***********************************************************************
 * Module:
 *    Week 08, Huffman
 *    Brother Helfrich, CS 235
 * Author:
 *    Sam Haymond, Emily Peck, Emily Barrera
 * Summary:
 *    This program will implement the huffman() function
 ************************************************************************/

#include <iostream>        // for CIN and COUT
#include <fstream>         // for IFSTREAM
#include <cassert>         // for ASSERT
#include <string>          // for STRING: binary representation of codes
#include "bnode.h"         // for BINARY_NODE class definition
#include "list.h"        // for list container
#include "pair.h"          // for PAIR container
#include "huffman.h"       // for HUFFMAN() prototype
#include <string>
#include <vector>
#include <queue>

using std::cout;
using std::cin;
using std::ifstream;
using std::endl;
using std::string;
using std::bad_alloc;
using namespace custom;

void insertSort(list <BNode<pairo<string, double> >* > data,
                pairo <string, double> p);

void display(BNode<pairo<string,double> > * parent);
/*******************************************
 * HUFFMAN
 * Driver program to exercise the huffman generation code
 *******************************************/
void huffman(const string & fileName)
{
   vector <BNode<pairo<string, double> >* > data;
   pairo <string, double> p;
   int i = 0;

   //ifstream fin(fileName.c_str());
   ifstream fin(fileName.c_str());
   if (fin.fail())
      return;

   while (fin >> p)
   {
      BNode <pairo<string, double> > * pNode;
      try
      {
         pNode = new BNode<pairo<string, double> >(p);
      }

      catch (std::bad_alloc)
      {
         throw "ERROR";
      }
       
       data.push_back(pNode);
        i++;
   }

   fin.close();
    
    
    vector <BNode<pairo<string, double> >* > temp;
    BNode<pairo<string,double> > * small;
    BNode<pairo<string,double> > * smallest;
    int countParents = 2;
    
    while (data.size() > 1)
    {
        int i = 0;
        
        smallest = *data.begin();
        small = *data.begin();
        
        vector <BNode<pairo<string, double> >* > :: iterator itSmallest = data.begin();
        vector <BNode<pairo<string, double> >* > :: iterator itSmall = data.begin();
        
        for (vector <BNode<pairo<string, double> >* > :: iterator it = data.begin(); it != data.end(); it++)
        {
            if ((*it)->data.second < smallest->data.second)
            {
                smallest = *it;
                itSmallest = it;
                //cerr << "smallest " << *it << endl;
            }
        }

        BNode <pairo<string, double> > * copySmallest = new BNode<pairo<string, double> > (*smallest);

        if (*itSmall != NULL)
        {
            data.erase(itSmallest);
        }
        
        for (vector <BNode<pairo<string, double> >* > :: iterator it = data.begin(); it != data.end(); it++)
        {
            if ((*it)->data.second < small->data.second && *it != smallest)
            {
                small = *it;
                itSmall = it;
            }
            //cerr << "smallest " << *it << endl;
        }
        
        BNode <pairo<string, double> > * copySmall = new BNode<pairo<string, double> > (*small);
        
        BNode<pairo<string,double> > * parent = new BNode<pairo<string, double> >;
        parent->pLeft = copySmallest;
        parent->pRight = copySmall;
        copySmall->pParent = parent;
        copySmallest->pParent = parent;
        
        parent->data.second = copySmall->data.second + copySmallest->data.second;
        temp.push_back(copySmallest);
        temp.push_back(copySmall);
        
        if (*itSmall != NULL)
        {
            data.erase(itSmall);
        }
        
        data.push_back(parent);

        cerr << "size " << data.size() << endl;
    }
    
    temp.push_back(*data.begin());
    
    pairo <char, string> sam;
    
    display(data[0]);
    
    
   return;
}

void display(BNode<pairo<string,double> > * parent)
{
    if( parent == NULL)
        return;
    queue <BNode<pairo<string,double> > * > q;
    q.push(parent);
    
    while(!q.empty())
    {
        if (q.front()->pLeft != NULL)
            q.push(q.front()->pLeft);
        
        if (q.front()->pRight != NULL)
            q.push(q.front()->pRight);
        cout << q.front()->data;
        q.pop();
    }

   

   /*if (parent == NULL)
      return;

   display(parent->pLeft);
   cout << parent->data << " ";
   display(parent->pRight);*/
    
}
