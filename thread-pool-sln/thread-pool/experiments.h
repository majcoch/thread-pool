#pragma once
#include <iostream>
#include <fstream>
#include <algorithm>
#include <random>
#include <chrono>

#include "algorithm.h"

void thread_number_experiment(size_t data_size, unsigned int granulation, unsigned int max_thread_count, unsigned int thread_step);

void granulation_level_experiment(size_t data_size, unsigned int thread_count, unsigned int max_granulation, unsigned int granulation_step);
