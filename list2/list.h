/***********************************************************************
 * Header:
 *    list
 * Summary:
 *    This class contains the notion of an list: a bucket to hold
 *    data for the user. This is just a starting-point for more advanced
 *    constainers such as the list, set, list, list, list, and map
 *    which we will build later this semester.
 *
 *    This will contain the class definition of:
 *       list             : similar to std::list
 *       list :: iterator : an iterator through the list
 * Author
 *    Sam Haymond, Emily Peck
 ************************************************************************/

#ifndef LIST_H
#define LIST_H

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
 * list
 * A class that holds stuff
 ***********************************************/
template <class T>
class list
{
public:
   // constructors and destructors
   list() : pHead(NULL), pTail(NULL), numElements(0) {}
   //list(int numCapacity)                 throw (const char *);
   list(const list & rhs)               throw (const char *);
   ~list() { clear(); }

   list & operator = (const list & rhs) throw (const char *);
   
   // standard container interfaces
   // list treats size and max_size the same
   int  size()     const { return numElements; }
   bool empty()    const { return size() == 0;        }

   void clear();
   T & back()                      throw (const char *);
   T back()        const           throw (const char *);
   T & front()                     throw (const char *);
   T front()       const           throw (const char *);
   void push_back( const T & rhs)  throw (const char *); 
   void push_front(const T & rhs)  throw (const char *); 
   void pop_back(); 
   void pop_front(); 
   
   class iterator;
   class reverse_iterator;

   iterator insert(iterator & it, const T & data) throw (const char *);
   iterator erase(list <T> :: iterator it);
   iterator find(const T & t);
   
   // the various iterator interfaces
   iterator begin()  const { return iterator (pHead); }
   iterator end()    const;
   iterator rBegin() const;

   //reverse_iterator begin() { return reverse_iterator (data); }
   reverse_iterator rend() const;
   reverse_iterator rbegin() const;

private:
   // a debug utility to display the list
   Debug(void display() const); 

   class Node;
   Node * pHead;
   Node * pTail;
   int numElements;
};

template <class T>
class list<T>::Node
{
public:
   Node() : data(T()), pPrev(NULL), pNext(NULL) {}
   Node(T t) { data = t; pNext = NULL; pPrev = NULL; }
   
   T data;
   Node * pPrev;
   Node * pNext;
};

/**************************************************
 * list ITERATOR
 * An iterator through set
 *************************************************/
template <class T>
class list <T> :: iterator
{
   friend class list<T>;
public:
   // constructors, destructors, and assignment operator
   iterator()      : p(NULL)      {              }
   iterator(Node * p) : p(p)      {              }
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

   // prefix increment
   iterator & operator ++ ()
   {
      p = p->pNext;
      return *this;
   }

   // postfix increment
   iterator operator ++ (int postfix)
   {
      iterator tmp(*this);
      p = p->pNext;
      return tmp;
   }
   
private:
   Node * p;
};

/********************************************
 * list :: END
 * Note that you have to use "typename" before
 * the return value type
 ********************************************/
template <class T>
typename list <T> :: iterator list <T> :: end () const
{
   return iterator (NULL);
}

/********************************************
 * list :: rbegin
 * returns the second to last item in the set
 ********************************************/
template <class T>
typename list <T> :: iterator list <T> :: rBegin () const
{
   return iterator (pTail);
}

/**************************************************
 * list REVERSE_ITERATOR
 * An iterator through set
 *************************************************/
template <class T>
class list <T> :: reverse_iterator
{
   friend class list<T>;
public:
   // constructors, destructors, and assignment operator
   reverse_iterator()      : p(NULL)              {              }
   reverse_iterator(Node * p) : p(p)              {              }
   reverse_iterator(const reverse_iterator & rhs) { *this = rhs; }
   reverse_iterator & operator = (const reverse_iterator & rhs)
   {
      this->p = rhs.p;
      return *this;
   }

