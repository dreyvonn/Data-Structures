//
//  bnode.hpp
//  xcode wk08
//
//  Created by Emily Barrera Bravo, Sam Haymond, and
//  Emily Peck on 10/30/17.
//  Copyright © 2017 Emily Barrera Bravo. All rights reserved.
//

#ifndef bnode_h
#define bnode_h

#include <stdio.h>
#include <iostream>

using namespace std;


template <class T>
class BNode
{
public:
    //DEFALUT CONSTRUCTOR
    BNode() { pParent = pLeft = pRight = NULL;}
    //NON-DEFAULT CONSTRUCTOR
    BNode( T t) { pParent = pLeft = pRight = NULL; data = t;}
    T data;
    BNode *pLeft;
    BNode *pRight;
    BNode *pParent;
    
};

#endif /* bnode_h */


template <class T>
void addLeft (BNode <T> * pNode, const T & t) throw (const char *)
{
    BNode <T> * pAdd = new BNode<T>(t);
    pAdd->pParent = pNode;
    pNode->pLeft = pAdd;
    
  
}

template <class T>
void addRight (BNode <T> * pNode, const T & t) throw (const char *)
{
   
    BNode <T> * pAdd = new BNode<T>(t);
    pAdd->pParent = pNode;
    pNode->pRight = pAdd;
    
}

template <class T>
void addRight (BNode <T> * pNode, BNode<T> * pAdd)
{
    if (pAdd != NULL)
    {
        pAdd->pParent = pNode;
    }
    pNode->pRight = pAdd;
}

template <class T>
void addLeft (BNode <T> * pNode, BNode<T> * pAdd)
{
    if (pAdd != NULL)
    {
        pAdd->pParent = pNode;
    }
    pNode->pLeft = pAdd;
  
}

template <class T>
BNode<T> * copyBTree(const BNode<T> * pSrc) throw (const char *)
{
    if (pSrc == NULL)
    {
        return;
    }
    BNode<T> * destination = new BNode<T>(pSrc->data);
    
    destination->pLeft = copyBTree(pSrc->pLeft);
    if (destination->pLeft != NULL)
    {
        destination->pLeft->pParent = destination;
    }
    destination->pRight = copyBTree(pSrc->pRight);
    if (destination->pRight != NULL)
    {
        destination->pRight->pParent = destination;
    }
    return destination;
}

template <class T>
void deleteBTree(BNode <T> * & pNode)
{
    if (pNode == NULL)
    {
        return;
    }
    deleteBTree(pNode->pLeft);
    deleteBTree(pNode->pRight);
    delete pNode;
}

template <class T>
ostream & operator << (ostream & out, const BNode <T> * pHead)
{
   if (pHead == NULL)
      return out;

   out << pHead->pLeft;
   out << pHead->data << " ";
   out << pHead->pRight;

   return out;
}

template <class T>
int sizeBTree(const BNode <T> * pRoot)
{
    if (pRoot == NULL)
    {
        return 0;
    }
    else
    {
        return sizeBTree(pRoot->pLeft) + 1 + sizeBTree(pRoot->pRight);
    }
}
