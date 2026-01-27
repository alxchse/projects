#ifndef CUSTOMER_H_
#define CUSTOMER_H_

#include "LinkedStack.h"

class Basket; // forward declaration

class Customer
{
private:
   int id;         // ID number for this customer.
   int duration;   // How long this customer wants to shop for,
                   // zero or negative means they are ready to
                   // checkout.
   Basket *basket; // A basket to hold this customer's groceries.

public:
   Customer();
   ~Customer();

   int getID() const;
   int getDuration() const;

   void simulate_shopping();

   bool pick_basket(LinkedStack<Basket*> &pile);

   void return_basket(LinkedStack<Basket*> &pile);

   bool done_shopping() const;

   bool is_frustrated() const;

}; // end Customer

#endif
