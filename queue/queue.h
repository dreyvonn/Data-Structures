/***********************************************************************
 * Header:
 *    queue
 * Summary:
 *    This class contains the notion of an QUEUE: a bucket to hold
 *    data for the user. This is just a starting-point for more advanced
 *    constainers such as the queue, set, queue, queue, deque, and map
 *    which we will build later this semester.
 *
 *    This will contain the class definition of:
 *       QUEUE             : similar to std::QUEUE
 *       QUEUE :: iterator : an iterator through the QUEUE
 * Author
 *    Sam Haymond, Emily Peck
 ************************************************************************/

#ifndef QUEUE_H
#define QUEUE_H

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
 * QUEUE
 * A class that holds stuff
 ***********************************************/
template <class T>
class queue
{
public:
   // constructors and destructors
   queue() : data(NULL), numPop(0), numPush(0), numCapacity(0) {}
   queue(int numCapacity)                 throw (const char *);
   queue(const queue & rhs)               throw (const char *);
  ~queue()       { if (data != NULL) delete [] data;   }
   queue & operator = (const queue & rhs) throw (const char *);
   
   // standard container interfaces
   // QUEUE treats size and max_size the same
   int  size()     const { return numPush - numPop;                 }
   
   int capacity() const { return numCapacity;      }
   bool empty()   const { return (numPush - numPop) == 0; }
   //void resize(const int newCapacity) throw (const char *);

   void clear() { numPop = 0; numPush = 0; }
   T & back()                throw (const char *);
   T back()   const          throw (const char *);
   T & front()               throw (const char *);
   T front()   const         throw (const char *);
   void push(const T & rhs)  throw (const char *);  
   void pop(); 
   int iHead()       { assert(numCapacity); return numPop % numCapacity;        }
   int iTail() const { return (numPush - 1) % numCapacity; }

private:
   // a debug utility to display the QUEUE
   Debug(void display() const); 
   void resize(const int newCapacity) throw (const char *);

   T * data;              // dynamically allocated QUEUE of T
   int numCapacity;
   int numPop;
   int numPush;
};

/*******************************************
 * QUEUE :: Assignment
 *******************************************/
template <class T>
queue <T> & queue <T> :: operator = (const queue <T> & rhs)
          throw (const char *)
{
   numPush = 0;
   numPop = 0;

   if (capacity() < rhs.size())
   {
      resize(rhs.size());
   }

   for (int i = rhs.numPop; i < rhs.numPush; i++)
   {
      push(rhs.data[i % rhs.numCapacity]);
   }

   return *this;
}

/*******************************************
 * QUEUE :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
queue <T> :: queue(const queue <T> & rhs) throw (const char *)
{
   assert(rhs.size() >= 0);
      
   // do nothing if there is nothing to do
   if (rhs.size() == 0 || rhs.numCapacity == 0)
   {
      numPush     = 0;
      numPop      = 0;
      data        = NULL;
      numCapacity = 0;
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[rhs.numCapacity];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }
   
   // copy over the capacity
   numPush     = rhs.numPush;
   numPop      = rhs.numPop;
   numCapacity = rhs.numCapacity;

   // copy the items over one at a time using the assignment operator
   for (int i = 0; i < numCapacity; i++)
      data[i] = rhs.data[i];
}

/**********************************************
 * QUEUE : NON-DEFAULT CONSTRUCTOR
 * Preallocate the QUEUE to "capacity"
 **********************************************/
template <class T>
queue <T> :: queue(int numCapacity) throw (const char *)
{
   assert(numCapacity >= 0);
   
   // do nothing if there is nothing to do.
   // since we can't grow an QUEUE, this is kinda pointless
   if (numCapacity == 0)
   {
      this->numPush = 0;
      this->numPop  = 0;
      this->data    = NULL;
      numCapacity   = 0;
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
    this->numPush = 0;
    this->numPop  = 0;
    this->numCapacity = numCapacity;
}

#ifndef NDEBUG
/********************************************
 * QUEUE : DISPLAY
 * A debug utility to display the contents of the QUEUE
 *******************************************/
template <class T>
void queue <T> :: display() const
{
   std::cerr << "queue<T>::display()\n";
   std::cerr << "\tnumElements = " << size() << "\n";
   for (int i = 0; i < size(); i++)
      std::cerr << "\tdata[" << i << "] = " << data[i] << "\n";
}


/*******************************************
 * queue : to resize and queue that isn't
 * large enough. 
 *******************************************/
template <class T>
void queue <T> :: resize(int newCapacity) throw (const char *)
{
   if (numCapacity == 0)
   {
      numCapacity = 1;    
   }

   T *pNew; //create temporary pointer

   try
   {
      pNew = new T[newCapacity]; //point to temporary class
      assert(numCapacity);
      int j = iHead();

      for (int i = 0; i < size(); i++, j = (j + 1) % numCapacity)
      {
         pNew[i] = data[j]; //copy over data from old to new
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
 * queue :PUSH take some element and add it to
 *        the queue.
 *******************************************/
template <class T>
   void queue <T> :: push(const T & rhs) throw (const char *)
{
   if (numCapacity == 0)
   {
      numCapacity = 1;
      resize(numCapacity);
   }

   if (size() + 1 == numCapacity)
   {
      resize(numCapacity * 2);
   }

   data[(iTail() + 1) % numCapacity] = rhs;
   numPush++;
}

/*******************************************
 * queue :POP take some element and add it to
 *        the queue.
 *******************************************/
template <class T>
void queue<T>::pop()
{
   if (size() == 0)
      return;
   numPop++;
}

/*******************************************
 * queue :BACK take some element and add it to
 *        the queue.
 *******************************************/
template <class T>
T queue <T> :: back() const throw(const char *)
{
   if (!empty())
      return data[iTail()];
   else
      throw "ERROR: attempting to access an element in an empty queue";
}

/*******************************************
 * queue :BACK take some element and add it to
 *        the queue.
 *******************************************/
template <class T>
T & queue <T> :: back() throw (const char *)
{
   if (!empty())
   {
      return data[iTail()];
   }
   else
      throw "ERROR: attempting to access an element in an empty queue";
}

/*******************************************
 * queue :FRONT take some element and add it to
 *        the queue.
 *******************************************/
template <class T>
T queue <T> :: front() const throw(const char *)
{
   if (!empty())
   {
      return data[iHead()];
   }
   else
      throw "ERROR: attempting to access an element in an empty queue";
}

/*******************************************
 * queue :FRONT take some element and add it to
 *        the queue.
 *******************************************/
template <class T>
T & queue <T> :: front() throw (const char *)
{
   if (!empty())
   {
      return data[iHead()];
   }
   else
      throw "ERROR: attempting to access an element in an empty queue";
}


#endif // NDEBUG

}; // namespace custom

#endif // QUEUE_H

