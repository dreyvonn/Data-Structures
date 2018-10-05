/***********************************************************************
 * Header:
 *    BNode.H
 * Summary:
 *    declaration of BNode class.
 * Author
 *    Sam Haymond, Emily Peck
 ************************************************************************/
#ifndef BNODE_H
#define BNODE_H

#include <iostream>
#include <cassert>

using namespace std;


template <class T>
class BNode
{
public:
   BNode() : data(T()), pPrev(NULL), pNext(NULL) {}
   BNode(T t);
   
   T data;
   BNode <T> * pPrev;
   BNode <T> * pNext;
};

template <class T>
BNode <T> :: BNode(T t)
{   
   data = t;
   pNext = NULL;
   pPrev = NULL;
}

#endif 
