/***********************************************************************
 * Header:
 *    NODE.H
 * Summary:
 *    declaration of Node class.
 * Author
 *    Sam Haymond, Emily Peck
 ************************************************************************/
#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <cassert>

using namespace std;


template <class T>
class Node
{
public:
   Node() : data(T()), pPrev(NULL), pNext(NULL) {}
   Node(T t) { data = t; pNext = NULL; pPrev = NULL; }
   
   T data;
   Node <T> * pPrev;
   Node <T> * pNext;
};

#endif 