   // equals, not equals operator
   bool operator != (const reverse_iterator & rhs) const { return rhs.p != this->p; }
   bool operator == (const reverse_iterator & rhs) const { return rhs.p == this->p; }

   // dereference operator
         T & operator * ()       { return p->data; }
   const T & operator * () const { return p->data; }

   // prefix increment
   reverse_iterator & operator ++ ()
   {
      p = p->pPrev;
      return *this;
   }

   // postfix increment
   reverse_iterator operator ++ (int postfix)
   {
      reverse_iterator tmp(*this);
      p = p->pPrev;
      return tmp;
   }
   
private:
   Node * p;
};

/********************************************
 * list :: END
 * Note that you have to use "typename" before
 * the return value type
 ********************************************/
template <class T>
typename list <T> :: reverse_iterator list <T> :: rend () const
{
   return reverse_iterator (NULL);
}

/********************************************
 * list :: rbegin
 * returns the second to last item in the set
 ********************************************/
template <class T>
typename list <T> :: reverse_iterator list <T> :: rbegin () const
{
   return reverse_iterator (pTail);
}

/*******************************************
 * list :: Assignment
 *******************************************/
template <class T>
list <T> & list <T> :: operator = (const list <T> & rhs)
          throw (const char *)
{
   clear();

   try
   {
      pTail = pHead = new Node (rhs.pHead->data);
      for (Node * p = rhs.pHead->pNext; p; p = p->pNext)
      {
         push_back(p->data);
      }
      numElements = rhs.size();
   }

   catch (std::bad_alloc)
   {
      throw "ERROR: unable to allocate a new node for a list";
   }

   return *this;
}

/*******************************************
 * list :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
list <T> :: list(const list <T> & rhs) throw (const char *)
{
   assert(rhs.size() >= 0);

   if (rhs.size() == 0)
   {
      pHead = NULL;
      pTail = NULL;
      numElements = 0;
   }

   else
   {
      pTail = pHead = new Node (rhs.pHead->data);
      for (Node * p = rhs.pHead; p; p = p->pNext)
      {
         push_back(p->data);
      }
      numElements = rhs.size();
   }

}

#ifndef NDEBUG

/*******************************************
 * list :PUSH take some element and add it to
 *        the list.
 *******************************************/
template <class T>
   void list <T> :: push_back(const T & t) throw (const char *)
{
   try
   {
      Node * pNew = new Node (t);

      if (pTail != NULL)
      {
         pNew->pPrev = pTail;
         pTail->pNext = pNew;

         pTail = pNew;
         numElements++;
      }
      else 
      {
         pTail = pNew;
         pHead = pNew;
         numElements++;
      }
   }

   catch (std::bad_alloc)
   {
      throw "ERROR: unable to allocate a new node for a list";
   }
}

/*******************************************
 * list :PUSH take some element and add it to
 *        the list.
 *******************************************/
template <class T>
   void list <T> :: push_front(const T & t) throw (const char *)
{
   try
   {
      Node * pNew = new Node (t);

      if (pHead != NULL)
      {
         pNew->pNext = pHead;
         pHead->pPrev = pNew;
         pNew->pPrev = NULL;

         pHead = pNew;
         numElements++;
      }

      else
      {
         pHead = pNew;
         pTail = pNew;
         numElements++;
      }
   }

   catch (std::bad_alloc)
   {
      throw "ERROR: unable to allocate a new node for a list";
   }
}

/*******************************************
 * list :POP take some element and add it to
 *        the list.
 *******************************************/
template <class T>
void list<T>::pop_back()
{
   /*if (size() == 0)
      return;
   iBack--;*/
   if (numElements == 0)
      return;

   Node * pRemove = pTail;
   pTail = pRemove->pPrev;
   pRemove->pPrev->pNext = NULL;
   delete pRemove;
   numElements--;
}

