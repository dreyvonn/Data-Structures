/***********************************************************************
 * Header:
 *    Stack
 * Summary:
 *    This class contains the notion of an array: a bucket to hold
 *    data for the user. This is just a starting-point for more advanced
 *    constainers such as the stack, set, stack, queue, deque, and map
 *    which we will build later this semester.
 *
 *    This will contain the class definition of:
 *       array             : similar to std::array
 *       array :: iterator : an iterator through the array
 * Author
 *    Sam Haymond
 ************************************************************************/

#ifndef STACK_H
#define STACK_H

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
class stack
{
public:
   // constructors and destructors
   stack() : data(NULL), numElements(0), numCapacity(0) {}
   stack(int numCapacity)                  throw (const char *);
   stack(const stack & rhs)        throw (const char *);
  ~stack()                         { if (data != NULL) delete [] data;   }
   stack & operator = (const stack & rhs) throw (const char *);
   
   // standard container interfaces
   // array treats size and max_size the same
   int  size()     const { return numElements;                 }
   
   // array-specific interfaces
   // what would happen if I passed -1 or something greater than numElements?
   T & operator [] (int index)       throw (const char *){ return data[index];}
   T   operator [] (int index) const throw (const char *){ return data[index];}
   
   // the various iterator interfaces
   class iterator;
   iterator begin()      { return iterator (data); }
   iterator end();
   
   int capacity() const { return numCapacity; }
   bool empty() const { return numElements == 0; }
   void resize(const int newCapacity) throw (const char *);

   void clear() { numElements == 0; }
   T & top() throw (const char *);
   T top() const throw (const char *);
   void push(const T & rhs) throw (const char *);  
   void pop(); 

private:
   // a debug utility to display the array
   Debug(void display() const); 

   T * data;              // dynamically allocated array of T
   int numElements;               // both the capacity and the numElementsber of elements
   int numCapacity;
};

/**************************************************
 * ARRAY ITERATOR
 * An iterator through array
 *************************************************/
template <class T>
class stack <T> :: iterator
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
typename stack <T> :: iterator stack <T> :: end ()
{
   return iterator (data + numElements);
}

/*******************************************
 * ARRAY :: Assignment
 *******************************************/
template <class T>
stack <T> & stack <T> :: operator = (const stack <T> & rhs)
          throw (const char *)
{
   resize(rhs.numElements);

   for (int i = 0; i < rhs.numElements; i++)
   {
      data[i] = rhs.data[i];
   }

   numElements = rhs.numElements;

   return *this;
}

/*******************************************
 * ARRAY :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
stack <T> :: stack(const stack <T> & rhs) throw (const char *)
{
   assert(rhs.numElements >= 0);
      
   // do nothing if there is nothing to do
   if (rhs.numElements == 0)
   {
      numElements = 0;
      data = NULL;
      numCapacity = 0;
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[rhs.numElements];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }
   
   // copy over the capacity
   numElements = rhs.numElements;
   numCapacity = rhs.numCapacity;

   // copy the items over one at a time using the assignment operator
   for (int i = 0; i < numElements; i++)
      data[i] = rhs.data[i];
}

/**********************************************
 * ARRAY : NON-DEFAULT CONSTRUCTOR
 * Preallocate the array to "capacity"
 **********************************************/
template <class T>
stack <T> :: stack(int numCapacity) throw (const char *)
{
   assert(numCapacity >= 0);
   
   // do nothing if there is nothing to do.
   // since we can't grow an array, this is kinda pointless
   if (numCapacity == 0)
   {
      this->numElements = 0;
      this->data = NULL;
      numCapacity = 0;
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[numCapacity];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }

      
   // copy over the stuff
   this->numElements = 0;
   this->numCapacity = numCapacity;
}

#ifndef NDEBUG
/********************************************
 * ARRAY : DISPLAY
 * A debug utility to display the contents of the array
 *******************************************/
template <class T>
void stack <T> :: display() const
{
   std::cerr << "stack<T>::display()\n";
   std::cerr << "\tnumElements = " << numElements << "\n";
   for (int i = 0; i < numElements; i++)
      std::cerr << "\tdata[" << i << "] = " << data[i] << "\n";
}


/*******************************************
 * stack : to resize and stack that isn't
 * large enough. 
 *******************************************/
template <class T>
void stack <T> :: resize(int newCapacity) throw (const char *)
{
   if (newCapacity == 0)
      newCapacity = 1;

   T *pNew; //create temporary pointer

   try
   {
      pNew = new T[newCapacity]; //point to temporary class

      for (int i = 0; i < size(); ++i)
      {
         pNew[i] = data[i]; //copy over data from old to new
      }

      delete [] data; //delete old data

      data = pNew; //point to new object

      numCapacity = newCapacity;
   }

   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }
}

/*******************************************
 * stack :PUSH take some element and add it to
 *        the stack.
 *******************************************/
template <class T>
   void stack <T> :: push(const T & rhs) throw (const char *)
{
   if (numCapacity == 0)
   {
      resize(1);
   }

   if (numElements == numCapacity)
   {
      resize(numCapacity * 2);
   }

   data[numElements] = rhs;
   numElements++;
}

template <class T>
void stack<T>::pop()
{
   if (numElements == 0)
      return;
   numElements--;
}

template <class T>
T stack <T> :: top() const throw(const char *)
{
   if (!empty())
      return data[numElements - 1];
   else
      throw "ERROR: Unable to reference the element from an empty Stack";
}

template <class T>
T & stack <T> :: top() throw (const char *)
{
   if (!empty())
      return data[numElements - 1];
   else
      throw "ERROR: Unable to reference the element from an empty Stack";
}

#endif // NDEBUG

}; // namespace custom

#endif // ARRAY_H

