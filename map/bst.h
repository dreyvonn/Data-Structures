/***********************************************************************
 * Header:
 *    BST
 * Summary:
 *    This class contains the notion of an BST: a bucket to hold
 *    data for the user. This is just a starting-point for more advanced
 *    constainers such as the BST, set, BST, BST, BST, and map
 *    which we will build later this semester.
 *
 *    This will contain the class definition of:
 *       BST             : similar to std::BST
 *       BST :: iterator : an iterator through the BST
 * Author
 *    Sam Haymond, Emily Peck, Emily Barrera
 ************************************************************************/

#ifndef BST_H
#define BST_H

#include <cassert>  // because I am paranoid
#include <cmath>

// a little helper macro to write debug code
#ifdef NDEBUG
#define Debug(statement)
#else
#define Debug(statement) statement
#endif // !NDEBUG

namespace custom
{
   template <class T> 
   class iterator;

   template <class T> 
   class iterator;

 
/************************************************
 * BST
 * A class that holds stuff
 ***********************************************/
template <class T>
class BST
{
public:
   // constructors and destructors
   BST() : numElements(0), root(NULL) {}
   BST(const BST & rhs)               throw (const char *);
   ~BST() { clear(); }

   BST & operator = (const BST & rhs) throw (const char *);
   class BNode;   

   // standard container interfaces
   // BST treats size and max_size the same
   int  size () const { return numElements; }
   bool empty() const { return size() == 0; }
   BNode * getRoot()  {return root;         }
   void insert(const T & t) throw (const char *);   
   void clear() { clear(root); }
   
   class iterator;
   iterator find(const T & t);
   iterator insert(iterator & it, const T & data) throw (const char *);
   
   void erase(BST <T> :: iterator it);
   
   // the various iterator interfaces
   iterator begin () const;
   iterator end   () const;
   iterator rbegin() const;
   iterator rend  () const;
   
private:
   // a debug utility to display the BST
   Debug(void display() const); 
   
   BNode * copyBTree(const BNode * pSrc) throw (const char *);
   void clear(BNode * & pNode);

   BNode * root;
   int numElements;
};

/************************************************
 * BNODE
 ***********************************************/
template <class T>
class BST<T>::BNode
{
  private:
  public:
    //DEFALUT CONSTRUCTOR
    BNode()     { pParent = pLeft = pRight = NULL; isRed = true;           }
    //NON-DEFAULT CONSTRUCTOR
    BNode( T t) { pParent = pLeft = pRight = NULL; data = t; isRed = true; }
    void balance();

    T data;
    BNode *pLeft;
    BNode *pRight;
    BNode *pParent;
    bool isRed;
};

/**************************************************
 * BST ITERATOR
 * An iterator through set
 *************************************************/
template <class T>
class BST <T> :: iterator
{
   friend class BST<T>;
public:
   // constructors, destructors, and assignment operator
   iterator()          : p(NULL)  {              }
   iterator(BNode * p) : p(p)     {              }
   iterator(const iterator & rhs) { *this = rhs; }
   iterator & operator = (const iterator & rhs)
   {
      this->p = rhs.p;
      return *this;
   }

   // equals, not equals operator
   bool operator != (const iterator & rhs) const { return rhs.p != this->p; }
   bool operator == (const iterator & rhs) const { return rhs.p == this->p; }

   // dereference operator
         T & operator * ()       { return p->data; }
   const T & operator * () const { return p->data; }


