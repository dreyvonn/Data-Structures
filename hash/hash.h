#ifndef HASH_H
#define HASH_H
#include "list.h"

using namespace custom;

/****************************************
 * HASH
 * A hash of data type T
 ****************************************/
template <class T>
class Hash
{
   public:
   Hash()               : numElements(0), numBuckets(0),          table(new list <T>[numBuckets]) {};
   Hash(int numBuckets) : numElements(0), numBuckets(numBuckets), table(new list <T>[numBuckets]) {};
   Hash(const Hash <T> & rhs) throw (const char *);
   ~Hash(){};
   
   Hash & operator = (const Hash <T> & rhs) throw (const char *);
   
   bool empty()const { return size() == 0; }
   bool find  (const T & t) const;
   void insert(const T & t) throw (const char *);
   
   virtual int  hash(const T & t) const  = 0;
   int  capacity() const { return numBuckets;  }
   int  size    () const { return numElements; }

private:
   list <T> * table;
   int numElements;
   int numBuckets;
};

/****************************************
 * HASH : copy
 * Copy constructor for the hash
 ****************************************/
template<class T>
Hash<T>::Hash(const Hash <T> & rhs) throw (const char *)
{
   numElements = rhs.size();
   numBuckets  = rhs.capacity();
   
   table = new list <T> [numBuckets];
   for (int i = 0; i < numBuckets; ++i)
   {
      table[i] = rhs.table[i];
   }

}

/****************************************
 * HASH : assignment opterator
 * assignment operator for the hash
 ****************************************/
template<class T>
Hash<T> & Hash<T>::operator = (const Hash <T> & rhs) throw (const char *)
{
   numElements = rhs.size();
   numBuckets  = rhs.capacity();
   
   table = new list <T> [numBuckets];
   for (int i = 0; i < numBuckets; ++i)
   {
      table[i] = rhs.table[i];
   }
   
   return *this;
}

/****************************************
 * HASH: insert
 * Insert an item into the hash.
 ****************************************/
template<class T>
void Hash<T>::insert(const T & t) throw (const char *)
{
   int i = hash(t);
   table[i].push_back(t);
   numElements++;   
}

/****************************************
 * HASH : find
 * Finds an item in the hash and returns
 * true if found, false if not. 
 ****************************************/
template<class T>
bool Hash<T>::find(const T & t) const
{
   int i = hash(t);  
   return table[i].find(t) != table[i].end();
}

#endif
