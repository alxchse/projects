
#include "Basket.h"
#include <stdlib.h>

int next_basket_serial = 2000;

Basket::Basket() {
  // Basket serial numbers are taken sequentially from a global variable.
  serial = next_basket_serial;
  next_basket_serial++;
}

Basket::~Basket() {
  // nothing to do
}

int Basket::getSerial() const {
  return serial;
}

int Basket::getUseCount() const {
  return uses;
}

void Basket::simulate_wear_and_tear() {
  uses++;
}
