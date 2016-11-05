#include "BucketSort.h"

#include <algorithm>

// TODO: replace this with a parallel version. 
void BucketSort::sort(unsigned int numCores) {
	std::sort(numbersToSort.begin(),numbersToSort.end(), [](const unsigned int& x, const unsigned int& y){
		unsigned int a = x;
		unsigned int b = y;
		// work out the starting digit of each number
		while (a / 10 > 0) {
			a = a / 10;
		}
		while (b / 10 > 0) {
			b = b / 10;
		}
		// if the digits are equal than sort on value.
		if (a == b)
			return x < y;
		else 
			return a < b;
	} );
}
