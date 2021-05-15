#pragma once
#include <thread>
#include <vector>
#include <future>
#include <functional>
#include "blocking_queue.h"

class thread_pool {
public:
	thread_pool();
	thread_pool(unsigned int threads);

	template<typename F, typename... Args>
	void add_work(F&& f, Args&&... args);

	template<typename F, typename... Args>
	auto add_task(F&& f, Args&&... args)->std::future<typename std::result_of<F(Args...)>::type>;

	unsigned int get_thread_count();

	~thread_pool();

private:
	unsigned int m_thread_count;
	std::vector<std::thread> m_threads;
	blocking_queue<std::function<void(void)>> m_queue;
	void m_worker_thread();
};

template<typename F, typename ...Args>
inline void thread_pool::add_work(F&& f, Args && ...args) {
	m_queue.push([=]() { f(args...); });
}

template<typename F, typename ...Args>
inline auto thread_pool::add_task(F&& f, Args && ...args) -> std::future<typename std::result_of<F(Args ...)>::type> {
	auto task = std::make_shared<std::packaged_task<std::result_of<F(Args...)>::type()>>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
	std::future<std::result_of<F(Args...)>::type> result = task->get_future();
	m_queue.push([task]() { (*task)(); });
	return result;
}
