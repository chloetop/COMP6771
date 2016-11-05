 /////////////////////////////////////////////////////////////// 
 //    														  //
 //                         ###    ######   ######      ##    //
 //                        ##      ##  ##   ##  ##     ###    //
 //      #####    #####   ##           ##       ##      ##    //
 //     ##       ##       #####       ##       ##       ##    //
 //     ##        ####    ##  ##      ##       ##       ##    //
 //     ##           ##   ##  ##     ##       ##        ##    //
 //      #####   #####     ####      ##       ##        ##    //
 //    														  //
 //     		COMP6771 Assignment_5: BUCKET SORT 		 	  //
 //     			PARALLEL BUCKET SORT HEADER			  	  //
 //                        z5081713                           //
 ///////////////////////////////////////////////////////////////

// gaurd
#ifndef BUCKET_SORT_H
#define BUCKET_SORT_H

#include <vector>

// Struct as in-Struct-ed.

struct BucketSort {
	
	// vector of numbers
	std::vector<unsigned int> numbersToSort;
	// Vector definition.
	std::vector<unsigned int> vecs[10] = {

		std::vector<unsigned int>(),
		std::vector<unsigned int>(),
		std::vector<unsigned int>(),
		std::vector<unsigned int>(),
		std::vector<unsigned int>(),
		std::vector<unsigned int>(),
		std::vector<unsigned int>(),
		std::vector<unsigned int>(),
		std::vector<unsigned int>(),
		std::vector<unsigned int>()

	};
	// Sort 
	void sort(unsigned int numCores);
	int lead(unsigned int num);

};


#endif /* BUCKET_SORT_H */