/***********************************************************************
 * Module:
 *    Week 11, Sort Heap
 *    Brother Helfrich, CS 235
 * Author:
 *    Sam Haymond, Emily Peck, Emily Barrera
 * Summary:
 *    This program will implement the Heap Sort
 ************************************************************************/

#ifndef SORT_HEAP_H
#define SORT_HEAP_H
#include <algorithm>
/*****************************************************
 * CLASS HEAP
 ****************************************************/
template <class T>
class Heap //makes sure that in a tree, the parents are bigger than children
{
  public:
   Heap(T arrayInput[], int numInput);
   void sort();

  private:
   T * array;
   int num;

   void percolateDown(int index);
};

#endif // SORT_HEAP_H

/*****************************************************
 * PROCOLATEDOWN
 * Takes index as parameter and fixes the heap from
 * that index down.
 ****************************************************/
template <class T>
void Heap<T> :: percolateDown(int index)
{
   int indexLeft = (index * 2);
   int indexRight = (indexLeft + 1);

   if(indexRight <= num && array[indexRight] > array[indexLeft] && array[indexRight] > array[index])
   {
      std::swap(array[index], array[indexRight]);
      percolateDown(indexRight);
   }
   else if (array[indexLeft] > array[index] && indexLeft <= num)//<
   {
      std::swap(array[index], array[indexLeft]);
      percolateDown(indexLeft);
   }

}

/*****************************************************
 * Heap Constructor
 * Heapify it.
 ****************************************************/
template <class T>
Heap <T> :: Heap(T arrayInput[], int numInput)
{
   array = arrayInput - 1;
   num = numInput;
    
   for (int i = num/2; i >= 1; i--)
      percolateDown(i);

}

/*****************************************************
 * SORT 
 * Performs sort
 ****************************************************/
template <class T>
void Heap<T> ::sort()
{
   while (num > 1)
   {
      std::swap(array[1], array[num]);
      num--;
      percolateDown(1);
   }
}

/*****************************************************
 * SORT HEAP
 * Perform the heap sort
 ****************************************************/
template <class T>
void sortHeap(T array[], int num)
{
   Heap<T> h(array, num);
   h.sort();
}

