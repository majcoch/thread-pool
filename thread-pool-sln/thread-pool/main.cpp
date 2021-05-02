#include <iostream>
#include "thread_pool.h"


int main(int argc, char* argv[]) {
	thread_pool pool;
	std::cout << "Starting execution with " << pool.get_thread_count() << " threads" << std::endl;

	return 0;
}