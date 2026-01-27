#ifndef BASKET_H_
#define BASKET_H_

class Basket
{
private:
   int serial;     // Serial number number for this basket.
   int uses;       // Count of how many times this basket was used.

public:
   Basket();
   ~Basket();

   int getSerial() const;
   int getUseCount() const;

   void simulate_wear_and_tear();

}; // end Basket

#endif
