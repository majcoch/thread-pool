#include "thread_pool.h"

#include <iostream>
/* Macro for mutex variable name */
#define SCREEN_GUARD screenGuard
/* Screen log printing mutex */
std::mutex SCREEN_GUARD;
/* Thread safe macro for logging to standard output */
#define SAFE_LOG(message) SCREEN_GUARD.lock(); \
                          std::cout <<"Thread [" << std::this_thread::get_id() << "]: " << (message) << std::endl; \
                          SCREEN_GUARD.unlock();




thread_pool::thread_pool() {
	unsigned int hw_threads = std::thread::hardware_concurrency();
	m_thread_count = hw_threads;
	for (unsigned int t = 0; t < hw_threads; t++) {
		m_threads.emplace_back(std::thread(&thread_pool::m_worker_thread, this));
	}
}

thread_pool::thread_pool(unsigned int threads) {
	m_thread_count = threads;
	for (unsigned int t = 0; t < threads; t++) {
		m_threads.emplace_back(std::thread(&thread_pool::m_worker_thread, this));
	}
}

unsigned int thread_pool::get_thread_count() {
	return m_thread_count;
}

thread_pool::~thread_pool() {
	m_queue.push(nullptr); // poison pill
	for (size_t i = 0; i < m_threads.size(); i++) {
		m_threads[i].join();
	}
}

void thread_pool::m_worker_thread() {
	bool worker_running = true;
	//SAFE_LOG("I'm alive");

	while (worker_running) {
		auto task = m_queue.pop();
		if (nullptr != task) {
			//SAFE_LOG("Executing task...");
			task();
		}
		else {
			worker_running = false;
			m_queue.push(nullptr);
			//SAFE_LOG("I'm dead");
		}
	}
}
