#include </usr/include/gmpxx.h>
#include <string>
#include <cstdlib>
#include <iostream>
using namespace std;

typedef mpz_class BigInt;

BigInt power1(int, int);
BigInt power2(int, int);
BigInt power3(int, int);
int main(int argc, char *argv[]) {
    if (argc != 4) {
        cout <<"usage: " << argv[0] << " <power1/power2/power3> "
             << " <base> " << " <exponent> " << endl;
        cout << "For example: " << "./exp power1 2 4" << endl;
        return 1;
    } 
    string choice = argv[1];
    int base = atoi(argv[2]);
    int exponent = atoi(argv[3]);

    BigInt result = 0;
    if (choice == "power1") {
        result = power1(base, exponent);
    } else if (choice == "power2") {
        result = power2(base, exponent);
    } else if (choice == "power3") {
        result = power3(base, exponent);
    }

    // Comment the following line when timing the program
    // for very large exponents
    cout << "Result is: " << result <<  endl;
    
    return 0;
}

/*
 * Computes the value of x^n using iteration.
 * Precondition: n >= 0.
 */
BigInt power1(int x, int n) {
    BigInt result = 1;
    if (n == 0)
        return result;

    for (int i = 0; i <= n; i++) {
        result = x * result;
    }
    return result;
}

/*
 * Computes the value of x^n recursively using the
 * formulation x^n = 1 if n = 0 and x*x^n-1 otherwise.
 * Precondition: n >= 0.
 */
BigInt power2(int x, int n) {
    BigInt result = 1;
    if (n == 0)
        return result;

    result = x * power2(x,n-1);
    return result;
}

/*
 * Computes the value of x^n recursively using
 * the formulation
 *       | 1 if n = 0
 * x^n = | (x^n/2)^2 if n is even,
 *       | x*(x^n/2)^2 if n > 0 and n is odd.
 * Precondition: n >= 0.
 */
BigInt power3(int x, int n) {
    BigInt result = 1;
    if (n == 0)
        return result;

    if (n % 2 == 0) {
        result = power3(x, n/2);
        return result * result;
    } else {
        result = power3(x, n/2);
        return result * result * x;
    }
}
