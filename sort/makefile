###############################################################
# Program:
#     Assignment 11, Sorts
#     Brother Helfrich, CS235
# Author:
#     Sam Haymond, Emily Peck, Emily Barrera
# Summary:
#     This program implemented seven sorting algorithms: 
#     Bubble Sort, Selection Sort, Insertion Sort, Binary Sort,
#     Heap Sort, Merge Sort, and Quick Sort.
# Time:
#     Individually:
#     Emily Barrera: 1.5 hours
#     Emily Peck   :
#     Sam Haymond  : 2 hours
#    
#     Together:
#     
#
###############################################################

##############################################################
# The main rule
##############################################################
a.out: assignment11.o
	g++ -o a.out assignment11.o -g
	tar -cf assignment11.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment11.o     : the driver program
##############################################################
assignment11.o: assignment11.cpp sortValue.h \
		sortBinary.h sortInsertion.h sortHeap.h sortBubble.h \
		sortSelection.h sortMerge.h sortQuick.h
	g++ -c assignment11.cpp -g