/*******************************************
 * list :POP take some element and add it to
 *        the list.
 *******************************************/
template <class T>
void list<T>::pop_front()
{
   /*if (size() == 0)
      return;
   iFront++;*/
   if (numElements == 0)
      return;

   Node * pRemove = pHead;
   pHead = pRemove->pNext;
   pRemove->pNext->pPrev = NULL;
   delete pRemove;
   numElements--;
}

/*******************************************
 * list :BACK take some element and add it to
 *        the list.
 *******************************************/
template <class T>
T list <T> :: back() const throw(const char *)
{
   if (!empty())
      return pTail->data;
   else
      throw "ERROR: unable to access data from an empty list";
}

/*******************************************
 * list :BACK take some element and add it to
 *        the list.
 *******************************************/
template <class T>
T & list <T> :: back() throw (const char *)
{
   if (!empty())
   {
      return pTail->data;
   }
   else
      throw "ERROR: unable to access data from an empty list";
}

/*******************************************
 * list :FRONT take some element and add it to
 *        the list.
 *******************************************/
template <class T>
T list <T> :: front() const throw(const char *)
{
   if (!empty())
   {
      return pHead->data;
   }
   else
      throw "ERROR: unable to access data from an empty list";
}

/*******************************************
 * list :FRONT take some element and add it to
 *        the list.
 *******************************************/
template <class T>
T & list <T> :: front() throw (const char *)
{
   if (!empty())
   {
      return pHead->data;
   }
   else
      throw "ERROR: unable to access data from an empty list";
}

/*******************************************
 * list :CLEAR delete all of the data in the 
 *       list.
 *******************************************/
template <class T> 
void list <T> :: clear()
{
   Node * pDelete;
   while (pHead != NULL)
   {
      pDelete = pHead; 
      pHead = pHead->pNext;
      delete pDelete;
      pDelete = NULL;
   }
   numElements = 0;
   pHead = NULL;
   pTail = NULL;
}

/*******************************************
 * list :INSERT insert an item in the middle
 *       of the list.
 *******************************************/
template <class T>
typename list <T> :: iterator list <T> :: insert(iterator & it, const T & data) throw (const char *)
{

   Node * pNew;
   try 
   {
      
      if (it.p != NULL)
      {
         pNew = new Node(data);
         pNew->pNext = it.p;
         pNew->pPrev = it.p->pPrev;
         it.p->pPrev = pNew;

         if (pNew->pPrev)
         {
            pNew->pPrev->pNext = pNew;
         }
         
         if (!pNew->pPrev)
            pHead = pNew;

         if (!pNew->pNext)
            pTail = pNew;
      }
      else
         push_back(data);
   }

   catch (std::bad_alloc)
   {
      throw "ERROR: unable to allocate a new node for a list";
   }  

   return pNew;
}

/*******************************************
 * list :ERASE delete an item in the middle
 *       of the list.
 *******************************************/
template <class T>
typename list <T> :: iterator list <T> :: erase(list <T> :: iterator it)
{
   Node * pReturn;
   Node * pRemove = it.p;

   if (pRemove->pPrev)
      pRemove->pPrev->pNext = pRemove->pNext;

   if (pRemove->pNext)
      pRemove->pNext->pPrev = pRemove->pPrev;

   pReturn = pRemove->pNext;

   if (pRemove->pPrev == NULL)
      pHead = pRemove->pNext;

   if (!pRemove->pNext)
      pTail = pRemove->pPrev;

   delete pRemove;

   return pReturn;
}

#endif // NDEBUG

}; // namespace custom


/*******************************************
 * list :ERASE delete an item in the middle
 *       of the list.
 *******************************************/
template <class T>
typename list <T> :: iterator list <T> :: find(const T & t)
{
   for (Node * pFind = pHead; pFind; pFind = pFind->pNext)
   {
      if (pFind->data == t)
         return iterator(pFind);
   }
   return end();
}

#endif // list_H

