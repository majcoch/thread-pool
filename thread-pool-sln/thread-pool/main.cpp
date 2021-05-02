#include <iostream>
#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <functional>

#include "algorithm.h"


void generate_random_data(std::vector<int>& v);

int main(int argc, char* argv[]) {
	thread_pool pool(5);
	std::cout << "Starting execution with " << pool.get_thread_count() << " threads" << std::endl;

	std::vector<int> v(10);
	generate_random_data(v);


	system("pause");
	return 0;
}

void generate_random_data(std::vector<int> &v) {
	std::random_device rnd_device;
	std::mt19937 mersenne_engine{ rnd_device() };
	std::uniform_int_distribution<int> dist{ 1, 52 };
	auto gen = [&dist, &mersenne_engine]() { return dist(mersenne_engine); };
	generate(begin(v), end(v), gen);
}