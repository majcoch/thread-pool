#pragma once
#include <deque>
#include <mutex>

template<typename T> class blocking_queue {
public:
	void push(const T &item);
	T pop();

private:
	std::deque<T> m_queue;
	std::mutex m_mutex;
	std::condition_variable m_condition;
};

template<typename T>
inline void blocking_queue<T>::push(const T& item) {
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		m_queue.push_front(item);
	}
	m_condition.notify_one();
}

template<typename T>
inline T blocking_queue<T>::pop() {
	std::unique_lock<std::mutex> lock(m_mutex);
	m_condition.wait(lock, [=] { return !m_queue.empty(); });
	T rc(std::move(m_queue.back()));
	m_queue.pop_back();
	return rc;
}