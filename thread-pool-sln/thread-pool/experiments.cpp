#include "experiments.h"

struct Comma final : std::numpunct<char>
{
	char do_decimal_point() const override { return ','; }
};

void generate_random_data(std::vector<int>& v) {
	std::random_device rnd_device;
	std::mt19937 mersenne_engine{ rnd_device() };
	std::uniform_int_distribution<int> dist{ 1, 52 };
	auto gen = [&dist, &mersenne_engine]() { return dist(mersenne_engine); };
	generate(begin(v), end(v), gen);
}

bool is_even(int i) {
	return i % 2 == 0;
}

void fun_operation(int& i) {
	i = i + (int)sqrt(i + 3) - (i % 15);
}

bool compare(int a, int b) {
	return a > b;
}

std::tuple<std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>>
evaluate_find(std::vector<int> &test_data, thread_pool& pool, unsigned long granulation) {
	// Run parallel algorithm
	std::chrono::steady_clock::time_point start_p = std::chrono::high_resolution_clock::now();
	auto p_res = find(test_data.begin(), test_data.end(), 7, pool, granulation);
	std::chrono::steady_clock::time_point finish_p = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> elapsed_p = finish_p - start_p;

	// Run sequential algorithm
	std::chrono::steady_clock::time_point start_s = std::chrono::high_resolution_clock::now();
	auto s_res = std::find(test_data.begin(), test_data.end(), 7);
	std::chrono::steady_clock::time_point finish_s = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> elapsed_s = finish_s - start_s;

	// Verify results
	if (p_res != s_res) throw std::exception::exception();

	return std::make_tuple(elapsed_p, elapsed_s);
}

std::tuple<std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>>
evaluate_find_if(std::vector<int> &test_data, thread_pool& pool, unsigned long granulation) {
	// Run parallel algorithm
	std::chrono::steady_clock::time_point start_p = std::chrono::high_resolution_clock::now();
	auto p_res = find_if(test_data.begin(), test_data.end(), is_even, pool, granulation);
	std::chrono::steady_clock::time_point finish_p = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> elapsed_p = finish_p - start_p;

	// Run sequential algorithm
	std::chrono::steady_clock::time_point start_s = std::chrono::high_resolution_clock::now();
	auto s_res = std::find_if(test_data.begin(), test_data.end(), is_even);
	std::chrono::steady_clock::time_point finish_s = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> elapsed_s = finish_s - start_s;

	// Verify results
	if (p_res != s_res) throw std::exception::exception();

	return std::make_tuple(elapsed_p, elapsed_s);
}

std::tuple<std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>>
evaluate_find_if_not(std::vector<int> &test_data, thread_pool& pool, unsigned long granulation) {
	// Run parallel algorithm
	std::chrono::steady_clock::time_point start_p = std::chrono::high_resolution_clock::now();
	auto p_res = find_if_not(test_data.begin(), test_data.end(), is_even, pool, granulation);
	std::chrono::steady_clock::time_point finish_p = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> elapsed_p = finish_p - start_p;

	// Run sequential algorithm
	std::chrono::steady_clock::time_point start_s = std::chrono::high_resolution_clock::now();
	auto s_res = std::find_if_not(test_data.begin(), test_data.end(), is_even);
	std::chrono::steady_clock::time_point finish_s = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> elapsed_s = finish_s - start_s;

	// Verify results
	if (p_res != s_res) throw std::exception::exception();

	return std::make_tuple(elapsed_p, elapsed_s);
}

std::tuple<std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>>
evaluate_all_of(std::vector<int> &test_data, thread_pool& pool, unsigned long granulation) {
	// Run parallel algorithm
	std::chrono::steady_clock::time_point start_p = std::chrono::high_resolution_clock::now();
	auto p_res = all_of(test_data.begin(), test_data.end(), is_even, pool, granulation);
	std::chrono::steady_clock::time_point finish_p = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> elapsed_p = finish_p - start_p;

	// Run sequential algorithm
	std::chrono::steady_clock::time_point start_s = std::chrono::high_resolution_clock::now();
	auto s_res = std::all_of(test_data.begin(), test_data.end(), is_even);
	std::chrono::steady_clock::time_point finish_s = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> elapsed_s = finish_s - start_s;

	// Verify results
	if (p_res != s_res) throw std::exception::exception();

	return std::make_tuple(elapsed_p, elapsed_s);
}

