/***********************************************************************
 * Header:
 *    STOCK
 * Summary:
 *    This will contain just the prototype for stocksBuySell(). Stock 
 #    holds an amount, price, and profit made. 
 * Author
 *    Sam Haymond, Emily Peck
 ************************************************************************/

#ifndef STOCK_H
#define STOCK_H

#include "dollars.h"   // for Dollars defined in StockTransaction
#include "queue.h"     // for QUEUE
#include <iostream>    // for ISTREAM and OSTREAM

using namespace std;

class Stock
{
private:
   Dollars price;
   int amount;
   Dollars profit;
public:
   Stock() : price(), amount(0), profit() {}
   ~Stock() {}
   
   int getAmount() { return amount; }
   Dollars getPrice() { return price; }
   Dollars getProfit() { return profit; }

   void setAmount(int amount) { this->amount = amount; }
   void setPrice(Dollars price) { this->price = price; }
   void setProfit(Dollars profit) { this->profit = profit; }
};
// the interactive stock buy/sell function

void stocksBuySell();
//void display(Dollars price, queue <Stock> q);
//void sell(int amount);

#endif // STOCK_H

