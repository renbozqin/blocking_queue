#ifndef BLOCKING_QUEUE_H
#define BLOCKING_QUEUE_H

#include <iostream>
#include <vector>
#include <queue>
#include <condition_variable>
#include <assert.h>

#define MAX_CAPACITY 20

template<typename T>
class BlockingQueue{
	public:
		BlockingQueue() :mtx(), full_(), empty_(), capacity_(MAX_CAPACITY) { }
		void Put(const T& task);
		T Take();
		T Front(); 
		T Back();
		size_t Size();
		bool Empty();
		void SetCapacity(const size_t capacity);
	private:
		BlockingQueue(const BlockingQueue& rhs);
		BlockingQueue& operator= (const BlockingQueue& rhs);

	private:
		mutable std::mutex mtx;
		std::condition_variable full_;
		std::condition_variable empty_;
		std::queue<T> queue_;
		size_t capacity_; 
};

#endif
