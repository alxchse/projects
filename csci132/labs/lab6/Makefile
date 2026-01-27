
all: exponent flight

exponent: always
	clang++ -Wall Exponentiation.cpp -o exp -lgmpxx -lgmp

flight: always
	clang++ -g -Wall Flight.cpp PrecondViolatedExcept.cpp -o flight

.PHONY: always
