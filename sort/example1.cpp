#include <iostream>
#include <thread>

void counter(int numIterations) {
	for (int i = 0; i < numIterations; ++i) {
		std::cout << "Thread id: " << std::this_thread::get_id();
		std::cout << " value = " << i << std::endl;
	}
}

int main() {
	std::thread t1{counter, 6};	// start two threads
	std::thread t2{counter, 4};
	counter(2);	// call counter on the main thread
	t1.join();	// wait for the two threads to end. 
	t2.join();
}
