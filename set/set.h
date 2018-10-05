/***********************************************************************
 * Header:
 *    set
 * Summary:
 *    This class contains the notion of an set: a bucket to hold
 *    data for the user. This is just a starting-point for more advanced
 *    constainers such as the set, set, set, set, set, and map
 *    which we will build later this semester.
 *
 *    This will contain the class definition of:
 *       set             : similar to std::set
 *       set :: iterator : an iterator through the set
 * Author
 *    Sam Haymond, Emily Peck
 ************************************************************************/

#ifndef SET_H
#define SET_H

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
/************************************************
 * set
 * A class that holds stuff
 ***********************************************/
template <class T>
class set
{
public:
   // constructors and destructors
   set() : data(NULL), numCapacity(0), numElements(0) {}
   set(int numCapacity)               throw (const char *);
   set(const set & rhs)               throw (const char *);
  ~set() { if (data != NULL) delete [] data;   }
   set & operator = (const set & rhs) throw (const char *);
   
   // standard container interfaces
   int  size()      const { return numElements;        }
   int capacity()   const { return numCapacity;        }
   bool empty()     const { return size() == 0;        }
   int & getNumElements() { return numElements;        }

   class iterator;

   void clear() { numElements = 0; }
   void insert(const T & t) throw (const char *);
   void erase(set <T> :: iterator & it);
   set <T> :: iterator find(const T & t);

   //overloaded operators
   set <T> operator ||(const set <T> & rhs) const throw(const char *);
   set <T> operator &&(const set <T> & rhs) const throw(const char *);
   set <T> operator - (const set <T> & rhs) const throw(const char *);

   // the various iterator interfaces
   iterator begin() { return iterator (data); }
   iterator end();
   iterator rbegin();

private:
   // a debug utility to display the set
   Debug(void display() const); 
   void resize  (const int newCapacity) throw (const char *);
   int findIndex(const T & t) const;
   T * data;              // dynamically allocated set of T
   int numCapacity;
   int numElements;
};

/**************************************************
 * Set ITERATOR
 * An iterator through set
 *************************************************/
template <class T>
class set <T> :: iterator
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
 * Set :: END
 * Note that you have to use "typename" before
 * the return value type
 ********************************************/
template <class T>
typename set <T> :: iterator set <T> :: end ()
{
   return iterator (data + numElements);
}

/********************************************
 * Set :: rbegin
 * returns the second to last item in the set
 ********************************************/
template <class T>
typename set <T> :: iterator set <T> :: rbegin ()
{
   return iterator ((data + numElements) - 1);
}

/*******************************************
 * set :: Assignment
 *******************************************/
template <class T>
set <T> & set <T> :: operator = (const set <T> & rhs)
          throw (const char *)
{
   if (capacity() < rhs.size())
   {
      resize(rhs.size());
   }

   for (int i = 0; i < rhs.size(); i++)
   {
      data[i] = rhs.data[i];
   }

   numElements = rhs.size();

   return *this;
}

/*******************************************
 * set :: Union
 *******************************************/
template <class T> 
set <T> set <T> :: operator ||(const set <T> & rhs) const throw (const char *)
{
   int iLhs = 0;
   int iRhs = 0;
   set <T> setReturn;

   while (iLhs < numElements || iRhs < rhs.numElements)
   {
      if (iLhs == numElements)
      {
         setReturn.insert(rhs.data[iRhs++]);
      } 
      else if (iRhs == rhs.numElements)
      {
         setReturn.insert(data[iLhs++]);
      }
      else if (data[iLhs] == rhs.data[iRhs])
      {
         setReturn.insert(data[iLhs]);
         iLhs++;
         iRhs++;
      }
      else if (data[iLhs] < rhs.data[iRhs])
      {
         setReturn.insert(data[iLhs++]);
      }
      else 
         setReturn.insert(rhs.data[iRhs++]);
   }

   return setReturn;
}

/*******************************************
 * set :: Intersection
 *******************************************/
template <class T>
set <T> set <T> :: operator &&(const set <T> & rhs) const throw (const char*)
{
   int iLhs = 0;
   int iRhs = 0;
   set <T> setReturn;

   while (iLhs < numElements || iRhs < rhs.numElements)
   {
      if (iLhs == numElements)
         return setReturn;
      else if (iRhs == rhs.numElements)
         return setReturn;
      else if (data[iLhs] == rhs.data[iRhs])
      {
         setReturn.insert(data[iLhs]);
         iLhs++;
         iRhs++;
      }
      else if (data[iLhs] < rhs.data[iRhs])
         iLhs++;
      else
         iRhs++;
   }

   return setReturn;
}

/*******************************************
 * set :: Difference
 *******************************************/
template <class T>
set <T> set <T> :: operator -(const set <T> & rhs) const throw (const char*)
{
   int iLhs = 0;
   int iRhs = 0;
   set <T> setReturn;

   while (iLhs < numElements || iRhs < rhs.numElements)
   {
      if (iLhs == numElements)
         return setReturn;
      else if (iRhs == rhs.numElements)
         setReturn.insert(data[iLhs++]);
      else if (data[iLhs] == rhs.data[iRhs])
      {
         iLhs++;
         iRhs++;
      }
      else if (data[iLhs] < rhs.data[iRhs])
      {
         setReturn.insert(data[iLhs++]);
      }
      else
         iRhs++;
   }

   return setReturn;
}

