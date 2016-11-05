#include "BucketSort.h"

#include <typeinfo>

int BucketSort::lead(unsigned int num) {
	int d = num < 10000 ? (num < 100 ? (num < 10 ? 1 : 10 ) : num < 1000 ? 100 : 1000) :
								(num < 10000000 ? (num < 100000 ? 10000 : num < 1000000 ? 100000 : 1000000):
									(num < 100000000 ? 10000000 : num < 1000000000 ? 100000000 : 1000000000) );
	return num/d;

}

void BucketSort::sort(unsigned int numCores) {

	std::vector<std::shared_ptr<std::thread>> threads1;
	std::array<std::mutex, 10> mutexes;


	std::function<void(unsigned int id)> b_push;
	b_push = [this, &numCores, &mutexes] (unsigned int id) {
		int num;
		int cur;
		for (unsigned int i=id;i<numbersToSort.size()-numCores;i+=numCores) {
			//std::cout << i << " " << id << " " << numCores << " " << numbersToSort.size()-numCores << std::endl;
			cur = numbersToSort[i];
			num = BucketSort::lead(cur);
			mutexes[num].lock();
			vecs[num].push_back(cur);
			mutexes[num].unlock();
			
		}
	};

	for (unsigned int i = 1; i < numCores; ++i) {
		threads1.push_back(std::make_shared<std::thread>(b_push, i));
	}

	b_push(0);
	
	for (auto t : threads1) {
		t->join();
	}

	/*
	for (unsigned int n : numbersToSort) {
		vecs[BucketSort::lead(n)].push_back(n);
	}
	*/

	int work = 9;
	std::mutex mutexWork;

	std::function<void()> b_sort;
	b_sort = [this, &work, &mutexWork, &b_sort] () {
			
			mutexWork.lock();
			//std::cout << "working on: " << work << std::endl;
			int i = work--;
			mutexWork.unlock();
			
			std::sort(vecs[i].begin(),vecs[i].end());
			if (work>0) b_sort();
	};
	
	std::vector<std::shared_ptr<std::thread>> threads2;

	for (unsigned int i = 1; i < numCores; ++i) {
		threads2.push_back(std::make_shared<std::thread>(b_sort));
	}

	b_sort();
	
	numbersToSort.clear();
	numbersToSort.reserve(vecs[1].size() + vecs[2].size() + vecs[3].size() + vecs[4].size() + vecs[5].size()
												+ vecs[6].size() + vecs[7].size() + vecs[8].size() + vecs[9].size());

	for (auto t : threads2) {
		t->join();
	}
	
	numbersToSort = std::move(vecs[1]);
    std::move(std::begin(vecs[2]), std::end(vecs[2]), std::back_inserter(numbersToSort));
    std::move(std::begin(vecs[3]), std::end(vecs[3]), std::back_inserter(numbersToSort));
    std::move(std::begin(vecs[4]), std::end(vecs[4]), std::back_inserter(numbersToSort));
    std::move(std::begin(vecs[5]), std::end(vecs[5]), std::back_inserter(numbersToSort));
    std::move(std::begin(vecs[6]), std::end(vecs[6]), std::back_inserter(numbersToSort));
    std::move(std::begin(vecs[7]), std::end(vecs[7]), std::back_inserter(numbersToSort));
    std::move(std::begin(vecs[8]), std::end(vecs[8]), std::back_inserter(numbersToSort));
    std::move(std::begin(vecs[9]), std::end(vecs[9]), std::back_inserter(numbersToSort));

}
