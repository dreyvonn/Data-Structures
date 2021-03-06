/***********************************************************************
 * Header:
 *    list
 * Summary:
 *    Contains our class list as well as the nested classes iterator and
 *    node. Our list functions the same as std namespace list would (as far as we know).
 * Author
 *    Cameron Johnson, Jonah Barroso
 ************************************************************************/

#ifndef LIST_H
#define LIST_H
#include <iostream>

namespace custom
{
   template <class T>
   class list
   {
     private:
      int numElements;
      class Node;
      Node * pHead;
      Node * pTail;

     public:
      list () : pHead(NULL), pTail(NULL), numElements(0) {}
      list (const list & rhs);
      ~list() { clear(); }
      list <T> & operator = (const list <T> & rhs) throw (const char *);

      int  size ()  const { return numElements;                      }
      bool empty()  const { return (pHead == NULL && pTail == NULL); }
      void clear();

      void push_front(const T & t) throw (const char *);
      void push_back (const T & t) throw (const char *);
      void pop_back  ()            {if (!empty()) pTail = pTail->pPrev;   }
      void pop_front ()            {if (!empty()) pHead = pHead->pNext;   }
      T  front () const throw (const char *);
      T  back  () const throw (const char *);
      T & front()       throw (const char *);
      T & back ()       throw (const char *);

      class iterator;
      iterator begin ()  const   { return iterator (pHead);  }
      iterator end   ()  const   { return iterator (NULL);   }
      iterator find  (const T & t);
      iterator erase (list <T> :: iterator it);
      iterator insert(list <T> :: iterator & it, const T & t) throw (const char*);

      class reverse_iterator;
      reverse_iterator rbegin()  { return reverse_iterator (pTail); }
      reverse_iterator rend  ()  { return reverse_iterator (NULL);  }
   };

   /******************************************
    * NODE
    * Class implementation of our data type that list
    * is made up of.
    *******************************************/
   template <class T>
      class list <T> :: Node
   {
     public:
      T data;
      Node * pNext;
      Node * pPrev;
     Node(): data(T()), pNext(NULL), pPrev(NULL) {};
     Node(const T & t): data(t), pNext(NULL), pPrev(NULL) {};
   };

   /******************************************
    * COPY CONSTRUCTOR
    *******************************************/
   template <class T>
      list <T> :: list(const list <T> & rhs)
      : numElements(0), pHead(NULL), pTail(NULL)
   {
      *this = rhs;
   }

   /******************************************
    * ASSIGNMENT OPERATOR
    *******************************************/
   template <class T>
      list <T> & list <T> :: operator = (const list <T> & rhs) throw (const char *)
   {
      clear();
      for (Node * p = rhs.pHead; p; p = p->pNext)
         push_back(p->data);
      return *this;
   }

   /******************************************
       * CLEAR
       * removes all of the Nodes from our list
       *******************************************/
   template <class T>
      void list <T> :: clear()
   {
      Node * tmp = pHead;
      while(tmp != NULL)
      {
         tmp = pHead->pNext;
         delete pHead;
         pHead = tmp;
      }
      pTail = NULL;
      pHead = NULL;
      numElements = 0;
   }

   /******************************************
    * PUSH_FRONT
    * adds an element to the front of our list
    *******************************************/
   template <class T>
      void list <T> :: push_front(const T & t) throw (const char *)
   {
      Node * pNew = new Node (t);
      Node * p = pHead;

      if(p != NULL)
      {
         pNew->pNext = p;
         pNew->pPrev = p->pPrev;
         p->pPrev = pNew;
         if (pNew->pPrev)
            pNew->pPrev->pNext = pNew;
         else
            pHead = pNew;
      }
      else
      {
         pHead = pNew;
         pTail = pNew;
      }
      numElements++;
   }

   /******************************************
    * PUSH_BACK
    * adds an element to the end of our list
    *******************************************/
   template <class T>
      void list <T> :: push_back(const T & t) throw (const char *)
   {
      Node * pNew = new Node (t);
      Node * p = pTail;
      if(p != NULL)
      {
         pNew->pPrev = pTail;
         pNew->pNext = pTail->pNext;
         pTail->pNext = pNew;
         pTail = pNew;
      }
      else
      {
         pHead = pNew;
         pTail = pNew;
      }
      numElements++;
   }

   /******************************************
    * FRONT
    *******************************************/
   template <class T>
      T list <T> :: front() const throw (const char *)
   {
      if(!empty())
      {
         return pHead->data;
      }
      else
         throw "unable to access data from an empty list";
   }

   /******************************************
    * BACK
    *******************************************/
   template <class T>
      T list <T> :: back() const throw (const char*)
   {
      if(!empty())
      {
         return pTail->data;
      }
      else
         throw "unable to access data from an empty list";
   }

   /******************************************
    * FRONT BY REFERENCE
    *******************************************/
   template <class T>
      T & list <T> :: front() throw (const char *)
   {
      if(!empty())
      {
         return pHead->data;
      }
      else
         throw "unable to access data from an empty list";
   }

