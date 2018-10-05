#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <cctype>

using namespace std;

class Token
{
private:
   char token;
public:
   Token() : token('0') {}
   Token(char token) { this->token = token; }
   ~Token() {}

   void setToken(char token) { this->token = token; }
   int getType()
   {
      switch (token)
      {
         case '+':
         case '-':
            return 1;
         break;
         case '*':
         case '/':
            return 2;
         break;
         case '^':
            return 3;
         break;
         case '(':
            return 0;
         break;
         case ')':
            return 5;
         case ' ':
            return 7;
         break;
         case '.':
            return 8;
      }

      if (isalnum(token))
      {
         return 6;
      }


   }
   
};

#endif