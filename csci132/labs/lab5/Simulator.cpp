// Discrete event simulator for a grocery store, simulating customers who arrive
// at the store, pick up a basket, shop for a while, then go to a checkout lane
// to wait for a cashier, then give back their basket, then depart the store
// with their groceries. 
//
// We simulate only certain aspects of the scenario, and leave out other things:
//  - We only simulate 1 day worth of shopping, around 700 minutes.
//  - The simulation proceeds minute by minute, starting with t=0, t=1, t=2, etc.
//  - All customers are more-or-less identical, except that each customer has a
//    unique ID number, and each customer has a different (random) amount of
//    time they want to shop for before they are ready to check out. Once they
//    leave, customers don't ever return to the store.
//  - Each customer gets one basket. Each basket has a serial number and a "use
//    counter" to keep track of how many minutes the basket was in use by a
//    customer.
//  - We don't model food, purchases, prices, money, etc. So our simulated
//    customers don't actually buy anything, and the simulated baskets don't
//    actually hold any food.
//  - We don't simulate the store "closing." Instead, we just keep the
//    simulation running until all customers have left the store.

#include "Customer.h"
#include "Basket.h"
#include "LinkedBag.h"
#include "LinkedSet.h"
#include "ArrayQueue.h"
#include "StackInterface.h"
#include "LinkedStack.h"
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

// const int CHECKOUT_LANE_SIZE = 10;

// customer arrival times
LinkedBag<int> arrivals;

// set of baskets waiting to be picked up by customers
LinkedStack<Basket*> baskets;

// set of customers who are currently shopping
LinkedSet<Customer*> shoppers;

// set of customers who are waiting to check out
ArrayQueue<Customer*> checkout;

// bag filled with times that baskets are used
LinkedBag<int> hist;

int numFinished = 0;              // how many customers were simulated in total
int numSuccess = 0;               // how many of them were completely successfull
int numRejectedNoBaskets = 0;     // how many of them gave up because there were no baskets
int numRejectedBusyCashiers = 0;  // how many of them gave up because the cashier was too busy

// simulate_arriving_customer() is called once for each new customer arrival event,
// at the time of the arrival.
void simulate_arriving_customer() {

  // Create the new customer.
  Customer *c = new Customer();
  cout << "Customer " << c->getID() << " arrives at the store.\n";

  // Customer picks a basket on the way into the store.
  bool basketTaken = c->pick_basket(baskets);
  if (!basketTaken) {
    cout << "Customer " << c->getID() << " can't find a basket, goes home in despair!\n";
    numRejectedNoBaskets++;
    numFinished++;
    delete c;
    return;
  }

  // Customer joins the set of shoppers.
  shoppers.add(c);

  // Customer is ready to shop.
  cout << "Customer " << c->getID() << " is ready to shop for " << c->getDuration() << " min.\n";

}

// Each minute, simulate_shopper() is called once for each customer who is
// currently shopping.
void simulate_shopper(Customer *c) {
  // Time has passed, so decrement the duration they have left.
  c->simulate_shopping();

  // If they are ready to check out, try to join the checkout lane.
  if (c->done_shopping()) {
    cout << "Customer " << c->getID() << " is ready to check out.\n";
    shoppers.remove(c);
    bool foundLane = checkout.enqueue(c);
  
    if (!foundLane && c->is_frustrated()) {
      cout << "  no checkout lanes available, giving up in frustration!\n";
      // Return the customer's basket.
      c->return_basket(baskets);
      // Delete the customer, and update statistics.
      delete c;
      numRejectedBusyCashiers++;
      numFinished++;
    } else if (!foundLane) {
      cout << "  no checkout lanes available, shopping some more.\n";
      shoppers.add(c);
    } else {
      cout << "Customer " << c->getID() << " has joined the checkout lane.\n";
    }
  }
}



void simulate_cashier(int cashierNum, ArrayQueue<Customer*> &waiting) {
  // If no customers to serve, then don't do anything.
  if (waiting.isEmpty())
    return;

  // Otherwise, remove and checkout one customer.
  Customer *c = waiting.peekFront();
  waiting.dequeue();

  cout << "Cashier " << cashierNum << " checks out customer " << c->getID() << "\n";

  // Return the customer's basket.
  c->return_basket(baskets);

  // Delete the customer, and update statistics.
  delete c;
  numSuccess++;
  numFinished++;
}

void simulate_time_step(int t) {
  // First, simulate cashier checking out customers.
  simulate_cashier(1, checkout);

  // Next, simulate shopping behavior of existing customers.
  vector<Customer*> v = shoppers.toVector();
  for (int i = 0; i < v.size(); i++) {
    simulate_shopper(v[i]);
  }

  // Last, simulate arrival of new customer at time t, if needed.
  int numNewCustomers = arrivals.getFrequencyOf(t);
  for (int i = 0; i < numNewCustomers; i++) {
    simulate_arriving_customer();
  }
}


int main(int argCount, char **argVector)
{
  cout << std::unitbuf;

  if (argCount != 3) {
    cout << "Sorry, you must supply exactly 2 arguments, like this:\n"
      << "  " << argVector[0] << " N B\n"
      << "where N is the number of customers to simulate,\n"
      << "and B is the number of shopping baskets.\n";
    return 1;
  }

  int num_customers = atoi(argVector[1]);
  int num_baskets = atoi(argVector[2]);


  // Populate the pile of baskets.
  for (int i = 0; i < num_baskets; i++) {
    baskets.push(new Basket());
  }

  // Generate num_customers random arrival times between 0 and 699.
  for (int i = 0; i < num_customers; i++) {
    arrivals.add(rand() % 700);
  }

  int num_arrivals = arrivals.getCurrentSize();

  // Starting at t=0, simulate each time step. Keep simulating
  // until all num_arrivals customers have finished shopping.
  int t = 0;
  while (numFinished < num_arrivals) {
    cout << "t = " << t << "\n";
    simulate_time_step(t);
    t++;
  }

  // Print out some statistics
  cout << "* All customers finished.\n"
    << "Total time: " << t << " min\n"
    << "Total number of arrivals: " << num_arrivals << "\n"
    << "Number of happy customers: " <<  numSuccess << "\n"
    << "Number rejected due to no baskets: " <<  numRejectedNoBaskets << "\n"
    << "Number rejected due to busy cashiers: " <<  numRejectedBusyCashiers << "\n";

  int maxUsage = 0, minUsage = 10000;
  while (!baskets.isEmpty()) {
    Basket *b = baskets.peek();
    baskets.pop();
    if (b->getUseCount() > maxUsage) {
      maxUsage = b->getUseCount();
    }
    if (b->getUseCount() < minUsage) {
      minUsage = b->getUseCount();
    } 
    int MinsUsed = (b->getUseCount() / 10);
    hist.add(MinsUsed);

    delete b;
  }

  cout << "Basket maximum usage: " << maxUsage << " min\n";
  cout << "Basket minimum usage: " << minUsage << " min\n";

  cout << "Basket usage histogram:\n";
  for (int j = minUsage/10; j <= maxUsage/10; j++) {
    cout << hist.getFrequencyOf(j) << " baskets used for " << (j*10) << " min\n";
  }

  return 0;
}
