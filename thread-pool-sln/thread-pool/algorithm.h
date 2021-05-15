#pragma once
#include "thread_pool.h"
#include <algorithm>
#include <numeric>

template<class InputIt, class T>
constexpr InputIt find(InputIt first, InputIt last, const T& value, thread_pool& pool, const unsigned long packets = 0) {
	// Setup
	size_t packet_count = 0;
	if (0 == packets) {
		packet_count = pool.get_thread_count();
	}
	else {
		packet_count = packets;
	}
	size_t data_size = std::distance(first, last);
	size_t packet_size = (size_t)fmax(1, (data_size / packet_count));
	size_t last_packet_size = packet_size == 1 ? 0 : data_size % packet_count;

	// Dispatch
	std::vector<std::future<InputIt>> thread_results;
	InputIt partial_first = first;
	InputIt partial_last = first;
	for (size_t data = packet_size; data <= data_size - last_packet_size; data += packet_size) {
		partial_last += packet_size;
		thread_results.push_back(
			pool.add_task(std::find<InputIt, T>, partial_first, partial_last, value));
		partial_first += packet_size;
	}
	if (0 != last_packet_size) {
		partial_last = partial_first + last_packet_size;
		thread_results.push_back(
			pool.add_task(std::find<InputIt, T>, partial_first, partial_last, value));
	}

	// Collect
	partial_last = first + packet_size;
	size_t data_to_collect = data_size - last_packet_size - packet_size;
	for (size_t i = 0; i < thread_results.size(); i++) {
		InputIt result = thread_results[i].get();
		// Rsult found
		if (result != partial_last) return result;
		// Proceed to next check
		if (data_to_collect > 0) {
			partial_last += packet_size;
			data_to_collect -= packet_size;
		}
		else {
			partial_last += last_packet_size;
		}
	}

	return last;
}

template<class InputIt, class UnaryPredicate>
constexpr InputIt find_if(InputIt first, InputIt last, UnaryPredicate p, thread_pool& pool, const unsigned long packets = 0) {
	// Setup
	size_t packet_count = 0;
	if (0 == packets) {
		packet_count = pool.get_thread_count();
	}
	else {
		packet_count = packets;
	}
	size_t data_size = std::distance(first, last);
	size_t packet_size = (size_t)fmax(1, (data_size / packet_count));
	size_t last_packet_size = packet_size == 1 ? 0 : data_size % packet_count;

	// Dispatch
	std::vector<std::future<InputIt>> thread_results;
	InputIt partial_first = first;
	InputIt partial_last = first;
	for (size_t data = packet_size; data <= data_size - last_packet_size; data += packet_size) {
		partial_last += packet_size;
		thread_results.push_back(
			pool.add_task(std::find_if<InputIt, UnaryPredicate>, partial_first, partial_last, p));
		partial_first += packet_size;
	}
	if (0 != last_packet_size) {
		partial_last = partial_first + last_packet_size;
		thread_results.push_back(
			pool.add_task(std::find_if<InputIt, UnaryPredicate>, partial_first, partial_last, p));
	}

	// Collect
	partial_last = first + packet_size;
	size_t data_to_collect = data_size - last_packet_size - packet_size;
	for (size_t i = 0; i < thread_results.size(); i++) {
		InputIt result = thread_results[i].get();
		// Rsult found
		if (result != partial_last) return result;
		// Proceed to next check
		if (data_to_collect > 0) {
			partial_last += packet_size;
			data_to_collect -= packet_size;
		}
		else {
			partial_last += last_packet_size;
		}
	}

	return last;
}

template<class InputIt, class UnaryPredicate>
constexpr InputIt find_if_not(InputIt first, InputIt last, UnaryPredicate p, thread_pool& pool, const unsigned long packets = 0) {
	// Setup
	size_t packet_count = 0;
	if (0 == packets) {
		packet_count = pool.get_thread_count();
	}
	else {
		packet_count = packets;
	}
	size_t data_size = std::distance(first, last);
	size_t packet_size = (size_t)fmax(1, (data_size / packet_count));
	size_t last_packet_size = packet_size == 1 ? 0 : data_size % packet_count;

	// Dispatch
	std::vector<std::future<InputIt>> thread_results;
	InputIt partial_first = first;
	InputIt partial_last = first;
	for (size_t data = packet_size; data <= data_size - last_packet_size; data += packet_size) {
		partial_last += packet_size;
		thread_results.push_back(
			pool.add_task(std::find_if_not<InputIt, UnaryPredicate>, partial_first, partial_last, p));
		partial_first += packet_size;
	}
	if (0 != last_packet_size) {
		partial_last = partial_first + last_packet_size;
		thread_results.push_back(
			pool.add_task(std::find_if_not<InputIt, UnaryPredicate>, partial_first, partial_last, p));
	}

	// Collect
	partial_last = first + packet_size;
	size_t data_to_collect = data_size - last_packet_size - packet_size;
	for (size_t i = 0; i < thread_results.size(); i++) {
		InputIt result = thread_results[i].get();
		// Rsult found
		if (result != partial_last) return result;
		// Proceed to next check
		if (data_to_collect > 0) {
			partial_last += packet_size;
			data_to_collect -= packet_size;
		}
		else {
			partial_last += last_packet_size;
		}
	}

	return last;
}

