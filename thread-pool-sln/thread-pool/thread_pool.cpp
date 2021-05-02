#include "thread_pool.h"

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

	while (worker_running) {
		auto task = m_queue.pop();
		if (nullptr != task) {
			task();
		}
		else {
			worker_running = false;
			m_queue.push(nullptr);
		}
	}
}
