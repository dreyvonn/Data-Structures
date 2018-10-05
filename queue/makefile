###############################################################
# Program:
#     Assignment 03, QUEUE
#     Brother Helfrich, CS235
# Author:
#     Sam Haymond, Emily Peck
# Summary:
#     This is a queue, we implement the queue by storing/selling
#     stocks to demonstrate the properties of a queue. The 
#     hardest part was understanding what stock was doing. 
#     the instructions didn't make it very clear. 
# Time:
#     Together - 9.5 hours
#     Emily - 5 hours alone
#     Sam - 1 hour alone
#     Total - 15.5 hours
###############################################################

##############################################################
# The main rule
##############################################################
a.out: queue.h assignment03.o dollars.o stock.o
	g++ -o a.out assignment03.o dollars.o stock.o -g
	tar -cf assignment03.tar *.h *.cpp makefile

dollarsTest: dollars.o dollarsTest.cpp
	g++ -o dollarsTest dollars.o dollarsTest.cpp

##############################################################
# The individual components
#      assignment03.o : the driver program
#      dollars.o      : the Dollars class
#      stock.o        : the logic for the stock program
##############################################################
assignment03.o: queue.h assignment03.cpp
	g++ -c assignment03.cpp -g

dollars.o: dollars.h dollars.cpp
	g++ -c dollars.cpp

stock.o: stock.h stock.cpp queue.h
	g++ -c stock.cpp