std::tuple<std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>>
evaluate_any_of(std::vector<int> &test_data, thread_pool& pool, unsigned long granulation) {
	// Run parallel algorithm
	std::chrono::steady_clock::time_point start_p = std::chrono::high_resolution_clock::now();
	auto p_res = any_of(test_data.begin(), test_data.end(), is_even, pool, granulation);
	std::chrono::steady_clock::time_point finish_p = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> elapsed_p = finish_p - start_p;

	// Run sequential algorithm
	std::chrono::steady_clock::time_point start_s = std::chrono::high_resolution_clock::now();
	auto s_res = std::any_of(test_data.begin(), test_data.end(), is_even);
	std::chrono::steady_clock::time_point finish_s = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> elapsed_s = finish_s - start_s;

	// Verify results
	if (p_res != s_res) throw std::exception::exception();

	return std::make_tuple(elapsed_p, elapsed_s);
}

std::tuple<std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>>
evaluate_non_of(std::vector<int> &test_data, thread_pool& pool, unsigned long granulation) {
	// Run parallel algorithm
	std::chrono::steady_clock::time_point start_p = std::chrono::high_resolution_clock::now();
	auto p_res = none_of(test_data.begin(), test_data.end(), is_even, pool, granulation);
	std::chrono::steady_clock::time_point finish_p = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> elapsed_p = finish_p - start_p;

	// Run sequential algorithm
	std::chrono::steady_clock::time_point start_s = std::chrono::high_resolution_clock::now();
	auto s_res = std::none_of(test_data.begin(), test_data.end(), is_even);
	std::chrono::steady_clock::time_point finish_s = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> elapsed_s = finish_s - start_s;

	// Verify results
	if (p_res != s_res) throw std::exception::exception();

	return std::make_tuple(elapsed_p, elapsed_s);
}

std::tuple<std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>>
evaluate_count(std::vector<int> &test_data, thread_pool& pool, unsigned long granulation) {
	// Run parallel algorithm
	std::chrono::steady_clock::time_point start_p = std::chrono::high_resolution_clock::now();
	auto p_res = count(test_data.begin(), test_data.end(), 7, pool, granulation);
	std::chrono::steady_clock::time_point finish_p = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> elapsed_p = finish_p - start_p;

	// Run sequential algorithm
	std::chrono::steady_clock::time_point start_s = std::chrono::high_resolution_clock::now();
	auto s_res = std::count(test_data.begin(), test_data.end(), 7);
	std::chrono::steady_clock::time_point finish_s = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> elapsed_s = finish_s - start_s;

	// Verify results
	if (p_res != s_res) throw std::exception::exception();

	return std::make_tuple(elapsed_p, elapsed_s);
}

std::tuple<std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>>
evaluate_count_if(std::vector<int> &test_data, thread_pool& pool, unsigned long granulation) {
	// Run parallel algorithm
	std::chrono::steady_clock::time_point start_p = std::chrono::high_resolution_clock::now();
	auto p_res = count_if(test_data.begin(), test_data.end(), is_even, pool, granulation);
	std::chrono::steady_clock::time_point finish_p = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> elapsed_p = finish_p - start_p;

	// Run sequential algorithm
	std::chrono::steady_clock::time_point start_s = std::chrono::high_resolution_clock::now();
	auto s_res = std::count_if(test_data.begin(), test_data.end(), is_even);
	std::chrono::steady_clock::time_point finish_s = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> elapsed_s = finish_s - start_s;

	// Verify results
	if (p_res != s_res) throw std::exception::exception();

	return std::make_tuple(elapsed_p, elapsed_s);
}

