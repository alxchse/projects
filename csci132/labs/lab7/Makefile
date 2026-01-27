
all: pairs slowcommon fastercommon fastestcommon

pairs: always
	clang++ -Wall -O2 -o pairs Pairs.cpp

slowcommon: always
	clang++ -Wall -O2 -o slowcommon ComputeCommonSlow.cpp

fastercommon: always
	clang++ -Wall -O2 -o fastercommon ComputeCommonFaster.cpp

fastestcommon: always
	clang++ -Wall -O2 -o fastestcommon ComputeCommonFastest.cpp

.PHONY: always

