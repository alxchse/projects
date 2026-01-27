
#include "Customer.h"
#include "Basket.h"
#include "LinkedStack.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

int next_customer_id = 1000;

Customer::Customer() {
  // Customer IDs are taken sequentially from a global variable.
  id = next_customer_id;
  next_customer_id++;

  // Each customer shops for random duration between 0 and 19.
  duration = rand() % 20;

  // Initially the customer doesn't have a basket.
  basket = nullptr;
}

Customer::~Customer() {
  assert(basket == nullptr);
}

int Customer::getID() const {
  return id;
}

int Customer::getDuration() const {
  return duration;
}

void Customer::simulate_shopping() {
  assert(basket != nullptr);
  duration--;
  basket->simulate_wear_and_tear();
}

bool Customer::pick_basket(LinkedStack<Basket*> &pile) {
  assert(basket == nullptr);
  if (pile.isEmpty())
  {
    return false;
  }
  else
  {
    // Baskets are in a disorganized pile, so just pick one at random.
    basket = pile.peek();
    pile.pop();
    cout << "Customer " << id << " picks up basket " << basket->getSerial() << "\n";
    return true;

    // Baskets are in a disorganized pile, so just pick one at random.
    // basket = pile.pickRandom();
    // pile.remove(basket);
    // cout << "Customer " << id << " picks up basket " << basket->getSerial() << "\n";
    // return true;
  }
}

void Customer::return_basket(LinkedStack<Basket*> &pile) {

  assert(basket != nullptr);
  cout << "Customer " << id << " is done with basket " << basket->getSerial() << "\n";
  pile.push(basket);
  basket = nullptr;

  // assert(basket != nullptr);
  // cout << "Customer " << id << " is done with basket " << basket->getSerial() << "\n";
  // pile.add(basket);
  // basket = nullptr;
}

bool Customer::done_shopping() const {
  return (duration <= 0);
}

bool Customer::is_frustrated() const {
  return (duration < -20);
}
