/***********************************************************************
 * Module:
 *    Week 08, Pairo
 *    Brother Helfrich, CS 235
 * Author:
 *    Br. Helfrich
 * Summary:
 *    This program will implement a pairo: two values
 ************************************************************************/

#ifndef PAIRO_H
#define PAIRO_H

#include <iostream>  // for ISTREAM and OSTREAM

namespace custom
{

/**********************************************
 * PAIRo
 * This class couples together a pairo of values, which may be of
 * different types (T1 and T2). The individual values can be
 * accessed through its public members first and second.
 *
 * Additionally, when compairoing two pairos, only T1 is compared. This
 * is a key in a name-value pairo.
 ***********************************************/
template <class T1, class T2>
class pairo
{
public:
   // constructors
   pairo() : first(), second() {}
   pairo(const T1 & first, const T2 & second) : first(first), second(second) {}
   pairo(const pairo <T1, T2> & rhs)   : first(rhs.first), second(rhs.second) {}

   // copy the values
   pairo <T1, T2> & operator = (const pairo <T1, T2> & rhs)
   {
      first  = rhs.first;
      second = rhs.second;
      return *this;
   }

   // constant fetchers
   const T1 & getFirst()  const { return first;  }
   const T2 & getSecond() const { return second; }
   
   // compare Pairos.  Only first will be compared!
   bool operator >  (const pairo & rhs) const { return first >  rhs.first; }
   bool operator >= (const pairo & rhs) const { return first >= rhs.first; }
   bool operator <  (const pairo & rhs) const { return first <  rhs.first; }
   bool operator <= (const pairo & rhs) const { return first <= rhs.first; }
   bool operator == (const pairo & rhs) const { return first == rhs.first; }
   bool operator != (const pairo & rhs) const { return first != rhs.first; }
   
   // these are public.  We cannot validate!
   T1 first;
   T2 second;
};

/*****************************************************
 * PAIRo INSERTION
 * Display a pairo for debug purposes
 ****************************************************/
template <class T1, class T2>
inline std::ostream & operator << (std::ostream & out,
                                   const pairo <T1, T2> & rhs)
{
   out << '(' << rhs.first << ", " << rhs.second << ')';
   return out;
}

/*****************************************************
 * PAIRo EXTRACTION
 * input a pairo
 ****************************************************/
template <class T1, class T2>
inline std::istream & operator >> (std::istream & in,
                                   pairo <T1, T2> & rhs)
{
   in >> rhs.first >> rhs.second;
   return in;
}

}

#endif // PAIRo_H
