/***************************************
 * This is a code fragment meant to help
 * you debug your queue code. I hope
 * this helps
 *                    - Br. Helfrich
 ***************************************/


#ifdef DEBUG
// this code should be copy-pasted into queue.h immediately after
// the class definition. Also, put the following inside the class
// definition itself:
//     void display() const;
// Please remove this comment when you have done that.

using std::cerr;
using std::endl;
/*******************************************************
 * debug display
 *******************************************************/
template <class T>
void queue <T> :: display() const
{
   // display the contents of the array
   cerr << "data = ";
   for (int i = 0; i < numCapacity; i++)
   {
      if (iHead() > iTail() && (i <= iTail() || i >= iHead()))
         cerr << data[i] <<  ' ';
      else if (iHead() <= iTail() && i >= iHead() && i <= iTail())
         cerr << data[i] << ' ';
      else
         cerr << "? ";
   }
   cerr << endl;

   // display the contents of the member variables
   cerr << "numPush     " << numPush << endl;
   cerr << "numPop      " << numPop  << endl;
   cerr << "numCapacity " << numCapacity << endl;

   // display the contents of the header and tail
   if (numCapacity)
   {
      cerr << "iHead()     " << iHead() << endl;
      cerr << "iTail()     " << iTail()  << endl;
   }
}
#else
template <class T>
void queue <T> :: display() const
{
}
#endif // DEBUG
