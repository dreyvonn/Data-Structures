#include <iostream>
#include "bnode.h"

using namespace std;

/***********************************************
 * COPY
 * Copy the items in the list to a new one.
 **********************************************/
template <class T>
BNode <T> * copy(BNode <T> * pSource) throw (const char *)
{
   BNode <T> * pDestination = new BNode <T> (pSource->data);
   BNode <T> * pSrc;
   BNode <T> * pDes = pDestination;

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
BNode <T> * insert(BNode <T> * pBNode, const T & t, bool after = false)
{
   BNode <T> * pNew = new BNode <T> (t);
   
   if (pBNode != NULL && after == false)
   {
      pNew->pNext = pBNode;
      pNew->pPrev = pBNode->pPrev;
      pBNode->pPrev = pNew;

      if (pNew->pPrev)
      {
         pNew->pPrev->pNext = pNew;
      }
   }

   if (pBNode != NULL && after == true)
   {
      pNew->pPrev = pBNode;
      pNew->pNext = pBNode->pNext;
      pBNode->pNext = pNew;

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
BNode <T> * find(BNode <T> * pHead, const T & t)
{
   BNode <T> * p;
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
void freeData(BNode <T> * &pHead)
{
   BNode <T> * pDelete;
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
BNode <T> * remove(BNode <T> * pRemove)
{
   BNode <T> * pReturn;

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
ostream & operator << (ostream & out, BNode <T> * pCurrent)
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
