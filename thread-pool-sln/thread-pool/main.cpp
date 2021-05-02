#include <iostream>
#include <algorithm>
#include "algorithm.h"

bool is_even(int i) {
	return (0 == i % 2);
}

int main(int argc, char* argv[]) {
	thread_pool pool(5);
	std::cout << "Starting execution with " << pool.get_thread_count() << " threads" << std::endl;

	std::vector<int> v = std::vector<int>(100000000);
	std::fill(v.begin(), v.end(), 2);
	
	// Sequential
	auto start = std::chrono::high_resolution_clock::now();
	bool s_result = std::all_of(v.begin(), v.end(), is_even);
	auto finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> s_elapsed = finish - start;
	std::cout << "Sequential: " << s_elapsed.count() << "ms" << std::endl;
	std::cout << "Result " << s_result << std::endl;

	// Parallel
	start = std::chrono::high_resolution_clock::now();
	bool p_result = all_of(v.begin(), v.end(), is_even, pool);
	finish = std::chrono::high_resolution_clock::now(); 
	std::chrono::duration<double, std::milli> p_elapsed = finish - start;
	std::cout << "Parallel: " << p_elapsed.count() << "ms" << std::endl;
	std::cout << "Result " << p_result << std::endl;

	system("pause");
	return 0;
}