std::tuple<std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>>
evaluate_for_each(std::vector<int> &test_data, thread_pool& pool, unsigned long granulation) {
	std::vector<int> control_data = test_data;

	// Run parallel algorithm
	std::chrono::steady_clock::time_point start_p = std::chrono::high_resolution_clock::now();
	for_each(test_data.begin(), test_data.end(), fun_operation, pool, granulation);
	std::chrono::steady_clock::time_point finish_p = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> elapsed_p = finish_p - start_p;

	// Run sequential algorithm
	std::chrono::steady_clock::time_point start_s = std::chrono::high_resolution_clock::now();
	std::for_each(control_data.begin(), control_data.end(), fun_operation);
	std::chrono::steady_clock::time_point finish_s = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> elapsed_s = finish_s - start_s;

	// Verify results
	if (memcmp(test_data.data(), control_data.data(), test_data.size())) throw std::exception::exception();

	return std::make_tuple(elapsed_p, elapsed_s);
}

std::tuple<std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>>
evaluate_accumulate(std::vector<int> &test_data, thread_pool& pool, unsigned long granulation) {
	// Run parallel algorithm
	std::chrono::steady_clock::time_point start_p = std::chrono::high_resolution_clock::now();
	auto p_res = accumulate(test_data.begin(), test_data.end(), 7, pool, granulation);
	std::chrono::steady_clock::time_point finish_p = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> elapsed_p = finish_p - start_p;

	// Run sequential algorithm
	std::chrono::steady_clock::time_point start_s = std::chrono::high_resolution_clock::now();
	auto s_res = std::accumulate(test_data.begin(), test_data.end(), 7);
	std::chrono::steady_clock::time_point finish_s = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> elapsed_s = finish_s - start_s;

	
	// Verify results
	if (p_res != s_res) throw std::exception::exception();

	return std::make_tuple(elapsed_p, elapsed_s);
}

std::tuple<std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>>
evaluate_sort(std::vector<int> &test_data, thread_pool& pool, unsigned long granulation) {
	std::vector<int> control_data = test_data;
	// Run parallel algorithm
	std::chrono::steady_clock::time_point start_p = std::chrono::high_resolution_clock::now();
	sort(test_data.begin(), test_data.end(), compare, pool, granulation);
	std::chrono::steady_clock::time_point finish_p = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> elapsed_p = finish_p - start_p;

	// Run sequential algorithm
	std::chrono::steady_clock::time_point start_s = std::chrono::high_resolution_clock::now();
	std::sort(control_data.begin(), control_data.end(), compare);
	std::chrono::steady_clock::time_point finish_s = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> elapsed_s = finish_s - start_s;

	// Verify results
	if (memcmp(test_data.data(), control_data.data(), test_data.size())) throw std::exception::exception();

	return std::make_tuple(elapsed_p, elapsed_s);
}

std::tuple<std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>>
evaluate_inner_product(std::vector<int> &test_data1, std::vector<int> &test_data2, thread_pool& pool, unsigned long granulation) {
	std::vector<int> control_data1 = test_data1;
	std::vector<int> control_data2 = test_data2;

	// Run parallel algorithm
	std::chrono::steady_clock::time_point start_p = std::chrono::high_resolution_clock::now();
	auto p_res = inner_product(test_data1.begin(), test_data1.end(), test_data2.begin(), 0, pool, granulation);
	std::chrono::steady_clock::time_point finish_p = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> elapsed_p = finish_p - start_p;

	// Run sequential algorithm
	std::chrono::steady_clock::time_point start_s = std::chrono::high_resolution_clock::now();
	auto s_res = std::inner_product(test_data1.begin(), test_data1.end(), test_data2.begin(), 0);
	std::chrono::steady_clock::time_point finish_s = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> elapsed_s = finish_s - start_s;

	// Verify results
	if (p_res != s_res) throw std::exception::exception();

	return std::make_tuple(elapsed_p, elapsed_s);
}

