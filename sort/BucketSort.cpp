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
 //     			PARALLEL BUCKET SORT CPP			  	  //
 //                        z5081713                           //
 ///////////////////////////////////////////////////////////////


#include "BucketSort.h"
#include <algorithm>
#include <iostream> // to handle IO
#include <thread> //Duh!!
#include <cstring> // for lexicographic compare. not a good idea, but using it as a last resort.

int BucketSort::lead(unsigned int num) {
	int d = num < 10000 ? (num < 100 ? (num < 10 ? 1 : 10 ) : num < 1000 ? 100 : 1000) :
								(num < 10000000 ? (num < 100000 ? 10000 : num < 1000000 ? 100000 : 1000000):
									(num < 100000000 ? 10000000 : num < 1000000000 ? 100000000 : 1000000000));
	return num/d;

}

//Custom comparator to perform sort. Probably not the ideal way to do it.
bool compare_vecs(unsigned int a, unsigned int b){
	return std::strcmp(std::to_string(a).c_str(), std::to_string(b).c_str())< 0;
}

// Sort function to handle vecs. Multithreaded style!!.
void BucketSort::sort(unsigned int numCores) {


	for (unsigned int n : numbersToSort) {
		vecs[BucketSort::lead(n)].push_back(n);
	}
	// So many threads. Sorting with std::sort and custom comparator defined above
	std::thread t1{[this](){ std::sort(vecs[1].begin(),vecs[1].end(),compare_vecs); }};
	std::thread t2{[this](){ std::sort(vecs[2].begin(),vecs[2].end(),compare_vecs); }};
	std::thread t3{[this](){ std::sort(vecs[3].begin(),vecs[3].end(),compare_vecs); }};
	std::thread t4{[this](){ std::sort(vecs[4].begin(),vecs[4].end(),compare_vecs); }};
	std::thread t5{[this](){ std::sort(vecs[5].begin(),vecs[5].end(),compare_vecs); }};
	std::thread t6{[this](){ std::sort(vecs[6].begin(),vecs[6].end(),compare_vecs); }};
	std::thread t7{[this](){ std::sort(vecs[7].begin(),vecs[7].end(),compare_vecs); }};
	std::thread t8{[this](){ std::sort(vecs[8].begin(),vecs[8].end(),compare_vecs); }};
	std::thread t9{[this](){ std::sort(vecs[9].begin(),vecs[9].end(),compare_vecs); }};

	numbersToSort.clear();
	numbersToSort.reserve(vecs[1].size() + vecs[2].size() + vecs[3].size() + vecs[4].size() + vecs[5].size()
												+ vecs[6].size() + vecs[7].size() + vecs[8].size() + vecs[9].size());
	// Join threads and consolidate results
	t1.join();
	numbersToSort = std::move(vecs[1]);
	t2.join();
    std::move(std::begin(vecs[2]), std::end(vecs[2]), std::back_inserter(numbersToSort));
    t3.join();
    std::move(std::begin(vecs[3]), std::end(vecs[3]), std::back_inserter(numbersToSort));
    t4.join();
    std::move(std::begin(vecs[4]), std::end(vecs[4]), std::back_inserter(numbersToSort));
    t5.join();
    std::move(std::begin(vecs[5]), std::end(vecs[5]), std::back_inserter(numbersToSort));
    t6.join();
    std::move(std::begin(vecs[6]), std::end(vecs[6]), std::back_inserter(numbersToSort));
    t7.join();
    std::move(std::begin(vecs[7]), std::end(vecs[7]), std::back_inserter(numbersToSort));
    t8.join();
    std::move(std::begin(vecs[8]), std::end(vecs[8]), std::back_inserter(numbersToSort));
    t9.join();
    std::move(std::begin(vecs[9]), std::end(vecs[9]), std::back_inserter(numbersToSort));
    
}