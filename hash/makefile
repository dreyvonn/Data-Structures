###############################################################
# Program:
#     Assignment 12, Hash
#     Brother Helfrich, CS235
# Author:
#     Sam Haymond, Emily Peck, Emily Barrera
# Summary:
#     The hash has a number of buckets (lists) that contain
#     data. This program tests and implements the hash.
#
# Time Spent: 
#		Sam 1 hr
#     Emily P
#               Emily B 1 hr
#     Together 3 hrs
#
# Hardest Part:
#     The hardest part for us was understanding the functionality
#     of the hash. Making it and implementing it didn't end up
#     being too hard.
#     
###############################################################

##############################################################
# The main rule
##############################################################
a.out: assignment12.o spellCheck.o
	g++ -o a.out assignment12.o spellCheck.o -g
	tar -cf assignment12.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment12.o     : the driver program
#      spellCheck.o       : the spell-check program and driver
##############################################################
assignment12.o: hash.h assignment12.cpp list.h
	g++ -c assignment12.cpp -g

spellCheck.o: hash.h spellCheck.h spellCheck.cpp
	g++ -c spellCheck.cpp -g