   iterator & operator -- ();
   // prefix increment
   iterator & operator ++ ();
   
private:
   BNode * p;
};

/**************************************************
 * BST ITERATOR :: DECREMENT PREFIX
 *     advance by one. 
 * Author:      Br. Helfrich
 * Performance: O(log n) though O(1) in the common case
 *************************************************/
template <class T>
typename BST <T> :: iterator & BST <T> :: iterator :: operator -- ()
{
   // do nothing if we have nothing
   if (NULL == p)
      return *this;

   // if there is a left node, take it
   if (NULL != p->pLeft)
   {
      // go left
      p = p->pLeft;

      // jig right - there might be more right-most children
      while (p->pRight)
         p = p->pRight;
      return *this;
   }

   // there are no left children, the right are done
   assert(NULL == p->pLeft);
   BNode * pSave = p;

   // go up
   p = p->pParent;

   // if the parent is the NULL, we are done!
   if (NULL == p)
      return *this;

   // if we are the right-child, got to the parent.
   if (pSave == p->pRight)
      return *this;

   // we are the left-child, go up as long as we are the left child!
   while (NULL != p && pSave == p->pLeft)
   {
      pSave = p;
      p = p->pParent;
   }

   return *this;
}

/************************************************
 * ITERATOR Prefix it goes through the tree
 * correctly. 
 ***********************************************/
template <class T>
typename BST <T> :: iterator & BST <T> :: iterator :: operator ++ ()
{
   // do nothing if we have nothing
   if (NULL == p)
      return *this;

   // if there is a left node, take it
   if (NULL != p->pRight)
   {
      // go left
      p = p->pRight;

      // jig right - there might be more right-most children
      while (p->pLeft)
         p = p->pLeft;
      return *this;
   }

   // there are no left children, the right are done
   assert(NULL == p->pRight);
   BNode * pSave = p;

   // go up
   p = p->pParent;

   // if the parent is the NULL, we are done!
   if (NULL == p)
      return *this;

   // if we are the right-child, got to the parent.
   if (pSave == p->pLeft)
      return *this;

   // we are the left-child, go up as long as we are the left child!
   while (NULL != p && pSave == p->pRight)
   {
      pSave = p;
      p = p->pParent;
   }

   return *this;
}

/********************************************
 * BST :: BEGIN
 * Note that you have to use "typename" before
 * the return value type
 ********************************************/
template <class T>
typename BST <T> :: iterator BST <T> :: begin () const
{
   BNode * pNode = root;

   if (pNode == NULL)
   {
      return iterator (NULL);
   }

   if (pNode)
   {
      while (pNode->pLeft != NULL)
      {
         pNode = pNode->pLeft;
      }
      return iterator (pNode);
   }
}

/********************************************
 * BST :: rbegin
 * returns the second to last item in the set
 ********************************************/
template <class T>
typename BST <T> :: iterator BST <T> :: rbegin () const
{
   BNode * pNode = root;

   if (pNode == NULL)
   {
      return iterator (NULL);
   }

   if (pNode)
   {
      while (pNode->pRight != NULL)
      {
         pNode = pNode->pRight;
      }
      return iterator (pNode);
   }

}

/********************************************
 * BST :: END
 * Note that you have to use "typename" before
 * the return value type
 ********************************************/
template <class T>
typename BST <T> :: iterator BST <T> :: end () const
{
   return iterator (NULL);
}

/********************************************
 * BST :: rend
 * returns the second to last item in the set
 ********************************************/
template <class T>
typename BST <T> :: iterator BST <T> :: rend () const
{
   return iterator (NULL);
}

/*******************************************
 * BST :: Assignment
 *******************************************/
template <class T>
BST <T> & BST <T> :: operator = (const BST <T> & rhs)
          throw (const char *)
{
   clear();

   root = copyBTree(rhs.root);
   numElements = rhs.numElements;

   return *this;
}

/*******************************************
 * BST :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
BST <T> :: BST(const BST <T> & rhs) throw (const char *)
{
   assert(rhs.size() >= 0);

   if (rhs.size() == 0)
   {
      root = NULL;
      numElements = 0;
   }
   else
   {
      root = NULL;
      *this = rhs;
   }
}

#ifndef NDEBUG

/************************************************
 * BALANCE
 * Makes sure the tree is balanced, (no 2 reds
 * in a row)
 ***********************************************/
template <class T>
void BST <T> :: BNode :: balance()
{
   // Case 1: No Parent
   if (!pParent)
   {
      isRed = false;
      return;
   }

   // Case 2: Black Parent
   else if (pParent->isRed != true)
      return;

   // Case 3: Red parent, black granny, red aunt
   if (pParent && pParent->pParent && pParent->pParent->pRight)
   {
      BNode * dad      = pParent;
      BNode * gramps   = pParent->pParent;
      BNode * tio      = pParent->pParent->pRight;

      if (dad->isRed && !gramps->isRed && tio->isRed)
      {
         gramps->isRed = true;
         tio->isRed    = false;
         dad->isRed    = false;
      }

      gramps->balance();
   }
}

/************************************************
 * COPYBTREE
 * copys the tree, 
 ***********************************************/
template <class T>
typename BST <T> :: BNode * BST <T> :: copyBTree(const BNode * pSrc) throw (const char *)
{
   if (pSrc == NULL)
   {
      return NULL;
   }
   BNode * destination = new BNode(pSrc->data);
   
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

/************************************************
 * INSERT
 * It inserts the node in the correct spot.
 ***********************************************/
template <class T>
   void BST <T> :: insert(const T & t) throw (const char *)
{
   BNode * pNode = root;
   BNode * pNew = new BNode(t);
   bool done = false;
   
   while (!done)
   {
      if (pNode == NULL)
      {
         root = pNew;
         numElements++;
         done = true;
      }

      else if (t < pNode->data)
      {
         if (!pNode->pLeft)
         {
            pNode->pLeft = pNew;
            pNew->pParent = pNode;
            numElements++;
            done = true;
         }
         else 
         {
            pNode = pNode->pLeft;
         }
      }

      else if (t > pNode->data)
      {
         if (!pNode->pRight)
         {
            pNode->pRight = pNew;
            pNew->pParent = pNode;
            numElements++;
            done = true;
         }
         else 
         {
            pNode = pNode->pRight;
         }
      }
   }

   pNew->balance();
}

/************************************************
 * BST : FIND
 * Finds a specific value and returns an iterator
 * pointing to it. If the value doesn't exist,
 * returns NULL.
 ***********************************************/
template <class T> 
typename BST <T> :: iterator BST <T> :: find(const T & t)
{
   BST <T> :: iterator it;
   for (it = begin(); it != end(); ++it)
   {
      if (*it == t)
      {
         return it;
      }
   }

   return end();
}

/*******************************************
 * BST :CLEAR delete all of the data in the 
 *       BST.
 *******************************************/
template <class T> 
void BST <T> :: clear(BNode * & pNode)
{
    if (pNode == NULL)
    {
        return;
    }
    clear(pNode->pLeft);
    clear(pNode->pRight);
    delete pNode;
    pNode = NULL;
    numElements--;

    return;
}


/*******************************************
 * BST :ERASE delete an item in the middle
 *       of the BST.
 *******************************************/
template <class T>
void BST <T> :: erase(BST <T> :: iterator it)
{
   // CASE 1:
   if(it.p->pRight == NULL && it.p->pLeft == NULL)
   {
      if (it.p->pParent != NULL && it.p->pParent->pRight == it.p)
      {
         it.p->pParent->pRight = NULL;
      }
      if (it.p->pParent != NULL && it.p->pParent->pLeft == it.p)
      {
         it.p->pParent->pLeft = NULL; 
      }
      delete it.p;

   }

   // CASE 2:
   if(it.p->pRight == NULL && it.p->pLeft != NULL)
   {
      it.p->pLeft->pParent = it.p->pParent;
      if (it.p->pParent != NULL && it.p->pParent->pRight == it.p)
         it.p->pParent->pRight = it.p->pLeft;
      if (it.p->pParent != NULL && it.p->pParent->pLeft == it.p)
         it.p->pParent->pLeft = it.p->pLeft;
      delete it.p;
   }

   if(it.p->pLeft == NULL && it.p->pRight != NULL)
   {
      it.p->pRight->pParent = it.p->pParent;
      if (it.p->pParent != NULL && it.p->pParent->pRight == it.p)
         it.p->pParent->pRight = it.p->pRight;
      if (it.p->pParent != NULL && it.p->pParent->pLeft == it.p)
         it.p->pParent->pLeft = it.p->pRight;
      delete it.p;
   }

   // CASE 3:
   
  
   if (it.p->pLeft != NULL && it.p->pRight != NULL)
   {
      BNode * temp = it.p->pRight;
      while (temp->pLeft != NULL)
      {
         temp = temp->pLeft;
      }
      
      it.p->data = temp->data;
      if (temp->pRight != NULL)
      {
         temp->pRight->pParent = temp->pParent;
         if (temp->pParent->pRight == temp)
            temp->pParent->pRight = temp->pRight;
         if (temp->pParent->pLeft == temp)
            temp->pParent->pLeft = temp->pRight;
         
         delete temp;
      }
      else
      {
         if (temp->pParent->pRight == temp)
            temp->pParent->pRight = NULL;
         if (temp->pParent->pLeft == temp)
            temp->pParent->pLeft = NULL;
         delete temp;
      }
   }
}

#endif // NDEBUG

}; // namespace custom

#endif // BST_H

