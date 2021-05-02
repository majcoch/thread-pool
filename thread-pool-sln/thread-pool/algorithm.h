#pragma once
#include "thread_pool.h"

template<class InputIt, class T>
constexpr InputIt find(InputIt first, InputIt last, const T& value, thread_pool& pool) {
	unsigned int avaliable_threads = pool.get_thread_count();
	size_t length = std::distance(first, last);
	size_t portion = length / avaliable_threads;

	std::vector<std::future<InputIt>> partial_results = std::vector<std::future<InputIt>>(avaliable_threads);
	for (unsigned int thread = 0; thread < avaliable_threads; thread++) {
		InputIt partial_first = first + (thread * portion);
		InputIt partial_last = first + ((thread + 1) * portion);
		partial_results[thread] = pool.add_task([](InputIt first, InputIt last, const T & value) {
			for (; first != last; ++first) {
				if (*first == value) {
					return first;
				}
			}
			return last;
		}, partial_first, partial_last, value);
	}

	for (unsigned int thread = 0; thread < avaliable_threads; thread++) {
		InputIt partial_last = first + ((thread + 1) * portion);
		InputIt result = partial_results[thread].get();
		if (result != partial_last) return result;
	}
	return last;
}

template<class InputIt, class UnaryPredicate>
constexpr InputIt find_if(InputIt first, InputIt last, UnaryPredicate p, thread_pool& pool) {
	unsigned int avaliable_threads = pool.get_thread_count();
	size_t length = std::distance(first, last);
	size_t portion = length / avaliable_threads;

	std::vector<std::future<InputIt>> partial_results = std::vector<std::future<InputIt>>(avaliable_threads);
	for (unsigned int thread = 0; thread < avaliable_threads; thread++) {
		InputIt partial_first = first + (thread * portion);
		InputIt partial_last = first + ((thread + 1) * portion);
		partial_results[thread] = pool.add_task([](InputIt first, InputIt last, UnaryPredicate p) {
			for (; first != last; ++first) {
				if (p(*first)) {
					return first;
				}
			}
			return last;
		}, partial_first, partial_last, p);
	}

	for (unsigned int thread = 0; thread < avaliable_threads; thread++) {
		InputIt partial_last = first + ((thread + 1) * portion);
		InputIt result = partial_results[thread].get();
		if (result != partial_last) return result;
	}
	return last;
}

template<class InputIt, class UnaryPredicate>
constexpr InputIt find_if_not(InputIt first, InputIt last, UnaryPredicate p, thread_pool& pool) {
	unsigned int avaliable_threads = pool.get_thread_count();
	size_t length = std::distance(first, last);
	size_t portion = length / avaliable_threads;

	std::vector<std::future<InputIt>> partial_results = std::vector<std::future<InputIt>>(avaliable_threads);
	for (unsigned int thread = 0; thread < avaliable_threads; thread++) {
		InputIt partial_first = first + (thread * portion);
		InputIt partial_last = first + ((thread + 1) * portion);
		partial_results[thread] = pool.add_task([](InputIt first, InputIt last, UnaryPredicate p) {
			for (; first != last; ++first) {
				if (!p(*first)) {
					return first;
				}
			}
			return last;
		}, partial_first, partial_last, p);
	}

	for (unsigned int thread = 0; thread < avaliable_threads; thread++) {
		InputIt partial_last = first + ((thread + 1) * portion);
		InputIt result = partial_results[thread].get();
		if (result != partial_last) return result;
	}
	return last;	
}

template<class InputIt, class UnaryPredicate>
constexpr bool all_of(InputIt first, InputIt last, UnaryPredicate p, thread_pool& pool) {
	return find_if_not(first, last, p, pool) == last;
}

template<class InputIt, class UnaryPredicate>
constexpr bool any_of(InputIt first, InputIt last, UnaryPredicate p, thread_pool& pool)
{
	return find_if(first, last, p, pool) != last;
}

template<class InputIt, class UnaryPredicate>
constexpr bool none_of(InputIt first, InputIt last, UnaryPredicate p, thread_pool& pool)
{
	return std::find_if(first, last, p, pool) == last;
}

template<class InputIt, class T>
typename std::iterator_traits<InputIt>::difference_type
count(InputIt first, InputIt last, const T& value, thread_pool& pool) {
	unsigned int avaliable_threads = pool.get_thread_count();
	size_t length = std::distance(first, last);
	size_t portion = length / avaliable_threads;
	std::vector<std::future<std::iterator_traits<InputIt>::difference_type>> partial_results = std::vector<std::future<std::iterator_traits<InputIt>::difference_type>>(avaliable_threads);
	for (unsigned int thread = 0; thread < avaliable_threads; thread++) {
		InputIt partial_first = first + (thread * portion);
		InputIt partial_last = first + ((thread + 1) * portion);
		partial_results[thread] = pool.add_task([](InputIt first, InputIt last, const T& value) {
			typename std::iterator_traits<InputIt>::difference_type ret = 0;
			for (; first != last; ++first) {
				if (*first == value) {
					ret++;
				}
			}
			return ret;
		}, partial_first, partial_last, value);
	}

	typename std::iterator_traits<InputIt>::difference_type res = 0;
	for (unsigned int thread = 0; thread < avaliable_threads; thread++) {
		 res += partial_results[thread].get();
	}

	return res;
}

template<class InputIt, class UnaryPredicate>
typename std::iterator_traits<InputIt>::difference_type
count_if(InputIt first, InputIt last, UnaryPredicate p, thread_pool& pool) {
	unsigned int avaliable_threads = pool.get_thread_count();
	size_t length = std::distance(first, last);
	size_t portion = length / avaliable_threads;
	std::vector<std::future<std::iterator_traits<InputIt>::difference_type>> partial_results = std::vector<std::future<std::iterator_traits<InputIt>::difference_type>>(avaliable_threads);
	for (unsigned int thread = 0; thread < avaliable_threads; thread++) {
		InputIt partial_first = first + (thread * portion);
		InputIt partial_last = first + ((thread + 1) * portion);
		partial_results[thread] = pool.add_task([](InputIt first, InputIt last, UnaryPredicate p) {
			typename std::iterator_traits<InputIt>::difference_type ret = 0;
			for (; first != last; ++first) {
				if (p(*first)) {
					ret++;
				}
			}
			return ret;
			}, partial_first, partial_last, p);
	}

	typename std::iterator_traits<InputIt>::difference_type res = 0;
	for (unsigned int thread = 0; thread < avaliable_threads; thread++) {
		res += partial_results[thread].get();
	}

	return res;
}

template<class InputIt, class UnaryFunction>
constexpr UnaryFunction for_each(InputIt first, InputIt last, UnaryFunction f, thread_pool& pool) {
	unsigned int avaliable_threads = pool.get_thread_count();
	size_t length = std::distance(first, last);
	size_t portion = length / avaliable_threads;

	std::vector<std::future<bool>> empty_result(avaliable_threads);
	for (unsigned int thread = 0; thread < avaliable_threads; thread++) {
		InputIt partial_first = first + (thread * portion);
		InputIt partial_last = first + ((thread + 1) * portion);
		empty_result[thread] = pool.add_task([](InputIt first, InputIt last, UnaryFunction f) -> bool{
			for (; first != last; ++first) {
				f(*first);
			}
			return true;
		}, partial_first, partial_last, f);
	}

	for (unsigned int thread = 0; thread < avaliable_threads; thread++) {
		empty_result[thread].get();
	}

	return f;
}