template<class InputIt, class UnaryPredicate>
constexpr bool all_of(InputIt first, InputIt last, UnaryPredicate p, thread_pool& pool, const unsigned long packets = 0) {
	return find_if_not(first, last, p, pool, packets) == last;
}

template<class InputIt, class UnaryPredicate>
constexpr bool any_of(InputIt first, InputIt last, UnaryPredicate p, thread_pool& pool, const unsigned long packets = 0) {
	return find_if(first, last, p, pool, packets) != last;
}

template<class InputIt, class UnaryPredicate>
constexpr bool none_of(InputIt first, InputIt last, UnaryPredicate p, thread_pool& pool, const unsigned long packets = 0) {
	return find_if(first, last, p, pool, packets) == last;
}

template<class InputIt, class T>
typename std::iterator_traits<InputIt>::difference_type
count(InputIt first, InputIt last, const T& value, thread_pool& pool, const unsigned long packets = 0) {
	size_t packet_count = 0;
	if (0 == packets) {
		packet_count = pool.get_thread_count();
	}
	else {
		packet_count = packets;
	}
	size_t data_size = std::distance(first, last);
	size_t packet_size = (size_t)fmax(1, (data_size / packet_count));
	size_t last_packet_size = packet_size == 1 ? 0 : data_size % packet_count;

	std::vector<std::future<std::iterator_traits<InputIt>::difference_type>> thread_results;
	InputIt partial_first = first;
	InputIt partial_last = first;
	for (size_t data = packet_size; data <= data_size - last_packet_size; data += packet_size) {
		partial_last += packet_size;
		thread_results.push_back(
			pool.add_task(std::count<InputIt, T>, partial_first, partial_last, value));
		partial_first += packet_size;
	}
	if (0 != last_packet_size) {
		partial_last = partial_first + last_packet_size;
		thread_results.push_back(
			pool.add_task(std::count<InputIt, T>, partial_first, partial_last, value));
	}

	typename std::iterator_traits<InputIt>::difference_type res = 0;
	for (unsigned int thread = 0; thread < thread_results.size(); thread++) {
		 res += thread_results[thread].get();
	}

	return res;
}

template<class InputIt, class UnaryPredicate>
typename std::iterator_traits<InputIt>::difference_type
count_if(InputIt first, InputIt last, UnaryPredicate p, thread_pool& pool, const unsigned long packets = 0) {
	size_t packet_count = 0;
	if (0 == packets) {
		packet_count = pool.get_thread_count();
	}
	else {
		packet_count = packets;
	}
	size_t data_size = std::distance(first, last);
	size_t packet_size = (size_t)fmax(1, (data_size / packet_count));
	size_t last_packet_size = packet_size == 1 ? 0 : data_size % packet_count;

	std::vector<std::future<std::iterator_traits<InputIt>::difference_type>> thread_results;
	InputIt partial_first = first;
	InputIt partial_last = first;
	for (size_t data = packet_size; data <= data_size - last_packet_size; data += packet_size) {
		partial_last += packet_size;
		thread_results.push_back(
			pool.add_task(std::count_if<InputIt, UnaryPredicate>, partial_first, partial_last, p));
		partial_first += packet_size;
	}
	if (0 != last_packet_size) {
		partial_last = partial_first + last_packet_size;
		thread_results.push_back(
			pool.add_task(std::count_if<InputIt, UnaryPredicate>, partial_first, partial_last, p));
	}

	typename std::iterator_traits<InputIt>::difference_type res = 0;
	for (unsigned int thread = 0; thread < thread_results.size(); thread++) {
		res += thread_results[thread].get();
	}

	return res;
}

