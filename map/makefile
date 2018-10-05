###############################################################
# Program:
#     Assignment 10, Map
#     Brother Helfrich, CS235
# Author:
#     Sam Haymond, Emily Peck, Emily Barrera
# Summary:
#     This assignment tests all the functions of a map and then
#     implements it by reading from a file into the map and 
#     allowning the user to ask for the count of a certain word
#     and know the exact amount of times that word is used in 
#     the file. 
#
# Time spent:
#		Sam - 2 hr
#     Emily -
#     Emily B. - 1 hr
#     Together - 10 hrs
#
# Most difficult part:
#		The most difficult part for us was the weird syntax that
#		is needed due to the double template class. 
###############################################################

##############################################################
# The main rule
##############################################################
a.out: assignment10.o wordCount.o
	g++ -o a.out assignment10.o wordCount.o -g
	tar -cf assignment10.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment10.o : the driver program
#      wordCount.o    : the wordCount() function
##############################################################
assignment10.o: pair.h map.h bst.h assignment10.cpp
	g++ -c assignment10.cpp -g

wordCount.o: map.h bst.h wordCount.h wordCount.cpp 
	g++ -c wordCount.cpp -g 