std::tuple<std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>>
evaluate_adjacent_difference(std::vector<int> &test_data1, std::vector<int> &test_data2, thread_pool& pool, unsigned long granulation) {
	std::vector<int> control_data1 = test_data1;
	std::vector<int> control_data2 = test_data2;

	// Run parallel algorithm
	std::chrono::steady_clock::time_point start_p = std::chrono::high_resolution_clock::now();
	auto p_res = adjacent_difference(test_data1.begin(), test_data1.end(), test_data2.begin(), pool, granulation);
	std::chrono::steady_clock::time_point finish_p = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> elapsed_p = finish_p - start_p;

	// Run sequential algorithm
	std::chrono::steady_clock::time_point start_s = std::chrono::high_resolution_clock::now();
	auto s_res = std::adjacent_difference(test_data1.begin(), test_data1.end(), test_data2.begin());
	std::chrono::steady_clock::time_point finish_s = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> elapsed_s = finish_s - start_s;

	// Verify results
	if (memcmp(test_data1.data(), control_data1.data(), test_data1.size())) throw std::exception::exception();

	return std::make_tuple(elapsed_p, elapsed_s);
}

void thread_number_experiment(size_t data_size, unsigned int granulation, unsigned int max_thread_count, unsigned int thread_step) {
	std::ofstream output_file;
	output_file.open("thread.csv", std::ios::out);
	if (output_file.is_open()) {
		// CSV file setup
		output_file.imbue(std::locale(std::locale::classic(), new Comma));
		output_file << "Exp. name;Threads;Granulation;Par. Exec. Time;Seq. Exec. Time;Valid" << std::endl;

		// Experiments setup
		std::cout << "Thread count experiment" << std::endl;
		std::cout << "Starting execution with granulation set to [" <<  granulation << "] packets." << std::endl;
		std::vector<int> v1(data_size);
		std::vector<int> v2(data_size);

		std::tuple<std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>> results;

		std::cout << "evaluate_find" << std::endl;
		for (unsigned int i = 1; i <= max_thread_count; i += thread_step) {
			// Create thread pool with thread count for experiment iteration
			thread_pool pool(i);
			// Perform experiment and record the result
			try {
				generate_random_data(v1);
				results = evaluate_find(v1, pool, granulation);
				output_file << "find;" << i << ";" << granulation << ";" <<  std::get<0>(results).count() << ";" << std::get<1>(results).count() << ";" << "1" << std::endl;
			}
			catch (const std::exception&) {
				output_file << "find;" << i << ";" << granulation << ";" << "-" << ";" << "-" << ";" << "0" << std::endl;
			}
		}

		std::cout << "evaluate_find_if" << std::endl;
		for (unsigned int i = 1; i <= max_thread_count; i += thread_step) {
			// Create thread pool with thread count for experiment iteration
			thread_pool pool(i);
			// Perform experiment and record the result
			try {
				generate_random_data(v1);
				results = evaluate_find_if(v1, pool, granulation);
				output_file << "find_if;" << i << ";" << granulation << ";" << std::get<0>(results).count() << ";" << std::get<1>(results).count() << ";" << "1" << std::endl;
			}
			catch (const std::exception&) {
				output_file << "find_if;" << i << ";" << granulation << ";" << "-" << ";" << "-" << ";" << "0" << std::endl;
			}
		}

		std::cout << "evaluate_find_if_not" << std::endl;
		for (unsigned int i = 1; i <= max_thread_count; i += thread_step) {
			// Create thread pool with thread count for experiment iteration
			thread_pool pool(i);
			// Perform experiment and record the result
			try {
				generate_random_data(v1);
				results = evaluate_find_if_not(v1, pool, granulation);
				output_file << "find_if_not;" << i << ";" << granulation << ";" << std::get<0>(results).count() << ";" << std::get<1>(results).count() << ";" << "1" << std::endl;
			}
			catch (const std::exception&) {
				output_file << "find_if_not;" << i << ";" << granulation << ";" << "-" << ";" << "-" << ";" << "0" << std::endl;
			}
		}

		std::cout << "evaluate_all_of" << std::endl;
		for (unsigned int i = 1; i <= max_thread_count; i += thread_step) {
			// Create thread pool with thread count for experiment iteration
			thread_pool pool(i);
			// Perform experiment and record the result
			try {
				generate_random_data(v1);
				results = evaluate_all_of(v1, pool, granulation);
				output_file << "all_of;" << i << ";" << granulation << ";" << std::get<0>(results).count() << ";" << std::get<1>(results).count() << ";" << "1" << std::endl;
			}
			catch (const std::exception&) {
				output_file << "all_of;" << i << ";" << granulation << ";" << "-" << ";" << "-" << ";" << "0" << std::endl;
			}
		}

		std::cout << "evaluate_any_of" << std::endl;
		for (unsigned int i = 1; i <= max_thread_count; i += thread_step) {
			// Create thread pool with thread count for experiment iteration
			thread_pool pool(i);
			// Perform experiment and record the result
			try {
				generate_random_data(v1);
				results = evaluate_any_of(v1, pool, granulation);
				output_file << "any_of;" << i << ";" << granulation << ";" << std::get<0>(results).count() << ";" << std::get<1>(results).count() << ";" << "1" << std::endl;
			}
			catch (const std::exception&) {
				output_file << "any_of;" << i << ";" << granulation << ";" << "-" << ";" << "-" << ";" << "0" << std::endl;
			}
		}

		std::cout << "evaluate_non_of" << std::endl;
		for (unsigned int i = 1; i <= max_thread_count; i += thread_step) {
			// Create thread pool with thread count for experiment iteration
			thread_pool pool(i);
			// Perform experiment and record the result
			try {
				generate_random_data(v1);
				results = evaluate_non_of(v1, pool, granulation);
				output_file << "non_of;" << i << ";" << granulation << ";" << std::get<0>(results).count() << ";" << std::get<1>(results).count() << ";" << "1" << std::endl;
			}
			catch (const std::exception&) {
				output_file << "non_of;" << i << ";" << granulation << ";" << "-" << ";" << "-" << ";" << "0" << std::endl;
			}
		}

		std::cout << "evaluate_count" << std::endl;
		for (unsigned int i = 1; i <= max_thread_count; i += thread_step) {
			// Create thread pool with thread count for experiment iteration
			thread_pool pool(i);
			// Perform experiment and record the result
			try {
				generate_random_data(v1);
				results = evaluate_count(v1, pool, granulation);
				output_file << "count;" << i << ";" << granulation << ";" << std::get<0>(results).count() << ";" << std::get<1>(results).count() << ";" << "1" << std::endl;
			}
			catch (const std::exception&) {
				output_file << "count;" << i << ";" << granulation << ";" << "-" << ";" << "-" << ";" << "0" << std::endl;
			}
		}

		std::cout << "evaluate_count_if" << std::endl;
		for (unsigned int i = 1; i <= max_thread_count; i += thread_step) {
			// Create thread pool with thread count for experiment iteration
			thread_pool pool(i);
			// Perform experiment and record the result
			try {
				generate_random_data(v1);
				results = evaluate_count_if(v1, pool, granulation);
				output_file << "count_if;" << i << ";" << granulation << ";" << std::get<0>(results).count() << ";" << std::get<1>(results).count() << ";" << "1" << std::endl;
			}
			catch (const std::exception&) {
				output_file << "count_if;" << i << ";" << granulation << ";" << "-" << ";" << "-" << ";" << "0" << std::endl;
			}
		}

		std::cout << "evaluate_for_each" << std::endl;
		for (unsigned int i = 1; i <= max_thread_count; i += thread_step) {
			// Create thread pool with thread count for experiment iteration
			thread_pool pool(i);
			// Perform experiment and record the result
			try {
				generate_random_data(v1);
				results = evaluate_for_each(v1, pool, granulation);
				output_file << "for_each;" << i << ";" << granulation << ";" << std::get<0>(results).count() << ";" << std::get<1>(results).count() << ";" << "1" << std::endl;
			}
			catch (const std::exception&) {
				output_file << "for_each;" << i << ";" << granulation << ";" << "-" << ";" << "-" << ";" << "0" << std::endl;
			}
		}

		std::cout << "evaluate_accumulate" << std::endl;
		for (unsigned int i = 1; i <= max_thread_count; i += thread_step) {
			// Create thread pool with thread count for experiment iteration
			thread_pool pool(i);
			// Perform experiment and record the result
			try {
				generate_random_data(v1);
				results = evaluate_accumulate(v1, pool, granulation);
				output_file << "accumulate;" << i << ";" << granulation << ";" << std::get<0>(results).count() << ";" << std::get<1>(results).count() << ";" << "1" << std::endl;
			}
			catch (const std::exception&) {
				output_file << "accumulate;" << i << ";" << granulation << ";" << "-" << ";" << "-" << ";" << "0" << std::endl;
			}
		}

		std::cout << "evaluate_sort" << std::endl;
		for (unsigned int i = 1; i <= max_thread_count; i += thread_step) {
			// Create thread pool with thread count for experiment iteration
			thread_pool pool(i);
			// Perform experiment and record the result
			try {
				generate_random_data(v1);
				results = evaluate_sort(v1, pool, granulation);
				output_file << "sort;" << i << ";" << granulation << ";" << std::get<0>(results).count() << ";" << std::get<1>(results).count() << ";" << "1" << std::endl;
			}
			catch (const std::exception&) {
				output_file << "sort;" << i << ";" << granulation << ";" << "-" << ";" << "-" << ";" << "0" << std::endl;
			}
		}

		std::cout << "evaluate_inner_product" << std::endl;
		for (unsigned int i = 1; i <= max_thread_count; i += thread_step) {
			// Create thread pool with thread count for experiment iteration
			thread_pool pool(i);
			// Perform experiment and record the result
			try {
				generate_random_data(v1);
				generate_random_data(v2);
				results = evaluate_inner_product(v1,v2, pool, granulation);
				output_file << "inner_product;" << i << ";" << granulation << ";" << std::get<0>(results).count() << ";" << std::get<1>(results).count() << ";" << "1" << std::endl;
			}
			catch (const std::exception&) {
				output_file << "inner_product;" << i << ";" << granulation << ";" << "-" << ";" << "-" << ";" << "0" << std::endl;
			}
		}

		std::cout << "evaluate_adjacent_difference" << std::endl;
		for (unsigned int i = 1; i <= max_thread_count; i += thread_step) {
			// Create thread pool with thread count for experiment iteration
			thread_pool pool(i);
			// Perform experiment and record the result
			try {
				generate_random_data(v1);
				generate_random_data(v2);
				results = evaluate_adjacent_difference(v1, v2, pool, granulation);
				output_file << "adjacent_difference;" << i << ";" << granulation << ";" << std::get<0>(results).count() << ";" << std::get<1>(results).count() << ";" << "1" << std::endl;
			}
			catch (const std::exception&) {
				output_file << "adjacent_difference;" << i << ";" << granulation << ";" << "-" << ";" << "-" << ";" << "0" << std::endl;
			}
		}

		output_file.close();
	}

}