template<class InputIt, class UnaryFunction>
constexpr UnaryFunction for_each(InputIt first, InputIt last, UnaryFunction f, thread_pool& pool, const unsigned long packets = 0) {
	size_t packet_count = 0;
	if (0 == packets) {
		packet_count = pool.get_thread_count();
	}
	else {
		packet_count = packets;
	}
	size_t data_size = std::distance(first, last);
	size_t packet_size = (size_t)fmax(1, (data_size / packet_count));
	size_t last_packet_size = packet_size == 1 ? 0 : data_size % packet_count;
	
	std::vector<std::future<UnaryFunction>> thread_results;
	InputIt partial_first = first;
	InputIt partial_last = first;
	for (size_t data = packet_size; data <= data_size - last_packet_size; data += packet_size) {
		partial_last += packet_size;
		thread_results.push_back(
			pool.add_task(std::for_each<InputIt, UnaryFunction> , partial_first, partial_last, f));
		partial_first += packet_size;
	}
	if (0 != last_packet_size) {
		partial_last = partial_first + last_packet_size;
		thread_results.push_back(
			pool.add_task(std::for_each<InputIt, UnaryFunction>, partial_first, partial_last, f));
	}

	for (unsigned int thread = 0; thread < thread_results.size(); thread++) {
		thread_results[thread].get();
	}

	return f;
}

template<class InputIt, class OutputIt, class UnaryOperation>
OutputIt transform(InputIt first1, InputIt last1, OutputIt d_first, UnaryOperation unary_op, thread_pool& pool, const unsigned long packets = 0) {
	size_t packet_count = 0;
	if (0 == packets) {
		packet_count = pool.get_thread_count();
	}
	else {
		packet_count = packets;
	}
	size_t data_size = std::distance(first1, last1);
	size_t packet_size = fmax(1, (data_size / packet_count));
	size_t last_packet_size = packet_size == 1 ? 0 : data_size % packet_count;

	std::vector<std::future<OutputIt>> thread_results;
	InputIt partial1_first = first1;
	InputIt partial1_last = first1;
	OutputIt partial2_first = d_first;
	for (size_t data = packet_size; data <= data_size - last_packet_size; data += packet_size) {
		partial1_last += packet_size;
		thread_results.push_back(
			pool.add_task(std::transform<InputIt, OutputIt, UnaryOperation>, partial1_first, partial1_last, partial2_first, unary_op));
		partial1_first += packet_size;
		partial2_first += packet_size;
	}
	if (0 != last_packet_size) {
		partial1_last = partial1_first + last_packet_size;
		thread_results.push_back(
			pool.add_task(std::transform<InputIt, OutputIt, UnaryOperation>, partial1_first, partial1_last, partial2_first, unary_op));
	}

	for (unsigned int thread = 0; thread < thread_results.size(); thread++) {
		thread_results[thread].get();
	}

	return d_first;
}

template<class RandomIt, class Compare>
constexpr void sort(RandomIt first, RandomIt last, Compare comp, thread_pool& pool, const unsigned long packets = 0) {
	size_t packet_count = 0;
	if (0 == packets) {
		packet_count = pool.get_thread_count();
	}
	else {
		packet_count = packets;
	}
	size_t data_size = std::distance(first, last);
	size_t packet_size = fmax(1, (data_size / packet_count));
	size_t last_packet_size = packet_size == 1 ? 0 : data_size % packet_count;

	std::vector<std::future<void>> thread_results;
	RandomIt partial_first = first;
	RandomIt partial_last = first;
	for (size_t data = packet_size; data <= data_size - last_packet_size; data += packet_size) {
		partial_last += packet_size;
		thread_results.push_back(
			pool.add_task(std::sort<RandomIt, Compare>, partial_first, partial_last, comp));
		partial_first += packet_size;
	}
	if (0 != last_packet_size) {
		partial_last = partial_first + last_packet_size;
		thread_results.push_back(
			pool.add_task(std::sort<RandomIt, Compare>, partial_first, partial_last, comp));
	}

	// get all sub-sorted data
	for (unsigned int thread = 0; thread < thread_results.size(); thread++) {
		thread_results[thread].get();
	}

	// merge results
	long long packets_sorted = thread_results.size() - 1;
	if (0 != last_packet_size) packets_sorted -= 1;
	for (long long part = 1; part <= packets_sorted; part++) {
		std::inplace_merge(first, first + (part * packet_size), first + ((part + 1) * packet_size), comp);
	}
	if (0 != last_packet_size) {
		std::inplace_merge(first, first + ((packets_sorted + 1) * packet_size), last, comp);
	}
}

