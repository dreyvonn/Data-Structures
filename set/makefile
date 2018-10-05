###############################################################
# Program:
#     Assignment 05, SET
#     Brother Helfrich, CS235
# Author:
#     Sam Haymond, Emily Peck
# Summary:
#     This is a set that will store sets of data and sort them
#     appropriatly. The assignment05.cpp is there to make sure
#     the set works properly. Go fish is an example of 
#     the implementation of a set. 
# Time:
#     Together: 6 hrs
#     Emily:    3 hrs
#     Sam:      2 hrs
#     Total:    11 hrs
###############################################################

##############################################################
# The main rule
##############################################################
a.out: assignment05.o goFish.o card.o
	g++ -o a.out assignment05.o goFish.o card.o -g
	tar -cf assignment05.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment05.o : the driver program
#      goFish.o       : the logic for the goFish game
#      card.o         : a single playing card
##############################################################
assignment05.o: set.h goFish.h assignment05.cpp
	g++ -c assignment05.cpp -g

goFish.o: set.h goFish.h goFish.cpp card.h
	g++ -c goFish.cpp

card.o: card.h card.cpp
	g++ -c card.cpp 
