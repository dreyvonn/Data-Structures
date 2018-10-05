###############################################################
# Program:
#     Assignment 04, DEQUE
#     Brother Helfrich, CS235
# Author:
#     Sam Haymond, Emily Peck
# Summary:
#    This program acts a double ended queue. It allows 
# 	the user to access the queue from the front and the back.
#	as well as popping them from the back and front. 
#	the hardest part was the iNormalize. Our normalize was one off.
# Time: 
#	Emily: 2 hrs
#	Sam: 1 hr
#	Together: 11hrs
###############################################################

##############################################################
# The main rule
##############################################################
a.out: deque.h assignment04.o nowServing.o
	g++ -o a.out assignment04.o nowServing.o -g
	tar -cf assignment04.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment04.o : the driver program
#      nowServing.o   : the logic for the now serving program
##############################################################
assignment04.o: deque.h assignment04.cpp
	g++ -c assignment04.cpp -g

nowServing.o: nowServing.h nowServing.cpp deque.h
	g++ -c nowServing.cpp