   /******************************************
    * BACK BY REFERENCE
    *******************************************/
   template <class T>
      T & list <T> :: back() throw (const char*)
   {
      if(!empty())
      {
         return pTail->data;
      }
      else
         throw "unable to access data from an empty list";
   }
   /**************************************************
    * LIST ITERATOR
        *************************************************/
   template <class T>
      class list <T> :: iterator
   {
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

      friend iterator list <T> :: insert(list <T> :: iterator & it, const T & t) throw (const char *);
      friend list <T> :: iterator list <T> :: erase(list <T> :: iterator it);

      // equals, not equals operator
      bool operator != (const iterator & rhs) const { return rhs.p != this->p; }
      bool operator == (const iterator & rhs) const { return rhs.p == this->p; }

      // dereference operator
      T & operator * ()       { return p->data; }
      const T & operator * () const { return p->data; }

      // prefix increment
      iterator & operator ++ ()
      {
         if (p != NULL)
            p = p->pNext;
         return *this;
      }

      // postfix increment
      iterator operator ++ (int postfix)
      {
         iterator tmp(*this);
         if (p != NULL)
            p = p->pNext;
         return tmp;
      }

      // prefix decrement
      iterator & operator -- ()
      {
         if (p != NULL)
            p = p->pPrev;
         return *this;
      }

      // postfix decrement
      iterator operator -- (int postfix)
      {
         iterator tmp(*this);
         if (p != NULL)
            p = p->pPrev;
         return tmp;
      }

     protected:
      Node * p;
   };

   /**************************************************
    * LIST REVERSE_ITERATOR
    * It's the same as our iterator..but it's reversed
    *************************************************/
   template <class T>
      class list <T> :: reverse_iterator
   {
     public:
      // constructors, destructors, and assignment operator
     reverse_iterator()      : p(NULL)      {              }
     reverse_iterator(Node * p) : p(p)         {              }
      reverse_iterator(const reverse_iterator & rhs) { *this = rhs; }
      reverse_iterator & operator = (const iterator & rhs)
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
         if (p != NULL)
            p = p->pPrev;

         return *this;
      }

      // postfix increment
      reverse_iterator operator ++ (int postfix)
      {
         reverse_iterator tmp(*this);
         if (p != NULL)
            p = p->pPrev;

         return tmp;
      }

      // prefix decrement
      reverse_iterator & operator -- ()
      {
         if (p != NULL)
            p = p->pNext;
         return *this;
      }

      // postfix decrement
      reverse_iterator operator -- (int postfix)
      {
         reverse_iterator tmp(*this);
         if (p != NULL)
            p = p->pNext;
         return tmp;
      }

     protected:
      Node * p;
   };

   /*****************************************
    * FIND
    * Locates a specific node in our linked-list
    ******************************************/
   template <class T>
      typename list <T> :: iterator list <T> :: find(const T & t)
   {
      for (Node * pFind = pHead; pFind; pFind  = pFind->pNext)
      {
         if (pFind->data == t)
            return iterator(pFind);
      }
      return end();
   }

   /*****************************************
    * ERASE
    * Deletes a single item in our list by
    * reassigning the pointers on both sides of the node
    ******************************************/
   template <class T>
      typename list <T> :: iterator list <T> :: erase(list <T> :: iterator it)
   {
      Node *pReturn = new Node();
      if (it.p == NULL)
         return it;

      // We meed tp check if there is a node before and after the node
      // to be removed.
      if (it.p->pPrev)
         it.p->pPrev->pNext = it.p->pNext;
      if (it.p->pNext)
         it.p->pNext->pPrev = it.p->pPrev;
      if (it.p->pPrev)
         pReturn = it.p->pPrev;
      else
         pReturn = it.p->pNext;

      if (it.p->pPrev == NULL)
         pop_front();
      if (it.p->pNext == NULL)
         pop_back();

      delete it.p;
      numElements--;
      it.p = pReturn;
      return it;
   }

   /*****************************************
    * INSERT
    * Adds a node into our linked list either to the front or back
    * of our list depending on what is desired.
    ******************************************/
   template <class T>
      typename list <T> :: iterator list <T> :: insert(list <T> :: iterator & it, const T & t) throw(const char*)
   {
      Node * p = it.p;
      Node * pNew = new Node (t);

      if (empty())              // Just in case there is nothing in our list to start
      {
         pHead = pNew;
         pTail = pNew;
      }
      else if (p != NULL)       // Placing node at head of list
      {
         pNew->pNext = p;
         pNew->pPrev = p->pPrev;
         p->pPrev = pNew;
         if (pNew->pPrev)
            pNew->pPrev->pNext = pNew;
         else
            pHead = pNew;
      }
      else                     // Placing node at end of list
      {
         pNew->pPrev = pTail;
         pNew->pNext = pTail->pNext;
         pTail->pNext = pNew;
         pTail = pNew;
      }
      numElements++;
      typename list <T> :: iterator temp(pNew);
      return temp;
   }
};
#endif
