#pragma once

#include <deque>
#include <mutex>

template<typename T> class blocking_queue {
public:
	void push(const T &item);
	T pop();
private:
	std::mutex              d_mutex;
	std::condition_variable d_condition;
	std::deque<T>           d_queue;
};

template<typename T>
inline void blocking_queue<T>::push(const T& item) {
	{
		std::unique_lock<std::mutex> lock(this->d_mutex);
		d_queue.push_front(item);
	}
	this->d_condition.notify_one();
}

template<typename T>
inline T blocking_queue<T>::pop() {
	std::unique_lock<std::mutex> lock(this->d_mutex);
	this->d_condition.wait(lock, [=] { return !this->d_queue.empty(); });
	T rc(std::move(this->d_queue.back()));
	this->d_queue.pop_back();
	return rc;
}