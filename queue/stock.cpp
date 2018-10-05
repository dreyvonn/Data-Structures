/***********************************************************************
 * Implementation:
 *    STOCK
 * Summary:
 *    This will contain the implementation for stocksBuySell() as well
 *    as any other function or class implementation you need
 * Author
 *    Sam Haymond, Emily Peck
 **********************************************************************/

#include <iostream>    // for ISTREAM, OSTREAM, CIN, and COUT
#include <string>      // for STRING
#include <cassert>     // for ASSERT
#include "stock.h"     // for STOCK_TRANSACTION
#include "queue.h"     // for QUEUE
#include "dollars.h"
using namespace std;
using namespace custom;

void sell(queue <Stock> &q, Stock s, queue <Stock> &history, Dollars & proceeds);
void display(queue <Stock> &q, queue <Stock> &history, Dollars proceeds);
/************************************************
 * STOCKS BUY SELL
 * The interactive function allowing the user to
 * buy and sell stocks
 ***********************************************/
void stocksBuySell()
{
   // instructions
   cout << "This program will allow you to buy and sell stocks. "
        << "The actions are:\n";
   cout << "  buy 200 $1.57   - Buy 200 shares at $1.57\n";
   cout << "  sell 150 $2.15  - Sell 150 shares at $2.15\n";
   cout << "  display         - Display your current stock portfolio\n";
   cout << "  quit            - Display a final report and quit the program\n";

   string action; 
   int amount;
   Dollars price;
   Dollars proceeds;
   bool quit = false;
   Stock s;
   queue <Stock> q;
   queue <Stock> history;

   while (!quit)
   {
      cout << "> ";
      cin >> action;

      switch (action[0])
      {
         case 'B':
         case 'b':
            cin >> amount;
            cin >> price;
            s.setAmount(amount);
            s.setPrice(price);
            q.push(s);
         break;
         case 's':
         case 'S':
            
            cin >> amount;
            cin >> price;
            s.setPrice(price);
            s.setAmount(amount);
            sell(q, s, history, proceeds);

         break;
         case 'd':
         case 'D':
            display(q, history, proceeds);
         break;
         case 'q':
         case 'Q':
            quit = true;
         break;
         default:
            cout << "invalid action" << endl;
      }
   }
}
void display (queue <Stock>& q, queue <Stock> &history, Dollars proceeds)
{
   queue <Stock> qTemp;
   queue <Stock> hTemp;
   int tempSize= 0;
   qTemp = q;
   tempSize = qTemp.size();
   hTemp = history;
   if (!q.empty())
   {
      cout << "Currently held:" << endl;
      for (int i = 0; i < tempSize; ++i)
      {
         cout << "\tBought " 
              << qTemp.front().getAmount() 
              << " shares at " 
              << qTemp.front().getPrice() 
              << endl;
         qTemp.pop();
      }
   }
   if (!history.empty())
   {
       cout << "Sell History:" << endl;
       for (int i = history.size(); i != 0; i--)
        {
            cout << "\tSold "
            << hTemp.front().getAmount()
            << " shares at "
            << hTemp.front().getPrice()
            << " for a profit of "
            << hTemp.front().getProfit()
            << endl;
            hTemp.pop();
        }
   }
   cout << "Proceeds: " << proceeds << endl; 
}

void sell(queue <Stock>& q, Stock s, queue <Stock> &history, Dollars & proceeds)
{
    int tempAmount = s.getAmount();
    Stock temp;
    temp.setPrice(s.getPrice());
    while (tempAmount != 0 )
    {
        if (s.getAmount() < q.front().getAmount())
        {
            s.setProfit((s.getPrice() - q.front().getPrice()) * s.getAmount());
            history.push(s);
            temp.setAmount(temp.getAmount() + s.getAmount());
            q.front().setAmount(q.front().getAmount() - s.getAmount());
            tempAmount = 0;
            proceeds += s.getProfit();
        }
        else if (s.getAmount() == q.front().getAmount())
        {
            s.setProfit((s.getPrice() - q.front().getPrice()) * s.getAmount());
            history.push(s);
            temp.setAmount(temp.getAmount() + s.getAmount());
            tempAmount = 0;
            if (!q.empty())
                q.pop();
            proceeds += s.getProfit();
        }
        //amount being sold is more than the oldest batch
        else
        {         
            temp.setAmount(temp.getAmount() + q.front().getAmount());
            temp.setProfit((temp.getPrice() - q.front().getPrice()) * temp.getAmount());
            history.push(temp);
            s.setAmount(s.getAmount() - q.front().getAmount());
            if (!q.empty())
                q.pop();
            proceeds += temp.getProfit();
        }
    }
}