template<class InputIt, class T>
constexpr T accumulate(InputIt first, InputIt last, T init, thread_pool& pool, const unsigned long packets = 0) {
	size_t packet_count = 0;
	if (0 == packets) {
		packet_count = pool.get_thread_count();
	}
	else {
		packet_count = packets;
	}
	size_t data_size = std::distance(first, last);
	size_t packet_size = (size_t)fmax(1, (data_size / packet_count));
	size_t last_packet_size = packet_size == 1 ? 0 : data_size % packet_count;

	std::vector<std::future<T>> thread_results;
	InputIt partial_first = first;
	InputIt partial_last = first;
	for (size_t data = packet_size; data <= data_size - last_packet_size; data += packet_size) {
		partial_last += packet_size;
		thread_results.push_back(
			pool.add_task(std::accumulate<InputIt, T>, partial_first, partial_last, 0));
		partial_first += packet_size;
	}
	if (0 != last_packet_size) {
		partial_last = partial_first + last_packet_size;
		thread_results.push_back(
			pool.add_task(std::accumulate<InputIt, T>, partial_first, partial_last, 0));
	}

	for (unsigned int thread = 0; thread < thread_results.size(); thread++) {
		init += thread_results[thread].get();
	}

	return init;
}

template<class InputIt1, class InputIt2, class T>
constexpr T inner_product(InputIt1 first1, InputIt1 last1, InputIt2 first2, T init, thread_pool& pool, const unsigned long packets = 0) {
	size_t packet_count = 0;
	if (0 == packets) {
		packet_count = pool.get_thread_count();
	}
	else {
		packet_count = packets;
	}
	size_t data_size = std::distance(first1, last1);
	size_t packet_size = (size_t)fmax(1, (data_size / packet_count));
	size_t last_packet_size = packet_size == 1 ? 0 : data_size % packet_count;

	std::vector<std::future<T>> thread_results;
	InputIt1 partial1_first = first1;
	InputIt1 partial1_last = first1;
	InputIt2 partial2_first = first2;
	for (size_t data = packet_size; data <= data_size - last_packet_size; data += packet_size) {
		partial1_last += packet_size;
		thread_results.push_back(
			pool.add_task(std::inner_product<InputIt1, InputIt2, T>, partial1_first, partial1_last, partial2_first, 0));
		partial1_first += packet_size;
		partial2_first += packet_size;
	}
	if (0 != last_packet_size) {
		partial1_last = partial1_first + last_packet_size;
		thread_results.push_back(
			pool.add_task(std::inner_product<InputIt1, InputIt2, T>, partial1_first, partial1_last, partial2_first, 0));
	}

	for (unsigned int thread = 0; thread < thread_results.size(); thread++) {
		init += thread_results[thread].get();
	}

	return init;
}

template<class InputIt, class OutputIt>
constexpr OutputIt adjacent_difference(InputIt first, InputIt last, OutputIt d_first, thread_pool& pool, const unsigned long packets = 0){ 
	size_t packet_count = 0;
	if (0 == packets) {
		packet_count = pool.get_thread_count();
	}
	else {
		packet_count = packets;
	}
	size_t data_size = std::distance(first, last);
	size_t packet_size = (size_t)fmax(1, (data_size / packet_count));
	size_t last_packet_size = packet_size == 1 ? 0 : data_size % packet_count;

	std::vector<std::future<OutputIt>> thread_results;
	InputIt partial1_first = first;
	InputIt partial1_last = first;
	OutputIt partial2_first = d_first;
	for (size_t data = packet_size; data <= data_size - last_packet_size; data += packet_size) {
		partial1_last += packet_size;
		thread_results.push_back(
			pool.add_task(std::adjacent_difference<InputIt, OutputIt>, partial1_first, partial1_last, partial2_first));
		partial1_first += packet_size;
		partial2_first += packet_size;
	}
	if (0 != last_packet_size) {
		partial1_last = partial1_first + last_packet_size;
		thread_results.push_back(
			pool.add_task(std::adjacent_difference<InputIt, OutputIt>, partial1_first, partial1_last, partial2_first));
	}

	for (unsigned int thread = 0; thread < thread_results.size(); thread++) {
		thread_results[thread].get();
	}

	return ++d_first;
}