void granulation_level_experiment(size_t data_size, unsigned int thread_count, unsigned int max_granulation, unsigned int granulation_step) {
	std::ofstream output_file;
	output_file.open("granulation.csv", std::ios::out);
	if (output_file.is_open()) {
		// CSV file setup
		output_file.imbue(std::locale(std::locale::classic(), new Comma));
		output_file << "Exp. name;Threads;Granulation;Par. Exec. Time;Seq. Exec. Time;Valid" << std::endl;

		// Experiments setup
		thread_pool pool(thread_count);
		std::cout << "Granulation level experiment" << std::endl;
		std::cout << "Starting execution with [" << pool.get_thread_count() << "] threads" << std::endl;
		std::vector<int> v1(data_size);
		std::vector<int> v2(data_size);
		

		std::tuple<std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>> results;

		std::cout << "evaluate_find" << std::endl;
		for (unsigned int i = granulation_step; i <= max_granulation; i += granulation_step) {
			// Perform experiment and record the result
			try {
				generate_random_data(v1);
				results = evaluate_find(v1, pool, i);
				output_file << "find;" << thread_count << ";" << i << ";" << std::get<0>(results).count() << ";" << std::get<1>(results).count() << ";" << "1" << std::endl;
			}
			catch (const std::exception&) {
				output_file << "find;" << thread_count << ";" << i << ";" << "-" << ";" << "-" << ";" << "0" << std::endl;
			}
		}

		std::cout << "evaluate_find_if" << std::endl;
		for (unsigned int i = granulation_step; i <= max_granulation; i += granulation_step) {
			// Perform experiment and record the result
			try {
				generate_random_data(v1);
				results = evaluate_find_if(v1, pool, i);
				output_file << "find_if;" << thread_count << ";" << i << ";" << std::get<0>(results).count() << ";" << std::get<1>(results).count() << ";" << "1" << std::endl;
			}
			catch (const std::exception&) {
				output_file << "find_if;" << thread_count << ";" << i << ";" << "-" << ";" << "-" << ";" << "0" << std::endl;
			}
		}

		std::cout << "evaluate_find_if_not" << std::endl;
		for (unsigned int i = granulation_step; i <= max_granulation; i += granulation_step) {
			// Perform experiment and record the result
			try {
				generate_random_data(v1);
				results = evaluate_find_if_not(v1, pool, i);
				output_file << "find_if_not;" << thread_count << ";" << i << ";" << std::get<0>(results).count() << ";" << std::get<1>(results).count() << ";" << "1" << std::endl;
			}
			catch (const std::exception&) {
				output_file << "find_if_not;" << thread_count << ";" << i << ";" << "-" << ";" << "-" << ";" << "0" << std::endl;
			}
		}

		std::cout << "evaluate_all_of" << std::endl;
		for (unsigned int i = granulation_step; i <= max_granulation; i += granulation_step) {
			// Perform experiment and record the result
			try {
				generate_random_data(v1);
				results = evaluate_all_of(v1, pool, i);
				output_file << "all_of;" << thread_count << ";" << i << ";" << std::get<0>(results).count() << ";" << std::get<1>(results).count() << ";" << "1" << std::endl;
			}
			catch (const std::exception&) {
				output_file << "all_of;" << thread_count << ";" << i << ";" << "-" << ";" << "-" << ";" << "0" << std::endl;
			}
		}

		std::cout << "evaluate_any_of" << std::endl;
		for (unsigned int i = granulation_step; i <= max_granulation; i += granulation_step) {
			// Perform experiment and record the result
			try {
				generate_random_data(v1);
				results = evaluate_any_of(v1, pool, i);
				output_file << "any_of;" << thread_count << ";" << i << ";" << std::get<0>(results).count() << ";" << std::get<1>(results).count() << ";" << "1" << std::endl;
			}
			catch (const std::exception&) {
				output_file << "any_of;" << thread_count << ";" << i << ";" << "-" << ";" << "-" << ";" << "0" << std::endl;
			}
		}

		std::cout << "evaluate_non_of" << std::endl;
		for (unsigned int i = granulation_step; i <= max_granulation; i += granulation_step) {
			// Perform experiment and record the result
			try {
				generate_random_data(v1);
				results = evaluate_non_of(v1, pool, i);
				output_file << "non_of;" << thread_count << ";" << i << ";" << std::get<0>(results).count() << ";" << std::get<1>(results).count() << ";" << "1" << std::endl;
			}
			catch (const std::exception&) {
				output_file << "non_of;" << thread_count << ";" << i << ";" << "-" << ";" << "-" << ";" << "0" << std::endl;
			}
		}

		std::cout << "evaluate_count" << std::endl;
		for (unsigned int i = granulation_step; i <= max_granulation; i += granulation_step) {
			// Perform experiment and record the result
			try {
				generate_random_data(v1);
				results = evaluate_count(v1, pool, i);
				output_file << "count;" << thread_count << ";" << i << ";" << std::get<0>(results).count() << ";" << std::get<1>(results).count() << ";" << "1" << std::endl;
			}
			catch (const std::exception&) {
				output_file << "count;" << thread_count << ";" << i << ";" << "-" << ";" << "-" << ";" << "0" << std::endl;
			}
		}

		std::cout << "evaluate_count_if" << std::endl;
		for (unsigned int i = granulation_step; i <= max_granulation; i += granulation_step) {
			// Perform experiment and record the result
			try {
				generate_random_data(v1);
				results = evaluate_count_if(v1, pool, i);
				output_file << "count_if;" << thread_count << ";" << i << ";" << std::get<0>(results).count() << ";" << std::get<1>(results).count() << ";" << "1" << std::endl;
			}
			catch (const std::exception&) {
				output_file << "count_if;" << thread_count << ";" << i << ";" << "-" << ";" << "-" << ";" << "0" << std::endl;
			}
		}

		std::cout << "evaluate_for_each" << std::endl;
		for (unsigned int i = granulation_step; i <= max_granulation; i += granulation_step) {
			// Perform experiment and record the result
			try {
				generate_random_data(v1);
				results = evaluate_for_each(v1, pool, i);
				output_file << "for_each;" << thread_count << ";" << i << ";" << std::get<0>(results).count() << ";" << std::get<1>(results).count() << ";" << "1" << std::endl;
			}
			catch (const std::exception&) {
				output_file << "for_each;" << thread_count << ";" << i << ";" << "-" << ";" << "-" << ";" << "0" << std::endl;
			}
		}

		std::cout << "evaluate_accumulate" << std::endl;
		for (unsigned int i = granulation_step; i <= max_granulation; i += granulation_step) {
			// Perform experiment and record the result
			try {
				generate_random_data(v1);
				results = evaluate_accumulate(v1, pool, i);
				output_file << "accumulate;" << thread_count << ";" << i << ";" << std::get<0>(results).count() << ";" << std::get<1>(results).count() << ";" << "1" << std::endl;
			}
			catch (const std::exception&) {
				output_file << "accumulate;" << thread_count << ";" << i << ";" << "-" << ";" << "-" << ";" << "0" << std::endl;
			}
		}

		std::cout << "evaluate_sort" << std::endl;
		for (unsigned int i = granulation_step; i <= max_granulation; i += granulation_step) {
			// Perform experiment and record the result
			try {
				generate_random_data(v1);
				results = evaluate_sort(v1, pool, i);
				output_file << "sort;" << thread_count << ";" << i << ";" << std::get<0>(results).count() << ";" << std::get<1>(results).count() << ";" << "1" << std::endl;
			}
			catch (const std::exception&) {
				output_file << "sort;" << thread_count << ";" << i << ";" << "-" << ";" << "-" << ";" << "0" << std::endl;
			}
		}

		std::cout << "evaluate_inner_product" << std::endl;
		for (unsigned int i = granulation_step; i <= max_granulation; i += granulation_step) {
			// Perform experiment and record the result
			try {
				generate_random_data(v1);
				generate_random_data(v2);
				results = evaluate_inner_product(v1, v2, pool, i);
				output_file << "inner_product;" << thread_count << ";" << i << ";" << std::get<0>(results).count() << ";" << std::get<1>(results).count() << ";" << "1" << std::endl;
			}
			catch (const std::exception&) {
				output_file << "inner_product;" << thread_count << ";" << i << ";" << "-" << ";" << "-" << ";" << "0" << std::endl;
			}
		}

		std::cout << "evaluate_adjacent_difference" << std::endl;
		for (unsigned int i = granulation_step; i <= max_granulation; i += granulation_step) {
			// Perform experiment and record the result
			try {
				generate_random_data(v1);
				generate_random_data(v2);
				results = evaluate_adjacent_difference(v1, v2, pool, i);
				output_file << "adjacent_difference;" << thread_count << ";" << i << ";" << std::get<0>(results).count() << ";" << std::get<1>(results).count() << ";" << "1" << std::endl;
			}
			catch (const std::exception&) {
				output_file << "adjacent_difference;" << thread_count << ";" << i << ";" << "-" << ";" << "-" << ";" << "0" << std::endl;
			}
		}

		output_file.close();
	}
}

