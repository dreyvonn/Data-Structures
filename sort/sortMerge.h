/***********************************************************************
 * Module:
 *    Week 11, Sort Merge
 *    Brother Helfrich, CS 235
 * Author:
 *    Sam Haymond, Emily Peck, Emily Barrera
 * Summary:
 *    This program will implement the Merge Sort
 ************************************************************************/

#ifndef SORT_MERGE_H
#define SORT_MERGE_H

/*****************************************************
 * SORT MERGE
 * Perform the merge sort
 ****************************************************/
template <class T>
void merge(T destination[],  T source1[], int size1, T source2[], int size2)
{
   int i1 = 0;
   int i2 = 0;

   for (int iDestination = 0; iDestination < (size1 + size2); ++iDestination)
   {
      if (i1 <= size1 && (i2 == size2 || source1[1] < source2[i2]))
         destination[iDestination] = source1[i1++];
      else
         destination[iDestination] = source2[i2++];
   }
}

template <class T>
void sortMerge(T array[], int num)
{
   int iBegin1 = 0;
   int iBegin2 = 0;
   int iEnd1 = 0;
   int iEnd2 = 0;
   int numIterations = 0;
   T source[num];

   //T destination[num];

   //source = array;
   T * pSource = source;
   T * pDest = array;

   for(int i = 0; i < num; i++)
      source[i] = array[i];

   /*do{
      int numIterations = 0;
      while (iBegin1 < num)
      {
         numIterations++;
         for (iEnd1 = iBegin1 + 1; num && !(pSource[iEnd1 - 1] > pSource[iEnd1]); ++iEnd1)
         {
            iBegin2 = iEnd1 + 1;
         }
         for (iEnd2 = iBegin2 + 1; num && !(pSource[iEnd2 - 1] > pSource[iEnd2]); ++iEnd2)
         {
            if( iBegin2 < num)
               merge(pDest,
                     source + iBegin1,
                     iEnd1  - iBegin1 + 1,
                     source + iBegin2,
                     iEnd2  - iBegin2 + 1);
               iBegin1 = iEnd2 + 1;
         }
      }
      std::swap(pSource, pDest);
   }
   while (numIterations > 1);*/

   if(array != source)
   {
      for(int i = 0; i < num - 1; i++)
         array[i] = source[i];
   }


}



#endif // SORT_MERGE_H
