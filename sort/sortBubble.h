/***********************************************************************
 * Module:
 *    Week 11, Sort Bubble
 *    Brother Helfrich, CS 235
 * Author:
 *    Sam Haymond, Emily Peck, Emily Barrera
 * Summary:
 *    This program will implement the Bubble Sort
 ************************************************************************/

#ifndef SORT_BUBBLE_H
#define SORT_BUBBLE_H

/*****************************************************
 * SWAP
 * Swaps two values in the array.
 ****************************************************/
template <class T>
void swap(T array[], int iCheck, int iNext)
{
   T iTemp;
   iTemp = array[iCheck];
   array[iCheck] = array[iNext];
   array[iNext] = iTemp;
}

/*****************************************************
 * SORT BUBBLE
 * Perform the bubble sort
 ****************************************************/
template <class T>
void sortBubble(T array[], int num)
{
   for (int iPivot = num - 1; iPivot > 0; --iPivot)
   {
      bool swapped = false;
      for (int iCheck = 0; iCheck < iPivot; ++iCheck)
      {
         if (array[iCheck] > array[iCheck + 1])
         {
            swap(array, iCheck, iCheck + 1);
            swapped = true;
         }
      }
      if (!swapped)
         return;
   }
}

#endif // SORT_BUBBLE_H