/*******************************************
 * set :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
set <T> :: set(const set <T> & rhs) throw (const char *)
{
   assert(rhs.size() >= 0);
      
   // do nothing if there is nothing to do
   if (rhs.size() == 0 || rhs.numCapacity == 0)
   {
      data        = NULL;
      numCapacity = 0;
      numElements = 0;
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
   numCapacity = rhs.numCapacity;
   numElements = rhs.numElements;

   // copy the items over one at a time using the assignment operator
   for (int i = 0; i < numCapacity; i++)
      data[i] = rhs.data[i];
}

/**********************************************
 * set : NON-DEFAULT CONSTRUCTOR
 * Preallocate the set to "capacity"
 **********************************************/
template <class T>
set <T> :: set(int numCapacity) throw (const char *)
{
   assert(numCapacity >= 0);
   
   // do nothing if there is nothing to do.
   // since we can't grow an set, this is kinda pointless
   if (numCapacity == 0)
   {
      this->data    = NULL;
      numCapacity   = 0;
      numElements   = 0;
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
    this->numCapacity = numCapacity;
    numElements = 0;
}

#ifndef NDEBUG
/********************************************
 * set : DISPLAY
 * A debug utility to display the contents of the set
 *******************************************/
template <class T>
void set <T> :: display() const
{
   std::cerr << "set<T>::display()\n";
   std::cerr << "\tnumElements = " << size() << "\n";
   for (int i = 0; i < size(); i++)
      std::cerr << "\tdata[" << i << "] = " << data[i] << "\n";
}


/*******************************************
 * set : to resize and set that isn't
 * large enough. 
 *******************************************/
template <class T>
void set <T> :: resize(int newCapacity) throw (const char *)
{
   if (numCapacity == 0)
   {
      numCapacity = 1;    
   }

   //int iBackNew = size() - 1;
   T *pNew; //create temporary pointer

   try
   {
      pNew = new T[newCapacity]; //point to temporary class
      assert(numCapacity);
      //int j = iNormalize(iFront);

      for (int i = 0; i < size(); i++)
      {
         if (data != NULL)
         {
            pNew[i] = data[i]; //copy over data from old to new
         }
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
 * set :INSERT take some element and add it to
 *        the set.
 *******************************************/
template <class T>
int set <T> :: findIndex(const T & t) const
{
   int iBegin = 0;
   int iEnd = numElements - 1;
   int iMiddle = 0;

   for (int i = 0; i < numElements; ++i)
   {
      if (numElements == 0)
         return numElements;
      else if (t == data[i])
         return i;
      else if (t < data[i])
         return i;
   }

   return numElements;

   /*while (iBegin <= iEnd)
   {
      iMiddle = (iBegin + iEnd) / 2;
      if (t == data[iMiddle])
          return iMiddle;
      else if (t < data[iMiddle])
         iEnd = (iMiddle - 1);
      else
         iBegin = (iMiddle + 1);
   }

   if (data[iMiddle] > t)
      return iMiddle - 1;
   else if (data[iMiddle] < t)
      return iMiddle + 1;
   else
      return numElements;*/
}
/*******************************************
 * set :INSERT take some element and add it to
 *        the set.
 *******************************************/
template <class T>
void set <T> :: insert(const T & element) throw (const char *)
{
   int iInsert = findIndex(element);
    if(data != NULL)
    {
      //resize
         if (size() == capacity())
         {
            resize(numCapacity * 2);
         }
        if (data[iInsert] != element)
        {
            
            
            //shift everything over
            for (int i = numElements - 1; i >= iInsert; i--)
            {
                data[i + 1] = data[i];
            }
            
            //insert value
            data[iInsert] = element;
            numElements++;
        }
    }
    else
    {
        resize(1);
        data[0] = element;
        numElements++;
    }
}

/*******************************************
 * set :ERASE erases element from the set
 *******************************************/
template <class T>
void set <T> :: erase(set <T> :: iterator & it)
{
   std::cerr << *it << std::endl;

   set <T> :: iterator itNext = it;
   itNext++;

   int iErase = findIndex(*it);
   int temp = numElements;
   numElements--;

   for (int i = iErase; i < numElements; ++i)
   {
      data[i] = data[i + 1];
   }

   /*std::cerr << "outside" << std::endl;
   while (it != end())
   {
      std::cerr << "it before " << *it << std::endl;
      std::cerr << "itNext before " << *itNext << std::endl;
      *it = *itNext;
      it++;
      itNext++;
      std::cerr << "it after " << *it << std::endl;
      std::cerr << "itNext after " << *itNext << std::endl;
   }*/
}

/*******************************************
 * set :FIND find some element and add it to
 *        the set.
 *******************************************/
template <class T>
typename set <T> :: iterator set <T> :: find(const T & t)
{
   //is this how iterators are returned?
   int iBegin = 0;
   int iEnd = numElements - 1;
   while (iBegin <= iEnd)
   {
      int iMiddle = (iBegin + iEnd) / 2;
      if (t == data[iMiddle])
         return iterator(data + iMiddle);
      if (t < data[iMiddle])
         iEnd = (iMiddle - 1);
      else
         iBegin = (iMiddle + 1);
   }
   
   return end();
}

#endif // NDEBUG

}; // namespace custom

#endif // set_H

