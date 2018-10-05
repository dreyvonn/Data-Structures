/***********************************************************************
 * Header:
 *    map
 * Summary:
 *    This class contains the notion of an map: It holds a binary search 
 *    tree that has nodes consisting of a key and a value. The values are
 *    accessed by the keys. 
 *
 *    This will contain the class definition of:
 *       map             : similar to std::map
 *       map :: iterator : an iterator through the map
 * Author
 *    Sam Haymond, Emily Peck, Emily Barrera
 ************************************************************************/

#ifndef MAP_H
#define MAP_H

#include <cassert>  // because I am paranoid
#include <cmath>
#include <iostream>
#include "bst.h"
#include "pair.h"

// a little helper macro to write debug code
#ifdef NDEBUG
#define Debug(statement)
#else
#define Debug(statement) statement
#endif // !NDEBUG

namespace custom
{
   
/************************************************
 * map
 * A class that holds stuff
 ***********************************************/
template<class K, class V>
class map
{
public:
   // constructors and destructors
   map() {}
   map(const map <K, V> & rhs)               throw (const char *);
  ~map() { clear(); }
   map & operator = (const map <K, V> & rhs) throw (const char *);
   
   // standard container interfaces
   int  size () const { return bst.size();  }
   bool empty() const { return size() == 0; }
   void insert(const Pair<K, V> & p) throw (const char *);
   void clear();

   V & operator [] (const K & k)       throw (const char *);
   V   operator [] (const K & k) const throw (const char *);
   
   // the various iterator interfaces
   class iterator;
   iterator begin() { return iterator (bst.begin()); }
   iterator end  ();
   iterator find(const K & k);
   
private:
   // a debug utility to display the map
   Debug(void display() const); 

   BST <Pair<K, V> > bst;
};

/**************************************************
 * map ITERATOR
 * An iterator through map
 *************************************************/
template <class K, class V>
class map <K, V> :: iterator
{
public:
   // constructors, destructors, and assignment operator
   iterator() {}
   iterator(const iterator & rhs) { *this = rhs; }
   iterator(const typename BST <Pair<K, V> > :: iterator & rhs) 
   { 
      if (rhs != NULL) 
         it = rhs; 
   }

   iterator & operator = (const iterator & rhs)
   {
      it = rhs.it;
      return *this;
   }


   // equals, not equals operator
   bool operator != (const iterator & rhs) const { return it != rhs.it; }
   bool operator == (const iterator & rhs) const { return it == rhs.it; }

   // dereference operator
         Pair <K, V> & operator * ()       { return *it; }
   const Pair <K, V> & operator * () const { return *it; }

   // prefix increment
   iterator & operator ++ ()
   {
      ++it;
      return *this;
   }

   // postfix increment
   iterator operator ++ (int postfix)
   {
      iterator tmp(*this);
      ++it;
      return tmp;
   }

   iterator & operator -- ()
   {
      --it;
      return *this;
   }

   iterator operator -- (int postfix)
   {
      iterator tmp(*this);
      --it;
      return tmp;
   }
   
private:
   typename BST <Pair<K, V> > :: iterator it;
};


/********************************************
 * map :: END
 * Note that you have to use "typename" before
 * the return value type
 ********************************************/
template <class K, class V>
typename map <K, V> :: iterator map <K, V> :: end ()
{
   return iterator (bst.end());
}

/*******************************************
 * map :: Assignment
 *******************************************/
template <class K, class V>
map <K, V> & map <K, V> :: operator = (const map <K, V> & rhs)
          throw (const char *)
{

   bst = rhs.bst;

   return *this;
}

/*******************************************
 * map :: COPY CONSTRUCTOR
 *******************************************/
template <class K, class V>
map <K, V> :: map(const map <K, V> & rhs) throw (const char *)
{
   *this = rhs;
}

/************************************************
 * MAP : FIND
 * Finds a specific value and returns an iterator
 * pointing to it. If the value doesn't exist,
 * returns NULL.
 ***********************************************/
template <class K, class V> 
typename map <K, V> :: iterator map <K, V> :: find(const K & k)
{
   Pair<K, V> p(k, V());
   return bst.find(p);
}

/************************************************
 * INSERT
 * It inserts the node in the correct spot.
 ***********************************************/
template <class K, class V>
   void map <K, V> :: insert(const Pair <K, V> & p) throw (const char *)
{
   map <K, V> :: iterator it = bst.find(p);
   if (it != end())
      *it = p;
   else
      bst.insert(p);
}

#ifndef NDEBUG

/************************************************
 * MAP : ACCESS
 * Allows the user access to any part of the map
 * using a key
 ***********************************************/
template <class K, class V>
V  map <K,V> :: operator [] (const K & k) const throw (const char *)
{
   Pair <K,V> p(k, V());
   map<K, V> :: iterator it;
   it = bst.find(p);
   if ( it != end())
      return (*it).second;
   else
   {
      bst.insert(p);
      return (*(bst.find(p))).second;
   }
   
}

/************************************************
 * MAP : ACCESS
 * Allows the user access to any part of the map
 * using a key
 ***********************************************/
template <class K, class V>
V & map<K,V> :: operator [] (const K & k) throw (const char *)
{
   Pair <K,V> p(k, V());
   map<K, V> :: iterator it;
   it = bst.find(p);
   if ( it != end())
      return (*it).second;
   else
   {
      bst.insert(p);
      return (*(bst.find(p))).second;
   }

}

/*******************************************
 * map : clears the map, makes the 
 *          num of elements zero. 
 *******************************************/
template <class K, class V>
void map <K, V> :: clear()
{
   bst.clear();
   return;
}

#endif // NDEBUG

}; // namespace custom

#endif // map_H

