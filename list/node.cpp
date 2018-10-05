#include <iostream>
#include "node.h"

using namespace std;

/***********************************************
 * COPY
 * Copy the items in the list to a new one.
 **********************************************/
template <class T>
Node <T> * copy(Node <T> * pSource) throw (const char *)
{
   Node <T> * pDestination = new Node <T> (pSource->data);
   Node <T> * pSrc;
   Node <T> * pDes = pDestination;

   for (pSrc = pSource->pNext; pSrc; pSrc = pSrc->pNext)
   {
      cerr << "pSrc data " << pSrc->data << endl;
      pDes = insert(pDes, pSrc->data, true);
   }

   return pDestination;
}
/***********************************************
 * INSERT
 * Insert items into list
 **********************************************/
template <class T>
Node <T> * insert(Node <T> * pNode, const T & t, bool after = false)
{
   Node <T> * pNew = new Node <T> (t);
   
   if (pNode != NULL && after == false)
   {
      pNew->pNext = pNode;
      pNew->pPrev = pNode->pPrev;
      pNode->pPrev = pNew;

      if (pNew->pPrev)
      {
         pNew->pPrev->pNext = pNew;
      }
   }

   if (pNode != NULL && after == true)
   {
      pNew->pPrev = pNode;
      pNew->pNext = pNode->pNext;
      pNode->pNext = pNew;

      if (pNew->pNext)
      {
         pNew->pNext->pPrev = pNew;
      }
   }

   return pNew;
}

/***********************************************
 * FIND
 * Find items in list.
 **********************************************/
template <class T>
Node <T> * find(Node <T> * pHead, const T & t)
{
   Node <T> * p;
   for (p = pHead; p; p = p->pNext)
   {
      if (p->data == t)
         return p;
   }
   
   return NULL;
}

/**********************************************
 * FREE DATA
 * Free the data
 **********************************************/
template <class T>
void freeData(Node <T> * &pHead)
{
   Node <T> * pDelete;
   while (pHead != NULL)
   {
      pDelete = pHead; 
      pHead = pHead->pNext;
      delete pDelete;
      pDelete = NULL;
   }
}
      
/***********************************************
 * REMOVE
 * Remove items from the list.
 **********************************************/
 template <class T>
Node <T> * remove(Node <T> * pRemove)
{
   Node <T> * pReturn;

   if (pRemove == NULL)
      return pReturn;

   if (pRemove->pPrev)
      pRemove->pPrev->pNext = pRemove->pNext;

   if (pRemove->pNext)
      pRemove->pNext->pPrev = pRemove->pPrev;

   if (pRemove->pPrev)
      pReturn = pRemove->pPrev;
   else
      pReturn = pRemove->pNext;

   delete pRemove;

   return pReturn;
}

/***********************************************
 * EXTRACTION OPERATOR
 **********************************************/
template <class T>
ostream & operator << (ostream & out, Node <T> * pCurrent)
{
   while (pCurrent)
   {
      if (pCurrent->pNext)
         cout << pCurrent->data << ", ";
         
      else 
         cout << pCurrent->data; 
   
      pCurrent = pCurrent->pNext;
   }
   return out;
}
