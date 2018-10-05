/***********************************************************************
 * Header:
 *    Array
 * Summary:
 *    This class contains the notion of an array: a bucket to hold
 *    data for the user. This is just a starting-point for more advanced
 *    constainers such as the vector, set, stack, queue, deque, and map
 *    which we will build later this semester.
 *
 *    This will contain the class definition of:
 *       array             : similar to std::array
 *       array :: iterator : an iterator through the array
 * Author
 *    Sam Haymond
 ************************************************************************/

#ifndef VECTOR_H
#define VECTOR_H

#include <cassert>  // because I am paranoid

// a little helper macro to write debug code
#ifdef NDEBUG
#define Debug(statement)
#else
#define Debug(statement) statement
#endif // !NDEBUG

namespace custom
{

/************************************************
 * ARRAY
 * A class that holds stuff
 ***********************************************/
template <class T>
class vector
{
public:
   // constructors and destructors
   vector() : data(NULL), num(0), numCapacity(0) {}
   vector(int num)                  throw (const char *);
   vector(const vector & rhs)        throw (const char *);
  ~vector()                         { delete [] data;   }
   vector & operator = (const vector & rhs) throw (const char *);
   
   // standard container interfaces
   // array treats size and max_size the same
   int  size()     const { return num;                 }
   int  max_size() const { return num;                 }
   
   // array-specific interfaces
   // what would happen if I passed -1 or something greater than num?
   T & operator [] (int index)       throw (const char *){ return data[index];}
   T   operator [] (int index) const throw (const char *){ return data[index];}
   
   // the various iterator interfaces
   class iterator;
   iterator begin()      { return iterator (data); }
   iterator end();
   
   int capacity() const { return numCapacity; }
   bool empty() const { return num == 0; }
   void resize(const int newCapacity);
   void push_back(T var);
   void clear();

private:
   // a debug utility to display the array
   Debug(void display() const); 

   T * data;              // dynamically allocated array of T
   int num;               // both the capacity and the number of elements
   int numCapacity;
};

/**************************************************
 * ARRAY ITERATOR
 * An iterator through array
 *************************************************/
template <class T>
class vector <T> :: iterator
{
public:
   // constructors, destructors, and assignment operator
   iterator()      : p(NULL)      {              }
   iterator(T * p) : p(p)         {              }
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
         T & operator * ()       { return *p; }
   const T & operator * () const { return *p; }

   // prefix increment
   iterator & operator ++ ()
   {
      p++;
      return *this;
   }

   // postfix increment
   iterator operator ++ (int postfix)
   {
      iterator tmp(*this);
      p++;
      return tmp;
   }
   
private:
   T * p;
};


/********************************************
 * ARRAY :: END
 * Note that you have to use "typename" before
 * the return value type
 ********************************************/
template <class T>
typename vector <T> :: iterator vector <T> :: end ()
{
   return iterator (data + num);
}

/*******************************************
 * ARRAY :: Assignment
 *******************************************/
template <class T>
vector <T> & vector <T> :: operator = (const vector <T> & rhs)
          throw (const char *)
{
   while (numCapacity < rhs.num)
   {
      resize(numCapacity * 2);
   }

   num = rhs.num;

   for (int i = 0; i < num; i++)
   {
      data[i] = rhs.data[i];
   }

   return *this;
}

/*******************************************
 * ARRAY :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
vector <T> :: vector(const vector <T> & rhs) throw (const char *)
{
   assert(rhs.num >= 0);
      
   // do nothing if there is nothing to do
   if (rhs.num == 0)
   {
      num = 0;
      data = NULL;
      numCapacity = 0;
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[rhs.num];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }
   
   // copy over the capacity
   num = rhs.num;
   numCapacity = rhs.numCapacity;

   // copy the items over one at a time using the assignment operator
   for (int i = 0; i < num; i++)
      data[i] = rhs.data[i];
}

/**********************************************
 * ARRAY : NON-DEFAULT CONSTRUCTOR
 * Preallocate the array to "capacity"
 **********************************************/
template <class T>
vector <T> :: vector(int num) throw (const char *)
{
   assert(num >= 0);
   
   // do nothing if there is nothing to do.
   // since we can't grow an array, this is kinda pointless
   if (num == 0)
   {
      this->num = 0;
      this->data = NULL;
      numCapacity = 0;
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[num];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }

      
   // copy over the stuff
   this->num = num;
   numCapacity = num;
}

#ifndef NDEBUG
/********************************************
 * ARRAY : DISPLAY
 * A debug utility to display the contents of the array
 *******************************************/
template <class T>
void vector <T> :: display() const
{
   std::cerr << "vector<T>::display()\n";
   std::cerr << "\tnum = " << num << "\n";
   for (int i = 0; i < num; i++)
      std::cerr << "\tdata[" << i << "] = " << data[i] << "\n";
}


/*******************************************
 * VECTOR : to resize and vector that isn't
 * large enough. 
 *******************************************/
template <class T>
void vector <T> :: resize(int newCapacity)
{
   T *pNew;

   try
   {
      pNew = new T[newCapacity];

      for (int i = 0; i < size(); ++i)
      {
         pNew[i] = data[i];
      }

      delete [] data;

      data = pNew;

      numCapacity = newCapacity;
   }

   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }
}

/*******************************************
 * VECTOR : take some element and add it to
 *          the vector.
 *******************************************/
template <class T>
void vector <T> :: push_back(T var)
{
   if (numCapacity == 0)
   {
      resize(1);
   }

   if (num == numCapacity)
   {
      resize(numCapacity * 2);
   }

   data[num] = var;
   num++;
}

/*******************************************
 * VECTOR : clears the vector, makes the 
 *          num of elements zero. 
 *******************************************/
template <class T>
void vector <T> :: clear()
{
   num = 0;
}

#endif // NDEBUG

}; // namespace custom

#endif // ARRAY_H

