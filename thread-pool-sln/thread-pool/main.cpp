#include "experiments.h"

int main(int argc, char* argv[]) {

	size_t data_size = 100000000;

	unsigned int granulation = 5;
	unsigned int thread_max = 20;
	unsigned int thread_step = 1;
	thread_number_experiment(data_size, granulation, thread_max, thread_step);

	unsigned int thread_count = 5;
	unsigned int granulation_max = 20;
	unsigned int granulation_step = 1;
	granulation_level_experiment(data_size, thread_count, granulation_max, granulation_step);

	return 0;
}